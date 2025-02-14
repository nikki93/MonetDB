/*
 * SPDX-License-Identifier: MPL-2.0
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0.  If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright 1997 - July 2008 CWI, August 2008 - 2023 MonetDB B.V.
 */

/*
 * Authors: M. Ivanova, M. Kersten, N. Nes
 *
 * This module contains primitives for accessing data in FITS file format.
 */

#include "monetdb_config.h"
#include <glob.h>

/* clash with GDK? */
#undef ttype
#include <fitsio.h>
#include <fitsio2.h>
#include <longnam.h>

#include "fits.h"
#include "mutils.h"
#include "sql_mvc.h"
#include "sql_scenario.h"
#include "sql_execute.h"
#include "sql.h"
#include "mal_exception.h"

#define FITS_INS_COL "INSERT INTO sys.fits_columns(id, name, type, units, number, table_id) \
	 VALUES(%d,'%s','%s','%s',%d,%d);"
#define ATTACHDIR "call sys.fitsattach('%s');"

static void
FITSinitCatalog(mvc *m)
{
	sql_schema *sch;
	sql_table *fits_tp, *fits_fl, *fits_tbl, *fits_col;
	sql_column *col = NULL;

	sch = mvc_bind_schema(m, "sys");

	fits_fl = mvc_bind_table(m, sch, "fits_files");
	if (fits_fl == NULL) {
		mvc_create_table(&fits_fl, m, sch, "fits_files", tt_table, 0, SQL_PERSIST, 0, 2, 0);
		mvc_create_column_(&col, m, fits_fl, "id", "int", 32);
		mvc_create_column_(&col, m, fits_fl, "name", "varchar", 80);
	}

	fits_tbl = mvc_bind_table(m, sch, "fits_tables");
	if (fits_tbl == NULL) {
		mvc_create_table(&fits_tbl, m, sch, "fits_tables", tt_table, 0, SQL_PERSIST, 0, 8, 0);
		mvc_create_column_(&col, m, fits_tbl, "id", "int", 32);
		mvc_create_column_(&col, m, fits_tbl, "name", "varchar", 80);
		mvc_create_column_(&col, m, fits_tbl, "columns", "int", 32);
		mvc_create_column_(&col, m, fits_tbl, "file_id", "int", 32);
		mvc_create_column_(&col, m, fits_tbl, "hdu", "int", 32);
		mvc_create_column_(&col, m, fits_tbl, "date", "varchar", 80);
		mvc_create_column_(&col, m, fits_tbl, "origin", "varchar", 80);
		mvc_create_column_(&col, m, fits_tbl, "comment", "varchar", 80);
	}

	fits_col = mvc_bind_table(m, sch, "fits_columns");
	if (fits_col == NULL) {
		mvc_create_table(&fits_col, m, sch, "fits_columns", tt_table, 0, SQL_PERSIST, 0, 6, 0);
		mvc_create_column_(&col, m, fits_col, "id", "int", 32);
		mvc_create_column_(&col, m, fits_col, "name", "varchar", 80);
		mvc_create_column_(&col, m, fits_col, "type", "varchar", 80);
		mvc_create_column_(&col, m, fits_col, "units", "varchar", 80);
		mvc_create_column_(&col, m, fits_col, "number", "int", 32);
		mvc_create_column_(&col, m, fits_col, "table_id", "int", 32);
	}

	fits_tp = mvc_bind_table(m, sch, "fits_table_properties");
	if (fits_tp == NULL) {
		mvc_create_table(&fits_tp, m, sch, "fits_table_properties", tt_table, 0, SQL_PERSIST, 0, 5, 0);
		mvc_create_column_(&col, m, fits_tp, "table_id", "int", 32);
		mvc_create_column_(&col, m, fits_tp, "xtension", "varchar", 80);
		mvc_create_column_(&col, m, fits_tp, "bitpix", "int", 32);
		mvc_create_column_(&col, m, fits_tp, "stilvers", "varchar", 80);
		mvc_create_column_(&col, m, fits_tp, "stilclas", "varchar", 80);
	}
}

static int
fits2mtype(int t, int rep)
{
	if (rep > 1) {
		return TYPE_blob;
	}
	switch (t) {
	case TBIT:
	case TLOGICAL:
		return TYPE_bit;
	case TBYTE:
	case TSBYTE:
		return TYPE_bte;
	case TSTRING:
		return TYPE_str;
	case TUSHORT:
	case TSHORT:
		return TYPE_sht;
	case TUINT:
	case TINT:
		return TYPE_int;
	case TLONG:
	case TULONG:
	case TLONGLONG:
		return TYPE_lng;
	case TFLOAT:
		return TYPE_flt;
	case TDOUBLE:
		return TYPE_dbl;
	/* missing */
	case TCOMPLEX:
	case TDBLCOMPLEX:
		return -1;
	}
	return -1;
}

static int
fits2subtype(sql_subtype *tpe, int t, long rep, long wid) /* type long used by fits library */
{
	if (rep > 1) {
		sql_find_subtype(tpe, "blob", (unsigned int)rep*wid, 0);
		return 1;
	}
	switch (t) {
	case TBIT:
	case TLOGICAL:
		sql_find_subtype(tpe, "boolean", 0, 0);
		break;
	case TBYTE:
	case TSBYTE:
		sql_find_subtype(tpe, "char", 1, 0);
		break;
	case TSTRING:
		sql_find_subtype(tpe, "varchar", (unsigned int)wid, 0);
		break;
	case TUSHORT:
	case TSHORT:
		sql_find_subtype(tpe, "smallint", 16, 0);
		break;
	case TUINT:
	case TINT:
		sql_find_subtype(tpe, "int", 32, 0);
		break;
	case TULONG:
	case TLONG:
	case TLONGLONG:
		sql_find_subtype(tpe, "bigint", 64, 0);
		break;
	case TFLOAT:
		sql_find_subtype(tpe, "real", 32, 0);
		break;
	case TDOUBLE:
		sql_find_subtype(tpe, "double", 51, 0);
		break;
	/* missing */
	case TCOMPLEX:
	case TDBLCOMPLEX:
		return -1;
	}
	return 1;
}

str FITSexportTable(Client cntxt, MalBlkPtr mb, MalStkPtr stk, InstrPtr pci)
{
	str msg = MAL_SUCCEED;
	str tname = *getArgReference_str(stk, pci, 1);
	mvc *m = NULL;
	sql_trans *tr;
	sql_schema *sch;
	sql_table *tbl, *column, *tables = NULL;
	sql_column *col;
	oid rid = oid_nil;
	str type, name, *colname, *tform;
	fitsfile *fptr;
	char filename[BUFSIZ];
	size_t nrows = 0;
	long optimal; /* type long used by fits library */
	rids * rs;

	lng tm0, texportboolean=0, texportchar=0, texportstring=0, texportshort=0, texportint=0, texportlng=0, texportfloat=0, texportdouble=0;
	size_t numberrow = 0, dimension = 0;
	int cc = 0, status = 0, j = 0, columns, *fid, block = 0;
	int boolcols = 0, charcols = 0, strcols = 0, shortcols = 0, intcols = 0, lngcols = 0, floatcols = 0, doublecols = 0;
	int hdutype;

	char *charvalue, *readcharrows;
	str strvalue; char **readstrrows;
	short *shortvalue, *readshortrows;
	int *intvalue, *readintrows;
	lng *lngvalue, *readlngrows;
	float *realvalue, *readfloatrows;
	double *doublevalue, *readdoublerows;
	_Bool *boolvalue, *readboolrows;

	if ((msg = getSQLContext(cntxt, mb, &m, NULL)) != MAL_SUCCEED)
		return msg;
	if ((msg = checkSQLContext(cntxt)) != MAL_SUCCEED)
		return msg;

	tr = m->session->tr;
	sqlstore *store = tr->store;
	sch = mvc_bind_schema(m, "sys");

	/* First step: look if the table exists in the database. If the table is not in the database, the export function cannot continue */

	tbl = mvc_bind_table(m, sch, tname);
	if (tbl == NULL) {
		msg = createException (MAL, "fits.exporttable", SQLSTATE(FI000) "Table %s is missing.\n", tname);
		return msg;
	}


	columns = ol_length((*tbl).columns);
	colname = (str *) GDKmalloc(columns * sizeof(str));
	tform = (str *) GDKmalloc(columns * sizeof(str));
	if (colname == NULL || tform == NULL) {
		GDKfree(colname);
		GDKfree(tform);
		throw(MAL, "fits.exporttable", SQLSTATE(HY013) MAL_MALLOC_FAIL);
	}

	TRC_DEBUG(FITS, "Number of columns: %d\n", columns);

	tables = mvc_bind_table(m, sch, "_tables");
	col = mvc_bind_column(m, tables, "name");
	rid = store->table_api.column_find_row(m->session->tr, col, tname, NULL);

	col = mvc_bind_column(m, tables, "id");
	fid = (int*) store->table_api.column_find_value(m->session->tr, col, rid);

	column =  mvc_bind_table(m, sch, "_columns");
	col = mvc_bind_column(m, column, "table_id");

	rs = store->table_api.rids_select(m->session->tr, col, (void *) fid, (void *) fid, NULL);
	GDKfree(fid);

	while ((rid = store->table_api.rids_next(rs)), !is_oid_nil(rid))
	{
		col = mvc_bind_column(m, column, "name");
		name = (char *) store->table_api.column_find_value(m->session->tr, col, rid);
		colname[j] = toLower(name);
		GDKfree(name);

		col = mvc_bind_column(m, column, "type");
		type = (char *) store->table_api.column_find_value(m->session->tr, col, rid);

		if (strcmp(type,"boolean")==0) tform[j] = "1L";

 		if (strcmp(type,"char")==0) tform[j] = "1S";

		if (strcmp(type,"varchar")==0) tform[j] = "8A";

		if (strcmp(type,"smallint")==0) tform[j] = "1I";

		if (strcmp(type,"int")==0) tform[j] = "1J";

		if (strcmp(type,"bigint")==0) tform[j] = "1K";

		if (strcmp(type,"real")==0) tform[j] = "1E";

		if (strcmp(type,"double")==0) tform[j] = "1D";
		GDKfree(type);

		j++;
	}

	col = mvc_bind_column(m, tbl, colname[0]);

	nrows = store->storage_api.count_col(tr, col, 0);
	assert(nrows <= (size_t) GDK_oid_max);

	snprintf(filename,BUFSIZ,"\n%s.fit",tname);
	TRC_INFO(FITS, "Filename: %s\n", filename);

	MT_remove(filename);

	status=0;

	fits_create_file(&fptr, filename, &status);
	fits_create_img(fptr,  USHORT_IMG, 0, NULL, &status);
	fits_close_file(fptr, &status);
	fits_open_file(&fptr, filename, READWRITE, &status);

	fits_movabs_hdu(fptr, 1, &hdutype, &status);
	fits_create_tbl( fptr, BINARY_TBL, 0, columns, colname, tform, NULL, tname, &status);

	for (cc = 0; cc < columns; cc++)
	{
		char * columntype;
		col = mvc_bind_column(m, tbl, colname[cc]);
		columntype = col -> type.type->base.name;

		if (strcmp(columntype,"boolean")==0)
		{
			boolcols++; dimension = 0; block = 0;
			fits_get_rowsize(fptr,&optimal,&status);
			readboolrows = (_Bool *) GDKmalloc (sizeof(_Bool) * optimal);

			for (numberrow = 0; numberrow < nrows ; numberrow++)
			{
				boolvalue = (_Bool*) store->table_api.column_find_value(m->session->tr, col, (oid) numberrow);
				readboolrows[dimension] = *boolvalue;
				GDKfree(boolvalue);
				dimension++;

				if (dimension == (size_t) optimal)
				{
					dimension = 0;
					tm0 = GDKusec();
					fits_write_col(fptr, TLOGICAL, cc+1, (optimal*block)+1, 1, optimal, readboolrows, &status);
					texportboolean += GDKusec() - tm0;
					GDKfree(readboolrows);
					readboolrows = (_Bool *) GDKmalloc (sizeof(_Bool) * optimal);
					block++;
				}
			}
			tm0 = GDKusec();
			fits_write_col(fptr, TLOGICAL, cc+1, (optimal*block)+1, 1, dimension, readboolrows, &status);
			texportboolean += GDKusec() - tm0;
			GDKfree(readboolrows);
		}

		if (strcmp(columntype,"char")==0)
		{
			charcols++; dimension = 0; block = 0;
			fits_get_rowsize(fptr,&optimal,&status);
			readcharrows = (char *) GDKmalloc (sizeof(char) * optimal);

			for (numberrow = 0; numberrow < nrows ; numberrow++)
			{
				charvalue = (char*) store->table_api.column_find_value(m->session->tr, col, (oid) numberrow);
				readcharrows[dimension] = *charvalue;
				GDKfree(charvalue);
				dimension++;

				if (dimension == (size_t) optimal)
				{
					dimension = 0;
					tm0 = GDKusec();
					fits_write_col(fptr, TBYTE, cc+1, (optimal*block)+1, 1, optimal, readcharrows, &status);
					texportchar += GDKusec() - tm0;
					GDKfree(readcharrows);
					readcharrows = (char *) GDKmalloc (sizeof(char) * optimal);
					block++;
				}
			}
			tm0 = GDKusec();
			fits_write_col(fptr, TBYTE, cc+1, (optimal*block)+1, 1, dimension, readcharrows, &status);
			texportchar += GDKusec() - tm0;
			GDKfree(readcharrows);
		}

		if (strcmp(columntype,"varchar")==0)
		{
			strcols++; dimension=0; block=0;
			fits_get_rowsize(fptr,&optimal,&status);
			readstrrows = (char **) GDKmalloc (sizeof(char *) * optimal);

			for (numberrow = 0; numberrow < nrows ; numberrow++)
			{
				strvalue = (char *) store->table_api.column_find_value(m->session->tr, col, (oid) numberrow);
				readstrrows[dimension] = strvalue;
				dimension++;

				if (dimension == (size_t) optimal)
				{
					dimension = 0;
					tm0 = GDKusec();
					fits_write_col_str(fptr, cc+1, (optimal*block)+1, 1, optimal, readstrrows, &status);
					texportstring += GDKusec() - tm0;
					for (dimension = 0; dimension < (size_t) optimal; dimension++)
						GDKfree(readstrrows[dimension]);
					dimension = 0;
					GDKfree(readstrrows);
					readstrrows = (char **) GDKmalloc(sizeof(char *) * optimal);
					block++;
				}
			}
			tm0 = GDKusec();
			fits_write_col_str(fptr, cc+1, (optimal*block)+1, 1, dimension, readstrrows, &status);
			texportstring += GDKusec() - tm0;
			for (numberrow = 0; numberrow < dimension; numberrow++)
				GDKfree(readstrrows[numberrow]);
			GDKfree(readstrrows);
		}

		if (strcmp(columntype,"smallint")==0)
		{
			shortcols++; dimension = 0; block = 0;
			fits_get_rowsize(fptr,&optimal,&status);
			readshortrows = (short *) GDKmalloc (sizeof(short) * optimal);

			for (numberrow = 0; numberrow < nrows ; numberrow++)
			{
				shortvalue = (short*) store->table_api.column_find_value(m->session->tr, col, (oid) numberrow);
				readshortrows[dimension] = *shortvalue;
				GDKfree(shortvalue);
				dimension++;

				if (dimension == (size_t) optimal)
				{
					dimension = 0;
					tm0 = GDKusec();
					fits_write_col(fptr, TSHORT, cc+1, (optimal*block)+1, 1, optimal, readshortrows, &status);
					texportshort += GDKusec() - tm0;
					GDKfree(readshortrows);
					readshortrows = (short *) GDKmalloc (sizeof(short) * optimal);
					block++;
				}
			}
			tm0 = GDKusec();
			fits_write_col(fptr, TSHORT, cc+1, (optimal*block)+1, 1, dimension, readshortrows, &status);
			texportshort += GDKusec() - tm0;
			GDKfree(readshortrows);
		}

		if (strcmp(columntype,"int")==0)
		{
			intcols++; dimension = 0; block = 0;
			fits_get_rowsize(fptr,&optimal,&status);
			readintrows = (int *) GDKmalloc (sizeof(int) * optimal);

			for (numberrow = 0; numberrow < nrows ; numberrow++)
			{
				intvalue = (int*) store->table_api.column_find_value(m->session->tr, col, (oid) numberrow);
				readintrows[dimension] = *intvalue;
				GDKfree(intvalue);
				dimension++;

				if (dimension == (size_t) optimal)
				{
					dimension = 0;
					tm0 = GDKusec();
					fits_write_col(fptr, TINT, cc+1, (optimal*block)+1, 1, optimal, readintrows, &status);
					texportint += GDKusec() - tm0;
					GDKfree(readintrows);
					readintrows = (int *) GDKmalloc (sizeof(int) * optimal);
					block++;
				}
			}
			tm0 = GDKusec();
			fits_write_col(fptr, TINT, cc+1, (optimal*block)+1, 1, dimension, readintrows, &status);
			texportint += GDKusec() - tm0;
			GDKfree(readintrows);
		}

		if (strcmp(columntype,"bigint")==0)
		{
			lngcols++; dimension = 0; block = 0;
			fits_get_rowsize(fptr,&optimal,&status);
			readlngrows = (lng *) GDKmalloc (sizeof(lng) * optimal);

			for (numberrow = 0; numberrow < nrows ; numberrow++)
			{
				lngvalue = (lng*) store->table_api.column_find_value(m->session->tr, col, (oid) numberrow);
				readlngrows[dimension] = *lngvalue;
				GDKfree(lngvalue);
				dimension++;

				if (dimension == (size_t) optimal)
				{
					dimension = 0;
					tm0 = GDKusec();
					fits_write_col(fptr, TLONG, cc+1, (optimal*block)+1, 1, optimal, readlngrows, &status);
					texportlng += GDKusec() - tm0;
					GDKfree(readlngrows);
					readlngrows = (lng *) GDKmalloc (sizeof(lng) * optimal);
					block++;
				}
			}
			tm0 = GDKusec();
			fits_write_col(fptr, TLONG, cc+1, (optimal*block)+1, 1, dimension, readlngrows, &status);
			texportlng += GDKusec() - tm0;
			GDKfree(readlngrows);
		}

		if (strcmp(columntype,"real")==0)
		{
			floatcols++; dimension = 0; block = 0;
			fits_get_rowsize(fptr,&optimal,&status);
			readfloatrows = (float *) GDKmalloc (sizeof(float) * optimal);

			for (numberrow = 0; numberrow < nrows ; numberrow++)
			{
				realvalue = (float*) store->table_api.column_find_value(m->session->tr, col, (oid) numberrow);
				readfloatrows[dimension] = *realvalue;
				GDKfree(realvalue);
				dimension++;

				if (dimension == (size_t) optimal)
				{
					dimension = 0;
					tm0 = GDKusec();
					fits_write_col(fptr, TFLOAT, cc+1, (optimal*block)+1, 1, optimal, readfloatrows, &status);
					texportfloat += GDKusec() - tm0;
					GDKfree(readfloatrows);
					readfloatrows = (float *) GDKmalloc (sizeof(float) * optimal);
					block++;
				}
			}
			tm0 = GDKusec();
			fits_write_col(fptr, TFLOAT, cc+1, (optimal*block)+1, 1, dimension, readfloatrows, &status);
			texportfloat += GDKusec() - tm0;
			GDKfree(readfloatrows);
		}

		if (strcmp(columntype,"double")==0)
		{
			doublecols++; dimension = 0; block = 0;
			fits_get_rowsize(fptr,&optimal,&status);
			readdoublerows = (double *) GDKmalloc (sizeof(double) * optimal);

			for (numberrow = 0; numberrow < nrows ; numberrow++)
			{
				doublevalue = (double*) store->table_api.column_find_value(m->session->tr, col, (oid) numberrow);
				readdoublerows[dimension] = *doublevalue;
				GDKfree(doublevalue);
				dimension++;

				if (dimension == (size_t) optimal)
				{
					dimension = 0;
					tm0 = GDKusec();
					fits_write_col(fptr, TDOUBLE, cc+1, (optimal*block)+1, 1, optimal, readdoublerows, &status);
					texportdouble += GDKusec() - tm0;
					GDKfree(readdoublerows);
					readdoublerows = (double *) GDKmalloc (sizeof(double) * optimal);
					block++;
				}
			}
			tm0 = GDKusec();
			fits_write_col(fptr, TDOUBLE, cc+1, (optimal*block)+1, 1, optimal, readdoublerows, &status);
			texportdouble += GDKusec() - tm0;
			GDKfree(readdoublerows);
		}
	}


	// print all the times that were needed to export each one of the columns
	if (texportboolean > 0)		TRC_DEBUG(FITS, "%d Boolean\tcolumn(s) exported in "LLFMT" usec\n", boolcols, texportboolean);
	if (texportchar > 0)		TRC_DEBUG(FITS, "%d Char\t\tcolumn(s) exported in "LLFMT" usec\n", charcols, texportchar);
	if (texportstring > 0)		TRC_DEBUG(FITS, "%d String\tcolumn(s) exported in "LLFMT" usec\n", strcols, texportstring);
	if (texportshort > 0)		TRC_DEBUG(FITS, "%d Short\t\tcolumn(s) exported in "LLFMT" usec\n", shortcols, texportshort);
	if (texportint > 0)			TRC_DEBUG(FITS, "%d Integer\tcolumn(s) exported in "LLFMT" usec\n", intcols, texportint);
	if (texportlng > 0)			TRC_DEBUG(FITS, "%d Long\t\tcolumn(s) exported in "LLFMT" usec\n", lngcols, texportlng);
	if (texportfloat > 0)		TRC_DEBUG(FITS, "%d Float\t\tcolumn(s) exported in "LLFMT" usec\n", floatcols, texportfloat);
	if (texportdouble > 0)		TRC_DEBUG(FITS, "%d Double\tcolumn(s) exported in "LLFMT" usec\n", doublecols, texportdouble);


	fits_close_file(fptr, &status);
	return msg;
}


str FITSdir(Client cntxt, MalBlkPtr mb, MalStkPtr stk, InstrPtr pci)
{
	str msg = MAL_SUCCEED;
	str dir = *getArgReference_str(stk, pci, 1);
	DIR *dp;
	struct dirent *ep;
	fitsfile *fptr;
	char *s;
	int status = 0;
	(void)mb;

	dp = opendir(dir);
	if (dp != NULL) {
		char stmt[BUFSIZ];
		char fname[BUFSIZ];

		s = stmt;

		while ((ep = readdir(dp)) != NULL && !msg) {
			snprintf(fname, sizeof(fname), "%s/%s", dir, ep->d_name);
			status = 0;
			fits_open_file(&fptr, fname, READONLY, &status);
			if (status == 0) {
				char *filename = SQLescapeString(fname);
				if (!filename) {
					msg = createException(MAL, "fits.listdir", SQLSTATE(HY013) MAL_MALLOC_FAIL);
					break;
				}
				snprintf(stmt, sizeof(stmt), ATTACHDIR, filename);
				GDKfree(filename);
				TRC_DEBUG(FITS, "Executing: %s\n", s);
				msg = SQLstatementIntern(cntxt, s, "fits.listofdir", TRUE, FALSE, NULL);
				fits_close_file(fptr, &status);
			}

		}
		(void)closedir(dp);
	} else
		msg = createException(MAL, "listdir", SQLSTATE(FI000) "Couldn't open the directory");

	return msg;
}

str FITSdirpat(Client cntxt, MalBlkPtr mb, MalStkPtr stk, InstrPtr pci)
{
	str msg = MAL_SUCCEED;
	str dir = *getArgReference_str(stk, pci, 1);
	str pat = *getArgReference_str(stk, pci, 2);
	fitsfile *fptr;
	char *s;
	int status = 0;
	glob_t globbuf;
	char fulldirectory[BUFSIZ];
	size_t j = 0;

	(void)mb;

	globbuf.gl_offs = 0;
	snprintf(fulldirectory, sizeof(fulldirectory), "%s/%s", dir, pat);
	glob(fulldirectory, GLOB_DOOFFS, NULL, &globbuf);

	TRC_DEBUG(FITS, "Fulldir: %s - Size: %zu\n", fulldirectory, globbuf.gl_pathc);

	if (globbuf.gl_pathc == 0)
		throw(MAL, "fits.listdirpat", SQLSTATE(FI000) "Couldn't open the directory or there are no files that match the pattern");

	for (j = 0; j < globbuf.gl_pathc; j++) {
		char stmt[BUFSIZ];
		char fname[BUFSIZ];

		s = stmt;
		strcpy_len(fname, globbuf.gl_pathv[j], sizeof(fname));
		status = 0;
		fits_open_file(&fptr, fname, READONLY, &status);
		if (status == 0) {
			char *filename = SQLescapeString(fname);
			if (!filename) {
				throw(MAL, "fits.listdirpat", SQLSTATE(HY013) MAL_MALLOC_FAIL);
			}
			snprintf(stmt, sizeof(stmt), ATTACHDIR, filename);
			GDKfree(filename);
			TRC_DEBUG(FITS, "Executing: %s\n", s);
			msg = SQLstatementIntern(cntxt, s, "fits.listofdirpat", TRUE, FALSE, NULL);
			fits_close_file(fptr, &status);

			break;
		}
	}

	return msg;
}


str
FITStest(int *res, str *fname)
{
	fitsfile *fptr;       /* pointer to the FITS file, defined in fitsio.h */
	str msg = MAL_SUCCEED;
	int status = 0, hdutype;

	*res = 0;
	if (fits_open_file(&fptr, *fname, READONLY, &status))
		msg = createException(MAL, "fits.test", SQLSTATE(FI000) "Missing FITS file %s", *fname);
	else {
		fits_movabs_hdu(fptr, 2, &hdutype, &status);
		*res = hdutype;
		fits_close_file(fptr, &status);
	}

	return msg;
}

str FITSattach(Client cntxt, MalBlkPtr mb, MalStkPtr stk, InstrPtr pci)
{
	mvc *m = NULL;
	sql_trans *tr;
	sql_schema *sch;
	sql_table *fits_tp, *fits_fl, *fits_tbl, *fits_col, *tbl = NULL;
	sql_column *col;
	str msg = MAL_SUCCEED;
	str fname = *getArgReference_str(stk, pci, 1);
	fitsfile *fptr;  /* pointer to the FITS file */
	int status = 0, i, j, hdutype, hdunum = 1, cnum = 0, bitpixnumber = 0;
	oid fid, tid, cid, rid = oid_nil;
	char tname[BUFSIZ], *tname_low = NULL, *s, bname[BUFSIZ-100], stmt[BUFSIZ];
	long tbcol; /* type long used by fits library */
	char cname[BUFSIZ], tform[BUFSIZ], tunit[BUFSIZ], tnull[BUFSIZ], tdisp[BUFSIZ];
	char *esc_cname, *esc_tform, *esc_tunit;
	double tscal, tzero;
	char xtensionname[BUFSIZ] = "", stilversion[BUFSIZ] = "";
	char stilclass[BUFSIZ] = "", tdate[BUFSIZ] = "", orig[BUFSIZ] = "", comm[BUFSIZ] = "";

	if ((msg = getSQLContext(cntxt, mb, &m, NULL)) != MAL_SUCCEED)
		return msg;
	if ((msg = checkSQLContext(cntxt)) != MAL_SUCCEED)
		return msg;

	if (fits_open_file(&fptr, fname, READONLY, &status)) {
		msg = createException(MAL, "fits.attach", SQLSTATE(FI000) "Missing FITS file %s.\n", fname);
		return msg;
	}

	tr = m->session->tr;
	sch = mvc_bind_schema(m, "sys");
	sqlstore *store = tr->store;

	fits_fl = mvc_bind_table(m, sch, "fits_files");
	if (fits_fl == NULL)
		FITSinitCatalog(m);

	fits_fl = mvc_bind_table(m, sch, "fits_files");
	fits_tbl = mvc_bind_table(m, sch, "fits_tables");
	fits_col = mvc_bind_table(m, sch, "fits_columns");
	fits_tp = mvc_bind_table(m, sch, "fits_table_properties");

	/* check if the file is already attached */
	col = mvc_bind_column(m, fits_fl, "name");
	rid = store->table_api.column_find_row(m->session->tr, col, fname, NULL);
	if (!is_oid_nil(rid)) {
		fits_close_file(fptr, &status);
		throw(MAL, "fits.attach", SQLSTATE(FI000) "File %s already attached\n", fname);
	}

	/* add row in the fits_files catalog table */
	BUN offset;
	if (store->storage_api.claim_tab(m->session->tr, fits_fl, 1, &offset, NULL) != LOG_OK) {
		fits_close_file(fptr, &status);
		throw(MAL, "fits.attach", SQLSTATE(HY013) MAL_MALLOC_FAIL);
	}
	if (!isNew(fits_fl) && sql_trans_add_dependency_change(m->session->tr, fits_fl->base.id, dml) != LOG_OK) {
		fits_close_file(fptr, &status);
		throw(MAL, "fits.attach", SQLSTATE(HY013) MAL_MALLOC_FAIL);
	}
	col = mvc_bind_column(m, fits_fl, "id");
	fid = store->storage_api.count_col(tr, col, 0) + 1;
	store->storage_api.append_col(m->session->tr,
		mvc_bind_column(m, fits_fl, "id"), offset, NULL, &fid, 1, TYPE_int);
	store->storage_api.append_col(m->session->tr,
		mvc_bind_column(m, fits_fl, "name"), offset, NULL, &fname, 1, TYPE_str);
	col = mvc_bind_column(m, fits_tbl, "id");
	tid = store->storage_api.count_col(tr, col, 0) + 1;

	if ((s = strrchr(fname, DIR_SEP)) == NULL)
		s = fname;
	else
		s++;
	if (strcpy_len(bname, s, sizeof(bname)) >= sizeof(bname)) {
		fits_close_file(fptr, &status);
		throw(MAL, "fits.attach", SQLSTATE(FI000) "File name too long\n");
	}
	strcpy(bname, s);
	s = strrchr(bname, '.');
	if (s) *s = 0;

	fits_get_num_hdus(fptr, &hdunum, &status);
	for (i = 1; i <= hdunum; i++) {
		fits_movabs_hdu(fptr, i, &hdutype, &status);
		if (hdutype != ASCII_TBL && hdutype != BINARY_TBL)
			continue;

		/* SQL table name - the name of FITS extention */
		fits_read_key(fptr, TSTRING, "EXTNAME", tname, NULL, &status);
		if (status) {
			snprintf(tname, sizeof(tname), "%s_%d", bname, i);
			tname_low = toLower(tname);
			status = 0;
		}else  { /* check table name for existence in the fits catalog */
			tname_low = toLower(tname);
			col = mvc_bind_column(m, fits_tbl, "name");
			rid = store->table_api.column_find_row(m->session->tr, col, tname_low, NULL);
			/* or as regular SQL table */
			tbl = mvc_bind_table(m, sch, tname_low);
			if (!is_oid_nil(rid) || tbl) {
				snprintf(tname, sizeof(tname), "%s_%d", bname, i);
				tname_low = toLower(tname);
			}
		}

		fits_read_key(fptr, TSTRING, "BITPIX", &bitpixnumber, NULL, &status);
		if (status) {
			status = 0;
		}
		fits_read_key(fptr, TSTRING, "DATE-HDU", tdate, NULL, &status);
		if (status) {
			status = 0;
		}
		fits_read_key(fptr, TSTRING, "XTENSION", xtensionname, NULL, &status);
		if (status) {
			status = 0;
		}
		fits_read_key(fptr, TSTRING, "STILVERS", stilversion, NULL, &status);
		if (status) {
			status = 0;
		}
		fits_read_key(fptr, TSTRING, "STILCLAS", stilclass, NULL, &status);
		if (status) {
			status = 0;
		}
		fits_read_key(fptr, TSTRING, "ORIGIN", orig, NULL, &status);
		if (status) {
			status = 0;
		}
		fits_read_key(fptr, TSTRING, "COMMENT", comm, NULL, &status);
		if (status) {
			status = 0;
		}

		fits_get_num_cols(fptr, &cnum, &status);

		BUN offset;
		if (store->storage_api.claim_tab(m->session->tr, fits_tbl, 1, &offset, NULL) != LOG_OK) {
			fits_close_file(fptr, &status);
			throw(MAL, "fits.attach", SQLSTATE(HY013) MAL_MALLOC_FAIL);
		}
		if (!isNew(fits_tbl) && sql_trans_add_dependency_change(m->session->tr, fits_tbl->base.id, dml) != LOG_OK) {
			fits_close_file(fptr, &status);
			throw(MAL, "fits.attach", SQLSTATE(HY013) MAL_MALLOC_FAIL);
		}
		store->storage_api.append_col(m->session->tr,
			mvc_bind_column(m, fits_tbl, "id"), offset, NULL, &tid, 1, TYPE_int);
		store->storage_api.append_col(m->session->tr,
			mvc_bind_column(m, fits_tbl, "name"), offset, NULL, &tname_low, 1, TYPE_str);
		store->storage_api.append_col(m->session->tr,
			mvc_bind_column(m, fits_tbl, "columns"), offset, NULL, &cnum, 1, TYPE_int);
		store->storage_api.append_col(m->session->tr,
			mvc_bind_column(m, fits_tbl, "file_id"), offset, NULL, &fid, 1, TYPE_int);
		store->storage_api.append_col(m->session->tr,
			mvc_bind_column(m, fits_tbl, "hdu"), offset, NULL, &i, 1, TYPE_int);
		char *vptr = tdate;
		store->storage_api.append_col(m->session->tr,
			mvc_bind_column(m, fits_tbl, "date"), offset, NULL, &vptr, 1, TYPE_str);
		vptr = orig;
		store->storage_api.append_col(m->session->tr,
			mvc_bind_column(m, fits_tbl, "origin"), offset, NULL, &vptr, 1, TYPE_str);
		vptr = comm;
		store->storage_api.append_col(m->session->tr,
			mvc_bind_column(m, fits_tbl, "comment"), offset, NULL, &vptr, 1, TYPE_str);

		if (store->storage_api.claim_tab(m->session->tr, fits_tp, 1, &offset, NULL) != LOG_OK) {
			fits_close_file(fptr, &status);
			throw(MAL, "fits.attach", SQLSTATE(HY013) MAL_MALLOC_FAIL);
		}
		if (!isNew(fits_tp) && sql_trans_add_dependency_change(m->session->tr, fits_tp->base.id, dml) != LOG_OK) {
			fits_close_file(fptr, &status);
			throw(MAL, "fits.attach", SQLSTATE(HY013) MAL_MALLOC_FAIL);
		}
		store->storage_api.append_col(m->session->tr,
			mvc_bind_column(m, fits_tp, "table_id"), offset, NULL, &tid, 1, TYPE_int);
		vptr = xtensionname;
		store->storage_api.append_col(m->session->tr,
			mvc_bind_column(m, fits_tp, "xtension"), offset, NULL, &vptr, 1, TYPE_str);
		store->storage_api.append_col(m->session->tr,
			mvc_bind_column(m, fits_tp, "bitpix"), offset, NULL, &bitpixnumber, 1, TYPE_int);
		vptr = stilversion;
		store->storage_api.append_col(m->session->tr,
			mvc_bind_column(m, fits_tp, "stilvers"), offset, NULL, &vptr, 1, TYPE_str);
		vptr = stilclass;
		store->storage_api.append_col(m->session->tr,
			mvc_bind_column(m, fits_tp, "stilclas"), offset, NULL, &vptr, 1, TYPE_str);

		/* read columns description */
		s = stmt;
		col = mvc_bind_column(m, fits_col, "id");
		cid = store->storage_api.count_col(tr, col, 0) + 1;
		for (j = 1; j <= cnum; j++, cid++) {
			fits_get_acolparms(fptr, j, cname, &tbcol, tunit, tform, &tscal, &tzero, tnull, tdisp, &status);
			/* escape the various strings to avoid SQL injection attacks */
			esc_cname = SQLescapeString(cname);
			if (!esc_cname) {
				fits_close_file(fptr, &status);
				throw(MAL, "fits.attach", SQLSTATE(HY013) MAL_MALLOC_FAIL);
			}
			esc_tform = SQLescapeString(tform);
			if (!esc_tform) {
				GDKfree(esc_cname);
				fits_close_file(fptr, &status);
				throw(MAL, "fits.attach", SQLSTATE(HY013) MAL_MALLOC_FAIL);
			}
			esc_tunit = SQLescapeString(tunit);
			if (!esc_tunit) {
				GDKfree(esc_tform);
				GDKfree(esc_cname);
				fits_close_file(fptr, &status);
				throw(MAL, "fits.attach", SQLSTATE(HY013) MAL_MALLOC_FAIL);
			}
			snprintf(stmt, sizeof(stmt), FITS_INS_COL, (int)cid, esc_cname, esc_tform, esc_tunit, j, (int)tid);
			GDKfree(esc_tunit);
			GDKfree(esc_tform);
			GDKfree(esc_cname);
			msg = SQLstatementIntern(cntxt, s, "fits.attach", TRUE, FALSE, NULL);
			if (msg != MAL_SUCCEED) {
				fits_close_file(fptr, &status);
				return msg;
			}
		}
		tid++;
	}
	fits_close_file(fptr, &status);

	return MAL_SUCCEED;
}

str FITSloadTable(Client cntxt, MalBlkPtr mb, MalStkPtr stk, InstrPtr pci)
{
	mvc *m = NULL;
	sql_schema *sch;
	sql_table *fits_fl, *fits_tbl, *tbl = NULL;
	sql_column *col;
	sql_subtype tpe;
	fitsfile *fptr;
	str tname = *getArgReference_str(stk, pci, 1);
	str fname;
	str msg = MAL_SUCCEED;
	oid rid = oid_nil, frid = oid_nil;
	int status = 0, cnum = 0, *fid, *hdu, hdutype, j, anynull = 0, mtype;
	int *tpcode = NULL;
	long *rep = NULL, *wid = NULL, rows; /* type long used by fits library */
	char keywrd[80], **cname, nm[FLEN_VALUE];
	const void *nilptr;
	BUN offset;
	BAT *pos = NULL;

	if ((msg = getSQLContext(cntxt, mb, &m, NULL)) != MAL_SUCCEED)
		return msg;
	if ((msg = checkSQLContext(cntxt)) != MAL_SUCCEED)
		return msg;
	sch = mvc_bind_schema(m, "sys");

	fits_tbl = mvc_bind_table(m, sch, "fits_tables");
	if (fits_tbl == NULL) {
		msg = createException(MAL, "fits.loadtable", SQLSTATE(FI000) "FITS catalog is missing.\n");
		return msg;
	}

	tbl = mvc_bind_table(m, sch, tname);
	if (tbl) {
		msg = createException(MAL, "fits.loadtable", SQLSTATE(FI000) "Table %s is already created.\n", tname);
		return msg;
	}

	col = mvc_bind_column(m, fits_tbl, "name");
	sqlstore *store = m->session->tr->store;
	rid = store->table_api.column_find_row(m->session->tr, col, tname, NULL);
	if (is_oid_nil(rid)) {
		msg = createException(MAL, "fits.loadtable", SQLSTATE(FI000) "Table %s is unknown in FITS catalog. Attach first the containing file\n", tname);
		return msg;
	}

	/* Open FITS file and move to the table HDU */
	col = mvc_bind_column(m, fits_tbl, "file_id");
	fid = (int*)store->table_api.column_find_value(m->session->tr, col, rid);

	fits_fl = mvc_bind_table(m, sch, "fits_files");
	col = mvc_bind_column(m, fits_fl, "id");
	frid = store->table_api.column_find_row(m->session->tr, col, (void *)fid, NULL);
	GDKfree(fid);
	if (is_oid_nil(frid)) {
		msg = createException(MAL, "fits.loadtable", SQLSTATE(FI000) "Table %s is unknown in FITS catalog. Attach first the containing file\n", tname);
		return msg;
	}
	col = mvc_bind_column(m, fits_fl, "name");
	fname = (char *)store->table_api.column_find_value(m->session->tr, col, frid);
	if (fits_open_file(&fptr, fname, READONLY, &status)) {
		msg = createException(MAL, "fits.loadtable", SQLSTATE(FI000) "Missing FITS file %s.\n", fname);
		GDKfree(fname);
		return msg;
	}
	GDKfree(fname);

	col = mvc_bind_column(m, fits_tbl, "hdu");
	hdu = (int*)store->table_api.column_find_value(m->session->tr, col, rid);
	fits_movabs_hdu(fptr, *hdu, &hdutype, &status);
	if (hdutype != ASCII_TBL && hdutype != BINARY_TBL) {
		msg = createException(MAL, "fits.loadtable", SQLSTATE(FI000) "HDU %d is not a table.\n", *hdu);
		GDKfree(hdu);
		fits_close_file(fptr, &status);
		return msg;
	}
	GDKfree(hdu);

	/* create a SQL table to hold the FITS table */
	/*	col = mvc_bind_column(m, fits_tbl, "columns");
	   cnum = *(int*) store->table_api.column_find_value(m->session->tr, col, rid); */
	fits_get_num_cols(fptr, &cnum, &status);
	mvc_create_table(&tbl, m, sch, tname, tt_table, 0, SQL_PERSIST, 0, cnum, 0);

	// TODO: Check that the allocations succeeded
	tpcode = (int *)GDKzalloc(sizeof(int) * cnum);
	rep = (long *)GDKzalloc(sizeof(long) * cnum);
	wid = (long *)GDKzalloc(sizeof(long) * cnum);
	cname = (char **)GDKzalloc(sizeof(char *) * cnum);

	for (j = 1; j <= cnum; j++) {
		sql_column *col = NULL;
		/*		fits_get_acolparms(fptr, j, cname, &tbcol, tunit, tform, &tscal, &tzero, tnull, tdisp, &status); */
		snprintf(keywrd, 80, "TTYPE%d", j);
		fits_read_key(fptr, TSTRING, keywrd, nm, NULL, &status);
		if (status) {
			snprintf(nm, FLEN_VALUE, "column_%d", j);
			status = 0;
		}
		cname[j - 1] = toLower(nm);
		fits_get_coltype(fptr, j, &tpcode[j - 1], &rep[j - 1], &wid[j - 1], &status);
		fits2subtype(&tpe, tpcode[j - 1], rep[j - 1], wid[j - 1]);

		TRC_DEBUG(FITS, "%d %ld %ld - M: %s\n", tpcode[j-1], rep[j-1], wid[j-1], tpe.type->base.name);

		mvc_create_column(&col, m, tbl, cname[j - 1], &tpe);
	}

	/* data load */
	fits_get_num_rows(fptr, &rows, &status);
	/* Nothing more to do */
	if (rows == 0) {
		goto bailout;
	}

	TRC_INFO(FITS, "Loading %ld rows in table %s\n", rows, tname);

	if (store->storage_api.claim_tab(m->session->tr, tbl, rows, &offset, &pos) != LOG_OK) {
		msg = createException(MAL, "fits.loadtable", SQLSTATE(HY013) MAL_MALLOC_FAIL);
		goto bailout;
	}
	for (j = 1; j <= cnum; j++) {
		BAT *tmp = NULL;
		lng time0 = GDKusec();
		mtype = fits2mtype(tpcode[j - 1], rep[j - 1]);
		nilptr = ATOMnilptr(mtype);
		col = mvc_bind_column(m, tbl, cname[j - 1]);

		tmp = COLnew(0, mtype, rows, TRANSIENT);
		if (tmp == NULL){
			msg = createException(MAL,"fits.load", SQLSTATE(HY013) MAL_MALLOC_FAIL);
			goto bailout;
		}
		if (mtype == TYPE_blob) {
			long i;
			unsigned long nbytes = rep[j - 1] * wid[j - 1];
			blob **v = (blob **)GDKzalloc(sizeof(blob *) * rows);

			mtype = fits2mtype(tpcode[j - 1], 1);
			nilptr = ATOMnilptr(mtype);

			if (v == NULL) {
				BBPreclaim(tmp);
				msg = createException(MAL,"fits.load", SQLSTATE(HY013) MAL_MALLOC_FAIL);
				goto bailout;
			}

			for(i = 0; i < rows; i++) {
				v[i] = (blob *)GDKmalloc(offsetof(blob, data) + nbytes);
				if (v[i] == NULL) {
					BBPreclaim(tmp);
					long k = 0;
					for (k = 0; k < i; k++) {
						GDKfree(v[k]);
					}
					GDKfree(v);
					msg = createException(MAL,"fits.load", SQLSTATE(HY013) MAL_MALLOC_FAIL);
					goto bailout;
				}
				fits_read_col(fptr, tpcode[j - 1], j, i + 1, 1, rep[j - 1], (void *)nilptr,
					      (void *)v[i]->data, &anynull, &status);
				v[i]->nitems = nbytes;
				if (BUNappend(tmp, v[i], false) != GDK_SUCCEED) {
					BBPreclaim(tmp);
					for (i = 0; i < rows; i++) {
						GDKfree(v[i]);
					}
					GDKfree(v);
					msg = createException(MAL,"fits.loadtable", SQLSTATE(HY013) MAL_MALLOC_FAIL);
					goto bailout;
				}
			}

			for(i = 0; i < rows; i++) {
				GDKfree(v[i]);
			}
			GDKfree(v);
		}
		else if (mtype == TYPE_str) {
/*			char *v = GDKzalloc(wid[j-1]);*/
			/* type long demanded by "rows", i.e., by fits library */
			long bsize = 50, batch = bsize, k, i;
			lng tm0, tloadtm = 0, tattachtm = 0;
			char **v = (char **) GDKzalloc(sizeof(char *) * bsize);
			for(i = 0; i < bsize; i++)
				v[i] = GDKzalloc(wid[j-1]);
			for(i = 0; i < rows; i += batch) {
				batch = rows - i < bsize ? rows - i: bsize;
				tm0 = GDKusec();
				fits_read_col(fptr, tpcode[j - 1], j, 1 + i, 1, batch, (void *) nilptr, (void *)v, &anynull, &status);
				tloadtm += GDKusec() - tm0;
				tm0 = GDKusec();
				for(k = 0; k < batch ; k++)
					if (BUNappend(tmp, v[k], false) != GDK_SUCCEED) {
						BBPreclaim(tmp);
						msg = createException(MAL, "fits.loadtable", SQLSTATE(HY013) MAL_MALLOC_FAIL);
						goto bailout;
					}
				tattachtm += GDKusec() - tm0;
			}
			for(i = 0; i < bsize ; i++)
				GDKfree(v[i]);
			GDKfree(v);
			TRC_INFO(FITS, "String column load "LLFMT" usec, BUNappend "LLFMT" usec\n", tloadtm, tattachtm);
		}
		else {
			BATiter bi = bat_iterator_nolock(tmp);
			fits_read_col(fptr, tpcode[j - 1], j, 1, 1, rows, (void *) nilptr, (void *)BUNtloc(bi, 0), &anynull, &status);
			BATsetcount(tmp, rows);
			tmp->tsorted = false;
			tmp->trevsorted = false;
		}

		if (status) {
			char buf[FLEN_ERRMSG + 1];
			fits_read_errmsg(buf);
			BBPreclaim(tmp);
			msg = createException(MAL, "fits.loadtable", SQLSTATE(FI000) "Cannot load column %s of %s table: %s.\n", cname[j - 1], tname, buf);
			break;
		}

		TRC_INFO(FITS, "#Column %s loaded for "LLFMT" usec\t", cname[j-1], GDKusec() - time0);
		if (store->storage_api.append_col(m->session->tr, col, offset, pos, tmp, BATcount(tmp), TYPE_bat) != LOG_OK) {
			BBPreclaim(tmp);
			msg = createException(MAL, "fits.loadtable", SQLSTATE(HY013) MAL_MALLOC_FAIL);
			break;
		}
		TRC_INFO(FITS, "Total "LLFMT" usec\n", GDKusec() - time0);
		BBPreclaim(tmp);
	}

  bailout:
	bat_destroy(pos);
	GDKfree(tpcode);
	GDKfree(rep);
	GDKfree(wid);
	GDKfree(cname);

	fits_close_file(fptr, &status);
	return msg;
}

#include "mel.h"
static mel_func fits_init_funcs[] = {
 pattern("fits", "listdir", FITSdir, true, "Attach all FITS files in the directory", args(1,2, arg("",void),arg("dirname",str))),
 pattern("fits", "listdirpattern", FITSdirpat, true, "Attach all FITS file in the directory, giving a pattern", args(1,3, arg("",void),arg("dirname",str),arg("pattern",str))),
 command("fits", "fitstest", FITStest, false, "Returns the type of first extension in the FITS file filename", args(1,2, arg("",int),arg("filename",str))),
 pattern("fits", "attach", FITSattach, true, "Open a FITS file and return catalog of the table HDUs", args(1,2, arg("",void),arg("fname",str))),
 pattern("fits", "load", FITSloadTable, true, "Load a FITS table from an attached file", args(1,2, arg("",void),arg("tablename",str))),
 pattern("fits", "export", FITSexportTable, false, "Export a table to a FITS file", args(1,2, arg("",void),arg("tablename",str))),
 { .imp=NULL }
};
#include "mal_import.h"
#ifdef _MSC_VER
#undef read
#pragma section(".CRT$XCU",read)
#endif
LIB_STARTUP_FUNC(init_fits_mal)
{ mal_module("fits", NULL, fits_init_funcs); }
