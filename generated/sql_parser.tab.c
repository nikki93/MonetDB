/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         sqlparse
#define yylex           sqllex
#define yyerror         sqlerror
#define yydebug         sqldebug
#define yynerrs         sqlnerrs

/* First part of user prologue.  */
#line 11 "sql_parser.y"

#include "monetdb_config.h"
#include "sql_mem.h"
#include "sql_parser.h"
#include "sql_symbol.h"
#include "sql_datetime.h"
#include "sql_decimal.h"	/* for decimal_from_str() */
#include "sql_semantic.h"	/* for sql_add_param() */
#include "sql_env.h"
#include "rel_sequence.h"	/* for sql_next_seq_name() */

static int sqlerror(mvc *sql, const char *err);
static int sqlformaterror(mvc *sql, _In_z_ _Printf_format_string_ const char *format, ...)
	        __attribute__((__format__(__printf__, 2, 3)));

static void *ma_alloc(sql_allocator *sa, size_t sz);
static void ma_free(void *p);

#include <unistd.h>
#include <string.h>

#define SA 	m->sa
#define _symbol_create(t,d)         symbol_create( SA, t, d)
#define _symbol_create_list(t,d)    symbol_create_list( SA, t, d)
#define _symbol_create_int(t,d)     symbol_create_int( SA, t, d)
#define _symbol_create_lng(t,d)     symbol_create_lng( SA, t, d)
#define _symbol_create_symbol(t,d)  symbol_create_symbol( SA, t, d)
#define _symbol_create_hexa(t,d)    symbol_create_hexa( SA, t, d)
#define _newAtomNode(d)		    newAtomNode( SA, d)

#define L()                  dlist_create( SA )

#define append_list(l,d)     dlist_append_list( SA, l, d)
#define append_int(l,d)      dlist_append_int( SA, l, d)
#define append_lng(l,d)      dlist_append_lng( SA, l, d)
#define append_symbol(l,d)   dlist_append_symbol( SA, l, d)
#define append_string(l,d)   dlist_append_string( SA, l, d)
#define append_type(l,d)     dlist_append_type( SA, l, d)

#define _atom_string(t, v)   atom_string(SA, t, v)

#define Malloc(sz) ma_alloc(m->ta,sz)
#define YYMALLOC Malloc
#define YYFREE ma_free 

#define YY_parse_LSP_NEEDED	/* needed for bison++ 1.21.11-3 */

#define SET_Z(info)(info = info | 0x02)
#define SET_M(info)(info = info | 0x01)

#ifdef HAVE_HGE
#define MAX_DEC_DIGITS 38
#define MAX_HEX_DIGITS 32
#else
#define MAX_DEC_DIGITS 18
#define MAX_HEX_DIGITS 16
#endif

static inline int
UTF8_strlen(const char *val)
{
	const unsigned char *s = (const unsigned char *) val;
	int pos = 0;

	while (*s) {
		int c = *s++;

		pos++;
		if (c < 0xC0)
			continue;
		if (*s++ < 0x80)
			return int_nil;
		if (c < 0xE0)
			continue;
		if (*s++ < 0x80)
			return int_nil;
		if (c < 0xF0)
			continue;
		if (*s++ < 0x80)
			return int_nil;
		if (c < 0xF8)
			continue;
		if (*s++ < 0x80)
			return int_nil;
		if (c < 0xFC)
			continue;
		if (*s++ < 0x80)
			return int_nil;
	}
	return pos;
}


static char *
uescape_xform(char *restrict s, const char *restrict esc)
{
	size_t i, j;

	for (i = j = 0; s[i]; i++) {
		if (s[i] == *esc) {
			if (s[i + 1] == *esc) {
				s[j++] = *esc;
				i++;
			} else {
				int c = 0;
				int n;
				if (s[i + 1] == '+') {
					n = 6;
					i++;
				} else {
					n = 4;
				}
				do {
					i++;
					c <<= 4;
					if ('0' <= s[i] && s[i] <= '9')
						c |= s[i] - '0';
					else if ('a' <= s[i] && s[i] <= 'f')
						c |= s[i] - 'a' + 10;
					else if ('A' <= s[i] && s[i] <= 'F')
						c |= s[i] - 'A' + 10;
					else
						return NULL;
				} while (--n > 0);
				if (c == 0 || c > 0x10FFFF || (c & 0xFFF800) == 0xD800)
					return NULL;
				if (c < 0x80) {
					s[j++] = c;
				} else {
					if (c < 0x800) {
						s[j++] = 0xC0 | (c >> 6);
					} else {
						if (c < 0x10000) {
							s[j++] = 0xE0 | (c >> 12);
						} else {
							s[j++] = 0xF0 | (c >> 18);
							s[j++] = 0x80 | ((c >> 12) & 0x3F);
						}
						s[j++] = 0x80 | ((c >> 6) & 0x3F);
					}
					s[j++] = 0x80 | (c & 0x3F);
				}
			}
		} else {
			s[j++] = s[i];
		}
	}
	s[j] = 0;
	return s;
}

#line 228 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "sql_parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_STRING = 3,                     /* STRING  */
  YYSYMBOL_USTRING = 4,                    /* USTRING  */
  YYSYMBOL_XSTRING = 5,                    /* XSTRING  */
  YYSYMBOL_IDENT = 6,                      /* IDENT  */
  YYSYMBOL_UIDENT = 7,                     /* UIDENT  */
  YYSYMBOL_aTYPE = 8,                      /* aTYPE  */
  YYSYMBOL_ALIAS = 9,                      /* ALIAS  */
  YYSYMBOL_RANK = 10,                      /* RANK  */
  YYSYMBOL_sqlINT = 11,                    /* sqlINT  */
  YYSYMBOL_OIDNUM = 12,                    /* OIDNUM  */
  YYSYMBOL_HEXADECIMAL = 13,               /* HEXADECIMAL  */
  YYSYMBOL_INTNUM = 14,                    /* INTNUM  */
  YYSYMBOL_APPROXNUM = 15,                 /* APPROXNUM  */
  YYSYMBOL_USING = 16,                     /* USING  */
  YYSYMBOL_GLOBAL = 17,                    /* GLOBAL  */
  YYSYMBOL_CAST = 18,                      /* CAST  */
  YYSYMBOL_CONVERT = 19,                   /* CONVERT  */
  YYSYMBOL_CHARACTER = 20,                 /* CHARACTER  */
  YYSYMBOL_VARYING = 21,                   /* VARYING  */
  YYSYMBOL_LARGE = 22,                     /* LARGE  */
  YYSYMBOL_OBJECT = 23,                    /* OBJECT  */
  YYSYMBOL_VARCHAR = 24,                   /* VARCHAR  */
  YYSYMBOL_CLOB = 25,                      /* CLOB  */
  YYSYMBOL_sqlTEXT = 26,                   /* sqlTEXT  */
  YYSYMBOL_BINARY = 27,                    /* BINARY  */
  YYSYMBOL_sqlBLOB = 28,                   /* sqlBLOB  */
  YYSYMBOL_sqlDECIMAL = 29,                /* sqlDECIMAL  */
  YYSYMBOL_sqlFLOAT = 30,                  /* sqlFLOAT  */
  YYSYMBOL_TINYINT = 31,                   /* TINYINT  */
  YYSYMBOL_SMALLINT = 32,                  /* SMALLINT  */
  YYSYMBOL_BIGINT = 33,                    /* BIGINT  */
  YYSYMBOL_HUGEINT = 34,                   /* HUGEINT  */
  YYSYMBOL_sqlINTEGER = 35,                /* sqlINTEGER  */
  YYSYMBOL_sqlDOUBLE = 36,                 /* sqlDOUBLE  */
  YYSYMBOL_sqlREAL = 37,                   /* sqlREAL  */
  YYSYMBOL_PRECISION = 38,                 /* PRECISION  */
  YYSYMBOL_PARTIAL = 39,                   /* PARTIAL  */
  YYSYMBOL_SIMPLE = 40,                    /* SIMPLE  */
  YYSYMBOL_ACTION = 41,                    /* ACTION  */
  YYSYMBOL_CASCADE = 42,                   /* CASCADE  */
  YYSYMBOL_RESTRICT = 43,                  /* RESTRICT  */
  YYSYMBOL_BOOL_FALSE = 44,                /* BOOL_FALSE  */
  YYSYMBOL_BOOL_TRUE = 45,                 /* BOOL_TRUE  */
  YYSYMBOL_CURRENT_DATE = 46,              /* CURRENT_DATE  */
  YYSYMBOL_CURRENT_TIMESTAMP = 47,         /* CURRENT_TIMESTAMP  */
  YYSYMBOL_CURRENT_TIME = 48,              /* CURRENT_TIME  */
  YYSYMBOL_LOCALTIMESTAMP = 49,            /* LOCALTIMESTAMP  */
  YYSYMBOL_LOCALTIME = 50,                 /* LOCALTIME  */
  YYSYMBOL_BIG = 51,                       /* BIG  */
  YYSYMBOL_LITTLE = 52,                    /* LITTLE  */
  YYSYMBOL_NATIVE = 53,                    /* NATIVE  */
  YYSYMBOL_ENDIAN = 54,                    /* ENDIAN  */
  YYSYMBOL_LEX_ERROR = 55,                 /* LEX_ERROR  */
  YYSYMBOL_GEOMETRY = 56,                  /* GEOMETRY  */
  YYSYMBOL_GEOMETRYSUBTYPE = 57,           /* GEOMETRYSUBTYPE  */
  YYSYMBOL_GEOMETRYA = 58,                 /* GEOMETRYA  */
  YYSYMBOL_USER = 59,                      /* USER  */
  YYSYMBOL_CURRENT_USER = 60,              /* CURRENT_USER  */
  YYSYMBOL_SESSION_USER = 61,              /* SESSION_USER  */
  YYSYMBOL_LOCAL = 62,                     /* LOCAL  */
  YYSYMBOL_BEST = 63,                      /* BEST  */
  YYSYMBOL_EFFORT = 64,                    /* EFFORT  */
  YYSYMBOL_CURRENT_ROLE = 65,              /* CURRENT_ROLE  */
  YYSYMBOL_sqlSESSION = 66,                /* sqlSESSION  */
  YYSYMBOL_CURRENT_SCHEMA = 67,            /* CURRENT_SCHEMA  */
  YYSYMBOL_CURRENT_TIMEZONE = 68,          /* CURRENT_TIMEZONE  */
  YYSYMBOL_sqlDELETE = 69,                 /* sqlDELETE  */
  YYSYMBOL_UPDATE = 70,                    /* UPDATE  */
  YYSYMBOL_SELECT = 71,                    /* SELECT  */
  YYSYMBOL_INSERT = 72,                    /* INSERT  */
  YYSYMBOL_MATCHED = 73,                   /* MATCHED  */
  YYSYMBOL_LATERAL = 74,                   /* LATERAL  */
  YYSYMBOL_LEFT = 75,                      /* LEFT  */
  YYSYMBOL_RIGHT = 76,                     /* RIGHT  */
  YYSYMBOL_FULL = 77,                      /* FULL  */
  YYSYMBOL_OUTER = 78,                     /* OUTER  */
  YYSYMBOL_NATURAL = 79,                   /* NATURAL  */
  YYSYMBOL_CROSS = 80,                     /* CROSS  */
  YYSYMBOL_JOIN = 81,                      /* JOIN  */
  YYSYMBOL_INNER = 82,                     /* INNER  */
  YYSYMBOL_COMMIT = 83,                    /* COMMIT  */
  YYSYMBOL_ROLLBACK = 84,                  /* ROLLBACK  */
  YYSYMBOL_SAVEPOINT = 85,                 /* SAVEPOINT  */
  YYSYMBOL_RELEASE = 86,                   /* RELEASE  */
  YYSYMBOL_WORK = 87,                      /* WORK  */
  YYSYMBOL_CHAIN = 88,                     /* CHAIN  */
  YYSYMBOL_NO = 89,                        /* NO  */
  YYSYMBOL_PRESERVE = 90,                  /* PRESERVE  */
  YYSYMBOL_ROWS = 91,                      /* ROWS  */
  YYSYMBOL_START = 92,                     /* START  */
  YYSYMBOL_TRANSACTION = 93,               /* TRANSACTION  */
  YYSYMBOL_READ = 94,                      /* READ  */
  YYSYMBOL_WRITE = 95,                     /* WRITE  */
  YYSYMBOL_ONLY = 96,                      /* ONLY  */
  YYSYMBOL_ISOLATION = 97,                 /* ISOLATION  */
  YYSYMBOL_LEVEL = 98,                     /* LEVEL  */
  YYSYMBOL_UNCOMMITTED = 99,               /* UNCOMMITTED  */
  YYSYMBOL_COMMITTED = 100,                /* COMMITTED  */
  YYSYMBOL_sqlREPEATABLE = 101,            /* sqlREPEATABLE  */
  YYSYMBOL_SERIALIZABLE = 102,             /* SERIALIZABLE  */
  YYSYMBOL_DIAGNOSTICS = 103,              /* DIAGNOSTICS  */
  YYSYMBOL_sqlSIZE = 104,                  /* sqlSIZE  */
  YYSYMBOL_STORAGE = 105,                  /* STORAGE  */
  YYSYMBOL_SNAPSHOT = 106,                 /* SNAPSHOT  */
  YYSYMBOL_ASYMMETRIC = 107,               /* ASYMMETRIC  */
  YYSYMBOL_SYMMETRIC = 108,                /* SYMMETRIC  */
  YYSYMBOL_ORDER = 109,                    /* ORDER  */
  YYSYMBOL_ORDERED = 110,                  /* ORDERED  */
  YYSYMBOL_BY = 111,                       /* BY  */
  YYSYMBOL_IMPRINTS = 112,                 /* IMPRINTS  */
  YYSYMBOL_ESCAPE = 113,                   /* ESCAPE  */
  YYSYMBOL_UESCAPE = 114,                  /* UESCAPE  */
  YYSYMBOL_HAVING = 115,                   /* HAVING  */
  YYSYMBOL_sqlGROUP = 116,                 /* sqlGROUP  */
  YYSYMBOL_ROLLUP = 117,                   /* ROLLUP  */
  YYSYMBOL_CUBE = 118,                     /* CUBE  */
  YYSYMBOL_sqlNULL = 119,                  /* sqlNULL  */
  YYSYMBOL_GROUPING = 120,                 /* GROUPING  */
  YYSYMBOL_SETS = 121,                     /* SETS  */
  YYSYMBOL_FROM = 122,                     /* FROM  */
  YYSYMBOL_FOR = 123,                      /* FOR  */
  YYSYMBOL_MATCH = 124,                    /* MATCH  */
  YYSYMBOL_EXTRACT = 125,                  /* EXTRACT  */
  YYSYMBOL_SEQUENCE = 126,                 /* SEQUENCE  */
  YYSYMBOL_INCREMENT = 127,                /* INCREMENT  */
  YYSYMBOL_RESTART = 128,                  /* RESTART  */
  YYSYMBOL_CONTINUE = 129,                 /* CONTINUE  */
  YYSYMBOL_MAXVALUE = 130,                 /* MAXVALUE  */
  YYSYMBOL_MINVALUE = 131,                 /* MINVALUE  */
  YYSYMBOL_CYCLE = 132,                    /* CYCLE  */
  YYSYMBOL_NEXT = 133,                     /* NEXT  */
  YYSYMBOL_VALUE = 134,                    /* VALUE  */
  YYSYMBOL_CACHE = 135,                    /* CACHE  */
  YYSYMBOL_GENERATED = 136,                /* GENERATED  */
  YYSYMBOL_ALWAYS = 137,                   /* ALWAYS  */
  YYSYMBOL_IDENTITY = 138,                 /* IDENTITY  */
  YYSYMBOL_SERIAL = 139,                   /* SERIAL  */
  YYSYMBOL_BIGSERIAL = 140,                /* BIGSERIAL  */
  YYSYMBOL_AUTO_INCREMENT = 141,           /* AUTO_INCREMENT  */
  YYSYMBOL_SCOLON = 142,                   /* SCOLON  */
  YYSYMBOL_AT = 143,                       /* AT  */
  YYSYMBOL_XMLCOMMENT = 144,               /* XMLCOMMENT  */
  YYSYMBOL_XMLCONCAT = 145,                /* XMLCONCAT  */
  YYSYMBOL_XMLDOCUMENT = 146,              /* XMLDOCUMENT  */
  YYSYMBOL_XMLELEMENT = 147,               /* XMLELEMENT  */
  YYSYMBOL_XMLATTRIBUTES = 148,            /* XMLATTRIBUTES  */
  YYSYMBOL_XMLFOREST = 149,                /* XMLFOREST  */
  YYSYMBOL_XMLPARSE = 150,                 /* XMLPARSE  */
  YYSYMBOL_STRIP = 151,                    /* STRIP  */
  YYSYMBOL_WHITESPACE = 152,               /* WHITESPACE  */
  YYSYMBOL_XMLPI = 153,                    /* XMLPI  */
  YYSYMBOL_XMLQUERY = 154,                 /* XMLQUERY  */
  YYSYMBOL_PASSING = 155,                  /* PASSING  */
  YYSYMBOL_XMLTEXT = 156,                  /* XMLTEXT  */
  YYSYMBOL_NIL = 157,                      /* NIL  */
  YYSYMBOL_REF = 158,                      /* REF  */
  YYSYMBOL_ABSENT = 159,                   /* ABSENT  */
  YYSYMBOL_EMPTY = 160,                    /* EMPTY  */
  YYSYMBOL_DOCUMENT = 161,                 /* DOCUMENT  */
  YYSYMBOL_ELEMENT = 162,                  /* ELEMENT  */
  YYSYMBOL_CONTENT = 163,                  /* CONTENT  */
  YYSYMBOL_XMLNAMESPACES = 164,            /* XMLNAMESPACES  */
  YYSYMBOL_NAMESPACE = 165,                /* NAMESPACE  */
  YYSYMBOL_XMLVALIDATE = 166,              /* XMLVALIDATE  */
  YYSYMBOL_RETURNING = 167,                /* RETURNING  */
  YYSYMBOL_LOCATION = 168,                 /* LOCATION  */
  YYSYMBOL_ID = 169,                       /* ID  */
  YYSYMBOL_ACCORDING = 170,                /* ACCORDING  */
  YYSYMBOL_XMLSCHEMA = 171,                /* XMLSCHEMA  */
  YYSYMBOL_URI = 172,                      /* URI  */
  YYSYMBOL_XMLAGG = 173,                   /* XMLAGG  */
  YYSYMBOL_FILTER = 174,                   /* FILTER  */
  YYSYMBOL_UNION = 175,                    /* UNION  */
  YYSYMBOL_EXCEPT = 176,                   /* EXCEPT  */
  YYSYMBOL_INTERSECT = 177,                /* INTERSECT  */
  YYSYMBOL_CORRESPONDING = 178,            /* CORRESPONDING  */
  YYSYMBOL_DATA = 179,                     /* DATA  */
  YYSYMBOL_180_ = 180,                     /* '('  */
  YYSYMBOL_181_ = 181,                     /* ')'  */
  YYSYMBOL_NOT = 182,                      /* NOT  */
  YYSYMBOL_183_ = 183,                     /* '='  */
  YYSYMBOL_ALL = 184,                      /* ALL  */
  YYSYMBOL_ANY = 185,                      /* ANY  */
  YYSYMBOL_NOT_BETWEEN = 186,              /* NOT_BETWEEN  */
  YYSYMBOL_BETWEEN = 187,                  /* BETWEEN  */
  YYSYMBOL_NOT_IN = 188,                   /* NOT_IN  */
  YYSYMBOL_sqlIN = 189,                    /* sqlIN  */
  YYSYMBOL_NOT_EXISTS = 190,               /* NOT_EXISTS  */
  YYSYMBOL_EXISTS = 191,                   /* EXISTS  */
  YYSYMBOL_NOT_LIKE = 192,                 /* NOT_LIKE  */
  YYSYMBOL_LIKE = 193,                     /* LIKE  */
  YYSYMBOL_NOT_ILIKE = 194,                /* NOT_ILIKE  */
  YYSYMBOL_ILIKE = 195,                    /* ILIKE  */
  YYSYMBOL_OR = 196,                       /* OR  */
  YYSYMBOL_SOME = 197,                     /* SOME  */
  YYSYMBOL_AND = 198,                      /* AND  */
  YYSYMBOL_COMPARISON = 199,               /* COMPARISON  */
  YYSYMBOL_200_ = 200,                     /* '+'  */
  YYSYMBOL_201_ = 201,                     /* '-'  */
  YYSYMBOL_202_ = 202,                     /* '&'  */
  YYSYMBOL_203_ = 203,                     /* '|'  */
  YYSYMBOL_204_ = 204,                     /* '^'  */
  YYSYMBOL_LEFT_SHIFT = 205,               /* LEFT_SHIFT  */
  YYSYMBOL_RIGHT_SHIFT = 206,              /* RIGHT_SHIFT  */
  YYSYMBOL_LEFT_SHIFT_ASSIGN = 207,        /* LEFT_SHIFT_ASSIGN  */
  YYSYMBOL_RIGHT_SHIFT_ASSIGN = 208,       /* RIGHT_SHIFT_ASSIGN  */
  YYSYMBOL_CONCATSTRING = 209,             /* CONCATSTRING  */
  YYSYMBOL_SUBSTRING = 210,                /* SUBSTRING  */
  YYSYMBOL_POSITION = 211,                 /* POSITION  */
  YYSYMBOL_SPLIT_PART = 212,               /* SPLIT_PART  */
  YYSYMBOL_213_ = 213,                     /* '*'  */
  YYSYMBOL_214_ = 214,                     /* '/'  */
  YYSYMBOL_215_ = 215,                     /* '%'  */
  YYSYMBOL_UMINUS = 216,                   /* UMINUS  */
  YYSYMBOL_217_ = 217,                     /* '~'  */
  YYSYMBOL_GEOM_OVERLAP = 218,             /* GEOM_OVERLAP  */
  YYSYMBOL_GEOM_OVERLAP_OR_ABOVE = 219,    /* GEOM_OVERLAP_OR_ABOVE  */
  YYSYMBOL_GEOM_OVERLAP_OR_BELOW = 220,    /* GEOM_OVERLAP_OR_BELOW  */
  YYSYMBOL_GEOM_OVERLAP_OR_LEFT = 221,     /* GEOM_OVERLAP_OR_LEFT  */
  YYSYMBOL_GEOM_OVERLAP_OR_RIGHT = 222,    /* GEOM_OVERLAP_OR_RIGHT  */
  YYSYMBOL_GEOM_BELOW = 223,               /* GEOM_BELOW  */
  YYSYMBOL_GEOM_ABOVE = 224,               /* GEOM_ABOVE  */
  YYSYMBOL_GEOM_DIST = 225,                /* GEOM_DIST  */
  YYSYMBOL_GEOM_MBR_EQUAL = 226,           /* GEOM_MBR_EQUAL  */
  YYSYMBOL_TEMP = 227,                     /* TEMP  */
  YYSYMBOL_TEMPORARY = 228,                /* TEMPORARY  */
  YYSYMBOL_MERGE = 229,                    /* MERGE  */
  YYSYMBOL_REMOTE = 230,                   /* REMOTE  */
  YYSYMBOL_REPLICA = 231,                  /* REPLICA  */
  YYSYMBOL_UNLOGGED = 232,                 /* UNLOGGED  */
  YYSYMBOL_ASC = 233,                      /* ASC  */
  YYSYMBOL_DESC = 234,                     /* DESC  */
  YYSYMBOL_AUTHORIZATION = 235,            /* AUTHORIZATION  */
  YYSYMBOL_CHECK = 236,                    /* CHECK  */
  YYSYMBOL_CONSTRAINT = 237,               /* CONSTRAINT  */
  YYSYMBOL_CREATE = 238,                   /* CREATE  */
  YYSYMBOL_COMMENT = 239,                  /* COMMENT  */
  YYSYMBOL_NULLS = 240,                    /* NULLS  */
  YYSYMBOL_FIRST = 241,                    /* FIRST  */
  YYSYMBOL_LAST = 242,                     /* LAST  */
  YYSYMBOL_TYPE = 243,                     /* TYPE  */
  YYSYMBOL_PROCEDURE = 244,                /* PROCEDURE  */
  YYSYMBOL_FUNCTION = 245,                 /* FUNCTION  */
  YYSYMBOL_sqlLOADER = 246,                /* sqlLOADER  */
  YYSYMBOL_AGGREGATE = 247,                /* AGGREGATE  */
  YYSYMBOL_RETURNS = 248,                  /* RETURNS  */
  YYSYMBOL_EXTERNAL = 249,                 /* EXTERNAL  */
  YYSYMBOL_sqlNAME = 250,                  /* sqlNAME  */
  YYSYMBOL_DECLARE = 251,                  /* DECLARE  */
  YYSYMBOL_CALL = 252,                     /* CALL  */
  YYSYMBOL_LANGUAGE = 253,                 /* LANGUAGE  */
  YYSYMBOL_ANALYZE = 254,                  /* ANALYZE  */
  YYSYMBOL_MINMAX = 255,                   /* MINMAX  */
  YYSYMBOL_SQL_EXPLAIN = 256,              /* SQL_EXPLAIN  */
  YYSYMBOL_SQL_PLAN = 257,                 /* SQL_PLAN  */
  YYSYMBOL_SQL_DEBUG = 258,                /* SQL_DEBUG  */
  YYSYMBOL_SQL_TRACE = 259,                /* SQL_TRACE  */
  YYSYMBOL_PREP = 260,                     /* PREP  */
  YYSYMBOL_PREPARE = 261,                  /* PREPARE  */
  YYSYMBOL_EXEC = 262,                     /* EXEC  */
  YYSYMBOL_EXECUTE = 263,                  /* EXECUTE  */
  YYSYMBOL_DEALLOCATE = 264,               /* DEALLOCATE  */
  YYSYMBOL_DEFAULT = 265,                  /* DEFAULT  */
  YYSYMBOL_DISTINCT = 266,                 /* DISTINCT  */
  YYSYMBOL_DROP = 267,                     /* DROP  */
  YYSYMBOL_TRUNCATE = 268,                 /* TRUNCATE  */
  YYSYMBOL_FOREIGN = 269,                  /* FOREIGN  */
  YYSYMBOL_RENAME = 270,                   /* RENAME  */
  YYSYMBOL_ENCRYPTED = 271,                /* ENCRYPTED  */
  YYSYMBOL_UNENCRYPTED = 272,              /* UNENCRYPTED  */
  YYSYMBOL_PASSWORD = 273,                 /* PASSWORD  */
  YYSYMBOL_GRANT = 274,                    /* GRANT  */
  YYSYMBOL_REVOKE = 275,                   /* REVOKE  */
  YYSYMBOL_ROLE = 276,                     /* ROLE  */
  YYSYMBOL_ADMIN = 277,                    /* ADMIN  */
  YYSYMBOL_INTO = 278,                     /* INTO  */
  YYSYMBOL_IS = 279,                       /* IS  */
  YYSYMBOL_KEY = 280,                      /* KEY  */
  YYSYMBOL_ON = 281,                       /* ON  */
  YYSYMBOL_OPTION = 282,                   /* OPTION  */
  YYSYMBOL_OPTIONS = 283,                  /* OPTIONS  */
  YYSYMBOL_PATH = 284,                     /* PATH  */
  YYSYMBOL_PRIMARY = 285,                  /* PRIMARY  */
  YYSYMBOL_PRIVILEGES = 286,               /* PRIVILEGES  */
  YYSYMBOL_PUBLIC = 287,                   /* PUBLIC  */
  YYSYMBOL_REFERENCES = 288,               /* REFERENCES  */
  YYSYMBOL_SCHEMA = 289,                   /* SCHEMA  */
  YYSYMBOL_SET = 290,                      /* SET  */
  YYSYMBOL_AUTO_COMMIT = 291,              /* AUTO_COMMIT  */
  YYSYMBOL_RETURN = 292,                   /* RETURN  */
  YYSYMBOL_ALTER = 293,                    /* ALTER  */
  YYSYMBOL_ADD = 294,                      /* ADD  */
  YYSYMBOL_TABLE = 295,                    /* TABLE  */
  YYSYMBOL_COLUMN = 296,                   /* COLUMN  */
  YYSYMBOL_TO = 297,                       /* TO  */
  YYSYMBOL_UNIQUE = 298,                   /* UNIQUE  */
  YYSYMBOL_VALUES = 299,                   /* VALUES  */
  YYSYMBOL_VIEW = 300,                     /* VIEW  */
  YYSYMBOL_WHERE = 301,                    /* WHERE  */
  YYSYMBOL_WITH = 302,                     /* WITH  */
  YYSYMBOL_sqlDATE = 303,                  /* sqlDATE  */
  YYSYMBOL_TIME = 304,                     /* TIME  */
  YYSYMBOL_TIMESTAMP = 305,                /* TIMESTAMP  */
  YYSYMBOL_INTERVAL = 306,                 /* INTERVAL  */
  YYSYMBOL_CENTURY = 307,                  /* CENTURY  */
  YYSYMBOL_DECADE = 308,                   /* DECADE  */
  YYSYMBOL_YEAR = 309,                     /* YEAR  */
  YYSYMBOL_QUARTER = 310,                  /* QUARTER  */
  YYSYMBOL_DOW = 311,                      /* DOW  */
  YYSYMBOL_DOY = 312,                      /* DOY  */
  YYSYMBOL_MONTH = 313,                    /* MONTH  */
  YYSYMBOL_WEEK = 314,                     /* WEEK  */
  YYSYMBOL_DAY = 315,                      /* DAY  */
  YYSYMBOL_HOUR = 316,                     /* HOUR  */
  YYSYMBOL_MINUTE = 317,                   /* MINUTE  */
  YYSYMBOL_SECOND = 318,                   /* SECOND  */
  YYSYMBOL_EPOCH = 319,                    /* EPOCH  */
  YYSYMBOL_ZONE = 320,                     /* ZONE  */
  YYSYMBOL_LIMIT = 321,                    /* LIMIT  */
  YYSYMBOL_OFFSET = 322,                   /* OFFSET  */
  YYSYMBOL_SAMPLE = 323,                   /* SAMPLE  */
  YYSYMBOL_SEED = 324,                     /* SEED  */
  YYSYMBOL_CASE = 325,                     /* CASE  */
  YYSYMBOL_WHEN = 326,                     /* WHEN  */
  YYSYMBOL_THEN = 327,                     /* THEN  */
  YYSYMBOL_ELSE = 328,                     /* ELSE  */
  YYSYMBOL_NULLIF = 329,                   /* NULLIF  */
  YYSYMBOL_COALESCE = 330,                 /* COALESCE  */
  YYSYMBOL_IF = 331,                       /* IF  */
  YYSYMBOL_ELSEIF = 332,                   /* ELSEIF  */
  YYSYMBOL_WHILE = 333,                    /* WHILE  */
  YYSYMBOL_DO = 334,                       /* DO  */
  YYSYMBOL_ATOMIC = 335,                   /* ATOMIC  */
  YYSYMBOL_BEGIN = 336,                    /* BEGIN  */
  YYSYMBOL_END = 337,                      /* END  */
  YYSYMBOL_COPY = 338,                     /* COPY  */
  YYSYMBOL_RECORDS = 339,                  /* RECORDS  */
  YYSYMBOL_DELIMITERS = 340,               /* DELIMITERS  */
  YYSYMBOL_STDIN = 341,                    /* STDIN  */
  YYSYMBOL_STDOUT = 342,                   /* STDOUT  */
  YYSYMBOL_FWF = 343,                      /* FWF  */
  YYSYMBOL_CLIENT = 344,                   /* CLIENT  */
  YYSYMBOL_SERVER = 345,                   /* SERVER  */
  YYSYMBOL_INDEX = 346,                    /* INDEX  */
  YYSYMBOL_REPLACE = 347,                  /* REPLACE  */
  YYSYMBOL_AS = 348,                       /* AS  */
  YYSYMBOL_TRIGGER = 349,                  /* TRIGGER  */
  YYSYMBOL_OF = 350,                       /* OF  */
  YYSYMBOL_BEFORE = 351,                   /* BEFORE  */
  YYSYMBOL_AFTER = 352,                    /* AFTER  */
  YYSYMBOL_ROW = 353,                      /* ROW  */
  YYSYMBOL_STATEMENT = 354,                /* STATEMENT  */
  YYSYMBOL_sqlNEW = 355,                   /* sqlNEW  */
  YYSYMBOL_OLD = 356,                      /* OLD  */
  YYSYMBOL_EACH = 357,                     /* EACH  */
  YYSYMBOL_REFERENCING = 358,              /* REFERENCING  */
  YYSYMBOL_OVER = 359,                     /* OVER  */
  YYSYMBOL_PARTITION = 360,                /* PARTITION  */
  YYSYMBOL_CURRENT = 361,                  /* CURRENT  */
  YYSYMBOL_EXCLUDE = 362,                  /* EXCLUDE  */
  YYSYMBOL_FOLLOWING = 363,                /* FOLLOWING  */
  YYSYMBOL_PRECEDING = 364,                /* PRECEDING  */
  YYSYMBOL_OTHERS = 365,                   /* OTHERS  */
  YYSYMBOL_TIES = 366,                     /* TIES  */
  YYSYMBOL_RANGE = 367,                    /* RANGE  */
  YYSYMBOL_UNBOUNDED = 368,                /* UNBOUNDED  */
  YYSYMBOL_GROUPS = 369,                   /* GROUPS  */
  YYSYMBOL_WINDOW = 370,                   /* WINDOW  */
  YYSYMBOL_X_BODY = 371,                   /* X_BODY  */
  YYSYMBOL_MAX_MEMORY = 372,               /* MAX_MEMORY  */
  YYSYMBOL_MAX_WORKERS = 373,              /* MAX_WORKERS  */
  YYSYMBOL_OPTIMIZER = 374,                /* OPTIMIZER  */
  YYSYMBOL_375_ = 375,                     /* ','  */
  YYSYMBOL_376_ = 376,                     /* '.'  */
  YYSYMBOL_377_ = 377,                     /* ':'  */
  YYSYMBOL_378_ = 378,                     /* '['  */
  YYSYMBOL_379_ = 379,                     /* ']'  */
  YYSYMBOL_380_ = 380,                     /* '?'  */
  YYSYMBOL_YYACCEPT = 381,                 /* $accept  */
  YYSYMBOL_sqlstmt = 382,                  /* sqlstmt  */
  YYSYMBOL_383_1 = 383,                    /* $@1  */
  YYSYMBOL_384_2 = 384,                    /* $@2  */
  YYSYMBOL_385_3 = 385,                    /* $@3  */
  YYSYMBOL_386_4 = 386,                    /* $@4  */
  YYSYMBOL_387_5 = 387,                    /* $@5  */
  YYSYMBOL_prepare = 388,                  /* prepare  */
  YYSYMBOL_execute = 389,                  /* execute  */
  YYSYMBOL_opt_prepare = 390,              /* opt_prepare  */
  YYSYMBOL_deallocate = 391,               /* deallocate  */
  YYSYMBOL_create = 392,                   /* create  */
  YYSYMBOL_create_or_replace = 393,        /* create_or_replace  */
  YYSYMBOL_if_exists = 394,                /* if_exists  */
  YYSYMBOL_if_not_exists = 395,            /* if_not_exists  */
  YYSYMBOL_drop = 396,                     /* drop  */
  YYSYMBOL_set = 397,                      /* set  */
  YYSYMBOL_declare = 398,                  /* declare  */
  YYSYMBOL_sql = 399,                      /* sql  */
  YYSYMBOL_opt_minmax = 400,               /* opt_minmax  */
  YYSYMBOL_declare_statement = 401,        /* declare_statement  */
  YYSYMBOL_variable_ref_commalist = 402,   /* variable_ref_commalist  */
  YYSYMBOL_variable_list = 403,            /* variable_list  */
  YYSYMBOL_opt_equal = 404,                /* opt_equal  */
  YYSYMBOL_set_statement = 405,            /* set_statement  */
  YYSYMBOL_schema = 406,                   /* schema  */
  YYSYMBOL_schema_name_clause = 407,       /* schema_name_clause  */
  YYSYMBOL_authorization_identifier = 408, /* authorization_identifier  */
  YYSYMBOL_opt_schema_default_char_set = 409, /* opt_schema_default_char_set  */
  YYSYMBOL_opt_schema_element_list = 410,  /* opt_schema_element_list  */
  YYSYMBOL_schema_element_list = 411,      /* schema_element_list  */
  YYSYMBOL_schema_element = 412,           /* schema_element  */
  YYSYMBOL_opt_grantor = 413,              /* opt_grantor  */
  YYSYMBOL_grantor = 414,                  /* grantor  */
  YYSYMBOL_grant = 415,                    /* grant  */
  YYSYMBOL_authid_list = 416,              /* authid_list  */
  YYSYMBOL_opt_with_grant = 417,           /* opt_with_grant  */
  YYSYMBOL_opt_with_admin = 418,           /* opt_with_admin  */
  YYSYMBOL_opt_from_grantor = 419,         /* opt_from_grantor  */
  YYSYMBOL_revoke = 420,                   /* revoke  */
  YYSYMBOL_opt_grant_for = 421,            /* opt_grant_for  */
  YYSYMBOL_opt_admin_for = 422,            /* opt_admin_for  */
  YYSYMBOL_privileges = 423,               /* privileges  */
  YYSYMBOL_global_privileges = 424,        /* global_privileges  */
  YYSYMBOL_global_privilege = 425,         /* global_privilege  */
  YYSYMBOL_object_name = 426,              /* object_name  */
  YYSYMBOL_object_privileges = 427,        /* object_privileges  */
  YYSYMBOL_operation_commalist = 428,      /* operation_commalist  */
  YYSYMBOL_operation = 429,                /* operation  */
  YYSYMBOL_grantee_commalist = 430,        /* grantee_commalist  */
  YYSYMBOL_grantee = 431,                  /* grantee  */
  YYSYMBOL_alter_statement = 432,          /* alter_statement  */
  YYSYMBOL_opt_with_encrypted_password = 433, /* opt_with_encrypted_password  */
  YYSYMBOL_user_schema = 434,              /* user_schema  */
  YYSYMBOL_opt_schema_path = 435,          /* opt_schema_path  */
  YYSYMBOL_alter_table_element = 436,      /* alter_table_element  */
  YYSYMBOL_drop_table_element = 437,       /* drop_table_element  */
  YYSYMBOL_opt_column = 438,               /* opt_column  */
  YYSYMBOL_create_statement = 439,         /* create_statement  */
  YYSYMBOL_seq_def = 440,                  /* seq_def  */
  YYSYMBOL_opt_seq_params = 441,           /* opt_seq_params  */
  YYSYMBOL_params_list = 442,              /* params_list  */
  YYSYMBOL_opt_alt_seq_params = 443,       /* opt_alt_seq_params  */
  YYSYMBOL_opt_seq_param = 444,            /* opt_seq_param  */
  YYSYMBOL_opt_alt_seq_param = 445,        /* opt_alt_seq_param  */
  YYSYMBOL_opt_seq_common_param = 446,     /* opt_seq_common_param  */
  YYSYMBOL_index_def = 447,                /* index_def  */
  YYSYMBOL_opt_index_type = 448,           /* opt_index_type  */
  YYSYMBOL_role_def = 449,                 /* role_def  */
  YYSYMBOL_opt_max_memory = 450,           /* opt_max_memory  */
  YYSYMBOL_opt_max_workers = 451,          /* opt_max_workers  */
  YYSYMBOL_opt_optimizer = 452,            /* opt_optimizer  */
  YYSYMBOL_opt_default_role = 453,         /* opt_default_role  */
  YYSYMBOL_opt_schema_details_list = 454,  /* opt_schema_details_list  */
  YYSYMBOL_opt_encrypted = 455,            /* opt_encrypted  */
  YYSYMBOL_table_def = 456,                /* table_def  */
  YYSYMBOL_partition_type = 457,           /* partition_type  */
  YYSYMBOL_partition_expression = 458,     /* partition_expression  */
  YYSYMBOL_partition_on = 459,             /* partition_on  */
  YYSYMBOL_opt_partition_by = 460,         /* opt_partition_by  */
  YYSYMBOL_partition_list_value = 461,     /* partition_list_value  */
  YYSYMBOL_partition_range_from = 462,     /* partition_range_from  */
  YYSYMBOL_partition_range_to = 463,       /* partition_range_to  */
  YYSYMBOL_partition_list = 464,           /* partition_list  */
  YYSYMBOL_opt_with_nulls = 465,           /* opt_with_nulls  */
  YYSYMBOL_opt_partition_spec = 466,       /* opt_partition_spec  */
  YYSYMBOL_opt_as_partition = 467,         /* opt_as_partition  */
  YYSYMBOL_with_opt_credentials = 468,     /* with_opt_credentials  */
  YYSYMBOL_opt_temp = 469,                 /* opt_temp  */
  YYSYMBOL_opt_on_commit = 470,            /* opt_on_commit  */
  YYSYMBOL_table_content_source = 471,     /* table_content_source  */
  YYSYMBOL_as_subquery_clause = 472,       /* as_subquery_clause  */
  YYSYMBOL_with_or_without_data = 473,     /* with_or_without_data  */
  YYSYMBOL_table_element_list = 474,       /* table_element_list  */
  YYSYMBOL_add_table_element = 475,        /* add_table_element  */
  YYSYMBOL_table_element = 476,            /* table_element  */
  YYSYMBOL_serial_or_bigserial = 477,      /* serial_or_bigserial  */
  YYSYMBOL_column_def = 478,               /* column_def  */
  YYSYMBOL_opt_column_def_opt_list = 479,  /* opt_column_def_opt_list  */
  YYSYMBOL_column_def_opt_list = 480,      /* column_def_opt_list  */
  YYSYMBOL_column_options = 481,           /* column_options  */
  YYSYMBOL_column_option_list = 482,       /* column_option_list  */
  YYSYMBOL_column_option = 483,            /* column_option  */
  YYSYMBOL_default = 484,                  /* default  */
  YYSYMBOL_default_value = 485,            /* default_value  */
  YYSYMBOL_column_constraint = 486,        /* column_constraint  */
  YYSYMBOL_generated_column = 487,         /* generated_column  */
  YYSYMBOL_serial_opt_params = 488,        /* serial_opt_params  */
  YYSYMBOL_table_constraint = 489,         /* table_constraint  */
  YYSYMBOL_opt_constraint_name = 490,      /* opt_constraint_name  */
  YYSYMBOL_ref_action = 491,               /* ref_action  */
  YYSYMBOL_ref_on_update = 492,            /* ref_on_update  */
  YYSYMBOL_ref_on_delete = 493,            /* ref_on_delete  */
  YYSYMBOL_opt_ref_action = 494,           /* opt_ref_action  */
  YYSYMBOL_opt_match_type = 495,           /* opt_match_type  */
  YYSYMBOL_opt_match = 496,                /* opt_match  */
  YYSYMBOL_column_constraint_type = 497,   /* column_constraint_type  */
  YYSYMBOL_table_constraint_type = 498,    /* table_constraint_type  */
  YYSYMBOL_domain_constraint_type = 499,   /* domain_constraint_type  */
  YYSYMBOL_ident_commalist = 500,          /* ident_commalist  */
  YYSYMBOL_like_table = 501,               /* like_table  */
  YYSYMBOL_view_def = 502,                 /* view_def  */
  YYSYMBOL_query_expression_def = 503,     /* query_expression_def  */
  YYSYMBOL_query_expression = 504,         /* query_expression  */
  YYSYMBOL_opt_with_check_option = 505,    /* opt_with_check_option  */
  YYSYMBOL_opt_column_list = 506,          /* opt_column_list  */
  YYSYMBOL_column_commalist_parens = 507,  /* column_commalist_parens  */
  YYSYMBOL_variable_ref_commalist_parens = 508, /* variable_ref_commalist_parens  */
  YYSYMBOL_type_def = 509,                 /* type_def  */
  YYSYMBOL_external_function_name = 510,   /* external_function_name  */
  YYSYMBOL_function_body = 511,            /* function_body  */
  YYSYMBOL_func_def_type = 512,            /* func_def_type  */
  YYSYMBOL_func_def_opt_return = 513,      /* func_def_opt_return  */
  YYSYMBOL_func_def = 514,                 /* func_def  */
  YYSYMBOL_routine_body = 515,             /* routine_body  */
  YYSYMBOL_procedure_statement_list = 516, /* procedure_statement_list  */
  YYSYMBOL_trigger_procedure_statement_list = 517, /* trigger_procedure_statement_list  */
  YYSYMBOL_procedure_statement = 518,      /* procedure_statement  */
  YYSYMBOL_trigger_procedure_statement = 519, /* trigger_procedure_statement  */
  YYSYMBOL_control_statement = 520,        /* control_statement  */
  YYSYMBOL_call_statement = 521,           /* call_statement  */
  YYSYMBOL_call_procedure_statement = 522, /* call_procedure_statement  */
  YYSYMBOL_routine_invocation = 523,       /* routine_invocation  */
  YYSYMBOL_routine_name = 524,             /* routine_name  */
  YYSYMBOL_argument_list = 525,            /* argument_list  */
  YYSYMBOL_return_statement = 526,         /* return_statement  */
  YYSYMBOL_return_value = 527,             /* return_value  */
  YYSYMBOL_case_statement = 528,           /* case_statement  */
  YYSYMBOL_when_statement = 529,           /* when_statement  */
  YYSYMBOL_when_statements = 530,          /* when_statements  */
  YYSYMBOL_when_search_statement = 531,    /* when_search_statement  */
  YYSYMBOL_when_search_statements = 532,   /* when_search_statements  */
  YYSYMBOL_case_opt_else_statement = 533,  /* case_opt_else_statement  */
  YYSYMBOL_if_statement = 534,             /* if_statement  */
  YYSYMBOL_if_opt_else = 535,              /* if_opt_else  */
  YYSYMBOL_while_statement = 536,          /* while_statement  */
  YYSYMBOL_opt_begin_label = 537,          /* opt_begin_label  */
  YYSYMBOL_opt_end_label = 538,            /* opt_end_label  */
  YYSYMBOL_table_function_column_list = 539, /* table_function_column_list  */
  YYSYMBOL_func_data_type = 540,           /* func_data_type  */
  YYSYMBOL_opt_paramlist = 541,            /* opt_paramlist  */
  YYSYMBOL_paramlist = 542,                /* paramlist  */
  YYSYMBOL_trigger_def = 543,              /* trigger_def  */
  YYSYMBOL_trigger_action_time = 544,      /* trigger_action_time  */
  YYSYMBOL_trigger_event = 545,            /* trigger_event  */
  YYSYMBOL_opt_referencing_list = 546,     /* opt_referencing_list  */
  YYSYMBOL_old_or_new_values_alias_list = 547, /* old_or_new_values_alias_list  */
  YYSYMBOL_old_or_new_values_alias = 548,  /* old_or_new_values_alias  */
  YYSYMBOL_opt_as = 549,                   /* opt_as  */
  YYSYMBOL_opt_row = 550,                  /* opt_row  */
  YYSYMBOL_triggered_action = 551,         /* triggered_action  */
  YYSYMBOL_opt_for_each = 552,             /* opt_for_each  */
  YYSYMBOL_row_or_statement = 553,         /* row_or_statement  */
  YYSYMBOL_opt_when = 554,                 /* opt_when  */
  YYSYMBOL_triggered_statement = 555,      /* triggered_statement  */
  YYSYMBOL_routine_designator = 556,       /* routine_designator  */
  YYSYMBOL_drop_statement = 557,           /* drop_statement  */
  YYSYMBOL_opt_typelist = 558,             /* opt_typelist  */
  YYSYMBOL_typelist = 559,                 /* typelist  */
  YYSYMBOL_drop_action = 560,              /* drop_action  */
  YYSYMBOL_update_statement = 561,         /* update_statement  */
  YYSYMBOL_transaction_statement = 562,    /* transaction_statement  */
  YYSYMBOL_start_transaction = 563,        /* start_transaction  */
  YYSYMBOL_transaction_stmt = 564,         /* transaction_stmt  */
  YYSYMBOL_transaction_mode_list = 565,    /* transaction_mode_list  */
  YYSYMBOL__transaction_mode_list = 566,   /* _transaction_mode_list  */
  YYSYMBOL_transaction_mode = 567,         /* transaction_mode  */
  YYSYMBOL_iso_level = 568,                /* iso_level  */
  YYSYMBOL_opt_work = 569,                 /* opt_work  */
  YYSYMBOL_opt_chain = 570,                /* opt_chain  */
  YYSYMBOL_opt_to_savepoint = 571,         /* opt_to_savepoint  */
  YYSYMBOL_opt_on_location = 572,          /* opt_on_location  */
  YYSYMBOL_copyfrom_stmt = 573,            /* copyfrom_stmt  */
  YYSYMBOL_copyto_stmt = 574,              /* copyto_stmt  */
  YYSYMBOL_opt_fwf_widths = 575,           /* opt_fwf_widths  */
  YYSYMBOL_fwf_widthlist = 576,            /* fwf_widthlist  */
  YYSYMBOL_opt_header_list = 577,          /* opt_header_list  */
  YYSYMBOL_header_list = 578,              /* header_list  */
  YYSYMBOL_header = 579,                   /* header  */
  YYSYMBOL_opt_seps = 580,                 /* opt_seps  */
  YYSYMBOL_opt_using = 581,                /* opt_using  */
  YYSYMBOL_opt_nr = 582,                   /* opt_nr  */
  YYSYMBOL_opt_null_string = 583,          /* opt_null_string  */
  YYSYMBOL_opt_escape = 584,               /* opt_escape  */
  YYSYMBOL_opt_best_effort = 585,          /* opt_best_effort  */
  YYSYMBOL_string_commalist = 586,         /* string_commalist  */
  YYSYMBOL_string_commalist_contents = 587, /* string_commalist_contents  */
  YYSYMBOL_opt_endianness = 588,           /* opt_endianness  */
  YYSYMBOL_delete_stmt = 589,              /* delete_stmt  */
  YYSYMBOL_check_identity = 590,           /* check_identity  */
  YYSYMBOL_truncate_stmt = 591,            /* truncate_stmt  */
  YYSYMBOL_update_stmt = 592,              /* update_stmt  */
  YYSYMBOL_opt_search_condition = 593,     /* opt_search_condition  */
  YYSYMBOL_merge_update_or_delete = 594,   /* merge_update_or_delete  */
  YYSYMBOL_merge_insert = 595,             /* merge_insert  */
  YYSYMBOL_merge_match_clause = 596,       /* merge_match_clause  */
  YYSYMBOL_merge_when_list = 597,          /* merge_when_list  */
  YYSYMBOL_merge_stmt = 598,               /* merge_stmt  */
  YYSYMBOL_insert_stmt = 599,              /* insert_stmt  */
  YYSYMBOL_values_or_query_spec = 600,     /* values_or_query_spec  */
  YYSYMBOL_row_commalist = 601,            /* row_commalist  */
  YYSYMBOL_atom_commalist = 602,           /* atom_commalist  */
  YYSYMBOL_value_commalist = 603,          /* value_commalist  */
  YYSYMBOL_null = 604,                     /* null  */
  YYSYMBOL_insert_atom = 605,              /* insert_atom  */
  YYSYMBOL_value = 606,                    /* value  */
  YYSYMBOL_opt_distinct = 607,             /* opt_distinct  */
  YYSYMBOL_assignment_commalist = 608,     /* assignment_commalist  */
  YYSYMBOL_assignment = 609,               /* assignment  */
  YYSYMBOL_opt_where_clause = 610,         /* opt_where_clause  */
  YYSYMBOL_joined_table = 611,             /* joined_table  */
  YYSYMBOL_join_type = 612,                /* join_type  */
  YYSYMBOL_opt_outer = 613,                /* opt_outer  */
  YYSYMBOL_outer_join_type = 614,          /* outer_join_type  */
  YYSYMBOL_join_spec = 615,                /* join_spec  */
  YYSYMBOL_with_query = 616,               /* with_query  */
  YYSYMBOL_with_list = 617,                /* with_list  */
  YYSYMBOL_with_list_element = 618,        /* with_list_element  */
  YYSYMBOL_with_query_expression = 619,    /* with_query_expression  */
  YYSYMBOL_simple_select = 620,            /* simple_select  */
  YYSYMBOL_select_statement_single_row = 621, /* select_statement_single_row  */
  YYSYMBOL_select_no_parens_orderby = 622, /* select_no_parens_orderby  */
  YYSYMBOL_select_no_parens = 623,         /* select_no_parens  */
  YYSYMBOL_set_distinct = 624,             /* set_distinct  */
  YYSYMBOL_opt_corresponding = 625,        /* opt_corresponding  */
  YYSYMBOL_selection = 626,                /* selection  */
  YYSYMBOL_table_exp = 627,                /* table_exp  */
  YYSYMBOL_window_definition = 628,        /* window_definition  */
  YYSYMBOL_window_definition_list = 629,   /* window_definition_list  */
  YYSYMBOL_opt_window_clause = 630,        /* opt_window_clause  */
  YYSYMBOL_opt_from_clause = 631,          /* opt_from_clause  */
  YYSYMBOL_table_ref_commalist = 632,      /* table_ref_commalist  */
  YYSYMBOL_table_ref = 633,                /* table_ref  */
  YYSYMBOL_table_name = 634,               /* table_name  */
  YYSYMBOL_opt_table_name = 635,           /* opt_table_name  */
  YYSYMBOL_opt_group_by_clause = 636,      /* opt_group_by_clause  */
  YYSYMBOL_group_by_list = 637,            /* group_by_list  */
  YYSYMBOL_group_by_element = 638,         /* group_by_element  */
  YYSYMBOL_ordinary_grouping_set = 639,    /* ordinary_grouping_set  */
  YYSYMBOL_ordinary_grouping_element = 640, /* ordinary_grouping_element  */
  YYSYMBOL_column_ref_commalist = 641,     /* column_ref_commalist  */
  YYSYMBOL_grouping_set_list = 642,        /* grouping_set_list  */
  YYSYMBOL_grouping_set_element = 643,     /* grouping_set_element  */
  YYSYMBOL_opt_having_clause = 644,        /* opt_having_clause  */
  YYSYMBOL_search_condition = 645,         /* search_condition  */
  YYSYMBOL_and_exp = 646,                  /* and_exp  */
  YYSYMBOL_opt_order_by_clause = 647,      /* opt_order_by_clause  */
  YYSYMBOL_opt_limit = 648,                /* opt_limit  */
  YYSYMBOL_opt_offset = 649,               /* opt_offset  */
  YYSYMBOL_opt_sample = 650,               /* opt_sample  */
  YYSYMBOL_opt_seed = 651,                 /* opt_seed  */
  YYSYMBOL_sort_specification_list = 652,  /* sort_specification_list  */
  YYSYMBOL_ordering_spec = 653,            /* ordering_spec  */
  YYSYMBOL_opt_asc_desc = 654,             /* opt_asc_desc  */
  YYSYMBOL_opt_nulls_first_last = 655,     /* opt_nulls_first_last  */
  YYSYMBOL_predicate = 656,                /* predicate  */
  YYSYMBOL_pred_exp = 657,                 /* pred_exp  */
  YYSYMBOL_any_all_some = 658,             /* any_all_some  */
  YYSYMBOL_comparison_predicate = 659,     /* comparison_predicate  */
  YYSYMBOL_between_predicate = 660,        /* between_predicate  */
  YYSYMBOL_opt_bounds = 661,               /* opt_bounds  */
  YYSYMBOL_like_predicate = 662,           /* like_predicate  */
  YYSYMBOL_like_exp = 663,                 /* like_exp  */
  YYSYMBOL_test_for_null = 664,            /* test_for_null  */
  YYSYMBOL_in_predicate = 665,             /* in_predicate  */
  YYSYMBOL_pred_exp_list = 666,            /* pred_exp_list  */
  YYSYMBOL_existence_test = 667,           /* existence_test  */
  YYSYMBOL_filter_arg_list = 668,          /* filter_arg_list  */
  YYSYMBOL_filter_args = 669,              /* filter_args  */
  YYSYMBOL_filter_exp = 670,               /* filter_exp  */
  YYSYMBOL_subquery_with_orderby = 671,    /* subquery_with_orderby  */
  YYSYMBOL_subquery = 672,                 /* subquery  */
  YYSYMBOL_simple_scalar_exp = 673,        /* simple_scalar_exp  */
  YYSYMBOL_scalar_exp = 674,               /* scalar_exp  */
  YYSYMBOL_opt_over = 675,                 /* opt_over  */
  YYSYMBOL_value_exp = 676,                /* value_exp  */
  YYSYMBOL_param = 677,                    /* param  */
  YYSYMBOL_window_specification = 678,     /* window_specification  */
  YYSYMBOL_window_ident_clause = 679,      /* window_ident_clause  */
  YYSYMBOL_search_condition_commalist = 680, /* search_condition_commalist  */
  YYSYMBOL_window_partition_clause = 681,  /* window_partition_clause  */
  YYSYMBOL_window_order_clause = 682,      /* window_order_clause  */
  YYSYMBOL_window_frame_clause = 683,      /* window_frame_clause  */
  YYSYMBOL_window_frame_units = 684,       /* window_frame_units  */
  YYSYMBOL_window_frame_extent = 685,      /* window_frame_extent  */
  YYSYMBOL_window_frame_start = 686,       /* window_frame_start  */
  YYSYMBOL_window_bound = 687,             /* window_bound  */
  YYSYMBOL_window_frame_between = 688,     /* window_frame_between  */
  YYSYMBOL_window_following_bound = 689,   /* window_following_bound  */
  YYSYMBOL_window_frame_exclusion = 690,   /* window_frame_exclusion  */
  YYSYMBOL_func_ref = 691,                 /* func_ref  */
  YYSYMBOL_qfunc = 692,                    /* qfunc  */
  YYSYMBOL_func_ident = 693,               /* func_ident  */
  YYSYMBOL_datetime_funcs = 694,           /* datetime_funcs  */
  YYSYMBOL_opt_brackets = 695,             /* opt_brackets  */
  YYSYMBOL_string_funcs = 696,             /* string_funcs  */
  YYSYMBOL_column_exp_commalist = 697,     /* column_exp_commalist  */
  YYSYMBOL_column_exp = 698,               /* column_exp  */
  YYSYMBOL_opt_alias_name = 699,           /* opt_alias_name  */
  YYSYMBOL_atom = 700,                     /* atom  */
  YYSYMBOL_qrank = 701,                    /* qrank  */
  YYSYMBOL_aggr_or_window_ref = 702,       /* aggr_or_window_ref  */
  YYSYMBOL_opt_sign = 703,                 /* opt_sign  */
  YYSYMBOL_tz = 704,                       /* tz  */
  YYSYMBOL_time_precision = 705,           /* time_precision  */
  YYSYMBOL_timestamp_precision = 706,      /* timestamp_precision  */
  YYSYMBOL_datetime_type = 707,            /* datetime_type  */
  YYSYMBOL_non_second_datetime_field = 708, /* non_second_datetime_field  */
  YYSYMBOL_datetime_field = 709,           /* datetime_field  */
  YYSYMBOL_extract_datetime_field = 710,   /* extract_datetime_field  */
  YYSYMBOL_start_field = 711,              /* start_field  */
  YYSYMBOL_end_field = 712,                /* end_field  */
  YYSYMBOL_single_datetime_field = 713,    /* single_datetime_field  */
  YYSYMBOL_interval_qualifier = 714,       /* interval_qualifier  */
  YYSYMBOL_interval_type = 715,            /* interval_type  */
  YYSYMBOL_session_user = 716,             /* session_user  */
  YYSYMBOL_session_timezone = 717,         /* session_timezone  */
  YYSYMBOL_session_schema = 718,           /* session_schema  */
  YYSYMBOL_session_role = 719,             /* session_role  */
  YYSYMBOL_literal = 720,                  /* literal  */
  YYSYMBOL_interval_expression = 721,      /* interval_expression  */
  YYSYMBOL_qname = 722,                    /* qname  */
  YYSYMBOL_column_ref = 723,               /* column_ref  */
  YYSYMBOL_variable_ref = 724,             /* variable_ref  */
  YYSYMBOL_cast_exp = 725,                 /* cast_exp  */
  YYSYMBOL_case_exp = 726,                 /* case_exp  */
  YYSYMBOL_case_search_condition_commalist = 727, /* case_search_condition_commalist  */
  YYSYMBOL_when_value = 728,               /* when_value  */
  YYSYMBOL_when_value_list = 729,          /* when_value_list  */
  YYSYMBOL_when_search = 730,              /* when_search  */
  YYSYMBOL_when_search_list = 731,         /* when_search_list  */
  YYSYMBOL_case_opt_else = 732,            /* case_opt_else  */
  YYSYMBOL_nonzero = 733,                  /* nonzero  */
  YYSYMBOL_nonzerolng = 734,               /* nonzerolng  */
  YYSYMBOL_poslng = 735,                   /* poslng  */
  YYSYMBOL_posint = 736,                   /* posint  */
  YYSYMBOL_data_type = 737,                /* data_type  */
  YYSYMBOL_subgeometry_type = 738,         /* subgeometry_type  */
  YYSYMBOL_type_alias = 739,               /* type_alias  */
  YYSYMBOL_varchar = 740,                  /* varchar  */
  YYSYMBOL_clob = 741,                     /* clob  */
  YYSYMBOL_blob = 742,                     /* blob  */
  YYSYMBOL_column = 743,                   /* column  */
  YYSYMBOL_authid = 744,                   /* authid  */
  YYSYMBOL_calc_restricted_ident = 745,    /* calc_restricted_ident  */
  YYSYMBOL_restricted_ident = 746,         /* restricted_ident  */
  YYSYMBOL_calc_ident = 747,               /* calc_ident  */
  YYSYMBOL_ident = 748,                    /* ident  */
  YYSYMBOL_non_reserved_word = 749,        /* non_reserved_word  */
  YYSYMBOL_lngval = 750,                   /* lngval  */
  YYSYMBOL_ident_or_uident = 751,          /* ident_or_uident  */
  YYSYMBOL_intval = 752,                   /* intval  */
  YYSYMBOL_opt_uescape = 753,              /* opt_uescape  */
  YYSYMBOL_ustring = 754,                  /* ustring  */
  YYSYMBOL_blobstring = 755,               /* blobstring  */
  YYSYMBOL_sstring = 756,                  /* sstring  */
  YYSYMBOL_string = 757,                   /* string  */
  YYSYMBOL_exec = 758,                     /* exec  */
  YYSYMBOL_dealloc_ref = 759,              /* dealloc_ref  */
  YYSYMBOL_dealloc = 760,                  /* dealloc  */
  YYSYMBOL_exec_ref = 761,                 /* exec_ref  */
  YYSYMBOL_opt_path_specification = 762,   /* opt_path_specification  */
  YYSYMBOL_path_specification = 763,       /* path_specification  */
  YYSYMBOL_schema_name_list = 764,         /* schema_name_list  */
  YYSYMBOL_comment_on_statement = 765,     /* comment_on_statement  */
  YYSYMBOL_catalog_object = 766,           /* catalog_object  */
  YYSYMBOL_XML_value_expression = 767,     /* XML_value_expression  */
  YYSYMBOL_XML_value_expression_list = 768, /* XML_value_expression_list  */
  YYSYMBOL_XML_primary = 769,              /* XML_primary  */
  YYSYMBOL_XML_value_function = 770,       /* XML_value_function  */
  YYSYMBOL_XML_comment = 771,              /* XML_comment  */
  YYSYMBOL_XML_concatenation = 772,        /* XML_concatenation  */
  YYSYMBOL_XML_document = 773,             /* XML_document  */
  YYSYMBOL_XML_element = 774,              /* XML_element  */
  YYSYMBOL_opt_comma_XML_namespace_declaration_attributes_element_content = 775, /* opt_comma_XML_namespace_declaration_attributes_element_content  */
  YYSYMBOL_XML_element_name = 776,         /* XML_element_name  */
  YYSYMBOL_XML_attributes = 777,           /* XML_attributes  */
  YYSYMBOL_XML_attribute_list = 778,       /* XML_attribute_list  */
  YYSYMBOL_XML_attribute = 779,            /* XML_attribute  */
  YYSYMBOL_opt_XML_attribute_name = 780,   /* opt_XML_attribute_name  */
  YYSYMBOL_XML_attribute_value = 781,      /* XML_attribute_value  */
  YYSYMBOL_XML_attribute_name = 782,       /* XML_attribute_name  */
  YYSYMBOL_XML_element_content_and_option = 783, /* XML_element_content_and_option  */
  YYSYMBOL_XML_element_content_list = 784, /* XML_element_content_list  */
  YYSYMBOL_XML_element_content = 785,      /* XML_element_content  */
  YYSYMBOL_opt_XML_content_option = 786,   /* opt_XML_content_option  */
  YYSYMBOL_XML_content_option = 787,       /* XML_content_option  */
  YYSYMBOL_XML_forest = 788,               /* XML_forest  */
  YYSYMBOL_opt_XML_namespace_declaration_and_comma = 789, /* opt_XML_namespace_declaration_and_comma  */
  YYSYMBOL_forest_element_list = 790,      /* forest_element_list  */
  YYSYMBOL_forest_element = 791,           /* forest_element  */
  YYSYMBOL_forest_element_value = 792,     /* forest_element_value  */
  YYSYMBOL_opt_forest_element_name = 793,  /* opt_forest_element_name  */
  YYSYMBOL_forest_element_name = 794,      /* forest_element_name  */
  YYSYMBOL_XML_parse = 795,                /* XML_parse  */
  YYSYMBOL_XML_whitespace_option = 796,    /* XML_whitespace_option  */
  YYSYMBOL_XML_PI = 797,                   /* XML_PI  */
  YYSYMBOL_XML_PI_target = 798,            /* XML_PI_target  */
  YYSYMBOL_opt_comma_string_value_expression = 799, /* opt_comma_string_value_expression  */
  YYSYMBOL_XML_query = 800,                /* XML_query  */
  YYSYMBOL_XQuery_expression = 801,        /* XQuery_expression  */
  YYSYMBOL_opt_XML_query_argument_list = 802, /* opt_XML_query_argument_list  */
  YYSYMBOL_XML_query_default_passing_mechanism = 803, /* XML_query_default_passing_mechanism  */
  YYSYMBOL_XML_query_argument_list = 804,  /* XML_query_argument_list  */
  YYSYMBOL_XML_query_argument = 805,       /* XML_query_argument  */
  YYSYMBOL_XML_query_context_item = 806,   /* XML_query_context_item  */
  YYSYMBOL_XML_query_variable = 807,       /* XML_query_variable  */
  YYSYMBOL_opt_XML_query_returning_mechanism = 808, /* opt_XML_query_returning_mechanism  */
  YYSYMBOL_XML_query_empty_handling_option = 809, /* XML_query_empty_handling_option  */
  YYSYMBOL_XML_text = 810,                 /* XML_text  */
  YYSYMBOL_XML_validate = 811,             /* XML_validate  */
  YYSYMBOL_document_or_content_or_sequence = 812, /* document_or_content_or_sequence  */
  YYSYMBOL_document_or_content = 813,      /* document_or_content  */
  YYSYMBOL_opt_XML_returning_clause = 814, /* opt_XML_returning_clause  */
  YYSYMBOL_XML_namespace_declaration = 815, /* XML_namespace_declaration  */
  YYSYMBOL_XML_namespace_declaration_item_list = 816, /* XML_namespace_declaration_item_list  */
  YYSYMBOL_XML_namespace_declaration_item = 817, /* XML_namespace_declaration_item  */
  YYSYMBOL_XML_namespace_prefix = 818,     /* XML_namespace_prefix  */
  YYSYMBOL_XML_namespace_URI = 819,        /* XML_namespace_URI  */
  YYSYMBOL_XML_regular_namespace_declaration_item = 820, /* XML_regular_namespace_declaration_item  */
  YYSYMBOL_XML_default_namespace_declaration_item = 821, /* XML_default_namespace_declaration_item  */
  YYSYMBOL_opt_XML_passing_mechanism = 822, /* opt_XML_passing_mechanism  */
  YYSYMBOL_XML_passing_mechanism = 823,    /* XML_passing_mechanism  */
  YYSYMBOL_opt_XML_valid_according_to_clause = 824, /* opt_XML_valid_according_to_clause  */
  YYSYMBOL_XML_valid_according_to_clause = 825, /* XML_valid_according_to_clause  */
  YYSYMBOL_XML_valid_according_to_what = 826, /* XML_valid_according_to_what  */
  YYSYMBOL_XML_valid_according_to_URI = 827, /* XML_valid_according_to_URI  */
  YYSYMBOL_XML_valid_target_namespace_URI = 828, /* XML_valid_target_namespace_URI  */
  YYSYMBOL_XML_URI = 829,                  /* XML_URI  */
  YYSYMBOL_opt_XML_valid_schema_location = 830, /* opt_XML_valid_schema_location  */
  YYSYMBOL_XML_valid_schema_location_URI = 831, /* XML_valid_schema_location_URI  */
  YYSYMBOL_XML_valid_according_to_identifier = 832, /* XML_valid_according_to_identifier  */
  YYSYMBOL_registered_XML_Schema_name = 833, /* registered_XML_Schema_name  */
  YYSYMBOL_opt_XML_valid_element_clause = 834, /* opt_XML_valid_element_clause  */
  YYSYMBOL_XML_valid_element_clause = 835, /* XML_valid_element_clause  */
  YYSYMBOL_opt_XML_valid_element_name_specification = 836, /* opt_XML_valid_element_name_specification  */
  YYSYMBOL_XML_valid_element_name_specification = 837, /* XML_valid_element_name_specification  */
  YYSYMBOL_XML_valid_element_namespace_specification = 838, /* XML_valid_element_namespace_specification  */
  YYSYMBOL_XML_valid_element_namespace_URI = 839, /* XML_valid_element_namespace_URI  */
  YYSYMBOL_XML_valid_element_name = 840,   /* XML_valid_element_name  */
  YYSYMBOL_XML_aggregate = 841             /* XML_aggregate  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;


/* Second part of user prologue.  */
#line 184 "sql_parser.y"

extern int sqllex( YYSTYPE *yylval, void *m );
/* enable to activate debugging support
int yydebug=1;
*/

#line 1110 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"


#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  275
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   23124

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  381
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  461
/* YYNRULES -- Number of rules.  */
#define YYNRULES  1297
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  2380

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   617


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int16 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,   215,   202,     2,
     180,   181,   213,   200,   375,   201,   376,   214,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   377,     2,
       2,   183,     2,   380,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   378,     2,   379,   204,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,   203,     2,   217,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   182,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   205,   206,   207,   208,   209,   210,   211,   212,
     216,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   291,   292,   293,   294,   295,   296,
     297,   298,   299,   300,   301,   302,   303,   304,   305,   306,
     307,   308,   309,   310,   311,   312,   313,   314,   315,   316,
     317,   318,   319,   320,   321,   322,   323,   324,   325,   326,
     327,   328,   329,   330,   331,   332,   333,   334,   335,   336,
     337,   338,   339,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,   350,   351,   352,   353,   354,   355,   356,
     357,   358,   359,   360,   361,   362,   363,   364,   365,   366,
     367,   368,   369,   370,   371,   372,   373,   374
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   728,   728,   739,   739,   753,   753,   767,   767,   781,
     781,   790,   790,   795,   796,   797,   798,   799,   800,   804,
     805,   809,   810,   813,   815,   819,   823,   826,   827,   831,
     832,   836,   837,   841,   844,   847,   851,   852,   853,   854,
     855,   856,   857,   858,   859,   866,   867,   871,   872,   876,
     877,   881,   882,   886,   891,   899,   900,   904,   909,   914,
     921,   928,   935,   942,   949,   957,   966,   975,   979,   983,
     990,   993,   994,   998,   999,  1003,  1004,  1008,  1008,  1008,
    1008,  1008,  1011,  1012,  1016,  1017,  1021,  1030,  1041,  1042,
    1047,  1048,  1052,  1053,  1058,  1059,  1063,  1071,  1081,  1082,
    1086,  1087,  1091,  1095,  1102,  1103,  1108,  1109,  1113,  1114,
    1115,  1126,  1127,  1128,  1132,  1133,  1138,  1139,  1140,  1141,
    1142,  1143,  1144,  1148,  1149,  1154,  1155,  1161,  1167,  1178,
    1184,  1190,  1196,  1202,  1208,  1219,  1225,  1232,  1238,  1253,
    1258,  1270,  1279,  1280,  1284,  1285,  1289,  1290,  1295,  1300,
    1304,  1308,  1310,  1318,  1326,  1331,  1336,  1345,  1346,  1350,
    1351,  1352,  1353,  1354,  1355,  1356,  1357,  1373,  1384,  1401,
    1411,  1412,  1415,  1416,  1420,  1421,  1425,  1426,  1427,  1431,
    1432,  1433,  1434,  1435,  1439,  1440,  1441,  1442,  1443,  1444,
    1445,  1446,  1453,  1463,  1464,  1465,  1466,  1486,  1491,  1506,
    1507,  1511,  1512,  1516,  1517,  1521,  1522,  1526,  1530,  1538,
    1539,  1540,  1544,  1557,  1564,  1577,  1593,  1606,  1619,  1637,
    1638,  1642,  1646,  1647,  1651,  1652,  1672,  1676,  1677,  1681,
    1682,  1686,  1687,  1691,  1692,  1696,  1701,  1707,  1716,  1717,
    1722,  1727,  1733,  1742,  1743,  1744,  1745,  1746,  1747,  1751,
    1752,  1753,  1754,  1758,  1759,  1763,  1773,  1774,  1775,  1779,
    1781,  1785,  1785,  1786,  1786,  1786,  1789,  1790,  1794,  1802,
    1855,  1856,  1860,  1862,  1867,  1876,  1878,  1882,  1882,  1882,
    1885,  1889,  1893,  1902,  1931,  1969,  1970,  1975,  1986,  1987,
    1991,  1992,  1993,  1994,  1995,  1999,  2003,  2007,  2008,  2009,
    2010,  2011,  2015,  2016,  2017,  2018,  2022,  2023,  2027,  2028,
    2029,  2030,  2031,  2041,  2045,  2047,  2049,  2063,  2067,  2069,
    2074,  2078,  2091,  2092,  2096,  2097,  2101,  2102,  2106,  2107,
    2111,  2115,  2119,  2127,  2131,  2132,  2136,  2137,  2138,  2139,
    2140,  2141,  2142,  2143,  2144,  2145,  2148,  2149,  2152,  2166,
    2180,  2228,  2230,  2234,  2252,  2253,  2258,  2259,  2264,  2265,
    2266,  2267,  2268,  2269,  2270,  2271,  2272,  2273,  2274,  2275,
    2279,  2280,  2281,  2282,  2283,  2284,  2285,  2286,  2290,  2291,
    2292,  2293,  2294,  2295,  2308,  2312,  2316,  2325,  2328,  2329,
    2330,  2334,  2338,  2339,  2340,  2345,  2351,  2359,  2367,  2369,
    2374,  2382,  2384,  2389,  2390,  2397,  2411,  2412,  2414,  2425,
    2446,  2447,  2451,  2452,  2456,  2460,  2468,  2470,  2475,  2476,
    2480,  2484,  2489,  2538,  2553,  2554,  2559,  2560,  2561,  2562,
    2563,  2567,  2568,  2572,  2573,  2579,  2580,  2581,  2582,  2585,
    2587,  2590,  2592,  2596,  2604,  2605,  2609,  2610,  2614,  2615,
    2619,  2621,  2627,  2636,  2642,  2651,  2660,  2666,  2671,  2672,
    2673,  2674,  2683,  2684,  2685,  2689,  2692,  2697,  2698,  2699,
    2704,  2705,  2709,  2710,  2711,  2712,  2713,  2714,  2715,  2719,
    2726,  2727,  2731,  2733,  2735,  2737,  2741,  2743,  2745,  2750,
    2751,  2755,  2757,  2762,  2763,  2764,  2765,  2769,  2770,  2771,
    2772,  2773,  2777,  2778,  2782,  2783,  2784,  2788,  2789,  2793,
    2794,  2795,  2800,  2815,  2830,  2836,  2848,  2857,  2866,  2876,
    2877,  2882,  2883,  2888,  2889,  2893,  2894,  2898,  2902,  2911,
    2915,  2920,  2925,  2934,  2935,  2939,  2940,  2941,  2942,  2944,
    2949,  2950,  2954,  2955,  2956,  2960,  2961,  2965,  2966,  2970,
    2971,  2976,  2977,  2978,  2979,  2983,  2993,  2994,  2995,  2999,
    3005,  3014,  3026,  3027,  3031,  3035,  3040,  3048,  3053,  3061,
    3062,  3066,  3077,  3085,  3096,  3099,  3103,  3107,  3108,  3113,
    3114,  3119,  3120,  3125,  3129,  3130,  3134,  3135,  3136,  3140,
    3141,  3142,  3146,  3147,  3152,  3157,  3165,  3166,  3172,  3174,
    3182,  3190,  3201,  3202,  3203,  3207,  3208,  3212,  3213,  3214,
    3218,  3219,  3239,  3243,  3253,  3254,  3258,  3271,  3272,  3273,
    3274,  3275,  3276,  3280,  3281,  3285,  3297,  3309,  3341,  3350,
    3359,  3367,  3372,  3373,  3377,  3378,  3379,  3384,  3385,  3387,
    3392,  3396,  3407,  3412,  3413,  3417,  3418,  3422,  3423,  3427,
    3428,  3433,  3438,  3444,  3450,  3461,  3473,  3478,  3483,  3488,
    3493,  3498,  3506,  3507,  3511,  3512,  3516,  3517,  3521,  3522,
    3523,  3524,  3525,  3529,  3530,  3534,  3535,  3539,  3540,  3544,
    3545,  3549,  3550,  3551,  3552,  3553,  3557,  3558,  3562,  3567,
    3571,  3576,  3580,  3581,  3586,  3587,  3591,  3595,  3596,  3600,
    3604,  3605,  3609,  3613,  3617,  3618,  3622,  3626,  3627,  3632,
    3640,  3641,  3642,  3646,  3647,  3648,  3652,  3653,  3654,  3655,
    3656,  3657,  3658,  3659,  3663,  3664,  3668,  3669,  3670,  3674,
    3681,  3688,  3696,  3707,  3714,  3724,  3725,  3726,  3730,  3737,
    3744,  3751,  3761,  3765,  3781,  3782,  3786,  3792,  3798,  3803,
    3811,  3813,  3820,  3821,  3825,  3826,  3830,  3834,  3843,  3844,
    3848,  3849,  3854,  3855,  3863,  3871,  3879,  3887,  3895,  3903,
    3911,  3919,  3927,  3935,  3943,  3950,  3958,  3966,  3974,  3982,
    3990,  3998,  4006,  4013,  4021,  4029,  4037,  4045,  4047,  4060,
    4064,  4065,  4069,  4070,  4071,  4075,  4076,  4084,  4085,  4086,
    4087,  4088,  4089,  4090,  4091,  4092,  4100,  4101,  4102,  4103,
    4104,  4108,  4117,  4122,  4123,  4127,  4128,  4132,  4133,  4138,
    4139,  4144,  4145,  4150,  4151,  4152,  4156,  4162,  4166,  4169,
    4171,  4177,  4178,  4182,  4186,  4189,  4194,  4195,  4196,  4197,
    4198,  4202,  4207,  4226,  4227,  4232,  4233,  4234,  4235,  4239,
    4247,  4253,  4259,  4265,  4271,  4280,  4281,  4285,  4296,  4307,
    4315,  4323,  4331,  4339,  4353,  4354,  4359,  4364,  4369,  4374,
    4382,  4383,  4384,  4388,  4392,  4393,  4398,  4404,  4410,  4416,
    4422,  4428,  4434,  4440,  4456,  4472,  4488,  4492,  4493,  4494,
    4498,  4499,  4510,  4512,  4516,  4518,  4522,  4523,  4529,  4538,
    4539,  4540,  4541,  4542,  4546,  4547,  4551,  4552,  4553,  4554,
    4555,  4556,  4558,  4560,  4564,  4570,  4573,  4579,  4582,  4588,
    4591,  4596,  4618,  4619,  4620,  4624,  4625,  4629,  4630,  4634,
    4635,  4639,  4645,  4706,  4734,  4792,  4826,  4840,  4853,  4866,
    4879,  4880,  4894,  4908,  4923,  4938,  4955,  4959,  4966,  5012,
    5013,  5017,  5028,  5031,  5035,  5043,  5046,  5052,  5058,  5066,
    5071,  5073,  5079,  5087,  5091,  5096,  5104,  5106,  5111,  5119,
    5121,  5126,  5127,  5133,  5144,  5155,  5165,  5175,  5177,  5182,
    5183,  5185,  5187,  5196,  5197,  5206,  5207,  5208,  5209,  5210,
    5212,  5213,  5224,  5239,  5240,  5251,  5266,  5267,  5268,  5269,
    5270,  5271,  5272,  5274,  5275,  5277,  5286,  5297,  5308,  5315,
    5328,  5341,  5348,  5368,  5381,  5397,  5409,  5410,  5414,  5415,
    5416,  5419,  5420,  5423,  5425,  5428,  5429,  5431,  5432,  5433,
    5437,  5448,  5449,  5451,  5452,  5453,  5454,  5458,  5469,  5470,
    5471,  5472,  5473,  5474,  5475,  5476,  5477,  5478,  5479,  5480,
    5481,  5482,  5483,  5484,  5485,  5486,  5487,  5488,  5489,  5490,
    5491,  5492,  5493,  5495,  5496,  5497,  5498,  5499,  5500,  5501,
    5502,  5503,  5504,  5505,  5506,  5507,  5508,  5509,  5510,  5511,
    5512,  5513,  5514,  5515,  5516,  5517,  5518,  5519,  5520,  5521,
    5522,  5523,  5524,  5525,  5526,  5527,  5528,  5529,  5530,  5531,
    5532,  5533,  5534,  5535,  5536,  5537,  5538,  5539,  5540,  5541,
    5542,  5543,  5544,  5545,  5546,  5547,  5548,  5549,  5550,  5551,
    5552,  5555,  5556,  5557,  5558,  5559,  5560,  5561,  5562,  5563,
    5564,  5565,  5566,  5567,  5568,  5569,  5570,  5574,  5594,  5595,
    5599,  5620,  5621,  5633,  5635,  5640,  5642,  5647,  5649,  5654,
    5655,  5665,  5672,  5673,  5677,  5684,  5690,  5706,  5707,  5711,
    5714,  5717,  5723,  5732,  5733,  5734,  5735,  5741,  5748,  5749,
    5750,  5754,  5758,  5760,  5765,  5769,  5770,  5771,  5772,  5773,
    5774,  5775,  5776,  5777,  5778,  5782,  5790,  5798,  5805,  5819,
    5820,  5824,  5828,  5832,  5836,  5840,  5844,  5851,  5855,  5859,
    5860,  5870,  5878,  5879,  5883,  5887,  5891,  5898,  5900,  5905,
    5909,  5910,  5914,  5915,  5916,  5917,  5918,  5922,  5935,  5936,
    5940,  5942,  5947,  5953,  5957,  5958,  5962,  5967,  5976,  5977,
    5981,  5992,  5996,  5997,  6002,  6012,  6015,  6017,  6021,  6025,
    6026,  6030,  6031,  6035,  6039,  6042,  6044,  6048,  6049,  6053,
    6061,  6070,  6071,  6075,  6076,  6080,  6081,  6082,  6097,  6101,
    6102,  6112,  6113,  6117,  6121,  6125,  6133,  6137,  6140,  6142,
    6146,  6147,  6150,  6152,  6156,  6161,  6162,  6166,  6167,  6171,
    6175,  6178,  6180,  6184,  6188,  6192,  6195,  6197,  6201,  6202,
    6206,  6208,  6212,  6216,  6217,  6221,  6225,  6229
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "STRING", "USTRING",
  "XSTRING", "IDENT", "UIDENT", "aTYPE", "ALIAS", "RANK", "sqlINT",
  "OIDNUM", "HEXADECIMAL", "INTNUM", "APPROXNUM", "USING", "GLOBAL",
  "CAST", "CONVERT", "CHARACTER", "VARYING", "LARGE", "OBJECT", "VARCHAR",
  "CLOB", "sqlTEXT", "BINARY", "sqlBLOB", "sqlDECIMAL", "sqlFLOAT",
  "TINYINT", "SMALLINT", "BIGINT", "HUGEINT", "sqlINTEGER", "sqlDOUBLE",
  "sqlREAL", "PRECISION", "PARTIAL", "SIMPLE", "ACTION", "CASCADE",
  "RESTRICT", "BOOL_FALSE", "BOOL_TRUE", "CURRENT_DATE",
  "CURRENT_TIMESTAMP", "CURRENT_TIME", "LOCALTIMESTAMP", "LOCALTIME",
  "BIG", "LITTLE", "NATIVE", "ENDIAN", "LEX_ERROR", "GEOMETRY",
  "GEOMETRYSUBTYPE", "GEOMETRYA", "USER", "CURRENT_USER", "SESSION_USER",
  "LOCAL", "BEST", "EFFORT", "CURRENT_ROLE", "sqlSESSION",
  "CURRENT_SCHEMA", "CURRENT_TIMEZONE", "sqlDELETE", "UPDATE", "SELECT",
  "INSERT", "MATCHED", "LATERAL", "LEFT", "RIGHT", "FULL", "OUTER",
  "NATURAL", "CROSS", "JOIN", "INNER", "COMMIT", "ROLLBACK", "SAVEPOINT",
  "RELEASE", "WORK", "CHAIN", "NO", "PRESERVE", "ROWS", "START",
  "TRANSACTION", "READ", "WRITE", "ONLY", "ISOLATION", "LEVEL",
  "UNCOMMITTED", "COMMITTED", "sqlREPEATABLE", "SERIALIZABLE",
  "DIAGNOSTICS", "sqlSIZE", "STORAGE", "SNAPSHOT", "ASYMMETRIC",
  "SYMMETRIC", "ORDER", "ORDERED", "BY", "IMPRINTS", "ESCAPE", "UESCAPE",
  "HAVING", "sqlGROUP", "ROLLUP", "CUBE", "sqlNULL", "GROUPING", "SETS",
  "FROM", "FOR", "MATCH", "EXTRACT", "SEQUENCE", "INCREMENT", "RESTART",
  "CONTINUE", "MAXVALUE", "MINVALUE", "CYCLE", "NEXT", "VALUE", "CACHE",
  "GENERATED", "ALWAYS", "IDENTITY", "SERIAL", "BIGSERIAL",
  "AUTO_INCREMENT", "SCOLON", "AT", "XMLCOMMENT", "XMLCONCAT",
  "XMLDOCUMENT", "XMLELEMENT", "XMLATTRIBUTES", "XMLFOREST", "XMLPARSE",
  "STRIP", "WHITESPACE", "XMLPI", "XMLQUERY", "PASSING", "XMLTEXT", "NIL",
  "REF", "ABSENT", "EMPTY", "DOCUMENT", "ELEMENT", "CONTENT",
  "XMLNAMESPACES", "NAMESPACE", "XMLVALIDATE", "RETURNING", "LOCATION",
  "ID", "ACCORDING", "XMLSCHEMA", "URI", "XMLAGG", "FILTER", "UNION",
  "EXCEPT", "INTERSECT", "CORRESPONDING", "DATA", "'('", "')'", "NOT",
  "'='", "ALL", "ANY", "NOT_BETWEEN", "BETWEEN", "NOT_IN", "sqlIN",
  "NOT_EXISTS", "EXISTS", "NOT_LIKE", "LIKE", "NOT_ILIKE", "ILIKE", "OR",
  "SOME", "AND", "COMPARISON", "'+'", "'-'", "'&'", "'|'", "'^'",
  "LEFT_SHIFT", "RIGHT_SHIFT", "LEFT_SHIFT_ASSIGN", "RIGHT_SHIFT_ASSIGN",
  "CONCATSTRING", "SUBSTRING", "POSITION", "SPLIT_PART", "'*'", "'/'",
  "'%'", "UMINUS", "'~'", "GEOM_OVERLAP", "GEOM_OVERLAP_OR_ABOVE",
  "GEOM_OVERLAP_OR_BELOW", "GEOM_OVERLAP_OR_LEFT", "GEOM_OVERLAP_OR_RIGHT",
  "GEOM_BELOW", "GEOM_ABOVE", "GEOM_DIST", "GEOM_MBR_EQUAL", "TEMP",
  "TEMPORARY", "MERGE", "REMOTE", "REPLICA", "UNLOGGED", "ASC", "DESC",
  "AUTHORIZATION", "CHECK", "CONSTRAINT", "CREATE", "COMMENT", "NULLS",
  "FIRST", "LAST", "TYPE", "PROCEDURE", "FUNCTION", "sqlLOADER",
  "AGGREGATE", "RETURNS", "EXTERNAL", "sqlNAME", "DECLARE", "CALL",
  "LANGUAGE", "ANALYZE", "MINMAX", "SQL_EXPLAIN", "SQL_PLAN", "SQL_DEBUG",
  "SQL_TRACE", "PREP", "PREPARE", "EXEC", "EXECUTE", "DEALLOCATE",
  "DEFAULT", "DISTINCT", "DROP", "TRUNCATE", "FOREIGN", "RENAME",
  "ENCRYPTED", "UNENCRYPTED", "PASSWORD", "GRANT", "REVOKE", "ROLE",
  "ADMIN", "INTO", "IS", "KEY", "ON", "OPTION", "OPTIONS", "PATH",
  "PRIMARY", "PRIVILEGES", "PUBLIC", "REFERENCES", "SCHEMA", "SET",
  "AUTO_COMMIT", "RETURN", "ALTER", "ADD", "TABLE", "COLUMN", "TO",
  "UNIQUE", "VALUES", "VIEW", "WHERE", "WITH", "sqlDATE", "TIME",
  "TIMESTAMP", "INTERVAL", "CENTURY", "DECADE", "YEAR", "QUARTER", "DOW",
  "DOY", "MONTH", "WEEK", "DAY", "HOUR", "MINUTE", "SECOND", "EPOCH",
  "ZONE", "LIMIT", "OFFSET", "SAMPLE", "SEED", "CASE", "WHEN", "THEN",
  "ELSE", "NULLIF", "COALESCE", "IF", "ELSEIF", "WHILE", "DO", "ATOMIC",
  "BEGIN", "END", "COPY", "RECORDS", "DELIMITERS", "STDIN", "STDOUT",
  "FWF", "CLIENT", "SERVER", "INDEX", "REPLACE", "AS", "TRIGGER", "OF",
  "BEFORE", "AFTER", "ROW", "STATEMENT", "sqlNEW", "OLD", "EACH",
  "REFERENCING", "OVER", "PARTITION", "CURRENT", "EXCLUDE", "FOLLOWING",
  "PRECEDING", "OTHERS", "TIES", "RANGE", "UNBOUNDED", "GROUPS", "WINDOW",
  "X_BODY", "MAX_MEMORY", "MAX_WORKERS", "OPTIMIZER", "','", "'.'", "':'",
  "'['", "']'", "'?'", "$accept", "sqlstmt", "$@1", "$@2", "$@3", "$@4",
  "$@5", "prepare", "execute", "opt_prepare", "deallocate", "create",
  "create_or_replace", "if_exists", "if_not_exists", "drop", "set",
  "declare", "sql", "opt_minmax", "declare_statement",
  "variable_ref_commalist", "variable_list", "opt_equal", "set_statement",
  "schema", "schema_name_clause", "authorization_identifier",
  "opt_schema_default_char_set", "opt_schema_element_list",
  "schema_element_list", "schema_element", "opt_grantor", "grantor",
  "grant", "authid_list", "opt_with_grant", "opt_with_admin",
  "opt_from_grantor", "revoke", "opt_grant_for", "opt_admin_for",
  "privileges", "global_privileges", "global_privilege", "object_name",
  "object_privileges", "operation_commalist", "operation",
  "grantee_commalist", "grantee", "alter_statement",
  "opt_with_encrypted_password", "user_schema", "opt_schema_path",
  "alter_table_element", "drop_table_element", "opt_column",
  "create_statement", "seq_def", "opt_seq_params", "params_list",
  "opt_alt_seq_params", "opt_seq_param", "opt_alt_seq_param",
  "opt_seq_common_param", "index_def", "opt_index_type", "role_def",
  "opt_max_memory", "opt_max_workers", "opt_optimizer", "opt_default_role",
  "opt_schema_details_list", "opt_encrypted", "table_def",
  "partition_type", "partition_expression", "partition_on",
  "opt_partition_by", "partition_list_value", "partition_range_from",
  "partition_range_to", "partition_list", "opt_with_nulls",
  "opt_partition_spec", "opt_as_partition", "with_opt_credentials",
  "opt_temp", "opt_on_commit", "table_content_source",
  "as_subquery_clause", "with_or_without_data", "table_element_list",
  "add_table_element", "table_element", "serial_or_bigserial",
  "column_def", "opt_column_def_opt_list", "column_def_opt_list",
  "column_options", "column_option_list", "column_option", "default",
  "default_value", "column_constraint", "generated_column",
  "serial_opt_params", "table_constraint", "opt_constraint_name",
  "ref_action", "ref_on_update", "ref_on_delete", "opt_ref_action",
  "opt_match_type", "opt_match", "column_constraint_type",
  "table_constraint_type", "domain_constraint_type", "ident_commalist",
  "like_table", "view_def", "query_expression_def", "query_expression",
  "opt_with_check_option", "opt_column_list", "column_commalist_parens",
  "variable_ref_commalist_parens", "type_def", "external_function_name",
  "function_body", "func_def_type", "func_def_opt_return", "func_def",
  "routine_body", "procedure_statement_list",
  "trigger_procedure_statement_list", "procedure_statement",
  "trigger_procedure_statement", "control_statement", "call_statement",
  "call_procedure_statement", "routine_invocation", "routine_name",
  "argument_list", "return_statement", "return_value", "case_statement",
  "when_statement", "when_statements", "when_search_statement",
  "when_search_statements", "case_opt_else_statement", "if_statement",
  "if_opt_else", "while_statement", "opt_begin_label", "opt_end_label",
  "table_function_column_list", "func_data_type", "opt_paramlist",
  "paramlist", "trigger_def", "trigger_action_time", "trigger_event",
  "opt_referencing_list", "old_or_new_values_alias_list",
  "old_or_new_values_alias", "opt_as", "opt_row", "triggered_action",
  "opt_for_each", "row_or_statement", "opt_when", "triggered_statement",
  "routine_designator", "drop_statement", "opt_typelist", "typelist",
  "drop_action", "update_statement", "transaction_statement",
  "start_transaction", "transaction_stmt", "transaction_mode_list",
  "_transaction_mode_list", "transaction_mode", "iso_level", "opt_work",
  "opt_chain", "opt_to_savepoint", "opt_on_location", "copyfrom_stmt",
  "copyto_stmt", "opt_fwf_widths", "fwf_widthlist", "opt_header_list",
  "header_list", "header", "opt_seps", "opt_using", "opt_nr",
  "opt_null_string", "opt_escape", "opt_best_effort", "string_commalist",
  "string_commalist_contents", "opt_endianness", "delete_stmt",
  "check_identity", "truncate_stmt", "update_stmt", "opt_search_condition",
  "merge_update_or_delete", "merge_insert", "merge_match_clause",
  "merge_when_list", "merge_stmt", "insert_stmt", "values_or_query_spec",
  "row_commalist", "atom_commalist", "value_commalist", "null",
  "insert_atom", "value", "opt_distinct", "assignment_commalist",
  "assignment", "opt_where_clause", "joined_table", "join_type",
  "opt_outer", "outer_join_type", "join_spec", "with_query", "with_list",
  "with_list_element", "with_query_expression", "simple_select",
  "select_statement_single_row", "select_no_parens_orderby",
  "select_no_parens", "set_distinct", "opt_corresponding", "selection",
  "table_exp", "window_definition", "window_definition_list",
  "opt_window_clause", "opt_from_clause", "table_ref_commalist",
  "table_ref", "table_name", "opt_table_name", "opt_group_by_clause",
  "group_by_list", "group_by_element", "ordinary_grouping_set",
  "ordinary_grouping_element", "column_ref_commalist", "grouping_set_list",
  "grouping_set_element", "opt_having_clause", "search_condition",
  "and_exp", "opt_order_by_clause", "opt_limit", "opt_offset",
  "opt_sample", "opt_seed", "sort_specification_list", "ordering_spec",
  "opt_asc_desc", "opt_nulls_first_last", "predicate", "pred_exp",
  "any_all_some", "comparison_predicate", "between_predicate",
  "opt_bounds", "like_predicate", "like_exp", "test_for_null",
  "in_predicate", "pred_exp_list", "existence_test", "filter_arg_list",
  "filter_args", "filter_exp", "subquery_with_orderby", "subquery",
  "simple_scalar_exp", "scalar_exp", "opt_over", "value_exp", "param",
  "window_specification", "window_ident_clause",
  "search_condition_commalist", "window_partition_clause",
  "window_order_clause", "window_frame_clause", "window_frame_units",
  "window_frame_extent", "window_frame_start", "window_bound",
  "window_frame_between", "window_following_bound",
  "window_frame_exclusion", "func_ref", "qfunc", "func_ident",
  "datetime_funcs", "opt_brackets", "string_funcs", "column_exp_commalist",
  "column_exp", "opt_alias_name", "atom", "qrank", "aggr_or_window_ref",
  "opt_sign", "tz", "time_precision", "timestamp_precision",
  "datetime_type", "non_second_datetime_field", "datetime_field",
  "extract_datetime_field", "start_field", "end_field",
  "single_datetime_field", "interval_qualifier", "interval_type",
  "session_user", "session_timezone", "session_schema", "session_role",
  "literal", "interval_expression", "qname", "column_ref", "variable_ref",
  "cast_exp", "case_exp", "case_search_condition_commalist", "when_value",
  "when_value_list", "when_search", "when_search_list", "case_opt_else",
  "nonzero", "nonzerolng", "poslng", "posint", "data_type",
  "subgeometry_type", "type_alias", "varchar", "clob", "blob", "column",
  "authid", "calc_restricted_ident", "restricted_ident", "calc_ident",
  "ident", "non_reserved_word", "lngval", "ident_or_uident", "intval",
  "opt_uescape", "ustring", "blobstring", "sstring", "string", "exec",
  "dealloc_ref", "dealloc", "exec_ref", "opt_path_specification",
  "path_specification", "schema_name_list", "comment_on_statement",
  "catalog_object", "XML_value_expression", "XML_value_expression_list",
  "XML_primary", "XML_value_function", "XML_comment", "XML_concatenation",
  "XML_document", "XML_element",
  "opt_comma_XML_namespace_declaration_attributes_element_content",
  "XML_element_name", "XML_attributes", "XML_attribute_list",
  "XML_attribute", "opt_XML_attribute_name", "XML_attribute_value",
  "XML_attribute_name", "XML_element_content_and_option",
  "XML_element_content_list", "XML_element_content",
  "opt_XML_content_option", "XML_content_option", "XML_forest",
  "opt_XML_namespace_declaration_and_comma", "forest_element_list",
  "forest_element", "forest_element_value", "opt_forest_element_name",
  "forest_element_name", "XML_parse", "XML_whitespace_option", "XML_PI",
  "XML_PI_target", "opt_comma_string_value_expression", "XML_query",
  "XQuery_expression", "opt_XML_query_argument_list",
  "XML_query_default_passing_mechanism", "XML_query_argument_list",
  "XML_query_argument", "XML_query_context_item", "XML_query_variable",
  "opt_XML_query_returning_mechanism", "XML_query_empty_handling_option",
  "XML_text", "XML_validate", "document_or_content_or_sequence",
  "document_or_content", "opt_XML_returning_clause",
  "XML_namespace_declaration", "XML_namespace_declaration_item_list",
  "XML_namespace_declaration_item", "XML_namespace_prefix",
  "XML_namespace_URI", "XML_regular_namespace_declaration_item",
  "XML_default_namespace_declaration_item", "opt_XML_passing_mechanism",
  "XML_passing_mechanism", "opt_XML_valid_according_to_clause",
  "XML_valid_according_to_clause", "XML_valid_according_to_what",
  "XML_valid_according_to_URI", "XML_valid_target_namespace_URI",
  "XML_URI", "opt_XML_valid_schema_location",
  "XML_valid_schema_location_URI", "XML_valid_according_to_identifier",
  "registered_XML_Schema_name", "opt_XML_valid_element_clause",
  "XML_valid_element_clause", "opt_XML_valid_element_name_specification",
  "XML_valid_element_name_specification",
  "XML_valid_element_namespace_specification",
  "XML_valid_element_namespace_URI", "XML_valid_element_name",
  "XML_aggregate", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-1973)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1269)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    2324,    54, -1973,    38, 20875,   -57,   263,   457,   457, 20875,
     506, -1973, -1973,    30,   331,   442,   376, -1973, 16927, 20875,
   -1973, -1973, -1973, -1973, -1973, -1973, -1973, -1973, -1973, -1973,
   21204,   498,   138,   892,   440,   497, 20875, -1973,   408,   705,
   -1973,   722,   814,  1368,   596,   625, 14271, 14600,   653, -1973,
   -1973, -1973, -1973, -1973, -1973, -1973, -1973, -1973, -1973, -1973,
   -1973, -1973, -1973, -1973, -1973, -1973,   674, -1973, -1973, -1973,
   -1973, -1973, -1973, -1973, -1973, -1973, -1973, -1973, -1973,   926,
     673,   733, -1973, -1973, 20875, -1973,   780, -1973, -1973, -1973,
   -1973, -1973, -1973, -1973, -1973, -1973, -1973, -1973, -1973, -1973,
   -1973, -1973, -1973, -1973, -1973, -1973, -1973, -1973, -1973, -1973,
   -1973, -1973, -1973, -1973, -1973, -1973, -1973, -1973, -1973, -1973,
   -1973, -1973, -1973, -1973, -1973, -1973, -1973, -1973, -1973, -1973,
   -1973, -1973, -1973, -1973, -1973, -1973, -1973, -1973, -1973, -1973,
   -1973, -1973, -1973, -1973, -1973, -1973, -1973, -1973, -1973, -1973,
   -1973, -1973, -1973, -1973, -1973, -1973, -1973, -1973, -1973, -1973,
   -1973, -1973, -1973, -1973, -1973, -1973, -1973, -1973, -1973, -1973,
   -1973, -1973, -1973, -1973, -1973, -1973, -1973, -1973, -1973, -1973,
   -1973, -1973, -1973, -1973, -1973, -1973, -1973, -1973, -1973, 21533,
   -1973,   568, -1973, -1973, -1973,  6960, 20875, -1973,   752,   752,
   -1973, 20875,   -57,  1129, 20875,   609,   999, -1973, -1973, -1973,
   -1973,   813, -1973,   669,   882, 22786, 22786,  2324,  2324, 20875,
    1033, -1973,   780, -1973, -1973, -1973, -1973,   882,   882, -1973,
     781, -1973,   882,   580, -1973,   -98,   694, -1973,   709,   825,
     749, -1973, -1973, -1973, -1973,   847,   873,   481,  1572,  1018,
     940, 18243, 20875,   834,   834,  7338,   782,    95, -1973,   882,
   -1973,  1114,  1117,  1127,   409,   906,  1181,   919, -1973,   923,
    1186, -1973, -1973,   620, -1973, -1973, 22786, -1973,  1023, -1973,
   -1973, -1973,   475,  1002, 20875,  1105, -1973, -1973, 20875, -1973,
   -1973,   922,   925,   931,   952, 20875, 20875,   924,   924, -1973,
     920, -1973, -1973,   975,  1032, -1973, -1973,  1035,  1042, 20875,
   20875,  1074, 20875, 20875, 20875,   557, 20875, 20875,   834,   834,
     834, 20875,   834,   834, -1973, -1973, -1973, -1973,  1089, -1973,
   -1973, 20875,   951,   983,  1047,  1193,  1204,  1204,  1204,  1204,
    1209,   986,  1102,  1106,   952,  1063,  2194,  1062, -1973, -1973,
   -1973,   940,  1345,   -54,   -54,   -54,  1137, -1973, -1973, 21533,
    1280, -1973, 20875,  1178, -1973, 20875,  1469,  1469,  1469,  1337,
     780,  1280,  1369,  1296, -1973, -1973, -1973, -1973, -1973,  1304,
    1315,  1482, -1973, -1973, -1973,  1328,  1328,  1328,  1328,  1328,
   -1973, -1973, -1973, -1973,  1354,  1357,  1405,  1367,  1377,  1403,
    1404,  1406,  1408,  1409,  1412,  1413,  1414,  1421,  3558,  9606,
    1422,  1422, 11118, 11118,  1425,  1426,  1428, -1973, 11118,  1280,
     116,   154,   462,  7716,  1432,  1433,  9606, -1973, -1973,   665,
   18572,  1389, -1973,  1680, -1973, -1973, -1973, -1973, -1973, -1973,
   20875, -1973, -1973, -1973, 15922, -1973, -1973,  1103,  1436, -1973,
   -1973,  1242, -1973, -1973,  1441,  1263, -1973, -1973, -1973, -1973,
   -1973, -1973,  1280,  1280,   -62,  1280,   780, -1973, -1973, -1973,
   -1973, -1973, -1973, -1973, -1973, -1973, -1973, -1973, -1973, -1973,
   -1973, -1973,   491,  1264, -1973,  1326, -1973,  6960, -1973, 21533,
   -1973, 20875, 20875, 20875, 20875, 20875, 20875, 20875, -1973,  1346,
    8094, 16927, 20875,  1303, -1973,  1486,  1487, -1973, -1973,  1033,
    1497,  1502,  1372, -1973, -1973, -1973, -1973, -1973, -1973, -1973,
     100,  1572,   100,  1307, 14929,   485,  1518,  1523,  1526,    27,
     940,  1327,  1551,  1546, -1973,  1277, -1973,  1176,   634,   559,
    1462, 20875, 20875, -1973,   -28, -1973,  1459,  1476,   -37,  1478,
   20875, -1973, -1973, -1973, -1973, -1973, -1973, -1973,  1311, -1973,
   -1973, -1973,  1479,   904, 20875, -1973,    81, 20875,  1383,  1181,
    1342,  1527,  2794, -1973, -1973, -1973, -1973, -1973,  1363, -1973,
   -1973,   871,   924,   924,   924,   924,  1419,  1373,  1481, 21862,
   20875, 20875,   924, -1973, -1973, -1973,   882,  1081, -1973,  1494,
   -1973, -1973, 20875,  1372, -1973, 20875, 20875, 20875, -1973, 20875,
   20875,  1204,   294, -1973,  1422, -1973, 20875,  1245, 20875, 20875,
    9606, 20875, -1973,   780,  1496, -1973,   862, -1973, -1973, -1973,
    1498,  1503, -1973, -1973, -1973, -1973, -1973,  1639, -1973,  1505,
   -1973, -1973, -1973,  1506,  1511,  1073, 20875, -1973, -1973, -1973,
    1512,  1524,  1529,  1532,  1535, 20875, -1973,  9606, -1973, -1973,
    1504,  1504,  1504,    51,  1365,  1397, -1973, -1973, 18901,  1331,
   -1973, -1973, -1973,  1457, -1973,  9606,  9606,  1701,  1522, -1973,
   -1973, -1973, -1973, -1973, 20875,  1978,  1607, 11118, 11118, 11118,
    1483,  1571,   469,  1488,  1736, 11118,   482, 11118,  3558,  1560,
    1189,   826,  1336,   337,  1680,   455, -1973, -1973,  3558,  1963,
    1963, 11118, 11118, 11118,  1015, -1973,   722,  1440,   722,  1440,
   -1973, -1973,  1280,  9606,   -26, -1973,   786,  9606,  9606,  1680,
     629, 15282, 20875, -1973,  1375,  9606, -1973,  9606,  3936,  1355,
    1355,  1566,  1569, 11118, 11118, 11118, 11118,  3936,    62,  1374,
   11118, 11118, 11118, 11118, 11118, 11118, 11118, 11118, 11118, 11118,
   11118, 11118, 11118, 11118, 11118, 11118, 11118, 11118, 11118, 11118,
   11118, 11118, 11118, 11118,  1538,  4314,  6960,  5826, 19230, -1973,
   -1973, -1973, 15611, -1973, -1973, 17256,  1455, -1973,   529, -1973,
   -1973,  1668,  1675, -1973,  1640,  1747, -1973, -1973, -1973,  1392,
   -1973, -1973,  1590,   856, -1973,  1459,   340, -1973, -1973,   341,
   -1973,    57,  1517, -1973, -1973,  1372, -1973, -1973, -1973, -1973,
   -1973, -1973,  -113, -1973, -1973, -1973,   246, -1973,   101, 20875,
   -1973, -1973, -1973, -1973, -1973, -1973,   100,   100, -1973, -1973,
   -1973,  1219,   722,   940, -1973, -1973,  1508,  1480,  1176,  1489,
    1161,  1665,  1493,  1281,  1281, -1973,  1181, 11659,   559, -1973,
   -1973, -1973,  1510,   893, -1973,  7338,  4692, 17585,  7338, -1973,
    1598, -1973,  1661,    67,  1757,  1509,   882, 20875,  1449,  1181,
   -1973, -1973,   342, -1973, -1973,  1180,  1459,  1176,  1495, 11659,
   -1973,   871, -1973, -1973, 20875, 20875, 20875, 20875,  1539,  1514,
   -1973, -1973, 20875,  1534,  1557,   412,  1519, 20875,  1450, -1973,
   -1973,    69, 19559,  1372, -1973,  1372,  1372,  1372, -1973,  1590,
   20875, -1973, -1973, -1973,  1280, -1973,  1280,  1506,  1511,  1281,
   -1973, -1973, -1973,  1459, -1973, -1973,   722, -1973,  1778,   722,
     722,   722, -1973,   976,  1440,  1440, -1973, -1973, -1973, -1973,
   -1973,  1511,  1506,  1516, -1973, -1973, -1973,   722,   722,   722,
     722,   722,  2194,    -3,  1427, -1973,  1693,    30,    30,    30,
   -1973, -1973, -1973,    51,  1303,  9606, -1973,  1622,    33, -1973,
    1624, -1973, 20875,   -46,   261, -1973, -1973,   344, -1973,  1438,
   -1973, -1973, -1973, -1973, -1973, -1973, -1973, -1973, -1973, -1973,
    1687, 20875, 15922,   415, 15922, -1973,   -72, -1973,  1644, 20875,
    1635, 11118,  1442, -1973, -1973, 11118, 20875, -1973,  1664,   415,
   -1973, 11118, -1973,  1707,  1259, -1973, -1973, -1973,  1299,  9606,
   11804, 13924, 12510,  1643,  1521,  1280,  1646,  1280,  1073,   -68,
    9606, -1973,   811,  9606, -1973,  1484,   351,   388,   383,  9606,
   -1973, 15940, 13942, -1973,  1445,  1435, 22191, 22191, 22191,   -24,
      65, 20875,  1397,  1389,  1680, -1973, -1973, -1973,  1533,  1648,
   -1973, -1973,  9606,  9606,  3558,  3558, -1973, 13216, -1973, -1973,
   -1973,  1550,  1650, -1973,  1712, -1973, 15922,  1830,  1830,  1830,
    1830,  1830,  1830,  1830,  1830,  1830,  1830,  1963,  1963,  1963,
    1015,  1039,  1039,  1039,  1039,  1690,  1690,  1690,  1690,  1690,
   -1973,  1458,  9606,  1654,  9606,   413,   102, -1973, -1973,  9606,
    9606,   414, 20875, -1973,  1659, -1973,   118, -1973, -1973, -1973,
   20875, 15282, 20875,  2735, -1973, -1973, -1973, -1973,  9606, -1973,
   20875, -1973, -1973, -1973, -1973, -1973, -1973,  1563,   100,  1720,
    1574,  1720, -1973,    76,    76,  1390,  1749, -1973, -1973, -1973,
   -1973, -1973,  1280, 20875,  1576,  1556,  1561, -1973, -1973, -1973,
    1281,   995,  1181,  1181, -1973, -1973, -1973,  1554,   736,  1196,
     173,  1558,  1202, -1973, -1973,   423,   441,   455, -1973, 16927,
   -1973,  1733,  1513,   499,  1155,    67,  1734,   882, -1973, -1973,
   -1973,  3558,  1582,  1281, -1973, -1973,  1677,  1677,  1677,  1677,
   20875,   142, -1973, -1973,  1838,  1580, 20875,  1619, 17914, -1973,
   -1973,  1528, 20875,  1677,   409, -1973,  1520, -1973, -1973,  1596,
   -1973,  1697,  1515, 11659, -1973, -1973, -1973, -1973,  1372, -1973,
    1699, -1973, -1973,  1700,   460,  1702,  1555, -1973,   463, -1973,
   -1973, -1973, -1973,  1585,  1087,  1703,  1559,  1706,  1708,  1710,
    1715, -1973, -1973, -1973,  1631,  9606,  1717, -1973, -1973, -1973,
   -1973, -1973,  1564,  1459,  1422, 18901,  1397,  7338, -1973, 11659,
   11659, -1973, 20875, 20875, 11118, -1973,   569,  1750, 11118,  1751,
    1752, -1973,  1565, 10362, 15922,   308, -1973,  1587, -1973,    50,
   -1973,  1568,  1787,  1644,  1755,  1774,  1644,  1443,  1765,  1771,
    1680, 11118, 11118, 11118, 11118, -1973,  1633, -1973, -1973, -1973,
   -1973,  9606,   -67, -1973,  1617,  1459, -1973,  9606,  9606, -1973,
    9606,  1680, 22191, 22191, 13942,  1775,  1777,  1779,  1349, 15282,
   -1973, -1973, -1973,  1199,  1874, -1973,  1882,  1886, 20875, -1973,
    1786, -1973, -1973, -1973, 16927, -1973, -1973,  1593,  1621,  1854,
    3558,  1444,  1507,   479,   486,  1280,  3558, -1973,   492, -1973,
     504,  1600, 16269,   511,   512, -1973,  1793,  1618, -1973, 20875,
   -1973,   700,  1601, -1973,  1798,  1606,  1459, -1973,  1704, -1973,
     142, -1973,  1711, -1973, -1973, -1973, -1973, -1973, -1973,  1966,
   -1973,  1280, 20875,  1705,  1718,  1181, -1973,  1181, -1973, -1973,
   20875, 20875, 20875, -1973, -1973, 20875, 20875, 20875,  1888,  1407,
   20875, 20875, -1973, 20875, 20875, 19888, -1973, -1973, -1973,  1637,
   -1973,  1280,  1280,  1509,  1613, -1973, -1973, -1973,  1733,    93,
    1868, -1973,  1280,  1181,  1632,  1714, -1973, -1973, -1973, -1973,
   -1973, -1973,  1713, 20875,   877, -1973, -1973, 16927, 20875, 20875,
     537, -1973, -1973, -1973, -1973, -1973,   869, -1973,  2675,   271,
     409,  1816,  1716,  1721, 20875, 20875,  1753, 20875, -1973, -1973,
   -1973, -1973, -1973,   722, -1973,   722, -1973,   722,  1511, -1973,
   -1973, -1973,   722, -1973, -1973, -1973, -1973,  1279, -1973, -1973,
   20875,    63, -1973, -1973, -1973, -1973, -1973,  1817,  1821, -1973,
    1628, 14254, -1973, -1973, -1973, -1973, -1973, -1973,  9984,  1644,
    1740, 11118, 15922,   542, -1973,  1658, -1973, -1973,  1031, 11118,
    1644, 20875, -1973,  1855,  1856,  1828, 11118,  1644,    45, 11118,
   -1973,  1787, -1973,  1719,  1829, -1973,  1831,  3558,  3558, 13572,
   12160, 14583, 12863, -1973,  1459,  9606, -1973,   829,  1459,  1459,
   -1973, -1973, -1973, -1973, -1973,  1435,  1934, 15282, 15282, -1973,
   -1973,  1837, 20875,   124, 20875,  1839,  1907,  1905,  1841,  9606,
    9606, -1973, -1973, -1973,  1843, -1973, -1973,  1844, -1973, -1973,
   -1973,  1917,  1920, -1973,  9606, 20875, -1973, 11659, -1973, -1973,
   -1973,  1674, -1973, -1973,  1280,  1758, -1973, -1973, -1973, -1973,
    1372,  1372,  1372, -1973,  1738, -1973, -1973, -1973, -1973,  1683,
     725,  1683, -1973, -1973,  1280,  1662,   565, -1973,  1280, -1973,
    1853,  1853,   499,  1788, -1973,  1925, -1973,  1280, 20875,  1666,
   -1973,  1696,   773, -1973,   877, -1973, -1973, -1973, -1973, -1973,
   -1973, -1973, -1973, -1973, -1973, 17914,  1759,  1766,   882, -1973,
   -1973, -1973, -1973,  1086,  1780,  1756, 20875,  1974, -1973,  1825,
   -1973,  1666,  1709, 22700, 11824, 11659,  1881,  1883,  1887, -1973,
    1889, -1973, -1973,   571, -1973, -1973, -1973, -1973, -1973,  1891,
   15922,  1694, -1973,   573, -1973,  1724,  1893, -1973, -1973, -1973,
   10362, 20875,  1791,  1794,  1795,  1796, -1973, -1973,  1898, -1973,
   -1973, -1973, -1973, -1973,   883,  1900, -1973, -1973,   416,  1725,
   -1973, -1973, -1973,   421, -1973,  1911, -1973, -1973,   574,   587,
   11118, -1973, -1973, 11118, -1973, 11118,  1459, -1973, 15282, -1973,
      96, 20875,   602, -1973, 20875,  6204,  9606, -1973, -1973,   645,
     645, -1973, -1973,  9606,  1975,    44,   323, -1973, -1973,  1812,
   -1973, 20875, -1973, -1973, -1973, 20875,  1727, -1973,  1824,   640,
   -1973, -1973,  1280, -1973, -1973, 20875,    67,  1509,  1509,  1280,
     232,  1789, -1973, -1973, -1973,  1790,   882,   882, -1973,  1953,
   -1973,  9606, -1973,  1086, -1973, -1973, -1973, -1973,   881,  1913,
      99, -1973,   615,    92,  1813,  1177,  1971,  1916, -1973, -1973,
     -57,   506,  1728,  1851, 16927,  2101,  5070,  8472,  9606,     0,
   -1973, -1973, -1973, -1973, -1973, -1973, -1973, -1973, -1973, -1973,
   -1973, -1973, -1973, -1973, -1973, -1973,  1776, -1973, -1973, -1973,
   -1973,  1735, -1973, -1973, -1973, -1973, -1973, -1973, 11118, 11118,
   11118, -1973, 10740, -1973, -1973, -1973, -1973,  1991,   105,  1992,
    1994, -1973, -1973, 20875, -1973, -1973, 11118,  1833,  1835,  1936,
     447, -1973, -1973, 14912, 15265, 15594, -1973,   882,  9606, -1973,
     619, -1973,  1938,  1940,  1941,   438,  3180,  1748, -1973,  1459,
    1459,  1754,  9606, -1973, -1973, -1973, -1973,  5448,    86, -1973,
    1800,  1280, -1973, -1973,   810, -1973,   927, -1973,  2005,  9606,
    1760,   639, -1973,  1280,   133,    67, -1973,  1842, -1973, -1973,
      82,   404, -1973,  1840, -1973,  1782, -1973,  1459, -1973, -1973,
    2008,  1952,  1857, 20875, -1973, -1973, -1973,   759,  1954, -1973,
   -1973,  2043,  2045, -1973, -1973,   325,   633,  1177, -1973,  1783,
   -1973,  1815, 20875,  6960, 20875, -1973,  1959, -1973,    78,  1962,
   -1973, -1973,  1459,  9606, -1973,  1021,   332,   313, -1973, 12883,
    9606, -1973, 15922,   646, -1973,  1797, -1973, -1973,  1768, -1973,
   -1973,  1981, -1973, -1973, -1973,  1787, -1973,  1986,  1993, -1973,
    1987, 20875,  2148,   793, -1973, -1973, -1973, -1973, -1973, -1973,
    1459, -1973, -1973, 20217, 20217,  1976, -1973,  6204,  1427,  6582,
    1801,  1799,   -70,  1803, -1973, -1973,  1957,  2084, -1973, -1973,
    8850,  2039,  1979, -1973, -1973, -1973, -1973, -1973,  1280, -1973,
   20875, -1973,  2048, -1973,  1733,   133, 22520, -1973,  1805,  1982,
    1988, -1973,  1280,  1899, 20875,  2028, -1973,  9606, -1973,   882,
     648, -1973, -1973, -1973, -1973,  1637, -1973,  1637,  1637,  1637,
   -1973,  1192,  1995, 13589,   666, 11659,  1895, -1973,  1802,  9606,
   -1973, -1973, -1973,   455,   328, -1973, -1973,  1834,  9606, -1973,
    1067, -1973, 12883,  2049,   -85, -1973, 11118, 20875, -1973, 11118,
   -1973, -1973, -1973, -1973,  2022, -1973, -1973, -1973,  2022, -1973,
    2027, 20875,  2148, -1973, -1973, -1973,  2031, 20875,   676, -1973,
   -1973,   683, 16598, -1973,  1179,   588, -1973,  1996, -1973, -1973,
   -1973, -1973,     5, -1973,  9606,  1869,  1957,  2064,  1901,  1459,
    1906,  9606, -1973, -1973, -1973,  2134,  1733,  1280,  1561,  1181,
    1836,  9606, 20875,  1176,  1280,   882,  2026,   863,  2083, -1973,
     759, 20875, 20875, 20875, 20875, -1973, -1973, -1973,  9606,  1873,
   -1973, -1973, -1973, -1973, -1973, -1973, -1973, -1973, -1973, -1973,
   -1973, 20875, -1973, 20875,   695,  1459,  2029, -1973, 12177,  1892,
     611, -1973,  1876, 11471,  2074,  1896, -1973, -1973, -1973, -1973,
   -1973,  2148, -1973, -1973, -1973, -1973, -1973, -1973, -1973, -1973,
   -1973,   697, -1973, 20217, -1973,  2052,  2054,  2114, 20546, -1973,
     707, -1973, -1973, -1973,  6582,  1871, -1973,  1884, -1973,  1459,
    1485,  1912, -1973,  9228, -1973, -1973,   729,  1459,  2174, -1973,
    2134, -1973, -1973,   722,  1866,  2060,  1459,  2061,  1970, -1973,
    2083,   871, -1973, -1973,   895,  1964, -1973, -1973, -1973, -1973,
   -1973,   875, -1973, 11659, -1973, -1973,  9606, -1973, 12177,  2104,
   -1973, -1973,  1922, -1973,  9606,  1918,  1921, -1973, 12530, -1973,
   -1973, -1973, -1973, 20217, 20217,  2068, -1973, -1973, 16598, -1973,
   -1973, -1973, -1973,  1969, -1973,  2181,  2130,  1960,  1459,  1960,
    9606, -1973,  1923, -1973,  1280,  1718, -1973, -1973,  1280,  1964,
     721, -1973, -1973, -1973, -1973,  1490,  1980,  1984, -1973, -1973,
   13236, -1973,  1459, -1973, 12177, -1973, 12177,   649,  1932, -1973,
    1935,   730,   732, 16598, -1973, 18901,   882, -1973, -1973,  2152,
   -1973, -1973, -1973,  2087, -1973, -1973, -1973, -1973, -1973, -1973,
      74,    74,  2203, -1973,  2205, -1973, -1973,  2131, -1973, -1973,
   20875, -1973, -1973,   738,  1902,   529,  1977,  1181, -1973, -1973,
    2237,    18, -1973, -1973, -1973, 11471, -1973, -1973, -1973, -1973,
   -1973,   741, -1973, -1973, -1973, -1973, -1973, -1973,  1181, -1973
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       0,     0,    18,     0,     0,   589,     0,   503,   503,     0,
       0,   480,    16,     0,     0,    26,     0,    35,     0,     0,
       7,     5,     9,    11,    20,    19,    22,    21,    25,    33,
       0,     0,    98,    34,     0,     0,     0,   481,   535,     0,
       3,     0,    23,    27,     0,     0,     0,     0,     0,    42,
      43,    36,    37,    38,    41,    39,   165,   164,   161,   162,
     163,    45,   166,    40,   471,   470,     0,   479,   477,   478,
     472,   473,   475,   476,   474,   612,   633,   623,   624,   692,
       0,     0,    46,    17,     0,  1031,  1141,  1033,  1034,  1035,
    1050,  1096,  1115,  1053,  1063,  1066,  1087,  1094,  1077,  1081,
    1109,  1055,  1052,  1057,  1086,  1074,  1110,  1112,  1082,  1061,
    1051,  1083,  1089,  1092,  1041,  1062,  1067,  1134,  1136,  1131,
    1130,  1132,  1121,  1126,  1124,  1125,  1123,  1129,  1133,  1128,
    1127,  1122,  1135,  1047,  1071,  1113,  1114,  1118,  1039,  1070,
    1095,  1080,  1085,  1117,  1093,  1049,  1064,  1091,  1079,  1101,
    1072,  1116,  1102,  1054,  1045,  1046,  1043,  1044,  1099,  1106,
    1084,  1098,  1100,  1103,  1107,  1065,  1058,  1040,  1042,  1059,
    1060,  1048,  1068,  1073,  1104,  1075,  1076,  1119,  1078,  1120,
    1069,  1108,  1105,  1038,  1056,  1111,  1088,  1090,  1097,   870,
    1037,   949,  1036,   590,   591,     0,     0,   502,   506,   506,
     483,     0,   589,     0,     0,     0,     0,   848,   846,   847,
     385,     0,   843,   845,   328,     0,     0,     0,     0,  1058,
     556,  1025,  1141,  1027,  1028,  1029,   117,   328,   328,   116,
     112,   118,   328,     0,   122,     0,     0,   102,   104,     0,
     113,   114,    88,  1030,  1024,     0,     0,     0,     0,     0,
     489,     0,     0,    29,    29,     0,   631,     0,   615,   328,
    1137,     0,     0,     0,     0,     0,     0,     0,   322,     0,
       0,   325,   324,     0,   975,     1,     0,  1140,     0,   976,
    1151,    24,     0,     0,     0,     0,   194,   195,     0,   244,
     243,     0,     0,     0,     0,     0,     0,    31,    31,   193,
       0,   159,   160,     0,   340,   337,   336,   344,   338,     0,
       0,   342,     0,     0,     0,     0,     0,     0,    29,    29,
      29,     0,    29,    29,   922,   924,   923,   930,  1109,   928,
     926,     0,   929,   927,  1059,     0,    56,    56,    56,    56,
       0,   955,  1113,  1114,  1118,    31,     0,    49,    50,    51,
       2,   489,     0,   634,   634,   634,   694,    13,    14,   870,
       0,  1032,  1038,     0,   872,     0,  1147,  1143,  1145,  1031,
    1141,  1033,  1034,  1035,   934,   933,   932,   935,   936,     0,
       0,     0,  1021,   946,   947,   855,   855,   855,   855,   855,
     802,   801,   803,   583,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   866,     0,  1042,
    1059,  1060,  1048,     0,     0,     0,     0,   811,   807,   647,
     870,   689,   725,   691,   716,   717,   718,   719,   720,   721,
       0,   722,   791,   790,   723,   762,   808,     0,     0,   804,
     809,   640,   864,   795,     0,   794,   800,   873,   940,   799,
     798,   797,     0,     0,   952,     0,  1141,   942,  1149,   931,
     810,  1175,  1176,  1177,  1178,  1179,  1180,  1181,  1182,  1183,
    1184,   886,   574,     0,   482,   507,   484,     0,   632,   870,
      28,     0,     0,     0,     0,     0,     0,     0,  1170,     0,
       0,     0,     0,   700,   329,     0,     0,    10,    12,   556,
       0,     0,   467,  1026,   119,   120,   111,   121,   106,   107,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     489,     0,     0,     0,   488,   490,   491,   209,   143,     0,
       0,     0,     0,   585,     0,   579,   584,     0,   952,     0,
       0,   619,   621,   622,   620,   613,   618,   617,     0,   552,
     553,   554,     0,   692,     0,   537,   551,     0,     0,     0,
     536,     0,     0,  1153,  1152,  1154,   248,   247,     0,   246,
     245,   171,    31,    31,    31,    31,     0,    82,     0,     0,
       0,     0,    31,   341,   345,   339,   328,     0,   343,     0,
     459,   168,     0,   467,   458,     0,     0,     0,   460,     0,
       0,    56,     0,   925,     0,    55,     0,     0,     0,     0,
       0,     0,  1138,  1141,  1001,  1015,   977,  1016,  1018,  1019,
     990,   993,   985,   986,   988,   989,   987,   996,   998,  1008,
    1012,  1011,   896,   893,   895,     0,     0,   999,  1000,    53,
    1003,   978,   979,   983,  1006,     0,   486,     0,   635,   636,
     637,   637,   637,     0,   697,   596,  1142,   871,     0,   950,
    1148,  1144,  1146,  1032,   943,     0,     0,     0,     0,   850,
     852,   851,   854,   853,     0,     0,     0,     0,     0,     0,
       0,  1218,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   691,     0,   724,     0,   753,   752,     0,   787,
     788,     0,     0,     0,   782,   937,     0,   891,     0,   891,
     887,   888,     0,     0,     0,   969,   971,     0,     0,   754,
       0,     0,     0,   625,   645,     0,   869,     0,     0,   735,
     735,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   796,
     944,   941,     0,   945,  1150,     0,     0,   576,   574,   572,
     504,     0,     0,   485,   647,     0,  1169,  1163,  1164,     0,
    1165,  1168,   462,     0,   841,   815,     0,   844,   845,     0,
     318,     0,    47,     8,     6,   467,   558,   557,   469,   468,
     560,   125,    92,   123,   126,    89,    90,   105,   340,  1058,
     103,   110,   109,   115,    99,   101,     0,     0,   487,   494,
     493,     0,     0,     0,   211,   210,     0,     0,   209,   145,
       0,     0,   180,   889,   889,   190,     0,     0,   169,   174,
     183,    30,     0,     0,   577,     0,     0,     0,     0,   614,
       0,   323,     0,   529,     0,   509,   328,     0,     0,     0,
       4,  1155,     0,   581,   588,   587,   586,   209,     0,     0,
     167,   170,   172,   178,     0,     0,     0,     0,     0,     0,
     197,    32,  1039,    71,    67,   328,     0,     0,     0,   424,
     425,     0,   420,   467,   457,   467,   467,   467,   461,   462,
       0,   331,    58,    61,     0,    63,     0,   893,   895,   889,
      64,    60,    62,    57,   956,  1139,     0,  1017,     0,     0,
       0,     0,   997,     0,   891,   891,   899,   900,   901,   902,
     903,   895,   893,     0,   920,   921,    52,     0,     0,     0,
       0,     0,     0,   710,   693,   707,   638,     0,     0,     0,
     696,   695,   974,     0,   700,     0,   555,     0,   647,   592,
       0,  1023,     0,     0,     0,  1022,   856,     0,   677,   952,
     907,   908,   909,   911,   912,   910,   905,   913,   904,   906,
       0,     0,     0,   762,  1174,  1172,  1255,  1171,  1255,     0,
       0,     0,     0,  1253,  1254,     0,     0,  1235,  1236,   762,
    1252,     0,  1251,   692,     0,   761,   760,   789,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   966,   971,     0,   970,     0,     0,     0,     0,     0,
     756,     0,     0,   657,   648,   649,   656,   662,   662,   949,
     647,     0,   596,   688,   690,   728,   726,   727,   730,     0,
     736,   737,     0,     0,     0,     0,   738,   742,   740,   739,
     741,   729,     0,   745,     0,   757,   778,   763,   764,   769,
     779,   768,   783,   784,   785,   786,   862,   765,   766,   767,
     780,   770,   775,   773,   771,   772,   774,   776,   777,   781,
     868,   882,     0,     0,  1044,     0,   952,   865,   876,     0,
    1044,     0,   813,   793,  1035,   867,   953,   575,   573,   505,
       0,     0,     0,     0,   452,  1162,  1161,   842,     0,   330,
       0,   702,   703,   701,    48,    44,   559,     0,     0,    94,
       0,    94,   108,    94,    94,     0,     0,   501,   500,   495,
     496,   492,     0,     0,     0,     0,   147,   188,   186,   191,
     889,   889,     0,     0,   189,   179,   175,     0,   158,   158,
       0,   158,   158,   580,   882,     0,     0,     0,   616,     0,
     534,   540,     0,     0,     0,   529,     0,   328,   538,   539,
    1156,     0,     0,   889,   176,   173,   328,   328,   328,   328,
       0,     0,    68,    70,     0,  1157,     0,     0,   288,   212,
     254,     0,     0,   328,     0,   427,   429,   426,   428,     0,
     419,     0,   418,     0,   455,    66,   453,   456,   467,    59,
       0,   973,  1020,     0,     0,     0,   973,  1013,     0,  1014,
     897,   898,   918,   917,     0,     0,   973,     0,     0,     0,
       0,    54,   711,   712,   713,     0,     0,   628,   629,   630,
     699,   698,   704,   597,     0,     0,   596,     0,   951,     0,
       0,   805,     0,     0,     0,   806,     0,     0,     0,     0,
       0,  1197,  1189,     0,  1223,  1210,  1220,  1224,  1219,   762,
    1231,  1232,     0,  1255,     0,  1272,  1255,   760,     0,     0,
     751,     0,     0,     0,     0,   892,     0,   938,   894,   939,
     948,     0,     0,   967,     0,   972,   962,     0,     0,   960,
       0,   755,     0,   662,     0,   657,     0,     0,   602,     0,
     607,   608,   609,   602,     0,   603,     0,   605,  1038,   654,
     661,   663,   652,   651,     0,   626,   643,   646,     0,   664,
       0,     0,     0,     0,     0,     0,     0,   744,     0,   880,
       0,   883,     0,     0,     0,   877,     0,   817,   814,     0,
     508,   602,  1166,   464,     0,   465,   816,   319,     0,   124,
       0,    87,     0,    86,    96,    97,   497,   498,   499,     0,
     139,     0,     0,     0,   205,     0,   182,     0,   187,   185,
       0,     0,     0,   157,   130,     0,     0,     0,     0,     0,
       0,     0,   129,     0,     0,   288,   883,   578,   514,   439,
     517,     0,     0,   509,   547,   549,   510,   511,   540,     0,
       0,   582,     0,     0,   224,     0,   215,   217,   332,    84,
      85,    83,     0,     0,    73,  1158,    69,     0,     0,     0,
       0,   263,   259,   261,   264,   262,     0,   265,     0,  1023,
       0,     0,   249,   326,     0,     0,   347,     0,   422,   454,
    1002,   980,   991,     0,   994,     0,  1009,     0,   895,   915,
     919,  1004,     0,   981,   982,   984,  1007,     0,   709,   708,
       0,     0,   627,   595,   593,   561,   594,     0,     0,   678,
     953,     0,  1257,  1256,  1185,  1173,  1186,  1187,     0,  1255,
    1052,     0,  1264,     0,  1259,     0,  1261,  1262,     0,     0,
    1255,     0,  1222,     0,     0,     0,     0,  1255,     0,     0,
    1238,  1245,  1249,     0,     0,  1273,     0,     0,     0,     0,
       0,     0,     0,   890,   968,     0,   961,     0,   963,   964,
     655,   653,   598,   759,   758,   650,     0,     0,     0,   606,
     604,   659,     0,   950,     0,     0,     0,   686,     0,     0,
       0,   746,   747,   743,     0,   885,   884,     0,   879,   878,
     792,     0,   819,   954,     0,     0,   463,     0,    93,    95,
      91,     0,   142,   144,     0,     0,   138,   184,   181,   141,
     467,   467,   467,   135,     0,   132,   133,   131,   137,   238,
       0,   238,   127,   440,     0,   530,     0,   518,     0,   516,
     523,   523,     0,     0,   177,     0,   214,     0,     0,  1160,
    1159,    27,     0,    65,    74,    75,    77,    78,    81,    79,
      80,   213,   320,   289,   253,   288,     0,     0,     0,   287,
     266,   267,   269,   270,     0,   256,     0,     0,   218,     0,
     321,   430,   431,     0,   410,     0,     0,     0,     0,   916,
       0,   715,   714,     0,   706,   705,   957,   958,   849,     0,
    1209,  1194,  1196,  1210,  1207,  1190,     0,  1267,  1266,  1258,
       0,     0,     0,     0,     0,     0,  1211,  1221,     0,  1226,
    1225,  1228,  1229,  1227,   762,     0,  1271,  1270,   762,  1237,
    1239,  1241,  1242,     0,  1246,     0,  1250,  1297,     0,     0,
       0,   859,   860,     0,   861,     0,   965,   959,     0,   599,
     602,     0,     0,   644,   813,     0,     0,   641,   732,   733,
     734,   731,   881,     0,     0,   821,     0,  1167,   466,     0,
     146,     0,   155,   156,   154,     0,     0,   134,     0,     0,
     128,   541,     0,   548,   550,     0,   529,   509,   509,     0,
       0,   240,    72,    76,   260,  1023,     0,     0,   314,     0,
     284,     0,   268,   271,   272,   277,   278,   279,     0,     0,
       0,   255,     0,     0,     0,     0,   444,     0,   346,   417,
     589,  1055,   480,     0,     0,  1049,     0,     0,     0,   354,
     366,   367,   360,   361,   362,   365,   363,   349,   351,   368,
     379,   378,   383,   382,   381,   380,     0,   364,   359,   358,
     369,     0,   421,   992,   995,  1010,  1005,   639,     0,     0,
       0,  1206,     0,  1188,  1260,  1263,  1265,     0,     0,     0,
       0,  1217,  1230,     0,  1243,  1269,     0,     0,     0,     0,
       0,   748,   749,     0,     0,     0,   601,     0,     0,   600,
       0,   660,     0,     0,     0,     0,     0,   665,   666,   668,
     687,   818,     0,   823,   824,   825,   812,     0,     0,   569,
     571,     0,   206,   136,     0,   151,     0,   149,     0,     0,
     531,     0,   525,   527,   542,   529,   515,   147,   220,   219,
       0,   209,   216,     0,   315,     0,   280,   281,   273,   309,
       0,     0,     0,     0,   310,   282,   313,   288,     0,   258,
     192,     0,     0,   252,   327,   441,   441,   432,   433,     0,
     423,   448,     0,     0,     0,   384,     0,   387,     0,  1058,
     392,   391,   393,     0,   401,   403,     0,     0,   354,   410,
       0,   411,  1204,     0,  1199,  1202,  1195,  1208,  1191,  1193,
    1212,     0,  1215,  1214,  1213,  1268,  1240,     0,     0,  1234,
       0,     0,     0,  1286,  1275,  1276,   857,   858,   863,   611,
     610,   658,   642,     0,     0,     0,   672,     0,   820,     0,
       0,     0,     0,   836,   826,   827,   562,     0,   570,   140,
       0,     0,     0,   239,   153,   152,   150,   148,     0,   524,
       0,   528,     0,   543,   540,   542,     0,   207,   199,     0,
       0,   225,     0,     0,     0,     0,   308,     0,   311,   328,
       0,   275,   257,   250,   251,   439,   442,   439,   439,   439,
     434,     0,     0,   410,     0,     0,     0,   348,     0,   388,
     334,   350,   335,     0,     0,   354,   402,     0,     0,   398,
     403,   354,   410,     0,     0,  1198,     0,     0,  1201,     0,
    1216,  1244,  1247,  1248,  1281,  1285,  1284,  1280,  1281,  1279,
       0,     0,     0,  1274,  1287,  1288,  1290,     0,     0,   673,
     676,     0,     0,   667,     0,     0,   831,     0,   832,   830,
     828,   829,     0,   822,     0,     0,   562,     0,     0,   227,
       0,     0,   532,   526,   544,   545,   540,  1100,   147,     0,
     201,     0,     0,   209,     0,   328,   285,     0,   306,   274,
     288,     0,     0,     0,     0,   446,   447,   445,     0,   481,
     374,   375,   372,   373,   450,   376,   443,   371,   370,   377,
     416,     0,   414,     0,     0,   389,     0,   354,   404,     0,
       0,   399,     0,   406,     0,   355,   354,  1200,  1205,  1203,
    1192,     0,  1278,  1277,  1293,  1296,  1292,  1295,  1294,  1289,
    1291,     0,   669,     0,   670,     0,     0,     0,     0,   681,
       0,   679,   834,   835,     0,     0,   838,     0,   839,   563,
       0,     0,   228,     0,   237,   231,     0,   226,     0,   513,
     545,   208,   200,     0,   203,     0,   221,     0,     0,   242,
     306,     0,   283,   317,   302,   297,   276,   438,   436,   437,
     435,     0,   356,     0,   333,   386,     0,   394,   400,     0,
     396,   354,     0,   354,     0,     0,   355,   352,   410,  1283,
    1282,   675,   674,     0,     0,     0,   685,   671,     0,   833,
     840,   837,   565,     0,   567,     0,     0,   233,   229,   233,
       0,   546,   519,   202,     0,   205,   223,   222,     0,   297,
       0,   304,   305,   303,   307,     0,   298,   299,   312,   449,
     410,   415,   390,   355,   397,   395,   407,     0,     0,   353,
       0,     0,     0,     0,   680,     0,   328,   568,   230,     0,
     236,   235,   232,     0,   512,   204,   198,   241,   316,   286,
       0,     0,     0,   301,     0,   300,   451,     0,   354,   405,
     412,   682,   683,     0,   564,   574,     0,     0,   291,   292,
       0,     0,   296,   295,   357,   406,   409,   413,   684,   566,
     234,     0,   521,   290,   293,   294,   408,   520,     0,   522
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1973,  1348, -1973, -1973, -1973, -1973, -1973,  2238,    14, -1973,
   -1973, -1037, -1973,   812,  -111,  -972, -1973, -1973,   754, -1973,
      21,  -282, -1973,  -215,    25,   295, -1973,  1065, -1973, -1973,
   -1973,   635, -1973,   908,     3,  2051, -1973, -1973,    70,    10,
   -1973, -1973,  2053, -1973,  1781, -1973, -1973, -1973,  1784,  -433,
    1154,    72, -1973, -1973, -1812, -1973, -1973,   121,   104, -1973,
   -1973,    64, -1973,  -882,  1453,  -452, -1973, -1973, -1973, -1973,
   -1973, -1973,    12, -1973,  -832,  2256, -1973, -1973, -1973, -1973,
      24, -1973, -1973, -1973,    19, -1973,   696, -1973, -1973, -1973,
       2, -1973, -1973, -1973,   890,   661, -1973, -1973, -1973, -1973,
   -1973, -1973, -1720, -1973,   417, -1973, -1973, -1973, -1973, -1154,
     -23,    15,    23,    29, -1973,    83, -1973, -1973, -1973, -1088,
   -1973, -1973,  -242,  -470, -1973,  -208,  -478, -1973, -1973, -1973,
   -1973,     8, -1973, -1973, -1973, -1901, -1973, -1615,    20, -1972,
   -1973,   299, -1973, -1973, -1973, -1973, -1973, -1973,   252, -1973,
     368, -1973,   254, -1973,   -29, -1973, -1973, -1973, -1973, -1973,
   -1973, -1973, -1973, -1973, -1973, -1973, -1973,   390,  -910,   392,
   -1973, -1973, -1973, -1973, -1973,  1818,   115,  1420,   743,  -534,
      35,    39, -1973, -1973,  -145, -1973,  1500, -1973,  2333,  2149,
   -1973, -1345, -1973, -1973, -1973, -1973,   716, -1973,   320, -1165,
   -1973, -1973, -1400,   316,   123, -1256,   928,  1804,  2097,  1846,
   -1973,  2099,   231, -1973, -1973,   459, -1973,  2105,  2107,  -780,
   -1973,  1499, -1018, -1973,  -819,  -549,  -200,    40,  1091,  -931,
    -960,  1025, -1973, -1973, -1973,   125, -1973,  1819, -1973, -1973,
      17,   152,   141,  1217,   912,  -476,  1312,   799, -1973, -1973,
    1396, -1973,  -702,  -957,  -955, -1973, -1973,   369, -1835, -1854,
    -666,    55,   103, -1973,   466,  1642,  1359, -1973, -1973,  1410,
   -1973,   488,  1118, -1973, -1973, -1973,  -348,  1641, -1973, -1973,
    1647, -1973,   592, -1973, -1973, -1973, -1973, -1973,  1649, -1973,
    1530,  -345, -1973,  1149, -1973,  -659,  -616,   642, -1973,  -698,
   -1973, -1973, -1973, -1973, -1973,   493,   175, -1973, -1973, -1973,
     -11,     9,  -457, -1973,  1056, -1973, -1973,  1615,  -217, -1973,
   -1973, -1973,  -778,  -490,  -557,  -607, -1973,  -644, -1973, -1973,
   -1973, -1973, -1973,  1361, -1973,  2346, -1973, -1973, -1973,  1785,
   -1973,   132,  -594,   -13, -1973, -1973, -1973,  1362, -1973,  1671,
   -1973,  1364,   357,  1545,  -253,  -281,  -292, -1973,  -315, -1973,
   -1973,  -312, -1160,    22, -1973, -1973, -1973,    -4, -1973,  -593,
    -296,   -18,  -159, -1973, -1973,  1084,   343, -1973, -1973, -1973,
   -1973, -1973, -1973, -1973, -1973, -1973,  -649, -1973, -1973, -1973,
   -1973, -1973, -1973, -1973, -1973, -1973,   551, -1973,   319, -1973,
   -1973, -1973, -1644, -1973,   561,   719, -1973, -1973, -1973, -1973,
     884, -1973, -1973, -1973, -1973, -1973, -1973, -1973, -1973, -1973,
   -1973, -1973, -1973, -1973,   548, -1973, -1973, -1973, -1973, -1973,
   -1973, -1973,  1722,  -906,   897, -1973,   717, -1973,   899, -1973,
   -1973,   436, -1188, -1973, -1973, -1973, -1973, -1973, -1925,   324,
   -1973, -1973, -1973, -1973, -1973, -1973,   317, -1973, -1973, -1973,
   -1973
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    39,   276,   216,   215,   217,   218,    40,    41,   282,
      42,    43,    44,   541,   590,    45,    46,    47,    48,  1145,
    1820,   346,   347,   616,  1821,  1822,   903,  1212,  1215,  1643,
    1644,  1645,   900,  1451,  1823,   235,  1151,  1149,  1391,  1824,
     247,   248,   236,   237,   238,   830,   239,   240,   241,   822,
     823,  1825,   849,  1166,  1404,  1422,  1414,  1415,  1826,    56,
     890,   891,   858,   892,   859,   893,    57,   300,   301,  2140,
    2234,  2295,  1606,  2038,   846,   302,  1920,  2235,  2041,  1636,
    2225,  2128,  2287,  2226,  2330,  2023,  1767,  1922,   303,  1668,
    1219,  1220,  1801,  1460,  1461,  1462,  1662,  1463,  1792,  1793,
    1464,  2050,  1794,  1795,  1926,  1796,  1797,  2242,  1465,  1798,
    2362,  2306,  2307,  2308,  2304,  2245,  1935,  1659,  1936,   809,
    1467,    58,   267,   268,  1670,  1221,   504,   335,    59,  2067,
    2071,   323,  1674,    60,  1827,  1969,  2310,  2259,  2164,  1829,
    1830,  1831,  1955,  1956,  2174,  1832,  1961,  1833,  2079,  2080,
    1964,  1965,  2077,  1834,  2265,  1835,  1836,  2366,  2064,  1808,
    1231,  1232,    62,   911,  1229,  1806,  1947,  1948,  1624,  2057,
    1950,  1951,  2157,  2063,  2166,   498,  1837,  1134,  1384,   820,
    1838,  1839,    66,    67,   534,   535,   536,  1159,   198,   484,
     793,  1195,    68,    69,  2334,  2371,  1776,  1911,  1912,  1191,
    1192,   269,  1430,  2034,  2229,  1433,  1434,   270,    70,   512,
      71,    72,  2125,  2284,  2327,  1899,  1900,    73,    74,   789,
     256,   544,   882,   428,   545,   883,   195,   978,   979,   976,
    1053,  1346,  1570,  1347,  1879,   271,   257,   258,   555,    76,
    1840,   272,    79,   660,   967,   429,   733,  1356,  1357,  1062,
     734,  1054,  1338,  1351,  1352,  1577,  1887,  1888,  2108,  2109,
    2201,  2210,  2211,  1747,   805,   431,   356,   664,   974,   812,
    1502,   964,   965,  1264,  1498,   432,   433,  1069,   434,   435,
    1072,   436,  1076,   437,   438,   703,   439,   730,   440,   441,
    1056,   442,   443,   444,   779,   445,   446,  1376,  1377,   806,
    1592,  1755,  1896,  1897,  2013,  2116,  2117,  2015,  2118,  2123,
    1057,   547,   212,   449,   679,   450,   451,   452,   363,   453,
     454,   455,   722,  1035,   717,   719,   647,   952,   999,  1000,
     953,  1490,   954,   955,   648,   456,   337,   338,   339,   457,
     458,  1058,   459,   349,   460,   461,  1048,  1041,  1042,   725,
     726,  1045,  1240,   971,   273,   278,  1385,  1248,   462,   651,
     652,   463,   980,   824,   243,   244,   190,   548,   192,   274,
     465,  1241,   361,   466,   467,   468,   469,    80,   575,    81,
     280,  1454,  1455,  1640,    82,   499,  1005,  1006,  1007,   470,
     471,   472,   473,   474,  1519,  1292,  1691,  1973,  1974,  2088,
    1975,  2189,  1692,  1693,  1694,  1530,  1706,   475,  1011,  1295,
    1296,  1297,  1532,  1710,   476,  1535,   477,  1301,  1537,   478,
    1018,  1303,  1539,  1719,  1720,  1721,  1722,  1723,  1869,   479,
     480,  1021,  1015,  1287,  1012,  1523,  1524,  1856,  1525,  1526,
    1527,  1864,  1865,  1544,  1545,  1993,  1994,  2098,  2099,  2192,
    2270,  1995,  2096,  2103,  2104,  2199,  2105,  2106,  2198,  2196,
     481
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     191,   574,   487,    52,   788,   200,   503,   210,  1128,  1205,
      53,   794,   787,   565,   213,   191,  1164,    77,   987,   514,
     515,    49,   562,   279,   517,    50,   191,   211,  1003,  1055,
    1438,   650,   259,   340,   653,    64,  1019,   945,  1629,    65,
    1008,   998,   341,   341,   807,   234,  1183,   970,  1023,   612,
     654,   558,   312,   242,   649,  1202,  1363,  1364,  1468,  1828,
     702,   704,   260,   513,  1466,   706,   707,  2082,   260,   914,
     972,  1141,    54,  1928,   277,  1172,  1173,  1115,   729,  1121,
     191,   366,   367,  1190,   366,   367,   944,   860,  1627,   826,
     988,  2165,  1335,  -481,  2215,  1286,   366,   367,  2039,  1349,
    1289,   202,  1290,  1353,    55,  2037,   221,   222,   223,   224,
     225,   735,  1877,  1304,  1540,    63,  2358,  2359,  -845,  -893,
    -893,  2216,   617,   618,   619,    75,   735,   193,   735,   735,
     658,  1359,   261,   262,   263,  1893,   189,  2374,  1225,  1226,
    1533,  1227,   665,  -845,  -100,  -100,  -100,  -100,  -100,   837,
     735,   214,    78,   864,   203,   731,  -845,  -895,  -895,  2016,
      84,  1941,   220,  2360,     3,     4,     5,     6,  1185,  2111,
     735,  1340,  1341,  1342,  2178,  1343,  1344,  2197,  1345,  1716,
    2183,  1083,  1942,  1631,   447,   364,   589,   731,  1938,  1147,
     977,   464,   191,   735,  1981,  1142,    83,   486,  1390,   520,
     191,  1534,  1449,  1717,   448,  1976,   656,  1450,  1979,   194,
      13,   673,   659,   736,   497,   191,   359,  2051,    52,    52,
      52,    52,  2032, -1047,  1982,    53,    53,    53,    53,  1037,
    1262,  1263,    77,    77,    77,    77,    49,    49,    49,    49,
      50,    50,    50,    50,  1084,  1418,  2033,   538,   191,  2186,
      64,    64,    64,    64,    65,    65,    65,    65,  2209,  1321,
    1555,   234,  1148,   972,   279,  1468,  2269,  1419,  2017,   922,
     242,  1466,   795,  1432,   556,    13,  2258,   521,  1939,    52,
     578,  1146,  -845,  2375,   191,  2268,    53,    54,    54,    54,
      54,   191,   587,    77,  2121,    51,   716,    49,  -845,    61,
    1040,    50,  1279,  1288,  -845,   191,   191,   784,   191,   600,
     191,    64,   191,   604,   782,    65,   878,   191,   787,    55,
      55,    55,    55,   602,    14,   807,  2231,   341,   482,    35,
      63,    63,    63,    63,   718,  1968,   489,  1228,  2165,   867,
      75,    75,    75,    75,  1252,  1505,   593,   865,    54,  2272,
     702,   509,  1354,  1724,  2083,   364,  1299,  1270,   667,  1943,
    2314,   669,  2316,  2040,  2361,  1639,  2217,    78,    78,    78,
      78,  2218,  1305,   962,  1335,  1560,  1778,  1878,  1561,  1234,
      55,  1235,  1236,  1237,   539,   838,  1671,   821,   908,  1064,
    1068,    63,  1405,  1407,    35,  1253,   920,  1541, -1047,  1081,
    1546,    75,   521,  1153,  1154,   563,   860,  -533,  1275,   557,
     807,  1894,   245,  1895,  1368,   246,  1370,  1641,  -893,   260,
     581,  1373,  1374,   873,  2209,  1443,   364,   586,    78,  1381,
    2246,   427,  1915,  1916,  1630,  -551,   191,   427,  2321,  2322,
     646,   596,   597,   427,   599,  2190,   601,  2365,   603,  2070,
    1060,  1148,  -318,   608,  1250,  1251,  -895,   735,  1506,   261,
     262,   263,  1420,  2042,   935,  -889,  -889,  2184,  1421,  2209,
     550,   894,   895,   896,   897,   921,   447, -1047,  1372,   202,
     202,   907,  1642,   464,  1742,   364,   277,   191,   797,   191,
     799,   191,   191,   191,  1379,  1468,   448,   808,   810,   251,
     982,  1466,   366,   367,   221,   222,   223,   224,   225,   735,
      51,    51,    51,    51,    61,    61,    61,    61,  1028,   735,
     191,  1137,  1139,  1200,   735,  1281,   202,  1538,   735,  1728,
    1729,  1918,   497,   699,  1217, -1268,  1990,   862,   191,   234,
    1867,   196,   650,   825,   197,   653,   259,   735,  1150,   700,
     226,   227,   228,   229,   226,   227,   228,   229,  1143,  2005,
     191,   654,   202,   191,  1329,  1175,   252,   226,   227,   228,
     229,    51,   749,  1664,   650,    61, -1268,   653,  1802,  1408,
    1409,  1868,  1286, -1268,   735,   904,   191,   906,   264,   264,
    1528,   201,  1218,   654,  1371,  1375, -1255,  1204,   191,  1919,
     202,   191,   191,   191,  1426,   191,   191,  1641,  1020,   204,
    1489,  1914,   923,  1696,   931,   932,  1991,   934,   684,  1992,
    2055,  1148,  1427,   796,  1708,   798,  1199,   800,   801,   802,
    1013,  1715,  1014,   956,  2135,    13,  1280,  1565,   205,  1515,
    2081,  1482,   341,  1013,  1486,  1014,  -318,   650,   850,  1898,
     653,   341,  1441,  1880,   265,  2177,   832,   206,  2078,   573,
    1581,   430,   720,   721,   981,   230,   654,  1582,  1196,   646,
    1261,   785,  1642,  1585,   863,   844,   845,   255,  2056,  1432,
     989,  1310,   230,  1529,   313,  1586,   851,   852,  1509,   853,
     854,   855,  1588,  1589,   856,  1512,   872,   884,  1033,   876,
    1036,  1331,   518,   666,  1479,   275,  1332,    35,    35,    13,
      36,    36,  1029,   885,   674,  1138,  1140,  1201,  1654,  1282,
    1271,   546,   905,  1699,  1361,  1362,  1327,  1059,   341,   253,
     266,   304,  1513,   277,   913,   254,  2230,   915,   916,   917,
     211,   918,   919,    26,    27,  1906,  1773,    26,    27,   231,
    2035,   314,  1847,   231,    35,  1871,   786,    36,  1330,  1907,
      26,    27,   715,  1328,  1863,   447,   231,   351,  1872,   232,
     304,  1116,   464,   232,  1123,  1340,  1341,  1342,  1126,  1343,
    1344,   810,  1345,  1881,   735,   448,   232,   731,  1138,  1138,
      35, -1268,  2065,    36,   786,   350,  1940,   977,  1138,   304,
    2001,   305,   306,   307,   308,   780,   781,   735,   783,   315,
     850,  1578,  1607,   888,  1608,   357,   865,  1584,   650,   233,
    2029,   653,  1908,   699,  1160,   191,  1406,  2085,    35,  2149,
     699,    36,   313,   699,  1683,  1483,   233,   654,  1487,  1024,
     305,   306,   307,   308,   747,   735,   700,  2170,   851,   700,
    1634,   853,   854,   855,  1201,  1528,   856,  2202,   519,   366,
     367,  1201,  1116,  1126,  2204,  1739,  1740,  1138,   316,   305,
     306,   307,   308,   191,   701,   358,  2255,  1714,  2271,  1138,
    1718,  1679,  2100,   937,   938,  1684,  1138,  1138,  2277,   724,
     191,   191,   191,   191,   360,  1789,   309,   807,  1213,   314,
    1790,   317,  2339,   191,   847,  1909,   988,   857,  1233,   875,
    2289,  2351,  1655,  2352,   318,   807,  1239,  1700,   650,  2368,
     319,   653,  2377,  1246,   748,   320,   203,   311,  2058,  1503,
     366,   367,  2020,  2021,  2301,  2302,   848,   654,  2261,  1256,
    1628,  1478,   569,   732,   365,   310,  1282,   304,  1850,  1201,
     483,  2213,  2121,   430,   249,  2101,   490,   315,  2102,   570,
     850,  1152,  1201,   888,   650,   650,   311,   653,   653,   505,
     506,   321,  2303,  1411,   322,  1135,  2348,  1140,  1278,   366,
     367,  1594,  1473,   654,   654,   250,  2056,  1507,  1508,  1440,
    1140,   522,  1768,   500,  1140,   311,  1459,   191,   851,  2022,
    1929,   853,   854,   855,  1049,  1291,   856,  1027,  1050,  1197,
    1737,  2253,  1300,   352,  2030,  1769,   316,   305,   306,   307,
     308,  2086,   735,  2150,  1791,   735,  1206,  1207,  1208,  1209,
     571,  1412,  1413,  1247,   531,   352,  1876,   532,   886,  1223,
    1333,  2171,   939,   533,  2243,   501,  2024,   213,  1059,   317,
   -1233,  2203,  1350,  1350,  1350,  1891,  2309,  1358,  2203,   735,
     211,   211,   502,  1930, -1233,  1038,   542,   516,   319,   889,
    2256,   735,  1282,   320,    24,    25,  1762,  1763,  1764,   353,
     354,   355,  2278, -1058,   523,   488,   933, -1058, -1058,  2043,
   -1058, -1058, -1058, -1058, -1058, -1058, -1058, -1058, -1058, -1058,
   -1058,   353,   354,   355,  2290,  2203,   524,  2203,  1267,  1268,
    1269,   530,   723,  2278,  1043,    15,  2378,  1931,  1378,   321,
   -1058, -1058,   322,   963,   525,   491,  1380,  1059,  1382,   526,
     605,   606,   607,  1285,   609,   610,  1387,  1040,  1656,  1043,
     211,   983,   984,   311,    29,  2151,  1136,  2152,  2153,  2154,
    1702,    31,    32,   650,  1657,   527,   653,   549,   750,  1400,
    1178,   510,   511,  1179,   701,   540,  1932,  1658,   559,  1933,
      34,   560,   654,   304,   701,   705,  1663,  1336,  1428,  1934,
    1788,   561,   750,  1180,   564,   213,  1181,  1182,  1703,  1039,
    1704,  1705,   260,  1046,  1047,   720,   721,   566,   211,   884,
     884,   567,  1676,   572,  1337,  -288,  1448,  1718,  1444,  1445,
    1446,  1447,  1213,   568,  1469,   885,   885,   582,   191,   889,
     583,  1393,  1789,  1394,  1395,  1472,   584,  1790,  1665,   576,
     577,  1749,  1750,   765,   766,   767,   768,   769,   770,   771,
     772,   773,   430,   305,   306,   307,   308,   585,   366,   367,
     368,   622,   623,   924,   625,   588,   374,   375,   376,   377,
     378,   769,   770,   771,   772,   773,   591,   674,  -288,   715,
     592,   981,   381,   382,  1340,  1341,  1342,   593,   989,  1510,
     594,  1345,   650,   366,   367,   653,  1249,   595,   492,   383,
     384,  1167,  1168,  1169,   493,   494,  1243,  1244,  1245,   495,
    1417,   654,  1423,  1425,   353,   354,   355,   925,  1923,  1924,
     488,  2238,  1336,  1155,  1255,  1257,  1258,  1259,  1260,   598,
    1156,  1157,  -288,  1459,   611,  1158,   884, -1106,  1350,  1350,
    1059,   546,   579,   580,   546,  1059,  1078,  1079,  1080,  1337,
   -1138, -1138,   885,   211,  1571,   496,  1960,  1963,   211,  2075,
    1573,  1791,   790,   791,  1471,   353,   354,   355,   650, -1107,
     650,   653,   621,   653,   353,   354,   355,   613,  1126,   311,
    1026,  -288, -1015, -1015,  -288,  1593,   614,   654,  1317,   654,
    1319,  1809,   946,  1842,  -288,   283,   947,   615,   948,   949,
     950,   951,   620,  2078,   588,  2075,   946,  -244,  1603,  1999,
     947,  -243,   948,   949,   950,  1488,  1609,  1610,   191,  2110,
    2110,  1612,  1613,  1614,   818,   819,  1618,   191,  1205,  1620,
     191,   981,   839,   840,  1340,  1341,  1342,   284,  1343,  1344,
     285,  1345,   909,   910,   353,   354,   355,   655, -1058, -1058,
    1307,  1273,   680,   681,   682,   683,  1651,   844,   845,   810,
     670,   671,   672,   213,   191,  1653,   657,  1646,   663,  1336,
   -1139, -1139,  1070,  1071,  1647,   279,   211,  1677,   668,  1678,
     810,   191,   366,  1675,  1680,   563,  -874,  2066,   286,   774,
     287,   720,   721,  1685,   675,   884,  1337,  1308,  1309,  1396,
    1397,   884,  1413,  1416,   288,   676,   989,  1424,  1413,  1436,
    1437,   885,  1616,  1617,   677,  1399,  1322,   885,   678,  1325,
    1340,  1341,  1342,   988,  1343,  1344,  -602,  1345,  2110,   738,
    1681,  1682,   739,   740,   741,   742,  1648,  1709,   743,   744,
     745,   746,  1945,  1946,   684,   747,  1435,   685,   702,   686,
     886,   886,  2212,  2120,  1611,  2155,  2156,   687,   926,   927,
     928,   929,  -632,  1619,  2282,  2283,  1621,   688,  1649,  2340,
    2341,   709,   710,  1059,  1059,   507,   508,   714,   810,  1650,
    1358,   661,   662,   968,   969,  2369,   211,   211,   221,   222,
     223,   224,   225,   689,   690,  -632,   691,   737,   692,   693,
    1652,  1757,   694,   695,   696,   289,   290,   291,   292,   293,
     294,   697,   705,  2176,  1386,   711,   712,  1672,   713,  2110,
    1953,   295,   727,   728,   988,   748,   775,   776,  -632,  -632,
    -632,   777,   778,   792,  -632,   803,   811,   738,   813,   814,
     739,   740,   741,   742,  1782,   816,   743,   744,   745,   746,
     817,   834,  1579,   747,   296,   233,   835,  1646,   836,   841,
     842,  1785,   843,   861,  1647,   735,   866,   297,   868,   870,
     871,   877,   810,   298,   879,   887,   299,   886,   898,   880,
    1841,   901,   884,   884,   912,   899,   936,   942,   940,  2110,
    2110,  -632,   966,   941,  2110,   943,   716,   973,   885,   885,
     738,   718,   957,   739,   740,   741,   742,  1855,   975,   743,
     744,   745,   746,   986,   958,  1580,   747,   982,  1583,   959,
    -632,  -750,   960,   283,  -196,   961,  1648,  -632,  -632,   739,
     740,   741,   742,   748,   985,   743,   744,   745,   746,  2110,
    1001,   963,   747,  1009,  1059,  1010,  -632,   810,  1016,  1017,
    1378,  1025,  1034,   546,  1602,  1061,  1074,   211,  1649,  1075,
     650,  1110,   426,   653,  1127,   284,  1129,  1902,   285,  1650,
    1130,  1903,   731,  1131,  -632,  -632,  -632,  -632,  1132,   654,
    1133,  1913,  1144,  2172,  1625,  1435,  1170,  1163,  1187,  1165,
    1177,  1162,  1435,  1189,  1193,  1633,   748,  1554,  1198,  1210,
    1194,  1211,  1216,  1557,  1558,  1171,  1559,  1203,  1224,  1214,
    1222,  1242,  1265,   210,  1266,  1274,   286,  1277,   287,  1284,
    1059,  1286,   748,  1254,  1283,  1293,   352,  1298,  -632,  1302,
    1339,  1326,   288,   211,  1315,  1316,   886,  1318,  1360,   748,
    1366,  1367,   886,   750,  -841,  1369,  1002,  1004,  1004,  -875,
    1388,  2148,  1390,  1398,  1002,  1402,  1004,   977,  1392,  1401,
    1403,  1410,  1429,  1431,  1413,  1442,  1439,  1218,  1452,  1985,
    1030,  1031,  1032,   738,  1453,  1457,   739,   740,   741,   742,
    1474,  1497,   743,   744,   745,   746,  1470,  1475,  1476,   747,
    1480,  1481,  -914,  1484,  1491,   787,  2232,  1493,  1501,  1494,
    1477,  1495,  1077,  1077,  1077,  1077,  1496,  1500,  1538,  1086,
    1087,  1088,  1089,  1090,  1091,  1092,  1093,  1094,  1095,  1096,
    1097,  1098,  1099,  1100,  1101,  1102,  1103,  1104,  1105,  1106,
    1107,  1108,  1109,   289,   290,   291,   292,   293,   294,   191,
    1485,  1514,  1516,  1517,  1492,  1531,  1542,  2240,   650,   295,
    1518,   653,   447,  1536,  1543,  1547,  1957,  1760,   981,   464,
    2068,  1548,  2293,  1553,  1556,  1567,  1562,   654,  1563,   748,
    1564,  2311,   448,  1568,  1569,  1841,  1572,  1771,  1574,  1575,
    1576,  1774,   296,   750,  1590,  1435,  -842,  1595,  1591,  1596,
    1781,  1597,  1601,  1605,  1615,  1623,  1598,  2095,  1628,  1604,
    1632,   298,  1635,  1600,   299,  1637,  1666,  1667,  1686,   989,
     989,  1673,  1687,  1638,  1379,  1697,  1701,  1711,  1712,  1713,
    1726,   699,  1727,   886,   886,  1738,  1725,  1741,  1745,  1744,
    1746,  1736,  1748,  1669,  1751,  1752,  1913,   700,  1753,  1754,
    1759,  1766,  2138,  1775,  1761,  1765,  1780,  1772,  1779,  1786,
     191,  1140,  -196,   761,   762,   763,  1787,   764,   765,   766,
     767,   768,   769,   770,   771,   772,   773,  1803,  1800,  1841,
    1756,  1804,  1843,  1799,  1844,  2049,  2162,  1805,  1845,  1849,
    1846,  1848,  1857,  2163,  1853,  1858,  1859,  1860,  1841,  1861,
    2169,  1862,  1870,  2188,  2160,  1901,  1892,  1904,  2161,  1905,
    1925,  1921,  1664,  1937,  1949,  1944,  1952,  2195,  2167,  1852,
    1866,  1954,  2168,   989,  2372, -1057,   750,  1958,   989,  1970,
    1980,  1983,  1971,  1984,  1987,  1910,  1988,  1989,  2355,  2002,
    2003,  2004,  1917,  2007,  2026,  2379,  1898,  2046,  2044,  1138,
    2045,  2036,  2047,  2052,  2053,  2028,  2054,  2048,  2237,  2069,
    2061,  2062,  2073,  2089,  2090,  2087,  2092,  2247,  2248,  2249,
    2250,  2097,  2094,  2093,  2119,  2124,  2112,  2126,  2130,  2131,
    1294,  2134,  2141,  2120,  1002,  2122,  2146,   981,  2142,  2254,
    1004,  2179,  2144,   732,  1841,  2158,  2145,  2139,  2173,  1841,
     764,   765,   766,   767,   768,   769,   770,   771,   772,   773,
    2191,  2185,  2194,  2101,  2214,  2222,  2220,  2228,  2223,   989,
     622,   623,   624,   625,   989,  2224,  2241,  2244,  2252,  2233,
    2257,  1889,  1890,  2262,   626,   279,  2266,  2260,   627,   628,
     629,   381,   382,   630,   631,   632,   633,   634,   635,   636,
     637,   638,  2273,  2267,  2274,  2275,  2280,  2281,  2291,  2285,
    2294,  2296,  2297,  2298,  2019,  2305,  2313,  2315,  2323,  2025,
     639,   640,   641,  2326,  1841,  2318,  2031,  1927,  2319,  2325,
    2328,  2342,  2329,  2349,  1841,  2344,  2333,  2357,  2350,   989,
     989,  2356,  2340,  2364,   989,  2341,  2370,  1275,  2373,  1783,
     281,  1456,  1962,  1966,  1967,   990,   991,   946,   992,   993,
     994,   947,   995,   948,   949,   950,   996,   997,  1599,   529,
     528,  2072,  1389,   348,   827,  2300,  1841,  2336,  2331,   833,
    1841,  1176,  1841,  2162,  2332,  1622,  1784,  1770,  2363,   989,
    2163,   981,  2345,  2299,   -15,     1,  2027,  2169,  2338,  2343,
    2347,  2160,  2181,  2076,  2182,  2161,  2376,  2060,  2059,  1238,
    1758,   199,   831,  1161,  2000,  2167,  2367,  1777,   485,  2168,
    2133,  2136,   701,  2292,   551,   815,   552,  2221,   963,  2018,
    1626,  1841,   553,  2012,   554,  2354,  1504,  1186,  1566,   869,
     874,  2132,  1355,  1743,  1276,  1927,  2113,  1063,  2353,     2,
    2008,  2324,  1306,  1499,  1272,  2143,  1882,  1073,  1082,  2279,
    2014,  1117,   336,     3,     4,     5,     6,  1044,  1085,  1320,
    1188,  1174,   930,  1978,  1323,  2187,  1324,     7,     8,     9,
      10,  1977,  1851,  1707,  1986,  1695,    11,  1854,  1022,   430,
    1698,  2091,  2193,  2200,     0,     0,     0,     0,     0,  2074,
       0,     0,     0,  1511,     0,     0,  2084,  1004,     0,     0,
       0,     0,  1522,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1549,  1550,  1551,  1552,     0,     0,    12,     0,     0,     0,
       0,     0,     0,  1889,     0,  2115,     0,     0,     0,     0,
    1760,     0,     0,     0,     0,     0,  2129,  2239,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   642,   643,   644,
     645,     0,     0,     0,    13,     0,     0,     0,     0,     0,
       0,     0,     0,  2147,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  2175,     0,     0,     0,     0,
       0,     0,     0,     0,  2180,     0,     0,     0,     0,     0,
       0,     0,     0,    14,     0,     0,     0,     0,     0,     0,
       0,     0,    15,    16,     0,     0,     0,     0,     0,   646,
       0,     0,     0,     0,     0,    17,    18,     0,    19,     0,
      20,    21,    22,    23,    24,    25,    26,    27,    28,     0,
    2219,    29,    30,     0,     0,     0,     0,  2227,    31,    32,
       0,     0,     0,     0,     0,     0,     0,  2236,     0,     0,
       0,     0,     0,     0,    33,     0,     0,    34,     0,     0,
       0,     0,     0,    35,  2251,     0,    36,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  2335,     0,     0,
       0,  2337,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      37,     0,    38,     0,     0,     0,     0,  1690,     0,     0,
    1522,     0,     0,     0,     0,     0,     0,     0,  1294,     0,
    2115,   622,   623,   624,   625,  1002,     0,     0,  1002,  2288,
       0,     0,     0,     0,     0,   626,     0,     0,     0,   627,
     628,   629,   381,   382,   630,   631,   632,   633,   634,   635,
     636,   637,   638,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  2312,     0,     0,     0,     0,     0,     0,     0,
    2317,   639,   640,   641,     0,     0,     0,     0,     0,     0,
       0,   622,   623,   624,   625,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   626,  2227,     0,     0,   627,
     628,   629,   381,   382,   630,   631,   632,   633,   634,   635,
     636,   637,   638,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   639,   640,   641,     0,     0,     0,   366,   367,   368,
     369,   370,   371,   372,   373,   374,   375,   376,   377,   378,
       0,     0,   379,   380,  1660,  1661,    90,    91,     0,     0,
      92,   381,   382,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    93,     0,     0,    94,     0,     0,   383,   384,
     385,   386,   387,   388,   389,    95,    96,    97,    98,  1522,
      99,     0,     0,   324,   325,   326,     0,     0,     0,   390,
     100,   391,   392,     0,     0,   202,   207,     0,     0,   208,
     209,     0,     0,     0,     0,     0,     0,     0,     0,  1873,
     101,     0,  1874,   102,  1875,     0,   103,     0,     0,     0,
       0,     0,   104,     0,     0,     0,     0,   105,   106,   107,
       0,     0,     0,     0,     0,     0,   108,     0,   109,     0,
       0,     0,     0,   393,   394,     0,  1383,     0,   110,   395,
       0,   111,     0,     0,   112,   113,   114,   396,   115,   116,
       0,     0,     0,     0,     0,     0,     0,     0,   397,   398,
     399,   400,     0,   401,   402,   117,   118,   403,   404,   119,
     405,   120,   121,   122,   123,   124,   125,   126,     0,   127,
     406,   128,   129,   130,   131,     0,   132,   407,   133,     0,
       0,     0,     0,   134,   698,   881,   409,     0,   642,   643,
     644,   645,     0,     0,   410,   411,     0,     0,     0,     0,
       0,     0,     0,     0,   412,   413,     0,  1972,  1690,  1690,
       0,  1690,     0,     0,   414,   415,   416,     0,     0,     0,
       0,   418,     0,     0,     0,  1002,     0,     0,     0,     0,
       0,   135,   136,     0,     0,     0,   137,     0,     0,   138,
       0,     0,     0,   139,   140,   141,   142,   143,   642,   643,
     644,   645,     0,     0,   144,     0,     0,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,     0,
     157,     0,     0,     0,     0,     0,     0,   158,     0,     0,
     159,     0,     0,     0,   160,     0,     0,   161,   162,     0,
     163,     0,     0,   164,     0,   165,     0,     0,     0,   166,
     167,     0,     0,    35,     0,     0,    36,   419,   420,   421,
     422,   172,   173,     0,   174,   175,   176,     0,   177,     0,
       0,     0,     0,   178,   179,     0,     0,     0,     0,   423,
       0,     0,     0,   424,   425,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   180,   181,
       0,   182,   183,     0,     0,     0,     0,   184,   185,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   186,   187,   188,     0,
       0,     0,   426,     0,   427,     0,     0,     0,     0,     0,
       0,     0,     0,   366,   367,   368,   369,   370,   371,   372,
     373,   374,   375,   376,   377,   378,     0,     0,   379,   380,
       0,     0,    90,    91,     0,     0,    92,   381,   382,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    93,     0,
       0,    94,     0,     0,   383,   384,   385,   386,   387,   388,
     389,    95,    96,    97,    98,  1972,    99,     0,  1690,   324,
     325,   326,     0,     0,     0,   390,   100,   391,   392,     0,
       0,   202,   207,     0,     0,   208,   209,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   101,     0,     0,   102,
       0,     0,   103,     0,     0,     0,     0,     0,   104,     0,
       0,     0,     0,   105,   106,   107,     0,     0,     0,     0,
       0,     0,   108,     0,   109,     0,     0,     0,     0,   393,
     394,     0,     0,     0,   110,   395,     0,   111,     0,     0,
     112,   113,   114,   396,   115,   116,     0,     0,     0,     0,
       0,     0,     0,     0,   397,   398,   399,   400,     0,   401,
     402,   117,   118,   403,   404,   119,   405,   120,   121,   122,
     123,   124,   125,   126,     0,   127,   406,   128,   129,   130,
     131,     0,   132,   407,   133,     0,     0,     0,     0,   134,
     698,  2006,   409,     0,     0,     0,     0,     0,     0,     0,
     410,   411,     0,     0,     0,     0,     0,     0,     0,     0,
     412,   413,     0,     0,     0,     0,     0,     0,     0,     0,
     414,   415,   416,     0,     0,     0,     0,   418,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   135,   136,     0,
       0,     0,   137,     0,     0,   138,     0,     0,     0,   139,
     140,   141,   142,   143,     0,     0,     0,     0,     0,     0,
     144,     0,     0,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,     0,   157,     0,     0,     0,
       0,     0,     0,   158,     0,     0,   159,     0,     0,     0,
     160,     0,     0,   161,   162,     0,   163,     0,     0,   164,
       0,   165,     0,     0,     0,   166,   167,     0,     0,    35,
       0,     0,    36,   419,   420,   421,   422,   172,   173,     0,
     174,   175,   176,     0,   177,     0,     0,     0,     0,   178,
     179,     0,     0,     0,     0,   423,     0,     0,     0,   424,
     425,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   180,   181,     0,   182,   183,     0,
       0,     0,     0,   184,   185,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   186,   187,   188,     0,     0,     0,   426,     0,
     427,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,     0,     0,   379,   380,     0,     0,
      90,    91,     0,     0,    92,   381,   382,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    93,     0,     0,    94,
       0,     0,   383,   384,   385,   386,   387,   388,   389,    95,
      96,    97,    98,     0,    99,     0,     0,   324,   325,   326,
       0,     0,     0,   390,   100,   391,   392,     0,     0,   202,
     207,     0,     0,   208,   209,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   101,     0,     0,   102,     0,     0,
     103,     0,     0,     0,     0,     0,   104,     0,     0,     0,
       0,   105,   106,   107,     0,     0,     0,     0,     0,     0,
     108,     0,   109,     0,     0,     0,     0,   393,   394,     0,
       0,     0,   110,   395,     0,   111,     0,     0,   112,   113,
     114,   396,   115,   116,     0,     0,     0,     0,     0,     0,
       0,     0,   397,   398,   399,   400,     0,   401,   402,   117,
     118,   403,   404,   119,   405,   120,   121,   122,   123,   124,
     125,   126,     0,   127,   406,   128,   129,   130,   131,     0,
     132,   407,   133,     0,     0,     0,     0,   134,   698,     0,
     409,     0,     0,     0,     0,     0,     0,     0,   410,   411,
       0,     0,     0,     0,     0,     0,     0,     0,   412,   413,
       0,     0,     0,     0,     0,     0,     0,     0,   414,   415,
     416,     0,     0,     0,     0,   418,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   135,   136,     0,     0,     0,
     137,     0,     0,   138,     0,     0,     0,   139,   140,   141,
     142,   143,     0,     0,     0,     0,     0,     0,   144,     0,
       0,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,     0,   157,     0,     0,     0,     0,     0,
       0,   158,     0,     0,   159,     0,     0,     0,   160,     0,
       0,   161,   162,     0,   163,     0,     0,   164,     0,   165,
       0,     0,     0,   166,   167,     0,     0,    35,     0,     0,
      36,   419,   420,   421,   422,   172,   173,     0,   174,   175,
     176,     0,   177,     0,     0,     0,     0,   178,   179,     0,
       0,     0,     0,   423,     0,     0,     0,   424,   425,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   180,   181,     0,   182,   183,     0,     0,     0,
       0,   184,   185,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     186,   187,   188,     0,     0,     0,   426,     0,   427,   366,
     367,   368,   369,   370,   371,   372,   373,   374,   375,   376,
     377,   378,     0,     0,   379,   380,     0,     0,    90,    91,
       0,     0,    92,   381,   382,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    93,     0,     0,    94,     0,     0,
     383,   384,   385,   386,   387,   388,   389,    95,    96,    97,
      98,     0,    99,     0,     0,   324,   325,   326,     0,     0,
       0,   390,   100,   391,   392,     0,     0,     0,   207,     0,
       0,   208,   209,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   101,     0,     0,   102,     0,     0,   103,     0,
       0,     0,     0,     0,   104,     0,     0,     0,     0,   105,
     106,   107,     0,     0,     0,     0,     0,     0,   108,     0,
     109,     0,     0,     0,     0,   393,   394,     0,     0,     0,
     110,   395,     0,   111,     0,     0,   112,   113,   114,   396,
     115,   116,     0,     0,     0,     0,     0,     0,     0,     0,
     397,   398,   399,   400,     0,   401,   402,   117,   118,   403,
     404,   119,   405,   120,   121,   122,   123,   124,   125,   126,
       0,   127,   406,   128,   129,   130,   131,     0,   132,   407,
     133,     0,     0,     0,     0,   134,   408,     0,   409,     0,
    1065,  1066,     0,     0,     0,     0,   410,   411,     0,     0,
       0,     0,     0,  1067,     0,     0,   412,   413,     0,     0,
       0,     0,     0,     0,     0,     0,   414,   415,   416,     0,
       0,     0,     0,   418,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   135,   136,     0,     0,     0,   137,     0,
       0,   138,     0,     0,     0,   139,   140,   141,   142,   143,
       0,     0,     0,     0,     0,     0,   144,     0,     0,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,     0,   157,     0,     0,     0,     0,     0,     0,   158,
       0,     0,   159,     0,     0,     0,   160,     0,     0,   161,
     162,     0,   163,     0,     0,   164,     0,   165,     0,     0,
       0,   166,   167,     0,     0,     0,     0,     0,     0,   419,
     420,   421,   422,   172,   173,     0,   174,   175,   176,     0,
     177,     0,     0,     0,     0,   178,   179,     0,     0,     0,
       0,   423,     0,     0,     0,   424,   425,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     180,   181,     0,   182,   183,     0,     0,     0,     0,   184,
     185,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   186,   187,
     188,     0,     0,     0,   426,     0,   427,   366,   367,   368,
     369,   370,   371,   372,   373,   374,   375,   376,   377,   378,
       0,     0,   379,   380,     0,     0,    90,    91,     0,     0,
      92,   381,   382,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    93,     0,     0,    94,     0,     0,   383,   384,
     385,   386,   387,   388,   389,    95,    96,    97,    98,     0,
      99,     0,     0,   324,   325,   326,     0,     0,     0,   390,
     100,   391,   392,     0,     0,     0,   207,     0,     0,   208,
     209,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     101,     0,     0,   102,     0,     0,   103,     0,     0,     0,
       0,     0,   104,     0,     0,     0,     0,   105,   106,   107,
       0,     0,     0,     0,     0,     0,   108,     0,   109,     0,
       0,     0,     0,   393,   394,     0,     0,     0,   110,   395,
       0,   111,     0,     0,   112,   113,   114,   396,   115,   116,
       0,     0,     0,     0,     0,     0,     0,     0,   397,   398,
     399,   400,     0,   401,   402,   117,   118,   403,   404,   119,
     405,   120,   121,   122,   123,   124,   125,   126,     0,   127,
     406,   128,   129,   130,   131,     0,   132,   407,   133,     0,
       0,     0,     0,   134,   408,  1111,   409,     0,  1112,     0,
       0,     0,     0,     0,   410,   411,     0,     0,     0,     0,
       0,     0,     0,     0,   412,   413,     0,     0,     0,     0,
       0,     0,     0,     0,   414,   415,   416,  1113,     0,     0,
       0,   418,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   135,   136,     0,     0,     0,   137,     0,     0,   138,
       0,     0,     0,   139,   140,   141,   142,   143,     0,     0,
       0,     0,     0,     0,   144,     0,     0,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,     0,
    1114,     0,     0,     0,     0,     0,     0,   158,     0,     0,
     159,     0,     0,     0,   160,     0,     0,   161,   162,     0,
     163,     0,     0,   164,     0,   165,     0,     0,     0,   166,
     167,     0,     0,     0,     0,     0,     0,   419,   420,   421,
     422,   172,   173,     0,   174,   175,   176,     0,   177,     0,
       0,     0,     0,   178,   179,     0,     0,     0,     0,   423,
       0,     0,     0,   424,   425,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   180,   181,
       0,   182,   183,     0,     0,     0,     0,   184,   185,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   186,   187,   188,     0,
       0,     0,   426,     0,   427,   366,   367,   368,   369,   370,
     371,   372,   373,   374,   375,   376,   377,   378,     0,     0,
     379,   380,     0,     0,    90,    91,     0,     0,    92,   381,
     382,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      93,     0,     0,    94,     0,     0,   383,   384,   385,   386,
     387,   388,   389,    95,    96,    97,    98,     0,    99,     0,
       0,   324,   325,   326,     0,     0,     0,   390,   100,   391,
     392,     0,     0,     0,   207,     0,     0,   208,   209,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   101,     0,
       0,   102,     0,     0,   103,     0,     0,     0,     0,     0,
     104,     0,     0,     0,     0,   105,   106,   107,     0,     0,
       0,     0,     0,     0,   108,     0,   109,     0,     0,     0,
       0,   393,   394,     0,     0,     0,   110,   395,     0,   111,
       0,     0,   112,   113,   114,   396,   115,   116,     0,     0,
       0,     0,     0,     0,     0,     0,   397,   398,   399,   400,
       0,   401,   402,   117,   118,   403,   404,   119,   405,   120,
     121,   122,   123,   124,   125,   126,     0,   127,   406,   128,
     129,   130,   131,     0,   132,   407,   133,     0,     0,     0,
       0,   134,   408,  1184,   409,     0,  1112,     0,     0,     0,
       0,     0,   410,   411,     0,     0,     0,     0,     0,     0,
       0,     0,   412,   413,     0,     0,     0,     0,     0,     0,
       0,     0,   414,   415,   416,  1113,     0,     0,     0,   418,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   135,
     136,     0,     0,     0,   137,     0,     0,   138,     0,     0,
       0,   139,   140,   141,   142,   143,     0,     0,     0,     0,
       0,     0,   144,     0,     0,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,     0,  1114,     0,
       0,     0,     0,     0,     0,   158,     0,     0,   159,     0,
       0,     0,   160,     0,     0,   161,   162,     0,   163,     0,
       0,   164,     0,   165,     0,     0,     0,   166,   167,     0,
       0,     0,     0,     0,     0,   419,   420,   421,   422,   172,
     173,     0,   174,   175,   176,     0,   177,     0,     0,     0,
       0,   178,   179,     0,     0,     0,     0,   423,     0,     0,
       0,   424,   425,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   180,   181,     0,   182,
     183,     0,     0,     0,     0,   184,   185,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   186,   187,   188,     0,     0,     0,
     426,     0,   427,   366,   367,   368,   369,   370,   371,   372,
     373,   374,   375,   376,   377,   378,     0,     0,   379,   380,
       0,     0,    90,    91,     0,     0,    92,   381,   382,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    93,     0,
       0,    94,     0,     0,   383,   384,   385,   386,   387,   388,
     389,    95,    96,    97,    98,     0,    99,     0,     0,   324,
     325,   326,     0,     0,     0,   390,   100,   391,   392,     0,
       0,   202,   207,     0,     0,   208,   209,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   101,     0,     0,   102,
       0,     0,   103,     0,     0,     0,     0,     0,   104,     0,
       0,     0,     0,   105,   106,   107,     0,     0,     0,     0,
       0,     0,   108,     0,   109,     0,     0,     0,     0,   393,
     394,     0,     0,     0,   110,   395,     0,   111,     0,     0,
     112,   113,   114,   396,   115,   116,     0,     0,     0,     0,
       0,     0,     0,     0,   397,   398,   399,   400,     0,   401,
     402,   117,   118,   403,   404,   119,   405,   120,   121,   122,
     123,   124,   125,   126,     0,   127,   406,   128,   129,   130,
     131,     0,   132,   407,   133,     0,     0,     0,     0,   134,
     698,     0,   409,     0,     0,     0,     0,     0,     0,     0,
     410,   411,     0,     0,     0,     0,     0,     0,     0,     0,
     412,   413,     0,     0,     0,     0,     0,     0,     0,     0,
     414,   415,   416,     0,     0,     0,     0,   418,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   135,   136,     0,
       0,     0,   137,     0,     0,   138,     0,     0,     0,   139,
     140,   141,   142,   143,     0,     0,     0,     0,     0,     0,
     144,     0,     0,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,     0,   157,     0,     0,     0,
       0,     0,     0,   158,     0,     0,   159,     0,     0,     0,
     160,     0,     0,   161,   162,     0,   163,     0,     0,   164,
       0,   165,     0,     0,     0,  1959,   167,     0,     0,    35,
       0,     0,    36,   419,   420,   421,   422,   172,   173,     0,
     174,   175,   176,     0,   177,     0,     0,     0,     0,   178,
     179,     0,     0,     0,     0,   423,     0,     0,     0,   424,
     425,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   180,   181,     0,   182,   183,     0,
       0,     0,     0,   184,   185,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   186,   187,   188,     0,     0,     0,   426,     0,
     427,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,     0,     0,   379,   380,     0,     0,
      90,    91,     0,     0,    92,   381,   382,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    93,     0,     0,    94,
       0,     0,   383,   384,   385,   386,   387,   388,   389,    95,
      96,    97,    98,     0,    99,     0,     0,   324,   325,   326,
       0,     0,     0,   390,   100,   391,   392,     0,     0,     0,
     207,     0,     0,   208,   209,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   101,     0,     0,   102,     0,     0,
     103,     0,     0,     0,     0,     0,   104,     0,     0,     0,
       0,   105,   106,   107,     0,     0,     0,     0,     0,     0,
     108,     0,   109,     0,     0,     0,     0,   393,   394,     0,
       0,     0,   110,   395,     0,   111,     0,     0,   112,   113,
     114,   396,   115,   116,     0,     0,     0,     0,     0,     0,
       0,     0,   397,   398,   399,   400,     0,   401,   402,   117,
     118,   403,   404,   119,   405,   120,   121,   122,   123,   124,
     125,   126,     0,   127,   406,   128,   129,   130,   131,     0,
     132,   407,   133,     0,     0,     0,     0,   134,   408,     0,
     409,     0,     0,     0,     0,  2009,     0,     0,   410,   411,
       0,     0,     0,     0,     0,     0,     0,     0,   412,   413,
       0,     0,     0,     0,     0,     0,     0,     0,   414,   415,
     416,     0,     0,     0,     0,   418,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   135,   136,     0,     0,     0,
     137,     0,     0,   138,     0,     0,     0,   139,   140,   141,
     142,   143,     0,     0,     0,     0,     0,     0,   144,     0,
       0,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,     0,   157,     0,     0,     0,     0,     0,
       0,   158,     0,     0,   159,     0,     0,     0,   160,     0,
       0,   161,   162,     0,   163,     0,     0,   164,     0,   165,
       0,     0,     0,   166,   167,     0,     0,     0,     0,     0,
       0,   419,   420,   421,   422,   172,   173,     0,   174,   175,
     176,     0,   177,     0,     0,     0,     0,   178,   179,     0,
       0,     0,     0,   423,     0,     0,     0,   424,   425,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   180,   181,     0,   182,   183,     0,     0,     0,
       0,   184,   185,     0,     0,     0,     0,     0,     0,  2010,
       0,     0,     0,     0,     0,     0,  2011,     0,     0,     0,
     186,   187,   188,     0,     0,     0,   426,     0,   427,   366,
     367,   368,   369,   370,   371,   372,   373,   374,   375,   376,
     377,   378,     0,     0,   379,   380,     0,     0,    90,    91,
       0,     0,    92,   381,   382,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    93,     0,     0,    94,     0,     0,
     383,   384,   385,   386,   387,   388,   389,    95,    96,    97,
      98,     0,    99,     0,     0,   324,   325,   326,     0,     0,
       0,   390,   100,   391,   392,     0,     0,     0,   207,     0,
       0,   208,   209,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   101,     0,     0,   102,     0,     0,   103,     0,
       0,     0,     0,     0,   104,     0,     0,     0,     0,   105,
     106,   107,     0,     0,     0,     0,     0,     0,   108,     0,
     109,     0,     0,     0,     0,   393,   394,     0,     0,     0,
     110,   395,     0,   111,     0,     0,   112,   113,   114,   396,
     115,   116,     0,     0,     0,     0,     0,     0,     0,     0,
     397,   398,   399,   400,     0,   401,   402,   117,   118,   403,
     404,   119,   405,   120,   121,   122,   123,   124,   125,   126,
       0,   127,   406,   128,   129,   130,   131,     0,   132,   407,
     133,     0,     0,     0,     0,   134,   408,  1118,   409,     0,
    1119,     0,     0,     0,     0,     0,   410,   411,     0,     0,
       0,     0,     0,     0,     0,     0,   412,   413,     0,     0,
       0,     0,     0,     0,     0,     0,   414,   415,   416,     0,
       0,     0,     0,   418,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   135,   136,     0,     0,     0,   137,     0,
       0,   138,     0,     0,     0,   139,   140,   141,   142,   143,
       0,     0,     0,     0,     0,     0,   144,     0,     0,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,     0,  1120,     0,     0,     0,     0,     0,     0,   158,
       0,     0,   159,     0,     0,     0,   160,     0,     0,   161,
     162,     0,   163,     0,     0,   164,     0,   165,     0,     0,
       0,   166,   167,     0,     0,     0,     0,     0,     0,   419,
     420,   421,   422,   172,   173,     0,   174,   175,   176,     0,
     177,     0,     0,     0,     0,   178,   179,     0,     0,     0,
       0,   423,     0,     0,     0,   424,   425,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     180,   181,     0,   182,   183,     0,     0,     0,     0,   184,
     185,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   186,   187,
     188,     0,     0,     0,   426,     0,   427,   366,   367,   368,
     369,   370,   371,   372,   373,   374,   375,   376,   377,   378,
       0,     0,   379,   380,     0,     0,    90,    91,     0,     0,
      92,   381,   382,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    93,     0,     0,    94,     0,     0,   383,   384,
     385,   386,   387,   388,   389,    95,    96,    97,    98,     0,
      99,     0,     0,   324,   325,   326,     0,     0,     0,   390,
     100,   391,   392,     0,     0,     0,   207,     0,     0,   208,
     209,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     101,     0,     0,   102,     0,     0,   103,     0,     0,     0,
       0,     0,   104,     0,     0,     0,     0,   105,   106,   107,
       0,     0,     0,     0,     0,     0,   108,     0,   109,     0,
       0,  1883,  1884,   393,  1885,     0,     0,     0,   110,   395,
       0,   111,     0,     0,   112,   113,   114,   396,   115,   116,
       0,     0,     0,     0,     0,     0,     0,     0,   397,   398,
     399,   400,     0,   401,   402,   117,   118,   403,   404,   119,
     405,   120,   121,   122,   123,   124,   125,   126,     0,   127,
     406,   128,   129,   130,   131,     0,   132,   407,   133,     0,
       0,     0,     0,   134,  1886,     0,   409,     0,     0,     0,
       0,     0,     0,     0,   410,   411,     0,     0,     0,     0,
       0,     0,     0,     0,   412,   413,     0,     0,     0,     0,
       0,     0,     0,     0,   414,   415,   416,     0,     0,     0,
       0,   418,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   135,   136,     0,     0,     0,   137,     0,     0,   138,
       0,     0,     0,   139,   140,   141,   142,   143,     0,     0,
       0,     0,     0,     0,   144,     0,     0,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,     0,
     157,     0,     0,     0,     0,     0,     0,   158,     0,     0,
     159,     0,     0,     0,   160,     0,     0,   161,   162,     0,
     163,     0,     0,   164,     0,   165,     0,     0,     0,   166,
     167,     0,     0,     0,     0,     0,     0,   419,   420,   421,
     422,   172,   173,     0,   174,   175,   176,     0,   177,     0,
       0,     0,     0,   178,   179,     0,     0,     0,     0,   423,
       0,     0,     0,   424,   425,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   180,   181,
       0,   182,   183,     0,     0,     0,     0,   184,   185,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   186,   187,   188,     0,
       0,     0,   426,     0,   427,   366,   367,   368,   369,   370,
     371,   372,   373,   374,   375,   376,   377,   378,     0,     0,
     379,   380,     0,     0,    90,    91,     0,     0,    92,   381,
     382,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      93,     0,     0,    94,     0,     0,   383,   384,   385,   386,
     387,   388,   389,    95,    96,    97,    98,     0,    99,     0,
       0,   324,   325,   326,     0,     0,     0,   390,   100,   391,
     392,     0,     0,     0,   207,     0,     0,   208,   209,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   101,     0,
       0,   102,     0,     0,   103,     0,     0,     0,     0,     0,
     104,     0,     0,     0,     0,   105,   106,   107,     0,     0,
       0,     0,     0,     0,   108,     0,   109,     0,     0,     0,
       0,   393,   394,     0,     0,     0,   110,   395,     0,   111,
       0,     0,   112,   113,   114,   396,   115,   116,     0,     0,
       0,     0,     0,     0,     0,     0,   397,   398,   399,   400,
       0,   401,   402,   117,   118,   403,   404,   119,   405,   120,
     121,   122,   123,   124,   125,   126,     0,   127,   406,   128,
     129,   130,   131,     0,   132,   407,   133,     0,     0,     0,
       0,   134,   408,     0,   409,     0,     0,     0,     0,     0,
       0,     0,   410,   411,     0,     0,     0,     0,     0,     0,
       0,     0,   412,   413,     0,     0,     0,     0,     0,     0,
       0,     0,   414,   415,   416,     0,     0,     0,     0,   418,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   135,
     136,     0,     0,     0,   137,     0,     0,   138,     0,     0,
       0,   139,   140,   141,   142,   143,     0,     0,     0,     0,
       0,     0,   144,     0,     0,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,     0,   157,     0,
       0,     0,     0,     0,     0,   158,     0,     0,   159,     0,
       0,     0,   160,     0,     0,   161,   162,     0,   163,     0,
       0,   164,     0,   165,     0,     0,     0,   166,   167,     0,
       0,     0,     0,     0,     0,   419,   420,   421,   422,   172,
     173,     0,   174,   175,   176,     0,   177,     0,     0,     0,
       0,   178,   179,     0,     0,     0,     0,   423,     0,     0,
       0,   424,   425,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   180,   181,     0,   182,
     183,     0,     0,     0,     0,   184,   185,     0,     0,     0,
       0,     0,     0,  2010,     0,     0,     0,     0,     0,     0,
    2114,     0,     0,     0,   186,   187,   188,     0,     0,     0,
     426,     0,   427,   366,   367,   368,   369,   370,   371,   372,
     373,   374,   375,   376,   377,   378,     0,     0,   379,   380,
       0,     0,    90,    91,     0,     0,    92,   381,   382,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    93,     0,
       0,    94,     0,     0,   383,   384,   385,   386,   387,   388,
     389,    95,    96,    97,    98,     0,    99,     0,     0,   324,
     325,   326,     0,     0,     0,   390,   100,   391,   392,     0,
       0,     0,   207,     0,     0,   208,   209,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   101,     0,     0,   102,
       0,     0,   103,     0,     0,     0,     0,     0,   104,     0,
       0,     0,     0,   105,   106,   107,     0,     0,     0,     0,
       0,     0,   108,     0,   109,     0,     0,     0,     0,   393,
     394,     0,     0,     0,   110,   395,     0,   111,     0,     0,
     112,   113,   114,   396,   115,   116,     0,     0,     0,     0,
       0,     0,     0,     0,   397,   398,   399,   400,     0,   401,
     402,   117,   118,   403,   404,   119,   405,   120,   121,   122,
     123,   124,   125,   126,     0,   127,   406,   128,   129,   130,
     131,     0,   132,   407,   133,     0,     0,     0,     0,   134,
     408,     0,   409,     0,     0,     0,     0,     0,     0,     0,
     410,   411,     0,     0,     0,     0,     0,     0,     0,     0,
     412,   413,     0,     0,     0,     0,     0,     0,     0,     0,
     414,   415,   416,   417,     0,     0,     0,   418,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   135,   136,     0,
       0,     0,   137,     0,     0,   138,     0,     0,     0,   139,
     140,   141,   142,   143,     0,     0,     0,     0,     0,     0,
     144,     0,     0,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,     0,   157,     0,     0,     0,
       0,     0,     0,   158,     0,     0,   159,     0,     0,     0,
     160,     0,     0,   161,   162,     0,   163,     0,     0,   164,
       0,   165,     0,     0,     0,   166,   167,     0,     0,     0,
       0,     0,     0,   419,   420,   421,   422,   172,   173,     0,
     174,   175,   176,     0,   177,     0,     0,     0,     0,   178,
     179,     0,     0,     0,     0,   423,     0,     0,     0,   424,
     425,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   180,   181,     0,   182,   183,     0,
       0,     0,     0,   184,   185,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   186,   187,   188,     0,     0,     0,   426,     0,
     427,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,     0,     0,   379,   380,     0,     0,
      90,    91,     0,     0,    92,   381,   382,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    93,     0,     0,    94,
       0,     0,   383,   384,   385,   386,   387,   388,   389,    95,
      96,    97,    98,     0,    99,     0,     0,   324,   325,   326,
       0,     0,     0,   390,   100,   391,   392,     0,     0,     0,
     207,     0,     0,   208,   209,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   101,     0,     0,   102,     0,     0,
     103,     0,     0,     0,     0,     0,   104,     0,     0,     0,
       0,   105,   106,   107,     0,     0,     0,     0,     0,     0,
     108,     0,   109,     0,     0,     0,     0,   393,   394,     0,
       0,     0,   110,   395,     0,   111,     0,     0,   112,   113,
     114,   396,   115,   116,     0,     0,     0,     0,     0,     0,
       0,     0,   397,   398,   399,   400,     0,   401,   402,   117,
     118,   403,   404,   119,   405,   120,   121,   122,   123,   124,
     125,   126,     0,   127,   406,   128,   129,   130,   131,     0,
     132,   407,   133,     0,     0,     0,     0,   134,   408,     0,
     409,     0,     0,     0,     0,     0,     0,     0,   410,   411,
       0,     0,     0,     0,     0,     0,     0,     0,   412,   413,
       0,     0,     0,     0,     0,     0,     0,     0,   414,   415,
     416,     0,     0,     0,     0,   418,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   135,   136,     0,     0,     0,
     137,     0,     0,   138,     0,     0,     0,   139,   140,   141,
     142,   143,     0,     0,     0,     0,     0,     0,   144,     0,
       0,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   543,   157,     0,     0,     0,     0,     0,
       0,   158,     0,     0,   159,     0,     0,     0,   160,     0,
       0,   161,   162,     0,   163,     0,     0,   164,     0,   165,
       0,     0,     0,   166,   167,     0,     0,     0,     0,     0,
       0,   419,   420,   421,   422,   172,   173,     0,   174,   175,
     176,     0,   177,     0,     0,     0,     0,   178,   179,     0,
       0,     0,     0,   423,     0,     0,     0,   424,   425,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   180,   181,     0,   182,   183,     0,     0,     0,
       0,   184,   185,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     186,   187,   188,     0,     0,     0,   426,     0,   427,   366,
     367,   368,   369,   370,   371,   372,   373,   374,   375,   376,
     377,   378,     0,     0,   379,   380,     0,     0,    90,    91,
       0,     0,    92,   381,   382,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    93,     0,     0,    94,     0,     0,
     383,   384,   385,   386,   387,   388,   389,    95,    96,    97,
      98,     0,    99,     0,     0,   324,   325,   326,     0,     0,
       0,   390,   100,   391,   392,     0,     0,     0,   207,     0,
       0,   208,   209,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   101,     0,     0,   102,     0,     0,   103,     0,
       0,     0,     0,     0,   104,     0,     0,     0,     0,   105,
     106,   107,     0,     0,     0,     0,     0,     0,   108,     0,
     109,     0,     0,     0,     0,   393,   394,     0,     0,     0,
     110,   395,     0,   111,     0,     0,   112,   113,   114,   396,
     115,   116,     0,     0,     0,     0,     0,     0,     0,     0,
     397,   398,   399,   400,     0,   401,   402,   117,   118,   403,
     404,   119,   405,   120,   121,   122,   123,   124,   125,   126,
       0,   127,   406,   128,   129,   130,   131,     0,   132,   407,
     133,     0,     0,     0,     0,   134,   408,     0,   409,     0,
       0,     0,     0,     0,     0,     0,   410,   411,     0,     0,
       0,     0,     0,     0,     0,     0,   412,   413,     0,     0,
       0,     0,     0,     0,     0,     0,   414,   415,   416,     0,
       0,     0,     0,   418,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   135,   136,     0,     0,     0,   137,     0,
       0,   138,     0,     0,     0,   139,   140,   141,   142,   143,
       0,     0,     0,     0,     0,     0,   144,     0,     0,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,     0,   157,     0,     0,     0,     0,     0,     0,   158,
       0,     0,   159,     0,     0,     0,   160,     0,     0,   161,
     162,     0,   163,     0,     0,   164,     0,   165,     0,     0,
       0,   166,   167,     0,     0,     0,     0,     0,     0,   419,
     420,   421,   422,   172,   173,     0,   174,   175,   176,     0,
     177,     0,     0,     0,     0,   178,   179,     0,     0,     0,
       0,   423,   723,     0,     0,   424,   425,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     180,   181,     0,   182,   183,     0,     0,     0,     0,   184,
     185,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   186,   187,
     188,     0,     0,     0,   426,     0,   427,   366,   367,   368,
     369,   370,   371,   372,   373,   374,   375,   376,   377,   378,
       0,     0,   379,   380,     0,     0,    90,    91,     0,     0,
      92,   381,   382,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    93,     0,     0,    94,     0,     0,   383,   384,
     385,   386,   387,   388,   389,    95,    96,    97,    98,     0,
      99,     0,     0,   324,   325,   326,     0,     0,     0,   390,
     100,   391,   392,     0,     0,     0,   207,     0,     0,   208,
     209,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     101,     0,     0,   102,     0,     0,   103,     0,     0,     0,
       0,     0,   104,     0,     0,     0,     0,   105,   106,   107,
       0,     0,     0,     0,     0,     0,   108,     0,   109,     0,
       0,     0,     0,   393,   394,     0,     0,     0,   110,   395,
       0,   111,     0,     0,   112,   113,   114,   396,   115,   116,
       0,     0,     0,     0,     0,     0,     0,     0,   397,   398,
     399,   400,     0,   401,   402,   117,   118,   403,   404,   119,
     405,   120,   121,   122,   123,   124,   125,   126,     0,   127,
     406,   128,   129,   130,   131,     0,   132,   407,   133,     0,
       0,     0,     0,   134,   408,   804,   409,     0,     0,     0,
       0,     0,     0,     0,   410,   411,     0,     0,     0,     0,
       0,     0,     0,     0,   412,   413,     0,     0,     0,     0,
       0,     0,     0,     0,   414,   415,   416,     0,     0,     0,
       0,   418,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   135,   136,     0,     0,     0,   137,     0,     0,   138,
       0,     0,     0,   139,   140,   141,   142,   143,     0,     0,
       0,     0,     0,     0,   144,     0,     0,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,     0,
     157,     0,     0,     0,     0,     0,     0,   158,     0,     0,
     159,     0,     0,     0,   160,     0,     0,   161,   162,     0,
     163,     0,     0,   164,     0,   165,     0,     0,     0,   166,
     167,     0,     0,     0,     0,     0,     0,   419,   420,   421,
     422,   172,   173,     0,   174,   175,   176,     0,   177,     0,
       0,     0,     0,   178,   179,     0,     0,     0,     0,   423,
       0,     0,     0,   424,   425,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   180,   181,
       0,   182,   183,     0,     0,     0,     0,   184,   185,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   186,   187,   188,     0,
       0,     0,   426,     0,   427,   366,   367,   368,   369,   370,
     371,   372,   373,   374,   375,   376,   377,   378,     0,     0,
     379,   380,     0,     0,    90,    91,     0,     0,    92,   381,
     382,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      93,     0,     0,    94,     0,     0,   383,   384,   385,   386,
     387,   388,   389,    95,    96,    97,    98,     0,    99,     0,
       0,   324,   325,   326,     0,     0,     0,   390,   100,   391,
     392,     0,     0,     0,   207,     0,     0,   208,   209,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   101,     0,
       0,   102,     0,     0,   103,     0,     0,     0,     0,     0,
     104,     0,     0,     0,     0,   105,   106,   107,     0,     0,
       0,     0,     0,     0,   108,     0,   109,     0,     0,     0,
       0,   393,   394,     0,     0,     0,   110,   395,     0,   111,
       0,     0,   112,   113,   114,   396,   115,   116,     0,     0,
       0,     0,     0,     0,     0,     0,   397,   398,   399,   400,
       0,   401,   402,   117,   118,   403,   404,   119,   405,   120,
     121,   122,   123,   124,   125,   126,     0,   127,   406,   128,
     129,   130,   131,     0,   132,   407,   133,     0,     0,     0,
       0,   134,   408,     0,   409,     0,     0,     0,     0,     0,
       0,     0,   410,   411,     0,     0,     0,     0,     0,     0,
       0,     0,   412,   413,     0,     0,     0,     0,     0,     0,
       0,     0,   414,   415,   416,     0,     0,     0,     0,   418,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   135,
     136,     0,     0,     0,   137,     0,     0,   138,     0,     0,
       0,   139,   140,   141,   142,   143,     0,     0,     0,     0,
       0,     0,   144,     0,     0,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,     0,   157,     0,
       0,     0,     0,     0,     0,   158,     0,     0,   159,     0,
       0,     0,   160,     0,     0,   161,   162,     0,   163,     0,
       0,   164,     0,   165,     0,     0,     0,   166,   167,     0,
       0,     0,     0,     0,     0,   419,   420,   421,   422,   172,
     173,     0,   174,   175,   176,     0,   177,     0,     0,     0,
       0,   178,   179,     0,     0,     0,     0,   423,  1963,     0,
       0,   424,   425,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   180,   181,     0,   182,
     183,     0,     0,     0,     0,   184,   185,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   186,   187,   188,     0,     0,     0,
     426,     0,   427,   366,   367,   368,   369,   370,   371,   372,
     373,   374,   375,   376,   377,   378,     0,     0,   379,   380,
       0,     0,    90,    91,     0,     0,    92,   381,   382,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    93,     0,
       0,    94,     0,     0,   383,   384,   385,   386,   387,   388,
     389,    95,    96,    97,    98,     0,    99,     0,     0,   324,
     325,   326,     0,     0,     0,   390,   100,   391,   392,     0,
       0,     0,   207,     0,     0,   208,   209,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   101,     0,     0,   102,
       0,     0,   103,     0,     0,     0,     0,     0,   104,     0,
       0,     0,     0,   105,   106,   107,     0,     0,     0,     0,
       0,     0,   108,     0,   109,     0,     0,     0,     0,   393,
     394,     0,     0,     0,   110,   395,     0,   111,     0,     0,
     112,   113,   114,   396,   115,   116,     0,     0,     0,     0,
       0,     0,     0,     0,   397,   398,   399,   400,     0,   401,
     402,   117,   118,   403,   404,   119,   405,   120,   121,   122,
     123,   124,   125,   126,     0,   127,   406,   128,   129,   130,
     131,     0,   132,   407,   133,     0,     0,     0,     0,   134,
     408,     0,   409,     0,     0,     0,     0,     0,     0,     0,
     410,   411,     0,     0,     0,     0,     0,     0,     0,     0,
     412,   413,     0,     0,     0,     0,     0,     0,     0,     0,
     414,   415,   416,     0,     0,     0,     0,   418,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   135,   136,     0,
       0,     0,   137,     0,     0,   138,     0,     0,     0,   139,
     140,   141,   142,   143,     0,     0,     0,     0,     0,     0,
     144,     0,     0,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,     0,   157,     0,     0,     0,
       0,     0,     0,   158,     0,     0,   159,     0,     0,     0,
     160,     0,     0,   161,   162,     0,   163,     0,     0,   164,
       0,   165,     0,     0,     0,   166,   167,     0,     0,     0,
       0,     0,     0,   419,   420,   421,   422,   172,   173,     0,
     174,   175,   176,     0,   177,     0,     0,     0,     0,   178,
     179,     0,     0,     0,     0,   423,     0,     0,     0,   424,
     425,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   180,   181,     0,   182,   183,     0,
       0,     0,     0,   184,   185,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  2127,     0,     0,
       0,     0,   186,   187,   188,     0,     0,     0,   426,     0,
     427,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,     0,     0,   379,   380,     0,     0,
      90,    91,     0,     0,    92,   381,   382,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    93,     0,     0,    94,
       0,     0,   383,   384,   385,   386,   387,   388,   389,    95,
      96,    97,    98,     0,    99,     0,     0,   324,   325,   326,
       0,     0,     0,   390,   100,   391,   392,     0,     0,     0,
     207,     0,     0,   208,   209,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   101,     0,     0,   102,     0,     0,
     103,     0,     0,     0,     0,     0,   104,     0,     0,     0,
       0,   105,   106,   107,     0,     0,     0,     0,     0,     0,
     108,     0,   109,     0,     0,     0,     0,   393,   394,     0,
       0,     0,   110,   395,     0,   111,     0,     0,   112,   113,
     114,   396,   115,   116,     0,     0,     0,     0,     0,     0,
       0,     0,   397,   398,   399,   400,     0,   401,   402,   117,
     118,   403,   404,   119,   405,   120,   121,   122,   123,   124,
     125,   126,     0,   127,   406,   128,   129,   130,   131,     0,
     132,   407,   133,     0,     0,     0,     0,   134,   408,     0,
     409,     0,     0,     0,     0,     0,     0,     0,   410,   411,
       0,     0,     0,     0,     0,     0,     0,     0,   412,   413,
       0,     0,     0,     0,     0,     0,     0,     0,   414,   415,
     416,     0,     0,     0,     0,   418,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   135,   136,     0,     0,     0,
     137,     0,     0,   138,     0,     0,     0,   139,   140,   141,
     142,   143,     0,     0,     0,     0,     0,     0,   144,     0,
       0,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,     0,   157,     0,     0,     0,     0,     0,
       0,   158,     0,     0,   159,     0,     0,     0,   160,     0,
       0,   161,   162,     0,   163,     0,     0,   164,     0,   165,
       0,     0,     0,   166,   167,     0,     0,     0,     0,     0,
       0,   419,   420,   421,   422,   172,   173,     0,   174,   175,
     176,     0,   177,     0,     0,     0,     0,   178,   179,     0,
       0,     0,     0,   423,     0,     0,     0,   424,   425,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   180,   181,     0,   182,   183,     0,     0,     0,
       0,   184,   185,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  2286,     0,     0,     0,     0,
     186,   187,   188,     0,     0,     0,   426,     0,   427,   366,
     367,   368,   369,   370,   371,   372,   373,   374,   375,   376,
     377,   378,     0,     0,   379,   380,     0,     0,    90,    91,
       0,     0,    92,   381,   382,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    93,     0,     0,    94,     0,     0,
     383,   384,   385,   386,   387,   388,   389,    95,    96,    97,
      98,     0,    99,     0,     0,   324,   325,   326,     0,     0,
       0,   390,   100,   391,   392,     0,     0,     0,   207,     0,
       0,   208,   209,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   101,     0,     0,   102,     0,     0,   103,     0,
       0,     0,     0,     0,   104,     0,     0,     0,     0,   105,
     106,   107,     0,     0,     0,     0,     0,     0,   108,     0,
     109,     0,     0,     0,     0,   393,   394,     0,     0,     0,
     110,   395,     0,   111,     0,     0,   112,   113,   114,   396,
     115,   116,     0,     0,     0,     0,     0,     0,     0,     0,
     397,   398,   399,   400,     0,   401,   402,   117,   118,   403,
     404,   119,   405,   120,   121,   122,   123,   124,   125,   126,
       0,   127,   406,   128,   129,   130,   131,     0,   132,   407,
     133,     0,     0,     0,     0,   134,   408,     0,   409,     0,
       0,     0,     0,     0,     0,     0,   410,   411,     0,     0,
       0,     0,     0,     0,     0,     0,   412,   413,     0,     0,
       0,     0,     0,     0,     0,     0,   414,   415,   416,     0,
       0,     0,     0,   418,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   135,   136,     0,     0,     0,   137,     0,
       0,   138,     0,     0,     0,   139,   140,   141,   142,   143,
       0,     0,     0,     0,     0,     0,   144,     0,     0,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,     0,   157,     0,     0,     0,     0,     0,     0,   158,
       0,     0,   159,     0,     0,     0,   160,     0,     0,   161,
     162,     0,   163,     0,     0,   164,     0,   165,     0,     0,
       0,   166,   167,     0,     0,     0,     0,     0,     0,   419,
     420,   421,   422,   172,   173,     0,   174,   175,   176,     0,
     177,     0,     0,     0,     0,   178,   179,     0,     0,     0,
       0,   423,     0,     0,     0,   424,   425,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     180,   181,     0,   182,   183,     0,     0,     0,     0,   184,
     185,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   186,   187,
     188,     0,     0,     0,   426,     0,   427,   366,   367,   368,
     369,   370,   371,   372,   373,   374,   375,   376,   377,   378,
       0,     0,   379,   380,     0,     0,    90,    91,     0,     0,
      92,   381,   382,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    93,     0,     0,    94,     0,     0,   383,   384,
     385,   386,   387,   388,   389,    95,    96,    97,    98,     0,
      99,     0,     0,   324,   325,   326,     0,     0,     0,   390,
     100,   391,   392,     0,     0,     0,   207,     0,     0,   208,
     209,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     101,     0,     0,   102,     0,     0,   103,     0,     0,     0,
       0,     0,   104,     0,     0,     0,     0,   105,   106,   107,
       0,     0,     0,     0,     0,     0,   108,     0,   109,     0,
       0,     0,     0,   393,   394,     0,     0,     0,   110,   395,
       0,   111,     0,     0,   112,   113,   114,   396,   115,   116,
       0,     0,     0,     0,     0,     0,     0,     0,   397,   398,
     399,   400,  1689,   401,   402,   117,   118,   403,   404,   119,
     405,   120,   121,   122,   123,   124,   125,   126,  1010,   127,
     406,   128,   129,   130,   131,     0,   132,   407,   133,     0,
       0,     0,     0,   134,   708,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   412,   413,     0,     0,     0,     0,
       0,     0,     0,     0,   414,   415,   416,     0,     0,     0,
       0,   418,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   135,   136,     0,     0,     0,   137,     0,     0,   138,
       0,     0,     0,   139,   140,   141,   142,   143,     0,     0,
       0,     0,     0,     0,   144,     0,     0,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,     0,
     157,     0,     0,     0,     0,     0,     0,   158,     0,     0,
     159,     0,     0,     0,   160,     0,     0,   161,   162,     0,
     163,     0,     0,   164,     0,   165,     0,     0,     0,   166,
     167,     0,     0,     0,     0,     0,     0,   419,   420,   421,
     422,   172,   173,     0,   174,   175,   176,     0,   177,     0,
       0,     0,     0,   178,   179,     0,     0,     0,     0,   423,
       0,     0,     0,   424,   425,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   180,   181,
       0,   182,   183,     0,     0,     0,     0,   184,   185,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   186,   187,   188,     0,
       0,     0,     0,     0,   427,   366,   367,   368,   369,   370,
     371,   372,   373,   374,   375,   376,   377,   378,     0,     0,
     379,   380,     0,     0,    90,    91,     0,     0,    92,   381,
     382,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      93,     0,     0,    94,     0,     0,   383,   384,   385,   386,
     387,   388,   389,    95,    96,    97,    98,     0,    99,     0,
       0,   324,   325,   326,     0,     0,     0,   390,   100,   391,
     392,     0,     0,     0,   207,     0,     0,   208,   209,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   101,     0,
       0,  1520,     0,     0,   103,     0,     0,     0,     0,     0,
     104,     0,     0,     0,     0,   105,   106,   107,     0,     0,
       0,     0,     0,     0,   108,     0,   109,     0,     0,     0,
       0,   393,   394,     0,     0,     0,   110,   395,     0,   111,
       0,     0,   112,   113,   114,   396,   115,   116,     0,     0,
       0,     0,     0,     0,     0,     0,   397,   398,   399,   400,
       0,   401,   402,   117,   118,   403,   404,   119,   405,   120,
     121,   122,   123,   124,   125,   126,     0,   127,   406,   128,
     129,   130,   131,     0,   132,   407,   133,     0,     0,     0,
       0,   134,   708,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   412,   413,     0,     0,     0,     0,     0,     0,
       0,     0,   414,   415,   416,     0,     0,     0,     0,   418,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   135,
     136,     0,     0,     0,   137,     0,     0,   138,     0,     0,
       0,   139,   140,   141,   142,   143,     0,     0,     0,     0,
       0,     0,   144,     0,     0,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,  1521,   157,     0,
       0,     0,     0,     0,     0,   158,     0,     0,   159,     0,
       0,     0,   160,     0,     0,   161,   162,     0,   163,     0,
       0,   164,     0,   165,     0,     0,     0,   166,   167,     0,
       0,     0,     0,     0,     0,   419,   420,   421,   422,   172,
     173,     0,   174,   175,   176,     0,   177,     0,     0,     0,
       0,   178,   179,     0,     0,     0,     0,   423,     0,     0,
       0,   424,   425,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   180,   181,     0,   182,
     183,     0,     0,     0,     0,   184,   185,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   186,   187,   188,     0,     0,     0,
       0,     0,   427,   366,   367,   368,   369,   370,   371,   372,
     373,   374,   375,   376,   377,   378,     0,     0,   379,   380,
       0,     0,    90,    91,     0,     0,    92,   381,   382,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    93,     0,
       0,    94,     0,     0,   383,   384,   385,   386,   387,   388,
     389,    95,    96,    97,    98,     0,    99,     0,     0,   324,
     325,   326,     0,     0,     0,   390,   100,   391,   392,     0,
       0,     0,   207,     0,     0,   208,   209,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   101,     0,     0,   102,
       0,     0,   103,     0,     0,     0,     0,     0,   104,     0,
       0,     0,     0,   105,   106,   107,     0,     0,     0,     0,
       0,     0,   108,     0,   109,     0,     0,     0,     0,   393,
     394,     0,     0,     0,   110,   395,     0,   111,     0,     0,
     112,   113,   114,   396,   115,   116,     0,     0,     0,     0,
       0,     0,     0,     0,   397,   398,   399,   400,  1689,   401,
     402,   117,   118,   403,   404,   119,   405,   120,   121,   122,
     123,   124,   125,   126,     0,   127,   406,   128,   129,   130,
     131,     0,   132,   407,   133,     0,     0,     0,     0,   134,
     708,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     412,   413,     0,     0,     0,     0,     0,     0,     0,     0,
     414,   415,   416,     0,     0,     0,     0,   418,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   135,   136,     0,
       0,     0,   137,     0,     0,   138,     0,     0,     0,   139,
     140,   141,   142,   143,     0,     0,     0,     0,     0,     0,
     144,     0,     0,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,     0,   157,     0,     0,     0,
       0,     0,     0,   158,     0,     0,   159,     0,     0,     0,
     160,     0,     0,   161,   162,     0,   163,     0,     0,   164,
       0,   165,     0,     0,     0,   166,   167,     0,     0,     0,
       0,     0,     0,   419,   420,   421,   422,   172,   173,     0,
     174,   175,   176,     0,   177,     0,     0,     0,     0,   178,
     179,     0,     0,     0,     0,   423,     0,     0,     0,   424,
     425,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   180,   181,     0,   182,   183,     0,
       0,     0,     0,   184,   185,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   186,   187,   188,     0,     0,     0,     0,     0,
     427,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,     0,     0,   379,   380,     0,     0,
      90,    91,     0,     0,    92,   381,   382,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    93,     0,     0,    94,
       0,     0,   383,   384,   385,   386,   387,   388,   389,    95,
      96,    97,    98,     0,    99,     0,     0,   324,   325,   326,
       0,     0,     0,   390,   100,   391,   392,     0,     0,     0,
     207,     0,     0,   208,   209,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   101,     0,     0,   102,     0,     0,
     103,     0,     0,     0,     0,     0,   104,     0,     0,     0,
       0,   105,   106,   107,     0,     0,     0,     0,     0,     0,
     108,     0,   109,     0,     0,     0,     0,   393,   394,     0,
       0,     0,   110,   395,     0,   111,     0,     0,   112,   113,
     114,   396,   115,   116,     0,     0,     0,     0,     0,     0,
       0,     0,   397,   398,   399,   400,     0,   401,   402,   117,
     118,   403,   404,   119,   405,   120,   121,   122,   123,   124,
     125,   126,     0,   127,   406,   128,   129,   130,   131,     0,
     132,   407,   133,     0,     0,     0,     0,   134,   708,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   412,   413,
       0,     0,     0,     0,     0,     0,     0,     0,   414,   415,
     416,     0,     0,     0,     0,   418,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   135,   136,     0,     0,     0,
     137,     0,     0,   138,     0,     0,     0,   139,   140,   141,
     142,   143,     0,     0,     0,     0,     0,     0,   144,     0,
       0,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,     0,   157,     0,     0,     0,     0,     0,
       0,   158,     0,     0,   159,     0,     0,     0,   160,     0,
       0,   161,   162,     0,   163,     0,     0,   164,     0,   165,
       0,     0,     0,   166,   167,     0,     0,     0,     0,     0,
       0,   419,   420,   421,   422,   172,   173,     0,   174,   175,
     176,     0,   177,     0,     0,     0,     0,   178,   179,     0,
       0,     0,     0,   423,     0,     0,     0,   424,   425,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   180,   181,     0,   182,   183,     0,     0,     0,
       0,   184,   185,     0,     0,     0,     0,    85,    86,    87,
      88,    89,     0,     0,     0,     0,     0,     0,     0,     0,
     186,   187,   188,    90,    91,     0,     0,    92,   427,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    93,
       0,     0,    94,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    95,    96,    97,    98,     0,    99,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   100,     0,     0,
       3,     4,  1810,     6,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     7,     8,     9,  1811,     0,     0,
     102,     0,     0,  1812,     0,     0,     0,     0,     0,   104,
       0,     0,     0,     0,   105,   106,   107,     0,     0,     0,
       0,     0,     0,   108,     0,   109,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   110,     0,     0,   111,     0,
       0,   112,   113,   114,     0,   115,   116,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   117,   118,     0,     0,   119,     0,   120,   121,
     122,   123,   124,   125,   126,     0,   127,     0,   128,   129,
     130,   131,     0,   132,     0,   133,     0,     0,     0,     0,
     134,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   622,   623,   624,   625,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   626,
       0,     0,     0,   627,   628,   629,   381,   382,   630,   631,
     632,   633,   634,   635,   636,   637,   638,     0,   135,   136,
      14,     0,     0,   137,     0,     0,   138,     0,     0,    15,
     139,   140,   141,   142,   143,   639,   640,   641,     0,     0,
       0,   144,    17,  1814,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,     0,   157,    29,    30,
       0,     0,     0,     0,   158,    31,    32,   159,     0,     0,
       0,   160,     0,     0,   161,   162,     0,   163,     0,     0,
     164,    33,   165,  1816,    34,     0,   166,   167,     0,     0,
       0,     0,     0,     0,   168,   169,   170,   171,   172,   173,
       0,   174,   175,   176,     0,   177,     0,     0,     0,     0,
     178,   179,     0,     0,     0,     0,  1817,     0,     0,  2263,
       0,     0,  1818,  2264,  -410,     0,     0,    37,     0,    38,
       0,     0,     0,     0,     0,   180,   181,     0,   182,   183,
       0,     0,     0,     0,   184,   185,     0,     0,     0,     0,
      85,    86,    87,    88,    89,     0,     0,     0,     0,     0,
       0,     0,     0,   186,   187,   188,    90,    91,     0,     0,
      92,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    93,     0,     0,    94,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    95,    96,    97,    98,     0,
      99,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     100,     0,     0,     3,     4,  1810,     6,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     7,     8,     9,
    1811,     0,     0,   102,     0,     0,  1812,     0,     0,     0,
       0,     0,   104,     0,     0,     0,  1311,   105,   106,   107,
       0,     0,     0,     0,     0,     0,   108,     0,   109,     0,
       0,     0,     0,     0,     0,     0,     0,   750,   110,     0,
       0,   111,     0,     0,   112,   113,   114,     0,   115,   116,
       0,     0,   642,   643,   644,   645,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   117,   118,     0,     0,   119,
       0,   120,   121,   122,   123,   124,   125,   126,     0,   127,
       0,   128,   129,   130,   131,     0,   132,     0,   133,     0,
       0,     0,     0,   134,   751,   752,   753,   754,   755,   756,
     757,   758,   759,   760,     0,     0,     0,   761,   762,   763,
       0,   764,   765,   766,   767,   768,   769,   770,   771,   772,
     773,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   135,   136,    14,     0,     0,   137,     0,     0,   138,
       0,     0,    15,   139,   140,   141,   142,   143,     0,     0,
       0,     0,     0,  1813,   144,    17,  1814,  1815,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,     0,
     157,    29,    30,     0,     0,     0,     0,   158,    31,    32,
     159,     0,     0,     0,   160,     0,     0,   161,   162,     0,
     163,     0,     0,   164,    33,   165,  1816,    34,     0,   166,
     167,     0,     0,     0,     0,     0,     0,   168,   169,   170,
     171,   172,   173,     0,   174,   175,   176,     0,   177,     0,
       0,     0,     0,   178,   179,     0,     0,     0,     0,  1817,
       0,     0,     0,     0,     0,  1818,     0,     0,     0,     0,
    1819,     0,    38,     0,     0,     0,     0,     0,   180,   181,
       0,   182,   183,     0,     0,     0,     0,   184,   185,  1312,
       0,     0,     0,    85,    86,    87,    88,    89,     0,     0,
       0,     0,     0,     0,     0,     0,   186,   187,   188,    90,
      91,     0,     0,    92,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    93,     0,     0,    94,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    95,    96,
      97,    98,     0,    99,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   100,     0,     0,     3,     4,  1810,     6,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       7,     8,     9,  1811,     0,     0,   102,     0,     0,  1812,
       0,     0,     0,     0,     0,   104,     0,     0,     0,     0,
     105,   106,   107,     0,     0,     0,     0,     0,     0,   108,
       0,   109,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   110,     0,   750,   111,     0,     0,   112,   113,   114,
       0,   115,   116,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   117,   118,
       0,     0,   119,     0,   120,   121,   122,   123,   124,   125,
     126,  1732,   127,     0,   128,   129,   130,   131,     0,   132,
       0,   133,     0,     0,     0,     0,   134,     0,     0,     0,
     751,   752,   753,   754,   755,   756,   757,   758,   759,   760,
       0,     0,     0,   761,   762,   763,     0,   764,   765,   766,
     767,   768,   769,   770,   771,   772,   773,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   135,   136,    14,     0,     0,   137,
       0,     0,   138,     0,     0,    15,   139,   140,   141,   142,
     143,     0,     0,     0,     0,     0,     0,   144,    17,  1814,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,     0,   157,    29,    30,     0,     0,     0,     0,
     158,    31,    32,   159,     0,     0,     0,   160,     0,     0,
     161,   162,     0,   163,     0,     0,   164,    33,   165,  1816,
      34,     0,   166,   167,     0,     0,     0,     0,     0,     0,
     168,   169,   170,   171,   172,   173,     0,   174,   175,   176,
       0,   177,     0,     0,     0,     0,   178,   179,     0,     0,
       0,     0,  1817,     0,     0,     0,     0,     0,  1818,     0,
    -410,     0,     0,    37,     0,    38,     0,     0,     0,     0,
       0,   180,   181,     0,   182,   183,     0,     0,     0,     0,
     184,   185,     0,     0,     0,  1733,    85,    86,    87,    88,
      89,     0,     0,     0,     0,     0,     0,     0,     0,   186,
     187,   188,    90,    91,     0,     0,    92,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    93,     0,
       0,    94,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    95,    96,    97,    98,     0,    99,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   100,     0,     0,     3,
       4,  1810,     6,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     7,     8,     9,  1811,     0,     0,   102,
       0,     0,  1812,     0,     0,     0,     0,     0,   104,     0,
       0,     0,     0,   105,   106,   107,     0,     0,     0,     0,
       0,     0,   108,     0,   109,     0,     0,     0,     0,     0,
       0,     0,     0,   750,   110,     0,     0,   111,     0,     0,
     112,   113,   114,     0,   115,   116,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   117,   118,     0,     0,   119,     0,   120,   121,   122,
     123,   124,   125,   126,     0,   127,     0,   128,   129,   130,
     131,     0,   132,     0,   133,     0,     0,     0,     0,   134,
     751,   752,   753,   754,   755,   756,   757,   758,   759,   760,
       0,     0,     0,   761,   762,   763,     0,   764,   765,   766,
     767,   768,   769,   770,   771,   772,   773,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   135,   136,    14,
       0,     0,   137,     0,     0,   138,     0,     0,    15,   139,
     140,   141,   142,   143,     0,     0,     0,     0,     0,     0,
     144,    17,  1814,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,     0,   157,    29,    30,     0,
       0,     0,     0,   158,    31,    32,   159,     0,     0,     0,
     160,     0,     0,   161,   162,     0,   163,     0,     0,   164,
      33,   165,  1816,    34,     0,   166,   167,     0,     0,     0,
       0,     0,     0,   168,   169,   170,   171,   172,   173,     0,
     174,   175,   176,     0,   177,     0,     0,     0,     0,   178,
     179,     0,     0,     0,     0,  1817,     0,     0,     0,     0,
       0,  1818,     0,     0,     0,     0,    37,  2320,    38,     0,
       0,     0,     0,     0,   180,   181,     0,   182,   183,     0,
       0,     0,     0,   184,   185,  1314,     0,     0,     0,    85,
      86,    87,    88,    89,     0,     0,     0,     0,     0,     0,
       0,     0,   186,   187,   188,    90,    91,     0,     0,    92,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    93,     0,     0,    94,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    95,    96,    97,    98,     0,    99,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   100,
       0,     0,     3,     4,  1810,     6,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     7,     8,     9,  1811,
       0,     0,   102,     0,     0,  1812,     0,     0,     0,     0,
       0,   104,     0,     0,     0,     0,   105,   106,   107,     0,
       0,     0,     0,     0,     0,   108,     0,   109,     0,     0,
       0,     0,     0,     0,     0,     0,   750,   110,     0,     0,
     111,     0,     0,   112,   113,   114,     0,   115,   116,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   117,   118,     0,     0,   119,     0,
     120,   121,   122,   123,   124,   125,   126,     0,   127,     0,
     128,   129,   130,   131,     0,   132,     0,   133,     0,     0,
       0,     0,   134,   751,   752,   753,   754,   755,   756,   757,
     758,   759,   760,     0,     0,     0,   761,   762,   763,     0,
     764,   765,   766,   767,   768,   769,   770,   771,   772,   773,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     135,   136,    14,     0,     0,   137,     0,     0,   138,     0,
       0,    15,   139,   140,   141,   142,   143,     0,     0,     0,
       0,     0,     0,   144,    17,  1814,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,     0,   157,
      29,    30,     0,     0,     0,     0,   158,    31,    32,   159,
       0,     0,     0,   160,     0,     0,   161,   162,     0,   163,
       0,     0,   164,    33,   165,  1816,    34,     0,   166,   167,
       0,     0,     0,     0,     0,     0,   168,   169,   170,   171,
     172,   173,     0,   174,   175,   176,     0,   177,     0,     0,
       0,     0,   178,   179,     0,     0,     0,     0,  1817,     0,
       0,     0,     0,     0,  1818,     0,     0,     0,     0,    37,
       0,    38,     0,     0,     0,     0,     0,   180,   181,     0,
     182,   183,     0,     0,     0,     0,   184,   185,  1735,     0,
       0,     0,    85,    86,    87,    88,    89,     0,     0,     0,
       0,     0,     0,     0,     0,   186,   187,   188,    90,    91,
       0,     0,    92,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    93,     0,     0,    94,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    95,    96,    97,
      98,     0,    99,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   100,     0,     0,     3,     4,  1810,     6,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     7,
       8,     9,  1811,     0,     0,   102,     0,     0,  1812,  1365,
       0,     0,     0,     0,   104,     0,     0,     0,     0,   105,
     106,   107,     0,     0,     0,     0,     0,     0,   108,     0,
     109,     0,     0,     0,     0,     0,     0,     0,     0,   750,
     110,     0,     0,   111,     0,     0,   112,   113,   114,     0,
     115,   116,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   117,   118,     0,
       0,   119,     0,   120,   121,   122,   123,   124,   125,   126,
       0,   127,     0,   128,   129,   130,   131,     0,   132,     0,
     133,     0,     0,     0,     0,   134,   751,   752,   753,   754,
     755,   756,   757,   758,   759,   760,     0,     0,     0,   761,
     762,   763,     0,   764,   765,   766,   767,   768,   769,   770,
     771,   772,   773,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   135,   136,    14,     0,     0,   137,     0,
       0,   138,     0,     0,     0,   139,   140,   141,   142,   143,
       0,     0,     0,     0,     0,     0,   144,    17,  1814,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,     0,   157,     0,    30,     0,     0,     0,     0,   158,
      31,    32,   159,     0,     0,     0,   160,     0,     0,   161,
     162,     0,   163,     0,     0,   164,    33,   165,  1816,     0,
       0,   166,   167,     0,     0,     0,     0,     0,     0,   168,
     169,   170,   171,   172,   173,     0,   174,   175,   176,     0,
     177,     0,     0,     0,     0,   178,   179,     0,     0,     0,
       0,  1817,     0,     0,     0,     0,     0,  1818,     0,     0,
       0,     0,    37,  2346,    38,     0,     0,     0,     0,     0,
     180,   181,     0,   182,   183,     0,     0,     0,     0,   184,
     185,     0,     0,     0,     0,    85,    86,    87,    88,    89,
       0,     0,     0,     0,     0,     0,     0,     0,   186,   187,
     188,    90,    91,     0,     0,    92,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    93,     0,     0,
      94,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      95,    96,    97,    98,     0,    99,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   100,     0,     0,     3,     4,
    1810,     6,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     7,     8,     9,  1811,     0,     0,   102,     0,
       0,  1812,     0,     0,     0,     0,     0,   104,     0,     0,
       0,     0,   105,   106,   107,  1730,     0,     0,     0,     0,
       0,   108,     0,   109,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   110,     0,   750,   111,     0,     0,   112,
     113,   114,     0,   115,   116,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     117,   118,     0,     0,   119,     0,   120,   121,   122,   123,
     124,   125,   126,  1731,   127,     0,   128,   129,   130,   131,
       0,   132,     0,   133,     0,     0,     0,     0,   134,     0,
       0,     0,   751,   752,   753,   754,   755,   756,   757,   758,
     759,   760,     0,     0,     0,   761,   762,   763,     0,   764,
     765,   766,   767,   768,   769,   770,   771,   772,   773,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   135,   136,    14,     0,
       0,   137,     0,     0,   138,     0,     0,     0,   139,   140,
     141,   142,   143,     0,     0,     0,     0,     0,     0,   144,
      17,  1814,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,     0,   157,     0,    30,     0,     0,
       0,     0,   158,    31,    32,   159,     0,     0,     0,   160,
       0,     0,   161,   162,     0,   163,     0,     0,   164,    33,
     165,  1816,     0,     0,   166,   167,     0,     0,     0,     0,
       0,     0,   168,   169,   170,   171,   172,   173,     0,   174,
     175,   176,     0,   177,     0,     0,     0,     0,   178,   179,
       0,     0,     0,     0,  1817,     0,     0,     0,     0,     0,
    1818,     0,     0,     0,     0,  2159,     0,    38,     0,     0,
       0,     0,     0,   180,   181,     0,   182,   183,     0,     0,
       0,     0,   184,   185,     0,     0,     0,     0,    85,    86,
      87,    88,    89,     0,     0,     0,     0,     0,     0,     0,
       0,   186,   187,   188,    90,    91,     0,     0,    92,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      93,     0,     0,    94,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    95,    96,    97,    98,     0,    99,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   100,     0,
       0,     0,     0,   202,   207,     0,  1051,   208,   209,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   101,     0,
       0,   102,     0,     0,   103,     0,     0,     0,     0,     0,
     104,     0,     0,     0,     0,   105,   106,   107,     0,     0,
       0,     0,     0,     0,   108,     0,   109,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   110,   750,     0,   111,
       0,     0,   112,   113,   114,     0,   115,   116,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   117,   118,     0,     0,   119,     0,   120,
     121,   122,   123,   124,   125,   126,     0,   127,     0,   128,
     129,   130,   131,  1313,   132,     0,   133,     0,     0,     0,
       0,   134,  1334,     0,   751,   752,   753,   754,   755,   756,
     757,   758,   759,   760,     0,     0,     0,   761,   762,   763,
       0,   764,   765,   766,   767,   768,   769,   770,   771,   772,
     773,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   135,
     136,     0,     0,     0,   137,     0,     0,   138,     0,     0,
       0,   139,   140,   141,   142,   143,     0,     0,     0,     0,
       0,     0,   144,     0,     0,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,     0,   157,     0,
       0,     0,     0,     0,     0,   158,     0,     0,   159,     0,
       0,     0,   160,     0,     0,   161,   162,     0,   163,     0,
       0,   164,     0,   165,     0,     0,     0,   166,   167,     0,
       0,    35,     0,     0,    36,   168,   169,   170,   171,   172,
     173,     0,   174,   175,   176,     0,   177,     0,     0,     0,
       0,   178,   179,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    85,    86,    87,
      88,    89,     0,     0,     0,     0,   180,   181,     0,   182,
     183,     0,     0,    90,    91,   184,   185,    92,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    93,
       0,     0,    94,     0,   186,   187,   188,     0,     0,     0,
       0,     0,    95,    96,    97,    98,     0,    99,     0,     0,
     324,   325,   326,     0,     0,     0,   327,   328,   329,   330,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   101,     0,     0,
     102,     0,     0,   103,     0,     0,     0,     0,     0,   104,
       0,     0,     0,     0,   105,   106,   107,     0,     0,     0,
       0,     0,     0,   108,     0,   109,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   110,     0,   750,   111,     0,
       0,   112,   113,   114,     0,   115,   116,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   117,   118,     0,     0,   119,     0,   120,   121,
     122,   123,   124,   125,   126,  1688,   127,     0,   128,   129,
     130,   131,     0,   132,     0,   133,     0,     0,     0,     0,
     134,   331,     0,     0,   751,   752,   753,   754,   755,   756,
     757,   758,   759,   760,     0,     0,     0,   761,   762,   763,
       0,   764,   765,   766,   767,   768,   769,   770,   771,   772,
     773,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   135,   136,
       0,     0,     0,   137,     0,     0,   138,     0,     0,     0,
     139,   140,   141,   142,   143,     0,     0,     0,     0,     0,
       0,   144,     0,     0,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,     0,   157,     0,     0,
       0,     0,     0,     0,   158,     0,     0,   332,     0,     0,
       0,   160,     0,     0,   161,   162,     0,   163,     0,     0,
     333,     0,   165,     0,     0,     0,   166,   167,     0,     0,
       0,     0,     0,     0,   168,   334,   170,   171,   172,   173,
       0,   174,   175,   176,     0,   177,     0,     0,     0,     0,
     178,   179,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    85,    86,    87,    88,
      89,     0,     0,     0,     0,   180,   181,   283,   182,   183,
       0,     0,    90,    91,   184,   185,    92,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    93,     0,
       0,    94,     0,   186,   187,   188,     0,     0,     0,     0,
       0,    95,    96,    97,    98,     0,    99,     0,     0,     0,
       0,     0,   285,     0,     0,     0,   100,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   101,     0,     0,   102,
       0,     0,   103,     0,     0,     0,     0,     0,   104,     0,
       0,     0,     0,   105,   106,   107,     0,     0,     0,     0,
       0,     0,   108,     0,   109,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   110,     0,   750,   111,     0,     0,
     112,   113,   114,     0,   115,   116,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   117,   118,     0,     0,   119,     0,   120,   121,   122,
     123,   124,   125,   126,  1734,   127,     0,   128,   129,   130,
     131,     0,   132,     0,   133,     0,     0,     0,     0,   134,
       0,     0,     0,   751,   752,   753,   754,   755,   756,   757,
     758,   759,   760,     0,     0,     0,   761,   762,   763,     0,
     764,   765,   766,   767,   768,   769,   770,   771,   772,   773,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   342,   343,   291,
     292,   293,   344,     0,     0,   138,     0,     0,     0,   139,
     140,   141,   142,   143,     0,     0,     0,     0,     0,     0,
     144,     0,     0,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,     0,   157,     0,     0,     0,
       0,     0,     0,   158,     0,     0,   159,     0,     0,     0,
     160,     0,     0,   161,   162,     0,   163,     0,     0,   164,
       0,   165,     0,     0,     0,   345,   167,     0,     0,     0,
       0,     0,     0,   168,   169,   170,   171,   172,   173,     0,
     174,   175,   176,     0,   177,     0,     0,     0,     0,   178,
     179,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    85,    86,    87,    88,    89,
       0,     0,     0,     0,   180,   181,     0,   182,   183,     0,
       0,    90,    91,   184,   185,    92,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    93,     0,     0,
      94,     0,   186,   187,   188,     0,     0,     0,     0,     0,
      95,    96,    97,    98,     0,    99,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   100,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   101,     0,     0,   102,     0,
       0,   103,     0,     0,     0,     0,     0,   104,     0,     0,
       0,     0,   105,   106,   107,     0,     0,     0,     0,     0,
       0,   108,     0,   109,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   110,     0,   750,   111,     0,     0,   112,
     113,   114,     0,   115,   116,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     117,   118,     0,     0,   119,     0,   120,   121,   122,   123,
     124,   125,   126,  1996,   127,     0,   128,   129,   130,   131,
       0,   132,     0,   828,     0,     0,     0,     0,   134,     0,
       0,     0,   751,   752,   753,   754,   755,   756,   757,   758,
     759,   760,     0,     0,     0,   761,   762,   763,     0,   764,
     765,   766,   767,   768,   769,   770,   771,   772,   773,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   135,   136,     0,     0,
       0,   137,     0,     0,   138,     0,     0,     0,   139,   140,
     141,   142,   143,   305,   306,   307,   308,     0,     0,   144,
       0,     0,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,     0,   157,     0,     0,     0,     0,
       0,     0,   158,     0,     0,   159,     0,     0,     0,   160,
       0,     0,   161,   162,     0,   163,     0,     0,   164,     0,
     165,     0,     0,     0,   829,   167,     0,     0,     0,     0,
       0,     0,   168,   169,   170,   171,   172,   173,     0,   174,
     175,   176,     0,   177,     0,     0,     0,     0,   178,   179,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   180,   181,     0,   182,   183,     0,     0,
       0,     0,   184,   185,     0,     0,     0,     0,    85,    86,
      87,    88,    89,     0,     0,     0,     0,     0,     0,   311,
       0,   186,   187,   188,    90,    91,     0,     0,    92,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      93,     0,     0,    94,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    95,    96,    97,    98,     0,    99,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   100,     0,
       0,     0,     0,     0,   207,     0,  1051,   208,   209,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   101,     0,
       0,   102,     0,     0,   103,     0,     0,     0,     0,     0,
     104,     0,     0,     0,     0,   105,   106,   107,     0,     0,
       0,     0,     0,     0,   108,     0,   109,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   110,     0,   750,   111,
       0,     0,   112,   113,   114,     0,   115,   116,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   117,   118,     0,     0,   119,     0,   120,
     121,   122,   123,   124,   125,   126,  1997,   127,     0,   128,
     129,   130,   131,     0,   132,     0,   133,     0,     0,     0,
       0,   134,  1052,     0,     0,   751,   752,   753,   754,   755,
     756,   757,   758,   759,   760,     0,     0,     0,   761,   762,
     763,     0,   764,   765,   766,   767,   768,   769,   770,   771,
     772,   773,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   135,
     136,     0,     0,     0,   137,     0,     0,   138,     0,     0,
       0,   139,   140,   141,   142,   143,     0,     0,     0,     0,
       0,     0,   144,     0,     0,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,     0,   157,     0,
       0,     0,     0,     0,     0,   158,     0,     0,   159,     0,
       0,     0,   160,     0,     0,   161,   162,     0,   163,     0,
       0,   164,     0,   165,     0,     0,     0,   166,   167,     0,
       0,     0,     0,     0,     0,   168,   169,   170,   171,   172,
     173,     0,   174,   175,   176,     0,   177,     0,     0,     0,
       0,   178,   179,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    85,    86,    87,
      88,  1124,     0,     0,     0,     0,   180,   181,     0,   182,
     183,     0,     0,    90,    91,   184,   185,    92,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    93,
       0,     0,    94,     0,   186,   187,   188,     0,     0,     0,
       0,     0,    95,    96,    97,    98,     0,    99,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   100,     0,     0,
       0,     0,     0,   207,     0,     0,   208,   209,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   101,     0,     0,
     102,     0,     0,   103,     0,     0,     0,     0,     0,   104,
       0,     0,     0,     0,   105,   106,   107,     0,     0,     0,
       0,     0,     0,   108,     0,   109,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   110,     0,   750,   111,     0,
       0,   112,   113,   114,     0,   115,   116,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   117,   118,     0,     0,   119,     0,   120,   121,
     122,   123,   124,   125,   126,  1998,   127,     0,   128,   129,
     130,   131,     0,   132,     0,   133,     0,     0,     0,     0,
     134,     0,     0,     0,   751,   752,   753,   754,   755,   756,
     757,   758,   759,   760,     0,     0,     0,   761,   762,   763,
       0,   764,   765,   766,   767,   768,   769,   770,   771,   772,
     773,     0,     0,     0,  1125,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   135,   136,
       0,     0,     0,   137,     0,     0,   138,     0,     0,     0,
     139,   140,   141,   142,   143,     0,     0,     0,     0,     0,
       0,   144,     0,     0,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,     0,   157,     0,     0,
       0,     0,     0,     0,   158,     0,     0,   159,     0,     0,
       0,   160,     0,     0,   161,   162,     0,   163,     0,     0,
     164,     0,   165,     0,     0,     0,   166,   167,     0,     0,
       0,     0,     0,     0,   168,   169,   170,   171,   172,   173,
       0,   174,   175,   176,     0,   177,     0,     0,     0,     0,
     178,   179,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    85,    86,    87,    88,
      89,     0,     0,     0,     0,   180,   181,     0,   182,   183,
       0,     0,    90,    91,   184,   185,    92,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    93,     0,
       0,    94,     0,   186,   187,   188,     0,     0,     0,     0,
       0,    95,    96,    97,    98,     0,    99,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   100,     0,     0,     0,
       0,     0,   207,     0,     0,   208,   209,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   101,     0,     0,   102,
       0,     0,   103,     0,     0,     0,     0,     0,   104,     0,
       0,     0,     0,   105,   106,   107,     0,     0,     0,     0,
       0,     0,   108,     0,   109,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   110,   750,     0,   111,     0,     0,
     112,   113,   114,     0,   115,   116,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   117,   118,     0,     0,   119,     0,   120,   121,   122,
     123,   124,   125,   126,     0,   127,     0,   128,   129,   130,
     131,     0,   132,     0,   133,     0,     0,     0,     0,   134,
     705,     0,   751,   752,   753,   754,   755,   756,   757,   758,
     759,   760,     0,     0,     0,   761,   762,   763,     0,   764,
     765,   766,   767,   768,   769,   770,   771,   772,   773,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   135,   136,     0,
       0,     0,   137,     0,     0,   138,     0,     0,     0,   139,
     140,   141,   142,   143,     0,     0,     0,     0,     0,     0,
     144,     0,     0,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,     0,   157,     0,     0,     0,
       0,     0,     0,   158,     0,     0,   159,     0,     0,     0,
     160,     0,     0,   161,   162,     0,   163,     0,     0,   164,
       0,   165,     0,     0,     0,   166,   167,     0,     0,     0,
       0,     0,     0,   168,   169,   170,   171,   172,   173,     0,
     174,   175,   176,     0,   177,     0,     0,     0,     0,   178,
     179,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    85,    86,    87,    88,  1124,
       0,     0,     0,     0,   180,   181,     0,   182,   183,     0,
       0,    90,    91,   184,   185,    92,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    93,     0,     0,
      94,     0,   186,   187,   188,     0,     0,     0,     0,     0,
      95,    96,    97,    98,     0,    99,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   100,     0,     0,     0,     0,
       0,   207,     0,     0,   208,   209,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   101,     0,     0,   102,     0,
       0,   103,     0,     0,     0,     0,     0,   104,     0,     0,
       0,     0,   105,   106,   107,     0,     0,     0,     0,     0,
       0,   108,     0,   109,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   110,     0,     0,   111,     0,     0,   112,
     113,   114,     0,   115,   116,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     117,   118,     0,     0,   119,     0,   120,   121,   122,   123,
     124,   125,   126,     0,   127,     0,   128,   129,   130,   131,
       0,   132,     0,   133,     0,     0,     0,     0,   134,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1587,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   135,   136,     0,     0,
       0,   137,     0,     0,   138,     0,     0,     0,   139,   140,
     141,   142,   143,     0,     0,     0,     0,     0,     0,   144,
       0,     0,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,     0,   157,     0,     0,     0,     0,
       0,     0,   158,     0,     0,   159,     0,     0,     0,   160,
       0,     0,   161,   162,     0,   163,     0,     0,   164,     0,
     165,     0,     0,     0,   166,   167,     0,     0,     0,     0,
       0,     0,   168,   169,   170,   171,   172,   173,     0,   174,
     175,   176,     0,   177,     0,     0,     0,     0,   178,   179,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    85,    86,    87,    88,    89,     0,
       0,     0,     0,   180,   181,     0,   182,   183,     0,     0,
      90,    91,   184,   185,    92,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    93,     0,     0,    94,
       0,   186,   187,   188,     0,     0,     0,     0,     0,    95,
      96,    97,    98,     0,    99,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   100,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   101,     0,     0,   102,     0,     0,
     103,     0,     0,     0,     0,     0,   104,     0,     0,     0,
       0,   105,   106,   107,     0,     0,     0,     0,     0,     0,
     108,     0,   109,     0,     0,  2205,  2206,     0,  2207,     0,
       0,     0,   110,     0,     0,   111,     0,     0,   112,   113,
     114,     0,   115,   116,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   117,
     118,     0,     0,   119,     0,   120,   121,   122,   123,   124,
     125,   126,     0,   127,     0,   128,   129,   130,   131,     0,
     132,     0,   133,     0,     0,     0,     0,   134,  2208,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   135,   136,     0,     0,     0,
     137,     0,     0,   138,     0,     0,     0,   139,   140,   141,
     142,   143,     0,     0,     0,     0,     0,     0,   144,     0,
       0,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,     0,   157,     0,     0,     0,     0,     0,
       0,   158,     0,     0,   159,     0,     0,     0,   160,     0,
       0,   161,   162,     0,   163,     0,     0,   164,     0,   165,
       0,     0,     0,   166,   167,     0,     0,     0,     0,     0,
       0,   168,   169,   170,   171,   172,   173,     0,   174,   175,
     176,     0,   177,     0,     0,     0,     0,   178,   179,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    85,    86,    87,    88,    89,     0,     0,
       0,     0,   180,   181,     0,   182,   183,     0,     0,    90,
      91,   184,   185,    92,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    93,     0,     0,    94,     0,
     186,   187,   188,     0,     0,     0,     0,     0,    95,    96,
      97,    98,     0,    99,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   100,     0,     0,     0,     0,     0,   207,
       0,     0,   208,   209,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   101,     0,     0,   102,     0,     0,   103,
       0,     0,     0,     0,     0,   104,     0,     0,     0,     0,
     105,   106,   107,     0,     0,     0,     0,     0,     0,   108,
       0,   109,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   110,     0,     0,   111,     0,     0,   112,   113,   114,
       0,   115,   116,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   117,   118,
       0,     0,   119,     0,   120,   121,   122,   123,   124,   125,
     126,     0,   127,     0,   128,   129,   130,   131,     0,   132,
       0,   133,     0,     0,     0,     0,   134,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   135,   136,     0,     0,     0,   137,
       0,     0,   138,     0,     0,     0,   139,   140,   141,   142,
     143,     0,     0,     0,     0,     0,     0,   144,     0,     0,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,     0,   157,     0,     0,     0,     0,     0,     0,
     158,     0,     0,   159,     0,     0,     0,   160,     0,     0,
     161,   162,     0,   163,     0,     0,   164,     0,   165,     0,
       0,     0,   166,   167,     0,     0,     0,     0,     0,     0,
     168,   169,   170,   171,   172,   173,     0,   174,   175,   176,
       0,   177,     0,     0,     0,     0,   178,   179,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    85,    86,    87,    88,    89,     0,     0,     0,
       0,   180,   181,     0,   182,   183,     0,     0,    90,    91,
     184,   185,    92,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    93,     0,     0,    94,     0,   186,
     187,   188,     0,     0,     0,     0,     0,    95,    96,    97,
      98,     0,    99,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   100,     0,     0,     0,     0,   202,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   101,     0,     0,   102,     0,     0,   103,     0,
       0,     0,     0,     0,   104,     0,     0,     0,     0,   105,
     106,   107,     0,     0,     0,     0,     0,     0,   108,     0,
     109,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     110,     0,     0,   111,     0,     0,   112,   113,   114,     0,
     115,   116,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   117,   118,     0,
       0,   119,     0,   120,   121,   122,   123,   124,   125,   126,
       0,   127,     0,   128,   129,   130,   131,     0,   132,     0,
     133,     0,     0,     0,     0,   134,    13,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   135,   136,     0,     0,     0,   137,     0,
       0,   138,     0,     0,     0,   139,   140,   141,   142,   143,
       0,     0,     0,     0,     0,     0,   144,     0,     0,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,     0,   157,     0,     0,     0,     0,     0,     0,   158,
       0,     0,   159,     0,     0,     0,   160,     0,     0,   161,
     162,     0,   163,     0,     0,   164,     0,   165,     0,     0,
       0,   166,   167,     0,     0,    35,     0,     0,     0,   168,
     169,   170,   171,   172,   173,     0,   174,   175,   176,     0,
     177,     0,     0,     0,     0,   178,   179,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    85,    86,    87,    88,  1124,     0,     0,     0,     0,
     180,   181,     0,   182,   183,     0,     0,    90,    91,   184,
     185,    92,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    93,     0,     0,    94,     0,   186,   187,
     188,     0,     0,     0,     0,     0,    95,    96,    97,    98,
       0,    99,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   100,     0,     0,     0,     0,     0,   207,     0,     0,
     208,   209,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   101,     0,     0,   102,     0,     0,   103,     0,     0,
       0,     0,     0,   104,     0,     0,     0,     0,   105,   106,
     107,     0,     0,     0,     0,     0,     0,   108,     0,   109,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   110,
       0,     0,   111,     0,     0,   112,   113,   114,     0,   115,
     116,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   117,   118,     0,     0,
     119,     0,   120,   121,   122,   123,   124,   125,   126,     0,
     127,     0,   128,   129,   130,   131,     0,   132,     0,   133,
       0,     0,     0,     0,   134,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   135,   136,     0,     0,     0,   137,     0,     0,
     138,     0,     0,     0,   139,   140,   141,   142,   143,     0,
       0,     0,     0,     0,     0,   144,     0,     0,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
       0,   157,     0,     0,     0,     0,     0,     0,   158,     0,
       0,   159,     0,     0,     0,   160,     0,     0,   161,   162,
       0,   163,     0,     0,   164,     0,   165,     0,     0,     0,
     166,   167,     0,     0,     0,     0,     0,     0,   168,   169,
     170,   171,   172,   173,     0,   174,   175,   176,     0,   177,
       0,     0,     0,     0,   178,   179,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      85,    86,    87,    88,    89,     0,     0,     0,     0,   180,
     181,     0,   182,   183,     0,     0,    90,    91,   184,   185,
      92,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    93,     0,     0,    94,     0,   186,   187,   188,
       0,     0,     0,     0,     0,    95,    96,    97,    98,     0,
      99,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     100,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     101,     0,     0,   102,     0,     0,   103,     0,     0,     0,
       0,     0,   104,     0,     0,     0,     0,   105,   106,   107,
       0,     0,     0,     0,     0,     0,   108,     0,   109,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   110,     0,
       0,   111,     0,     0,   112,   113,   114,     0,   115,   116,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   117,   118,     0,     0,   119,
       0,   120,   121,   122,   123,   124,   125,   126,     0,   127,
       0,   128,   129,   130,   131,     0,   132,     0,   133,     0,
       0,     0,     0,   134,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1458,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   135,   136,     0,     0,     0,   137,     0,     0,   138,
       0,  1459,     0,   139,   140,   141,   142,   143,     0,     0,
       0,     0,     0,     0,   144,     0,     0,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,     0,
     157,     0,     0,     0,     0,     0,     0,   158,     0,     0,
     159,     0,     0,     0,   160,     0,     0,   161,   162,     0,
     163,     0,     0,   164,     0,   165,     0,     0,     0,   166,
     167,     0,     0,     0,     0,     0,     0,   168,   169,   170,
     171,   172,   173,     0,   174,   175,   176,     0,   177,     0,
       0,     0,     0,   178,   179,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    85,
      86,    87,    88,    89,     0,     0,     0,     0,   180,   181,
       0,   182,   183,     0,     0,    90,    91,   184,   185,    92,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    93,     0,     0,    94,     0,   186,   187,   188,     0,
       0,     0,     0,     0,    95,    96,    97,    98,     0,    99,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   100,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   101,
       0,     0,   102,     0,     0,   103,     0,     0,     0,     0,
       0,   104,     0,     0,     0,     0,   105,   106,   107,     0,
       0,     0,     0,     0,     0,   108,     0,   109,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   110,     0,     0,
     111,     0,     0,   112,   113,   114,     0,   115,   116,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   117,   118,     0,     0,   119,     0,
     120,   121,   122,   123,   124,   125,   126,     0,   127,     0,
     128,   129,   130,   131,     0,   132,     0,   133,     0,     0,
       0,     0,   134,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     135,   136,     0,     0,     0,   137,     0,     0,   138,     0,
       0,     0,   139,   140,   141,   142,   143,     0,     0,     0,
       0,     0,     0,   144,     0,     0,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,     0,   157,
       0,     0,     0,     0,     0,     0,   158,     0,     0,   159,
       0,     0,     0,   160,     0,     0,   161,   162,     0,   163,
       0,     0,   164,   537,   165,     0,     0,     0,   166,   167,
       0,     0,     0,     0,     0,     0,   168,   169,   170,   171,
     172,   173,     0,   174,   175,   176,     0,   177,     0,     0,
       0,     0,   178,   179,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    85,    86,
      87,    88,    89,     0,     0,     0,     0,   180,   181,     0,
     182,   183,     0,     0,    90,    91,   184,   185,    92,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      93,     0,     0,    94,     0,   186,   187,   188,     0,     0,
       0,     0,     0,    95,    96,    97,    98,     0,    99,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   100,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   101,     0,
       0,   102,     0,     0,   103,     0,     0,     0,     0,     0,
     104,     0,     0,     0,     0,   105,   106,   107,     0,     0,
       0,     0,     0,     0,   108,     0,   109,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   110,     0,     0,   111,
       0,     0,   112,   113,   114,     0,   115,   116,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   117,   118,     0,     0,   119,     0,   120,
     121,   122,   123,   124,   125,   126,     0,   127,     0,   128,
     129,   130,   131,     0,   132,     0,   133,     0,     0,     0,
       0,   134,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   735,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   135,
     136,     0,     0,     0,   137,     0,     0,   138,     0,     0,
       0,   139,   140,   141,   142,   143,     0,     0,     0,     0,
       0,     0,   144,     0,     0,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,     0,   157,     0,
       0,     0,     0,     0,     0,   158,     0,     0,   159,     0,
       0,     0,   160,     0,     0,   161,   162,     0,   163,     0,
       0,   164,     0,   165,     0,     0,     0,   166,   167,     0,
       0,     0,     0,     0,     0,   168,   169,   170,   171,   172,
     173,     0,   174,   175,   176,     0,   177,     0,     0,     0,
       0,   178,   179,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    85,    86,    87,
      88,    89,     0,     0,     0,     0,   180,   181,     0,   182,
     362,     0,     0,    90,    91,   184,   185,    92,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    93,
       0,     0,    94,     0,   186,   187,   188,     0,     0,     0,
       0,     0,    95,    96,    97,    98,     0,    99,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   100,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   101,     0,     0,
     102,     0,     0,   103,     0,     0,     0,     0,     0,   104,
       0,     0,     0,     0,   105,   106,   107,     0,     0,     0,
       0,     0,     0,   108,     0,   109,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   110,     0,     0,   111,     0,
       0,   112,   113,   114,     0,   115,   116,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   117,   118,     0,     0,   119,     0,   120,   121,
     122,   123,   124,   125,   126,     0,   127,     0,   128,   129,
     130,   131,     0,   132,     0,   133,     0,     0,     0,     0,
     134,   502,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   135,   136,
       0,     0,     0,   137,     0,     0,   138,     0,     0,     0,
     139,   140,   141,   142,   143,     0,     0,     0,     0,     0,
       0,   144,     0,     0,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,     0,   157,     0,     0,
       0,     0,     0,     0,   158,     0,     0,   159,     0,     0,
       0,   160,     0,     0,   161,   162,     0,   163,     0,     0,
     164,     0,   165,     0,     0,     0,   166,   167,     0,     0,
       0,     0,     0,     0,   168,   169,   170,   171,   172,   173,
       0,   174,   175,   176,     0,   177,     0,     0,     0,     0,
     178,   179,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    85,    86,    87,    88,
      89,     0,     0,     0,     0,   180,   181,     0,   182,   183,
       0,     0,    90,    91,   184,   185,    92,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    93,     0,
       0,    94,     0,   186,   187,   188,     0,     0,     0,     0,
       0,    95,    96,    97,    98,     0,    99,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   100,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   101,     0,     0,   102,
       0,     0,   103,     0,     0,     0,     0,     0,   104,     0,
       0,     0,     0,   105,   106,   107,     0,     0,     0,     0,
       0,     0,   108,     0,   109,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   110,     0,     0,   111,     0,     0,
     112,   113,   114,     0,   115,   116,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   117,   118,     0,     0,   119,     0,   120,   121,   122,
     123,   124,   125,   126,     0,   127,     0,   128,   129,   130,
     131,     0,   132,     0,   133,     0,     0,     0,     0,   134,
    1122,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   135,   136,     0,
       0,     0,   137,     0,     0,   138,     0,     0,     0,   139,
     140,   141,   142,   143,     0,     0,     0,     0,     0,     0,
     144,     0,     0,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,     0,   157,     0,     0,     0,
       0,     0,     0,   158,     0,     0,   159,     0,     0,     0,
     160,     0,     0,   161,   162,     0,   163,     0,     0,   164,
       0,   165,     0,     0,     0,   166,   167,     0,     0,     0,
       0,     0,     0,   168,   169,   170,   171,   172,   173,     0,
     174,   175,   176,     0,   177,     0,     0,     0,     0,   178,
     179,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    85,    86,    87,    88,    89,
       0,     0,     0,     0,   180,   181,     0,   182,   183,     0,
       0,    90,    91,   184,   185,    92,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    93,     0,     0,
      94,     0,   186,   187,   188,     0,     0,     0,     0,     0,
      95,    96,    97,    98,     0,    99,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   100,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   101,     0,     0,   102,     0,
       0,   103,     0,     0,     0,     0,     0,   104,     0,     0,
       0,     0,   105,   106,   107,     0,     0,     0,     0,     0,
       0,   108,     0,   109,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   110,     0,     0,   111,     0,     0,   112,
     113,   114,     0,   115,   116,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     117,   118,     0,     0,   119,     0,   120,   121,   122,   123,
     124,   125,   126,     0,   127,     0,   128,   129,   130,   131,
       0,   132,     0,   133,     0,     0,     0,     0,   134,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1230,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   135,   136,     0,     0,
       0,   137,     0,     0,   138,     0,     0,     0,   139,   140,
     141,   142,   143,     0,     0,     0,     0,     0,     0,   144,
       0,     0,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,     0,   157,     0,     0,     0,     0,
       0,     0,   158,     0,     0,   159,     0,     0,     0,   160,
       0,     0,   161,   162,     0,   163,     0,     0,   164,     0,
     165,     0,     0,     0,   166,   167,     0,     0,     0,     0,
       0,     0,   168,   169,   170,   171,   172,   173,     0,   174,
     175,   176,     0,   177,     0,     0,     0,     0,   178,   179,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    85,    86,    87,    88,    89,     0,
       0,     0,     0,   180,   181,     0,   182,   183,     0,     0,
      90,    91,   184,   185,    92,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    93,     0,     0,    94,
       0,   186,   187,   188,     0,     0,     0,     0,     0,    95,
      96,    97,    98,     0,    99,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   100,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   101,     0,     0,   102,     0,     0,
     103,     0,     0,     0,     0,     0,   104,     0,     0,     0,
       0,   105,   106,   107,     0,     0,     0,     0,     0,     0,
     108,     0,   109,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   110,     0,     0,   111,     0,     0,   112,   113,
     114,     0,   115,   116,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   117,
     118,     0,     0,   119,     0,   120,   121,   122,   123,   124,
     125,   126,     0,   127,     0,   128,   129,   130,   131,     0,
     132,     0,   133,     0,     0,     0,     0,   134,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   135,   136,     0,     0,     0,
     137,     0,     0,   138,     0,  1459,     0,   139,   140,   141,
     142,   143,     0,     0,     0,     0,     0,     0,   144,     0,
       0,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,     0,   157,     0,     0,     0,     0,     0,
       0,   158,     0,     0,   159,     0,     0,     0,   160,     0,
       0,   161,   162,     0,   163,     0,     0,   164,     0,   165,
       0,     0,     0,   166,   167,     0,     0,     0,     0,     0,
       0,   168,   169,   170,   171,   172,   173,     0,   174,   175,
     176,     0,   177,     0,     0,     0,     0,   178,   179,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    85,    86,    87,    88,    89,     0,     0,
       0,     0,   180,   181,     0,   182,   183,     0,     0,    90,
      91,   184,   185,    92,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    93,     0,     0,    94,     0,
     186,   187,   188,     0,     0,     0,     0,     0,    95,    96,
      97,    98,     0,    99,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   100,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   101,     0,     0,   102,     0,     0,   103,
       0,     0,     0,     0,     0,   104,     0,     0,     0,     0,
     105,   106,   107,     0,     0,     0,     0,     0,     0,   108,
       0,   109,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   110,     0,     0,   111,     0,     0,   112,   113,   114,
       0,   115,   116,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   117,   118,
       0,     0,   119,     0,   120,   121,   122,   123,   124,   125,
     126,     0,   127,     0,   128,   129,   130,   131,     0,   132,
       0,   133,     0,     0,     0,     0,   134,  2107,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   135,   136,     0,     0,     0,   137,
       0,     0,   138,     0,     0,     0,   139,   140,   141,   142,
     143,     0,     0,     0,     0,     0,     0,   144,     0,     0,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,     0,   157,     0,     0,     0,     0,     0,     0,
     158,     0,     0,   159,     0,     0,     0,   160,     0,     0,
     161,   162,     0,   163,     0,     0,   164,     0,   165,     0,
       0,     0,   166,   167,     0,     0,     0,     0,     0,     0,
     168,   169,   170,   171,   172,   173,     0,   174,   175,   176,
       0,   177,     0,     0,     0,     0,   178,   179,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    85,    86,    87,    88,    89,     0,     0,     0,
       0,   180,   181,     0,   182,   183,     0,     0,    90,    91,
     184,   185,    92,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    93,     0,     0,    94,     0,   186,
     187,   188,     0,     0,     0,     0,     0,    95,    96,    97,
      98,     0,    99,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   100,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   101,     0,     0,   102,     0,     0,   103,     0,
       0,     0,     0,     0,   104,     0,     0,     0,     0,   105,
     106,   107,     0,     0,     0,     0,     0,     0,   108,     0,
     109,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     110,     0,     0,   111,     0,     0,   112,   113,   114,     0,
     115,   116,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   117,   118,     0,
       0,   119,     0,   120,   121,   122,   123,   124,   125,   126,
       0,   127,     0,   128,   129,   130,   131,     0,   132,     0,
     133,     0,     0,     0,     0,   134,     0,  2276,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   135,   136,     0,     0,     0,   137,     0,
       0,   138,     0,     0,     0,   139,   140,   141,   142,   143,
       0,     0,     0,     0,     0,     0,   144,     0,     0,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,     0,   157,     0,     0,     0,     0,     0,     0,   158,
       0,     0,   159,     0,     0,     0,   160,     0,     0,   161,
     162,     0,   163,     0,     0,   164,     0,   165,     0,     0,
       0,   166,   167,     0,     0,     0,     0,     0,     0,   168,
     169,   170,   171,   172,   173,     0,   174,   175,   176,     0,
     177,     0,     0,     0,     0,   178,   179,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    85,    86,    87,    88,    89,     0,     0,     0,     0,
     180,   181,     0,   182,   183,     0,     0,    90,    91,   184,
     185,    92,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    93,     0,     0,    94,     0,   186,   187,
     188,     0,     0,     0,     0,     0,    95,    96,    97,    98,
       0,    99,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   100,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   101,     0,     0,   102,     0,     0,   103,     0,     0,
       0,     0,     0,   104,     0,     0,     0,     0,   105,   106,
     107,     0,     0,     0,     0,     0,     0,   108,     0,   109,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   110,
       0,     0,   111,     0,     0,   112,   113,   114,     0,   115,
     116,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   117,   118,     0,     0,
     119,     0,   120,   121,   122,   123,   124,   125,   126,     0,
     127,     0,   128,   129,   130,   131,     0,   132,     0,   133,
       0,     0,     0,     0,   134,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   135,   136,     0,     0,     0,   137,     0,     0,
     138,     0,     0,     0,   139,   140,   141,   142,   143,     0,
       0,     0,     0,     0,     0,   144,     0,     0,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
       0,   157,     0,     0,     0,     0,     0,     0,   158,     0,
       0,   159,     0,     0,     0,   160,     0,     0,   161,   162,
       0,   163,     0,     0,   164,     0,   165,     0,     0,     0,
     166,   167,     0,     0,     0,     0,     0,     0,   168,   169,
     170,   171,   172,   173,     0,   174,   175,   176,     0,   177,
       0,     0,     0,     0,   178,   179,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      85,    86,    87,    88,    89,     0,     0,     0,     0,   180,
     181,     0,   182,   183,     0,     0,    90,    91,   184,   185,
      92,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    93,     0,     0,    94,     0,   186,   187,   188,
       0,     0,     0,     0,     0,    95,    96,    97,    98,     0,
      99,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     100,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     101,     0,     0,   102,     0,     0,   103,     0,     0,     0,
       0,     0,   104,     0,     0,     0,     0,   105,   106,   107,
       0,     0,     0,     0,     0,     0,   108,     0,   109,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   110,     0,
       0,   111,     0,     0,   112,   113,   114,     0,   115,   116,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   117,   118,     0,     0,   119,
       0,   120,   121,   122,   123,   124,   125,   126,     0,   127,
       0,   128,   129,   130,   131,     0,   132,     0,   133,     0,
       0,     0,     0,   134,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   135,   136,     0,     0,     0,   137,     0,     0,   138,
       0,     0,     0,   139,   140,   141,   142,   143,     0,     0,
       0,     0,     0,     0,   144,     0,     0,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,     0,
     157,     0,     0,     0,     0,     0,     0,   158,     0,     0,
     159,     0,     0,     0,   160,     0,     0,   161,   162,     0,
     163,     0,     0,   164,     0,   165,     0,     0,     0,   219,
     167,     0,     0,     0,     0,     0,     0,   168,   169,   170,
     171,   172,   173,     0,   174,   175,   176,     0,   177,     0,
       0,     0,     0,   178,   179,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    85,
      86,    87,    88,    89,     0,     0,     0,     0,   180,   181,
       0,   182,   183,     0,     0,    90,    91,   184,   185,    92,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    93,     0,     0,    94,     0,   186,   187,   188,     0,
       0,     0,     0,     0,    95,    96,    97,    98,     0,    99,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   100,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   101,
       0,     0,   102,     0,     0,   103,     0,     0,     0,     0,
       0,   104,     0,     0,     0,     0,   105,   106,   107,     0,
       0,     0,     0,     0,     0,   108,     0,   109,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   110,     0,     0,
     111,     0,     0,   112,   113,   114,     0,   115,   116,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   117,   118,     0,     0,   119,     0,
     120,   121,   122,   123,   124,   125,   126,     0,   127,     0,
     128,   129,   130,   131,     0,   132,     0,   133,     0,     0,
       0,     0,   134,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     135,   136,     0,     0,     0,   137,     0,     0,   138,     0,
       0,     0,   139,   140,   141,   142,   143,     0,     0,     0,
       0,     0,     0,   144,     0,     0,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,     0,   157,
       0,     0,     0,     0,     0,     0,   158,     0,     0,   159,
       0,     0,     0,   160,     0,     0,   161,   162,     0,   163,
       0,     0,   164,     0,   165,     0,     0,     0,   166,   167,
       0,     0,     0,     0,     0,     0,   168,   169,   170,   171,
     172,   173,     0,   174,   175,   176,     0,   177,     0,     0,
       0,     0,   178,   179,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    85,    86,
      87,    88,    89,     0,     0,     0,     0,   180,   181,     0,
     182,   362,     0,     0,    90,    91,   184,   185,    92,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      93,     0,     0,    94,     0,   186,   187,   188,     0,     0,
       0,     0,     0,    95,    96,    97,    98,     0,    99,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   100,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   101,     0,
       0,   102,     0,     0,   103,     0,     0,     0,     0,     0,
     104,     0,     0,     0,     0,   105,   106,   107,     0,     0,
       0,     0,     0,     0,   108,     0,   109,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   110,     0,     0,   111,
       0,     0,   112,   113,   114,     0,   115,   116,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   117,   118,     0,     0,   119,     0,   120,
     121,   122,   123,   124,   125,   126,     0,   127,     0,   128,
     129,   130,   131,     0,   132,     0,   133,     0,     0,     0,
       0,   134,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   135,
     136,     0,     0,     0,   137,     0,     0,   902,     0,     0,
       0,   139,   140,   141,   142,   143,     0,     0,     0,     0,
       0,     0,   144,     0,     0,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,     0,   157,     0,
       0,     0,     0,     0,     0,   158,     0,     0,   159,     0,
       0,     0,   160,     0,     0,   161,   162,     0,   163,     0,
       0,   164,     0,   165,     0,     0,     0,   166,   167,     0,
       0,     0,     0,     0,     0,   168,   169,   170,   171,   172,
     173,     0,   174,   175,   176,     0,   177,     0,     0,     0,
       0,   178,   179,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    85,    86,    87,
      88,    89,     0,     0,     0,     0,   180,   181,     0,   182,
     183,     0,     0,    90,    91,   184,   185,    92,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    93,
       0,     0,    94,     0,   186,   187,   188,     0,     0,     0,
       0,     0,    95,    96,    97,    98,     0,    99,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   100,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   101,     0,     0,
     102,     0,     0,   103,     0,     0,     0,     0,     0,   104,
       0,     0,     0,     0,   105,   106,   107,     0,     0,     0,
       0,     0,     0,   108,     0,   109,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   110,     0,     0,   111,     0,
       0,   112,   113,   114,     0,   115,   116,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   117,   118,     0,     0,   119,     0,   120,   121,
     122,   123,   124,   125,   126,     0,   127,     0,   128,   129,
     130,   131,     0,   132,     0,   133,     0,     0,     0,     0,
     134,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   135,   136,
       0,     0,     0,   137,     0,     0,   138,     0,     0,     0,
     139,   140,   141,   142,   143,     0,     0,     0,     0,     0,
       0,   144,     0,     0,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,     0,   157,     0,     0,
       0,     0,     0,     0,   158,     0,     0,   159,     0,     0,
       0,   160,     0,     0,   161,   162,     0,   163,     0,     0,
     164,     0,   165,     0,     0,     0,   166,   167,     0,     0,
       0,     0,     0,     0,   168,   169,   170,   171,   172,   173,
       0,   174,   175,   176,     0,   177,     0,     0,     0,     0,
     178,   179,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    85,    86,    87,    88,
      89,     0,     0,     0,     0,   180,   181,     0,   182,  1348,
       0,     0,    90,    91,   184,   185,    92,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    93,     0,
       0,    94,     0,   186,   187,   188,     0,     0,     0,     0,
       0,    95,    96,    97,    98,     0,    99,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   100,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   101,     0,     0,   102,
       0,     0,   103,     0,     0,     0,     0,     0,   104,     0,
       0,     0,     0,   105,   106,   107,     0,     0,     0,     0,
       0,     0,   108,     0,   109,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   110,     0,     0,   111,     0,     0,
     112,   113,   114,     0,   115,   116,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   117,   118,     0,     0,   119,     0,   120,   121,   122,
     123,   124,   125,   126,     0,   127,     0,   128,   129,   130,
     131,     0,   132,     0,   133,     0,     0,     0,     0,   134,
       0,     0,     0,     0,     0,     0,   622,   623,   624,   625,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     626,     0,     0,     0,   627,   628,   629,   381,   382,   630,
     631,   632,   633,   634,   635,   636,   637,   638,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   135,   136,     0,
       0,     0,   137,     0,     0,   138,   639,   640,   641,   139,
     140,   141,   142,   143,     0,     0,     0,     0,     0,     0,
     144,     0,     0,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,     0,   157,     0,     0,     0,
       0,     0,     0,   158,     0,     0,   159,     0,     0,     0,
     160,     0,     0,   161,  2137,     0,   163,     0,     0,   164,
       0,   165,     0,     0,     0,   166,   167,     0,     0,     0,
       0,     0,     0,   168,   169,   170,   171,   172,   173,     0,
     174,   175,   176,     0,   177,     0,     0,     0,     0,   178,
     179,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     3,     4,     5,     6,     0,
       0,     0,     0,     0,   180,   181,     0,   182,   183,     7,
       8,     9,    10,   184,   185,     0,     0,     0,    11,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   186,   187,   188,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    13,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1807,     0,     0,     0,     0,
       0,     0,     0,   642,   643,   644,   645,     0,     0,     0,
       0,     0,     0,     0,     0,    14,     0,     0,     0,     0,
       0,     0,     0,     0,    15,    16,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    17,    18,     0,
      19,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    29,    30,     0,     0,     0,     0,     0,
      31,    32,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    33,     0,     0,    34,
       0,     0,     0,     0,     0,    35,     0,     0,    36,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    37,     0,    38
};

static const yytype_int16 yycheck[] =
{
       4,   282,   202,     0,   482,     9,   214,    18,   788,   891,
       0,   487,   482,   266,    18,    19,   848,     0,   684,   227,
     228,     0,   264,    41,   232,     0,    30,    18,   687,   731,
    1195,   346,    36,    46,   346,     0,   695,   644,  1438,     0,
     689,   685,    46,    47,   501,    31,   865,   663,   697,   331,
     346,   259,    44,    31,   346,   887,  1074,  1075,  1218,  1674,
     408,   409,    11,   222,  1218,   410,   411,  1968,    11,   603,
     663,    14,     0,  1793,    11,   853,   854,   775,   426,   777,
      84,     3,     4,    16,     3,     4,   643,   539,  1433,   522,
     684,  2063,  1052,    93,    89,   167,     3,     4,    16,  1056,
    1006,    71,  1008,  1058,     0,  1917,     6,     7,     8,     9,
      10,   196,    16,  1019,  1302,     0,    42,    43,   180,     3,
       4,   116,   337,   338,   339,     0,   196,   184,   196,   196,
     184,  1062,    51,    52,    53,    91,     4,   119,    69,    70,
      90,    72,   359,   180,     6,     7,     8,     9,    10,   122,
     196,    19,     0,   181,    13,   122,   180,     3,     4,    73,
     122,    69,    30,    89,    69,    70,    71,    72,   866,  2004,
     196,    75,    76,    77,  2075,    79,    80,  2102,    82,   134,
    2081,   119,    90,  1439,   195,   189,   297,   122,    89,   302,
     668,   195,   196,   196,    89,   811,   142,   201,   122,   297,
     204,   151,    60,   158,   195,  1849,   351,    65,  1852,   266,
     180,   370,   266,   430,   206,   219,    84,  1937,   215,   216,
     217,   218,    89,   122,   119,   215,   216,   217,   218,   719,
     233,   234,   215,   216,   217,   218,   215,   216,   217,   218,
     215,   216,   217,   218,   182,    72,   113,   251,   252,   334,
     215,   216,   217,   218,   215,   216,   217,   218,  2112,   327,
     327,   247,   375,   856,   282,  1425,  2191,    94,   182,   614,
     248,  1425,   489,   180,   257,   180,  2177,   375,   179,   276,
     284,   815,   180,   265,   288,  2186,   276,   215,   216,   217,
     218,   295,   296,   276,   364,     0,   180,   276,   180,     0,
     326,   276,   348,   375,   180,   309,   310,   466,   312,   313,
     314,   276,   316,   317,   376,   276,   569,   321,   788,   215,
     216,   217,   218,   315,   229,   782,  2138,   331,   196,   299,
     215,   216,   217,   218,   180,   335,   204,   268,  2310,   376,
     215,   216,   217,   218,   951,  1276,   245,   375,   276,  2203,
     698,   219,   376,  1541,  1969,   359,  1015,   973,   362,   267,
    2261,   365,  2263,   281,   290,  1453,   361,   215,   216,   217,
     218,   366,  1021,   655,  1334,  1332,  1632,   281,  1333,   913,
     276,   915,   916,   917,   252,   530,  1474,   287,   596,   737,
     738,   276,  1170,  1171,   299,   952,   611,  1303,   297,   747,
    1306,   276,   375,   836,   837,   264,   858,   340,   375,   257,
     867,   367,   274,   369,  1112,   277,  1114,  1454,   302,    11,
     288,  1119,  1120,   342,  2278,  1203,   430,   295,   276,  1131,
    2150,   380,  1777,  1778,   341,    27,   440,   380,  2273,  2274,
     375,   309,   310,   380,   312,  2089,   314,  2348,   316,   371,
     732,   375,   181,   321,   944,   945,   302,   196,  1277,    51,
      52,    53,   289,    59,   623,     3,     4,  2082,   295,  2323,
     375,   582,   583,   584,   585,   181,   487,   376,   376,    71,
      71,   592,  1454,   487,  1572,   489,    11,   491,   492,   493,
     494,   495,   496,   497,   376,  1655,   487,   501,   502,    59,
     376,  1655,     3,     4,     6,     7,     8,     9,    10,   196,
     215,   216,   217,   218,   215,   216,   217,   218,   181,   196,
     524,   181,   181,   181,   196,   181,    71,   111,   196,  1547,
    1548,   299,   524,   408,   122,   119,    89,   541,   542,   525,
     119,   278,   857,   521,    87,   857,   550,   196,   302,   408,
      69,    70,    71,    72,    69,    70,    71,    72,   811,   121,
     564,   857,    71,   567,   181,   857,   126,    69,    70,    71,
      72,   276,   440,   302,   889,   276,   160,   889,  1666,  1172,
    1173,   160,   167,   167,   196,   589,   590,   591,   180,   180,
     282,    85,   180,   889,   181,   181,   181,   889,   602,   367,
      71,   605,   606,   607,   181,   609,   610,  1644,   126,   278,
    1254,  1776,   616,  1519,   618,   619,   169,   621,   180,   172,
     295,   375,   181,   491,  1530,   493,   879,   495,   496,   497,
     161,  1537,   163,   646,  2034,   180,   375,  1339,   196,  1288,
     327,   181,   646,   161,   181,   163,   375,   962,    89,   326,
     962,   655,  1201,  1741,   246,   327,   524,   281,   326,   184,
     181,   195,   200,   201,   668,   184,   962,   181,   876,   375,
     962,   180,  1644,   181,   542,   271,   272,   180,   353,   180,
     684,  1029,   184,   375,    59,   181,   127,   128,  1282,   130,
     131,   132,   181,   181,   135,   126,   564,   572,   716,   567,
     718,  1049,   122,   360,  1238,     0,  1051,   299,   299,   180,
     302,   302,   375,   572,   371,   375,   375,   375,   181,   375,
     973,   255,   590,   181,  1072,  1073,   375,   731,   732,   289,
     322,   174,   163,    11,   602,   295,  2136,   605,   606,   607,
     731,   609,   610,   262,   263,   105,   181,   262,   263,   268,
    1915,   126,   181,   268,   299,   181,   265,   302,   375,   119,
     262,   263,   419,   375,   348,   776,   268,    93,   181,   288,
     174,   775,   776,   288,   778,    75,    76,    77,   782,    79,
      80,   785,    82,   181,   196,   776,   288,   122,   375,   375,
     299,   375,  1952,   302,   265,   142,   181,  1275,   375,   174,
     181,   244,   245,   246,   247,   462,   463,   196,   465,   184,
      89,  1360,  1405,    92,  1407,   142,   375,  1366,  1133,   338,
     181,  1133,   182,   698,   842,   829,  1171,   181,   299,   181,
     705,   302,    59,   708,  1500,   375,   338,  1133,   375,   698,
     244,   245,   246,   247,   199,   196,   705,   181,   127,   708,
    1443,   130,   131,   132,   375,   282,   135,   181,   278,     3,
       4,   375,   866,   867,   181,  1567,  1568,   375,   243,   244,
     245,   246,   247,   877,   408,   142,   181,  1536,   181,   375,
    1539,  1488,    89,    21,    22,  1501,   375,   375,   181,   423,
     894,   895,   896,   897,   114,   136,   300,  1354,   902,   126,
     141,   276,   181,   907,   270,   265,  1500,   348,   912,   566,
     181,   181,   375,   181,   289,  1372,   920,   375,  1233,   181,
     295,  1233,   181,   941,   279,   300,   785,   370,   295,  1274,
       3,     4,   122,   123,    39,    40,   302,  1233,   327,   957,
     375,  1233,   322,   278,   376,   349,   375,   174,   375,   375,
     198,   363,   364,   487,    62,   162,   347,   184,   165,   339,
      89,   829,   375,    92,  1279,  1280,   370,  1279,  1280,   215,
     216,   346,    77,   237,   349,   119,   327,   375,   982,     3,
       4,   281,  1224,  1279,  1280,    93,   353,  1279,  1280,  1197,
     375,   297,   267,   180,   375,   370,   237,  1001,   127,   189,
     119,   130,   131,   132,   375,  1009,   135,   181,   379,   877,
     181,  2171,  1016,   109,   375,   290,   243,   244,   245,   246,
     247,   375,   196,   375,   265,   196,   894,   895,   896,   897,
     276,   295,   296,    57,    94,   109,  1738,    97,   572,   907,
    1051,   375,   180,   103,   181,   376,   119,  1051,  1052,   276,
     167,   375,  1056,  1057,  1058,  1753,   181,  1061,   375,   196,
    1051,  1052,   180,   182,   181,   722,   254,   286,   295,   348,
     375,   196,   375,   300,   260,   261,  1610,  1611,  1612,   175,
     176,   177,   375,    20,   375,   181,   620,    24,    25,  1921,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,   175,   176,   177,   375,   375,   281,   375,   967,   968,
     969,    93,   326,   375,   328,   238,   375,   236,  1122,   346,
      57,    58,   349,   657,   375,   126,  1130,  1131,  1132,   282,
     318,   319,   320,  1001,   322,   323,  1140,   326,   269,   328,
    1131,   675,   676,   370,   267,  2055,   803,  2057,  2058,  2059,
     119,   274,   275,  1468,   285,   282,  1468,   375,   143,  1163,
     267,   128,   129,   270,   698,   331,   285,   298,    54,   288,
     293,    54,  1468,   174,   708,   180,  1468,  1052,  1189,   298,
    1658,    54,   143,   290,   278,  1189,   293,   294,   157,   723,
     159,   160,    11,   727,   728,   200,   201,   278,  1189,  1074,
    1075,   278,  1483,   180,  1052,   119,  1210,  1866,  1206,  1207,
    1208,  1209,  1216,    27,  1218,  1074,  1075,   295,  1222,   348,
     295,  1151,   136,  1153,  1154,  1223,   295,   141,  1470,   227,
     228,  1579,  1580,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   776,   244,   245,   246,   247,   295,     3,     4,
       5,     6,     7,     8,     9,   331,    11,    12,    13,    14,
      15,   222,   223,   224,   225,   226,   346,   924,   182,   926,
     295,  1275,    27,    28,    75,    76,    77,   245,  1282,  1283,
     245,    82,  1597,     3,     4,  1597,   943,   245,   289,    44,
      45,   130,   131,   132,   295,   296,   939,   940,   941,   300,
    1179,  1597,  1181,  1182,   175,   176,   177,    62,  1786,  1787,
     181,  2143,  1187,    94,   957,   958,   959,   960,   961,   245,
     101,   102,   236,   237,   235,   106,  1201,   376,  1332,  1333,
    1334,   865,   227,   228,   868,  1339,   744,   745,   746,  1187,
       3,     4,  1201,  1334,  1348,   346,  1816,   326,  1339,   328,
    1354,   265,    88,    89,  1222,   175,   176,   177,  1673,   376,
    1675,  1673,   376,  1675,   175,   176,   177,   320,  1372,   370,
     181,   285,     3,     4,   288,  1379,   183,  1673,  1035,  1675,
    1037,  1673,   309,  1675,   298,    17,   313,   183,   315,   316,
     317,   318,   183,   326,   331,   328,   309,   295,  1402,  1877,
     313,   295,   315,   316,   317,   318,  1410,  1411,  1412,  2003,
    2004,  1415,  1416,  1417,    42,    43,  1420,  1421,  2300,  1423,
    1424,  1425,    95,    96,    75,    76,    77,    59,    79,    80,
      62,    82,   351,   352,   175,   176,   177,   375,   375,   376,
     181,   975,   386,   387,   388,   389,  1457,   271,   272,  1453,
     366,   367,   368,  1457,  1458,  1459,   111,  1454,   321,  1334,
       3,     4,   107,   108,  1454,  1483,  1457,  1485,   290,  1487,
    1474,  1475,     3,  1477,  1492,  1334,   180,  1953,   110,   376,
     112,   200,   201,  1501,   180,  1360,  1334,   188,   189,    99,
     100,  1366,   296,   297,   126,   180,  1500,   295,   296,   344,
     345,  1360,    95,    96,    22,  1162,  1040,  1366,   180,  1043,
      75,    76,    77,  2107,    79,    80,    81,    82,  2112,   183,
     241,   242,   186,   187,   188,   189,  1454,  1531,   192,   193,
     194,   195,   355,   356,   180,   199,  1193,   180,  1886,   134,
    1074,  1075,   363,   364,  1412,   353,   354,   180,   303,   304,
     305,   306,   109,  1421,    69,    70,  1424,   180,  1454,    69,
      70,   412,   413,  1567,  1568,   217,   218,   418,  1572,  1454,
    1574,   354,   355,   661,   662,  2355,  1567,  1568,     6,     7,
       8,     9,    10,   180,   180,   142,   180,   198,   180,   180,
    1458,  1595,   180,   180,   180,   227,   228,   229,   230,   231,
     232,   180,   180,  2073,  1138,   180,   180,  1475,   180,  2203,
    1810,   243,   180,   180,  2208,   279,   180,   375,   175,   176,
     177,   180,   359,   297,   181,   279,   323,   183,   142,   142,
     186,   187,   188,   189,  1638,   138,   192,   193,   194,   195,
     138,   123,   198,   199,   276,   338,   123,  1644,   122,    98,
     104,  1655,   375,   191,  1644,   196,   180,   289,   180,   348,
     181,   278,  1666,   295,   322,   302,   298,  1201,   249,   142,
    1674,   190,  1547,  1548,   180,   302,   180,    38,   180,  2273,
    2274,   238,   178,   180,  2278,   180,   180,   322,  1547,  1548,
     183,   180,   180,   186,   187,   188,   189,  1701,   301,   192,
     193,   194,   195,   181,   180,   198,   199,   376,  1365,   180,
     267,   375,   180,    17,   346,   180,  1644,   274,   275,   186,
     187,   188,   189,   279,    23,   192,   193,   194,   195,  2323,
     123,  1265,   199,   250,  1738,   164,   293,  1741,   250,     3,
    1744,   181,   302,  1277,  1401,   370,   180,  1738,  1644,   180,
    2065,   213,   378,  2065,   299,    59,    88,  1761,    62,  1644,
      85,  1765,   122,    16,   321,   322,   323,   324,   376,  2065,
     180,  1775,   255,  2065,  1431,  1432,   111,   297,   180,   290,
     270,   273,  1439,   122,    27,  1442,   279,  1321,   339,   250,
     281,   277,   235,  1327,  1328,   302,  1330,   302,   348,   265,
     281,    23,   375,  1814,   111,   183,   110,   183,   112,   122,
    1814,   167,   279,   297,   376,   180,   109,   375,   375,   155,
     375,   337,   126,  1814,   181,   304,  1360,   181,   180,   279,
     180,   119,  1366,   143,   376,   181,   687,   688,   689,   180,
     277,  2049,   122,    94,   695,   289,   697,  2325,   274,   273,
     289,   297,   119,   340,   296,   273,   122,   180,    20,  1863,
     711,   712,   713,   183,   284,   246,   186,   187,   188,   189,
     350,   240,   192,   193,   194,   195,   348,   281,   181,   199,
     181,   181,   297,   181,   181,  2355,  2139,   181,   324,   181,
     375,   181,   743,   744,   745,   746,   181,   180,   111,   750,
     751,   752,   753,   754,   755,   756,   757,   758,   759,   760,
     761,   762,   763,   764,   765,   766,   767,   768,   769,   770,
     771,   772,   773,   227,   228,   229,   230,   231,   232,  1933,
     375,   181,   181,   181,   375,   348,   181,  2145,  2253,   243,
     375,  2253,  1953,   375,   170,   180,  1814,  1604,  1952,  1953,
    1954,   180,  2233,   320,   337,    81,   181,  2253,   181,   279,
     181,  2253,  1953,    81,    78,  1969,   180,  1624,   375,   348,
     116,  1628,   276,   143,   181,  1632,   376,   376,   360,   181,
    1637,   375,    16,   265,    96,   348,   282,  1991,   375,   284,
     122,   295,   360,   282,   298,   281,   180,   281,   181,  2003,
    2004,   248,   181,   290,   376,   265,   348,   152,   152,   181,
     181,  1886,   181,  1547,  1548,    81,   297,   180,   111,   180,
     115,  1555,   181,   302,   181,   181,  2030,  1886,   111,   109,
     356,   348,  2036,   180,   276,   297,   111,   375,   250,   280,
    2044,   375,   346,   213,   214,   215,   280,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,    83,   302,  2063,
    1594,   236,   181,   283,   181,  1933,  2063,   358,   181,   375,
     181,   180,   281,  2063,   181,   281,   281,   281,  2082,   181,
    2063,   181,   171,  2087,  2063,   273,   111,   360,  2063,   265,
     137,   302,   302,   180,   123,   282,   180,  2101,  2063,   375,
     375,   250,  2063,  2107,  2357,   377,   143,     6,  2112,   333,
     119,   119,   377,   119,   281,  1772,   281,   181,  2326,   181,
     180,   180,  1779,   375,   119,  2378,   326,   119,   288,   375,
     348,   289,   180,   179,    91,   375,    91,   280,  2142,   180,
     357,   326,   180,   375,   163,   348,   160,  2151,  2152,  2153,
    2154,     3,   165,   160,   353,   198,   180,    73,   119,   180,
    1011,   113,   180,   364,  1015,   362,   138,  2171,   180,  2173,
    1021,   337,   273,   278,  2178,   180,  2044,   372,   376,  2183,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     168,   142,   165,   162,   198,   131,   327,    63,   297,  2203,
       6,     7,     8,     9,  2208,   299,   180,   124,   335,   373,
     181,  1745,  1746,   337,    20,  2233,   142,   325,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,   180,   337,   180,   121,   365,   353,    64,   327,
     374,   181,   181,   273,  1901,   281,   142,   325,   180,  1906,
      56,    57,    58,    72,  2258,   337,  1913,  1791,   337,   290,
     130,   281,   302,   331,  2268,   281,   343,   180,   333,  2273,
    2274,   119,    69,   142,  2278,    70,   299,   375,    41,  1644,
      42,  1216,  1816,  1817,  1818,   307,   308,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   318,   319,  1390,   248,
     247,  1958,  1148,    47,   523,  2241,  2310,  2295,  2289,   525,
    2314,   858,  2316,  2310,  2290,  1425,  1655,  1621,  2341,  2323,
    2310,  2325,  2307,  2240,     0,     1,  1909,  2310,  2299,  2306,
    2310,  2310,  2080,  1965,  2080,  2310,  2365,  1947,  1946,   919,
    1597,     8,   524,   843,  1878,  2310,  2350,  1631,   199,  2310,
    2030,  2035,  1886,  2230,   257,   509,   257,  2126,  1892,  1900,
    1432,  2365,   257,  1897,   257,  2325,  1275,   868,  1343,   550,
     566,  2028,  1060,  1574,   978,  1909,  2007,   735,  2323,    55,
    1892,  2278,  1023,  1265,   974,  2042,  1744,   740,   747,  2214,
    1897,   776,    46,    69,    70,    71,    72,   726,   749,  1038,
     870,   856,   617,  1852,  1042,  2086,  1042,    83,    84,    85,
      86,  1850,  1693,  1529,  1866,  1518,    92,  1700,   696,  1953,
    1521,  1985,  2098,  2106,    -1,    -1,    -1,    -1,    -1,  1963,
      -1,    -1,    -1,  1284,    -1,    -1,  1970,  1288,    -1,    -1,
      -1,    -1,  1293,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1311,  1312,  1313,  1314,    -1,    -1,   142,    -1,    -1,    -1,
      -1,    -1,    -1,  2007,    -1,  2009,    -1,    -1,    -1,    -1,
    2137,    -1,    -1,    -1,    -1,    -1,  2020,  2144,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   303,   304,   305,
     306,    -1,    -1,    -1,   180,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  2047,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  2069,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  2078,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   229,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   238,   239,    -1,    -1,    -1,    -1,    -1,   375,
      -1,    -1,    -1,    -1,    -1,   251,   252,    -1,   254,    -1,
     256,   257,   258,   259,   260,   261,   262,   263,   264,    -1,
    2124,   267,   268,    -1,    -1,    -1,    -1,  2131,   274,   275,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  2141,    -1,    -1,
      -1,    -1,    -1,    -1,   290,    -1,    -1,   293,    -1,    -1,
      -1,    -1,    -1,   299,  2158,    -1,   302,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  2294,    -1,    -1,
      -1,  2298,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     336,    -1,   338,    -1,    -1,    -1,    -1,  1518,    -1,    -1,
    1521,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1529,    -1,
    2214,     6,     7,     8,     9,  1536,    -1,    -1,  1539,  2223,
      -1,    -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  2256,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    2264,    56,    57,    58,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     6,     7,     8,     9,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    20,  2290,    -1,    -1,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    56,    57,    58,    -1,    -1,    -1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      -1,    -1,    18,    19,   139,   140,    22,    23,    -1,    -1,
      26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    38,    -1,    -1,    41,    -1,    -1,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,  1700,
      56,    -1,    -1,    59,    60,    61,    -1,    -1,    -1,    65,
      66,    67,    68,    -1,    -1,    71,    72,    -1,    -1,    75,
      76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1730,
      86,    -1,  1733,    89,  1735,    -1,    92,    -1,    -1,    -1,
      -1,    -1,    98,    -1,    -1,    -1,    -1,   103,   104,   105,
      -1,    -1,    -1,    -1,    -1,    -1,   112,    -1,   114,    -1,
      -1,    -1,    -1,   119,   120,    -1,   181,    -1,   124,   125,
      -1,   127,    -1,    -1,   130,   131,   132,   133,   134,   135,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   144,   145,
     146,   147,    -1,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,    -1,   165,
     166,   167,   168,   169,   170,    -1,   172,   173,   174,    -1,
      -1,    -1,    -1,   179,   180,   181,   182,    -1,   303,   304,
     305,   306,    -1,    -1,   190,   191,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   200,   201,    -1,  1848,  1849,  1850,
      -1,  1852,    -1,    -1,   210,   211,   212,    -1,    -1,    -1,
      -1,   217,    -1,    -1,    -1,  1866,    -1,    -1,    -1,    -1,
      -1,   227,   228,    -1,    -1,    -1,   232,    -1,    -1,   235,
      -1,    -1,    -1,   239,   240,   241,   242,   243,   303,   304,
     305,   306,    -1,    -1,   250,    -1,    -1,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,    -1,
     266,    -1,    -1,    -1,    -1,    -1,    -1,   273,    -1,    -1,
     276,    -1,    -1,    -1,   280,    -1,    -1,   283,   284,    -1,
     286,    -1,    -1,   289,    -1,   291,    -1,    -1,    -1,   295,
     296,    -1,    -1,   299,    -1,    -1,   302,   303,   304,   305,
     306,   307,   308,    -1,   310,   311,   312,    -1,   314,    -1,
      -1,    -1,    -1,   319,   320,    -1,    -1,    -1,    -1,   325,
      -1,    -1,    -1,   329,   330,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   344,   345,
      -1,   347,   348,    -1,    -1,    -1,    -1,   353,   354,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   372,   373,   374,    -1,
      -1,    -1,   378,    -1,   380,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    -1,    -1,    18,    19,
      -1,    -1,    22,    23,    -1,    -1,    26,    27,    28,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,
      -1,    41,    -1,    -1,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,  2086,    56,    -1,  2089,    59,
      60,    61,    -1,    -1,    -1,    65,    66,    67,    68,    -1,
      -1,    71,    72,    -1,    -1,    75,    76,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    86,    -1,    -1,    89,
      -1,    -1,    92,    -1,    -1,    -1,    -1,    -1,    98,    -1,
      -1,    -1,    -1,   103,   104,   105,    -1,    -1,    -1,    -1,
      -1,    -1,   112,    -1,   114,    -1,    -1,    -1,    -1,   119,
     120,    -1,    -1,    -1,   124,   125,    -1,   127,    -1,    -1,
     130,   131,   132,   133,   134,   135,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   144,   145,   146,   147,    -1,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,    -1,   165,   166,   167,   168,   169,
     170,    -1,   172,   173,   174,    -1,    -1,    -1,    -1,   179,
     180,   181,   182,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     190,   191,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     200,   201,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     210,   211,   212,    -1,    -1,    -1,    -1,   217,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   227,   228,    -1,
      -1,    -1,   232,    -1,    -1,   235,    -1,    -1,    -1,   239,
     240,   241,   242,   243,    -1,    -1,    -1,    -1,    -1,    -1,
     250,    -1,    -1,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,    -1,   266,    -1,    -1,    -1,
      -1,    -1,    -1,   273,    -1,    -1,   276,    -1,    -1,    -1,
     280,    -1,    -1,   283,   284,    -1,   286,    -1,    -1,   289,
      -1,   291,    -1,    -1,    -1,   295,   296,    -1,    -1,   299,
      -1,    -1,   302,   303,   304,   305,   306,   307,   308,    -1,
     310,   311,   312,    -1,   314,    -1,    -1,    -1,    -1,   319,
     320,    -1,    -1,    -1,    -1,   325,    -1,    -1,    -1,   329,
     330,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   344,   345,    -1,   347,   348,    -1,
      -1,    -1,    -1,   353,   354,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   372,   373,   374,    -1,    -1,    -1,   378,    -1,
     380,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    -1,    -1,    18,    19,    -1,    -1,
      22,    23,    -1,    -1,    26,    27,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,    -1,    41,
      -1,    -1,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    -1,    56,    -1,    -1,    59,    60,    61,
      -1,    -1,    -1,    65,    66,    67,    68,    -1,    -1,    71,
      72,    -1,    -1,    75,    76,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    86,    -1,    -1,    89,    -1,    -1,
      92,    -1,    -1,    -1,    -1,    -1,    98,    -1,    -1,    -1,
      -1,   103,   104,   105,    -1,    -1,    -1,    -1,    -1,    -1,
     112,    -1,   114,    -1,    -1,    -1,    -1,   119,   120,    -1,
      -1,    -1,   124,   125,    -1,   127,    -1,    -1,   130,   131,
     132,   133,   134,   135,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   144,   145,   146,   147,    -1,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,    -1,   165,   166,   167,   168,   169,   170,    -1,
     172,   173,   174,    -1,    -1,    -1,    -1,   179,   180,    -1,
     182,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   190,   191,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   200,   201,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   210,   211,
     212,    -1,    -1,    -1,    -1,   217,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   227,   228,    -1,    -1,    -1,
     232,    -1,    -1,   235,    -1,    -1,    -1,   239,   240,   241,
     242,   243,    -1,    -1,    -1,    -1,    -1,    -1,   250,    -1,
      -1,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,    -1,   266,    -1,    -1,    -1,    -1,    -1,
      -1,   273,    -1,    -1,   276,    -1,    -1,    -1,   280,    -1,
      -1,   283,   284,    -1,   286,    -1,    -1,   289,    -1,   291,
      -1,    -1,    -1,   295,   296,    -1,    -1,   299,    -1,    -1,
     302,   303,   304,   305,   306,   307,   308,    -1,   310,   311,
     312,    -1,   314,    -1,    -1,    -1,    -1,   319,   320,    -1,
      -1,    -1,    -1,   325,    -1,    -1,    -1,   329,   330,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   344,   345,    -1,   347,   348,    -1,    -1,    -1,
      -1,   353,   354,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     372,   373,   374,    -1,    -1,    -1,   378,    -1,   380,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    -1,    -1,    18,    19,    -1,    -1,    22,    23,
      -1,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    38,    -1,    -1,    41,    -1,    -1,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    -1,    56,    -1,    -1,    59,    60,    61,    -1,    -1,
      -1,    65,    66,    67,    68,    -1,    -1,    -1,    72,    -1,
      -1,    75,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    86,    -1,    -1,    89,    -1,    -1,    92,    -1,
      -1,    -1,    -1,    -1,    98,    -1,    -1,    -1,    -1,   103,
     104,   105,    -1,    -1,    -1,    -1,    -1,    -1,   112,    -1,
     114,    -1,    -1,    -1,    -1,   119,   120,    -1,    -1,    -1,
     124,   125,    -1,   127,    -1,    -1,   130,   131,   132,   133,
     134,   135,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     144,   145,   146,   147,    -1,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
      -1,   165,   166,   167,   168,   169,   170,    -1,   172,   173,
     174,    -1,    -1,    -1,    -1,   179,   180,    -1,   182,    -1,
     184,   185,    -1,    -1,    -1,    -1,   190,   191,    -1,    -1,
      -1,    -1,    -1,   197,    -1,    -1,   200,   201,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   210,   211,   212,    -1,
      -1,    -1,    -1,   217,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   227,   228,    -1,    -1,    -1,   232,    -1,
      -1,   235,    -1,    -1,    -1,   239,   240,   241,   242,   243,
      -1,    -1,    -1,    -1,    -1,    -1,   250,    -1,    -1,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,    -1,   266,    -1,    -1,    -1,    -1,    -1,    -1,   273,
      -1,    -1,   276,    -1,    -1,    -1,   280,    -1,    -1,   283,
     284,    -1,   286,    -1,    -1,   289,    -1,   291,    -1,    -1,
      -1,   295,   296,    -1,    -1,    -1,    -1,    -1,    -1,   303,
     304,   305,   306,   307,   308,    -1,   310,   311,   312,    -1,
     314,    -1,    -1,    -1,    -1,   319,   320,    -1,    -1,    -1,
      -1,   325,    -1,    -1,    -1,   329,   330,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     344,   345,    -1,   347,   348,    -1,    -1,    -1,    -1,   353,
     354,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   372,   373,
     374,    -1,    -1,    -1,   378,    -1,   380,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      -1,    -1,    18,    19,    -1,    -1,    22,    23,    -1,    -1,
      26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    38,    -1,    -1,    41,    -1,    -1,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    -1,
      56,    -1,    -1,    59,    60,    61,    -1,    -1,    -1,    65,
      66,    67,    68,    -1,    -1,    -1,    72,    -1,    -1,    75,
      76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      86,    -1,    -1,    89,    -1,    -1,    92,    -1,    -1,    -1,
      -1,    -1,    98,    -1,    -1,    -1,    -1,   103,   104,   105,
      -1,    -1,    -1,    -1,    -1,    -1,   112,    -1,   114,    -1,
      -1,    -1,    -1,   119,   120,    -1,    -1,    -1,   124,   125,
      -1,   127,    -1,    -1,   130,   131,   132,   133,   134,   135,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   144,   145,
     146,   147,    -1,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,    -1,   165,
     166,   167,   168,   169,   170,    -1,   172,   173,   174,    -1,
      -1,    -1,    -1,   179,   180,   181,   182,    -1,   184,    -1,
      -1,    -1,    -1,    -1,   190,   191,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   200,   201,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   210,   211,   212,   213,    -1,    -1,
      -1,   217,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   227,   228,    -1,    -1,    -1,   232,    -1,    -1,   235,
      -1,    -1,    -1,   239,   240,   241,   242,   243,    -1,    -1,
      -1,    -1,    -1,    -1,   250,    -1,    -1,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,    -1,
     266,    -1,    -1,    -1,    -1,    -1,    -1,   273,    -1,    -1,
     276,    -1,    -1,    -1,   280,    -1,    -1,   283,   284,    -1,
     286,    -1,    -1,   289,    -1,   291,    -1,    -1,    -1,   295,
     296,    -1,    -1,    -1,    -1,    -1,    -1,   303,   304,   305,
     306,   307,   308,    -1,   310,   311,   312,    -1,   314,    -1,
      -1,    -1,    -1,   319,   320,    -1,    -1,    -1,    -1,   325,
      -1,    -1,    -1,   329,   330,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   344,   345,
      -1,   347,   348,    -1,    -1,    -1,    -1,   353,   354,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   372,   373,   374,    -1,
      -1,    -1,   378,    -1,   380,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,    -1,
      18,    19,    -1,    -1,    22,    23,    -1,    -1,    26,    27,
      28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      38,    -1,    -1,    41,    -1,    -1,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    -1,    56,    -1,
      -1,    59,    60,    61,    -1,    -1,    -1,    65,    66,    67,
      68,    -1,    -1,    -1,    72,    -1,    -1,    75,    76,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,    -1,
      -1,    89,    -1,    -1,    92,    -1,    -1,    -1,    -1,    -1,
      98,    -1,    -1,    -1,    -1,   103,   104,   105,    -1,    -1,
      -1,    -1,    -1,    -1,   112,    -1,   114,    -1,    -1,    -1,
      -1,   119,   120,    -1,    -1,    -1,   124,   125,    -1,   127,
      -1,    -1,   130,   131,   132,   133,   134,   135,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   144,   145,   146,   147,
      -1,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,    -1,   165,   166,   167,
     168,   169,   170,    -1,   172,   173,   174,    -1,    -1,    -1,
      -1,   179,   180,   181,   182,    -1,   184,    -1,    -1,    -1,
      -1,    -1,   190,   191,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   200,   201,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   210,   211,   212,   213,    -1,    -1,    -1,   217,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   227,
     228,    -1,    -1,    -1,   232,    -1,    -1,   235,    -1,    -1,
      -1,   239,   240,   241,   242,   243,    -1,    -1,    -1,    -1,
      -1,    -1,   250,    -1,    -1,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,    -1,   266,    -1,
      -1,    -1,    -1,    -1,    -1,   273,    -1,    -1,   276,    -1,
      -1,    -1,   280,    -1,    -1,   283,   284,    -1,   286,    -1,
      -1,   289,    -1,   291,    -1,    -1,    -1,   295,   296,    -1,
      -1,    -1,    -1,    -1,    -1,   303,   304,   305,   306,   307,
     308,    -1,   310,   311,   312,    -1,   314,    -1,    -1,    -1,
      -1,   319,   320,    -1,    -1,    -1,    -1,   325,    -1,    -1,
      -1,   329,   330,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   344,   345,    -1,   347,
     348,    -1,    -1,    -1,    -1,   353,   354,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   372,   373,   374,    -1,    -1,    -1,
     378,    -1,   380,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    -1,    -1,    18,    19,
      -1,    -1,    22,    23,    -1,    -1,    26,    27,    28,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,
      -1,    41,    -1,    -1,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    -1,    56,    -1,    -1,    59,
      60,    61,    -1,    -1,    -1,    65,    66,    67,    68,    -1,
      -1,    71,    72,    -1,    -1,    75,    76,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    86,    -1,    -1,    89,
      -1,    -1,    92,    -1,    -1,    -1,    -1,    -1,    98,    -1,
      -1,    -1,    -1,   103,   104,   105,    -1,    -1,    -1,    -1,
      -1,    -1,   112,    -1,   114,    -1,    -1,    -1,    -1,   119,
     120,    -1,    -1,    -1,   124,   125,    -1,   127,    -1,    -1,
     130,   131,   132,   133,   134,   135,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   144,   145,   146,   147,    -1,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,    -1,   165,   166,   167,   168,   169,
     170,    -1,   172,   173,   174,    -1,    -1,    -1,    -1,   179,
     180,    -1,   182,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     190,   191,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     200,   201,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     210,   211,   212,    -1,    -1,    -1,    -1,   217,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   227,   228,    -1,
      -1,    -1,   232,    -1,    -1,   235,    -1,    -1,    -1,   239,
     240,   241,   242,   243,    -1,    -1,    -1,    -1,    -1,    -1,
     250,    -1,    -1,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,    -1,   266,    -1,    -1,    -1,
      -1,    -1,    -1,   273,    -1,    -1,   276,    -1,    -1,    -1,
     280,    -1,    -1,   283,   284,    -1,   286,    -1,    -1,   289,
      -1,   291,    -1,    -1,    -1,   295,   296,    -1,    -1,   299,
      -1,    -1,   302,   303,   304,   305,   306,   307,   308,    -1,
     310,   311,   312,    -1,   314,    -1,    -1,    -1,    -1,   319,
     320,    -1,    -1,    -1,    -1,   325,    -1,    -1,    -1,   329,
     330,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   344,   345,    -1,   347,   348,    -1,
      -1,    -1,    -1,   353,   354,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   372,   373,   374,    -1,    -1,    -1,   378,    -1,
     380,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    -1,    -1,    18,    19,    -1,    -1,
      22,    23,    -1,    -1,    26,    27,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,    -1,    41,
      -1,    -1,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    -1,    56,    -1,    -1,    59,    60,    61,
      -1,    -1,    -1,    65,    66,    67,    68,    -1,    -1,    -1,
      72,    -1,    -1,    75,    76,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    86,    -1,    -1,    89,    -1,    -1,
      92,    -1,    -1,    -1,    -1,    -1,    98,    -1,    -1,    -1,
      -1,   103,   104,   105,    -1,    -1,    -1,    -1,    -1,    -1,
     112,    -1,   114,    -1,    -1,    -1,    -1,   119,   120,    -1,
      -1,    -1,   124,   125,    -1,   127,    -1,    -1,   130,   131,
     132,   133,   134,   135,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   144,   145,   146,   147,    -1,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,    -1,   165,   166,   167,   168,   169,   170,    -1,
     172,   173,   174,    -1,    -1,    -1,    -1,   179,   180,    -1,
     182,    -1,    -1,    -1,    -1,   187,    -1,    -1,   190,   191,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   200,   201,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   210,   211,
     212,    -1,    -1,    -1,    -1,   217,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   227,   228,    -1,    -1,    -1,
     232,    -1,    -1,   235,    -1,    -1,    -1,   239,   240,   241,
     242,   243,    -1,    -1,    -1,    -1,    -1,    -1,   250,    -1,
      -1,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,    -1,   266,    -1,    -1,    -1,    -1,    -1,
      -1,   273,    -1,    -1,   276,    -1,    -1,    -1,   280,    -1,
      -1,   283,   284,    -1,   286,    -1,    -1,   289,    -1,   291,
      -1,    -1,    -1,   295,   296,    -1,    -1,    -1,    -1,    -1,
      -1,   303,   304,   305,   306,   307,   308,    -1,   310,   311,
     312,    -1,   314,    -1,    -1,    -1,    -1,   319,   320,    -1,
      -1,    -1,    -1,   325,    -1,    -1,    -1,   329,   330,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   344,   345,    -1,   347,   348,    -1,    -1,    -1,
      -1,   353,   354,    -1,    -1,    -1,    -1,    -1,    -1,   361,
      -1,    -1,    -1,    -1,    -1,    -1,   368,    -1,    -1,    -1,
     372,   373,   374,    -1,    -1,    -1,   378,    -1,   380,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    -1,    -1,    18,    19,    -1,    -1,    22,    23,
      -1,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    38,    -1,    -1,    41,    -1,    -1,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    -1,    56,    -1,    -1,    59,    60,    61,    -1,    -1,
      -1,    65,    66,    67,    68,    -1,    -1,    -1,    72,    -1,
      -1,    75,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    86,    -1,    -1,    89,    -1,    -1,    92,    -1,
      -1,    -1,    -1,    -1,    98,    -1,    -1,    -1,    -1,   103,
     104,   105,    -1,    -1,    -1,    -1,    -1,    -1,   112,    -1,
     114,    -1,    -1,    -1,    -1,   119,   120,    -1,    -1,    -1,
     124,   125,    -1,   127,    -1,    -1,   130,   131,   132,   133,
     134,   135,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     144,   145,   146,   147,    -1,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
      -1,   165,   166,   167,   168,   169,   170,    -1,   172,   173,
     174,    -1,    -1,    -1,    -1,   179,   180,   181,   182,    -1,
     184,    -1,    -1,    -1,    -1,    -1,   190,   191,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   200,   201,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   210,   211,   212,    -1,
      -1,    -1,    -1,   217,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   227,   228,    -1,    -1,    -1,   232,    -1,
      -1,   235,    -1,    -1,    -1,   239,   240,   241,   242,   243,
      -1,    -1,    -1,    -1,    -1,    -1,   250,    -1,    -1,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,    -1,   266,    -1,    -1,    -1,    -1,    -1,    -1,   273,
      -1,    -1,   276,    -1,    -1,    -1,   280,    -1,    -1,   283,
     284,    -1,   286,    -1,    -1,   289,    -1,   291,    -1,    -1,
      -1,   295,   296,    -1,    -1,    -1,    -1,    -1,    -1,   303,
     304,   305,   306,   307,   308,    -1,   310,   311,   312,    -1,
     314,    -1,    -1,    -1,    -1,   319,   320,    -1,    -1,    -1,
      -1,   325,    -1,    -1,    -1,   329,   330,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     344,   345,    -1,   347,   348,    -1,    -1,    -1,    -1,   353,
     354,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   372,   373,
     374,    -1,    -1,    -1,   378,    -1,   380,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      -1,    -1,    18,    19,    -1,    -1,    22,    23,    -1,    -1,
      26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    38,    -1,    -1,    41,    -1,    -1,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    -1,
      56,    -1,    -1,    59,    60,    61,    -1,    -1,    -1,    65,
      66,    67,    68,    -1,    -1,    -1,    72,    -1,    -1,    75,
      76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      86,    -1,    -1,    89,    -1,    -1,    92,    -1,    -1,    -1,
      -1,    -1,    98,    -1,    -1,    -1,    -1,   103,   104,   105,
      -1,    -1,    -1,    -1,    -1,    -1,   112,    -1,   114,    -1,
      -1,   117,   118,   119,   120,    -1,    -1,    -1,   124,   125,
      -1,   127,    -1,    -1,   130,   131,   132,   133,   134,   135,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   144,   145,
     146,   147,    -1,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,    -1,   165,
     166,   167,   168,   169,   170,    -1,   172,   173,   174,    -1,
      -1,    -1,    -1,   179,   180,    -1,   182,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   190,   191,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   200,   201,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   210,   211,   212,    -1,    -1,    -1,
      -1,   217,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   227,   228,    -1,    -1,    -1,   232,    -1,    -1,   235,
      -1,    -1,    -1,   239,   240,   241,   242,   243,    -1,    -1,
      -1,    -1,    -1,    -1,   250,    -1,    -1,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,    -1,
     266,    -1,    -1,    -1,    -1,    -1,    -1,   273,    -1,    -1,
     276,    -1,    -1,    -1,   280,    -1,    -1,   283,   284,    -1,
     286,    -1,    -1,   289,    -1,   291,    -1,    -1,    -1,   295,
     296,    -1,    -1,    -1,    -1,    -1,    -1,   303,   304,   305,
     306,   307,   308,    -1,   310,   311,   312,    -1,   314,    -1,
      -1,    -1,    -1,   319,   320,    -1,    -1,    -1,    -1,   325,
      -1,    -1,    -1,   329,   330,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   344,   345,
      -1,   347,   348,    -1,    -1,    -1,    -1,   353,   354,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   372,   373,   374,    -1,
      -1,    -1,   378,    -1,   380,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,    -1,
      18,    19,    -1,    -1,    22,    23,    -1,    -1,    26,    27,
      28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      38,    -1,    -1,    41,    -1,    -1,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    -1,    56,    -1,
      -1,    59,    60,    61,    -1,    -1,    -1,    65,    66,    67,
      68,    -1,    -1,    -1,    72,    -1,    -1,    75,    76,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,    -1,
      -1,    89,    -1,    -1,    92,    -1,    -1,    -1,    -1,    -1,
      98,    -1,    -1,    -1,    -1,   103,   104,   105,    -1,    -1,
      -1,    -1,    -1,    -1,   112,    -1,   114,    -1,    -1,    -1,
      -1,   119,   120,    -1,    -1,    -1,   124,   125,    -1,   127,
      -1,    -1,   130,   131,   132,   133,   134,   135,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   144,   145,   146,   147,
      -1,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,    -1,   165,   166,   167,
     168,   169,   170,    -1,   172,   173,   174,    -1,    -1,    -1,
      -1,   179,   180,    -1,   182,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   190,   191,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   200,   201,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   210,   211,   212,    -1,    -1,    -1,    -1,   217,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   227,
     228,    -1,    -1,    -1,   232,    -1,    -1,   235,    -1,    -1,
      -1,   239,   240,   241,   242,   243,    -1,    -1,    -1,    -1,
      -1,    -1,   250,    -1,    -1,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,    -1,   266,    -1,
      -1,    -1,    -1,    -1,    -1,   273,    -1,    -1,   276,    -1,
      -1,    -1,   280,    -1,    -1,   283,   284,    -1,   286,    -1,
      -1,   289,    -1,   291,    -1,    -1,    -1,   295,   296,    -1,
      -1,    -1,    -1,    -1,    -1,   303,   304,   305,   306,   307,
     308,    -1,   310,   311,   312,    -1,   314,    -1,    -1,    -1,
      -1,   319,   320,    -1,    -1,    -1,    -1,   325,    -1,    -1,
      -1,   329,   330,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   344,   345,    -1,   347,
     348,    -1,    -1,    -1,    -1,   353,   354,    -1,    -1,    -1,
      -1,    -1,    -1,   361,    -1,    -1,    -1,    -1,    -1,    -1,
     368,    -1,    -1,    -1,   372,   373,   374,    -1,    -1,    -1,
     378,    -1,   380,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    -1,    -1,    18,    19,
      -1,    -1,    22,    23,    -1,    -1,    26,    27,    28,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,
      -1,    41,    -1,    -1,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    -1,    56,    -1,    -1,    59,
      60,    61,    -1,    -1,    -1,    65,    66,    67,    68,    -1,
      -1,    -1,    72,    -1,    -1,    75,    76,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    86,    -1,    -1,    89,
      -1,    -1,    92,    -1,    -1,    -1,    -1,    -1,    98,    -1,
      -1,    -1,    -1,   103,   104,   105,    -1,    -1,    -1,    -1,
      -1,    -1,   112,    -1,   114,    -1,    -1,    -1,    -1,   119,
     120,    -1,    -1,    -1,   124,   125,    -1,   127,    -1,    -1,
     130,   131,   132,   133,   134,   135,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   144,   145,   146,   147,    -1,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,    -1,   165,   166,   167,   168,   169,
     170,    -1,   172,   173,   174,    -1,    -1,    -1,    -1,   179,
     180,    -1,   182,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     190,   191,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     200,   201,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     210,   211,   212,   213,    -1,    -1,    -1,   217,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   227,   228,    -1,
      -1,    -1,   232,    -1,    -1,   235,    -1,    -1,    -1,   239,
     240,   241,   242,   243,    -1,    -1,    -1,    -1,    -1,    -1,
     250,    -1,    -1,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,    -1,   266,    -1,    -1,    -1,
      -1,    -1,    -1,   273,    -1,    -1,   276,    -1,    -1,    -1,
     280,    -1,    -1,   283,   284,    -1,   286,    -1,    -1,   289,
      -1,   291,    -1,    -1,    -1,   295,   296,    -1,    -1,    -1,
      -1,    -1,    -1,   303,   304,   305,   306,   307,   308,    -1,
     310,   311,   312,    -1,   314,    -1,    -1,    -1,    -1,   319,
     320,    -1,    -1,    -1,    -1,   325,    -1,    -1,    -1,   329,
     330,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   344,   345,    -1,   347,   348,    -1,
      -1,    -1,    -1,   353,   354,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   372,   373,   374,    -1,    -1,    -1,   378,    -1,
     380,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    -1,    -1,    18,    19,    -1,    -1,
      22,    23,    -1,    -1,    26,    27,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,    -1,    41,
      -1,    -1,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    -1,    56,    -1,    -1,    59,    60,    61,
      -1,    -1,    -1,    65,    66,    67,    68,    -1,    -1,    -1,
      72,    -1,    -1,    75,    76,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    86,    -1,    -1,    89,    -1,    -1,
      92,    -1,    -1,    -1,    -1,    -1,    98,    -1,    -1,    -1,
      -1,   103,   104,   105,    -1,    -1,    -1,    -1,    -1,    -1,
     112,    -1,   114,    -1,    -1,    -1,    -1,   119,   120,    -1,
      -1,    -1,   124,   125,    -1,   127,    -1,    -1,   130,   131,
     132,   133,   134,   135,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   144,   145,   146,   147,    -1,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,    -1,   165,   166,   167,   168,   169,   170,    -1,
     172,   173,   174,    -1,    -1,    -1,    -1,   179,   180,    -1,
     182,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   190,   191,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   200,   201,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   210,   211,
     212,    -1,    -1,    -1,    -1,   217,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   227,   228,    -1,    -1,    -1,
     232,    -1,    -1,   235,    -1,    -1,    -1,   239,   240,   241,
     242,   243,    -1,    -1,    -1,    -1,    -1,    -1,   250,    -1,
      -1,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,    -1,    -1,    -1,    -1,    -1,
      -1,   273,    -1,    -1,   276,    -1,    -1,    -1,   280,    -1,
      -1,   283,   284,    -1,   286,    -1,    -1,   289,    -1,   291,
      -1,    -1,    -1,   295,   296,    -1,    -1,    -1,    -1,    -1,
      -1,   303,   304,   305,   306,   307,   308,    -1,   310,   311,
     312,    -1,   314,    -1,    -1,    -1,    -1,   319,   320,    -1,
      -1,    -1,    -1,   325,    -1,    -1,    -1,   329,   330,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   344,   345,    -1,   347,   348,    -1,    -1,    -1,
      -1,   353,   354,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     372,   373,   374,    -1,    -1,    -1,   378,    -1,   380,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    -1,    -1,    18,    19,    -1,    -1,    22,    23,
      -1,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    38,    -1,    -1,    41,    -1,    -1,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    -1,    56,    -1,    -1,    59,    60,    61,    -1,    -1,
      -1,    65,    66,    67,    68,    -1,    -1,    -1,    72,    -1,
      -1,    75,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    86,    -1,    -1,    89,    -1,    -1,    92,    -1,
      -1,    -1,    -1,    -1,    98,    -1,    -1,    -1,    -1,   103,
     104,   105,    -1,    -1,    -1,    -1,    -1,    -1,   112,    -1,
     114,    -1,    -1,    -1,    -1,   119,   120,    -1,    -1,    -1,
     124,   125,    -1,   127,    -1,    -1,   130,   131,   132,   133,
     134,   135,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     144,   145,   146,   147,    -1,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
      -1,   165,   166,   167,   168,   169,   170,    -1,   172,   173,
     174,    -1,    -1,    -1,    -1,   179,   180,    -1,   182,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   190,   191,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   200,   201,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   210,   211,   212,    -1,
      -1,    -1,    -1,   217,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   227,   228,    -1,    -1,    -1,   232,    -1,
      -1,   235,    -1,    -1,    -1,   239,   240,   241,   242,   243,
      -1,    -1,    -1,    -1,    -1,    -1,   250,    -1,    -1,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,    -1,   266,    -1,    -1,    -1,    -1,    -1,    -1,   273,
      -1,    -1,   276,    -1,    -1,    -1,   280,    -1,    -1,   283,
     284,    -1,   286,    -1,    -1,   289,    -1,   291,    -1,    -1,
      -1,   295,   296,    -1,    -1,    -1,    -1,    -1,    -1,   303,
     304,   305,   306,   307,   308,    -1,   310,   311,   312,    -1,
     314,    -1,    -1,    -1,    -1,   319,   320,    -1,    -1,    -1,
      -1,   325,   326,    -1,    -1,   329,   330,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     344,   345,    -1,   347,   348,    -1,    -1,    -1,    -1,   353,
     354,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   372,   373,
     374,    -1,    -1,    -1,   378,    -1,   380,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      -1,    -1,    18,    19,    -1,    -1,    22,    23,    -1,    -1,
      26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    38,    -1,    -1,    41,    -1,    -1,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    -1,
      56,    -1,    -1,    59,    60,    61,    -1,    -1,    -1,    65,
      66,    67,    68,    -1,    -1,    -1,    72,    -1,    -1,    75,
      76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      86,    -1,    -1,    89,    -1,    -1,    92,    -1,    -1,    -1,
      -1,    -1,    98,    -1,    -1,    -1,    -1,   103,   104,   105,
      -1,    -1,    -1,    -1,    -1,    -1,   112,    -1,   114,    -1,
      -1,    -1,    -1,   119,   120,    -1,    -1,    -1,   124,   125,
      -1,   127,    -1,    -1,   130,   131,   132,   133,   134,   135,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   144,   145,
     146,   147,    -1,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,    -1,   165,
     166,   167,   168,   169,   170,    -1,   172,   173,   174,    -1,
      -1,    -1,    -1,   179,   180,   181,   182,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   190,   191,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   200,   201,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   210,   211,   212,    -1,    -1,    -1,
      -1,   217,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   227,   228,    -1,    -1,    -1,   232,    -1,    -1,   235,
      -1,    -1,    -1,   239,   240,   241,   242,   243,    -1,    -1,
      -1,    -1,    -1,    -1,   250,    -1,    -1,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,    -1,
     266,    -1,    -1,    -1,    -1,    -1,    -1,   273,    -1,    -1,
     276,    -1,    -1,    -1,   280,    -1,    -1,   283,   284,    -1,
     286,    -1,    -1,   289,    -1,   291,    -1,    -1,    -1,   295,
     296,    -1,    -1,    -1,    -1,    -1,    -1,   303,   304,   305,
     306,   307,   308,    -1,   310,   311,   312,    -1,   314,    -1,
      -1,    -1,    -1,   319,   320,    -1,    -1,    -1,    -1,   325,
      -1,    -1,    -1,   329,   330,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   344,   345,
      -1,   347,   348,    -1,    -1,    -1,    -1,   353,   354,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   372,   373,   374,    -1,
      -1,    -1,   378,    -1,   380,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,    -1,
      18,    19,    -1,    -1,    22,    23,    -1,    -1,    26,    27,
      28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      38,    -1,    -1,    41,    -1,    -1,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    -1,    56,    -1,
      -1,    59,    60,    61,    -1,    -1,    -1,    65,    66,    67,
      68,    -1,    -1,    -1,    72,    -1,    -1,    75,    76,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,    -1,
      -1,    89,    -1,    -1,    92,    -1,    -1,    -1,    -1,    -1,
      98,    -1,    -1,    -1,    -1,   103,   104,   105,    -1,    -1,
      -1,    -1,    -1,    -1,   112,    -1,   114,    -1,    -1,    -1,
      -1,   119,   120,    -1,    -1,    -1,   124,   125,    -1,   127,
      -1,    -1,   130,   131,   132,   133,   134,   135,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   144,   145,   146,   147,
      -1,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,    -1,   165,   166,   167,
     168,   169,   170,    -1,   172,   173,   174,    -1,    -1,    -1,
      -1,   179,   180,    -1,   182,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   190,   191,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   200,   201,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   210,   211,   212,    -1,    -1,    -1,    -1,   217,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   227,
     228,    -1,    -1,    -1,   232,    -1,    -1,   235,    -1,    -1,
      -1,   239,   240,   241,   242,   243,    -1,    -1,    -1,    -1,
      -1,    -1,   250,    -1,    -1,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,    -1,   266,    -1,
      -1,    -1,    -1,    -1,    -1,   273,    -1,    -1,   276,    -1,
      -1,    -1,   280,    -1,    -1,   283,   284,    -1,   286,    -1,
      -1,   289,    -1,   291,    -1,    -1,    -1,   295,   296,    -1,
      -1,    -1,    -1,    -1,    -1,   303,   304,   305,   306,   307,
     308,    -1,   310,   311,   312,    -1,   314,    -1,    -1,    -1,
      -1,   319,   320,    -1,    -1,    -1,    -1,   325,   326,    -1,
      -1,   329,   330,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   344,   345,    -1,   347,
     348,    -1,    -1,    -1,    -1,   353,   354,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   372,   373,   374,    -1,    -1,    -1,
     378,    -1,   380,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    -1,    -1,    18,    19,
      -1,    -1,    22,    23,    -1,    -1,    26,    27,    28,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,
      -1,    41,    -1,    -1,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    -1,    56,    -1,    -1,    59,
      60,    61,    -1,    -1,    -1,    65,    66,    67,    68,    -1,
      -1,    -1,    72,    -1,    -1,    75,    76,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    86,    -1,    -1,    89,
      -1,    -1,    92,    -1,    -1,    -1,    -1,    -1,    98,    -1,
      -1,    -1,    -1,   103,   104,   105,    -1,    -1,    -1,    -1,
      -1,    -1,   112,    -1,   114,    -1,    -1,    -1,    -1,   119,
     120,    -1,    -1,    -1,   124,   125,    -1,   127,    -1,    -1,
     130,   131,   132,   133,   134,   135,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   144,   145,   146,   147,    -1,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,    -1,   165,   166,   167,   168,   169,
     170,    -1,   172,   173,   174,    -1,    -1,    -1,    -1,   179,
     180,    -1,   182,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     190,   191,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     200,   201,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     210,   211,   212,    -1,    -1,    -1,    -1,   217,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   227,   228,    -1,
      -1,    -1,   232,    -1,    -1,   235,    -1,    -1,    -1,   239,
     240,   241,   242,   243,    -1,    -1,    -1,    -1,    -1,    -1,
     250,    -1,    -1,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,    -1,   266,    -1,    -1,    -1,
      -1,    -1,    -1,   273,    -1,    -1,   276,    -1,    -1,    -1,
     280,    -1,    -1,   283,   284,    -1,   286,    -1,    -1,   289,
      -1,   291,    -1,    -1,    -1,   295,   296,    -1,    -1,    -1,
      -1,    -1,    -1,   303,   304,   305,   306,   307,   308,    -1,
     310,   311,   312,    -1,   314,    -1,    -1,    -1,    -1,   319,
     320,    -1,    -1,    -1,    -1,   325,    -1,    -1,    -1,   329,
     330,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   344,   345,    -1,   347,   348,    -1,
      -1,    -1,    -1,   353,   354,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   367,    -1,    -1,
      -1,    -1,   372,   373,   374,    -1,    -1,    -1,   378,    -1,
     380,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    -1,    -1,    18,    19,    -1,    -1,
      22,    23,    -1,    -1,    26,    27,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,    -1,    41,
      -1,    -1,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    -1,    56,    -1,    -1,    59,    60,    61,
      -1,    -1,    -1,    65,    66,    67,    68,    -1,    -1,    -1,
      72,    -1,    -1,    75,    76,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    86,    -1,    -1,    89,    -1,    -1,
      92,    -1,    -1,    -1,    -1,    -1,    98,    -1,    -1,    -1,
      -1,   103,   104,   105,    -1,    -1,    -1,    -1,    -1,    -1,
     112,    -1,   114,    -1,    -1,    -1,    -1,   119,   120,    -1,
      -1,    -1,   124,   125,    -1,   127,    -1,    -1,   130,   131,
     132,   133,   134,   135,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   144,   145,   146,   147,    -1,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,    -1,   165,   166,   167,   168,   169,   170,    -1,
     172,   173,   174,    -1,    -1,    -1,    -1,   179,   180,    -1,
     182,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   190,   191,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   200,   201,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   210,   211,
     212,    -1,    -1,    -1,    -1,   217,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   227,   228,    -1,    -1,    -1,
     232,    -1,    -1,   235,    -1,    -1,    -1,   239,   240,   241,
     242,   243,    -1,    -1,    -1,    -1,    -1,    -1,   250,    -1,
      -1,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,    -1,   266,    -1,    -1,    -1,    -1,    -1,
      -1,   273,    -1,    -1,   276,    -1,    -1,    -1,   280,    -1,
      -1,   283,   284,    -1,   286,    -1,    -1,   289,    -1,   291,
      -1,    -1,    -1,   295,   296,    -1,    -1,    -1,    -1,    -1,
      -1,   303,   304,   305,   306,   307,   308,    -1,   310,   311,
     312,    -1,   314,    -1,    -1,    -1,    -1,   319,   320,    -1,
      -1,    -1,    -1,   325,    -1,    -1,    -1,   329,   330,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   344,   345,    -1,   347,   348,    -1,    -1,    -1,
      -1,   353,   354,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   367,    -1,    -1,    -1,    -1,
     372,   373,   374,    -1,    -1,    -1,   378,    -1,   380,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    -1,    -1,    18,    19,    -1,    -1,    22,    23,
      -1,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    38,    -1,    -1,    41,    -1,    -1,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    -1,    56,    -1,    -1,    59,    60,    61,    -1,    -1,
      -1,    65,    66,    67,    68,    -1,    -1,    -1,    72,    -1,
      -1,    75,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    86,    -1,    -1,    89,    -1,    -1,    92,    -1,
      -1,    -1,    -1,    -1,    98,    -1,    -1,    -1,    -1,   103,
     104,   105,    -1,    -1,    -1,    -1,    -1,    -1,   112,    -1,
     114,    -1,    -1,    -1,    -1,   119,   120,    -1,    -1,    -1,
     124,   125,    -1,   127,    -1,    -1,   130,   131,   132,   133,
     134,   135,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     144,   145,   146,   147,    -1,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
      -1,   165,   166,   167,   168,   169,   170,    -1,   172,   173,
     174,    -1,    -1,    -1,    -1,   179,   180,    -1,   182,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   190,   191,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   200,   201,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   210,   211,   212,    -1,
      -1,    -1,    -1,   217,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   227,   228,    -1,    -1,    -1,   232,    -1,
      -1,   235,    -1,    -1,    -1,   239,   240,   241,   242,   243,
      -1,    -1,    -1,    -1,    -1,    -1,   250,    -1,    -1,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,    -1,   266,    -1,    -1,    -1,    -1,    -1,    -1,   273,
      -1,    -1,   276,    -1,    -1,    -1,   280,    -1,    -1,   283,
     284,    -1,   286,    -1,    -1,   289,    -1,   291,    -1,    -1,
      -1,   295,   296,    -1,    -1,    -1,    -1,    -1,    -1,   303,
     304,   305,   306,   307,   308,    -1,   310,   311,   312,    -1,
     314,    -1,    -1,    -1,    -1,   319,   320,    -1,    -1,    -1,
      -1,   325,    -1,    -1,    -1,   329,   330,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     344,   345,    -1,   347,   348,    -1,    -1,    -1,    -1,   353,
     354,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   372,   373,
     374,    -1,    -1,    -1,   378,    -1,   380,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      -1,    -1,    18,    19,    -1,    -1,    22,    23,    -1,    -1,
      26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    38,    -1,    -1,    41,    -1,    -1,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    -1,
      56,    -1,    -1,    59,    60,    61,    -1,    -1,    -1,    65,
      66,    67,    68,    -1,    -1,    -1,    72,    -1,    -1,    75,
      76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      86,    -1,    -1,    89,    -1,    -1,    92,    -1,    -1,    -1,
      -1,    -1,    98,    -1,    -1,    -1,    -1,   103,   104,   105,
      -1,    -1,    -1,    -1,    -1,    -1,   112,    -1,   114,    -1,
      -1,    -1,    -1,   119,   120,    -1,    -1,    -1,   124,   125,
      -1,   127,    -1,    -1,   130,   131,   132,   133,   134,   135,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,    -1,   172,   173,   174,    -1,
      -1,    -1,    -1,   179,   180,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   200,   201,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   210,   211,   212,    -1,    -1,    -1,
      -1,   217,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   227,   228,    -1,    -1,    -1,   232,    -1,    -1,   235,
      -1,    -1,    -1,   239,   240,   241,   242,   243,    -1,    -1,
      -1,    -1,    -1,    -1,   250,    -1,    -1,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,    -1,
     266,    -1,    -1,    -1,    -1,    -1,    -1,   273,    -1,    -1,
     276,    -1,    -1,    -1,   280,    -1,    -1,   283,   284,    -1,
     286,    -1,    -1,   289,    -1,   291,    -1,    -1,    -1,   295,
     296,    -1,    -1,    -1,    -1,    -1,    -1,   303,   304,   305,
     306,   307,   308,    -1,   310,   311,   312,    -1,   314,    -1,
      -1,    -1,    -1,   319,   320,    -1,    -1,    -1,    -1,   325,
      -1,    -1,    -1,   329,   330,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   344,   345,
      -1,   347,   348,    -1,    -1,    -1,    -1,   353,   354,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   372,   373,   374,    -1,
      -1,    -1,    -1,    -1,   380,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,    -1,
      18,    19,    -1,    -1,    22,    23,    -1,    -1,    26,    27,
      28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      38,    -1,    -1,    41,    -1,    -1,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    -1,    56,    -1,
      -1,    59,    60,    61,    -1,    -1,    -1,    65,    66,    67,
      68,    -1,    -1,    -1,    72,    -1,    -1,    75,    76,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,    -1,
      -1,    89,    -1,    -1,    92,    -1,    -1,    -1,    -1,    -1,
      98,    -1,    -1,    -1,    -1,   103,   104,   105,    -1,    -1,
      -1,    -1,    -1,    -1,   112,    -1,   114,    -1,    -1,    -1,
      -1,   119,   120,    -1,    -1,    -1,   124,   125,    -1,   127,
      -1,    -1,   130,   131,   132,   133,   134,   135,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   144,   145,   146,   147,
      -1,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,    -1,   165,   166,   167,
     168,   169,   170,    -1,   172,   173,   174,    -1,    -1,    -1,
      -1,   179,   180,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   200,   201,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   210,   211,   212,    -1,    -1,    -1,    -1,   217,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   227,
     228,    -1,    -1,    -1,   232,    -1,    -1,   235,    -1,    -1,
      -1,   239,   240,   241,   242,   243,    -1,    -1,    -1,    -1,
      -1,    -1,   250,    -1,    -1,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,    -1,
      -1,    -1,    -1,    -1,    -1,   273,    -1,    -1,   276,    -1,
      -1,    -1,   280,    -1,    -1,   283,   284,    -1,   286,    -1,
      -1,   289,    -1,   291,    -1,    -1,    -1,   295,   296,    -1,
      -1,    -1,    -1,    -1,    -1,   303,   304,   305,   306,   307,
     308,    -1,   310,   311,   312,    -1,   314,    -1,    -1,    -1,
      -1,   319,   320,    -1,    -1,    -1,    -1,   325,    -1,    -1,
      -1,   329,   330,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   344,   345,    -1,   347,
     348,    -1,    -1,    -1,    -1,   353,   354,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   372,   373,   374,    -1,    -1,    -1,
      -1,    -1,   380,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    -1,    -1,    18,    19,
      -1,    -1,    22,    23,    -1,    -1,    26,    27,    28,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,
      -1,    41,    -1,    -1,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    -1,    56,    -1,    -1,    59,
      60,    61,    -1,    -1,    -1,    65,    66,    67,    68,    -1,
      -1,    -1,    72,    -1,    -1,    75,    76,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    86,    -1,    -1,    89,
      -1,    -1,    92,    -1,    -1,    -1,    -1,    -1,    98,    -1,
      -1,    -1,    -1,   103,   104,   105,    -1,    -1,    -1,    -1,
      -1,    -1,   112,    -1,   114,    -1,    -1,    -1,    -1,   119,
     120,    -1,    -1,    -1,   124,   125,    -1,   127,    -1,    -1,
     130,   131,   132,   133,   134,   135,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,    -1,   165,   166,   167,   168,   169,
     170,    -1,   172,   173,   174,    -1,    -1,    -1,    -1,   179,
     180,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     200,   201,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     210,   211,   212,    -1,    -1,    -1,    -1,   217,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   227,   228,    -1,
      -1,    -1,   232,    -1,    -1,   235,    -1,    -1,    -1,   239,
     240,   241,   242,   243,    -1,    -1,    -1,    -1,    -1,    -1,
     250,    -1,    -1,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,    -1,   266,    -1,    -1,    -1,
      -1,    -1,    -1,   273,    -1,    -1,   276,    -1,    -1,    -1,
     280,    -1,    -1,   283,   284,    -1,   286,    -1,    -1,   289,
      -1,   291,    -1,    -1,    -1,   295,   296,    -1,    -1,    -1,
      -1,    -1,    -1,   303,   304,   305,   306,   307,   308,    -1,
     310,   311,   312,    -1,   314,    -1,    -1,    -1,    -1,   319,
     320,    -1,    -1,    -1,    -1,   325,    -1,    -1,    -1,   329,
     330,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   344,   345,    -1,   347,   348,    -1,
      -1,    -1,    -1,   353,   354,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   372,   373,   374,    -1,    -1,    -1,    -1,    -1,
     380,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    -1,    -1,    18,    19,    -1,    -1,
      22,    23,    -1,    -1,    26,    27,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,    -1,    41,
      -1,    -1,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    -1,    56,    -1,    -1,    59,    60,    61,
      -1,    -1,    -1,    65,    66,    67,    68,    -1,    -1,    -1,
      72,    -1,    -1,    75,    76,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    86,    -1,    -1,    89,    -1,    -1,
      92,    -1,    -1,    -1,    -1,    -1,    98,    -1,    -1,    -1,
      -1,   103,   104,   105,    -1,    -1,    -1,    -1,    -1,    -1,
     112,    -1,   114,    -1,    -1,    -1,    -1,   119,   120,    -1,
      -1,    -1,   124,   125,    -1,   127,    -1,    -1,   130,   131,
     132,   133,   134,   135,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   144,   145,   146,   147,    -1,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,    -1,   165,   166,   167,   168,   169,   170,    -1,
     172,   173,   174,    -1,    -1,    -1,    -1,   179,   180,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   200,   201,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   210,   211,
     212,    -1,    -1,    -1,    -1,   217,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   227,   228,    -1,    -1,    -1,
     232,    -1,    -1,   235,    -1,    -1,    -1,   239,   240,   241,
     242,   243,    -1,    -1,    -1,    -1,    -1,    -1,   250,    -1,
      -1,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,    -1,   266,    -1,    -1,    -1,    -1,    -1,
      -1,   273,    -1,    -1,   276,    -1,    -1,    -1,   280,    -1,
      -1,   283,   284,    -1,   286,    -1,    -1,   289,    -1,   291,
      -1,    -1,    -1,   295,   296,    -1,    -1,    -1,    -1,    -1,
      -1,   303,   304,   305,   306,   307,   308,    -1,   310,   311,
     312,    -1,   314,    -1,    -1,    -1,    -1,   319,   320,    -1,
      -1,    -1,    -1,   325,    -1,    -1,    -1,   329,   330,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   344,   345,    -1,   347,   348,    -1,    -1,    -1,
      -1,   353,   354,    -1,    -1,    -1,    -1,     6,     7,     8,
       9,    10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     372,   373,   374,    22,    23,    -1,    -1,    26,   380,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,
      -1,    -1,    41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    51,    52,    53,    54,    -1,    56,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,
      69,    70,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    83,    84,    85,    86,    -1,    -1,
      89,    -1,    -1,    92,    -1,    -1,    -1,    -1,    -1,    98,
      -1,    -1,    -1,    -1,   103,   104,   105,    -1,    -1,    -1,
      -1,    -1,    -1,   112,    -1,   114,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   124,    -1,    -1,   127,    -1,
      -1,   130,   131,   132,    -1,   134,   135,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   151,   152,    -1,    -1,   155,    -1,   157,   158,
     159,   160,   161,   162,   163,    -1,   165,    -1,   167,   168,
     169,   170,    -1,   172,    -1,   174,    -1,    -1,    -1,    -1,
     179,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     6,     7,     8,     9,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    20,
      -1,    -1,    -1,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    -1,   227,   228,
     229,    -1,    -1,   232,    -1,    -1,   235,    -1,    -1,   238,
     239,   240,   241,   242,   243,    56,    57,    58,    -1,    -1,
      -1,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,    -1,   266,   267,   268,
      -1,    -1,    -1,    -1,   273,   274,   275,   276,    -1,    -1,
      -1,   280,    -1,    -1,   283,   284,    -1,   286,    -1,    -1,
     289,   290,   291,   292,   293,    -1,   295,   296,    -1,    -1,
      -1,    -1,    -1,    -1,   303,   304,   305,   306,   307,   308,
      -1,   310,   311,   312,    -1,   314,    -1,    -1,    -1,    -1,
     319,   320,    -1,    -1,    -1,    -1,   325,    -1,    -1,   328,
      -1,    -1,   331,   332,   333,    -1,    -1,   336,    -1,   338,
      -1,    -1,    -1,    -1,    -1,   344,   345,    -1,   347,   348,
      -1,    -1,    -1,    -1,   353,   354,    -1,    -1,    -1,    -1,
       6,     7,     8,     9,    10,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   372,   373,   374,    22,    23,    -1,    -1,
      26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    38,    -1,    -1,    41,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    51,    52,    53,    54,    -1,
      56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      66,    -1,    -1,    69,    70,    71,    72,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    83,    84,    85,
      86,    -1,    -1,    89,    -1,    -1,    92,    -1,    -1,    -1,
      -1,    -1,    98,    -1,    -1,    -1,   122,   103,   104,   105,
      -1,    -1,    -1,    -1,    -1,    -1,   112,    -1,   114,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   143,   124,    -1,
      -1,   127,    -1,    -1,   130,   131,   132,    -1,   134,   135,
      -1,    -1,   303,   304,   305,   306,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   151,   152,    -1,    -1,   155,
      -1,   157,   158,   159,   160,   161,   162,   163,    -1,   165,
      -1,   167,   168,   169,   170,    -1,   172,    -1,   174,    -1,
      -1,    -1,    -1,   179,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,    -1,    -1,    -1,   213,   214,   215,
      -1,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   227,   228,   229,    -1,    -1,   232,    -1,    -1,   235,
      -1,    -1,   238,   239,   240,   241,   242,   243,    -1,    -1,
      -1,    -1,    -1,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,    -1,
     266,   267,   268,    -1,    -1,    -1,    -1,   273,   274,   275,
     276,    -1,    -1,    -1,   280,    -1,    -1,   283,   284,    -1,
     286,    -1,    -1,   289,   290,   291,   292,   293,    -1,   295,
     296,    -1,    -1,    -1,    -1,    -1,    -1,   303,   304,   305,
     306,   307,   308,    -1,   310,   311,   312,    -1,   314,    -1,
      -1,    -1,    -1,   319,   320,    -1,    -1,    -1,    -1,   325,
      -1,    -1,    -1,    -1,    -1,   331,    -1,    -1,    -1,    -1,
     336,    -1,   338,    -1,    -1,    -1,    -1,    -1,   344,   345,
      -1,   347,   348,    -1,    -1,    -1,    -1,   353,   354,   375,
      -1,    -1,    -1,     6,     7,     8,     9,    10,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   372,   373,   374,    22,
      23,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    38,    -1,    -1,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    51,    52,
      53,    54,    -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    66,    -1,    -1,    69,    70,    71,    72,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      83,    84,    85,    86,    -1,    -1,    89,    -1,    -1,    92,
      -1,    -1,    -1,    -1,    -1,    98,    -1,    -1,    -1,    -1,
     103,   104,   105,    -1,    -1,    -1,    -1,    -1,    -1,   112,
      -1,   114,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   124,    -1,   143,   127,    -1,    -1,   130,   131,   132,
      -1,   134,   135,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   151,   152,
      -1,    -1,   155,    -1,   157,   158,   159,   160,   161,   162,
     163,   181,   165,    -1,   167,   168,   169,   170,    -1,   172,
      -1,   174,    -1,    -1,    -1,    -1,   179,    -1,    -1,    -1,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
      -1,    -1,    -1,   213,   214,   215,    -1,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   227,   228,   229,    -1,    -1,   232,
      -1,    -1,   235,    -1,    -1,   238,   239,   240,   241,   242,
     243,    -1,    -1,    -1,    -1,    -1,    -1,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,    -1,   266,   267,   268,    -1,    -1,    -1,    -1,
     273,   274,   275,   276,    -1,    -1,    -1,   280,    -1,    -1,
     283,   284,    -1,   286,    -1,    -1,   289,   290,   291,   292,
     293,    -1,   295,   296,    -1,    -1,    -1,    -1,    -1,    -1,
     303,   304,   305,   306,   307,   308,    -1,   310,   311,   312,
      -1,   314,    -1,    -1,    -1,    -1,   319,   320,    -1,    -1,
      -1,    -1,   325,    -1,    -1,    -1,    -1,    -1,   331,    -1,
     333,    -1,    -1,   336,    -1,   338,    -1,    -1,    -1,    -1,
      -1,   344,   345,    -1,   347,   348,    -1,    -1,    -1,    -1,
     353,   354,    -1,    -1,    -1,   375,     6,     7,     8,     9,
      10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   372,
     373,   374,    22,    23,    -1,    -1,    26,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,
      -1,    41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    51,    52,    53,    54,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,    69,
      70,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    83,    84,    85,    86,    -1,    -1,    89,
      -1,    -1,    92,    -1,    -1,    -1,    -1,    -1,    98,    -1,
      -1,    -1,    -1,   103,   104,   105,    -1,    -1,    -1,    -1,
      -1,    -1,   112,    -1,   114,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   143,   124,    -1,    -1,   127,    -1,    -1,
     130,   131,   132,    -1,   134,   135,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   151,   152,    -1,    -1,   155,    -1,   157,   158,   159,
     160,   161,   162,   163,    -1,   165,    -1,   167,   168,   169,
     170,    -1,   172,    -1,   174,    -1,    -1,    -1,    -1,   179,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
      -1,    -1,    -1,   213,   214,   215,    -1,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   227,   228,   229,
      -1,    -1,   232,    -1,    -1,   235,    -1,    -1,   238,   239,
     240,   241,   242,   243,    -1,    -1,    -1,    -1,    -1,    -1,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,    -1,   266,   267,   268,    -1,
      -1,    -1,    -1,   273,   274,   275,   276,    -1,    -1,    -1,
     280,    -1,    -1,   283,   284,    -1,   286,    -1,    -1,   289,
     290,   291,   292,   293,    -1,   295,   296,    -1,    -1,    -1,
      -1,    -1,    -1,   303,   304,   305,   306,   307,   308,    -1,
     310,   311,   312,    -1,   314,    -1,    -1,    -1,    -1,   319,
     320,    -1,    -1,    -1,    -1,   325,    -1,    -1,    -1,    -1,
      -1,   331,    -1,    -1,    -1,    -1,   336,   337,   338,    -1,
      -1,    -1,    -1,    -1,   344,   345,    -1,   347,   348,    -1,
      -1,    -1,    -1,   353,   354,   375,    -1,    -1,    -1,     6,
       7,     8,     9,    10,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   372,   373,   374,    22,    23,    -1,    -1,    26,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    38,    -1,    -1,    41,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    51,    52,    53,    54,    -1,    56,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,
      -1,    -1,    69,    70,    71,    72,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    83,    84,    85,    86,
      -1,    -1,    89,    -1,    -1,    92,    -1,    -1,    -1,    -1,
      -1,    98,    -1,    -1,    -1,    -1,   103,   104,   105,    -1,
      -1,    -1,    -1,    -1,    -1,   112,    -1,   114,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   143,   124,    -1,    -1,
     127,    -1,    -1,   130,   131,   132,    -1,   134,   135,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   151,   152,    -1,    -1,   155,    -1,
     157,   158,   159,   160,   161,   162,   163,    -1,   165,    -1,
     167,   168,   169,   170,    -1,   172,    -1,   174,    -1,    -1,
      -1,    -1,   179,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   209,    -1,    -1,    -1,   213,   214,   215,    -1,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     227,   228,   229,    -1,    -1,   232,    -1,    -1,   235,    -1,
      -1,   238,   239,   240,   241,   242,   243,    -1,    -1,    -1,
      -1,    -1,    -1,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,    -1,   266,
     267,   268,    -1,    -1,    -1,    -1,   273,   274,   275,   276,
      -1,    -1,    -1,   280,    -1,    -1,   283,   284,    -1,   286,
      -1,    -1,   289,   290,   291,   292,   293,    -1,   295,   296,
      -1,    -1,    -1,    -1,    -1,    -1,   303,   304,   305,   306,
     307,   308,    -1,   310,   311,   312,    -1,   314,    -1,    -1,
      -1,    -1,   319,   320,    -1,    -1,    -1,    -1,   325,    -1,
      -1,    -1,    -1,    -1,   331,    -1,    -1,    -1,    -1,   336,
      -1,   338,    -1,    -1,    -1,    -1,    -1,   344,   345,    -1,
     347,   348,    -1,    -1,    -1,    -1,   353,   354,   375,    -1,
      -1,    -1,     6,     7,     8,     9,    10,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   372,   373,   374,    22,    23,
      -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    38,    -1,    -1,    41,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    51,    52,    53,
      54,    -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    66,    -1,    -1,    69,    70,    71,    72,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    83,
      84,    85,    86,    -1,    -1,    89,    -1,    -1,    92,   113,
      -1,    -1,    -1,    -1,    98,    -1,    -1,    -1,    -1,   103,
     104,   105,    -1,    -1,    -1,    -1,    -1,    -1,   112,    -1,
     114,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   143,
     124,    -1,    -1,   127,    -1,    -1,   130,   131,   132,    -1,
     134,   135,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   151,   152,    -1,
      -1,   155,    -1,   157,   158,   159,   160,   161,   162,   163,
      -1,   165,    -1,   167,   168,   169,   170,    -1,   172,    -1,
     174,    -1,    -1,    -1,    -1,   179,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,    -1,    -1,    -1,   213,
     214,   215,    -1,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   227,   228,   229,    -1,    -1,   232,    -1,
      -1,   235,    -1,    -1,    -1,   239,   240,   241,   242,   243,
      -1,    -1,    -1,    -1,    -1,    -1,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,    -1,   266,    -1,   268,    -1,    -1,    -1,    -1,   273,
     274,   275,   276,    -1,    -1,    -1,   280,    -1,    -1,   283,
     284,    -1,   286,    -1,    -1,   289,   290,   291,   292,    -1,
      -1,   295,   296,    -1,    -1,    -1,    -1,    -1,    -1,   303,
     304,   305,   306,   307,   308,    -1,   310,   311,   312,    -1,
     314,    -1,    -1,    -1,    -1,   319,   320,    -1,    -1,    -1,
      -1,   325,    -1,    -1,    -1,    -1,    -1,   331,    -1,    -1,
      -1,    -1,   336,   337,   338,    -1,    -1,    -1,    -1,    -1,
     344,   345,    -1,   347,   348,    -1,    -1,    -1,    -1,   353,
     354,    -1,    -1,    -1,    -1,     6,     7,     8,     9,    10,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   372,   373,
     374,    22,    23,    -1,    -1,    26,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,    -1,
      41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      51,    52,    53,    54,    -1,    56,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,    69,    70,
      71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    83,    84,    85,    86,    -1,    -1,    89,    -1,
      -1,    92,    -1,    -1,    -1,    -1,    -1,    98,    -1,    -1,
      -1,    -1,   103,   104,   105,   123,    -1,    -1,    -1,    -1,
      -1,   112,    -1,   114,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   124,    -1,   143,   127,    -1,    -1,   130,
     131,   132,    -1,   134,   135,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     151,   152,    -1,    -1,   155,    -1,   157,   158,   159,   160,
     161,   162,   163,   181,   165,    -1,   167,   168,   169,   170,
      -1,   172,    -1,   174,    -1,    -1,    -1,    -1,   179,    -1,
      -1,    -1,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,    -1,    -1,    -1,   213,   214,   215,    -1,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   227,   228,   229,    -1,
      -1,   232,    -1,    -1,   235,    -1,    -1,    -1,   239,   240,
     241,   242,   243,    -1,    -1,    -1,    -1,    -1,    -1,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,    -1,   266,    -1,   268,    -1,    -1,
      -1,    -1,   273,   274,   275,   276,    -1,    -1,    -1,   280,
      -1,    -1,   283,   284,    -1,   286,    -1,    -1,   289,   290,
     291,   292,    -1,    -1,   295,   296,    -1,    -1,    -1,    -1,
      -1,    -1,   303,   304,   305,   306,   307,   308,    -1,   310,
     311,   312,    -1,   314,    -1,    -1,    -1,    -1,   319,   320,
      -1,    -1,    -1,    -1,   325,    -1,    -1,    -1,    -1,    -1,
     331,    -1,    -1,    -1,    -1,   336,    -1,   338,    -1,    -1,
      -1,    -1,    -1,   344,   345,    -1,   347,   348,    -1,    -1,
      -1,    -1,   353,   354,    -1,    -1,    -1,    -1,     6,     7,
       8,     9,    10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   372,   373,   374,    22,    23,    -1,    -1,    26,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      38,    -1,    -1,    41,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    51,    52,    53,    54,    -1,    56,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,    -1,
      -1,    -1,    -1,    71,    72,    -1,    74,    75,    76,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,    -1,
      -1,    89,    -1,    -1,    92,    -1,    -1,    -1,    -1,    -1,
      98,    -1,    -1,    -1,    -1,   103,   104,   105,    -1,    -1,
      -1,    -1,    -1,    -1,   112,    -1,   114,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   124,   143,    -1,   127,
      -1,    -1,   130,   131,   132,    -1,   134,   135,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   151,   152,    -1,    -1,   155,    -1,   157,
     158,   159,   160,   161,   162,   163,    -1,   165,    -1,   167,
     168,   169,   170,   189,   172,    -1,   174,    -1,    -1,    -1,
      -1,   179,   180,    -1,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,    -1,    -1,    -1,   213,   214,   215,
      -1,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   227,
     228,    -1,    -1,    -1,   232,    -1,    -1,   235,    -1,    -1,
      -1,   239,   240,   241,   242,   243,    -1,    -1,    -1,    -1,
      -1,    -1,   250,    -1,    -1,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,    -1,   266,    -1,
      -1,    -1,    -1,    -1,    -1,   273,    -1,    -1,   276,    -1,
      -1,    -1,   280,    -1,    -1,   283,   284,    -1,   286,    -1,
      -1,   289,    -1,   291,    -1,    -1,    -1,   295,   296,    -1,
      -1,   299,    -1,    -1,   302,   303,   304,   305,   306,   307,
     308,    -1,   310,   311,   312,    -1,   314,    -1,    -1,    -1,
      -1,   319,   320,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     6,     7,     8,
       9,    10,    -1,    -1,    -1,    -1,   344,   345,    -1,   347,
     348,    -1,    -1,    22,    23,   353,   354,    26,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,
      -1,    -1,    41,    -1,   372,   373,   374,    -1,    -1,    -1,
      -1,    -1,    51,    52,    53,    54,    -1,    56,    -1,    -1,
      59,    60,    61,    -1,    -1,    -1,    65,    66,    67,    68,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,    -1,    -1,
      89,    -1,    -1,    92,    -1,    -1,    -1,    -1,    -1,    98,
      -1,    -1,    -1,    -1,   103,   104,   105,    -1,    -1,    -1,
      -1,    -1,    -1,   112,    -1,   114,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   124,    -1,   143,   127,    -1,
      -1,   130,   131,   132,    -1,   134,   135,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   151,   152,    -1,    -1,   155,    -1,   157,   158,
     159,   160,   161,   162,   163,   181,   165,    -1,   167,   168,
     169,   170,    -1,   172,    -1,   174,    -1,    -1,    -1,    -1,
     179,   180,    -1,    -1,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,    -1,    -1,    -1,   213,   214,   215,
      -1,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   227,   228,
      -1,    -1,    -1,   232,    -1,    -1,   235,    -1,    -1,    -1,
     239,   240,   241,   242,   243,    -1,    -1,    -1,    -1,    -1,
      -1,   250,    -1,    -1,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,    -1,   266,    -1,    -1,
      -1,    -1,    -1,    -1,   273,    -1,    -1,   276,    -1,    -1,
      -1,   280,    -1,    -1,   283,   284,    -1,   286,    -1,    -1,
     289,    -1,   291,    -1,    -1,    -1,   295,   296,    -1,    -1,
      -1,    -1,    -1,    -1,   303,   304,   305,   306,   307,   308,
      -1,   310,   311,   312,    -1,   314,    -1,    -1,    -1,    -1,
     319,   320,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     6,     7,     8,     9,
      10,    -1,    -1,    -1,    -1,   344,   345,    17,   347,   348,
      -1,    -1,    22,    23,   353,   354,    26,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,
      -1,    41,    -1,   372,   373,   374,    -1,    -1,    -1,    -1,
      -1,    51,    52,    53,    54,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    62,    -1,    -1,    -1,    66,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    86,    -1,    -1,    89,
      -1,    -1,    92,    -1,    -1,    -1,    -1,    -1,    98,    -1,
      -1,    -1,    -1,   103,   104,   105,    -1,    -1,    -1,    -1,
      -1,    -1,   112,    -1,   114,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   124,    -1,   143,   127,    -1,    -1,
     130,   131,   132,    -1,   134,   135,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   151,   152,    -1,    -1,   155,    -1,   157,   158,   159,
     160,   161,   162,   163,   181,   165,    -1,   167,   168,   169,
     170,    -1,   172,    -1,   174,    -1,    -1,    -1,    -1,   179,
      -1,    -1,    -1,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   209,    -1,    -1,    -1,   213,   214,   215,    -1,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   227,   228,   229,
     230,   231,   232,    -1,    -1,   235,    -1,    -1,    -1,   239,
     240,   241,   242,   243,    -1,    -1,    -1,    -1,    -1,    -1,
     250,    -1,    -1,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,    -1,   266,    -1,    -1,    -1,
      -1,    -1,    -1,   273,    -1,    -1,   276,    -1,    -1,    -1,
     280,    -1,    -1,   283,   284,    -1,   286,    -1,    -1,   289,
      -1,   291,    -1,    -1,    -1,   295,   296,    -1,    -1,    -1,
      -1,    -1,    -1,   303,   304,   305,   306,   307,   308,    -1,
     310,   311,   312,    -1,   314,    -1,    -1,    -1,    -1,   319,
     320,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     6,     7,     8,     9,    10,
      -1,    -1,    -1,    -1,   344,   345,    -1,   347,   348,    -1,
      -1,    22,    23,   353,   354,    26,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,    -1,
      41,    -1,   372,   373,   374,    -1,    -1,    -1,    -1,    -1,
      51,    52,    53,    54,    -1,    56,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    86,    -1,    -1,    89,    -1,
      -1,    92,    -1,    -1,    -1,    -1,    -1,    98,    -1,    -1,
      -1,    -1,   103,   104,   105,    -1,    -1,    -1,    -1,    -1,
      -1,   112,    -1,   114,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   124,    -1,   143,   127,    -1,    -1,   130,
     131,   132,    -1,   134,   135,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     151,   152,    -1,    -1,   155,    -1,   157,   158,   159,   160,
     161,   162,   163,   181,   165,    -1,   167,   168,   169,   170,
      -1,   172,    -1,   174,    -1,    -1,    -1,    -1,   179,    -1,
      -1,    -1,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,    -1,    -1,    -1,   213,   214,   215,    -1,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   227,   228,    -1,    -1,
      -1,   232,    -1,    -1,   235,    -1,    -1,    -1,   239,   240,
     241,   242,   243,   244,   245,   246,   247,    -1,    -1,   250,
      -1,    -1,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,    -1,   266,    -1,    -1,    -1,    -1,
      -1,    -1,   273,    -1,    -1,   276,    -1,    -1,    -1,   280,
      -1,    -1,   283,   284,    -1,   286,    -1,    -1,   289,    -1,
     291,    -1,    -1,    -1,   295,   296,    -1,    -1,    -1,    -1,
      -1,    -1,   303,   304,   305,   306,   307,   308,    -1,   310,
     311,   312,    -1,   314,    -1,    -1,    -1,    -1,   319,   320,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   344,   345,    -1,   347,   348,    -1,    -1,
      -1,    -1,   353,   354,    -1,    -1,    -1,    -1,     6,     7,
       8,     9,    10,    -1,    -1,    -1,    -1,    -1,    -1,   370,
      -1,   372,   373,   374,    22,    23,    -1,    -1,    26,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      38,    -1,    -1,    41,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    51,    52,    53,    54,    -1,    56,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,    -1,
      -1,    -1,    -1,    -1,    72,    -1,    74,    75,    76,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,    -1,
      -1,    89,    -1,    -1,    92,    -1,    -1,    -1,    -1,    -1,
      98,    -1,    -1,    -1,    -1,   103,   104,   105,    -1,    -1,
      -1,    -1,    -1,    -1,   112,    -1,   114,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   124,    -1,   143,   127,
      -1,    -1,   130,   131,   132,    -1,   134,   135,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   151,   152,    -1,    -1,   155,    -1,   157,
     158,   159,   160,   161,   162,   163,   181,   165,    -1,   167,
     168,   169,   170,    -1,   172,    -1,   174,    -1,    -1,    -1,
      -1,   179,   180,    -1,    -1,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,    -1,    -1,    -1,   213,   214,
     215,    -1,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   227,
     228,    -1,    -1,    -1,   232,    -1,    -1,   235,    -1,    -1,
      -1,   239,   240,   241,   242,   243,    -1,    -1,    -1,    -1,
      -1,    -1,   250,    -1,    -1,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,    -1,   266,    -1,
      -1,    -1,    -1,    -1,    -1,   273,    -1,    -1,   276,    -1,
      -1,    -1,   280,    -1,    -1,   283,   284,    -1,   286,    -1,
      -1,   289,    -1,   291,    -1,    -1,    -1,   295,   296,    -1,
      -1,    -1,    -1,    -1,    -1,   303,   304,   305,   306,   307,
     308,    -1,   310,   311,   312,    -1,   314,    -1,    -1,    -1,
      -1,   319,   320,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     6,     7,     8,
       9,    10,    -1,    -1,    -1,    -1,   344,   345,    -1,   347,
     348,    -1,    -1,    22,    23,   353,   354,    26,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,
      -1,    -1,    41,    -1,   372,   373,   374,    -1,    -1,    -1,
      -1,    -1,    51,    52,    53,    54,    -1,    56,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,
      -1,    -1,    -1,    72,    -1,    -1,    75,    76,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,    -1,    -1,
      89,    -1,    -1,    92,    -1,    -1,    -1,    -1,    -1,    98,
      -1,    -1,    -1,    -1,   103,   104,   105,    -1,    -1,    -1,
      -1,    -1,    -1,   112,    -1,   114,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   124,    -1,   143,   127,    -1,
      -1,   130,   131,   132,    -1,   134,   135,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   151,   152,    -1,    -1,   155,    -1,   157,   158,
     159,   160,   161,   162,   163,   181,   165,    -1,   167,   168,
     169,   170,    -1,   172,    -1,   174,    -1,    -1,    -1,    -1,
     179,    -1,    -1,    -1,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,    -1,    -1,    -1,   213,   214,   215,
      -1,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,    -1,    -1,    -1,   213,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   227,   228,
      -1,    -1,    -1,   232,    -1,    -1,   235,    -1,    -1,    -1,
     239,   240,   241,   242,   243,    -1,    -1,    -1,    -1,    -1,
      -1,   250,    -1,    -1,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,    -1,   266,    -1,    -1,
      -1,    -1,    -1,    -1,   273,    -1,    -1,   276,    -1,    -1,
      -1,   280,    -1,    -1,   283,   284,    -1,   286,    -1,    -1,
     289,    -1,   291,    -1,    -1,    -1,   295,   296,    -1,    -1,
      -1,    -1,    -1,    -1,   303,   304,   305,   306,   307,   308,
      -1,   310,   311,   312,    -1,   314,    -1,    -1,    -1,    -1,
     319,   320,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     6,     7,     8,     9,
      10,    -1,    -1,    -1,    -1,   344,   345,    -1,   347,   348,
      -1,    -1,    22,    23,   353,   354,    26,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,
      -1,    41,    -1,   372,   373,   374,    -1,    -1,    -1,    -1,
      -1,    51,    52,    53,    54,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,    -1,
      -1,    -1,    72,    -1,    -1,    75,    76,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    86,    -1,    -1,    89,
      -1,    -1,    92,    -1,    -1,    -1,    -1,    -1,    98,    -1,
      -1,    -1,    -1,   103,   104,   105,    -1,    -1,    -1,    -1,
      -1,    -1,   112,    -1,   114,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   124,   143,    -1,   127,    -1,    -1,
     130,   131,   132,    -1,   134,   135,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   151,   152,    -1,    -1,   155,    -1,   157,   158,   159,
     160,   161,   162,   163,    -1,   165,    -1,   167,   168,   169,
     170,    -1,   172,    -1,   174,    -1,    -1,    -1,    -1,   179,
     180,    -1,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,    -1,    -1,    -1,   213,   214,   215,    -1,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   227,   228,    -1,
      -1,    -1,   232,    -1,    -1,   235,    -1,    -1,    -1,   239,
     240,   241,   242,   243,    -1,    -1,    -1,    -1,    -1,    -1,
     250,    -1,    -1,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,    -1,   266,    -1,    -1,    -1,
      -1,    -1,    -1,   273,    -1,    -1,   276,    -1,    -1,    -1,
     280,    -1,    -1,   283,   284,    -1,   286,    -1,    -1,   289,
      -1,   291,    -1,    -1,    -1,   295,   296,    -1,    -1,    -1,
      -1,    -1,    -1,   303,   304,   305,   306,   307,   308,    -1,
     310,   311,   312,    -1,   314,    -1,    -1,    -1,    -1,   319,
     320,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     6,     7,     8,     9,    10,
      -1,    -1,    -1,    -1,   344,   345,    -1,   347,   348,    -1,
      -1,    22,    23,   353,   354,    26,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,    -1,
      41,    -1,   372,   373,   374,    -1,    -1,    -1,    -1,    -1,
      51,    52,    53,    54,    -1,    56,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,    -1,    -1,
      -1,    72,    -1,    -1,    75,    76,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    86,    -1,    -1,    89,    -1,
      -1,    92,    -1,    -1,    -1,    -1,    -1,    98,    -1,    -1,
      -1,    -1,   103,   104,   105,    -1,    -1,    -1,    -1,    -1,
      -1,   112,    -1,   114,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   124,    -1,    -1,   127,    -1,    -1,   130,
     131,   132,    -1,   134,   135,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     151,   152,    -1,    -1,   155,    -1,   157,   158,   159,   160,
     161,   162,   163,    -1,   165,    -1,   167,   168,   169,   170,
      -1,   172,    -1,   174,    -1,    -1,    -1,    -1,   179,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   213,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   227,   228,    -1,    -1,
      -1,   232,    -1,    -1,   235,    -1,    -1,    -1,   239,   240,
     241,   242,   243,    -1,    -1,    -1,    -1,    -1,    -1,   250,
      -1,    -1,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,    -1,   266,    -1,    -1,    -1,    -1,
      -1,    -1,   273,    -1,    -1,   276,    -1,    -1,    -1,   280,
      -1,    -1,   283,   284,    -1,   286,    -1,    -1,   289,    -1,
     291,    -1,    -1,    -1,   295,   296,    -1,    -1,    -1,    -1,
      -1,    -1,   303,   304,   305,   306,   307,   308,    -1,   310,
     311,   312,    -1,   314,    -1,    -1,    -1,    -1,   319,   320,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     6,     7,     8,     9,    10,    -1,
      -1,    -1,    -1,   344,   345,    -1,   347,   348,    -1,    -1,
      22,    23,   353,   354,    26,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,    -1,    41,
      -1,   372,   373,   374,    -1,    -1,    -1,    -1,    -1,    51,
      52,    53,    54,    -1,    56,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    66,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    86,    -1,    -1,    89,    -1,    -1,
      92,    -1,    -1,    -1,    -1,    -1,    98,    -1,    -1,    -1,
      -1,   103,   104,   105,    -1,    -1,    -1,    -1,    -1,    -1,
     112,    -1,   114,    -1,    -1,   117,   118,    -1,   120,    -1,
      -1,    -1,   124,    -1,    -1,   127,    -1,    -1,   130,   131,
     132,    -1,   134,   135,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   151,
     152,    -1,    -1,   155,    -1,   157,   158,   159,   160,   161,
     162,   163,    -1,   165,    -1,   167,   168,   169,   170,    -1,
     172,    -1,   174,    -1,    -1,    -1,    -1,   179,   180,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   227,   228,    -1,    -1,    -1,
     232,    -1,    -1,   235,    -1,    -1,    -1,   239,   240,   241,
     242,   243,    -1,    -1,    -1,    -1,    -1,    -1,   250,    -1,
      -1,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,    -1,   266,    -1,    -1,    -1,    -1,    -1,
      -1,   273,    -1,    -1,   276,    -1,    -1,    -1,   280,    -1,
      -1,   283,   284,    -1,   286,    -1,    -1,   289,    -1,   291,
      -1,    -1,    -1,   295,   296,    -1,    -1,    -1,    -1,    -1,
      -1,   303,   304,   305,   306,   307,   308,    -1,   310,   311,
     312,    -1,   314,    -1,    -1,    -1,    -1,   319,   320,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     6,     7,     8,     9,    10,    -1,    -1,
      -1,    -1,   344,   345,    -1,   347,   348,    -1,    -1,    22,
      23,   353,   354,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    38,    -1,    -1,    41,    -1,
     372,   373,   374,    -1,    -1,    -1,    -1,    -1,    51,    52,
      53,    54,    -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    66,    -1,    -1,    -1,    -1,    -1,    72,
      -1,    -1,    75,    76,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    86,    -1,    -1,    89,    -1,    -1,    92,
      -1,    -1,    -1,    -1,    -1,    98,    -1,    -1,    -1,    -1,
     103,   104,   105,    -1,    -1,    -1,    -1,    -1,    -1,   112,
      -1,   114,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   124,    -1,    -1,   127,    -1,    -1,   130,   131,   132,
      -1,   134,   135,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   151,   152,
      -1,    -1,   155,    -1,   157,   158,   159,   160,   161,   162,
     163,    -1,   165,    -1,   167,   168,   169,   170,    -1,   172,
      -1,   174,    -1,    -1,    -1,    -1,   179,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   227,   228,    -1,    -1,    -1,   232,
      -1,    -1,   235,    -1,    -1,    -1,   239,   240,   241,   242,
     243,    -1,    -1,    -1,    -1,    -1,    -1,   250,    -1,    -1,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,    -1,   266,    -1,    -1,    -1,    -1,    -1,    -1,
     273,    -1,    -1,   276,    -1,    -1,    -1,   280,    -1,    -1,
     283,   284,    -1,   286,    -1,    -1,   289,    -1,   291,    -1,
      -1,    -1,   295,   296,    -1,    -1,    -1,    -1,    -1,    -1,
     303,   304,   305,   306,   307,   308,    -1,   310,   311,   312,
      -1,   314,    -1,    -1,    -1,    -1,   319,   320,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     6,     7,     8,     9,    10,    -1,    -1,    -1,
      -1,   344,   345,    -1,   347,   348,    -1,    -1,    22,    23,
     353,   354,    26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    38,    -1,    -1,    41,    -1,   372,
     373,   374,    -1,    -1,    -1,    -1,    -1,    51,    52,    53,
      54,    -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    66,    -1,    -1,    -1,    -1,    71,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    86,    -1,    -1,    89,    -1,    -1,    92,    -1,
      -1,    -1,    -1,    -1,    98,    -1,    -1,    -1,    -1,   103,
     104,   105,    -1,    -1,    -1,    -1,    -1,    -1,   112,    -1,
     114,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     124,    -1,    -1,   127,    -1,    -1,   130,   131,   132,    -1,
     134,   135,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   151,   152,    -1,
      -1,   155,    -1,   157,   158,   159,   160,   161,   162,   163,
      -1,   165,    -1,   167,   168,   169,   170,    -1,   172,    -1,
     174,    -1,    -1,    -1,    -1,   179,   180,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   227,   228,    -1,    -1,    -1,   232,    -1,
      -1,   235,    -1,    -1,    -1,   239,   240,   241,   242,   243,
      -1,    -1,    -1,    -1,    -1,    -1,   250,    -1,    -1,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,    -1,   266,    -1,    -1,    -1,    -1,    -1,    -1,   273,
      -1,    -1,   276,    -1,    -1,    -1,   280,    -1,    -1,   283,
     284,    -1,   286,    -1,    -1,   289,    -1,   291,    -1,    -1,
      -1,   295,   296,    -1,    -1,   299,    -1,    -1,    -1,   303,
     304,   305,   306,   307,   308,    -1,   310,   311,   312,    -1,
     314,    -1,    -1,    -1,    -1,   319,   320,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     6,     7,     8,     9,    10,    -1,    -1,    -1,    -1,
     344,   345,    -1,   347,   348,    -1,    -1,    22,    23,   353,
     354,    26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    38,    -1,    -1,    41,    -1,   372,   373,
     374,    -1,    -1,    -1,    -1,    -1,    51,    52,    53,    54,
      -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    66,    -1,    -1,    -1,    -1,    -1,    72,    -1,    -1,
      75,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    86,    -1,    -1,    89,    -1,    -1,    92,    -1,    -1,
      -1,    -1,    -1,    98,    -1,    -1,    -1,    -1,   103,   104,
     105,    -1,    -1,    -1,    -1,    -1,    -1,   112,    -1,   114,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   124,
      -1,    -1,   127,    -1,    -1,   130,   131,   132,    -1,   134,
     135,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   151,   152,    -1,    -1,
     155,    -1,   157,   158,   159,   160,   161,   162,   163,    -1,
     165,    -1,   167,   168,   169,   170,    -1,   172,    -1,   174,
      -1,    -1,    -1,    -1,   179,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   227,   228,    -1,    -1,    -1,   232,    -1,    -1,
     235,    -1,    -1,    -1,   239,   240,   241,   242,   243,    -1,
      -1,    -1,    -1,    -1,    -1,   250,    -1,    -1,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
      -1,   266,    -1,    -1,    -1,    -1,    -1,    -1,   273,    -1,
      -1,   276,    -1,    -1,    -1,   280,    -1,    -1,   283,   284,
      -1,   286,    -1,    -1,   289,    -1,   291,    -1,    -1,    -1,
     295,   296,    -1,    -1,    -1,    -1,    -1,    -1,   303,   304,
     305,   306,   307,   308,    -1,   310,   311,   312,    -1,   314,
      -1,    -1,    -1,    -1,   319,   320,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       6,     7,     8,     9,    10,    -1,    -1,    -1,    -1,   344,
     345,    -1,   347,   348,    -1,    -1,    22,    23,   353,   354,
      26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    38,    -1,    -1,    41,    -1,   372,   373,   374,
      -1,    -1,    -1,    -1,    -1,    51,    52,    53,    54,    -1,
      56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      86,    -1,    -1,    89,    -1,    -1,    92,    -1,    -1,    -1,
      -1,    -1,    98,    -1,    -1,    -1,    -1,   103,   104,   105,
      -1,    -1,    -1,    -1,    -1,    -1,   112,    -1,   114,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   124,    -1,
      -1,   127,    -1,    -1,   130,   131,   132,    -1,   134,   135,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   151,   152,    -1,    -1,   155,
      -1,   157,   158,   159,   160,   161,   162,   163,    -1,   165,
      -1,   167,   168,   169,   170,    -1,   172,    -1,   174,    -1,
      -1,    -1,    -1,   179,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   193,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   227,   228,    -1,    -1,    -1,   232,    -1,    -1,   235,
      -1,   237,    -1,   239,   240,   241,   242,   243,    -1,    -1,
      -1,    -1,    -1,    -1,   250,    -1,    -1,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,    -1,
     266,    -1,    -1,    -1,    -1,    -1,    -1,   273,    -1,    -1,
     276,    -1,    -1,    -1,   280,    -1,    -1,   283,   284,    -1,
     286,    -1,    -1,   289,    -1,   291,    -1,    -1,    -1,   295,
     296,    -1,    -1,    -1,    -1,    -1,    -1,   303,   304,   305,
     306,   307,   308,    -1,   310,   311,   312,    -1,   314,    -1,
      -1,    -1,    -1,   319,   320,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     6,
       7,     8,     9,    10,    -1,    -1,    -1,    -1,   344,   345,
      -1,   347,   348,    -1,    -1,    22,    23,   353,   354,    26,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    38,    -1,    -1,    41,    -1,   372,   373,   374,    -1,
      -1,    -1,    -1,    -1,    51,    52,    53,    54,    -1,    56,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,
      -1,    -1,    89,    -1,    -1,    92,    -1,    -1,    -1,    -1,
      -1,    98,    -1,    -1,    -1,    -1,   103,   104,   105,    -1,
      -1,    -1,    -1,    -1,    -1,   112,    -1,   114,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   124,    -1,    -1,
     127,    -1,    -1,   130,   131,   132,    -1,   134,   135,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   151,   152,    -1,    -1,   155,    -1,
     157,   158,   159,   160,   161,   162,   163,    -1,   165,    -1,
     167,   168,   169,   170,    -1,   172,    -1,   174,    -1,    -1,
      -1,    -1,   179,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     227,   228,    -1,    -1,    -1,   232,    -1,    -1,   235,    -1,
      -1,    -1,   239,   240,   241,   242,   243,    -1,    -1,    -1,
      -1,    -1,    -1,   250,    -1,    -1,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,    -1,   266,
      -1,    -1,    -1,    -1,    -1,    -1,   273,    -1,    -1,   276,
      -1,    -1,    -1,   280,    -1,    -1,   283,   284,    -1,   286,
      -1,    -1,   289,   290,   291,    -1,    -1,    -1,   295,   296,
      -1,    -1,    -1,    -1,    -1,    -1,   303,   304,   305,   306,
     307,   308,    -1,   310,   311,   312,    -1,   314,    -1,    -1,
      -1,    -1,   319,   320,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     6,     7,
       8,     9,    10,    -1,    -1,    -1,    -1,   344,   345,    -1,
     347,   348,    -1,    -1,    22,    23,   353,   354,    26,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      38,    -1,    -1,    41,    -1,   372,   373,   374,    -1,    -1,
      -1,    -1,    -1,    51,    52,    53,    54,    -1,    56,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,    -1,
      -1,    89,    -1,    -1,    92,    -1,    -1,    -1,    -1,    -1,
      98,    -1,    -1,    -1,    -1,   103,   104,   105,    -1,    -1,
      -1,    -1,    -1,    -1,   112,    -1,   114,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   124,    -1,    -1,   127,
      -1,    -1,   130,   131,   132,    -1,   134,   135,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   151,   152,    -1,    -1,   155,    -1,   157,
     158,   159,   160,   161,   162,   163,    -1,   165,    -1,   167,
     168,   169,   170,    -1,   172,    -1,   174,    -1,    -1,    -1,
      -1,   179,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   196,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   227,
     228,    -1,    -1,    -1,   232,    -1,    -1,   235,    -1,    -1,
      -1,   239,   240,   241,   242,   243,    -1,    -1,    -1,    -1,
      -1,    -1,   250,    -1,    -1,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,    -1,   266,    -1,
      -1,    -1,    -1,    -1,    -1,   273,    -1,    -1,   276,    -1,
      -1,    -1,   280,    -1,    -1,   283,   284,    -1,   286,    -1,
      -1,   289,    -1,   291,    -1,    -1,    -1,   295,   296,    -1,
      -1,    -1,    -1,    -1,    -1,   303,   304,   305,   306,   307,
     308,    -1,   310,   311,   312,    -1,   314,    -1,    -1,    -1,
      -1,   319,   320,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     6,     7,     8,
       9,    10,    -1,    -1,    -1,    -1,   344,   345,    -1,   347,
     348,    -1,    -1,    22,    23,   353,   354,    26,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,
      -1,    -1,    41,    -1,   372,   373,   374,    -1,    -1,    -1,
      -1,    -1,    51,    52,    53,    54,    -1,    56,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,    -1,    -1,
      89,    -1,    -1,    92,    -1,    -1,    -1,    -1,    -1,    98,
      -1,    -1,    -1,    -1,   103,   104,   105,    -1,    -1,    -1,
      -1,    -1,    -1,   112,    -1,   114,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   124,    -1,    -1,   127,    -1,
      -1,   130,   131,   132,    -1,   134,   135,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   151,   152,    -1,    -1,   155,    -1,   157,   158,
     159,   160,   161,   162,   163,    -1,   165,    -1,   167,   168,
     169,   170,    -1,   172,    -1,   174,    -1,    -1,    -1,    -1,
     179,   180,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   227,   228,
      -1,    -1,    -1,   232,    -1,    -1,   235,    -1,    -1,    -1,
     239,   240,   241,   242,   243,    -1,    -1,    -1,    -1,    -1,
      -1,   250,    -1,    -1,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,    -1,   266,    -1,    -1,
      -1,    -1,    -1,    -1,   273,    -1,    -1,   276,    -1,    -1,
      -1,   280,    -1,    -1,   283,   284,    -1,   286,    -1,    -1,
     289,    -1,   291,    -1,    -1,    -1,   295,   296,    -1,    -1,
      -1,    -1,    -1,    -1,   303,   304,   305,   306,   307,   308,
      -1,   310,   311,   312,    -1,   314,    -1,    -1,    -1,    -1,
     319,   320,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     6,     7,     8,     9,
      10,    -1,    -1,    -1,    -1,   344,   345,    -1,   347,   348,
      -1,    -1,    22,    23,   353,   354,    26,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,
      -1,    41,    -1,   372,   373,   374,    -1,    -1,    -1,    -1,
      -1,    51,    52,    53,    54,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    86,    -1,    -1,    89,
      -1,    -1,    92,    -1,    -1,    -1,    -1,    -1,    98,    -1,
      -1,    -1,    -1,   103,   104,   105,    -1,    -1,    -1,    -1,
      -1,    -1,   112,    -1,   114,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   124,    -1,    -1,   127,    -1,    -1,
     130,   131,   132,    -1,   134,   135,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   151,   152,    -1,    -1,   155,    -1,   157,   158,   159,
     160,   161,   162,   163,    -1,   165,    -1,   167,   168,   169,
     170,    -1,   172,    -1,   174,    -1,    -1,    -1,    -1,   179,
     180,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   227,   228,    -1,
      -1,    -1,   232,    -1,    -1,   235,    -1,    -1,    -1,   239,
     240,   241,   242,   243,    -1,    -1,    -1,    -1,    -1,    -1,
     250,    -1,    -1,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,    -1,   266,    -1,    -1,    -1,
      -1,    -1,    -1,   273,    -1,    -1,   276,    -1,    -1,    -1,
     280,    -1,    -1,   283,   284,    -1,   286,    -1,    -1,   289,
      -1,   291,    -1,    -1,    -1,   295,   296,    -1,    -1,    -1,
      -1,    -1,    -1,   303,   304,   305,   306,   307,   308,    -1,
     310,   311,   312,    -1,   314,    -1,    -1,    -1,    -1,   319,
     320,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     6,     7,     8,     9,    10,
      -1,    -1,    -1,    -1,   344,   345,    -1,   347,   348,    -1,
      -1,    22,    23,   353,   354,    26,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,    -1,
      41,    -1,   372,   373,   374,    -1,    -1,    -1,    -1,    -1,
      51,    52,    53,    54,    -1,    56,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    86,    -1,    -1,    89,    -1,
      -1,    92,    -1,    -1,    -1,    -1,    -1,    98,    -1,    -1,
      -1,    -1,   103,   104,   105,    -1,    -1,    -1,    -1,    -1,
      -1,   112,    -1,   114,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   124,    -1,    -1,   127,    -1,    -1,   130,
     131,   132,    -1,   134,   135,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     151,   152,    -1,    -1,   155,    -1,   157,   158,   159,   160,
     161,   162,   163,    -1,   165,    -1,   167,   168,   169,   170,
      -1,   172,    -1,   174,    -1,    -1,    -1,    -1,   179,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   213,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   227,   228,    -1,    -1,
      -1,   232,    -1,    -1,   235,    -1,    -1,    -1,   239,   240,
     241,   242,   243,    -1,    -1,    -1,    -1,    -1,    -1,   250,
      -1,    -1,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,    -1,   266,    -1,    -1,    -1,    -1,
      -1,    -1,   273,    -1,    -1,   276,    -1,    -1,    -1,   280,
      -1,    -1,   283,   284,    -1,   286,    -1,    -1,   289,    -1,
     291,    -1,    -1,    -1,   295,   296,    -1,    -1,    -1,    -1,
      -1,    -1,   303,   304,   305,   306,   307,   308,    -1,   310,
     311,   312,    -1,   314,    -1,    -1,    -1,    -1,   319,   320,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     6,     7,     8,     9,    10,    -1,
      -1,    -1,    -1,   344,   345,    -1,   347,   348,    -1,    -1,
      22,    23,   353,   354,    26,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,    -1,    41,
      -1,   372,   373,   374,    -1,    -1,    -1,    -1,    -1,    51,
      52,    53,    54,    -1,    56,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    66,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    86,    -1,    -1,    89,    -1,    -1,
      92,    -1,    -1,    -1,    -1,    -1,    98,    -1,    -1,    -1,
      -1,   103,   104,   105,    -1,    -1,    -1,    -1,    -1,    -1,
     112,    -1,   114,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   124,    -1,    -1,   127,    -1,    -1,   130,   131,
     132,    -1,   134,   135,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   151,
     152,    -1,    -1,   155,    -1,   157,   158,   159,   160,   161,
     162,   163,    -1,   165,    -1,   167,   168,   169,   170,    -1,
     172,    -1,   174,    -1,    -1,    -1,    -1,   179,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   227,   228,    -1,    -1,    -1,
     232,    -1,    -1,   235,    -1,   237,    -1,   239,   240,   241,
     242,   243,    -1,    -1,    -1,    -1,    -1,    -1,   250,    -1,
      -1,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,    -1,   266,    -1,    -1,    -1,    -1,    -1,
      -1,   273,    -1,    -1,   276,    -1,    -1,    -1,   280,    -1,
      -1,   283,   284,    -1,   286,    -1,    -1,   289,    -1,   291,
      -1,    -1,    -1,   295,   296,    -1,    -1,    -1,    -1,    -1,
      -1,   303,   304,   305,   306,   307,   308,    -1,   310,   311,
     312,    -1,   314,    -1,    -1,    -1,    -1,   319,   320,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     6,     7,     8,     9,    10,    -1,    -1,
      -1,    -1,   344,   345,    -1,   347,   348,    -1,    -1,    22,
      23,   353,   354,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    38,    -1,    -1,    41,    -1,
     372,   373,   374,    -1,    -1,    -1,    -1,    -1,    51,    52,
      53,    54,    -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    66,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    86,    -1,    -1,    89,    -1,    -1,    92,
      -1,    -1,    -1,    -1,    -1,    98,    -1,    -1,    -1,    -1,
     103,   104,   105,    -1,    -1,    -1,    -1,    -1,    -1,   112,
      -1,   114,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   124,    -1,    -1,   127,    -1,    -1,   130,   131,   132,
      -1,   134,   135,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   151,   152,
      -1,    -1,   155,    -1,   157,   158,   159,   160,   161,   162,
     163,    -1,   165,    -1,   167,   168,   169,   170,    -1,   172,
      -1,   174,    -1,    -1,    -1,    -1,   179,   180,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   227,   228,    -1,    -1,    -1,   232,
      -1,    -1,   235,    -1,    -1,    -1,   239,   240,   241,   242,
     243,    -1,    -1,    -1,    -1,    -1,    -1,   250,    -1,    -1,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,    -1,   266,    -1,    -1,    -1,    -1,    -1,    -1,
     273,    -1,    -1,   276,    -1,    -1,    -1,   280,    -1,    -1,
     283,   284,    -1,   286,    -1,    -1,   289,    -1,   291,    -1,
      -1,    -1,   295,   296,    -1,    -1,    -1,    -1,    -1,    -1,
     303,   304,   305,   306,   307,   308,    -1,   310,   311,   312,
      -1,   314,    -1,    -1,    -1,    -1,   319,   320,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     6,     7,     8,     9,    10,    -1,    -1,    -1,
      -1,   344,   345,    -1,   347,   348,    -1,    -1,    22,    23,
     353,   354,    26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    38,    -1,    -1,    41,    -1,   372,
     373,   374,    -1,    -1,    -1,    -1,    -1,    51,    52,    53,
      54,    -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    86,    -1,    -1,    89,    -1,    -1,    92,    -1,
      -1,    -1,    -1,    -1,    98,    -1,    -1,    -1,    -1,   103,
     104,   105,    -1,    -1,    -1,    -1,    -1,    -1,   112,    -1,
     114,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     124,    -1,    -1,   127,    -1,    -1,   130,   131,   132,    -1,
     134,   135,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   151,   152,    -1,
      -1,   155,    -1,   157,   158,   159,   160,   161,   162,   163,
      -1,   165,    -1,   167,   168,   169,   170,    -1,   172,    -1,
     174,    -1,    -1,    -1,    -1,   179,    -1,   181,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   227,   228,    -1,    -1,    -1,   232,    -1,
      -1,   235,    -1,    -1,    -1,   239,   240,   241,   242,   243,
      -1,    -1,    -1,    -1,    -1,    -1,   250,    -1,    -1,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,    -1,   266,    -1,    -1,    -1,    -1,    -1,    -1,   273,
      -1,    -1,   276,    -1,    -1,    -1,   280,    -1,    -1,   283,
     284,    -1,   286,    -1,    -1,   289,    -1,   291,    -1,    -1,
      -1,   295,   296,    -1,    -1,    -1,    -1,    -1,    -1,   303,
     304,   305,   306,   307,   308,    -1,   310,   311,   312,    -1,
     314,    -1,    -1,    -1,    -1,   319,   320,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     6,     7,     8,     9,    10,    -1,    -1,    -1,    -1,
     344,   345,    -1,   347,   348,    -1,    -1,    22,    23,   353,
     354,    26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    38,    -1,    -1,    41,    -1,   372,   373,
     374,    -1,    -1,    -1,    -1,    -1,    51,    52,    53,    54,
      -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    86,    -1,    -1,    89,    -1,    -1,    92,    -1,    -1,
      -1,    -1,    -1,    98,    -1,    -1,    -1,    -1,   103,   104,
     105,    -1,    -1,    -1,    -1,    -1,    -1,   112,    -1,   114,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   124,
      -1,    -1,   127,    -1,    -1,   130,   131,   132,    -1,   134,
     135,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   151,   152,    -1,    -1,
     155,    -1,   157,   158,   159,   160,   161,   162,   163,    -1,
     165,    -1,   167,   168,   169,   170,    -1,   172,    -1,   174,
      -1,    -1,    -1,    -1,   179,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   227,   228,    -1,    -1,    -1,   232,    -1,    -1,
     235,    -1,    -1,    -1,   239,   240,   241,   242,   243,    -1,
      -1,    -1,    -1,    -1,    -1,   250,    -1,    -1,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
      -1,   266,    -1,    -1,    -1,    -1,    -1,    -1,   273,    -1,
      -1,   276,    -1,    -1,    -1,   280,    -1,    -1,   283,   284,
      -1,   286,    -1,    -1,   289,    -1,   291,    -1,    -1,    -1,
     295,   296,    -1,    -1,    -1,    -1,    -1,    -1,   303,   304,
     305,   306,   307,   308,    -1,   310,   311,   312,    -1,   314,
      -1,    -1,    -1,    -1,   319,   320,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       6,     7,     8,     9,    10,    -1,    -1,    -1,    -1,   344,
     345,    -1,   347,   348,    -1,    -1,    22,    23,   353,   354,
      26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    38,    -1,    -1,    41,    -1,   372,   373,   374,
      -1,    -1,    -1,    -1,    -1,    51,    52,    53,    54,    -1,
      56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      86,    -1,    -1,    89,    -1,    -1,    92,    -1,    -1,    -1,
      -1,    -1,    98,    -1,    -1,    -1,    -1,   103,   104,   105,
      -1,    -1,    -1,    -1,    -1,    -1,   112,    -1,   114,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   124,    -1,
      -1,   127,    -1,    -1,   130,   131,   132,    -1,   134,   135,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   151,   152,    -1,    -1,   155,
      -1,   157,   158,   159,   160,   161,   162,   163,    -1,   165,
      -1,   167,   168,   169,   170,    -1,   172,    -1,   174,    -1,
      -1,    -1,    -1,   179,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   227,   228,    -1,    -1,    -1,   232,    -1,    -1,   235,
      -1,    -1,    -1,   239,   240,   241,   242,   243,    -1,    -1,
      -1,    -1,    -1,    -1,   250,    -1,    -1,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,    -1,
     266,    -1,    -1,    -1,    -1,    -1,    -1,   273,    -1,    -1,
     276,    -1,    -1,    -1,   280,    -1,    -1,   283,   284,    -1,
     286,    -1,    -1,   289,    -1,   291,    -1,    -1,    -1,   295,
     296,    -1,    -1,    -1,    -1,    -1,    -1,   303,   304,   305,
     306,   307,   308,    -1,   310,   311,   312,    -1,   314,    -1,
      -1,    -1,    -1,   319,   320,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     6,
       7,     8,     9,    10,    -1,    -1,    -1,    -1,   344,   345,
      -1,   347,   348,    -1,    -1,    22,    23,   353,   354,    26,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    38,    -1,    -1,    41,    -1,   372,   373,   374,    -1,
      -1,    -1,    -1,    -1,    51,    52,    53,    54,    -1,    56,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,
      -1,    -1,    89,    -1,    -1,    92,    -1,    -1,    -1,    -1,
      -1,    98,    -1,    -1,    -1,    -1,   103,   104,   105,    -1,
      -1,    -1,    -1,    -1,    -1,   112,    -1,   114,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   124,    -1,    -1,
     127,    -1,    -1,   130,   131,   132,    -1,   134,   135,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   151,   152,    -1,    -1,   155,    -1,
     157,   158,   159,   160,   161,   162,   163,    -1,   165,    -1,
     167,   168,   169,   170,    -1,   172,    -1,   174,    -1,    -1,
      -1,    -1,   179,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     227,   228,    -1,    -1,    -1,   232,    -1,    -1,   235,    -1,
      -1,    -1,   239,   240,   241,   242,   243,    -1,    -1,    -1,
      -1,    -1,    -1,   250,    -1,    -1,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,    -1,   266,
      -1,    -1,    -1,    -1,    -1,    -1,   273,    -1,    -1,   276,
      -1,    -1,    -1,   280,    -1,    -1,   283,   284,    -1,   286,
      -1,    -1,   289,    -1,   291,    -1,    -1,    -1,   295,   296,
      -1,    -1,    -1,    -1,    -1,    -1,   303,   304,   305,   306,
     307,   308,    -1,   310,   311,   312,    -1,   314,    -1,    -1,
      -1,    -1,   319,   320,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     6,     7,
       8,     9,    10,    -1,    -1,    -1,    -1,   344,   345,    -1,
     347,   348,    -1,    -1,    22,    23,   353,   354,    26,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      38,    -1,    -1,    41,    -1,   372,   373,   374,    -1,    -1,
      -1,    -1,    -1,    51,    52,    53,    54,    -1,    56,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,    -1,
      -1,    89,    -1,    -1,    92,    -1,    -1,    -1,    -1,    -1,
      98,    -1,    -1,    -1,    -1,   103,   104,   105,    -1,    -1,
      -1,    -1,    -1,    -1,   112,    -1,   114,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   124,    -1,    -1,   127,
      -1,    -1,   130,   131,   132,    -1,   134,   135,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   151,   152,    -1,    -1,   155,    -1,   157,
     158,   159,   160,   161,   162,   163,    -1,   165,    -1,   167,
     168,   169,   170,    -1,   172,    -1,   174,    -1,    -1,    -1,
      -1,   179,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   227,
     228,    -1,    -1,    -1,   232,    -1,    -1,   235,    -1,    -1,
      -1,   239,   240,   241,   242,   243,    -1,    -1,    -1,    -1,
      -1,    -1,   250,    -1,    -1,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,    -1,   266,    -1,
      -1,    -1,    -1,    -1,    -1,   273,    -1,    -1,   276,    -1,
      -1,    -1,   280,    -1,    -1,   283,   284,    -1,   286,    -1,
      -1,   289,    -1,   291,    -1,    -1,    -1,   295,   296,    -1,
      -1,    -1,    -1,    -1,    -1,   303,   304,   305,   306,   307,
     308,    -1,   310,   311,   312,    -1,   314,    -1,    -1,    -1,
      -1,   319,   320,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     6,     7,     8,
       9,    10,    -1,    -1,    -1,    -1,   344,   345,    -1,   347,
     348,    -1,    -1,    22,    23,   353,   354,    26,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,
      -1,    -1,    41,    -1,   372,   373,   374,    -1,    -1,    -1,
      -1,    -1,    51,    52,    53,    54,    -1,    56,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,    -1,    -1,
      89,    -1,    -1,    92,    -1,    -1,    -1,    -1,    -1,    98,
      -1,    -1,    -1,    -1,   103,   104,   105,    -1,    -1,    -1,
      -1,    -1,    -1,   112,    -1,   114,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   124,    -1,    -1,   127,    -1,
      -1,   130,   131,   132,    -1,   134,   135,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   151,   152,    -1,    -1,   155,    -1,   157,   158,
     159,   160,   161,   162,   163,    -1,   165,    -1,   167,   168,
     169,   170,    -1,   172,    -1,   174,    -1,    -1,    -1,    -1,
     179,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   227,   228,
      -1,    -1,    -1,   232,    -1,    -1,   235,    -1,    -1,    -1,
     239,   240,   241,   242,   243,    -1,    -1,    -1,    -1,    -1,
      -1,   250,    -1,    -1,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,    -1,   266,    -1,    -1,
      -1,    -1,    -1,    -1,   273,    -1,    -1,   276,    -1,    -1,
      -1,   280,    -1,    -1,   283,   284,    -1,   286,    -1,    -1,
     289,    -1,   291,    -1,    -1,    -1,   295,   296,    -1,    -1,
      -1,    -1,    -1,    -1,   303,   304,   305,   306,   307,   308,
      -1,   310,   311,   312,    -1,   314,    -1,    -1,    -1,    -1,
     319,   320,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     6,     7,     8,     9,
      10,    -1,    -1,    -1,    -1,   344,   345,    -1,   347,   348,
      -1,    -1,    22,    23,   353,   354,    26,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,
      -1,    41,    -1,   372,   373,   374,    -1,    -1,    -1,    -1,
      -1,    51,    52,    53,    54,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    86,    -1,    -1,    89,
      -1,    -1,    92,    -1,    -1,    -1,    -1,    -1,    98,    -1,
      -1,    -1,    -1,   103,   104,   105,    -1,    -1,    -1,    -1,
      -1,    -1,   112,    -1,   114,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   124,    -1,    -1,   127,    -1,    -1,
     130,   131,   132,    -1,   134,   135,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   151,   152,    -1,    -1,   155,    -1,   157,   158,   159,
     160,   161,   162,   163,    -1,   165,    -1,   167,   168,   169,
     170,    -1,   172,    -1,   174,    -1,    -1,    -1,    -1,   179,
      -1,    -1,    -1,    -1,    -1,    -1,     6,     7,     8,     9,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      20,    -1,    -1,    -1,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   227,   228,    -1,
      -1,    -1,   232,    -1,    -1,   235,    56,    57,    58,   239,
     240,   241,   242,   243,    -1,    -1,    -1,    -1,    -1,    -1,
     250,    -1,    -1,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,    -1,   266,    -1,    -1,    -1,
      -1,    -1,    -1,   273,    -1,    -1,   276,    -1,    -1,    -1,
     280,    -1,    -1,   283,   284,    -1,   286,    -1,    -1,   289,
      -1,   291,    -1,    -1,    -1,   295,   296,    -1,    -1,    -1,
      -1,    -1,    -1,   303,   304,   305,   306,   307,   308,    -1,
     310,   311,   312,    -1,   314,    -1,    -1,    -1,    -1,   319,
     320,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    69,    70,    71,    72,    -1,
      -1,    -1,    -1,    -1,   344,   345,    -1,   347,   348,    83,
      84,    85,    86,   353,   354,    -1,    -1,    -1,    92,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   372,   373,   374,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   180,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   295,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   303,   304,   305,   306,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   229,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   238,   239,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   251,   252,    -1,
     254,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   267,   268,    -1,    -1,    -1,    -1,    -1,
     274,   275,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   290,    -1,    -1,   293,
      -1,    -1,    -1,    -1,    -1,   299,    -1,    -1,   302,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   336,    -1,   338
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int16 yystos[] =
{
       0,     1,    55,    69,    70,    71,    72,    83,    84,    85,
      86,    92,   142,   180,   229,   238,   239,   251,   252,   254,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   267,
     268,   274,   275,   290,   293,   299,   302,   336,   338,   382,
     388,   389,   391,   392,   393,   396,   397,   398,   399,   401,
     405,   406,   415,   420,   432,   439,   440,   447,   502,   509,
     514,   522,   543,   557,   561,   562,   563,   564,   573,   574,
     589,   591,   592,   598,   599,   616,   620,   621,   622,   623,
     758,   760,   765,   142,   122,     6,     7,     8,     9,    10,
      22,    23,    26,    38,    41,    51,    52,    53,    54,    56,
      66,    86,    89,    92,    98,   103,   104,   105,   112,   114,
     124,   127,   130,   131,   132,   134,   135,   151,   152,   155,
     157,   158,   159,   160,   161,   162,   163,   165,   167,   168,
     169,   170,   172,   174,   179,   227,   228,   232,   235,   239,
     240,   241,   242,   243,   250,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   266,   273,   276,
     280,   283,   284,   286,   289,   291,   295,   296,   303,   304,
     305,   306,   307,   308,   310,   311,   312,   314,   319,   320,
     344,   345,   347,   348,   353,   354,   372,   373,   374,   722,
     747,   748,   749,   184,   266,   607,   278,    87,   569,   569,
     748,    85,    71,   623,   278,   196,   281,    72,    75,    76,
     691,   692,   693,   748,   722,   385,   384,   386,   387,   295,
     722,     6,     7,     8,     9,    10,    69,    70,    71,    72,
     184,   268,   288,   338,   389,   416,   423,   424,   425,   427,
     428,   429,   744,   745,   746,   274,   277,   421,   422,    62,
      93,    59,   126,   289,   295,   180,   601,   617,   618,   748,
      11,    51,    52,    53,   180,   246,   322,   503,   504,   582,
     588,   616,   622,   735,   750,     0,   383,    11,   736,   752,
     761,   388,   390,    17,    59,    62,   110,   112,   126,   227,
     228,   229,   230,   231,   232,   243,   276,   289,   295,   298,
     448,   449,   456,   469,   174,   244,   245,   246,   247,   300,
     349,   370,   512,    59,   126,   184,   243,   276,   289,   295,
     300,   346,   349,   512,    59,    60,    61,    65,    66,    67,
      68,   180,   276,   289,   304,   508,   716,   717,   718,   719,
     724,   748,   227,   228,   232,   295,   402,   403,   456,   724,
     142,    93,   109,   175,   176,   177,   647,   142,   142,   722,
     114,   753,   348,   699,   748,   376,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    18,
      19,    27,    28,    44,    45,    46,    47,    48,    49,    50,
      65,    67,    68,   119,   120,   125,   133,   144,   145,   146,
     147,   149,   150,   153,   154,   156,   166,   173,   180,   182,
     190,   191,   200,   201,   210,   211,   212,   213,   217,   303,
     304,   305,   306,   325,   329,   330,   378,   380,   604,   626,
     645,   646,   656,   657,   659,   660,   662,   664,   665,   667,
     669,   670,   672,   673,   674,   676,   677,   691,   692,   694,
     696,   697,   698,   700,   701,   702,   716,   720,   721,   723,
     725,   726,   739,   742,   748,   751,   754,   755,   756,   757,
     770,   771,   772,   773,   774,   788,   795,   797,   800,   810,
     811,   841,   722,   198,   570,   570,   748,   607,   181,   722,
     347,   126,   289,   295,   296,   300,   346,   512,   556,   766,
     180,   376,   180,   506,   507,   399,   399,   382,   382,   722,
     128,   129,   590,   753,   506,   506,   286,   506,   122,   278,
     297,   375,   297,   375,   281,   375,   282,   282,   423,   416,
      93,    94,    97,   103,   565,   566,   567,   290,   748,   722,
     331,   394,   394,   265,   602,   605,   645,   692,   748,   375,
     375,   589,   592,   598,   599,   619,   621,   622,   506,    54,
      54,    54,   503,   623,   278,   735,   278,   278,    27,   322,
     339,   399,   180,   184,   736,   759,   227,   228,   748,   227,
     228,   722,   295,   295,   295,   295,   722,   748,   331,   395,
     395,   346,   295,   245,   245,   245,   722,   722,   245,   722,
     748,   722,   512,   722,   748,   394,   394,   394,   722,   394,
     394,   235,   402,   320,   183,   183,   404,   404,   404,   404,
     183,   376,     6,     7,     8,     9,    20,    24,    25,    26,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    56,
      57,    58,   303,   304,   305,   306,   375,   707,   715,   737,
     739,   740,   741,   742,   751,   375,   565,   111,   184,   266,
     624,   624,   624,   321,   648,   699,   757,   748,   290,   748,
     756,   756,   756,   753,   757,   180,   180,    22,   180,   695,
     695,   695,   695,   695,   180,   180,   134,   180,   180,   180,
     180,   180,   180,   180,   180,   180,   180,   180,   180,   616,
     623,   645,   657,   666,   657,   180,   672,   672,   180,   674,
     674,   180,   180,   180,   674,   757,   180,   705,   180,   706,
     200,   201,   703,   326,   645,   730,   731,   180,   180,   657,
     668,   122,   278,   627,   631,   196,   699,   198,   183,   186,
     187,   188,   189,   192,   193,   194,   195,   199,   279,   722,
     143,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   213,   214,   215,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   376,   180,   375,   180,   359,   675,
     757,   757,   376,   757,   753,   180,   265,   504,   507,   600,
      88,    89,   297,   571,   626,   699,   722,   748,   722,   748,
     722,   722,   722,   279,   181,   645,   680,   693,   748,   500,
     748,   323,   650,   142,   142,   590,   138,   138,    42,    43,
     560,   287,   430,   431,   744,   744,   430,   425,   174,   295,
     426,   556,   722,   429,   123,   123,   122,   122,   565,    95,
      96,    98,   104,   375,   271,   272,   455,   270,   302,   433,
      89,   127,   128,   130,   131,   132,   135,   348,   443,   445,
     446,   191,   748,   722,   181,   375,   180,   376,   180,   618,
     348,   181,   722,   342,   588,   757,   722,   278,   735,   322,
     142,   181,   603,   606,   616,   623,   645,   302,    92,   348,
     441,   442,   444,   446,   395,   395,   395,   395,   249,   302,
     413,   190,   235,   407,   748,   722,   748,   395,   506,   351,
     352,   544,   180,   722,   560,   722,   722,   722,   722,   722,
     404,   181,   672,   748,     8,    62,   303,   304,   305,   306,
     720,   748,   748,   645,   748,   753,   180,    21,    22,   180,
     180,   180,    38,   180,   705,   706,   309,   313,   315,   316,
     317,   318,   708,   711,   713,   714,   724,   180,   180,   180,
     180,   180,   402,   645,   652,   653,   178,   625,   625,   625,
     677,   734,   750,   322,   649,   301,   610,   507,   608,   609,
     743,   748,   376,   645,   645,    23,   181,   641,   723,   748,
     307,   308,   310,   311,   312,   314,   318,   319,   708,   709,
     710,   123,   674,   676,   674,   767,   768,   769,   767,   250,
     164,   789,   815,   161,   163,   813,   250,     3,   801,   676,
     126,   812,   813,   767,   623,   181,   181,   181,   181,   375,
     674,   674,   674,   752,   302,   704,   752,   704,   757,   645,
     326,   728,   729,   328,   730,   732,   645,   645,   727,   375,
     379,    74,   180,   611,   632,   633,   671,   691,   722,   748,
     402,   370,   630,   646,   657,   184,   185,   197,   657,   658,
     107,   108,   661,   661,   180,   180,   663,   674,   663,   663,
     663,   657,   658,   119,   182,   669,   674,   674,   674,   674,
     674,   674,   674,   674,   674,   674,   674,   674,   674,   674,
     674,   674,   674,   674,   674,   674,   674,   674,   674,   674,
     213,   181,   184,   213,   266,   680,   748,   698,   181,   184,
     266,   680,   180,   748,    10,   213,   748,   299,   600,    88,
      85,    16,   376,   180,   558,   119,   757,   181,   375,   181,
     375,    14,   677,   735,   255,   400,   560,   302,   375,   418,
     302,   417,   722,   430,   430,    94,   101,   102,   106,   568,
     752,   567,   273,   297,   455,   290,   434,   130,   131,   132,
     111,   302,   703,   703,   734,   737,   445,   270,   267,   270,
     290,   293,   294,   605,   181,   680,   602,   180,   671,   122,
      16,   580,   581,    27,   281,   572,   506,   722,   339,   735,
     181,   375,   455,   302,   737,   444,   722,   722,   722,   722,
     250,   277,   408,   748,   265,   409,   235,   122,   180,   471,
     472,   506,   281,   722,   348,    69,    70,    72,   268,   545,
     213,   541,   542,   748,   560,   560,   560,   560,   558,   748,
     733,   752,    23,   733,   733,   733,   752,    57,   738,   757,
     704,   704,   706,   705,   297,   733,   752,   733,   733,   733,
     733,   737,   233,   234,   654,   375,   111,   623,   623,   623,
     677,   735,   650,   645,   183,   375,   631,   183,   748,   348,
     375,   181,   375,   376,   122,   722,   167,   814,   375,   814,
     814,   748,   776,   180,   674,   790,   791,   792,   375,   676,
     748,   798,   155,   802,   814,   767,   647,   181,   188,   189,
     657,   122,   375,   189,   375,   181,   304,   757,   181,   757,
     714,   327,   645,   728,   732,   645,   337,   375,   375,   181,
     375,   657,   672,   691,   180,   611,   616,   622,   633,   375,
      75,    76,    77,    79,    80,    82,   612,   614,   348,   634,
     748,   634,   635,   635,   376,   627,   628,   629,   748,   610,
     180,   657,   657,   603,   603,   113,   180,   119,   680,   181,
     680,   181,   376,   680,   680,   181,   678,   679,   748,   376,
     748,   633,   748,   181,   559,   737,   645,   748,   277,   431,
     122,   419,   274,   419,   419,   419,    99,   100,    94,   757,
     748,   273,   289,   289,   435,   703,   672,   703,   750,   750,
     297,   237,   295,   296,   437,   438,   297,   438,    72,    94,
     289,   295,   436,   438,   295,   438,   181,   181,   691,   119,
     583,   340,   180,   586,   587,   757,   344,   345,   580,   122,
     506,   606,   273,   703,   471,   471,   471,   471,   748,    60,
      65,   414,    20,   284,   762,   763,   408,   246,   193,   237,
     474,   475,   476,   478,   481,   489,   490,   501,   743,   748,
     348,   722,   471,   503,   350,   281,   181,   375,   737,   560,
     181,   181,   181,   375,   181,   375,   181,   375,   318,   708,
     712,   181,   375,   181,   181,   181,   181,   240,   655,   653,
     180,   324,   651,   672,   609,   610,   605,   737,   737,   723,
     748,   674,   126,   163,   181,   767,   181,   181,   375,   775,
      89,   265,   674,   816,   817,   819,   820,   821,   282,   375,
     786,   348,   793,    90,   151,   796,   375,   799,   111,   803,
     823,   814,   181,   170,   824,   825,   814,   180,   180,   674,
     674,   674,   674,   320,   645,   327,   337,   645,   645,   645,
     634,   635,   181,   181,   181,   633,   612,    81,    81,    78,
     613,   748,   180,   748,   375,   348,   116,   636,   606,   198,
     198,   181,   181,   757,   606,   181,   181,   213,   181,   181,
     181,   360,   681,   748,   281,   376,   181,   375,   282,   414,
     282,    16,   757,   748,   284,   265,   453,   750,   750,   748,
     748,   722,   748,   748,   748,    96,    95,    96,   748,   722,
     748,   722,   475,   348,   549,   757,   587,   572,   375,   583,
     341,   586,   122,   757,   750,   360,   460,   281,   290,   500,
     764,   392,   396,   410,   411,   412,   415,   420,   432,   439,
     557,   691,   722,   748,   181,   375,   269,   285,   298,   498,
     139,   140,   477,   737,   302,   503,   180,   281,   470,   302,
     505,   500,   722,   248,   513,   748,   736,   752,   752,   706,
     752,   241,   242,   641,   677,   752,   181,   181,   181,   148,
     674,   777,   783,   784,   785,   815,   814,   265,   819,   181,
     375,   348,   119,   157,   159,   160,   787,   791,   814,   748,
     794,   152,   152,   181,   676,   814,   134,   158,   676,   804,
     805,   806,   807,   808,   823,   297,   181,   181,   603,   603,
     123,   181,   181,   375,   181,   375,   645,   181,    81,   633,
     633,   180,   500,   628,   180,   111,   115,   644,   181,   657,
     657,   181,   181,   111,   109,   682,   645,   748,   559,   356,
     757,   276,   560,   560,   560,   297,   348,   467,   267,   290,
     467,   757,   375,   181,   757,   180,   577,   577,   586,   250,
     111,   757,   748,   412,   476,   748,   280,   280,   507,   136,
     141,   265,   479,   480,   483,   484,   486,   487,   490,   283,
     302,   473,   500,    83,   236,   358,   546,   295,   540,   737,
      71,    86,    92,   249,   252,   253,   292,   325,   331,   336,
     401,   405,   406,   415,   420,   432,   439,   515,   518,   520,
     521,   522,   526,   528,   534,   536,   537,   557,   561,   562,
     621,   748,   737,   181,   181,   181,   181,   181,   180,   375,
     375,   786,   375,   181,   817,   748,   818,   281,   281,   281,
     281,   181,   181,   348,   822,   823,   375,   119,   160,   809,
     171,   181,   181,   674,   674,   674,   633,    16,   281,   615,
     500,   181,   678,   117,   118,   120,   180,   637,   638,   645,
     645,   680,   111,    91,   367,   369,   683,   684,   326,   596,
     597,   273,   748,   748,   360,   265,   105,   119,   182,   265,
     757,   578,   579,   748,   580,   572,   572,   757,   299,   367,
     457,   302,   468,   507,   507,   137,   485,   645,   483,   119,
     182,   236,   285,   288,   298,   497,   499,   180,    89,   179,
     181,    69,    90,   267,   282,   355,   356,   547,   548,   123,
     551,   552,   180,   607,   250,   523,   524,   722,     6,   295,
     504,   527,   645,   326,   531,   532,   645,   645,   335,   516,
     333,   377,   674,   778,   779,   781,   783,   785,   777,   783,
     119,    89,   119,   119,   119,   748,   805,   281,   281,   181,
      89,   169,   172,   826,   827,   832,   181,   181,   181,   507,
     645,   181,   181,   180,   180,   121,   181,   375,   652,   187,
     361,   368,   645,   685,   686,   688,    73,   182,   596,   757,
     122,   123,   189,   466,   119,   757,   119,   485,   375,   181,
     375,   757,    89,   113,   584,   580,   289,   435,   454,    16,
     281,   459,    59,   455,   288,   348,   119,   180,   280,   722,
     482,   483,   179,    91,    91,   295,   353,   550,   295,   550,
     548,   357,   326,   554,   539,   743,   626,   510,   748,   180,
     371,   511,   757,   180,   645,   328,   531,   533,   326,   529,
     530,   327,   516,   518,   645,   181,   375,   348,   780,   375,
     163,   822,   160,   160,   165,   748,   833,     3,   828,   829,
      89,   162,   165,   834,   835,   837,   838,   180,   639,   640,
     723,   639,   180,   638,   368,   645,   686,   687,   689,   353,
     364,   364,   362,   690,   198,   593,    73,   367,   462,   645,
     119,   180,   757,   579,   113,   583,   584,   284,   748,   372,
     450,   180,   180,   757,   273,   722,   138,   645,   506,   181,
     375,   549,   549,   549,   549,   353,   354,   553,   180,   336,
     401,   405,   415,   420,   519,   520,   555,   561,   562,   621,
     181,   375,   737,   376,   525,   645,   504,   327,   516,   337,
     645,   529,   533,   516,   518,   142,   334,   779,   748,   782,
     783,   168,   830,   830,   165,   748,   840,   829,   839,   836,
     837,   641,   181,   375,   181,   117,   118,   120,   180,   640,
     642,   643,   363,   363,   198,    89,   116,   361,   366,   645,
     327,   593,   131,   297,   299,   461,   464,   645,    63,   585,
     583,   435,   735,   373,   451,   458,   645,   748,   455,   757,
     506,   180,   488,   181,   124,   496,   483,   748,   748,   748,
     748,   645,   335,   743,   748,   181,   375,   181,   516,   518,
     325,   327,   337,   328,   332,   535,   142,   337,   516,   829,
     831,   181,   640,   180,   180,   121,   181,   181,   375,   687,
     365,   353,    69,    70,   594,   327,   367,   463,   645,   181,
     375,    64,   585,   736,   374,   452,   181,   181,   273,   496,
     442,    39,    40,    77,   495,   281,   492,   493,   494,   181,
     517,   737,   645,   142,   516,   325,   516,   645,   337,   337,
     337,   639,   639,   180,   643,   290,    72,   595,   130,   302,
     465,   465,   461,   343,   575,   757,   453,   757,   494,   181,
      69,    70,   281,   493,   281,   492,   337,   519,   327,   331,
     333,   181,   181,   642,   608,   506,   119,   180,    42,    43,
      89,   290,   491,   491,   142,   516,   538,   748,   181,   600,
     299,   576,   735,    41,   119,   265,   535,   181,   375,   735
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int16 yyr1[] =
{
       0,   381,   382,   383,   382,   384,   382,   385,   382,   386,
     382,   387,   382,   382,   382,   382,   382,   382,   382,   388,
     388,   389,   389,   390,   390,   391,   392,   393,   393,   394,
     394,   395,   395,   396,   397,   398,   399,   399,   399,   399,
     399,   399,   399,   399,   399,   399,   399,   400,   400,   401,
     401,   402,   402,   403,   403,   404,   404,   405,   405,   405,
     405,   405,   405,   405,   405,   406,   406,   407,   407,   407,
     408,   409,   409,   410,   410,   411,   411,   412,   412,   412,
     412,   412,   413,   413,   414,   414,   415,   415,   416,   416,
     417,   417,   418,   418,   419,   419,   420,   420,   421,   421,
     422,   422,   423,   423,   424,   424,   425,   425,   426,   426,
     426,   427,   427,   427,   428,   428,   429,   429,   429,   429,
     429,   429,   429,   430,   430,   431,   431,   432,   432,   432,
     432,   432,   432,   432,   432,   432,   432,   432,   432,   432,
     432,   432,   433,   433,   434,   434,   435,   435,   436,   436,
     436,   436,   436,   436,   437,   437,   437,   438,   438,   439,
     439,   439,   439,   439,   439,   439,   439,   440,   440,   440,
     441,   441,   442,   442,   443,   443,   444,   444,   444,   445,
     445,   445,   445,   445,   446,   446,   446,   446,   446,   446,
     446,   446,   447,   448,   448,   448,   448,   449,   449,   450,
     450,   451,   451,   452,   452,   453,   453,   454,   454,   455,
     455,   455,   456,   456,   456,   456,   456,   456,   456,   457,
     457,   458,   459,   459,   460,   460,   461,   462,   462,   463,
     463,   464,   464,   465,   465,   466,   466,   466,   467,   467,
     468,   468,   468,   469,   469,   469,   469,   469,   469,   470,
     470,   470,   470,   471,   471,   472,   473,   473,   473,   474,
     474,   475,   475,   476,   476,   476,   477,   477,   478,   478,
     479,   479,   480,   480,   481,   482,   482,   483,   483,   483,
     484,   485,   486,   487,   487,   488,   488,   489,   490,   490,
     491,   491,   491,   491,   491,   492,   493,   494,   494,   494,
     494,   494,   495,   495,   495,   495,   496,   496,   497,   497,
     497,   497,   497,   497,   498,   498,   498,   499,   500,   500,
     501,   502,   503,   503,   504,   504,   505,   505,   506,   506,
     507,   508,   509,   510,   511,   511,   512,   512,   512,   512,
     512,   512,   512,   512,   512,   512,   513,   513,   514,   514,
     514,   515,   515,   515,   516,   516,   517,   517,   518,   518,
     518,   518,   518,   518,   518,   518,   518,   518,   518,   518,
     519,   519,   519,   519,   519,   519,   519,   519,   520,   520,
     520,   520,   520,   520,   521,   522,   523,   524,   525,   525,
     525,   526,   527,   527,   527,   528,   528,   529,   530,   530,
     531,   532,   532,   533,   533,   534,   535,   535,   535,   536,
     537,   537,   538,   538,   539,   539,   540,   540,   541,   541,
     541,   542,   542,   543,   544,   544,   545,   545,   545,   545,
     545,   546,   546,   547,   547,   548,   548,   548,   548,   549,
     549,   550,   550,   551,   552,   552,   553,   553,   554,   554,
     555,   555,   556,   557,   557,   557,   557,   557,   557,   557,
     557,   557,   558,   558,   558,   559,   559,   560,   560,   560,
     399,   399,   561,   561,   561,   561,   561,   561,   561,   562,
     563,   563,   564,   564,   564,   564,   564,   564,   564,   565,
     565,   566,   566,   567,   567,   567,   567,   568,   568,   568,
     568,   568,   569,   569,   570,   570,   570,   571,   571,   572,
     572,   572,   573,   573,   573,   573,   574,   574,   574,   575,
     575,   576,   576,   577,   577,   578,   578,   579,   579,   580,
     580,   580,   580,   581,   581,   582,   582,   582,   582,   582,
     583,   583,   584,   584,   584,   585,   585,   586,   586,   587,
     587,   588,   588,   588,   588,   589,   590,   590,   590,   591,
     591,   592,   593,   593,   594,   594,   595,   596,   596,   597,
     597,   598,   599,   599,   600,   600,   600,   601,   601,   602,
     602,   603,   603,   604,   605,   605,   606,   606,   606,   607,
     607,   607,   608,   608,   609,   609,   610,   610,   611,   611,
     611,   611,   612,   612,   612,   613,   613,   614,   614,   614,
     615,   615,   399,   616,   617,   617,   618,   619,   619,   619,
     619,   619,   619,   399,   399,   620,   621,   622,   623,   623,
     623,   623,   623,   623,   624,   624,   624,   625,   625,   625,
     626,   627,   628,   629,   629,   630,   630,   631,   631,   632,
     632,   633,   633,   633,   633,   633,   633,   633,   634,   634,
     634,   634,   635,   635,   636,   636,   637,   637,   638,   638,
     638,   638,   638,   639,   639,   640,   640,   641,   641,   642,
     642,   643,   643,   643,   643,   643,   644,   644,   645,   645,
     646,   646,   647,   647,   648,   648,   648,   649,   649,   649,
     650,   650,   650,   650,   651,   651,   651,   652,   652,   653,
     654,   654,   654,   655,   655,   655,   656,   656,   656,   656,
     656,   656,   656,   656,   657,   657,   658,   658,   658,   659,
     659,   659,   659,   660,   660,   661,   661,   661,   662,   662,
     662,   662,   663,   663,   664,   664,   665,   665,   665,   665,
     666,   666,   667,   667,   668,   668,   669,   670,   671,   671,
     672,   672,   673,   673,   673,   673,   673,   673,   673,   673,
     673,   673,   673,   673,   673,   673,   673,   673,   673,   673,
     673,   673,   673,   673,   673,   673,   673,   673,   673,   673,
     674,   674,   675,   675,   675,   676,   676,   676,   676,   676,
     676,   676,   676,   676,   676,   676,   676,   676,   676,   676,
     676,   677,   678,   679,   679,   680,   680,   681,   681,   682,
     682,   683,   683,   684,   684,   684,   685,   685,   686,   686,
     686,   687,   687,   688,   689,   689,   690,   690,   690,   690,
     690,   691,   691,   692,   692,   693,   693,   693,   693,   694,
     694,   694,   694,   694,   694,   695,   695,   696,   696,   696,
     696,   696,   696,   696,   697,   697,   698,   698,   698,   698,
     699,   699,   699,   700,   701,   701,   702,   702,   702,   702,
     702,   702,   702,   702,   702,   702,   702,   703,   703,   703,
     704,   704,   705,   705,   706,   706,   707,   707,   707,   708,
     708,   708,   708,   708,   709,   709,   710,   710,   710,   710,
     710,   710,   710,   710,   711,   712,   712,   713,   713,   714,
     714,   715,   716,   716,   716,   717,   717,   718,   718,   719,
     719,   720,   720,   720,   720,   720,   720,   720,   720,   720,
     720,   720,   720,   720,   720,   720,   720,   720,   721,   722,
     722,   722,   723,   723,   723,   724,   724,   725,   725,   726,
     726,   726,   726,   727,   727,   728,   729,   729,   730,   731,
     731,   732,   732,   733,   734,   735,   736,   737,   737,   737,
     737,   737,   737,   737,   737,   737,   737,   737,   737,   737,
     737,   737,   737,   737,   737,   737,   737,   737,   737,   737,
     737,   737,   737,   737,   737,   737,   737,   737,   737,   737,
     737,   737,   737,   738,   738,   739,   740,   740,   741,   741,
     741,   742,   742,   743,   744,   745,   745,   745,   745,   745,
     746,   747,   747,   747,   747,   747,   747,   748,   749,   749,
     749,   749,   749,   749,   749,   749,   749,   749,   749,   749,
     749,   749,   749,   749,   749,   749,   749,   749,   749,   749,
     749,   749,   749,   749,   749,   749,   749,   749,   749,   749,
     749,   749,   749,   749,   749,   749,   749,   749,   749,   749,
     749,   749,   749,   749,   749,   749,   749,   749,   749,   749,
     749,   749,   749,   749,   749,   749,   749,   749,   749,   749,
     749,   749,   749,   749,   749,   749,   749,   749,   749,   749,
     749,   749,   749,   749,   749,   749,   749,   749,   749,   749,
     749,   749,   749,   749,   749,   749,   749,   749,   749,   749,
     749,   749,   749,   749,   749,   749,   749,   750,   751,   751,
     752,   753,   753,   754,   754,   755,   755,   756,   756,   757,
     757,   758,   759,   759,   760,   761,   761,   762,   762,   763,
     764,   765,   765,   766,   766,   766,   766,   766,   766,   766,
     766,   767,   768,   768,   769,   770,   770,   770,   770,   770,
     770,   770,   770,   770,   770,   771,   772,   773,   774,   775,
     775,   775,   775,   775,   775,   775,   775,   776,   777,   778,
     778,   779,   780,   780,   781,   782,   783,   784,   784,   785,
     786,   786,   787,   787,   787,   787,   787,   788,   789,   789,
     790,   790,   791,   792,   793,   793,   794,   795,   796,   796,
     797,   798,   799,   799,   800,   801,   802,   802,   803,   804,
     804,   805,   805,   806,   807,   808,   808,   809,   809,   810,
     811,   812,   812,   813,   813,   814,   814,   814,   815,   816,
     816,   817,   817,   818,   819,   820,   821,   821,   822,   822,
     823,   823,   824,   824,   825,   826,   826,   827,   827,   828,
     829,   830,   830,   831,   832,   833,   834,   834,   835,   835,
     836,   836,   837,   838,   838,   839,   840,   841
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     0,     4,     0,     4,     0,     4,     0,
       3,     0,     3,     2,     2,     0,     1,     2,     1,     1,
       1,     1,     1,     0,     1,     1,     1,     1,     3,     0,
       2,     0,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     5,     1,     1,     0,     1,     2,
       2,     1,     3,     2,     4,     1,     0,     4,     4,     5,
       4,     4,     4,     4,     4,     7,     5,     1,     2,     3,
       1,     0,     4,     0,     1,     1,     2,     1,     1,     1,
       1,     1,     0,     3,     1,     1,     6,     6,     1,     3,
       0,     3,     0,     3,     0,     2,     6,     6,     0,     3,
       0,     3,     1,     3,     1,     3,     2,     2,     2,     1,
       1,     2,     1,     1,     1,     3,     1,     1,     1,     2,
       2,     2,     1,     1,     3,     1,     1,     7,     8,     6,
       6,     7,     7,     7,     8,     7,     9,     7,     7,     6,
      10,     7,     4,     0,     3,     0,     3,     0,     5,     4,
       5,     4,     5,     5,     3,     3,     3,     1,     0,     2,
       2,     1,     1,     1,     1,     1,     1,     4,     3,     4,
       1,     0,     1,     2,     1,     2,     2,     4,     1,     2,
       1,     4,     3,     1,     4,     3,     2,     3,     2,     2,
       1,     2,     9,     1,     1,     1,     0,     3,    13,     0,
       2,     0,     2,     0,     2,     0,     3,     1,     3,     0,
       1,     1,     4,     6,     6,     5,     8,     5,     6,     1,
       1,     1,     4,     4,     0,     4,     1,     1,     2,     1,
       2,     1,     3,     0,     3,     5,     5,     3,     0,     3,
       0,     6,     4,     1,     1,     2,     2,     2,     2,     0,
       4,     4,     3,     3,     1,     4,     0,     3,     2,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     3,     2,
       0,     1,     1,     2,     6,     1,     3,     1,     1,     1,
       2,     1,     2,     5,     1,     0,     3,     2,     0,     2,
       2,     1,     1,     2,     2,     3,     3,     0,     1,     1,
       2,     2,     0,     1,     1,     1,     0,     2,     2,     1,
       1,     2,     5,     1,     2,     3,     8,     4,     1,     3,
       2,     7,     1,     3,     1,     1,     0,     3,     0,     1,
       3,     3,     6,     3,     1,     1,     1,     1,     1,     2,
       1,     2,     1,     2,     1,     2,     2,     0,    10,     8,
      10,     1,     5,     6,     0,     3,     0,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     4,     1,     0,     1,
       3,     2,     1,     1,     4,     6,     5,     4,     1,     2,
       4,     1,     2,     0,     2,     7,     0,     2,     5,     8,
       0,     2,     0,     1,     2,     4,     4,     1,     1,     1,
       0,     4,     2,     9,     1,     1,     1,     1,     1,     1,
       3,     0,     2,     1,     2,     4,     4,     4,     4,     0,
       1,     0,     1,     3,     0,     3,     1,     1,     0,     4,
       1,     4,     3,     5,     6,     5,     5,     4,     3,     3,
       3,     4,     0,     3,     2,     1,     3,     0,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     2,     3,     4,     3,     4,     3,     0,
       1,     1,     3,     2,     2,     3,     3,     2,     2,     2,
       1,     1,     1,     0,     2,     3,     0,     0,     3,     0,
       2,     2,    14,    12,     6,     9,     7,     6,     7,     0,
       4,     1,     3,     0,     3,     1,     3,     1,     2,     0,
       3,     5,     7,     0,     1,     0,     2,     2,     4,     4,
       0,     3,     0,     1,     2,     0,     2,     1,     3,     1,
       3,     0,     2,     2,     2,     5,     0,     2,     2,     5,
       4,     7,     0,     2,     3,     1,     3,     5,     6,     1,
       2,     9,     4,     5,     0,     2,     1,     3,     5,     1,
       3,     1,     3,     1,     1,     1,     1,     1,     1,     0,
       1,     1,     1,     3,     3,     3,     0,     2,     3,     4,
       5,     5,     0,     1,     2,     0,     1,     1,     1,     1,
       2,     2,     1,     3,     3,     1,     4,     1,     1,     1,
       1,     1,     1,     1,     1,     4,     6,     6,     5,     5,
       5,     2,     3,     1,     0,     1,     1,     0,     1,     5,
       1,     5,     5,     1,     3,     0,     2,     0,     2,     1,
       3,     2,     2,     3,     2,     3,     1,     1,     5,     2,
       4,     1,     0,     1,     0,     3,     1,     3,     1,     4,
       4,     5,     2,     1,     3,     3,     1,     1,     3,     1,
       3,     1,     4,     4,     5,     2,     0,     2,     3,     1,
       3,     1,     0,     3,     0,     2,     2,     0,     2,     2,
       0,     2,     2,     2,     0,     2,     2,     1,     3,     3,
       0,     1,     1,     0,     2,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     1,     1,     1,     3,
       3,     6,     6,     6,     6,     0,     1,     1,     3,     3,
       3,     3,     1,     3,     4,     3,     5,     5,     7,     7,
       1,     3,     2,     2,     1,     3,     3,     3,     3,     3,
       3,     3,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     3,     3,     3,     3,     2,     2,     3,
       1,     1,     4,     2,     0,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     4,     4,     1,     1,     1,
       1,     1,     4,     0,     1,     1,     3,     0,     3,     0,
       3,     0,     3,     1,     1,     1,     1,     1,     2,     2,
       2,     1,     1,     4,     2,     2,     0,     3,     2,     2,
       3,     3,     4,     1,     3,     1,     1,     1,     1,     6,
       2,     2,     2,     2,     2,     0,     2,     8,     8,     6,
       6,     6,     3,     8,     1,     3,     1,     3,     3,     2,
       0,     2,     1,     1,     1,     3,     3,     4,     5,     5,
       4,     6,     3,     4,     5,     5,     1,     1,     1,     0,
       3,     0,     3,     0,     3,     0,     1,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     2,     2,     2,     3,
       1,     2,     1,     1,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     4,     4,
       1,     2,     1,     2,     2,     2,     1,     1,     4,     1,
       3,     5,     1,     3,     5,     1,     3,     6,     6,     6,
       4,     5,     4,     3,     3,     4,     1,     2,     4,     1,
       2,     0,     2,     1,     1,     1,     1,     1,     1,     1,
       4,     4,     4,     1,     4,     1,     1,     1,     1,     1,
       1,     4,     6,     1,     4,     6,     1,     2,     1,     1,
       1,     1,     4,     1,     4,     6,     1,     4,     1,     4,
       6,     1,     1,     1,     1,     1,     1,     2,     1,     1,
       3,     1,     3,     1,     1,     1,     2,     1,     1,     1,
       1,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     0,     2,     1,     2,     1,     2,     1,     2,     1,
       2,     2,     1,     1,     3,     3,     4,     0,     1,     2,
       1,     5,     5,     2,     2,     2,     4,     6,     2,     2,
       1,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     5,     5,     5,     7,     0,
       2,     4,     6,     4,     2,     4,     2,     1,     4,     1,
       3,     2,     0,     2,     1,     1,     2,     1,     3,     1,
       0,     2,     3,     3,     3,     3,     4,     7,     0,     2,
       1,     3,     2,     1,     0,     2,     1,     6,     2,     2,
       7,     1,     0,     2,     8,     1,     0,     3,     1,     1,
       3,     1,     1,     2,     4,     0,     1,     3,     3,     5,
       6,     1,     1,     1,     1,     0,     2,     2,     4,     1,
       3,     1,     1,     1,     1,     3,     2,     2,     0,     1,
       2,     2,     0,     1,     5,     1,     1,     3,     3,     1,
       1,     0,     2,     1,     2,     1,     0,     1,     1,     2,
       0,     1,     2,     2,     2,     1,     1,     6
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (m, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, m); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, mvc *m)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (m);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, mvc *m)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep, m);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule, mvc *m)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)], m);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, m); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, mvc *m)
{
  YY_USE (yyvaluep);
  YY_USE (m);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (mvc *m)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, m);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* sqlstmt: sql SCOLON  */
#line 729 "sql_parser.y"
        {
		if (m->sym) {
			append_symbol(m->sym->data.lval, (yyval.sym));
			(yyval.sym) = m->sym;
		} else {
			m->sym = (yyval.sym) = (yyvsp[-1].sym);
		}
		YYACCEPT;
	}
#line 8117 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 3: /* $@1: %empty  */
#line 739 "sql_parser.y"
                        {
			  if (!m->emode) /* don't replace m_deps/instantiate */
		  	  	m->emode = m_prepare; 
			  m->scanner.as = m->scanner.yycur; 
			}
#line 8127 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 4: /* sqlstmt: prepare $@1 sql SCOLON  */
#line 744 "sql_parser.y"
                        {
			  if (m->sym) {
				append_symbol(m->sym->data.lval, (yyvsp[-1].sym));
				(yyval.sym) = m->sym;
			  } else {
				m->sym = (yyval.sym) = (yyvsp[-1].sym);
			  }
			  YYACCEPT;
			}
#line 8141 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 5: /* $@2: %empty  */
#line 753 "sql_parser.y"
                        {
		  	  m->emode = m_plan;
			  m->scanner.as = m->scanner.yycur; 
			}
#line 8150 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 6: /* sqlstmt: SQL_PLAN $@2 sql SCOLON  */
#line 757 "sql_parser.y"
                        {
			  if (m->sym) {
				append_symbol(m->sym->data.lval, (yyvsp[-1].sym));
				(yyval.sym) = m->sym;
			  } else {
				m->sym = (yyval.sym) = (yyvsp[-1].sym);
			  }
			  YYACCEPT;
			}
#line 8164 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 7: /* $@3: %empty  */
#line 767 "sql_parser.y"
                        {
		  	  m->emod |= mod_explain;
			  m->scanner.as = m->scanner.yycur; 
			}
#line 8173 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 8: /* sqlstmt: SQL_EXPLAIN $@3 sql SCOLON  */
#line 771 "sql_parser.y"
                        {
			  if (m->sym) {
				append_symbol(m->sym->data.lval, (yyvsp[-1].sym));
				(yyval.sym) = m->sym;
			  } else {
				m->sym = (yyval.sym) = (yyvsp[-1].sym);
			  }
			  YYACCEPT;
			}
#line 8187 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 9: /* $@4: %empty  */
#line 781 "sql_parser.y"
                        {
			  if (m->scanner.mode == LINE_1) {
				yyerror(m, "SQL debugging only supported in interactive mode");
				YYABORT;
			  }
		  	  m->emod |= mod_debug;
			  m->scanner.as = m->scanner.yycur; 
			}
#line 8200 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 10: /* sqlstmt: SQL_DEBUG $@4 sqlstmt  */
#line 789 "sql_parser.y"
                        { (yyval.sym) = (yyvsp[0].sym); YYACCEPT; }
#line 8206 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 11: /* $@5: %empty  */
#line 790 "sql_parser.y"
                        {
		  	  m->emod |= mod_trace;
			  m->scanner.as = m->scanner.yycur; 
			}
#line 8215 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 12: /* sqlstmt: SQL_TRACE $@5 sqlstmt  */
#line 794 "sql_parser.y"
                        { (yyval.sym) = (yyvsp[0].sym); YYACCEPT; }
#line 8221 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 13: /* sqlstmt: exec SCOLON  */
#line 795 "sql_parser.y"
                        { m->sym = (yyval.sym) = (yyvsp[-1].sym); YYACCEPT; }
#line 8227 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 14: /* sqlstmt: dealloc SCOLON  */
#line 796 "sql_parser.y"
                        { m->sym = (yyval.sym) = (yyvsp[-1].sym); YYACCEPT; }
#line 8233 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 15: /* sqlstmt: %empty  */
#line 797 "sql_parser.y"
                        { m->sym = (yyval.sym) = NULL; YYACCEPT; }
#line 8239 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 16: /* sqlstmt: SCOLON  */
#line 798 "sql_parser.y"
                        { m->sym = (yyval.sym) = NULL; YYACCEPT; }
#line 8245 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 17: /* sqlstmt: error SCOLON  */
#line 799 "sql_parser.y"
                        { m->sym = (yyval.sym) = NULL; YYACCEPT; }
#line 8251 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 18: /* sqlstmt: LEX_ERROR  */
#line 800 "sql_parser.y"
                        { m->sym = (yyval.sym) = NULL; YYABORT; }
#line 8257 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 26: /* create: CREATE  */
#line 823 "sql_parser.y"
            { (yyval.bval) = FALSE; }
#line 8263 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 28: /* create_or_replace: CREATE OR REPLACE  */
#line 827 "sql_parser.y"
                          { (yyval.bval) = TRUE; }
#line 8269 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 29: /* if_exists: %empty  */
#line 831 "sql_parser.y"
                      { (yyval.bval) = FALSE; }
#line 8275 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 30: /* if_exists: IF EXISTS  */
#line 832 "sql_parser.y"
                      { (yyval.bval) = TRUE; }
#line 8281 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 31: /* if_not_exists: %empty  */
#line 836 "sql_parser.y"
                      { (yyval.bval) = FALSE; }
#line 8287 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 32: /* if_not_exists: IF NOT_EXISTS  */
#line 837 "sql_parser.y"
                      { (yyval.bval) = TRUE; }
#line 8293 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 44: /* sql: ANALYZE qname opt_column_list opt_sample opt_minmax  */
#line 860 "sql_parser.y"
                { dlist *l = L();
		append_list(l, (yyvsp[-3].l));
		append_list(l, (yyvsp[-2].l));
		append_symbol(l, (yyvsp[-1].sym));
		append_int(l, (yyvsp[0].i_val));
		(yyval.sym) = _symbol_create_list( SQL_ANALYZE, l); }
#line 8304 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 47: /* opt_minmax: %empty  */
#line 871 "sql_parser.y"
                        { (yyval.i_val) = 0; }
#line 8310 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 48: /* opt_minmax: MINMAX  */
#line 872 "sql_parser.y"
                        { (yyval.i_val) = 1; }
#line 8316 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 49: /* declare_statement: declare variable_list  */
#line 876 "sql_parser.y"
                              { (yyval.sym) = _symbol_create_list( SQL_DECLARE, (yyvsp[0].l)); }
#line 8322 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 50: /* declare_statement: declare table_def  */
#line 877 "sql_parser.y"
                          { (yyval.sym) = (yyvsp[0].sym); if ((yyval.sym)) (yyval.sym)->token = SQL_DECLARE_TABLE; }
#line 8328 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 51: /* variable_ref_commalist: variable_ref  */
#line 881 "sql_parser.y"
                                            { (yyval.l) = append_list(L(), (yyvsp[0].l)); }
#line 8334 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 52: /* variable_ref_commalist: variable_ref_commalist ',' variable_ref  */
#line 882 "sql_parser.y"
                                            { (yyval.l) = append_list( (yyvsp[-2].l), (yyvsp[0].l) ); }
#line 8340 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 53: /* variable_list: variable_ref_commalist data_type  */
#line 887 "sql_parser.y"
                { dlist *l = L();
		append_list(l, (yyvsp[-1].l) );
		append_type(l, &(yyvsp[0].type) );
		(yyval.l) = append_symbol(L(), _symbol_create_list( SQL_DECLARE, l)); }
#line 8349 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 54: /* variable_list: variable_list ',' variable_ref_commalist data_type  */
#line 892 "sql_parser.y"
                { dlist *l = L();
		append_list(l, (yyvsp[-1].l) );
		append_type(l, &(yyvsp[0].type) );
		(yyval.l) = append_symbol((yyvsp[-3].l), _symbol_create_list( SQL_DECLARE, l)); }
#line 8358 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 57: /* set_statement: set variable_ref '=' search_condition  */
#line 905 "sql_parser.y"
                { dlist *l = L();
		append_list(l, (yyvsp[-2].l) );
		append_symbol(l, (yyvsp[0].sym) );
		(yyval.sym) = _symbol_create_list( SQL_SET, l); }
#line 8367 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 58: /* set_statement: set variable_ref_commalist_parens '=' subquery  */
#line 910 "sql_parser.y"
                { dlist *l = L();
	  	append_list(l, (yyvsp[-2].l));
	  	append_symbol(l, (yyvsp[0].sym));
	  	(yyval.sym) = _symbol_create_list( SQL_SET, l ); }
#line 8376 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 59: /* set_statement: set sqlSESSION AUTHORIZATION opt_equal ident  */
#line 915 "sql_parser.y"
                { dlist *l = L();
		  sql_subtype t;
		sql_find_subtype(&t, "char", UTF8_strlen((yyvsp[0].sval)), 0 );
		append_list(l, append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "current_user")));
		append_symbol(l, _newAtomNode( _atom_string(&t, (yyvsp[0].sval))) );
		(yyval.sym) = _symbol_create_list( SQL_SET, l); }
#line 8387 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 60: /* set_statement: set session_schema opt_equal ident  */
#line 922 "sql_parser.y"
                { dlist *l = L();
		  sql_subtype t;
		sql_find_subtype(&t, "char", UTF8_strlen((yyvsp[0].sval)), 0 );
		append_list(l, append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "current_schema")));
		append_symbol(l, _newAtomNode( _atom_string(&t, (yyvsp[0].sval))) );
		(yyval.sym) = _symbol_create_list( SQL_SET, l); }
#line 8398 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 61: /* set_statement: set session_user opt_equal ident  */
#line 929 "sql_parser.y"
                { dlist *l = L();
		  sql_subtype t;
		sql_find_subtype(&t, "char", UTF8_strlen((yyvsp[0].sval)), 0 );
		append_list(l, append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "current_user")));
		append_symbol(l, _newAtomNode( _atom_string(&t, (yyvsp[0].sval))) );
		(yyval.sym) = _symbol_create_list( SQL_SET, l); }
#line 8409 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 62: /* set_statement: set session_role opt_equal ident  */
#line 936 "sql_parser.y"
                { dlist *l = L();
		  sql_subtype t;
		sql_find_subtype(&t, "char", UTF8_strlen((yyvsp[0].sval)), 0);
		append_list(l, append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "current_role")));
		append_symbol(l, _newAtomNode( _atom_string(&t, (yyvsp[0].sval))) );
		(yyval.sym) = _symbol_create_list( SQL_SET, l); }
#line 8420 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 63: /* set_statement: set session_timezone opt_equal LOCAL  */
#line 943 "sql_parser.y"
                { dlist *l = L();
		  sql_subtype t;
		sql_find_subtype(&t, "sec_interval", inttype2digits(ihour, isec), 0);
		append_list(l, append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "current_timezone")));
		append_symbol(l, _newAtomNode(atom_int(SA, &t, 0)));
		(yyval.sym) = _symbol_create_list( SQL_SET, l); }
#line 8431 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 64: /* set_statement: set session_timezone opt_equal literal  */
#line 950 "sql_parser.y"
                { dlist *l = L();
		append_list(l, append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "current_timezone")));
		append_symbol(l, (yyvsp[0].sym) );
		(yyval.sym) = _symbol_create_list( SQL_SET, l); }
#line 8440 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 65: /* schema: create SCHEMA if_not_exists schema_name_clause opt_schema_default_char_set opt_path_specification opt_schema_element_list  */
#line 959 "sql_parser.y"
                { dlist *l = L();
		append_list(l, (yyvsp[-3].l));
		append_symbol(l, (yyvsp[-2].sym));
		append_symbol(l, (yyvsp[-1].sym));
		append_list(l, (yyvsp[0].l));
		append_int(l, (yyvsp[-4].bval));
		(yyval.sym) = _symbol_create_list( SQL_CREATE_SCHEMA, l); }
#line 8452 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 66: /* schema: drop SCHEMA if_exists qname drop_action  */
#line 967 "sql_parser.y"
                { dlist *l = L();
		append_list(l, (yyvsp[-1].l));
		append_int(l, (yyvsp[0].i_val));
		append_int(l, (yyvsp[-2].bval));
		(yyval.sym) = _symbol_create_list( SQL_DROP_SCHEMA, l); }
#line 8462 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 67: /* schema_name_clause: ident  */
#line 976 "sql_parser.y"
        { (yyval.l) = L();
	  append_string((yyval.l), (yyvsp[0].sval) );
	  append_string((yyval.l), NULL ); }
#line 8470 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 68: /* schema_name_clause: AUTHORIZATION authorization_identifier  */
#line 980 "sql_parser.y"
        { (yyval.l) = L();
	  append_string((yyval.l), NULL );
	  append_string((yyval.l), (yyvsp[0].sval) ); }
#line 8478 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 69: /* schema_name_clause: ident AUTHORIZATION authorization_identifier  */
#line 984 "sql_parser.y"
        { (yyval.l) = L();
	  append_string((yyval.l), (yyvsp[-2].sval) );
	  append_string((yyval.l), (yyvsp[0].sval) ); }
#line 8486 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 71: /* opt_schema_default_char_set: %empty  */
#line 993 "sql_parser.y"
                                { (yyval.sym) = NULL; }
#line 8492 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 72: /* opt_schema_default_char_set: DEFAULT CHARACTER SET ident  */
#line 994 "sql_parser.y"
                                { (yyval.sym) = _symbol_create( SQL_CHARSET, (yyvsp[0].sval) ); }
#line 8498 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 73: /* opt_schema_element_list: %empty  */
#line 998 "sql_parser.y"
                                { (yyval.l) = L(); }
#line 8504 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 75: /* schema_element_list: schema_element  */
#line 1003 "sql_parser.y"
                        { (yyval.l) = append_symbol(L(), (yyvsp[0].sym)); }
#line 8510 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 76: /* schema_element_list: schema_element_list schema_element  */
#line 1005 "sql_parser.y"
                        { (yyval.l) = append_symbol( (yyvsp[-1].l), (yyvsp[0].sym) ); }
#line 8516 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 82: /* opt_grantor: %empty  */
#line 1011 "sql_parser.y"
                         { (yyval.i_val) = cur_user; }
#line 8522 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 83: /* opt_grantor: WITH ADMIN grantor  */
#line 1012 "sql_parser.y"
                         { (yyval.i_val) = (yyvsp[0].i_val); }
#line 8528 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 84: /* grantor: CURRENT_USER  */
#line 1016 "sql_parser.y"
                        { (yyval.i_val) = cur_user; }
#line 8534 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 85: /* grantor: CURRENT_ROLE  */
#line 1017 "sql_parser.y"
                        { (yyval.i_val) = cur_role; }
#line 8540 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 86: /* grant: GRANT privileges TO grantee_commalist opt_with_grant opt_from_grantor  */
#line 1022 "sql_parser.y"
        { dlist *l = L();
	  append_list(l, (yyvsp[-4].l));
	  append_list(l, (yyvsp[-2].l));
	  append_int(l, (yyvsp[-1].bval));
	  append_int(l, (yyvsp[0].i_val));
	(yyval.sym) = _symbol_create_list( SQL_GRANT, l);
	}
#line 8552 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 87: /* grant: GRANT authid_list TO grantee_commalist opt_with_admin opt_from_grantor  */
#line 1032 "sql_parser.y"
        { dlist *l = L();
	  append_list(l, (yyvsp[-4].l));
	  append_list(l, (yyvsp[-2].l));
	  append_int(l, (yyvsp[-1].bval));
	  append_int(l, (yyvsp[0].i_val));
	(yyval.sym) = _symbol_create_list( SQL_GRANT_ROLES, l); }
#line 8563 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 88: /* authid_list: authid  */
#line 1041 "sql_parser.y"
                        { (yyval.l) = append_string(L(), (yyvsp[0].sval)); }
#line 8569 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 89: /* authid_list: authid_list ',' authid  */
#line 1043 "sql_parser.y"
                        { (yyval.l) = append_string((yyvsp[-2].l), (yyvsp[0].sval)); }
#line 8575 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 90: /* opt_with_grant: %empty  */
#line 1047 "sql_parser.y"
                                        { (yyval.bval) = 0; }
#line 8581 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 91: /* opt_with_grant: WITH GRANT OPTION  */
#line 1048 "sql_parser.y"
                                        { (yyval.bval) = 1; }
#line 8587 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 92: /* opt_with_admin: %empty  */
#line 1052 "sql_parser.y"
                                    { (yyval.bval) = 0; }
#line 8593 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 93: /* opt_with_admin: WITH ADMIN OPTION  */
#line 1053 "sql_parser.y"
                                { (yyval.bval) = 1; }
#line 8599 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 94: /* opt_from_grantor: %empty  */
#line 1058 "sql_parser.y"
                        { (yyval.i_val) = cur_user; }
#line 8605 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 95: /* opt_from_grantor: FROM grantor  */
#line 1059 "sql_parser.y"
                        { (yyval.i_val) = (yyvsp[0].i_val); }
#line 8611 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 96: /* revoke: REVOKE opt_grant_for privileges FROM grantee_commalist opt_from_grantor  */
#line 1064 "sql_parser.y"
        { dlist *l = L();
	  append_list(l, (yyvsp[-3].l));
	  append_list(l, (yyvsp[-1].l));
	  append_int(l, (yyvsp[-4].bval)); /* GRANT OPTION FOR */
	  append_int(l, 0);
	  append_int(l, (yyvsp[0].i_val));
	(yyval.sym) = _symbol_create_list( SQL_REVOKE, l); }
#line 8623 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 97: /* revoke: REVOKE opt_admin_for authid_list FROM grantee_commalist opt_from_grantor  */
#line 1072 "sql_parser.y"
        { dlist *l = L();
	  append_list(l, (yyvsp[-3].l));
	  append_list(l, (yyvsp[-1].l));
	  append_int(l, (yyvsp[-4].bval));
	  append_int(l, (yyvsp[0].i_val));
	(yyval.sym) = _symbol_create_list( SQL_REVOKE_ROLES, l); }
#line 8634 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 98: /* opt_grant_for: %empty  */
#line 1081 "sql_parser.y"
                                        { (yyval.bval) = 0; }
#line 8640 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 99: /* opt_grant_for: GRANT OPTION FOR  */
#line 1082 "sql_parser.y"
                                        { (yyval.bval) = 1; }
#line 8646 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 100: /* opt_admin_for: %empty  */
#line 1086 "sql_parser.y"
                                        { (yyval.bval) = 0; }
#line 8652 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 101: /* opt_admin_for: ADMIN OPTION FOR  */
#line 1087 "sql_parser.y"
                                        { (yyval.bval) = 1; }
#line 8658 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 102: /* privileges: global_privileges  */
#line 1092 "sql_parser.y"
        { (yyval.l) = L();
	  append_list((yyval.l), (yyvsp[0].l));
	  append_symbol((yyval.l), _symbol_create(SQL_GRANT, NULL)); }
#line 8666 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 103: /* privileges: object_privileges ON object_name  */
#line 1096 "sql_parser.y"
        { (yyval.l) = L();
	  append_list((yyval.l), (yyvsp[-2].l));
	  append_symbol((yyval.l), (yyvsp[0].sym)); }
#line 8674 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 104: /* global_privileges: global_privilege  */
#line 1102 "sql_parser.y"
                        { (yyval.l) = append_int(L(), (yyvsp[0].i_val)); }
#line 8680 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 105: /* global_privileges: global_privilege ',' global_privilege  */
#line 1104 "sql_parser.y"
                        { (yyval.l) = append_int(append_int(L(), (yyvsp[-2].i_val)), (yyvsp[0].i_val)); }
#line 8686 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 106: /* global_privilege: COPY FROM  */
#line 1108 "sql_parser.y"
                        { (yyval.i_val) = PRIV_COPYFROMFILE; }
#line 8692 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 107: /* global_privilege: COPY INTO  */
#line 1109 "sql_parser.y"
                        { (yyval.i_val) = PRIV_COPYINTOFILE; }
#line 8698 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 108: /* object_name: TABLE qname  */
#line 1113 "sql_parser.y"
                                { (yyval.sym) = _symbol_create_list(SQL_TABLE, (yyvsp[0].l)); }
#line 8704 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 109: /* object_name: qname  */
#line 1114 "sql_parser.y"
                                { (yyval.sym) = _symbol_create_list(SQL_NAME, (yyvsp[0].l)); }
#line 8710 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 110: /* object_name: routine_designator  */
#line 1115 "sql_parser.y"
                                { (yyval.sym) = _symbol_create_list(SQL_FUNC, (yyvsp[0].l)); }
#line 8716 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 111: /* object_privileges: ALL PRIVILEGES  */
#line 1126 "sql_parser.y"
                                        { (yyval.l) = NULL; }
#line 8722 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 112: /* object_privileges: ALL  */
#line 1127 "sql_parser.y"
                                        { (yyval.l) = NULL; }
#line 8728 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 114: /* operation_commalist: operation  */
#line 1132 "sql_parser.y"
                        { (yyval.l) = append_symbol(L(), (yyvsp[0].sym)); }
#line 8734 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 115: /* operation_commalist: operation_commalist ',' operation  */
#line 1134 "sql_parser.y"
                        { (yyval.l) = append_symbol((yyvsp[-2].l), (yyvsp[0].sym)); }
#line 8740 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 116: /* operation: INSERT  */
#line 1138 "sql_parser.y"
                                    { (yyval.sym) = _symbol_create(SQL_INSERT,NULL); }
#line 8746 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 117: /* operation: sqlDELETE  */
#line 1139 "sql_parser.y"
                                    { (yyval.sym) = _symbol_create(SQL_DELETE,NULL); }
#line 8752 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 118: /* operation: TRUNCATE  */
#line 1140 "sql_parser.y"
                                    { (yyval.sym) = _symbol_create(SQL_TRUNCATE,NULL); }
#line 8758 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 119: /* operation: UPDATE opt_column_list  */
#line 1141 "sql_parser.y"
                                    { (yyval.sym) = _symbol_create_list(SQL_UPDATE,(yyvsp[0].l)); }
#line 8764 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 120: /* operation: SELECT opt_column_list  */
#line 1142 "sql_parser.y"
                                    { (yyval.sym) = _symbol_create_list(SQL_SELECT,(yyvsp[0].l)); }
#line 8770 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 121: /* operation: REFERENCES opt_column_list  */
#line 1143 "sql_parser.y"
                                    { (yyval.sym) = _symbol_create_list(SQL_SELECT,(yyvsp[0].l)); }
#line 8776 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 122: /* operation: execute  */
#line 1144 "sql_parser.y"
                                    { (yyval.sym) = _symbol_create(SQL_EXECUTE,NULL); }
#line 8782 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 123: /* grantee_commalist: grantee  */
#line 1148 "sql_parser.y"
                                { (yyval.l) = append_string(L(), (yyvsp[0].sval)); }
#line 8788 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 124: /* grantee_commalist: grantee_commalist ',' grantee  */
#line 1150 "sql_parser.y"
                                { (yyval.l) = append_string((yyvsp[-2].l), (yyvsp[0].sval)); }
#line 8794 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 125: /* grantee: PUBLIC  */
#line 1154 "sql_parser.y"
                                { (yyval.sval) = NULL; }
#line 8800 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 126: /* grantee: authid  */
#line 1155 "sql_parser.y"
                                { (yyval.sval) = (yyvsp[0].sval); }
#line 8806 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 127: /* alter_statement: ALTER TABLE if_exists qname ADD opt_column add_table_element  */
#line 1162 "sql_parser.y"
        { dlist *l = L();
	  append_list(l, (yyvsp[-3].l));
	  append_symbol(l, (yyvsp[0].sym));
	  append_int(l, (yyvsp[-4].bval));
	  (yyval.sym) = _symbol_create_list( SQL_ALTER_TABLE, l ); }
#line 8816 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 128: /* alter_statement: ALTER TABLE if_exists qname ADD TABLE qname opt_as_partition  */
#line 1168 "sql_parser.y"
        { dlist *l = L(), *part;
	  append_list(l, (yyvsp[-4].l));
	  append_symbol(l, _symbol_create_list( SQL_TABLE, append_list(L(),(yyvsp[-1].l))));
	  append_int(l, (yyvsp[-5].bval));
	  if((yyvsp[0].sym)) {
	      part = (yyvsp[0].sym)->data.lval;
	      append_int(part, FALSE);
	  }
	  append_symbol(l, (yyvsp[0].sym));
	  (yyval.sym) = _symbol_create_list( SQL_ALTER_TABLE, l ); }
#line 8831 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 129: /* alter_statement: ALTER TABLE if_exists qname ALTER alter_table_element  */
#line 1179 "sql_parser.y"
        { dlist *l = L();
	  append_list(l, (yyvsp[-2].l));
	  append_symbol(l, (yyvsp[0].sym));
	  append_int(l, (yyvsp[-3].bval));
	  (yyval.sym) = _symbol_create_list( SQL_ALTER_TABLE, l ); }
#line 8841 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 130: /* alter_statement: ALTER TABLE if_exists qname DROP drop_table_element  */
#line 1185 "sql_parser.y"
        { dlist *l = L();
	  append_list(l, (yyvsp[-2].l));
	  append_symbol(l, (yyvsp[0].sym));
	  append_int(l, (yyvsp[-3].bval));
	  (yyval.sym) = _symbol_create_list( SQL_ALTER_TABLE, l ); }
#line 8851 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 131: /* alter_statement: ALTER TABLE if_exists qname SET READ ONLY  */
#line 1191 "sql_parser.y"
        { dlist *l = L();
	  append_list(l, (yyvsp[-3].l));
	  append_symbol(l, _symbol_create_int(SQL_ALTER_TABLE, tr_readonly));
	  append_int(l, (yyvsp[-4].bval));
	  (yyval.sym) = _symbol_create_list( SQL_ALTER_TABLE, l ); }
#line 8861 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 132: /* alter_statement: ALTER TABLE if_exists qname SET INSERT ONLY  */
#line 1197 "sql_parser.y"
        { dlist *l = L();
	  append_list(l, (yyvsp[-3].l));
	  append_symbol(l, _symbol_create_int(SQL_ALTER_TABLE, tr_append));
	  append_int(l, (yyvsp[-4].bval));
	  (yyval.sym) = _symbol_create_list( SQL_ALTER_TABLE, l ); }
#line 8871 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 133: /* alter_statement: ALTER TABLE if_exists qname SET READ WRITE  */
#line 1203 "sql_parser.y"
        { dlist *l = L();
	  append_list(l, (yyvsp[-3].l));
	  append_symbol(l, _symbol_create_int(SQL_ALTER_TABLE, tr_writable));
	  append_int(l, (yyvsp[-4].bval));
	  (yyval.sym) = _symbol_create_list( SQL_ALTER_TABLE, l ); }
#line 8881 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 134: /* alter_statement: ALTER TABLE if_exists qname SET TABLE qname opt_as_partition  */
#line 1209 "sql_parser.y"
        { dlist *l = L(), *part;
	  append_list(l, (yyvsp[-4].l));
	  append_symbol(l, _symbol_create_list( SQL_TABLE, append_list(L(),(yyvsp[-1].l))));
	  append_int(l, (yyvsp[-5].bval));
	  if((yyvsp[0].sym)) {
	      part = (yyvsp[0].sym)->data.lval;
	      append_int(part, TRUE);
	  }
	  append_symbol(l, (yyvsp[0].sym));
	  (yyval.sym) = _symbol_create_list( SQL_ALTER_TABLE, l ); }
#line 8896 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 135: /* alter_statement: ALTER TABLE if_exists qname RENAME TO ident  */
#line 1220 "sql_parser.y"
        { dlist *l = L();
	  append_list(l, (yyvsp[-3].l));
	  append_string(l, (yyvsp[0].sval));
	  append_int(l, (yyvsp[-4].bval));
	  (yyval.sym) = _symbol_create_list( SQL_RENAME_TABLE, l ); }
#line 8906 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 136: /* alter_statement: ALTER TABLE if_exists qname RENAME opt_column ident TO ident  */
#line 1226 "sql_parser.y"
        { dlist *l = L();
	  append_list(l, (yyvsp[-5].l));
	  append_string(l, (yyvsp[-2].sval));
	  append_string(l, (yyvsp[0].sval));
	  append_int(l, (yyvsp[-6].bval));
	  (yyval.sym) = _symbol_create_list( SQL_RENAME_COLUMN, l); }
#line 8917 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 137: /* alter_statement: ALTER TABLE if_exists qname SET SCHEMA ident  */
#line 1233 "sql_parser.y"
        { dlist *l = L();
	  append_list(l, (yyvsp[-3].l));
	  append_string(l, (yyvsp[0].sval));
	  append_int(l, (yyvsp[-4].bval));
	  (yyval.sym) = _symbol_create_list( SQL_SET_TABLE_SCHEMA, l ); }
#line 8927 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 138: /* alter_statement: ALTER USER ident opt_with_encrypted_password user_schema opt_schema_path opt_default_role  */
#line 1239 "sql_parser.y"
        { dlist *l = L(), *p = L();
	  if (!(yyvsp[-3].l) && !(yyvsp[-2].sval) && !(yyvsp[-1].sval) && !(yyvsp[0].sval)) {
		yyerror(m, "ALTER USER: At least one property should be updated");
		YYABORT;
	  }
	  append_string(l, (yyvsp[-4].sval));
	  append_string(p, (yyvsp[-3].l) ? (yyvsp[-3].l)->h->data.sval : NULL);
	  append_string(p, (yyvsp[-2].sval));
	  append_string(p, (yyvsp[-1].sval));
	  append_int(p, (yyvsp[-3].l) ? (yyvsp[-3].l)->h->next->data.i_val : 0);
	  append_string(p, NULL);
	  append_list(l, p);
	  append_string(l, (yyvsp[0].sval));
	  (yyval.sym) = _symbol_create_list( SQL_ALTER_USER, l ); }
#line 8946 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 139: /* alter_statement: ALTER USER ident RENAME TO ident  */
#line 1254 "sql_parser.y"
        { dlist *l = L();
	  append_string(l, (yyvsp[-3].sval));
	  append_string(l, (yyvsp[0].sval));
	  (yyval.sym) = _symbol_create_list( SQL_RENAME_USER, l ); }
#line 8955 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 140: /* alter_statement: ALTER USER SET opt_encrypted PASSWORD string USING OLD PASSWORD string  */
#line 1259 "sql_parser.y"
        { dlist *l = L();
	  dlist *p = L();
	  append_string(l, NULL);
	  append_string(p, (yyvsp[-4].sval));
	  append_string(p, NULL);
	  append_string(p, NULL);
	  append_int(p, (yyvsp[-6].i_val));
	  append_string(p, (yyvsp[0].sval));
	  append_list(l, p);
	  append_string(l, NULL);
	  (yyval.sym) = _symbol_create_list( SQL_ALTER_USER, l ); }
#line 8971 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 141: /* alter_statement: ALTER SCHEMA if_exists ident RENAME TO ident  */
#line 1271 "sql_parser.y"
        { dlist *l = L();
	  append_string(l, (yyvsp[-3].sval));
	  append_string(l, (yyvsp[0].sval));
	  append_int(l, (yyvsp[-4].bval));
	  (yyval.sym) = _symbol_create_list( SQL_RENAME_SCHEMA, l ); }
#line 8981 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 142: /* opt_with_encrypted_password: WITH opt_encrypted PASSWORD string  */
#line 1279 "sql_parser.y"
                                                { (yyval.l) = append_int(append_string(L(), (yyvsp[0].sval)), (yyvsp[-2].i_val)); }
#line 8987 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 143: /* opt_with_encrypted_password: %empty  */
#line 1280 "sql_parser.y"
                                                                { (yyval.l) = NULL; }
#line 8993 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 144: /* user_schema: SET SCHEMA ident  */
#line 1284 "sql_parser.y"
                                { (yyval.sval) = (yyvsp[0].sval); }
#line 8999 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 145: /* user_schema: %empty  */
#line 1285 "sql_parser.y"
                                { (yyval.sval) = NULL; }
#line 9005 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 146: /* opt_schema_path: SCHEMA PATH string  */
#line 1289 "sql_parser.y"
                                { (yyval.sval) = (yyvsp[0].sval); }
#line 9011 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 147: /* opt_schema_path: %empty  */
#line 1290 "sql_parser.y"
                                { (yyval.sval) = NULL; }
#line 9017 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 148: /* alter_table_element: opt_column ident SET DEFAULT default_value  */
#line 1296 "sql_parser.y"
        { dlist *l = L();
	  append_string(l, (yyvsp[-3].sval));
	  append_symbol(l, (yyvsp[0].sym));
	  (yyval.sym) = _symbol_create_list( SQL_DEFAULT, l); }
#line 9026 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 149: /* alter_table_element: opt_column ident SET sqlNULL  */
#line 1301 "sql_parser.y"
        { dlist *l = L();
	  append_string(l, (yyvsp[-2].sval));
	  (yyval.sym) = _symbol_create_list( SQL_NULL, l); }
#line 9034 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 150: /* alter_table_element: opt_column ident SET NOT sqlNULL  */
#line 1305 "sql_parser.y"
        { dlist *l = L();
	  append_string(l, (yyvsp[-3].sval));
	  (yyval.sym) = _symbol_create_list( SQL_NOT_NULL, l); }
#line 9042 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 151: /* alter_table_element: opt_column ident DROP DEFAULT  */
#line 1309 "sql_parser.y"
        { (yyval.sym) = _symbol_create( SQL_DROP_DEFAULT, (yyvsp[-2].sval)); }
#line 9048 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 152: /* alter_table_element: opt_column ident SET STORAGE string  */
#line 1311 "sql_parser.y"
        { dlist *l = L();
	  append_string(l, (yyvsp[-3].sval));
	  if (!strlen((yyvsp[0].sval)))
	  	append_string(l, NULL);
	  else
	  	append_string(l, (yyvsp[0].sval));
	  (yyval.sym) = _symbol_create_list( SQL_STORAGE, l); }
#line 9060 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 153: /* alter_table_element: opt_column ident SET STORAGE sqlNULL  */
#line 1319 "sql_parser.y"
        { dlist *l = L();
	  append_string(l, (yyvsp[-3].sval));
	  append_string(l, NULL);
	  (yyval.sym) = _symbol_create_list( SQL_STORAGE, l); }
#line 9069 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 154: /* drop_table_element: opt_column ident drop_action  */
#line 1327 "sql_parser.y"
        { dlist *l = L();
	  append_string(l, (yyvsp[-1].sval) );
	  append_int(l, (yyvsp[0].i_val) );
	  (yyval.sym) = _symbol_create_list( SQL_DROP_COLUMN, l ); }
#line 9078 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 155: /* drop_table_element: CONSTRAINT ident drop_action  */
#line 1332 "sql_parser.y"
        { dlist *l = L();
	  append_string(l, (yyvsp[-1].sval) );
	  append_int(l, (yyvsp[0].i_val) );
	  (yyval.sym) = _symbol_create_list( SQL_DROP_CONSTRAINT, l ); }
#line 9087 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 156: /* drop_table_element: TABLE qname drop_action  */
#line 1337 "sql_parser.y"
        { dlist *l = L();
	  append_list(l, (yyvsp[-1].l) );
	  append_int(l, (yyvsp[0].i_val) );
	  append_int(l, FALSE); /* no if exists check */
	  (yyval.sym) = _symbol_create_list( SQL_DROP_TABLE, l ); }
#line 9097 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 157: /* opt_column: COLUMN  */
#line 1345 "sql_parser.y"
                 { (yyval.i_val) = 0; }
#line 9103 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 158: /* opt_column: %empty  */
#line 1346 "sql_parser.y"
                 { (yyval.i_val) = 0; }
#line 9109 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 159: /* create_statement: create role_def  */
#line 1350 "sql_parser.y"
                        { (yyval.sym) = (yyvsp[0].sym); }
#line 9115 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 160: /* create_statement: create table_def  */
#line 1351 "sql_parser.y"
                        { (yyval.sym) = (yyvsp[0].sym); }
#line 9121 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 161: /* create_statement: view_def  */
#line 1352 "sql_parser.y"
                { (yyval.sym) = (yyvsp[0].sym); }
#line 9127 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 167: /* seq_def: create SEQUENCE qname opt_seq_params  */
#line 1374 "sql_parser.y"
        {
		dlist *l = L();
		append_list(l, (yyvsp[-1].l));
		append_list(l, (yyvsp[0].l));
		append_int(l, 0); /* to be dropped */
		(yyval.sym) = _symbol_create_list(SQL_CREATE_SEQ, l);
	}
#line 9139 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 168: /* seq_def: drop SEQUENCE qname  */
#line 1385 "sql_parser.y"
        {
		dlist *l = L();
		append_list(l, (yyvsp[0].l));
		(yyval.sym) = _symbol_create_list(SQL_DROP_SEQ, l);
	}
#line 9149 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 169: /* seq_def: ALTER SEQUENCE qname opt_alt_seq_params  */
#line 1402 "sql_parser.y"
        {
		dlist *l = L();
		append_list(l, (yyvsp[-1].l));
		append_list(l, (yyvsp[0].l)); 
		(yyval.sym) = _symbol_create_list(SQL_ALTER_SEQ, l);
	}
#line 9160 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 170: /* opt_seq_params: params_list  */
#line 1411 "sql_parser.y"
                     { (yyval.l) = (yyvsp[0].l); }
#line 9166 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 171: /* opt_seq_params: %empty  */
#line 1412 "sql_parser.y"
                 { (yyval.l) = NULL; }
#line 9172 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 172: /* params_list: opt_seq_param  */
#line 1415 "sql_parser.y"
                                          { (yyval.l) = append_symbol(L(), (yyvsp[0].sym)); }
#line 9178 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 173: /* params_list: params_list opt_seq_param  */
#line 1416 "sql_parser.y"
                                  { (yyval.l) = append_symbol((yyvsp[-1].l), (yyvsp[0].sym)); }
#line 9184 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 174: /* opt_alt_seq_params: opt_alt_seq_param  */
#line 1420 "sql_parser.y"
                                                { (yyval.l) = append_symbol(L(), (yyvsp[0].sym)); }
#line 9190 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 175: /* opt_alt_seq_params: opt_alt_seq_params opt_alt_seq_param  */
#line 1421 "sql_parser.y"
                                                { (yyval.l) = append_symbol((yyvsp[-1].l), (yyvsp[0].sym)); }
#line 9196 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 176: /* opt_seq_param: AS data_type  */
#line 1425 "sql_parser.y"
                                        { (yyval.sym) = _symbol_create_list(SQL_TYPE, append_type(L(),&(yyvsp[0].type))); }
#line 9202 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 177: /* opt_seq_param: START WITH opt_sign lngval  */
#line 1426 "sql_parser.y"
                                        { (yyval.sym) = _symbol_create_lng(SQL_START, is_lng_nil((yyvsp[0].l_val)) ? (yyvsp[0].l_val) : (yyvsp[-1].i_val) * (yyvsp[0].l_val)); }
#line 9208 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 178: /* opt_seq_param: opt_seq_common_param  */
#line 1427 "sql_parser.y"
                                        { (yyval.sym) = (yyvsp[0].sym); }
#line 9214 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 179: /* opt_alt_seq_param: AS data_type  */
#line 1431 "sql_parser.y"
                                        { (yyval.sym) = _symbol_create_list(SQL_TYPE, append_type(L(),&(yyvsp[0].type))); }
#line 9220 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 180: /* opt_alt_seq_param: RESTART  */
#line 1432 "sql_parser.y"
                                        { (yyval.sym) = _symbol_create_list(SQL_START, append_int(L(),0)); /* plain restart now */ }
#line 9226 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 181: /* opt_alt_seq_param: RESTART WITH opt_sign lngval  */
#line 1433 "sql_parser.y"
                                        { (yyval.sym) = _symbol_create_list(SQL_START, append_lng(append_int(L(),2), is_lng_nil((yyvsp[0].l_val)) ? (yyvsp[0].l_val) : (yyvsp[-1].i_val) * (yyvsp[0].l_val)));  }
#line 9232 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 182: /* opt_alt_seq_param: RESTART WITH subquery  */
#line 1434 "sql_parser.y"
                                        { (yyval.sym) = _symbol_create_list(SQL_START, append_symbol(append_int(L(),1), (yyvsp[0].sym)));  }
#line 9238 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 183: /* opt_alt_seq_param: opt_seq_common_param  */
#line 1435 "sql_parser.y"
                                        { (yyval.sym) = (yyvsp[0].sym); }
#line 9244 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 184: /* opt_seq_common_param: INCREMENT BY opt_sign lngval  */
#line 1439 "sql_parser.y"
                                        { (yyval.sym) = _symbol_create_lng(SQL_INC, is_lng_nil((yyvsp[0].l_val)) ? (yyvsp[0].l_val) : (yyvsp[-1].i_val) * (yyvsp[0].l_val)); }
#line 9250 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 185: /* opt_seq_common_param: MINVALUE opt_sign lngval  */
#line 1440 "sql_parser.y"
                                        { (yyval.sym) = _symbol_create_lng(SQL_MINVALUE, is_lng_nil((yyvsp[0].l_val)) ? (yyvsp[0].l_val) : (yyvsp[-1].i_val) * (yyvsp[0].l_val)); }
#line 9256 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 186: /* opt_seq_common_param: NO MINVALUE  */
#line 1441 "sql_parser.y"
                                        { (yyval.sym) = _symbol_create_int(SQL_MINVALUE, int_nil); /* Hack: SQL_MINVALUE + int_nil signals NO MINVALUE */ }
#line 9262 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 187: /* opt_seq_common_param: MAXVALUE opt_sign lngval  */
#line 1442 "sql_parser.y"
                                        { (yyval.sym) = _symbol_create_lng(SQL_MAXVALUE, is_lng_nil((yyvsp[0].l_val)) ? (yyvsp[0].l_val) : (yyvsp[-1].i_val) * (yyvsp[0].l_val)); }
#line 9268 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 188: /* opt_seq_common_param: NO MAXVALUE  */
#line 1443 "sql_parser.y"
                                        { (yyval.sym) = _symbol_create_int(SQL_MAXVALUE, int_nil); /* Hack: SQL_MAXVALUE + int_nil signals NO MAXVALUE */ }
#line 9274 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 189: /* opt_seq_common_param: CACHE nonzerolng  */
#line 1444 "sql_parser.y"
                                        { (yyval.sym) = _symbol_create_lng(SQL_CACHE, (yyvsp[0].l_val)); }
#line 9280 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 190: /* opt_seq_common_param: CYCLE  */
#line 1445 "sql_parser.y"
                                        { (yyval.sym) = _symbol_create_int(SQL_CYCLE, 1); }
#line 9286 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 191: /* opt_seq_common_param: NO CYCLE  */
#line 1446 "sql_parser.y"
                                        { (yyval.sym) = _symbol_create_int(SQL_CYCLE, 0); }
#line 9292 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 192: /* index_def: create opt_index_type INDEX ident ON qname '(' ident_commalist ')'  */
#line 1454 "sql_parser.y"
        { dlist *l = L();
	  append_string(l, (yyvsp[-5].sval));
	  append_int(l, (yyvsp[-7].i_val));
	  append_list(l, (yyvsp[-3].l));
	  append_list(l, (yyvsp[-1].l));
	  (yyval.sym) = _symbol_create_list( SQL_CREATE_INDEX, l); }
#line 9303 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 193: /* opt_index_type: UNIQUE  */
#line 1463 "sql_parser.y"
                        { (yyval.i_val) = hash_idx; }
#line 9309 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 194: /* opt_index_type: ORDERED  */
#line 1464 "sql_parser.y"
                        { (yyval.i_val) = ordered_idx; }
#line 9315 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 195: /* opt_index_type: IMPRINTS  */
#line 1465 "sql_parser.y"
                        { (yyval.i_val) = imprints_idx; }
#line 9321 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 196: /* opt_index_type: %empty  */
#line 1466 "sql_parser.y"
                        { (yyval.i_val) = hash_idx; }
#line 9327 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 197: /* role_def: ROLE ident opt_grantor  */
#line 1487 "sql_parser.y"
        { dlist *l = L();
	  append_string(l, (yyvsp[-1].sval));
	  append_int(l, (yyvsp[0].i_val));
	  (yyval.sym) = _symbol_create_list( SQL_CREATE_ROLE, l ); }
#line 9336 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 198: /* role_def: USER ident WITH opt_encrypted PASSWORD string sqlNAME string opt_schema_details_list opt_max_memory opt_max_workers opt_optimizer opt_default_role  */
#line 1492 "sql_parser.y"
    { dlist *l = L();
	  append_string(l, (yyvsp[-11].sval));
	  append_string(l, (yyvsp[-7].sval));
	  append_string(l, (yyvsp[-5].sval));
	  append_list(l, (yyvsp[-4].l));
	  append_int(l, (yyvsp[-9].i_val));
	  append_lng(l, (yyvsp[-3].l_val));
	  append_int(l, (yyvsp[-2].i_val));
	  append_string(l, (yyvsp[-1].sval));
	  append_string(l, (yyvsp[0].sval));
	  (yyval.sym) = _symbol_create_list( SQL_CREATE_USER, l ); }
#line 9352 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 199: /* opt_max_memory: %empty  */
#line 1506 "sql_parser.y"
                        { (yyval.l_val) = 0; }
#line 9358 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 200: /* opt_max_memory: MAX_MEMORY poslng  */
#line 1507 "sql_parser.y"
                        { (yyval.l_val) = (yyvsp[0].l_val); }
#line 9364 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 201: /* opt_max_workers: %empty  */
#line 1511 "sql_parser.y"
                        { (yyval.i_val) = 0; }
#line 9370 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 202: /* opt_max_workers: MAX_WORKERS posint  */
#line 1512 "sql_parser.y"
                        { (yyval.i_val) = (yyvsp[0].i_val); }
#line 9376 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 203: /* opt_optimizer: %empty  */
#line 1516 "sql_parser.y"
                        { (yyval.sval) = NULL; }
#line 9382 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 204: /* opt_optimizer: OPTIMIZER string  */
#line 1517 "sql_parser.y"
                        { (yyval.sval) = (yyvsp[0].sval); }
#line 9388 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 205: /* opt_default_role: %empty  */
#line 1521 "sql_parser.y"
                          { (yyval.sval) = NULL; }
#line 9394 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 206: /* opt_default_role: DEFAULT ROLE ident  */
#line 1522 "sql_parser.y"
                          { (yyval.sval) = (yyvsp[0].sval); }
#line 9400 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 207: /* opt_schema_details_list: opt_schema_path  */
#line 1527 "sql_parser.y"
    { dlist *l = L();
      append_string(l, NULL);
      (yyval.l) = append_string(l, (yyvsp[0].sval));}
#line 9408 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 208: /* opt_schema_details_list: SCHEMA ident opt_schema_path  */
#line 1531 "sql_parser.y"
    { dlist *l = L();
      append_string(l, (yyvsp[-1].sval));
      (yyval.l) = append_string(l, (yyvsp[0].sval));}
#line 9416 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 209: /* opt_encrypted: %empty  */
#line 1538 "sql_parser.y"
                        { (yyval.i_val) = SQL_PW_UNENCRYPTED; }
#line 9422 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 210: /* opt_encrypted: UNENCRYPTED  */
#line 1539 "sql_parser.y"
                        { (yyval.i_val) = SQL_PW_UNENCRYPTED; }
#line 9428 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 211: /* opt_encrypted: ENCRYPTED  */
#line 1540 "sql_parser.y"
                        { (yyval.i_val) = SQL_PW_ENCRYPTED; }
#line 9434 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 212: /* table_def: TABLE if_not_exists qname table_content_source  */
#line 1545 "sql_parser.y"
        { int commit_action = CA_COMMIT;
	  dlist *l = L();

	  append_int(l, SQL_PERSIST);
	  append_list(l, (yyvsp[-1].l));
	  append_symbol(l, (yyvsp[0].sym));
	  append_int(l, commit_action);
	  append_string(l, NULL);
	  append_list(l, NULL);
	  append_int(l, (yyvsp[-2].bval));
	  append_symbol(l, NULL); /* only used for merge table */
	  (yyval.sym) = _symbol_create_list( SQL_CREATE_TABLE, l ); }
#line 9451 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 213: /* table_def: TABLE if_not_exists qname FROM sqlLOADER func_ref  */
#line 1558 "sql_parser.y"
    {
      dlist *l = L();
      append_list(l, (yyvsp[-3].l));
      append_symbol(l, (yyvsp[0].sym));
      (yyval.sym) = _symbol_create_list( SQL_CREATE_TABLE_LOADER, l);
    }
#line 9462 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 214: /* table_def: MERGE TABLE if_not_exists qname table_content_source opt_partition_by  */
#line 1565 "sql_parser.y"
        { int commit_action = CA_COMMIT, tpe = SQL_MERGE_TABLE;
	  dlist *l = L();

	  append_int(l, tpe);
	  append_list(l, (yyvsp[-2].l));
	  append_symbol(l, (yyvsp[-1].sym));
	  append_int(l, commit_action);
	  append_string(l, NULL);
	  append_list(l, NULL);
	  append_int(l, (yyvsp[-3].bval));
	  append_symbol(l, (yyvsp[0].sym));
	  (yyval.sym) = _symbol_create_list( SQL_CREATE_TABLE, l ); }
#line 9479 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 215: /* table_def: REPLICA TABLE if_not_exists qname table_content_source  */
#line 1578 "sql_parser.y"
        { int commit_action = CA_COMMIT, tpe = SQL_REPLICA_TABLE;
	  dlist *l = L();

	  append_int(l, tpe);
	  append_list(l, (yyvsp[-1].l));
	  append_symbol(l, (yyvsp[0].sym));
	  append_int(l, commit_action);
	  append_string(l, NULL);
	  append_list(l, NULL);
	  append_int(l, (yyvsp[-2].bval));
	  append_symbol(l, NULL); /* only used for merge table */
	  (yyval.sym) = _symbol_create_list( SQL_CREATE_TABLE, l ); }
#line 9496 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 216: /* table_def: REMOTE TABLE if_not_exists qname table_content_source ON string with_opt_credentials  */
#line 1594 "sql_parser.y"
        { int commit_action = CA_COMMIT, tpe = SQL_REMOTE;
	  dlist *l = L();

	  append_int(l, tpe);
	  append_list(l, (yyvsp[-4].l));
	  append_symbol(l, (yyvsp[-3].sym));
	  append_int(l, commit_action);
	  append_string(l, (yyvsp[-1].sval));
	  append_list(l, (yyvsp[0].l));
	  append_int(l, (yyvsp[-5].bval));
	  append_symbol(l, NULL); /* only used for merge table */
	  (yyval.sym) = _symbol_create_list( SQL_CREATE_TABLE, l ); }
#line 9513 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 217: /* table_def: UNLOGGED TABLE if_not_exists qname table_content_source  */
#line 1607 "sql_parser.y"
        { int commit_action = CA_COMMIT, tpe = SQL_UNLOGGED_TABLE;
	  dlist *l = L();

	  append_int(l, tpe);
	  append_list(l, (yyvsp[-1].l));
	  append_symbol(l, (yyvsp[0].sym));
	  append_int(l, commit_action);
	  append_string(l, NULL);
	  append_list(l, NULL);
	  append_int(l, (yyvsp[-2].bval));
	  append_symbol(l, NULL); /* only used for merge table */
	  (yyval.sym) = _symbol_create_list( SQL_CREATE_TABLE, l ); }
#line 9530 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 218: /* table_def: opt_temp TABLE if_not_exists qname table_content_source opt_on_commit  */
#line 1620 "sql_parser.y"
        { int commit_action = CA_COMMIT;
	  dlist *l = L();

	  append_int(l, (yyvsp[-5].i_val));
	  append_list(l, (yyvsp[-2].l));
	  append_symbol(l, (yyvsp[-1].sym));
	  if ((yyvsp[-5].i_val) != SQL_PERSIST)
		commit_action = (yyvsp[0].i_val);
	  append_int(l, commit_action);
	  append_string(l, NULL);
	  append_list(l, NULL);
	  append_int(l, (yyvsp[-3].bval));
	  append_symbol(l, NULL); /* only used for merge table */
	  (yyval.sym) = _symbol_create_list( SQL_CREATE_TABLE, l ); }
#line 9549 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 219: /* partition_type: RANGE  */
#line 1637 "sql_parser.y"
                { (yyval.i_val) = PARTITION_RANGE; }
#line 9555 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 220: /* partition_type: VALUES  */
#line 1638 "sql_parser.y"
                { (yyval.i_val) = PARTITION_LIST; }
#line 9561 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 221: /* partition_expression: search_condition  */
#line 1642 "sql_parser.y"
                        { (yyval.sym) = (yyvsp[0].sym); }
#line 9567 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 222: /* partition_on: ON '(' ident ')'  */
#line 1646 "sql_parser.y"
                                      { (yyval.sym) = _symbol_create_list( SQL_PARTITION_COLUMN, append_string(L(), (yyvsp[-1].sval)) ); }
#line 9573 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 223: /* partition_on: USING '(' partition_expression ')'  */
#line 1647 "sql_parser.y"
                                      { (yyval.sym) = _symbol_create_list( SQL_PARTITION_EXPRESSION, append_symbol(L(), (yyvsp[-1].sym)) ); }
#line 9579 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 224: /* opt_partition_by: %empty  */
#line 1651 "sql_parser.y"
                                                                                 { (yyval.sym) = NULL; }
#line 9585 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 225: /* opt_partition_by: PARTITION BY partition_type partition_on  */
#line 1653 "sql_parser.y"
   { dlist *l = L();
     int properties = (yyvsp[-1].i_val);
     append_int(l, (yyvsp[-1].i_val));
     append_symbol(l, (yyvsp[0].sym));

     assert((yyvsp[-1].i_val) == PARTITION_RANGE || (yyvsp[-1].i_val) == PARTITION_LIST);
     if((yyvsp[0].sym)->token == SQL_PARTITION_COLUMN) {
        properties |= PARTITION_COLUMN;
     } else if((yyvsp[0].sym)->token == SQL_PARTITION_EXPRESSION) {
        properties |= PARTITION_EXPRESSION;
     } else {
        assert(0);
     }
     append_int(l, properties);

     (yyval.sym) = _symbol_create_list( SQL_MERGE_PARTITION, l ); }
#line 9606 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 226: /* partition_list_value: search_condition  */
#line 1672 "sql_parser.y"
                    { (yyval.sym) = (yyvsp[0].sym); }
#line 9612 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 227: /* partition_range_from: search_condition  */
#line 1676 "sql_parser.y"
                    { (yyval.sym) = (yyvsp[0].sym); }
#line 9618 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 228: /* partition_range_from: RANGE MINVALUE  */
#line 1677 "sql_parser.y"
                     { (yyval.sym) = _symbol_create(SQL_MINVALUE, NULL ); }
#line 9624 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 229: /* partition_range_to: search_condition  */
#line 1681 "sql_parser.y"
                    { (yyval.sym) = (yyvsp[0].sym); }
#line 9630 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 230: /* partition_range_to: RANGE MAXVALUE  */
#line 1682 "sql_parser.y"
                     { (yyval.sym) = _symbol_create(SQL_MAXVALUE, NULL ); }
#line 9636 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 231: /* partition_list: partition_list_value  */
#line 1686 "sql_parser.y"
                                                                { (yyval.l) = append_symbol(L(), (yyvsp[0].sym) ); }
#line 9642 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 232: /* partition_list: partition_list ',' partition_list_value  */
#line 1687 "sql_parser.y"
                                            { (yyval.l) = append_symbol((yyvsp[-2].l), (yyvsp[0].sym) ); }
#line 9648 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 233: /* opt_with_nulls: %empty  */
#line 1691 "sql_parser.y"
                        { (yyval.bval) = FALSE; }
#line 9654 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 234: /* opt_with_nulls: WITH sqlNULL VALUES  */
#line 1692 "sql_parser.y"
                        { (yyval.bval) = TRUE; }
#line 9660 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 235: /* opt_partition_spec: sqlIN '(' partition_list ')' opt_with_nulls  */
#line 1697 "sql_parser.y"
    { dlist *l = L();
      append_list(l, (yyvsp[-2].l));
      append_int(l, (yyvsp[0].bval));
      (yyval.sym) = _symbol_create_list( SQL_PARTITION_LIST, l ); }
#line 9669 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 236: /* opt_partition_spec: FROM partition_range_from TO partition_range_to opt_with_nulls  */
#line 1702 "sql_parser.y"
    { dlist *l = L();
      append_symbol(l, (yyvsp[-3].sym));
      append_symbol(l, (yyvsp[-1].sym));
      append_int(l, (yyvsp[0].bval));
      (yyval.sym) = _symbol_create_list( SQL_PARTITION_RANGE, l ); }
#line 9679 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 237: /* opt_partition_spec: FOR sqlNULL VALUES  */
#line 1708 "sql_parser.y"
    { dlist *l = L();
      append_symbol(l, NULL);
      append_symbol(l, NULL);
      append_int(l, TRUE);
      (yyval.sym) = _symbol_create_list( SQL_MERGE_PARTITION, l ); }
#line 9689 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 238: /* opt_as_partition: %empty  */
#line 1716 "sql_parser.y"
                                                         { (yyval.sym) = NULL; }
#line 9695 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 239: /* opt_as_partition: AS PARTITION opt_partition_spec  */
#line 1717 "sql_parser.y"
                                         { (yyval.sym) = (yyvsp[0].sym); }
#line 9701 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 240: /* with_opt_credentials: %empty  */
#line 1722 "sql_parser.y"
  {
	  (yyval.l) = append_string(L(), NULL);
	  append_int((yyval.l), SQL_PW_ENCRYPTED);
	  append_string((yyval.l), NULL);
  }
#line 9711 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 241: /* with_opt_credentials: WITH USER string opt_encrypted PASSWORD string  */
#line 1728 "sql_parser.y"
  {
	  (yyval.l) = append_string(L(), (yyvsp[-3].sval));
	  append_int((yyval.l), (yyvsp[-2].i_val));
	  append_string((yyval.l), (yyvsp[0].sval));
  }
#line 9721 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 242: /* with_opt_credentials: WITH opt_encrypted PASSWORD string  */
#line 1734 "sql_parser.y"
  {
	  (yyval.l) = append_string(L(), NULL);
	  append_int((yyval.l), (yyvsp[-2].i_val));
	  append_string((yyval.l), (yyvsp[0].sval));
  }
#line 9731 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 243: /* opt_temp: TEMPORARY  */
#line 1742 "sql_parser.y"
                        { (yyval.i_val) = SQL_LOCAL_TEMP; }
#line 9737 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 244: /* opt_temp: TEMP  */
#line 1743 "sql_parser.y"
                        { (yyval.i_val) = SQL_LOCAL_TEMP; }
#line 9743 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 245: /* opt_temp: LOCAL TEMPORARY  */
#line 1744 "sql_parser.y"
                        { (yyval.i_val) = SQL_LOCAL_TEMP; }
#line 9749 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 246: /* opt_temp: LOCAL TEMP  */
#line 1745 "sql_parser.y"
                        { (yyval.i_val) = SQL_LOCAL_TEMP; }
#line 9755 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 247: /* opt_temp: GLOBAL TEMPORARY  */
#line 1746 "sql_parser.y"
                        { (yyval.i_val) = SQL_GLOBAL_TEMP; }
#line 9761 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 248: /* opt_temp: GLOBAL TEMP  */
#line 1747 "sql_parser.y"
                        { (yyval.i_val) = SQL_GLOBAL_TEMP; }
#line 9767 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 249: /* opt_on_commit: %empty  */
#line 1751 "sql_parser.y"
                                 { (yyval.i_val) = CA_COMMIT; }
#line 9773 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 250: /* opt_on_commit: ON COMMIT sqlDELETE ROWS  */
#line 1752 "sql_parser.y"
                                 { (yyval.i_val) = CA_DELETE; }
#line 9779 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 251: /* opt_on_commit: ON COMMIT PRESERVE ROWS  */
#line 1753 "sql_parser.y"
                                 { (yyval.i_val) = CA_PRESERVE; }
#line 9785 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 252: /* opt_on_commit: ON COMMIT DROP  */
#line 1754 "sql_parser.y"
                                 { (yyval.i_val) = CA_DROP; }
#line 9791 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 253: /* table_content_source: '(' table_element_list ')'  */
#line 1758 "sql_parser.y"
                                { (yyval.sym) = _symbol_create_list( SQL_CREATE_TABLE, (yyvsp[-1].l)); }
#line 9797 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 254: /* table_content_source: as_subquery_clause  */
#line 1759 "sql_parser.y"
                                { (yyval.sym) = _symbol_create_list( SQL_SELECT, (yyvsp[0].l)); }
#line 9803 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 255: /* as_subquery_clause: opt_column_list AS query_expression_def with_or_without_data  */
#line 1767 "sql_parser.y"
                        { (yyval.l) = append_list(L(), (yyvsp[-3].l));
			  append_symbol((yyval.l), (yyvsp[-1].sym)); 
			  append_int((yyval.l), (yyvsp[0].i_val)); }
#line 9811 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 256: /* with_or_without_data: %empty  */
#line 1773 "sql_parser.y"
                        { (yyval.i_val) = 1; }
#line 9817 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 257: /* with_or_without_data: WITH NO DATA  */
#line 1774 "sql_parser.y"
                        { (yyval.i_val) = 0; }
#line 9823 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 258: /* with_or_without_data: WITH DATA  */
#line 1775 "sql_parser.y"
                        { (yyval.i_val) = 1; }
#line 9829 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 259: /* table_element_list: table_element  */
#line 1780 "sql_parser.y"
                        { (yyval.l) = append_symbol(L(), (yyvsp[0].sym)); }
#line 9835 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 260: /* table_element_list: table_element_list ',' table_element  */
#line 1782 "sql_parser.y"
                        { (yyval.l) = append_symbol( (yyvsp[-2].l), (yyvsp[0].sym) ); }
#line 9841 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 266: /* serial_or_bigserial: SERIAL  */
#line 1789 "sql_parser.y"
                     { (yyval.i_val) = 0; }
#line 9847 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 267: /* serial_or_bigserial: BIGSERIAL  */
#line 1790 "sql_parser.y"
                     { (yyval.i_val) = 1; }
#line 9853 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 268: /* column_def: column data_type opt_column_def_opt_list  */
#line 1795 "sql_parser.y"
                {
			dlist *l = L();
			append_string(l, (yyvsp[-2].sval));
			append_type(l, &(yyvsp[-1].type));
			append_list(l, (yyvsp[0].l));
			(yyval.sym) = _symbol_create_list(SQL_COLUMN, l);
		}
#line 9865 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 269: /* column_def: column serial_or_bigserial  */
#line 1803 "sql_parser.y"
                { /* SERIAL = INTEGER GENERATED ALWAYS AS IDENTITY PRIMARY KEY */
			/* handle multi-statements by wrapping them in a list */
			sql_subtype it;
			dlist* stmts;
			/* note: sql_next_seq_name uses sa_alloc */
			str sn = sql_next_seq_name(m);
			dlist *p; /* primary key */
			/* sequence generation code */
			dlist *l = L();
			/* finally all the options */
			dlist *o = L();

			/* the name of the sequence */
			dlist *seqn1 = L(), *seqn2 = L();

			if (m->scanner.schema)
				append_string(seqn1, m->scanner.schema);
			append_list(l, append_string(seqn1, sn));
			if ((yyvsp[0].i_val) == 1)
				sql_find_subtype(&it, "bigint", 64, 0);
			else
				sql_find_subtype(&it, "int", 32, 0);
			append_symbol(o, _symbol_create_list(SQL_TYPE, append_type(L(),&it)));
			append_list(l, o);
			append_int(l, 1); /* to be dropped */

			if (m->sym) {
				stmts = m->sym->data.lval;
			} else {
				stmts = L();
				m->sym = _symbol_create_list(SQL_MULSTMT, stmts);
			}
			append_symbol(stmts, _symbol_create_list(SQL_CREATE_SEQ, l));

			l = L();
			append_string(l, (yyvsp[-1].sval));
			append_type(l, &it);
			o = L();
			if (m->scanner.schema)
				append_string(seqn2, m->scanner.schema);
			append_string(seqn2, sn);
			append_symbol(o, _symbol_create_symbol(SQL_DEFAULT, _symbol_create_list(SQL_NEXT, seqn2)));
			p = L();
			append_string(p, NULL);
			append_symbol(p, _symbol_create(SQL_PRIMARY_KEY, NULL));
			append_symbol(o, _symbol_create_list(SQL_CONSTRAINT, p));
			append_list(l, o);
			(yyval.sym) = _symbol_create_list(SQL_COLUMN, l);
		}
#line 9919 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 270: /* opt_column_def_opt_list: %empty  */
#line 1855 "sql_parser.y"
                                { (yyval.l) = NULL; }
#line 9925 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 272: /* column_def_opt_list: column_option  */
#line 1861 "sql_parser.y"
                        { (yyval.l) = append_symbol(L(), (yyvsp[0].sym) ); }
#line 9931 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 273: /* column_def_opt_list: column_def_opt_list column_option  */
#line 1863 "sql_parser.y"
                        { (yyval.l) = append_symbol( (yyvsp[-1].l), (yyvsp[0].sym) ); }
#line 9937 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 274: /* column_options: ident WITH OPTIONS '(' column_option_list ')'  */
#line 1869 "sql_parser.y"
        { dlist *l = L();
	  append_string(l, (yyvsp[-5].sval) );
	  append_list(l, (yyvsp[-1].l) );
	  (yyval.sym) = _symbol_create_list( SQL_COLUMN_OPTIONS, l ); }
#line 9946 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 275: /* column_option_list: column_option  */
#line 1877 "sql_parser.y"
                        { (yyval.l) = append_symbol(L(), (yyvsp[0].sym) ); }
#line 9952 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 276: /* column_option_list: column_option_list ',' column_option  */
#line 1879 "sql_parser.y"
                        { (yyval.l) = append_symbol((yyvsp[-2].l), (yyvsp[0].sym) ); }
#line 9958 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 280: /* default: DEFAULT default_value  */
#line 1885 "sql_parser.y"
                          { (yyval.sym) = _symbol_create_symbol(SQL_DEFAULT, (yyvsp[0].sym)); }
#line 9964 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 281: /* default_value: search_condition  */
#line 1889 "sql_parser.y"
                        { (yyval.sym) = (yyvsp[0].sym); }
#line 9970 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 282: /* column_constraint: opt_constraint_name column_constraint_type  */
#line 1895 "sql_parser.y"
        { dlist *l = L();
	  append_string(l, (yyvsp[-1].sval) );
	  append_symbol(l, (yyvsp[0].sym) );
	  (yyval.sym) = _symbol_create_list( SQL_CONSTRAINT, l ); }
#line 9979 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 283: /* generated_column: GENERATED ALWAYS AS IDENTITY serial_opt_params  */
#line 1903 "sql_parser.y"
        {
		/* handle multi-statements by wrapping them in a list */
		sql_subtype it;
		dlist* stmts;
		/* note: sql_next_seq_name uses sa_alloc */
		str sn = sql_next_seq_name(m);
		/* sequence generation code */
		dlist *l = L();
		/* the name of the sequence */
		append_list(l, append_string(L(), sn));
		if (!(yyvsp[0].l))
			(yyvsp[0].l) = L();
		sql_find_subtype(&it, "int", 32, 0);
		append_symbol((yyvsp[0].l), _symbol_create_list(SQL_TYPE, append_type(L(),&it)));

		/* finally all the options */
		append_list(l, (yyvsp[0].l));
		append_int(l, 1); /* to be dropped */
		(yyval.sym) = _symbol_create_symbol(SQL_DEFAULT, _symbol_create_list(SQL_NEXT, append_string(L(), sn)));

		if (m->sym) {
			stmts = m->sym->data.lval;
		} else {
			stmts = L();
			m->sym = _symbol_create_list(SQL_MULSTMT, stmts);
		}
		append_symbol(stmts, _symbol_create_list(SQL_CREATE_SEQ, l));
	}
#line 10012 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 284: /* generated_column: AUTO_INCREMENT  */
#line 1932 "sql_parser.y"
        {
		/* handle multi-statements by wrapping them in a list */
		sql_subtype it;
		dlist* stmts;
		/* note: sql_next_seq_name uses sa_alloc */
		str sn = sql_next_seq_name(m);
		/* sequence generation code */
		dlist *l = L();
		/* finally all the options */
		dlist *o = L();

		/* the name of the sequence */
		dlist *seqn1 = L(), *seqn2 = L();

		if (m->scanner.schema)
			append_string(seqn1, m->scanner.schema);
		append_list(l, append_string(seqn1, sn));
		sql_find_subtype(&it, "int", 32, 0);
		append_symbol(o, _symbol_create_list(SQL_TYPE, append_type(L(),&it)));
		append_list(l, o);
		append_int(l, 1); /* to be dropped */
		if (m->scanner.schema)
			append_string(seqn2, m->scanner.schema);
		append_string(seqn2, sn);
		(yyval.sym) = _symbol_create_symbol(SQL_DEFAULT, _symbol_create_list(SQL_NEXT, seqn2));

		if (m->sym) {
			stmts = m->sym->data.lval;
		} else {
			stmts = L();
			m->sym = _symbol_create_list(SQL_MULSTMT, stmts);
		}	
		append_symbol(stmts, _symbol_create_list(SQL_CREATE_SEQ, l));
	}
#line 10051 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 285: /* serial_opt_params: %empty  */
#line 1969 "sql_parser.y"
                                                { (yyval.l) = NULL; }
#line 10057 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 286: /* serial_opt_params: '(' params_list ')'  */
#line 1970 "sql_parser.y"
                                                                { (yyval.l) = (yyvsp[-1].l); }
#line 10063 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 287: /* table_constraint: opt_constraint_name table_constraint_type  */
#line 1977 "sql_parser.y"
        { dlist *l = L();
	  append_string(l, (yyvsp[-1].sval) );
	  append_symbol(l, (yyvsp[0].sym) );
	  (yyval.sym) = _symbol_create_list( SQL_CONSTRAINT, l ); }
#line 10072 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 288: /* opt_constraint_name: %empty  */
#line 1986 "sql_parser.y"
                                { (yyval.sval) = NULL; }
#line 10078 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 289: /* opt_constraint_name: CONSTRAINT ident  */
#line 1987 "sql_parser.y"
                                { (yyval.sval) = (yyvsp[0].sval); }
#line 10084 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 290: /* ref_action: NO ACTION  */
#line 1991 "sql_parser.y"
                                { (yyval.i_val) = 0; }
#line 10090 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 291: /* ref_action: CASCADE  */
#line 1992 "sql_parser.y"
                                { (yyval.i_val) = 1; }
#line 10096 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 292: /* ref_action: RESTRICT  */
#line 1993 "sql_parser.y"
                                { (yyval.i_val) = 2; }
#line 10102 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 293: /* ref_action: SET sqlNULL  */
#line 1994 "sql_parser.y"
                                { (yyval.i_val) = 3; }
#line 10108 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 294: /* ref_action: SET DEFAULT  */
#line 1995 "sql_parser.y"
                                { (yyval.i_val) = 4; }
#line 10114 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 295: /* ref_on_update: ON UPDATE ref_action  */
#line 1999 "sql_parser.y"
                                { (yyval.i_val) = ((yyvsp[0].i_val) << 8); }
#line 10120 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 296: /* ref_on_delete: ON sqlDELETE ref_action  */
#line 2003 "sql_parser.y"
                                { (yyval.i_val) = (yyvsp[0].i_val); }
#line 10126 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 297: /* opt_ref_action: %empty  */
#line 2007 "sql_parser.y"
                                        { (yyval.i_val) = (2 << 8) + 2; /* defaults are RESTRICT */ }
#line 10132 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 298: /* opt_ref_action: ref_on_update  */
#line 2008 "sql_parser.y"
                                        { (yyval.i_val) = (yyvsp[0].i_val); }
#line 10138 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 299: /* opt_ref_action: ref_on_delete  */
#line 2009 "sql_parser.y"
                                        { (yyval.i_val) = (yyvsp[0].i_val); }
#line 10144 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 300: /* opt_ref_action: ref_on_delete ref_on_update  */
#line 2010 "sql_parser.y"
                                        { (yyval.i_val) = (yyvsp[-1].i_val) + (yyvsp[0].i_val); }
#line 10150 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 301: /* opt_ref_action: ref_on_update ref_on_delete  */
#line 2011 "sql_parser.y"
                                        { (yyval.i_val) = (yyvsp[-1].i_val) + (yyvsp[0].i_val); }
#line 10156 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 302: /* opt_match_type: %empty  */
#line 2015 "sql_parser.y"
                                { (yyval.i_val) = 0; }
#line 10162 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 303: /* opt_match_type: FULL  */
#line 2016 "sql_parser.y"
                                { (yyval.i_val) = 1; }
#line 10168 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 304: /* opt_match_type: PARTIAL  */
#line 2017 "sql_parser.y"
                                { (yyval.i_val) = 2; }
#line 10174 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 305: /* opt_match_type: SIMPLE  */
#line 2018 "sql_parser.y"
                                { (yyval.i_val) = 0; }
#line 10180 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 306: /* opt_match: %empty  */
#line 2022 "sql_parser.y"
                                { (yyval.i_val) = 0; }
#line 10186 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 307: /* opt_match: MATCH opt_match_type  */
#line 2023 "sql_parser.y"
                                { (yyval.i_val) = (yyvsp[0].i_val); }
#line 10192 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 308: /* column_constraint_type: NOT sqlNULL  */
#line 2027 "sql_parser.y"
                { (yyval.sym) = _symbol_create( SQL_NOT_NULL, NULL); }
#line 10198 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 309: /* column_constraint_type: sqlNULL  */
#line 2028 "sql_parser.y"
                { (yyval.sym) = _symbol_create( SQL_NULL, NULL); }
#line 10204 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 310: /* column_constraint_type: UNIQUE  */
#line 2029 "sql_parser.y"
                { (yyval.sym) = _symbol_create( SQL_UNIQUE, NULL ); }
#line 10210 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 311: /* column_constraint_type: PRIMARY KEY  */
#line 2030 "sql_parser.y"
                { (yyval.sym) = _symbol_create( SQL_PRIMARY_KEY, NULL ); }
#line 10216 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 312: /* column_constraint_type: REFERENCES qname opt_column_list opt_match opt_ref_action  */
#line 2033 "sql_parser.y"
                        { dlist *l = L();
			  append_list(l, (yyvsp[-3].l) );
			  append_list(l, (yyvsp[-2].l) );
			  append_int(l, (yyvsp[-1].i_val) );
			  append_int(l, (yyvsp[0].i_val) );
			  (yyval.sym) = _symbol_create_list( SQL_FOREIGN_KEY, l); }
#line 10227 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 314: /* table_constraint_type: UNIQUE column_commalist_parens  */
#line 2046 "sql_parser.y"
                        { (yyval.sym) = _symbol_create_list( SQL_UNIQUE, (yyvsp[0].l)); }
#line 10233 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 315: /* table_constraint_type: PRIMARY KEY column_commalist_parens  */
#line 2048 "sql_parser.y"
                        { (yyval.sym) = _symbol_create_list( SQL_PRIMARY_KEY, (yyvsp[0].l)); }
#line 10239 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 316: /* table_constraint_type: FOREIGN KEY column_commalist_parens REFERENCES qname opt_column_list opt_match opt_ref_action  */
#line 2052 "sql_parser.y"
                        { dlist *l = L();
			  append_list(l, (yyvsp[-3].l) );
			  append_list(l, (yyvsp[-5].l) );
			  append_list(l, (yyvsp[-2].l) );
			  append_int(l, (yyvsp[-1].i_val) );
			  append_int(l, (yyvsp[0].i_val) );
			  (yyval.sym) = _symbol_create_list( SQL_FOREIGN_KEY, l); }
#line 10251 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 317: /* domain_constraint_type: CHECK '(' search_condition ')'  */
#line 2063 "sql_parser.y"
                                   { (yyval.sym) = _symbol_create_symbol(SQL_CHECK, (yyvsp[-1].sym)); }
#line 10257 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 318: /* ident_commalist: ident  */
#line 2068 "sql_parser.y"
                        { (yyval.l) = append_string(L(), (yyvsp[0].sval)); }
#line 10263 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 319: /* ident_commalist: ident_commalist ',' ident  */
#line 2070 "sql_parser.y"
                        { (yyval.l) = append_string( (yyvsp[-2].l), (yyvsp[0].sval) ); }
#line 10269 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 320: /* like_table: LIKE qname  */
#line 2074 "sql_parser.y"
                        { (yyval.sym) = _symbol_create_list( SQL_LIKE, (yyvsp[0].l) ); }
#line 10275 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 321: /* view_def: create_or_replace VIEW qname opt_column_list AS query_expression_def opt_with_check_option  */
#line 2079 "sql_parser.y"
        {  dlist *l = L();
	  append_list(l, (yyvsp[-4].l));
	  append_list(l, (yyvsp[-3].l));
	  append_symbol(l, (yyvsp[-1].sym));
	  append_int(l, (yyvsp[0].bval));
	  append_int(l, TRUE);	/* persistent view */
	  append_int(l, (yyvsp[-6].bval));
	  (yyval.sym) = _symbol_create_list( SQL_CREATE_VIEW, l ); 
	}
#line 10289 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 323: /* query_expression_def: '(' query_expression_def ')'  */
#line 2092 "sql_parser.y"
                                        { (yyval.sym) = (yyvsp[-1].sym); }
#line 10295 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 326: /* opt_with_check_option: %empty  */
#line 2101 "sql_parser.y"
                                { (yyval.bval) = FALSE; }
#line 10301 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 327: /* opt_with_check_option: WITH CHECK OPTION  */
#line 2102 "sql_parser.y"
                                { (yyval.bval) = TRUE; }
#line 10307 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 328: /* opt_column_list: %empty  */
#line 2106 "sql_parser.y"
                                { (yyval.l) = NULL; }
#line 10313 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 330: /* column_commalist_parens: '(' ident_commalist ')'  */
#line 2111 "sql_parser.y"
                                { (yyval.l) = (yyvsp[-1].l); }
#line 10319 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 331: /* variable_ref_commalist_parens: '(' variable_ref_commalist ')'  */
#line 2115 "sql_parser.y"
                                        { (yyval.l) = (yyvsp[-1].l); }
#line 10325 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 332: /* type_def: create TYPE qname EXTERNAL sqlNAME ident  */
#line 2120 "sql_parser.y"
                        { dlist *l = L();
				append_list(l, (yyvsp[-3].l));
				append_string(l, (yyvsp[0].sval));
			  (yyval.sym) = _symbol_create_list( SQL_CREATE_TYPE, l ); }
#line 10334 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 333: /* external_function_name: ident '.' ident  */
#line 2127 "sql_parser.y"
                        { (yyval.l) = append_string(append_string(L(), (yyvsp[-2].sval)), (yyvsp[0].sval)); }
#line 10340 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 336: /* func_def_type: FUNCTION  */
#line 2136 "sql_parser.y"
                                        { (yyval.i_val) = F_FUNC; }
#line 10346 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 337: /* func_def_type: PROCEDURE  */
#line 2137 "sql_parser.y"
                                        { (yyval.i_val) = F_PROC; }
#line 10352 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 338: /* func_def_type: AGGREGATE  */
#line 2138 "sql_parser.y"
                                        { (yyval.i_val) = F_AGGR; }
#line 10358 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 339: /* func_def_type: AGGREGATE FUNCTION  */
#line 2139 "sql_parser.y"
                                { (yyval.i_val) = F_AGGR; }
#line 10364 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 340: /* func_def_type: FILTER  */
#line 2140 "sql_parser.y"
                                        { (yyval.i_val) = F_FILT; }
#line 10370 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 341: /* func_def_type: FILTER FUNCTION  */
#line 2141 "sql_parser.y"
                                { (yyval.i_val) = F_FILT; }
#line 10376 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 342: /* func_def_type: WINDOW  */
#line 2142 "sql_parser.y"
                                        { (yyval.i_val) = F_ANALYTIC; }
#line 10382 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 343: /* func_def_type: WINDOW FUNCTION  */
#line 2143 "sql_parser.y"
                                { (yyval.i_val) = F_ANALYTIC; }
#line 10388 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 344: /* func_def_type: sqlLOADER  */
#line 2144 "sql_parser.y"
                                        { (yyval.i_val) = F_LOADER; }
#line 10394 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 345: /* func_def_type: sqlLOADER FUNCTION  */
#line 2145 "sql_parser.y"
                                { (yyval.i_val) = F_LOADER; }
#line 10400 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 346: /* func_def_opt_return: RETURNS func_data_type  */
#line 2148 "sql_parser.y"
                                { (yyval.sym) = (yyvsp[0].sym); }
#line 10406 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 347: /* func_def_opt_return: %empty  */
#line 2149 "sql_parser.y"
                                                        { (yyval.sym) = NULL; }
#line 10412 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 348: /* func_def: create_or_replace func_def_type qname '(' opt_paramlist ')' func_def_opt_return EXTERNAL sqlNAME external_function_name  */
#line 2156 "sql_parser.y"
                        { dlist *f = L();
				append_list(f, (yyvsp[-7].l));
				append_list(f, (yyvsp[-5].l));
				append_symbol(f, (yyvsp[-3].sym));
				append_list(f, (yyvsp[0].l));
				append_list(f, NULL);
				append_int(f, (yyvsp[-8].i_val));
				append_int(f, FUNC_LANG_MAL);
				append_int(f, (yyvsp[-9].bval));
			  (yyval.sym) = _symbol_create_list( SQL_CREATE_FUNC, f ); }
#line 10427 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 349: /* func_def: create_or_replace func_def_type qname '(' opt_paramlist ')' func_def_opt_return routine_body  */
#line 2170 "sql_parser.y"
                        { dlist *f = L();
				append_list(f, (yyvsp[-5].l));
				append_list(f, (yyvsp[-3].l));
				append_symbol(f, (yyvsp[-1].sym));
				append_list(f, NULL);
				append_list(f, (yyvsp[0].l));
				append_int(f, (yyvsp[-6].i_val));
				append_int(f, FUNC_LANG_SQL);
				append_int(f, (yyvsp[-7].bval));
			  (yyval.sym) = _symbol_create_list( SQL_CREATE_FUNC, f ); }
#line 10442 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 350: /* func_def: create_or_replace func_def_type qname '(' opt_paramlist ')' func_def_opt_return LANGUAGE IDENT function_body  */
#line 2184 "sql_parser.y"
                {
			int lang = 0;
			dlist *f = L();
			char l = *(yyvsp[-1].sval);

			if (l == 'R' || l == 'r')
				lang = FUNC_LANG_R;
			else if (l == 'P' || l == 'p') {
				// code does not get cleaner than this people
				if (strcasecmp((yyvsp[-1].sval), "PYTHON_MAP") == 0) {
					lang = FUNC_LANG_MAP_PY;
				} else if (strcasecmp((yyvsp[-1].sval), "PYTHON3_MAP") == 0) {
					lang = FUNC_LANG_MAP_PY3;
				} else if (strcasecmp((yyvsp[-1].sval), "PYTHON3") == 0) {
					lang = FUNC_LANG_PY3;
				} else {
					lang = FUNC_LANG_PY;
				}
			} else if (l == 'C' || l == 'c') {
				if (strcasecmp((yyvsp[-1].sval), "CPP") == 0) {
					lang = FUNC_LANG_CPP;
				} else {
					lang = FUNC_LANG_C;
				}
			}
			else if (l == 'J' || l == 'j')
				lang = FUNC_LANG_J;
			else {
				sqlformaterror(m, "Language name R, C, PYTHON[3], PYTHON[3]_MAP or J(avascript):expected, received '%c'", l);
			}

			append_list(f, (yyvsp[-7].l));
			append_list(f, (yyvsp[-5].l));
			append_symbol(f, (yyvsp[-3].sym));
			append_list(f, NULL);
			append_list(f, append_string(L(), (yyvsp[0].sval)));
			append_int(f, (yyvsp[-8].i_val));
			append_int(f, lang);
			append_int(f, (yyvsp[-9].bval));
			(yyval.sym) = _symbol_create_list( SQL_CREATE_FUNC, f );
		}
#line 10488 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 351: /* routine_body: procedure_statement  */
#line 2229 "sql_parser.y"
                { (yyval.l) = L(); append_symbol( (yyval.l), (yyvsp[0].sym)); }
#line 10494 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 352: /* routine_body: BEGIN procedure_statement_list procedure_statement SCOLON END  */
#line 2233 "sql_parser.y"
                { (yyval.l) = append_symbol((yyvsp[-3].l),(yyvsp[-2].sym)); }
#line 10500 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 353: /* routine_body: BEGIN ATOMIC procedure_statement_list procedure_statement SCOLON END  */
#line 2237 "sql_parser.y"
                { (yyval.l) = append_symbol((yyvsp[-3].l),(yyvsp[-2].sym)); }
#line 10506 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 354: /* procedure_statement_list: %empty  */
#line 2252 "sql_parser.y"
                 { (yyval.l) = L(); }
#line 10512 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 355: /* procedure_statement_list: procedure_statement_list procedure_statement SCOLON  */
#line 2254 "sql_parser.y"
                                { (yyval.l) = append_symbol((yyvsp[-2].l),(yyvsp[-1].sym));}
#line 10518 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 356: /* trigger_procedure_statement_list: %empty  */
#line 2258 "sql_parser.y"
                 { (yyval.l) = L(); }
#line 10524 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 357: /* trigger_procedure_statement_list: trigger_procedure_statement_list trigger_procedure_statement SCOLON  */
#line 2260 "sql_parser.y"
                                        { (yyval.l) = append_symbol((yyvsp[-2].l),(yyvsp[-1].sym));}
#line 10530 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 384: /* call_statement: CALL routine_invocation  */
#line 2308 "sql_parser.y"
                                        { (yyval.sym) = (yyvsp[0].sym); }
#line 10536 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 385: /* call_procedure_statement: CALL func_ref  */
#line 2312 "sql_parser.y"
                                        {(yyval.sym) = _symbol_create_symbol(SQL_CALL, (yyvsp[0].sym));}
#line 10542 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 386: /* routine_invocation: routine_name '(' argument_list ')'  */
#line 2317 "sql_parser.y"
                { dlist *l = L(); 
		  append_list( l, (yyvsp[-3].l));
		  append_list( l, (yyvsp[-1].l));
		  assert(0);
		  (yyval.sym) = _symbol_create_list( SQL_FUNC, l);
		}
#line 10553 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 388: /* argument_list: %empty  */
#line 2328 "sql_parser.y"
                                                                { (yyval.l) = L(); }
#line 10559 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 389: /* argument_list: search_condition  */
#line 2329 "sql_parser.y"
                                                        { (yyval.l) = append_symbol( L(), (yyvsp[0].sym)); }
#line 10565 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 390: /* argument_list: argument_list ',' search_condition  */
#line 2330 "sql_parser.y"
                                        { (yyval.l) = append_symbol( (yyvsp[-2].l), (yyvsp[0].sym)); }
#line 10571 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 391: /* return_statement: RETURN return_value  */
#line 2334 "sql_parser.y"
                            { (yyval.sym) = _symbol_create_symbol(SQL_RETURN, (yyvsp[0].sym)); }
#line 10577 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 394: /* return_value: TABLE '(' query_expression ')'  */
#line 2341 "sql_parser.y"
                { (yyval.sym) = _symbol_create_symbol(SQL_TABLE, (yyvsp[-1].sym)); }
#line 10583 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 395: /* case_statement: CASE search_condition when_statements case_opt_else_statement END CASE  */
#line 2346 "sql_parser.y"
                { (yyval.sym) = _symbol_create_list(SQL_CASE,
		   append_list(
		    append_list(
		     append_symbol(
		      L(),(yyvsp[-4].sym)),(yyvsp[-3].l)),(yyvsp[-2].l))); }
#line 10593 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 396: /* case_statement: CASE when_search_statements case_opt_else_statement END CASE  */
#line 2352 "sql_parser.y"
                 { (yyval.sym) = _symbol_create_list(SQL_CASE,
		   append_list(
		    append_list(
		     L(),(yyvsp[-3].l)),(yyvsp[-2].l))); }
#line 10602 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 397: /* when_statement: WHEN search_condition THEN procedure_statement_list  */
#line 2360 "sql_parser.y"
                        { (yyval.sym) = _symbol_create_list( SQL_WHEN,
			   append_list(
			    append_symbol(
			     L(), (yyvsp[-2].sym)),(yyvsp[0].l))); }
#line 10611 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 398: /* when_statements: when_statement  */
#line 2368 "sql_parser.y"
                        { (yyval.l) = append_symbol( L(), (yyvsp[0].sym));}
#line 10617 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 399: /* when_statements: when_statements when_statement  */
#line 2370 "sql_parser.y"
                        { (yyval.l) = append_symbol( (yyvsp[-1].l), (yyvsp[0].sym)); }
#line 10623 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 400: /* when_search_statement: WHEN search_condition THEN procedure_statement_list  */
#line 2375 "sql_parser.y"
                        { (yyval.sym) = _symbol_create_list( SQL_WHEN,
			   append_list(
			    append_symbol(
			     L(), (yyvsp[-2].sym)),(yyvsp[0].l))); }
#line 10632 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 401: /* when_search_statements: when_search_statement  */
#line 2383 "sql_parser.y"
                        { (yyval.l) = append_symbol( L(), (yyvsp[0].sym)); }
#line 10638 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 402: /* when_search_statements: when_search_statements when_search_statement  */
#line 2385 "sql_parser.y"
                        { (yyval.l) = append_symbol( (yyvsp[-1].l), (yyvsp[0].sym)); }
#line 10644 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 403: /* case_opt_else_statement: %empty  */
#line 2389 "sql_parser.y"
                                        { (yyval.l) = NULL; }
#line 10650 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 404: /* case_opt_else_statement: ELSE procedure_statement_list  */
#line 2390 "sql_parser.y"
                                        { (yyval.l) = (yyvsp[0].l); }
#line 10656 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 405: /* if_statement: IF search_condition THEN procedure_statement_list if_opt_else END IF  */
#line 2400 "sql_parser.y"
                { dlist *l = L();
		  append_symbol(l, (yyvsp[-5].sym));
		  append_list(l, (yyvsp[-3].l));
		  append_symbol(l, (yyvsp[-2].sym));
		  (yyval.sym) = _symbol_create_list(SQL_IF, l);
		}
#line 10667 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 406: /* if_opt_else: %empty  */
#line 2411 "sql_parser.y"
                { (yyval.sym) = NULL; }
#line 10673 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 407: /* if_opt_else: ELSE procedure_statement_list  */
#line 2413 "sql_parser.y"
                { (yyval.sym) = _symbol_create_list(SQL_ELSE, (yyvsp[0].l)); }
#line 10679 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 408: /* if_opt_else: ELSEIF search_condition THEN procedure_statement_list if_opt_else  */
#line 2416 "sql_parser.y"
                { dlist *l = L();
		  append_symbol(l, (yyvsp[-3].sym));
		  append_list(l, (yyvsp[-1].l));
		  append_symbol(l, (yyvsp[0].sym));
		  { (yyval.sym) = _symbol_create_list(SQL_IF, l); }
		}
#line 10690 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 409: /* while_statement: opt_begin_label WHILE search_condition DO procedure_statement_list END WHILE opt_end_label  */
#line 2430 "sql_parser.y"
                { dlist *l;
		  char *label = (yyvsp[-7].sval)?(yyvsp[-7].sval):(yyvsp[0].sval);
		  if ((yyvsp[-7].sval) && (yyvsp[0].sval) && strcmp((yyvsp[-7].sval), (yyvsp[0].sval)) != 0) {
			(yyval.sym) = NULL;
			yyerror(m, "WHILE: labels should match");
			YYABORT;
		  }
 		  l = L();
		  append_symbol(l, (yyvsp[-5].sym)); /* condition */
		  append_list(l, (yyvsp[-3].l));	/* statements */
		  append_string(l, label);
		  (yyval.sym) = _symbol_create_list(SQL_WHILE, l);
		}
#line 10708 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 410: /* opt_begin_label: %empty  */
#line 2446 "sql_parser.y"
                        { (yyval.sval) = NULL; }
#line 10714 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 412: /* opt_end_label: %empty  */
#line 2451 "sql_parser.y"
                        { (yyval.sval) = NULL; }
#line 10720 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 414: /* table_function_column_list: column data_type  */
#line 2456 "sql_parser.y"
                                { (yyval.l) = L();
				  append_string((yyval.l), (yyvsp[-1].sval));
			  	  append_type((yyval.l), &(yyvsp[0].type));
				}
#line 10729 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 415: /* table_function_column_list: table_function_column_list ',' column data_type  */
#line 2461 "sql_parser.y"
                                { 
				  append_string((yyval.l), (yyvsp[-1].sval));
			  	  append_type((yyval.l), &(yyvsp[0].type));
				}
#line 10738 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 416: /* func_data_type: TABLE '(' table_function_column_list ')'  */
#line 2469 "sql_parser.y"
                { (yyval.sym) = _symbol_create_list(SQL_TABLE, (yyvsp[-1].l)); }
#line 10744 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 417: /* func_data_type: data_type  */
#line 2471 "sql_parser.y"
                { (yyval.sym) = _symbol_create_list(SQL_TYPE, append_type(L(),&(yyvsp[0].type))); }
#line 10750 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 419: /* opt_paramlist: '*'  */
#line 2476 "sql_parser.y"
                        { dlist *vararg = L();
			  append_string(vararg, "*");
			  append_type(vararg, NULL);
			  (yyval.l) = append_list(L(), vararg); }
#line 10759 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 420: /* opt_paramlist: %empty  */
#line 2480 "sql_parser.y"
                        { (yyval.l) = NULL; }
#line 10765 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 421: /* paramlist: paramlist ',' ident data_type  */
#line 2485 "sql_parser.y"
                        { dlist *p = L();
			  append_string(p, (yyvsp[-1].sval));
			  append_type(p, &(yyvsp[0].type));
			  (yyval.l) = append_list((yyvsp[-3].l), p); }
#line 10774 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 422: /* paramlist: ident data_type  */
#line 2490 "sql_parser.y"
                        { dlist *l = L();
			  dlist *p = L();
			  append_string(p, (yyvsp[-1].sval));
			  append_type(p, &(yyvsp[0].type));
			  (yyval.l) = append_list(l, p); }
#line 10784 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 423: /* trigger_def: create_or_replace TRIGGER qname trigger_action_time trigger_event ON qname opt_referencing_list triggered_action  */
#line 2540 "sql_parser.y"
        { dlist *l = L();
	  append_list(l, (yyvsp[-6].l));
	  append_int(l, (yyvsp[-5].i_val));
	  append_symbol(l, (yyvsp[-4].sym));
	  append_list(l, (yyvsp[-2].l));
	  append_list(l, (yyvsp[-1].l));
	  append_list(l, (yyvsp[0].l));
	  append_int(l, (yyvsp[-8].bval));
	  (yyval.sym) = _symbol_create_list(SQL_CREATE_TRIGGER, l); 
	}
#line 10799 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 424: /* trigger_action_time: BEFORE  */
#line 2553 "sql_parser.y"
                { (yyval.i_val) = 0; }
#line 10805 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 425: /* trigger_action_time: AFTER  */
#line 2554 "sql_parser.y"
                { (yyval.i_val) = 1; }
#line 10811 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 426: /* trigger_event: INSERT  */
#line 2559 "sql_parser.y"
                                { (yyval.sym) = _symbol_create_list(SQL_INSERT, NULL); }
#line 10817 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 427: /* trigger_event: sqlDELETE  */
#line 2560 "sql_parser.y"
                        { (yyval.sym) = _symbol_create_list(SQL_DELETE, NULL); }
#line 10823 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 428: /* trigger_event: TRUNCATE  */
#line 2561 "sql_parser.y"
                        { (yyval.sym) = _symbol_create_list(SQL_TRUNCATE, NULL); }
#line 10829 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 429: /* trigger_event: UPDATE  */
#line 2562 "sql_parser.y"
                                { (yyval.sym) = _symbol_create_list(SQL_UPDATE, NULL); }
#line 10835 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 430: /* trigger_event: UPDATE OF ident_commalist  */
#line 2563 "sql_parser.y"
                                { (yyval.sym) = _symbol_create_list(SQL_UPDATE, (yyvsp[0].l)); }
#line 10841 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 431: /* opt_referencing_list: %empty  */
#line 2567 "sql_parser.y"
                                                { (yyval.l) = NULL; }
#line 10847 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 432: /* opt_referencing_list: REFERENCING old_or_new_values_alias_list  */
#line 2568 "sql_parser.y"
                                                { (yyval.l) = (yyvsp[0].l); }
#line 10853 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 433: /* old_or_new_values_alias_list: old_or_new_values_alias  */
#line 2572 "sql_parser.y"
                                { (yyval.l) = append_list(L(), (yyvsp[0].l)); }
#line 10859 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 434: /* old_or_new_values_alias_list: old_or_new_values_alias_list old_or_new_values_alias  */
#line 2574 "sql_parser.y"
                                { (yyval.l) = append_list((yyvsp[-1].l), (yyvsp[0].l)); }
#line 10865 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 435: /* old_or_new_values_alias: OLD opt_row opt_as ident  */
#line 2579 "sql_parser.y"
                                { (yyval.l) = append_string(append_int(L(), 0), (yyvsp[0].sval)); }
#line 10871 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 436: /* old_or_new_values_alias: sqlNEW opt_row opt_as ident  */
#line 2580 "sql_parser.y"
                                { (yyval.l) = append_string(append_int(L(), 1), (yyvsp[0].sval)); }
#line 10877 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 437: /* old_or_new_values_alias: OLD TABLE opt_as ident  */
#line 2581 "sql_parser.y"
                                { (yyval.l) = append_string(append_int(L(), 0), (yyvsp[0].sval)); }
#line 10883 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 438: /* old_or_new_values_alias: sqlNEW TABLE opt_as ident  */
#line 2582 "sql_parser.y"
                                { (yyval.l) = append_string(append_int(L(), 1), (yyvsp[0].sval)); }
#line 10889 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 443: /* triggered_action: opt_for_each opt_when triggered_statement  */
#line 2597 "sql_parser.y"
        { (yyval.l) = L();
	  append_int((yyval.l), (yyvsp[-2].i_val));
	  append_symbol((yyval.l), (yyvsp[-1].sym));
	  append_list((yyval.l), (yyvsp[0].l));
	}
#line 10899 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 444: /* opt_for_each: %empty  */
#line 2604 "sql_parser.y"
                                        { (yyval.i_val) = 1; }
#line 10905 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 445: /* opt_for_each: FOR EACH row_or_statement  */
#line 2605 "sql_parser.y"
                                        { (yyval.i_val) = (yyvsp[0].i_val); }
#line 10911 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 446: /* row_or_statement: ROW  */
#line 2609 "sql_parser.y"
                { (yyval.i_val) = 0; }
#line 10917 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 447: /* row_or_statement: STATEMENT  */
#line 2610 "sql_parser.y"
                { (yyval.i_val) = 1; }
#line 10923 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 448: /* opt_when: %empty  */
#line 2614 "sql_parser.y"
                                        { (yyval.sym) = NULL; }
#line 10929 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 449: /* opt_when: WHEN '(' search_condition ')'  */
#line 2615 "sql_parser.y"
                                        { (yyval.sym) = (yyvsp[-1].sym); }
#line 10935 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 450: /* triggered_statement: trigger_procedure_statement  */
#line 2620 "sql_parser.y"
                                { (yyval.l) = append_symbol(L(), (yyvsp[0].sym)); }
#line 10941 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 451: /* triggered_statement: BEGIN ATOMIC trigger_procedure_statement_list END  */
#line 2623 "sql_parser.y"
                                { (yyval.l) = (yyvsp[-1].l); }
#line 10947 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 452: /* routine_designator: func_def_type qname opt_typelist  */
#line 2628 "sql_parser.y"
        { dlist *l = L();
	  append_list(l, (yyvsp[-1].l) );	
	  append_list(l, (yyvsp[0].l) );
	  append_int(l, (yyvsp[-2].i_val) );
	  (yyval.l) = l; }
#line 10957 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 453: /* drop_statement: drop TABLE if_exists qname drop_action  */
#line 2637 "sql_parser.y"
        { dlist *l = L();
	  append_list(l, (yyvsp[-1].l) );
	  append_int(l, (yyvsp[0].i_val) );
	  append_int(l, (yyvsp[-2].bval) );
	  (yyval.sym) = _symbol_create_list( SQL_DROP_TABLE, l ); }
#line 10967 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 454: /* drop_statement: drop func_def_type if_exists qname opt_typelist drop_action  */
#line 2643 "sql_parser.y"
        { dlist *l = L();
	  append_list(l, (yyvsp[-2].l) );
	  append_list(l, (yyvsp[-1].l) );
	  append_int(l, (yyvsp[-4].i_val) );
	  append_int(l, (yyvsp[-3].bval) );
	  append_int(l, 0 ); /* not all */
	  append_int(l, (yyvsp[0].i_val) );
	  (yyval.sym) = _symbol_create_list( SQL_DROP_FUNC, l ); }
#line 10980 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 455: /* drop_statement: drop ALL func_def_type qname drop_action  */
#line 2652 "sql_parser.y"
        { dlist *l = L();
	  append_list(l, (yyvsp[-1].l) );
	  append_list(l, NULL );
	  append_int(l, (yyvsp[-2].i_val) );
	  append_int(l, FALSE );
	  append_int(l, 1 ); /* all */
	  append_int(l, (yyvsp[0].i_val) );
	  (yyval.sym) = _symbol_create_list( SQL_DROP_FUNC, l ); }
#line 10993 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 456: /* drop_statement: drop VIEW if_exists qname drop_action  */
#line 2661 "sql_parser.y"
        { dlist *l = L();
	  append_list(l, (yyvsp[-1].l) );
	  append_int(l, (yyvsp[0].i_val) );
	  append_int(l, (yyvsp[-2].bval) );
	  (yyval.sym) = _symbol_create_list( SQL_DROP_VIEW, l ); }
#line 11003 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 457: /* drop_statement: drop TYPE qname drop_action  */
#line 2667 "sql_parser.y"
        { dlist *l = L();
	  append_list(l, (yyvsp[-1].l) );
	  append_int(l, (yyvsp[0].i_val) );
	  (yyval.sym) = _symbol_create_list( SQL_DROP_TYPE, l ); }
#line 11012 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 458: /* drop_statement: drop ROLE ident  */
#line 2671 "sql_parser.y"
                          { (yyval.sym) = _symbol_create( SQL_DROP_ROLE, (yyvsp[0].sval) ); }
#line 11018 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 459: /* drop_statement: drop USER ident  */
#line 2672 "sql_parser.y"
                          { (yyval.sym) = _symbol_create( SQL_DROP_USER, (yyvsp[0].sval) ); }
#line 11024 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 460: /* drop_statement: drop INDEX qname  */
#line 2673 "sql_parser.y"
                          { (yyval.sym) = _symbol_create_list( SQL_DROP_INDEX, (yyvsp[0].l) ); }
#line 11030 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 461: /* drop_statement: drop TRIGGER if_exists qname  */
#line 2675 "sql_parser.y"
        { dlist *l = L();
	  append_list(l, (yyvsp[0].l) );
	  append_int(l, (yyvsp[-1].bval) );
	  (yyval.sym) = _symbol_create_list( SQL_DROP_TRIGGER, l );
	}
#line 11040 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 462: /* opt_typelist: %empty  */
#line 2683 "sql_parser.y"
                        {(yyval.l) = NULL;}
#line 11046 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 463: /* opt_typelist: '(' typelist ')'  */
#line 2684 "sql_parser.y"
                        {(yyval.l) = (yyvsp[-1].l);}
#line 11052 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 464: /* opt_typelist: '(' ')'  */
#line 2685 "sql_parser.y"
                        {(yyval.l) = L(); }
#line 11058 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 465: /* typelist: data_type  */
#line 2689 "sql_parser.y"
                                { dlist *l = L();
				  append_type(l, &(yyvsp[0].type) );
				  (yyval.l)= l; }
#line 11066 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 466: /* typelist: data_type ',' typelist  */
#line 2692 "sql_parser.y"
                                { append_type((yyvsp[0].l), &(yyvsp[-2].type));
				  (yyval.l) = (yyvsp[0].l); }
#line 11073 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 467: /* drop_action: %empty  */
#line 2697 "sql_parser.y"
                        { (yyval.i_val) = 0; }
#line 11079 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 468: /* drop_action: RESTRICT  */
#line 2698 "sql_parser.y"
                        { (yyval.i_val) = 0; }
#line 11085 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 469: /* drop_action: CASCADE  */
#line 2699 "sql_parser.y"
                        { (yyval.i_val) = 1; }
#line 11091 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 479: /* transaction_statement: transaction_stmt  */
#line 2720 "sql_parser.y"
        {
	  (yyval.sym) = (yyvsp[0].sym);
	  m->type = Q_TRANS;					}
#line 11099 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 482: /* transaction_stmt: COMMIT opt_work opt_chain  */
#line 2732 "sql_parser.y"
                { (yyval.sym) = _symbol_create_int( TR_COMMIT, (yyvsp[0].bval));  }
#line 11105 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 483: /* transaction_stmt: SAVEPOINT ident  */
#line 2734 "sql_parser.y"
                { (yyval.sym) = _symbol_create( TR_SAVEPOINT, (yyvsp[0].sval)); }
#line 11111 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 484: /* transaction_stmt: RELEASE SAVEPOINT ident  */
#line 2736 "sql_parser.y"
                { (yyval.sym) = _symbol_create( TR_RELEASE, (yyvsp[0].sval)); }
#line 11117 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 485: /* transaction_stmt: ROLLBACK opt_work opt_chain opt_to_savepoint  */
#line 2738 "sql_parser.y"
                { (yyval.sym) = _symbol_create_list( TR_ROLLBACK,
		   append_string(
			append_int(L(), (yyvsp[-1].bval)), (yyvsp[0].sval) )); }
#line 11125 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 486: /* transaction_stmt: start_transaction TRANSACTION transaction_mode_list  */
#line 2742 "sql_parser.y"
                { (yyval.sym) = _symbol_create_int( TR_START, (yyvsp[0].i_val)); }
#line 11131 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 487: /* transaction_stmt: SET LOCAL TRANSACTION transaction_mode_list  */
#line 2744 "sql_parser.y"
                { (yyval.sym) = _symbol_create_int( TR_MODE, (yyvsp[0].i_val)); }
#line 11137 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 488: /* transaction_stmt: SET TRANSACTION transaction_mode_list  */
#line 2746 "sql_parser.y"
                { (yyval.sym) = _symbol_create_int( TR_MODE, (yyvsp[0].i_val)); }
#line 11143 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 489: /* transaction_mode_list: %empty  */
#line 2750 "sql_parser.y"
                                { (yyval.i_val) = tr_serializable; }
#line 11149 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 490: /* transaction_mode_list: _transaction_mode_list  */
#line 2751 "sql_parser.y"
                                { (yyval.i_val) = (yyvsp[0].i_val); }
#line 11155 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 491: /* _transaction_mode_list: transaction_mode  */
#line 2756 "sql_parser.y"
                { (yyval.i_val) = (yyvsp[0].i_val); }
#line 11161 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 492: /* _transaction_mode_list: _transaction_mode_list ',' transaction_mode  */
#line 2758 "sql_parser.y"
                { (yyval.i_val) = ((yyvsp[-2].i_val) | (yyvsp[0].i_val)); }
#line 11167 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 493: /* transaction_mode: READ ONLY  */
#line 2762 "sql_parser.y"
                                        { (yyval.i_val) = tr_readonly; }
#line 11173 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 494: /* transaction_mode: READ WRITE  */
#line 2763 "sql_parser.y"
                                        { (yyval.i_val) = tr_writable; }
#line 11179 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 495: /* transaction_mode: ISOLATION LEVEL iso_level  */
#line 2764 "sql_parser.y"
                                        { (yyval.i_val) = (yyvsp[0].i_val); }
#line 11185 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 496: /* transaction_mode: DIAGNOSTICS sqlSIZE intval  */
#line 2765 "sql_parser.y"
                                        { (yyval.i_val) = tr_none; /* not supported */ }
#line 11191 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 497: /* iso_level: READ UNCOMMITTED  */
#line 2769 "sql_parser.y"
                                { (yyval.i_val) = tr_snapshot; }
#line 11197 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 498: /* iso_level: READ COMMITTED  */
#line 2770 "sql_parser.y"
                                { (yyval.i_val) = tr_snapshot; }
#line 11203 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 499: /* iso_level: sqlREPEATABLE READ  */
#line 2771 "sql_parser.y"
                                { (yyval.i_val) = tr_snapshot; }
#line 11209 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 500: /* iso_level: SNAPSHOT  */
#line 2772 "sql_parser.y"
                                { (yyval.i_val) = tr_snapshot; }
#line 11215 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 501: /* iso_level: SERIALIZABLE  */
#line 2773 "sql_parser.y"
                                { (yyval.i_val) = tr_serializable; }
#line 11221 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 502: /* opt_work: WORK  */
#line 2777 "sql_parser.y"
                        { (yyval.bval) = 0; }
#line 11227 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 503: /* opt_work: %empty  */
#line 2778 "sql_parser.y"
                        { (yyval.bval) = 0; }
#line 11233 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 504: /* opt_chain: AND CHAIN  */
#line 2782 "sql_parser.y"
                        { (yyval.bval) = 1; }
#line 11239 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 505: /* opt_chain: AND NO CHAIN  */
#line 2783 "sql_parser.y"
                        { (yyval.bval) = 0; }
#line 11245 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 506: /* opt_chain: %empty  */
#line 2784 "sql_parser.y"
                        { (yyval.bval) = 0; }
#line 11251 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 507: /* opt_to_savepoint: %empty  */
#line 2788 "sql_parser.y"
                        { (yyval.sval) = NULL; }
#line 11257 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 508: /* opt_to_savepoint: TO SAVEPOINT ident  */
#line 2789 "sql_parser.y"
                        { (yyval.sval) = (yyvsp[0].sval); }
#line 11263 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 509: /* opt_on_location: %empty  */
#line 2793 "sql_parser.y"
                        { (yyval.bval) = 0; }
#line 11269 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 510: /* opt_on_location: ON CLIENT  */
#line 2794 "sql_parser.y"
                        { (yyval.bval) = 1; }
#line 11275 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 511: /* opt_on_location: ON SERVER  */
#line 2795 "sql_parser.y"
                        { (yyval.bval) = 0; }
#line 11281 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 512: /* copyfrom_stmt: COPY opt_nr INTO qname opt_column_list FROM string_commalist opt_header_list opt_on_location opt_seps opt_escape opt_null_string opt_best_effort opt_fwf_widths  */
#line 2801 "sql_parser.y"
        { dlist *l = L();
	  append_list(l, (yyvsp[-10].l));
	  append_list(l, (yyvsp[-9].l));
	  append_list(l, (yyvsp[-7].l));
	  append_list(l, (yyvsp[-6].l));
	  append_list(l, (yyvsp[-4].l));
	  append_list(l, (yyvsp[-12].l));
	  append_string(l, (yyvsp[-2].sval));
	  append_int(l, (yyvsp[-1].bval));
	  append_list(l, (yyvsp[0].l));
	  append_int(l, (yyvsp[-5].bval));
	  append_int(l, (yyvsp[-3].bval));
	  (yyval.sym) = _symbol_create_list( SQL_COPYFROM, l ); }
#line 11299 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 513: /* copyfrom_stmt: COPY opt_nr INTO qname opt_column_list FROM STDIN opt_header_list opt_seps opt_escape opt_null_string opt_best_effort  */
#line 2816 "sql_parser.y"
        { dlist *l = L();
	  append_list(l, (yyvsp[-8].l));
	  append_list(l, (yyvsp[-7].l));
	  append_list(l, NULL);
	  append_list(l, (yyvsp[-4].l));
	  append_list(l, (yyvsp[-3].l));
	  append_list(l, (yyvsp[-10].l));
	  append_string(l, (yyvsp[-1].sval));
	  append_int(l, (yyvsp[0].bval));
	  append_list(l, NULL);
	  append_int(l, 0);
	  append_int(l, (yyvsp[-2].bval));
	  (yyval.sym) = _symbol_create_list( SQL_COPYFROM, l ); }
#line 11317 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 514: /* copyfrom_stmt: COPY sqlLOADER INTO qname FROM func_ref  */
#line 2831 "sql_parser.y"
        { dlist *l = L();
	  append_list(l, (yyvsp[-2].l));
	  append_symbol(l, (yyvsp[0].sym));
	  (yyval.sym) = _symbol_create_list( SQL_COPYLOADER, l ); }
#line 11326 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 515: /* copyfrom_stmt: COPY opt_endianness BINARY INTO qname opt_column_list FROM string_commalist opt_on_location  */
#line 2837 "sql_parser.y"
        { dlist *l = L();
	  append_list(l, (yyvsp[-4].l));
	  append_list(l, (yyvsp[-3].l));
	  append_list(l, (yyvsp[-1].l));
	  append_int(l, (yyvsp[0].bval));
	  append_int(l, (yyvsp[-7].i_val));
	  (yyval.sym) = _symbol_create_list( SQL_BINCOPYFROM, l ); }
#line 11338 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 516: /* copyto_stmt: COPY query_expression_def INTO string opt_on_location opt_seps opt_null_string  */
#line 2849 "sql_parser.y"
        { dlist *l = L();
	  append_symbol(l, (yyvsp[-5].sym));
	  append_string(l, (yyvsp[-3].sval));
	  append_list(l, (yyvsp[-1].l));
	  append_string(l, (yyvsp[0].sval));
	  append_int(l, (yyvsp[-2].bval));
	  (yyval.sym) = _symbol_create_list( SQL_COPYINTO, l ); }
#line 11350 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 517: /* copyto_stmt: COPY query_expression_def INTO STDOUT opt_seps opt_null_string  */
#line 2858 "sql_parser.y"
        { dlist *l = L();
	  append_symbol(l, (yyvsp[-4].sym));
	  append_string(l, NULL);
	  append_list(l, (yyvsp[-1].l));
	  append_string(l, (yyvsp[0].sval));
	  append_int(l, 0);
	  (yyval.sym) = _symbol_create_list( SQL_COPYINTO, l ); }
#line 11362 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 518: /* copyto_stmt: COPY query_expression_def INTO opt_endianness BINARY string_commalist opt_on_location  */
#line 2867 "sql_parser.y"
        { dlist *l = L();
	  append_symbol(l, (yyvsp[-5].sym));
	  append_int(l, (yyvsp[-3].i_val));
	  append_list(l, (yyvsp[-1].l));
	  append_int(l, (yyvsp[0].bval));
	  (yyval.sym) = _symbol_create_list( SQL_BINCOPYINTO, l ); }
#line 11373 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 519: /* opt_fwf_widths: %empty  */
#line 2876 "sql_parser.y"
                                { (yyval.l) = NULL; }
#line 11379 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 520: /* opt_fwf_widths: FWF '(' fwf_widthlist ')'  */
#line 2877 "sql_parser.y"
                            { (yyval.l) = (yyvsp[-1].l); }
#line 11385 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 521: /* fwf_widthlist: poslng  */
#line 2882 "sql_parser.y"
                        { (yyval.l) = append_lng(L(), (yyvsp[0].l_val)); }
#line 11391 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 522: /* fwf_widthlist: fwf_widthlist ',' poslng  */
#line 2884 "sql_parser.y"
                        { (yyval.l) = append_lng((yyvsp[-2].l), (yyvsp[0].l_val)); }
#line 11397 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 523: /* opt_header_list: %empty  */
#line 2888 "sql_parser.y"
                                { (yyval.l) = NULL; }
#line 11403 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 524: /* opt_header_list: '(' header_list ')'  */
#line 2889 "sql_parser.y"
                                { (yyval.l) = (yyvsp[-1].l); }
#line 11409 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 525: /* header_list: header  */
#line 2893 "sql_parser.y"
                                { (yyval.l) = append_list(L(), (yyvsp[0].l)); }
#line 11415 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 526: /* header_list: header_list ',' header  */
#line 2894 "sql_parser.y"
                                { (yyval.l) = append_list((yyvsp[-2].l), (yyvsp[0].l)); }
#line 11421 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 527: /* header: ident  */
#line 2899 "sql_parser.y"
                        { dlist *l = L();
			  append_string(l, (yyvsp[0].sval) );
			  (yyval.l) = l; }
#line 11429 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 528: /* header: ident string  */
#line 2903 "sql_parser.y"
                        { dlist *l = L();
			  append_string(l, (yyvsp[-1].sval) );
			  append_string(l, (yyvsp[0].sval) );
			  (yyval.l) = l; }
#line 11438 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 529: /* opt_seps: %empty  */
#line 2911 "sql_parser.y"
                                { dlist *l = L();
				  append_string(l, sa_strdup(SA, "|"));
				  append_string(l, sa_strdup(SA, "\n"));
				  (yyval.l) = l; }
#line 11447 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 530: /* opt_seps: opt_using DELIMITERS string  */
#line 2916 "sql_parser.y"
                                { dlist *l = L();
				  append_string(l, (yyvsp[0].sval));
				  append_string(l, sa_strdup(SA, "\n"));
				  (yyval.l) = l; }
#line 11456 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 531: /* opt_seps: opt_using DELIMITERS string ',' string  */
#line 2921 "sql_parser.y"
                                { dlist *l = L();
				  append_string(l, (yyvsp[-2].sval));
				  append_string(l, (yyvsp[0].sval));
				  (yyval.l) = l; }
#line 11465 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 532: /* opt_seps: opt_using DELIMITERS string ',' string ',' string  */
#line 2926 "sql_parser.y"
                                { dlist *l = L();
				  append_string(l, (yyvsp[-4].sval));
				  append_string(l, (yyvsp[-2].sval));
				  append_string(l, (yyvsp[0].sval));
				  (yyval.l) = l; }
#line 11475 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 533: /* opt_using: %empty  */
#line 2934 "sql_parser.y"
                                { (yyval.sval) = NULL; }
#line 11481 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 534: /* opt_using: USING  */
#line 2935 "sql_parser.y"
                                { (yyval.sval) = NULL; }
#line 11487 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 535: /* opt_nr: %empty  */
#line 2939 "sql_parser.y"
                                { (yyval.l) = NULL; }
#line 11493 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 536: /* opt_nr: poslng RECORDS  */
#line 2940 "sql_parser.y"
                                { (yyval.l) = append_lng(append_lng(L(), (yyvsp[-1].l_val)), 0); }
#line 11499 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 537: /* opt_nr: OFFSET poslng  */
#line 2941 "sql_parser.y"
                                { (yyval.l) = append_lng(append_lng(L(), -1), (yyvsp[0].l_val)); }
#line 11505 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 538: /* opt_nr: poslng OFFSET poslng RECORDS  */
#line 2943 "sql_parser.y"
                                { (yyval.l) = append_lng(append_lng(L(), (yyvsp[-3].l_val)), (yyvsp[-1].l_val)); }
#line 11511 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 539: /* opt_nr: poslng RECORDS OFFSET poslng  */
#line 2945 "sql_parser.y"
                                { (yyval.l) = append_lng(append_lng(L(), (yyvsp[-3].l_val)), (yyvsp[0].l_val)); }
#line 11517 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 540: /* opt_null_string: %empty  */
#line 2949 "sql_parser.y"
                                { (yyval.sval) = NULL; }
#line 11523 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 541: /* opt_null_string: sqlNULL opt_as string  */
#line 2950 "sql_parser.y"
                                { (yyval.sval) = (yyvsp[0].sval); }
#line 11529 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 542: /* opt_escape: %empty  */
#line 2954 "sql_parser.y"
                        { (yyval.bval) = TRUE; }
#line 11535 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 543: /* opt_escape: ESCAPE  */
#line 2955 "sql_parser.y"
                        { (yyval.bval) = TRUE; }
#line 11541 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 544: /* opt_escape: NO ESCAPE  */
#line 2956 "sql_parser.y"
                        { (yyval.bval) = FALSE; }
#line 11547 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 545: /* opt_best_effort: %empty  */
#line 2960 "sql_parser.y"
                        { (yyval.bval) = FALSE; }
#line 11553 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 546: /* opt_best_effort: BEST EFFORT  */
#line 2961 "sql_parser.y"
                        { (yyval.bval) = TRUE; }
#line 11559 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 547: /* string_commalist: string_commalist_contents  */
#line 2965 "sql_parser.y"
                                           { (yyval.l) = (yyvsp[0].l); }
#line 11565 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 548: /* string_commalist: '(' string_commalist_contents ')'  */
#line 2966 "sql_parser.y"
                                           { (yyval.l) = (yyvsp[-1].l); }
#line 11571 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 549: /* string_commalist_contents: string  */
#line 2970 "sql_parser.y"
                        { (yyval.l) = append_string(L(), (yyvsp[0].sval)); }
#line 11577 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 550: /* string_commalist_contents: string_commalist_contents ',' string  */
#line 2972 "sql_parser.y"
                        { (yyval.l) = append_string((yyvsp[-2].l), (yyvsp[0].sval)); }
#line 11583 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 551: /* opt_endianness: %empty  */
#line 2976 "sql_parser.y"
                                { (yyval.i_val) = endian_native; }
#line 11589 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 552: /* opt_endianness: BIG ENDIAN  */
#line 2977 "sql_parser.y"
                                { (yyval.i_val) = endian_big; }
#line 11595 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 553: /* opt_endianness: LITTLE ENDIAN  */
#line 2978 "sql_parser.y"
                        { (yyval.i_val) = endian_little; }
#line 11601 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 554: /* opt_endianness: NATIVE ENDIAN  */
#line 2979 "sql_parser.y"
                        { (yyval.i_val) = endian_native; }
#line 11607 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 555: /* delete_stmt: sqlDELETE FROM qname opt_alias_name opt_where_clause  */
#line 2985 "sql_parser.y"
        { dlist *l = L();
	  append_list(l, (yyvsp[-2].l));
	  append_string(l, (yyvsp[-1].sval));
	  append_symbol(l, (yyvsp[0].sym));
	  (yyval.sym) = _symbol_create_list( SQL_DELETE, l ); }
#line 11617 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 556: /* check_identity: %empty  */
#line 2993 "sql_parser.y"
                                { (yyval.i_val) = 0; }
#line 11623 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 557: /* check_identity: CONTINUE IDENTITY  */
#line 2994 "sql_parser.y"
                        { (yyval.i_val) = 0; }
#line 11629 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 558: /* check_identity: RESTART IDENTITY  */
#line 2995 "sql_parser.y"
                        { (yyval.i_val) = 1; }
#line 11635 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 559: /* truncate_stmt: TRUNCATE TABLE qname check_identity drop_action  */
#line 3000 "sql_parser.y"
        { dlist *l = L();
	  append_list(l, (yyvsp[-2].l) );
	  append_int(l, (yyvsp[-1].i_val) );
	  append_int(l, (yyvsp[0].i_val) );
	  (yyval.sym) = _symbol_create_list( SQL_TRUNCATE, l ); }
#line 11645 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 560: /* truncate_stmt: TRUNCATE qname check_identity drop_action  */
#line 3006 "sql_parser.y"
        { dlist *l = L();
	  append_list(l, (yyvsp[-2].l) );
	  append_int(l, (yyvsp[-1].i_val) );
	  append_int(l, (yyvsp[0].i_val) );
	  (yyval.sym) = _symbol_create_list( SQL_TRUNCATE, l ); }
#line 11655 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 561: /* update_stmt: UPDATE qname opt_alias_name SET assignment_commalist opt_from_clause opt_where_clause  */
#line 3016 "sql_parser.y"
        { dlist *l = L();
	  append_list(l, (yyvsp[-5].l));
	  append_string(l, (yyvsp[-4].sval));
	  append_list(l, (yyvsp[-2].l));
	  append_symbol(l, (yyvsp[-1].sym));
	  append_symbol(l, (yyvsp[0].sym));
	  (yyval.sym) = _symbol_create_list( SQL_UPDATE, l ); }
#line 11667 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 562: /* opt_search_condition: %empty  */
#line 3026 "sql_parser.y"
                        { (yyval.sym) = NULL; }
#line 11673 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 563: /* opt_search_condition: AND search_condition  */
#line 3027 "sql_parser.y"
                        { (yyval.sym) = (yyvsp[0].sym); }
#line 11679 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 564: /* merge_update_or_delete: UPDATE SET assignment_commalist  */
#line 3032 "sql_parser.y"
   { dlist *l = L();
     append_list(l, (yyvsp[0].l));
     (yyval.sym) = _symbol_create_list( SQL_UPDATE, l ); }
#line 11687 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 565: /* merge_update_or_delete: sqlDELETE  */
#line 3036 "sql_parser.y"
   { (yyval.sym) = _symbol_create_list( SQL_DELETE, NULL ); }
#line 11693 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 566: /* merge_insert: INSERT opt_column_list values_or_query_spec  */
#line 3041 "sql_parser.y"
   { dlist *l = L();
     append_list(l, (yyvsp[-1].l));
     append_symbol(l, (yyvsp[0].sym));
     (yyval.sym) = _symbol_create_list( SQL_INSERT, l ); }
#line 11702 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 567: /* merge_match_clause: WHEN MATCHED opt_search_condition THEN merge_update_or_delete  */
#line 3049 "sql_parser.y"
   { dlist *l = L();
     append_symbol(l, (yyvsp[-2].sym));
     append_symbol(l, (yyvsp[0].sym));
     (yyval.sym) = _symbol_create_list( SQL_MERGE_MATCH, l ); }
#line 11711 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 568: /* merge_match_clause: WHEN NOT MATCHED opt_search_condition THEN merge_insert  */
#line 3054 "sql_parser.y"
   { dlist *l = L();
     append_symbol(l, (yyvsp[-2].sym));
     append_symbol(l, (yyvsp[0].sym));
     (yyval.sym) = _symbol_create_list( SQL_MERGE_NO_MATCH, l ); }
#line 11720 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 569: /* merge_when_list: merge_match_clause  */
#line 3061 "sql_parser.y"
                                      { (yyval.l) = append_symbol(L(), (yyvsp[0].sym)); }
#line 11726 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 570: /* merge_when_list: merge_when_list merge_match_clause  */
#line 3062 "sql_parser.y"
                                      { (yyval.l) = append_symbol((yyvsp[-1].l), (yyvsp[0].sym)); }
#line 11732 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 571: /* merge_stmt: MERGE INTO qname opt_alias_name USING table_ref ON search_condition merge_when_list  */
#line 3068 "sql_parser.y"
        { dlist *l = L();
	  append_list(l, (yyvsp[-6].l));
	  append_string(l, (yyvsp[-5].sval));
	  append_symbol(l, (yyvsp[-3].sym));
	  append_symbol(l, (yyvsp[-1].sym));
	  append_list(l, (yyvsp[0].l));
	  (yyval.sym) = _symbol_create_list( SQL_MERGE, l ); }
#line 11744 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 572: /* insert_stmt: INSERT INTO qname values_or_query_spec  */
#line 3079 "sql_parser.y"
        { dlist *l = L();
	  append_list(l, (yyvsp[-1].l));
	  append_list(l, NULL);
	  append_symbol(l, (yyvsp[0].sym));
	  (yyval.sym) = _symbol_create_list( SQL_INSERT, l ); }
#line 11754 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 573: /* insert_stmt: INSERT INTO qname column_commalist_parens values_or_query_spec  */
#line 3087 "sql_parser.y"
        { dlist *l = L();
	  append_list(l, (yyvsp[-2].l));
	  append_list(l, (yyvsp[-1].l));
	  append_symbol(l, (yyvsp[0].sym));
	  (yyval.sym) = _symbol_create_list( SQL_INSERT, l ); }
#line 11764 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 574: /* values_or_query_spec: %empty  */
#line 3096 "sql_parser.y"
        { dlist *l = L();
	  append_list(l, L());
	  (yyval.sym) = _symbol_create_list(SQL_VALUES, l); }
#line 11772 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 575: /* values_or_query_spec: DEFAULT VALUES  */
#line 3100 "sql_parser.y"
        { dlist *l = L();
	  append_list(l, L());
	  (yyval.sym) = _symbol_create_list(SQL_VALUES, l); }
#line 11780 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 577: /* row_commalist: '(' atom_commalist ')'  */
#line 3107 "sql_parser.y"
                                { (yyval.l) = append_list(L(), (yyvsp[-1].l)); }
#line 11786 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 578: /* row_commalist: row_commalist ',' '(' atom_commalist ')'  */
#line 3109 "sql_parser.y"
                                { (yyval.l) = append_list((yyvsp[-4].l), (yyvsp[-1].l)); }
#line 11792 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 579: /* atom_commalist: insert_atom  */
#line 3113 "sql_parser.y"
                        { (yyval.l) = append_symbol(L(), (yyvsp[0].sym)); }
#line 11798 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 580: /* atom_commalist: atom_commalist ',' insert_atom  */
#line 3115 "sql_parser.y"
                        { (yyval.l) = append_symbol((yyvsp[-2].l), (yyvsp[0].sym)); }
#line 11804 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 581: /* value_commalist: value  */
#line 3119 "sql_parser.y"
                        { (yyval.l) = append_symbol(L(), (yyvsp[0].sym)); }
#line 11810 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 582: /* value_commalist: value_commalist ',' value  */
#line 3121 "sql_parser.y"
                        { (yyval.l) = append_symbol((yyvsp[-2].l), (yyvsp[0].sym)); }
#line 11816 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 583: /* null: sqlNULL  */
#line 3125 "sql_parser.y"
                        { (yyval.sym) = _symbol_create(SQL_NULL, NULL ); }
#line 11822 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 585: /* insert_atom: DEFAULT  */
#line 3130 "sql_parser.y"
                        { (yyval.sym) = _symbol_create(SQL_DEFAULT, NULL ); }
#line 11828 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 589: /* opt_distinct: %empty  */
#line 3140 "sql_parser.y"
                        { (yyval.bval) = FALSE; }
#line 11834 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 590: /* opt_distinct: ALL  */
#line 3141 "sql_parser.y"
                        { (yyval.bval) = FALSE; }
#line 11840 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 591: /* opt_distinct: DISTINCT  */
#line 3142 "sql_parser.y"
                        { (yyval.bval) = TRUE; }
#line 11846 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 592: /* assignment_commalist: assignment  */
#line 3146 "sql_parser.y"
                        { (yyval.l) = append_symbol(L(), (yyvsp[0].sym) ); }
#line 11852 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 593: /* assignment_commalist: assignment_commalist ',' assignment  */
#line 3148 "sql_parser.y"
                        { (yyval.l) = append_symbol((yyvsp[-2].l), (yyvsp[0].sym) ); }
#line 11858 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 594: /* assignment: column '=' insert_atom  */
#line 3153 "sql_parser.y"
        { dlist *l = L();
	  append_symbol(l, (yyvsp[0].sym));
	  append_string(l, (yyvsp[-2].sval));
	  (yyval.sym) = _symbol_create_list( SQL_ASSIGN, l); }
#line 11867 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 595: /* assignment: column_commalist_parens '=' subquery  */
#line 3158 "sql_parser.y"
        { dlist *l = L();
	  append_symbol(l, (yyvsp[0].sym));
	  append_list(l, (yyvsp[-2].l));
	  (yyval.sym) = _symbol_create_list( SQL_ASSIGN, l ); }
#line 11876 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 596: /* opt_where_clause: %empty  */
#line 3165 "sql_parser.y"
                                { (yyval.sym) = NULL; }
#line 11882 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 597: /* opt_where_clause: WHERE search_condition  */
#line 3166 "sql_parser.y"
                                { (yyval.sym) = (yyvsp[0].sym); }
#line 11888 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 598: /* joined_table: '(' joined_table ')'  */
#line 3173 "sql_parser.y"
        { (yyval.sym) = (yyvsp[-1].sym); }
#line 11894 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 599: /* joined_table: table_ref CROSS JOIN table_ref  */
#line 3175 "sql_parser.y"
        { dlist *l = L();
	  append_symbol(l, (yyvsp[-3].sym));
	  append_int(l, 0);
	  append_int(l, 4);
	  append_symbol(l, (yyvsp[0].sym));
	  append_symbol(l, NULL);
	  (yyval.sym) = _symbol_create_list( SQL_JOIN, l); }
#line 11906 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 600: /* joined_table: table_ref join_type JOIN table_ref join_spec  */
#line 3183 "sql_parser.y"
        { dlist *l = L();
	  append_symbol(l, (yyvsp[-4].sym));
	  append_int(l, 0);
	  append_int(l, (yyvsp[-3].i_val));
	  append_symbol(l, (yyvsp[-1].sym));
	  append_symbol(l, (yyvsp[0].sym));
	  (yyval.sym) = _symbol_create_list( SQL_JOIN, l); }
#line 11918 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 601: /* joined_table: table_ref NATURAL join_type JOIN table_ref  */
#line 3191 "sql_parser.y"
        { dlist *l = L();
	  append_symbol(l, (yyvsp[-4].sym));
	  append_int(l, 1);
	  append_int(l, (yyvsp[-2].i_val));
	  append_symbol(l, (yyvsp[0].sym));
	  append_symbol(l, NULL);
	  (yyval.sym) = _symbol_create_list( SQL_JOIN, l); }
#line 11930 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 602: /* join_type: %empty  */
#line 3201 "sql_parser.y"
                                { (yyval.i_val) = 0; }
#line 11936 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 603: /* join_type: INNER  */
#line 3202 "sql_parser.y"
                                { (yyval.i_val) = 0; }
#line 11942 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 604: /* join_type: outer_join_type opt_outer  */
#line 3203 "sql_parser.y"
                                { (yyval.i_val) = 1 + (yyvsp[-1].i_val); }
#line 11948 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 605: /* opt_outer: %empty  */
#line 3207 "sql_parser.y"
                                { (yyval.i_val) = 0; }
#line 11954 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 606: /* opt_outer: OUTER  */
#line 3208 "sql_parser.y"
                                { (yyval.i_val) = 0; }
#line 11960 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 607: /* outer_join_type: LEFT  */
#line 3212 "sql_parser.y"
                        { (yyval.i_val) = 0; }
#line 11966 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 608: /* outer_join_type: RIGHT  */
#line 3213 "sql_parser.y"
                        { (yyval.i_val) = 1; }
#line 11972 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 609: /* outer_join_type: FULL  */
#line 3214 "sql_parser.y"
                        { (yyval.i_val) = 2; }
#line 11978 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 610: /* join_spec: ON search_condition  */
#line 3218 "sql_parser.y"
                                        { (yyval.sym) = (yyvsp[0].sym); }
#line 11984 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 611: /* join_spec: USING column_commalist_parens  */
#line 3220 "sql_parser.y"
                { (yyval.sym) = _symbol_create_list( SQL_USING, (yyvsp[0].l)); }
#line 11990 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 613: /* with_query: WITH with_list with_query_expression  */
#line 3244 "sql_parser.y"
        {
		dlist *l = L();
	  	append_list(l, (yyvsp[-1].l));
	  	append_symbol(l, (yyvsp[0].sym));
	  	(yyval.sym) = _symbol_create_list( SQL_WITH, l ); 
	}
#line 12001 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 614: /* with_list: with_list ',' with_list_element  */
#line 3253 "sql_parser.y"
                                         { (yyval.l) = append_symbol((yyvsp[-2].l), (yyvsp[0].sym)); }
#line 12007 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 615: /* with_list: with_list_element  */
#line 3254 "sql_parser.y"
                                         { (yyval.l) = append_symbol(L(), (yyvsp[0].sym)); }
#line 12013 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 616: /* with_list_element: ident opt_column_list AS subquery_with_orderby  */
#line 3259 "sql_parser.y"
        {  dlist *l = L();
	  append_list(l, append_string(L(), (yyvsp[-3].sval)));
	  append_list(l, (yyvsp[-2].l));
	  append_symbol(l, (yyvsp[0].sym));
	  append_int(l, FALSE);	/* no with check */
	  append_int(l, FALSE);	/* inlined view  (ie not persistent) */
	  append_int(l, FALSE); /* no replace clause */
	  (yyval.sym) = _symbol_create_list( SQL_CREATE_VIEW, l ); 
	}
#line 12027 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 625: /* simple_select: SELECT opt_distinct selection table_exp  */
#line 3286 "sql_parser.y"
        { (yyval.sym) = newSelectNode( SA, (yyvsp[-2].bval), (yyvsp[-1].l), NULL,
		(yyvsp[0].l)->h->data.sym,
		(yyvsp[0].l)->h->next->data.sym,
		(yyvsp[0].l)->h->next->next->data.sym,
		(yyvsp[0].l)->h->next->next->next->data.sym,
		NULL, NULL, NULL, NULL, NULL, NULL,
		(yyvsp[0].l)->h->next->next->next->next->data.sym);
	}
#line 12040 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 626: /* select_statement_single_row: SELECT opt_distinct selection INTO variable_ref_commalist table_exp  */
#line 3298 "sql_parser.y"
        { (yyval.sym) = newSelectNode( SA, (yyvsp[-4].bval), (yyvsp[-3].l), (yyvsp[-1].l),
		(yyvsp[0].l)->h->data.sym,
		(yyvsp[0].l)->h->next->data.sym,
		(yyvsp[0].l)->h->next->next->data.sym,
		(yyvsp[0].l)->h->next->next->next->data.sym,
		NULL, NULL, NULL, NULL, NULL, NULL,
		(yyvsp[0].l)->h->next->next->next->next->data.sym);
	}
#line 12053 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 627: /* select_no_parens_orderby: select_no_parens opt_order_by_clause opt_limit opt_offset opt_sample opt_seed  */
#line 3310 "sql_parser.y"
         { 
	  (yyval.sym) = (yyvsp[-5].sym);
	  if ((yyvsp[-4].sym) || (yyvsp[-3].sym) || (yyvsp[-2].sym) || (yyvsp[-1].sym) || (yyvsp[0].sym)) {
	  	if ((yyvsp[-5].sym) != NULL &&
		    ((yyvsp[-5].sym)->token == SQL_SELECT ||
		     (yyvsp[-5].sym)->token == SQL_UNION  ||
		     (yyvsp[-5].sym)->token == SQL_EXCEPT ||
		     (yyvsp[-5].sym)->token == SQL_INTERSECT)) {
			if ((yyvsp[-5].sym)->token == SQL_SELECT) {
	 			SelectNode *s = (SelectNode*)(yyvsp[-5].sym);
	
	  			s -> orderby = (yyvsp[-4].sym);
	  			s -> limit = (yyvsp[-3].sym);
	  			s -> offset = (yyvsp[-2].sym);
	  			s -> sample = (yyvsp[-1].sym);
				s -> seed = (yyvsp[0].sym);
			} else { /* Add extra select * from .. in case of UNION, EXCEPT, INTERSECT */
				(yyval.sym) = newSelectNode( 
					SA, 0, 
					append_symbol(L(), _symbol_create_list(SQL_TABLE, append_string(append_string(L(),NULL),NULL))), NULL,
					_symbol_create_list( SQL_FROM, append_symbol(L(), (yyvsp[-5].sym))), NULL, NULL, NULL, (yyvsp[-4].sym), _symbol_create_list(SQL_NAME, append_list(append_string(L(),"inner"),NULL)), (yyvsp[-3].sym), (yyvsp[-2].sym), (yyvsp[-1].sym), (yyvsp[0].sym), NULL);
			}
	  	} else {
			yyerror(m, "missing SELECT operator");
			YYABORT;
	  	}
	 } 
	}
#line 12086 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 628: /* select_no_parens: select_no_parens UNION set_distinct opt_corresponding select_no_parens  */
#line 3343 "sql_parser.y"
        { dlist *l = L();
	  append_symbol(l, (yyvsp[-4].sym));
	  append_int(l, (yyvsp[-2].bval));
	  append_list(l, (yyvsp[-1].l));
	  append_symbol(l, (yyvsp[0].sym));
	  (yyval.sym) = _symbol_create_list( SQL_UNION, l); }
#line 12097 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 629: /* select_no_parens: select_no_parens EXCEPT set_distinct opt_corresponding select_no_parens  */
#line 3352 "sql_parser.y"
        { dlist *l = L();
	  append_symbol(l, (yyvsp[-4].sym));
	  append_int(l, (yyvsp[-2].bval));
	  append_list(l, (yyvsp[-1].l));
	  append_symbol(l, (yyvsp[0].sym));
	  (yyval.sym) = _symbol_create_list( SQL_EXCEPT, l); }
#line 12108 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 630: /* select_no_parens: select_no_parens INTERSECT set_distinct opt_corresponding select_no_parens  */
#line 3361 "sql_parser.y"
        { dlist *l = L();
	  append_symbol(l, (yyvsp[-4].sym));
	  append_int(l, (yyvsp[-2].bval));
	  append_list(l, (yyvsp[-1].l));
	  append_symbol(l, (yyvsp[0].sym));
	  (yyval.sym) = _symbol_create_list( SQL_INTERSECT, l); }
#line 12119 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 631: /* select_no_parens: VALUES row_commalist  */
#line 3369 "sql_parser.y"
        { dlist *l = L();
	  append_list(l, (yyvsp[0].l));
	  (yyval.sym) = _symbol_create_list(SQL_VALUES, l); }
#line 12127 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 632: /* select_no_parens: '(' select_no_parens ')'  */
#line 3372 "sql_parser.y"
                             { (yyval.sym) = (yyvsp[-1].sym); }
#line 12133 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 634: /* set_distinct: %empty  */
#line 3377 "sql_parser.y"
                        { (yyval.bval) = TRUE; }
#line 12139 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 635: /* set_distinct: ALL  */
#line 3378 "sql_parser.y"
                        { (yyval.bval) = FALSE; }
#line 12145 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 636: /* set_distinct: DISTINCT  */
#line 3379 "sql_parser.y"
                        { (yyval.bval) = TRUE; }
#line 12151 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 637: /* opt_corresponding: %empty  */
#line 3384 "sql_parser.y"
                        { (yyval.l) = NULL; }
#line 12157 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 638: /* opt_corresponding: CORRESPONDING  */
#line 3386 "sql_parser.y"
                        { (yyval.l) = L(); }
#line 12163 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 639: /* opt_corresponding: CORRESPONDING BY '(' column_ref_commalist ')'  */
#line 3388 "sql_parser.y"
                        { (yyval.l) = (yyvsp[-1].l); }
#line 12169 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 641: /* table_exp: opt_from_clause opt_window_clause opt_where_clause opt_group_by_clause opt_having_clause  */
#line 3398 "sql_parser.y"
        { (yyval.l) = L();
	  append_symbol((yyval.l), (yyvsp[-4].sym));
	  append_symbol((yyval.l), (yyvsp[-2].sym));
	  append_symbol((yyval.l), (yyvsp[-1].sym));
	  append_symbol((yyval.l), (yyvsp[0].sym));
	  append_symbol((yyval.l), (yyvsp[-3].sym)); }
#line 12180 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 642: /* window_definition: ident AS '(' window_specification ')'  */
#line 3407 "sql_parser.y"
                                          { dlist *l = L(); append_string(l, (yyvsp[-4].sval)); append_list(l, (yyvsp[-1].l));
                                            (yyval.sym) = _symbol_create_list(SQL_NAME, l); }
#line 12187 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 643: /* window_definition_list: window_definition  */
#line 3412 "sql_parser.y"
                                                 { (yyval.l) = append_symbol(L(), (yyvsp[0].sym)); }
#line 12193 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 644: /* window_definition_list: window_definition_list ',' window_definition  */
#line 3413 "sql_parser.y"
                                                 { (yyval.l) = append_symbol((yyvsp[-2].l), (yyvsp[0].sym)); }
#line 12199 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 645: /* opt_window_clause: %empty  */
#line 3417 "sql_parser.y"
                                  { (yyval.sym) = NULL; }
#line 12205 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 646: /* opt_window_clause: WINDOW window_definition_list  */
#line 3418 "sql_parser.y"
                                  { (yyval.sym) = _symbol_create_list( SQL_WINDOW, (yyvsp[0].l)); }
#line 12211 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 647: /* opt_from_clause: %empty  */
#line 3422 "sql_parser.y"
                                 { (yyval.sym) = NULL; }
#line 12217 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 648: /* opt_from_clause: FROM table_ref_commalist  */
#line 3423 "sql_parser.y"
                                 { (yyval.sym) = _symbol_create_list( SQL_FROM, (yyvsp[0].l)); }
#line 12223 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 649: /* table_ref_commalist: table_ref  */
#line 3427 "sql_parser.y"
                        { (yyval.l) = append_symbol(L(), (yyvsp[0].sym)); }
#line 12229 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 650: /* table_ref_commalist: table_ref_commalist ',' table_ref  */
#line 3429 "sql_parser.y"
                        { (yyval.l) = append_symbol((yyvsp[-2].l), (yyvsp[0].sym)); }
#line 12235 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 651: /* table_ref: qname opt_table_name  */
#line 3433 "sql_parser.y"
                                { dlist *l = L();
		  		  append_list(l, (yyvsp[-1].l));
		  	  	  append_int(l, 0);
		  	  	  append_symbol(l, (yyvsp[0].sym));
		  		  (yyval.sym) = _symbol_create_list(SQL_NAME, l); }
#line 12245 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 652: /* table_ref: func_ref opt_table_name  */
#line 3439 "sql_parser.y"
                                { dlist *l = L();
		  		  append_symbol(l, (yyvsp[-1].sym));
		  	  	  append_int(l, 0);
		  	  	  append_symbol(l, (yyvsp[0].sym));
		  		  (yyval.sym) = _symbol_create_list(SQL_TABLE, l); }
#line 12255 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 653: /* table_ref: LATERAL func_ref opt_table_name  */
#line 3445 "sql_parser.y"
                                { dlist *l = L();
		  		  append_symbol(l, (yyvsp[-1].sym));
		  	  	  append_int(l, 1);
		  	  	  append_symbol(l, (yyvsp[0].sym));
		  		  (yyval.sym) = _symbol_create_list(SQL_TABLE, l); }
#line 12265 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 654: /* table_ref: subquery_with_orderby table_name  */
#line 3451 "sql_parser.y"
                                {
				  (yyval.sym) = (yyvsp[-1].sym);
				  if ((yyval.sym)->token == SQL_SELECT) {
				  	SelectNode *sn = (SelectNode*)(yyvsp[-1].sym);
				  	sn->name = (yyvsp[0].sym);
				  } else {
	  				append_int((yyvsp[0].sym)->data.lval, 0);
				  	append_symbol((yyvsp[-1].sym)->data.lval, (yyvsp[0].sym));
				  }
				}
#line 12280 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 655: /* table_ref: LATERAL subquery table_name  */
#line 3462 "sql_parser.y"
                                {
				  (yyval.sym) = (yyvsp[-1].sym);
				  if ((yyval.sym)->token == SQL_SELECT) {
				  	SelectNode *sn = (SelectNode*)(yyvsp[-1].sym);
				  	sn->name = (yyvsp[0].sym);
					sn->lateral = 1;
				  } else {
	  				append_int((yyvsp[-1].sym)->data.lval, 1);
				  	append_symbol((yyvsp[-1].sym)->data.lval, (yyvsp[0].sym));
				  }
				}
#line 12296 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 656: /* table_ref: subquery_with_orderby  */
#line 3474 "sql_parser.y"
                                { (yyval.sym) = NULL;
				  yyerror(m, "subquery table reference needs alias, use AS xxx");
				  YYABORT;
				}
#line 12305 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 657: /* table_ref: joined_table  */
#line 3478 "sql_parser.y"
                                { (yyval.sym) = (yyvsp[0].sym);
				  append_symbol((yyvsp[0].sym)->data.lval, NULL); }
#line 12312 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 658: /* table_name: AS ident '(' ident_commalist ')'  */
#line 3484 "sql_parser.y"
                                { dlist *l = L();
		  		  append_string(l, (yyvsp[-3].sval));
		  	  	  append_list(l, (yyvsp[-1].l));
		  		  (yyval.sym) = _symbol_create_list(SQL_NAME, l); }
#line 12321 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 659: /* table_name: AS ident  */
#line 3489 "sql_parser.y"
                                { dlist *l = L();
		  		  append_string(l, (yyvsp[0].sval));
		  	  	  append_list(l, NULL);
		  		  (yyval.sym) = _symbol_create_list(SQL_NAME, l); }
#line 12330 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 660: /* table_name: ident '(' ident_commalist ')'  */
#line 3494 "sql_parser.y"
                                { dlist *l = L();
		  		  append_string(l, (yyvsp[-3].sval));
		  	  	  append_list(l, (yyvsp[-1].l));
		  		  (yyval.sym) = _symbol_create_list(SQL_NAME, l); }
#line 12339 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 661: /* table_name: ident  */
#line 3499 "sql_parser.y"
                                { dlist *l = L();
		  		  append_string(l, (yyvsp[0].sval));
		  	  	  append_list(l, NULL);
		  		  (yyval.sym) = _symbol_create_list(SQL_NAME, l); }
#line 12348 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 662: /* opt_table_name: %empty  */
#line 3506 "sql_parser.y"
                    { (yyval.sym) = NULL; }
#line 12354 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 663: /* opt_table_name: table_name  */
#line 3507 "sql_parser.y"
                { (yyval.sym) = (yyvsp[0].sym); }
#line 12360 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 664: /* opt_group_by_clause: %empty  */
#line 3511 "sql_parser.y"
                                  { (yyval.sym) = NULL; }
#line 12366 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 665: /* opt_group_by_clause: sqlGROUP BY group_by_list  */
#line 3512 "sql_parser.y"
                              { (yyval.sym) = _symbol_create_list(SQL_GROUPBY, (yyvsp[0].l)); }
#line 12372 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 666: /* group_by_list: group_by_element  */
#line 3516 "sql_parser.y"
                                           { (yyval.l) = append_symbol(L(), (yyvsp[0].sym)); }
#line 12378 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 667: /* group_by_list: group_by_list ',' group_by_element  */
#line 3517 "sql_parser.y"
                                       { (yyval.l) = append_symbol((yyvsp[-2].l), (yyvsp[0].sym)); }
#line 12384 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 668: /* group_by_element: search_condition  */
#line 3521 "sql_parser.y"
                                            { (yyval.sym) = _symbol_create_list(SQL_GROUPBY, append_symbol(L(), (yyvsp[0].sym))); }
#line 12390 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 669: /* group_by_element: ROLLUP '(' ordinary_grouping_set ')'  */
#line 3522 "sql_parser.y"
                                            { (yyval.sym) = _symbol_create_list(SQL_ROLLUP, (yyvsp[-1].l)); }
#line 12396 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 670: /* group_by_element: CUBE '(' ordinary_grouping_set ')'  */
#line 3523 "sql_parser.y"
                                            { (yyval.sym) = _symbol_create_list(SQL_CUBE, (yyvsp[-1].l)); }
#line 12402 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 671: /* group_by_element: GROUPING SETS '(' grouping_set_list ')'  */
#line 3524 "sql_parser.y"
                                            { (yyval.sym) = _symbol_create_list(SQL_GROUPING_SETS, (yyvsp[-1].l)); }
#line 12408 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 672: /* group_by_element: '(' ')'  */
#line 3525 "sql_parser.y"
                                            { (yyval.sym) = _symbol_create_list(SQL_GROUPBY, NULL); }
#line 12414 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 673: /* ordinary_grouping_set: ordinary_grouping_element  */
#line 3529 "sql_parser.y"
                                                        { (yyval.l) = append_symbol(L(), (yyvsp[0].sym)); }
#line 12420 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 674: /* ordinary_grouping_set: ordinary_grouping_set ',' ordinary_grouping_element  */
#line 3530 "sql_parser.y"
                                                        { (yyval.l) = append_symbol((yyvsp[-2].l), (yyvsp[0].sym)); }
#line 12426 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 675: /* ordinary_grouping_element: '(' column_ref_commalist ')'  */
#line 3534 "sql_parser.y"
                                 { (yyval.sym) = _symbol_create_list(SQL_COLUMN_GROUP, (yyvsp[-1].l)); }
#line 12432 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 676: /* ordinary_grouping_element: column_ref  */
#line 3535 "sql_parser.y"
                                 { (yyval.sym) = _symbol_create_list(SQL_COLUMN, (yyvsp[0].l)); }
#line 12438 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 677: /* column_ref_commalist: column_ref  */
#line 3539 "sql_parser.y"
                                            { (yyval.l) = append_symbol(L(), _symbol_create_list(SQL_COLUMN,(yyvsp[0].l))); }
#line 12444 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 678: /* column_ref_commalist: column_ref_commalist ',' column_ref  */
#line 3540 "sql_parser.y"
                                        { (yyval.l) = append_symbol((yyvsp[-2].l), _symbol_create_list(SQL_COLUMN,(yyvsp[0].l))); }
#line 12450 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 679: /* grouping_set_list: grouping_set_element  */
#line 3544 "sql_parser.y"
                                                   { (yyval.l) = append_symbol(L(), (yyvsp[0].sym)); }
#line 12456 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 680: /* grouping_set_list: grouping_set_list ',' grouping_set_element  */
#line 3545 "sql_parser.y"
                                               { (yyval.l) = append_symbol((yyvsp[-2].l), (yyvsp[0].sym)); }
#line 12462 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 681: /* grouping_set_element: ordinary_grouping_element  */
#line 3549 "sql_parser.y"
                                            { (yyval.sym) = _symbol_create_list(SQL_GROUPBY, append_symbol(L(), (yyvsp[0].sym))); }
#line 12468 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 682: /* grouping_set_element: ROLLUP '(' ordinary_grouping_set ')'  */
#line 3550 "sql_parser.y"
                                            { (yyval.sym) = _symbol_create_list(SQL_ROLLUP, (yyvsp[-1].l)); }
#line 12474 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 683: /* grouping_set_element: CUBE '(' ordinary_grouping_set ')'  */
#line 3551 "sql_parser.y"
                                            { (yyval.sym) = _symbol_create_list(SQL_CUBE, (yyvsp[-1].l)); }
#line 12480 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 684: /* grouping_set_element: GROUPING SETS '(' grouping_set_list ')'  */
#line 3552 "sql_parser.y"
                                            { (yyval.sym) = _symbol_create_list(SQL_GROUPING_SETS, (yyvsp[-1].l)); }
#line 12486 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 685: /* grouping_set_element: '(' ')'  */
#line 3553 "sql_parser.y"
                                            { (yyval.sym) = _symbol_create_list(SQL_GROUPBY, NULL); }
#line 12492 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 686: /* opt_having_clause: %empty  */
#line 3557 "sql_parser.y"
                            { (yyval.sym) = NULL; }
#line 12498 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 687: /* opt_having_clause: HAVING search_condition  */
#line 3558 "sql_parser.y"
                            { (yyval.sym) = (yyvsp[0].sym); }
#line 12504 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 688: /* search_condition: search_condition OR and_exp  */
#line 3563 "sql_parser.y"
                { dlist *l = L();
		  append_symbol(l, (yyvsp[-2].sym));
		  append_symbol(l, (yyvsp[0].sym));
		  (yyval.sym) = _symbol_create_list(SQL_OR, l ); }
#line 12513 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 689: /* search_condition: and_exp  */
#line 3567 "sql_parser.y"
                { (yyval.sym) = (yyvsp[0].sym); }
#line 12519 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 690: /* and_exp: and_exp AND pred_exp  */
#line 3572 "sql_parser.y"
                { dlist *l = L();
		  append_symbol(l, (yyvsp[-2].sym));
		  append_symbol(l, (yyvsp[0].sym));
		  (yyval.sym) = _symbol_create_list(SQL_AND, l ); }
#line 12528 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 691: /* and_exp: pred_exp  */
#line 3576 "sql_parser.y"
                { (yyval.sym) = (yyvsp[0].sym); }
#line 12534 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 692: /* opt_order_by_clause: %empty  */
#line 3580 "sql_parser.y"
                                          { (yyval.sym) = NULL; }
#line 12540 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 693: /* opt_order_by_clause: ORDER BY sort_specification_list  */
#line 3582 "sql_parser.y"
                { (yyval.sym) = _symbol_create_list( SQL_ORDERBY, (yyvsp[0].l)); }
#line 12546 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 694: /* opt_limit: %empty  */
#line 3586 "sql_parser.y"
                        { (yyval.sym) = NULL; }
#line 12552 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 695: /* opt_limit: LIMIT nonzerolng  */
#line 3587 "sql_parser.y"
                        { 
		  	  sql_subtype *t = sql_bind_localtype("lng");
			  (yyval.sym) = _newAtomNode( atom_int(SA, t, (yyvsp[0].l_val))); 
			}
#line 12561 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 696: /* opt_limit: LIMIT param  */
#line 3591 "sql_parser.y"
                        { (yyval.sym) = (yyvsp[0].sym); }
#line 12567 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 697: /* opt_offset: %empty  */
#line 3595 "sql_parser.y"
                        { (yyval.sym) = NULL; }
#line 12573 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 698: /* opt_offset: OFFSET poslng  */
#line 3596 "sql_parser.y"
                        { 
		  	  sql_subtype *t = sql_bind_localtype("lng");
			  (yyval.sym) = _newAtomNode( atom_int(SA, t, (yyvsp[0].l_val))); 
			}
#line 12582 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 699: /* opt_offset: OFFSET param  */
#line 3600 "sql_parser.y"
                        { (yyval.sym) = (yyvsp[0].sym); }
#line 12588 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 700: /* opt_sample: %empty  */
#line 3604 "sql_parser.y"
                        { (yyval.sym) = NULL; }
#line 12594 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 701: /* opt_sample: SAMPLE poslng  */
#line 3605 "sql_parser.y"
                        { 
		  	  sql_subtype *t = sql_bind_localtype("lng");
			  (yyval.sym) = _newAtomNode( atom_int(SA, t, (yyvsp[0].l_val))); 
			}
#line 12603 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 702: /* opt_sample: SAMPLE INTNUM  */
#line 3609 "sql_parser.y"
                        { 
		  	  sql_subtype *t = sql_bind_localtype("dbl");
			  (yyval.sym) = _newAtomNode( atom_float(SA, t, strtod((yyvsp[0].sval), NULL)));
			}
#line 12612 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 703: /* opt_sample: SAMPLE param  */
#line 3613 "sql_parser.y"
                        { (yyval.sym) = (yyvsp[0].sym); }
#line 12618 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 704: /* opt_seed: %empty  */
#line 3617 "sql_parser.y"
                        { (yyval.sym) = NULL; }
#line 12624 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 705: /* opt_seed: SEED intval  */
#line 3618 "sql_parser.y"
                { 
		  	  sql_subtype *t = sql_bind_localtype("int");
			  (yyval.sym) = _newAtomNode( atom_int(SA, t, (yyvsp[0].i_val))); 
			}
#line 12633 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 706: /* opt_seed: SEED param  */
#line 3622 "sql_parser.y"
                { (yyval.sym) = (yyvsp[0].sym); }
#line 12639 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 707: /* sort_specification_list: ordering_spec  */
#line 3626 "sql_parser.y"
                         { (yyval.l) = append_symbol(L(), (yyvsp[0].sym)); }
#line 12645 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 708: /* sort_specification_list: sort_specification_list ',' ordering_spec  */
#line 3628 "sql_parser.y"
                         { (yyval.l) = append_symbol( (yyvsp[-2].l), (yyvsp[0].sym) ); }
#line 12651 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 709: /* ordering_spec: search_condition opt_asc_desc opt_nulls_first_last  */
#line 3633 "sql_parser.y"
        { dlist *l = L();
	  append_symbol(l, (yyvsp[-2].sym));
	  append_int(l, (yyvsp[-1].bval) | (((yyvsp[0].bval) == -1 ? !(yyvsp[-1].bval) : (yyvsp[0].bval)) << 1));
	  (yyval.sym) = _symbol_create_list(SQL_COLUMN, l ); }
#line 12660 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 710: /* opt_asc_desc: %empty  */
#line 3640 "sql_parser.y"
                { (yyval.bval) = TRUE; }
#line 12666 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 711: /* opt_asc_desc: ASC  */
#line 3641 "sql_parser.y"
                        { (yyval.bval) = TRUE; }
#line 12672 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 712: /* opt_asc_desc: DESC  */
#line 3642 "sql_parser.y"
                        { (yyval.bval) = FALSE; }
#line 12678 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 713: /* opt_nulls_first_last: %empty  */
#line 3646 "sql_parser.y"
                        { (yyval.bval) = -1; }
#line 12684 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 714: /* opt_nulls_first_last: NULLS LAST  */
#line 3647 "sql_parser.y"
                        { (yyval.bval) = TRUE; }
#line 12690 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 715: /* opt_nulls_first_last: NULLS FIRST  */
#line 3648 "sql_parser.y"
                        { (yyval.bval) = FALSE; }
#line 12696 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 724: /* pred_exp: NOT pred_exp  */
#line 3663 "sql_parser.y"
                 { (yyval.sym) = _symbol_create_symbol(SQL_NOT, (yyvsp[0].sym)); }
#line 12702 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 725: /* pred_exp: predicate  */
#line 3664 "sql_parser.y"
                 { (yyval.sym) = (yyvsp[0].sym); }
#line 12708 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 726: /* any_all_some: ANY  */
#line 3668 "sql_parser.y"
                { (yyval.i_val) = 0; }
#line 12714 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 727: /* any_all_some: SOME  */
#line 3669 "sql_parser.y"
                { (yyval.i_val) = 0; }
#line 12720 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 728: /* any_all_some: ALL  */
#line 3670 "sql_parser.y"
                { (yyval.i_val) = 1; }
#line 12726 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 729: /* comparison_predicate: pred_exp COMPARISON pred_exp  */
#line 3675 "sql_parser.y"
                { dlist *l = L();

		  append_symbol(l, (yyvsp[-2].sym));
		  append_string(l, (yyvsp[-1].sval));
		  append_symbol(l, (yyvsp[0].sym));
		  (yyval.sym) = _symbol_create_list(SQL_COMPARE, l ); }
#line 12737 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 730: /* comparison_predicate: pred_exp '=' pred_exp  */
#line 3682 "sql_parser.y"
                { dlist *l = L();

		  append_symbol(l, (yyvsp[-2].sym));
		  append_string(l, sa_strdup(SA, "="));
		  append_symbol(l, (yyvsp[0].sym));
		  (yyval.sym) = _symbol_create_list(SQL_COMPARE, l ); }
#line 12748 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 731: /* comparison_predicate: pred_exp COMPARISON any_all_some '(' value ')'  */
#line 3689 "sql_parser.y"
                { dlist *l = L();

		  append_symbol(l, (yyvsp[-5].sym));
		  append_string(l, (yyvsp[-4].sval));
		  append_symbol(l, (yyvsp[-1].sym));
		  append_int(l, (yyvsp[-3].i_val));
		  (yyval.sym) = _symbol_create_list(SQL_COMPARE, l ); }
#line 12760 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 732: /* comparison_predicate: pred_exp '=' any_all_some '(' value ')'  */
#line 3697 "sql_parser.y"
                { dlist *l = L();

		  append_symbol(l, (yyvsp[-5].sym));
		  append_string(l, sa_strdup(SA, "="));
		  append_symbol(l, (yyvsp[-1].sym));
		  append_int(l, (yyvsp[-3].i_val));
		  (yyval.sym) = _symbol_create_list(SQL_COMPARE, l ); }
#line 12772 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 733: /* between_predicate: pred_exp NOT_BETWEEN opt_bounds pred_exp AND pred_exp  */
#line 3708 "sql_parser.y"
                { dlist *l = L();
		  append_symbol(l, (yyvsp[-5].sym));
		  append_int(l, (yyvsp[-3].i_val));
		  append_symbol(l, (yyvsp[-2].sym));
		  append_symbol(l, (yyvsp[0].sym));
		  (yyval.sym) = _symbol_create_list(SQL_NOT_BETWEEN, l ); }
#line 12783 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 734: /* between_predicate: pred_exp BETWEEN opt_bounds pred_exp AND pred_exp  */
#line 3715 "sql_parser.y"
                { dlist *l = L();
		  append_symbol(l, (yyvsp[-5].sym));
		  append_int(l, (yyvsp[-3].i_val));
		  append_symbol(l, (yyvsp[-2].sym));
		  append_symbol(l, (yyvsp[0].sym));
		  (yyval.sym) = _symbol_create_list(SQL_BETWEEN, l ); }
#line 12794 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 735: /* opt_bounds: %empty  */
#line 3724 "sql_parser.y"
                { (yyval.i_val) = 0; }
#line 12800 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 736: /* opt_bounds: ASYMMETRIC  */
#line 3725 "sql_parser.y"
                { (yyval.i_val) = 0; }
#line 12806 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 737: /* opt_bounds: SYMMETRIC  */
#line 3726 "sql_parser.y"
                { (yyval.i_val) = 1; }
#line 12812 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 738: /* like_predicate: pred_exp NOT_LIKE like_exp  */
#line 3731 "sql_parser.y"
                { dlist *l = L();
		  append_symbol(l, (yyvsp[-2].sym));
		  append_symbol(l, (yyvsp[0].sym));
		  append_int(l, FALSE);  /* case sensitive */
		  append_int(l, TRUE);  /* anti */
		  (yyval.sym) = _symbol_create_list( SQL_LIKE, l ); }
#line 12823 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 739: /* like_predicate: pred_exp NOT_ILIKE like_exp  */
#line 3738 "sql_parser.y"
                { dlist *l = L();
		  append_symbol(l, (yyvsp[-2].sym));
		  append_symbol(l, (yyvsp[0].sym));
		  append_int(l, TRUE);  /* case insensitive */
		  append_int(l, TRUE);  /* anti */
		  (yyval.sym) = _symbol_create_list( SQL_LIKE, l ); }
#line 12834 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 740: /* like_predicate: pred_exp LIKE like_exp  */
#line 3745 "sql_parser.y"
                { dlist *l = L();
		  append_symbol(l, (yyvsp[-2].sym));
		  append_symbol(l, (yyvsp[0].sym));
		  append_int(l, FALSE);  /* case sensitive */
		  append_int(l, FALSE);  /* anti */
		  (yyval.sym) = _symbol_create_list( SQL_LIKE, l ); }
#line 12845 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 741: /* like_predicate: pred_exp ILIKE like_exp  */
#line 3752 "sql_parser.y"
                { dlist *l = L();
		  append_symbol(l, (yyvsp[-2].sym));
		  append_symbol(l, (yyvsp[0].sym));
		  append_int(l, TRUE);  /* case insensitive */
		  append_int(l, FALSE);  /* anti */
		  (yyval.sym) = _symbol_create_list( SQL_LIKE, l ); }
#line 12856 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 742: /* like_exp: scalar_exp  */
#line 3762 "sql_parser.y"
        { dlist *l = L();
	  append_symbol(l, (yyvsp[0].sym));
	  (yyval.sym) = _symbol_create_list(SQL_ESCAPE, l ); }
#line 12864 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 743: /* like_exp: scalar_exp ESCAPE string  */
#line 3766 "sql_parser.y"
        { const char *s = (yyvsp[0].sval);
	  if (_strlen(s) != 1) {
		sqlformaterror(m, SQLSTATE(22019) "%s", "ESCAPE must be one character");
		(yyval.sym) = NULL;
		YYABORT;
	  } else {
		dlist *l = L();
		append_symbol(l, (yyvsp[-2].sym));
		append_string(l, s);
		(yyval.sym) = _symbol_create_list(SQL_ESCAPE, l);
	  }
	}
#line 12881 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 744: /* test_for_null: pred_exp IS NOT sqlNULL  */
#line 3781 "sql_parser.y"
                            { (yyval.sym) = _symbol_create_symbol( SQL_IS_NOT_NULL, (yyvsp[-3].sym) );}
#line 12887 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 745: /* test_for_null: pred_exp IS sqlNULL  */
#line 3782 "sql_parser.y"
                            { (yyval.sym) = _symbol_create_symbol( SQL_IS_NULL, (yyvsp[-2].sym) ); }
#line 12893 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 746: /* in_predicate: pred_exp NOT_IN '(' value_commalist ')'  */
#line 3787 "sql_parser.y"
                { dlist *l = L();

		  append_symbol(l, (yyvsp[-4].sym));
		  append_list(l, (yyvsp[-1].l));
		  (yyval.sym) = _symbol_create_list(SQL_NOT_IN, l ); }
#line 12903 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 747: /* in_predicate: pred_exp sqlIN '(' value_commalist ')'  */
#line 3793 "sql_parser.y"
                { dlist *l = L();

		  append_symbol(l, (yyvsp[-4].sym));
		  append_list(l, (yyvsp[-1].l));
		  (yyval.sym) = _symbol_create_list(SQL_IN, l ); }
#line 12913 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 748: /* in_predicate: '(' pred_exp_list ')' NOT_IN '(' value_commalist ')'  */
#line 3799 "sql_parser.y"
                { dlist *l = L();
		  append_list(l, (yyvsp[-5].l));
		  append_list(l, (yyvsp[-1].l));
		  (yyval.sym) = _symbol_create_list(SQL_NOT_IN, l ); }
#line 12922 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 749: /* in_predicate: '(' pred_exp_list ')' sqlIN '(' value_commalist ')'  */
#line 3804 "sql_parser.y"
                { dlist *l = L();
		  append_list(l, (yyvsp[-5].l));
		  append_list(l, (yyvsp[-1].l));
		  (yyval.sym) = _symbol_create_list(SQL_IN, l ); }
#line 12931 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 750: /* pred_exp_list: pred_exp  */
#line 3812 "sql_parser.y"
                        { (yyval.l) = append_symbol( L(), (yyvsp[0].sym));}
#line 12937 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 751: /* pred_exp_list: pred_exp_list ',' pred_exp  */
#line 3814 "sql_parser.y"
                        { (yyval.l) = append_symbol( (yyvsp[-2].l), (yyvsp[0].sym)); }
#line 12943 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 752: /* existence_test: EXISTS subquery  */
#line 3820 "sql_parser.y"
                        { (yyval.sym) = _symbol_create_symbol( SQL_EXISTS, (yyvsp[0].sym) ); }
#line 12949 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 753: /* existence_test: NOT_EXISTS subquery  */
#line 3821 "sql_parser.y"
                                { (yyval.sym) = _symbol_create_symbol( SQL_NOT_EXISTS, (yyvsp[0].sym) ); }
#line 12955 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 754: /* filter_arg_list: pred_exp  */
#line 3825 "sql_parser.y"
                                        { (yyval.l) = append_symbol(L(), (yyvsp[0].sym)); }
#line 12961 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 755: /* filter_arg_list: filter_arg_list ',' pred_exp  */
#line 3826 "sql_parser.y"
                                        { (yyval.l) = append_symbol((yyvsp[-2].l), (yyvsp[0].sym));  }
#line 12967 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 756: /* filter_args: '[' filter_arg_list ']'  */
#line 3830 "sql_parser.y"
                                        { (yyval.l) = (yyvsp[-1].l); }
#line 12973 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 757: /* filter_exp: filter_args qname filter_args  */
#line 3835 "sql_parser.y"
                { dlist *l = L();
		  append_list(l, (yyvsp[-2].l));
		  append_list(l, (yyvsp[-1].l));
		  append_list(l, (yyvsp[0].l));
		  (yyval.sym) = _symbol_create_list(SQL_FILTER, l ); }
#line 12983 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 758: /* subquery_with_orderby: '(' select_no_parens_orderby ')'  */
#line 3843 "sql_parser.y"
                                        { (yyval.sym) = (yyvsp[-1].sym); }
#line 12989 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 759: /* subquery_with_orderby: '(' with_query ')'  */
#line 3844 "sql_parser.y"
                                        { (yyval.sym) = (yyvsp[-1].sym); }
#line 12995 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 760: /* subquery: '(' select_no_parens ')'  */
#line 3848 "sql_parser.y"
                                { (yyval.sym) = (yyvsp[-1].sym); }
#line 13001 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 761: /* subquery: '(' with_query ')'  */
#line 3849 "sql_parser.y"
                                { (yyval.sym) = (yyvsp[-1].sym); }
#line 13007 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 763: /* simple_scalar_exp: scalar_exp '+' scalar_exp  */
#line 3856 "sql_parser.y"
                        { dlist *l = L();
			  append_list(l, 
			  	append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "sql_add")));
	  		  append_int(l, FALSE); /* ignore distinct */
			  append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 13019 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 764: /* simple_scalar_exp: scalar_exp '-' scalar_exp  */
#line 3864 "sql_parser.y"
                        { dlist *l = L();
			  append_list(l, 
			  	append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "sql_sub")));
	  		  append_int(l, FALSE); /* ignore distinct */
			  append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 13031 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 765: /* simple_scalar_exp: scalar_exp '*' scalar_exp  */
#line 3872 "sql_parser.y"
                        { dlist *l = L();
			  append_list(l, 
			  	append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "sql_mul")));
				  append_int(l, FALSE); /* ignore distinct */
	  		  append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 13043 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 766: /* simple_scalar_exp: scalar_exp '/' scalar_exp  */
#line 3880 "sql_parser.y"
                        { dlist *l = L();
			  append_list(l, 
			  	append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "sql_div")));
				  append_int(l, FALSE); /* ignore distinct */
	  		  append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 13055 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 767: /* simple_scalar_exp: scalar_exp '%' scalar_exp  */
#line 3888 "sql_parser.y"
                        { dlist *l = L();
			  append_list(l, 
			  	append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "mod")));
				  append_int(l, FALSE); /* ignore distinct */
	  		  append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 13067 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 768: /* simple_scalar_exp: scalar_exp '^' scalar_exp  */
#line 3896 "sql_parser.y"
                        { dlist *l = L();
			  append_list(l, 
			  	append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "bit_xor")));
				  append_int(l, FALSE); /* ignore distinct */
	  		  append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 13079 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 769: /* simple_scalar_exp: scalar_exp '&' scalar_exp  */
#line 3904 "sql_parser.y"
                        { dlist *l = L();
			  append_list(l, 
			  	append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "bit_and")));
				  append_int(l, FALSE); /* ignore distinct */
	  		  append_symbol(l, (yyvsp[-2].sym));
			  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 13091 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 770: /* simple_scalar_exp: scalar_exp GEOM_OVERLAP scalar_exp  */
#line 3912 "sql_parser.y"
                        { dlist *l = L();
			  append_list(l, 
			  	append_string(L(), sa_strdup(SA, "mbr_overlap")));
				  append_int(l, FALSE); /* ignore distinct */
	  		  append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 13103 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 771: /* simple_scalar_exp: scalar_exp GEOM_OVERLAP_OR_LEFT scalar_exp  */
#line 3920 "sql_parser.y"
                        { dlist *l = L();
			  append_list(l, 
			  	append_string(L(), sa_strdup(SA, "mbr_overlap_or_left")));
				  append_int(l, FALSE); /* ignore distinct */
	  		  append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 13115 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 772: /* simple_scalar_exp: scalar_exp GEOM_OVERLAP_OR_RIGHT scalar_exp  */
#line 3928 "sql_parser.y"
                        { dlist *l = L();
			  append_list(l, 
			  	append_string(L(), sa_strdup(SA, "mbr_overlap_or_right")));
				  append_int(l, FALSE); /* ignore distinct */
	  		  append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 13127 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 773: /* simple_scalar_exp: scalar_exp GEOM_OVERLAP_OR_BELOW scalar_exp  */
#line 3936 "sql_parser.y"
                        { dlist *l = L();
			  append_list(l, 
			  	append_string(L(), sa_strdup(SA, "mbr_overlap_or_below")));
				  append_int(l, FALSE); /* ignore distinct */
	  		  append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 13139 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 774: /* simple_scalar_exp: scalar_exp GEOM_BELOW scalar_exp  */
#line 3944 "sql_parser.y"
                        { dlist *l = L();
			  append_list(l, append_string(L(), sa_strdup(SA, "mbr_below")));
			  append_int(l, FALSE); /* ignore distinct */
	  		  append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 13150 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 775: /* simple_scalar_exp: scalar_exp GEOM_OVERLAP_OR_ABOVE scalar_exp  */
#line 3951 "sql_parser.y"
                        { dlist *l = L();
			  append_list(l, 
			  	append_string(L(), sa_strdup(SA, "mbr_overlap_or_above")));
				  append_int(l, FALSE); /* ignore distinct */
	  		  append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 13162 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 776: /* simple_scalar_exp: scalar_exp GEOM_ABOVE scalar_exp  */
#line 3959 "sql_parser.y"
                        { dlist *l = L();
			  append_list(l, 
			  	append_string(L(), sa_strdup(SA, "mbr_above")));
				  append_int(l, FALSE); /* ignore distinct */
	  		  append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 13174 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 777: /* simple_scalar_exp: scalar_exp GEOM_DIST scalar_exp  */
#line 3967 "sql_parser.y"
                        { dlist *l = L();
			  append_list(l, 
			  	append_string(L(), sa_strdup(SA, "mbr_distance")));
				  append_int(l, FALSE); /* ignore distinct */
	  		  append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 13186 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 778: /* simple_scalar_exp: scalar_exp AT scalar_exp  */
#line 3975 "sql_parser.y"
                        { dlist *l = L();
			  append_list(l, 
			  	append_string(L(), sa_strdup(SA, "mbr_contained")));
				  append_int(l, FALSE); /* ignore distinct */
	  		  append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 13198 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 779: /* simple_scalar_exp: scalar_exp '|' scalar_exp  */
#line 3983 "sql_parser.y"
                        { dlist *l = L();
			  append_list(l, 
			  	append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "bit_or")));
				  append_int(l, FALSE); /* ignore distinct */
	  		  append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 13210 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 780: /* simple_scalar_exp: scalar_exp '~' scalar_exp  */
#line 3991 "sql_parser.y"
                        { dlist *l = L();
			  append_list(l, 
			  	append_string(L(), sa_strdup(SA, "mbr_contains")));
				  append_int(l, FALSE); /* ignore distinct */
	  		  append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 13222 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 781: /* simple_scalar_exp: scalar_exp GEOM_MBR_EQUAL scalar_exp  */
#line 3999 "sql_parser.y"
                        { dlist *l = L();
			  append_list(l, 
			  	append_string(L(), sa_strdup(SA, "mbr_equal")));
				  append_int(l, FALSE); /* ignore distinct */
	  		  append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 13234 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 782: /* simple_scalar_exp: '~' scalar_exp  */
#line 4007 "sql_parser.y"
                        { dlist *l = L();
			  append_list(l, 
			  	append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "bit_not")));
	  		  append_int(l, FALSE); /* ignore distinct */
			  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_UNOP, l ); }
#line 13245 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 783: /* simple_scalar_exp: scalar_exp LEFT_SHIFT scalar_exp  */
#line 4014 "sql_parser.y"
                        { dlist *l = L();
			  append_list(l, 
			  	append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "left_shift")));
			  	append_int(l, FALSE); /* ignore distinct */
				append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 13257 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 784: /* simple_scalar_exp: scalar_exp RIGHT_SHIFT scalar_exp  */
#line 4022 "sql_parser.y"
                        { dlist *l = L();
			  append_list(l, 
			  	append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "right_shift")));
	  		   append_int(l, FALSE); /* ignore distinct */
			   append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 13269 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 785: /* simple_scalar_exp: scalar_exp LEFT_SHIFT_ASSIGN scalar_exp  */
#line 4030 "sql_parser.y"
                        { dlist *l = L();
			  append_list(l, 
			  	append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "left_shift_assign")));
				  append_int(l, FALSE); /* ignore distinct */
	  		  append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 13281 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 786: /* simple_scalar_exp: scalar_exp RIGHT_SHIFT_ASSIGN scalar_exp  */
#line 4038 "sql_parser.y"
                        { dlist *l = L();
			  append_list(l, 
			  	append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "right_shift_assign")));
				  append_int(l, FALSE); /* ignore distinct */
	  		  append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 13293 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 787: /* simple_scalar_exp: '+' scalar_exp  */
#line 4046 "sql_parser.y"
                        { (yyval.sym) = (yyvsp[0].sym); }
#line 13299 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 788: /* simple_scalar_exp: '-' scalar_exp  */
#line 4048 "sql_parser.y"
                        { 
 			  (yyval.sym) = NULL;
			  assert(((yyvsp[0].sym)->token != SQL_COLUMN && (yyvsp[0].sym)->token != SQL_IDENT) || (yyvsp[0].sym)->data.lval->h->type != type_lng);
			  if (!(yyval.sym)) {
				dlist *l = L();
			  	append_list(l, 
			  		append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "sql_neg")));
	  		  	append_int(l, FALSE); /* ignore distinct */
				append_symbol(l, (yyvsp[0].sym));
	  		  	(yyval.sym) = _symbol_create_list( SQL_UNOP, l ); 
			  }
			}
#line 13316 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 789: /* simple_scalar_exp: '(' search_condition ')'  */
#line 4060 "sql_parser.y"
                                { (yyval.sym) = (yyvsp[-1].sym); }
#line 13322 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 790: /* scalar_exp: simple_scalar_exp  */
#line 4064 "sql_parser.y"
                        { (yyval.sym) = (yyvsp[0].sym); }
#line 13328 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 792: /* opt_over: OVER '(' window_specification ')'  */
#line 4069 "sql_parser.y"
                                          { (yyval.sym) = _symbol_create_list(SQL_WINDOW, append_list(L(), (yyvsp[-1].l))); }
#line 13334 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 793: /* opt_over: OVER ident  */
#line 4070 "sql_parser.y"
                                      { (yyval.sym) = _symbol_create_list(SQL_NAME, append_string(L(), (yyvsp[0].sval))); }
#line 13340 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 794: /* opt_over: %empty  */
#line 4071 "sql_parser.y"
                                      { (yyval.sym) = NULL; }
#line 13346 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 796: /* value_exp: aggr_or_window_ref opt_over  */
#line 4076 "sql_parser.y"
                                {
	 								if ((yyvsp[0].sym) && (yyvsp[0].sym)->token == SQL_NAME)
										(yyval.sym) = _symbol_create_list(SQL_WINDOW, append_string(append_symbol(L(), (yyvsp[-1].sym)), (yyvsp[0].sym)->data.lval->h->data.sval));
									else if ((yyvsp[0].sym))
										(yyval.sym) = _symbol_create_list(SQL_WINDOW, append_list(append_symbol(L(), (yyvsp[-1].sym)), (yyvsp[0].sym)->data.lval->h->data.lval));
									else
										(yyval.sym) = (yyvsp[-1].sym);
 								}
#line 13359 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 799: /* value_exp: column_ref  */
#line 4086 "sql_parser.y"
                     { (yyval.sym) = _symbol_create_list(SQL_COLUMN, (yyvsp[0].l)); }
#line 13365 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 800: /* value_exp: session_user  */
#line 4087 "sql_parser.y"
                     { (yyval.sym) = _symbol_create_list(SQL_NAME, append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "current_user"))); }
#line 13371 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 801: /* value_exp: CURRENT_SCHEMA  */
#line 4088 "sql_parser.y"
                     { (yyval.sym) = _symbol_create_list(SQL_NAME, append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "current_schema"))); }
#line 13377 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 802: /* value_exp: CURRENT_ROLE  */
#line 4089 "sql_parser.y"
                     { (yyval.sym) = _symbol_create_list(SQL_NAME, append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "current_role"))); }
#line 13383 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 803: /* value_exp: CURRENT_TIMEZONE  */
#line 4090 "sql_parser.y"
                     { (yyval.sym) = _symbol_create_list(SQL_NAME, append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "current_timezone"))); }
#line 13389 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 805: /* value_exp: GROUPING '(' column_ref_commalist ')'  */
#line 4092 "sql_parser.y"
                                          { dlist *l = L();
										    append_list(l, append_string(L(), "grouping"));
											append_int(l, FALSE); /* ignore distinct */
											for (dnode *dn = (yyvsp[-1].l)->h ; dn ; dn = dn->next) {
												symbol *sym = dn->data.sym; /* do like a aggrN */
												append_symbol(l, _symbol_create_list(SQL_COLUMN, sym->data.lval));
											}
										    (yyval.sym) = _symbol_create_list(SQL_AGGR, l); }
#line 13402 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 806: /* value_exp: NEXT VALUE FOR qname  */
#line 4100 "sql_parser.y"
                                          { (yyval.sym) = _symbol_create_list(SQL_NEXT, (yyvsp[0].l)); }
#line 13408 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 811: /* param: '?'  */
#line 4109 "sql_parser.y"
        { 
	  int nr = (m->params)?list_length(m->params):0;

	  sql_add_param(m, NULL, NULL);
	  (yyval.sym) = _symbol_create_int( SQL_PARAMETER, nr ); 
	}
#line 13419 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 812: /* window_specification: window_ident_clause window_partition_clause window_order_clause window_frame_clause  */
#line 4118 "sql_parser.y"
        { (yyval.l) = append_symbol(append_symbol(append_symbol(append_string(L(), (yyvsp[-3].sval)), (yyvsp[-2].sym)), (yyvsp[-1].sym)), (yyvsp[0].sym)); }
#line 13425 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 813: /* window_ident_clause: %empty  */
#line 4122 "sql_parser.y"
                    { (yyval.sval) = NULL; }
#line 13431 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 814: /* window_ident_clause: ident  */
#line 4123 "sql_parser.y"
                    { (yyval.sval) = (yyvsp[0].sval); }
#line 13437 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 815: /* search_condition_commalist: search_condition  */
#line 4127 "sql_parser.y"
                                                    { (yyval.l) = append_symbol(L(), (yyvsp[0].sym)); }
#line 13443 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 816: /* search_condition_commalist: search_condition_commalist ',' search_condition  */
#line 4128 "sql_parser.y"
                                                    { (yyval.l) = append_symbol((yyvsp[-2].l), (yyvsp[0].sym)); }
#line 13449 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 817: /* window_partition_clause: %empty  */
#line 4132 "sql_parser.y"
                        { (yyval.sym) = NULL; }
#line 13455 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 818: /* window_partition_clause: PARTITION BY search_condition_commalist  */
#line 4134 "sql_parser.y"
        { (yyval.sym) = _symbol_create_list( SQL_GROUPBY, (yyvsp[0].l) ); }
#line 13461 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 819: /* window_order_clause: %empty  */
#line 4138 "sql_parser.y"
                        { (yyval.sym) = NULL; }
#line 13467 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 820: /* window_order_clause: ORDER BY sort_specification_list  */
#line 4140 "sql_parser.y"
        { (yyval.sym) = _symbol_create_list( SQL_ORDERBY, (yyvsp[0].l) ); }
#line 13473 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 821: /* window_frame_clause: %empty  */
#line 4144 "sql_parser.y"
                        { (yyval.sym) = NULL; }
#line 13479 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 822: /* window_frame_clause: window_frame_units window_frame_extent window_frame_exclusion  */
#line 4146 "sql_parser.y"
        { (yyval.sym) = _symbol_create_list( SQL_FRAME, append_int(append_int((yyvsp[-1].l), (yyvsp[-2].i_val)), (yyvsp[0].i_val))); }
#line 13485 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 823: /* window_frame_units: ROWS  */
#line 4150 "sql_parser.y"
                        { (yyval.i_val) = FRAME_ROWS; }
#line 13491 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 824: /* window_frame_units: RANGE  */
#line 4151 "sql_parser.y"
                        { (yyval.i_val) = FRAME_RANGE; }
#line 13497 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 825: /* window_frame_units: GROUPS  */
#line 4152 "sql_parser.y"
                        { (yyval.i_val) = FRAME_GROUPS; }
#line 13503 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 826: /* window_frame_extent: window_frame_start  */
#line 4156 "sql_parser.y"
                              { dlist *l = L(); append_symbol(l, (yyvsp[0].sym));
                            symbol *s = _symbol_create_int( SQL_FOLLOWING, CURRENT_ROW_BOUND);
                            dlist *l2 = append_symbol(L(), s);
                            symbol *sym = _symbol_create_list( SQL_CURRENT_ROW, l2);
                            append_symbol(l, sym);
                            (yyval.l) = l; }
#line 13514 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 827: /* window_frame_extent: window_frame_between  */
#line 4162 "sql_parser.y"
                          { (yyval.l) = (yyvsp[0].l); }
#line 13520 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 828: /* window_frame_start: UNBOUNDED PRECEDING  */
#line 4166 "sql_parser.y"
                              { symbol *s = _symbol_create_int( SQL_PRECEDING, UNBOUNDED_PRECEDING_BOUND);
                            dlist *l2 = append_symbol(L(), s);
                            (yyval.sym) = _symbol_create_list( SQL_PRECEDING, l2); }
#line 13528 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 829: /* window_frame_start: search_condition PRECEDING  */
#line 4169 "sql_parser.y"
                               { dlist *l2 = append_symbol(L(), (yyvsp[-1].sym));
                            (yyval.sym) = _symbol_create_list( SQL_PRECEDING, l2); }
#line 13535 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 830: /* window_frame_start: CURRENT ROW  */
#line 4171 "sql_parser.y"
                          { symbol *s = _symbol_create_int( SQL_PRECEDING, CURRENT_ROW_BOUND);
                            dlist *l = append_symbol(L(), s);
                            (yyval.sym) = _symbol_create_list( SQL_CURRENT_ROW, l); }
#line 13543 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 833: /* window_frame_between: BETWEEN window_bound AND window_bound  */
#line 4182 "sql_parser.y"
                                              { (yyval.l) = append_symbol(append_symbol(L(), (yyvsp[-2].sym)), (yyvsp[0].sym)); }
#line 13549 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 834: /* window_following_bound: UNBOUNDED FOLLOWING  */
#line 4186 "sql_parser.y"
                              { symbol *s = _symbol_create_int( SQL_FOLLOWING, UNBOUNDED_FOLLOWING_BOUND);
                            dlist *l2 = append_symbol(L(), s);
                            (yyval.sym) = _symbol_create_list( SQL_FOLLOWING, l2); }
#line 13557 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 835: /* window_following_bound: search_condition FOLLOWING  */
#line 4189 "sql_parser.y"
                               { dlist *l2 = append_symbol(L(), (yyvsp[-1].sym));
                            (yyval.sym) = _symbol_create_list( SQL_FOLLOWING, l2); }
#line 13564 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 836: /* window_frame_exclusion: %empty  */
#line 4194 "sql_parser.y"
                                        { (yyval.i_val) = EXCLUDE_NONE; }
#line 13570 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 837: /* window_frame_exclusion: EXCLUDE CURRENT ROW  */
#line 4195 "sql_parser.y"
                                { (yyval.i_val) = EXCLUDE_CURRENT_ROW; }
#line 13576 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 838: /* window_frame_exclusion: EXCLUDE sqlGROUP  */
#line 4196 "sql_parser.y"
                                { (yyval.i_val) = EXCLUDE_GROUP; }
#line 13582 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 839: /* window_frame_exclusion: EXCLUDE TIES  */
#line 4197 "sql_parser.y"
                                { (yyval.i_val) = EXCLUDE_TIES; }
#line 13588 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 840: /* window_frame_exclusion: EXCLUDE NO OTHERS  */
#line 4198 "sql_parser.y"
                                { (yyval.i_val) = EXCLUDE_NONE; }
#line 13594 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 841: /* func_ref: qfunc '(' ')'  */
#line 4203 "sql_parser.y"
        { dlist *l = L();
  	  append_list(l, (yyvsp[-2].l));
      append_int(l, FALSE); /* ignore distinct */
	  (yyval.sym) = _symbol_create_list( SQL_OP, l ); }
#line 13603 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 842: /* func_ref: qfunc '(' search_condition_commalist ')'  */
#line 4208 "sql_parser.y"
        { dlist *l = L();
  	  append_list(l, (yyvsp[-3].l));
	  append_int(l, FALSE); /* ignore distinct */
	  if (dlist_length((yyvsp[-1].l)) == 1) {
  	  	append_symbol(l, (yyvsp[-1].l)->h->data.sym);
	  	(yyval.sym) = _symbol_create_list( SQL_UNOP, l ); 
	  } else if (dlist_length((yyvsp[-1].l)) == 2) {
  	  	append_symbol(l, (yyvsp[-1].l)->h->data.sym);
  	  	append_symbol(l, (yyvsp[-1].l)->h->next->data.sym);
	  	(yyval.sym) = _symbol_create_list( SQL_BINOP, l ); 
	  } else {
  	  	append_list(l, (yyvsp[-1].l));
	  	(yyval.sym) = _symbol_create_list( SQL_NOP, l ); 
	  }
	}
#line 13623 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 843: /* qfunc: func_ident  */
#line 4226 "sql_parser.y"
                                { (yyval.l) = append_string(L(), (yyvsp[0].sval)); }
#line 13629 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 844: /* qfunc: ident '.' func_ident  */
#line 4227 "sql_parser.y"
                                { (yyval.l) = append_string(
					append_string(L(), (yyvsp[-2].sval)), (yyvsp[0].sval));}
#line 13636 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 845: /* func_ident: ident  */
#line 4232 "sql_parser.y"
                { (yyval.sval) = (yyvsp[0].sval); }
#line 13642 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 846: /* func_ident: LEFT  */
#line 4233 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "left"); }
#line 13648 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 847: /* func_ident: RIGHT  */
#line 4234 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "right"); }
#line 13654 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 848: /* func_ident: INSERT  */
#line 4235 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "insert"); }
#line 13660 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 849: /* datetime_funcs: EXTRACT '(' extract_datetime_field FROM scalar_exp ')'  */
#line 4240 "sql_parser.y"
                        { dlist *l = L();
			  const char *ident = datetime_field((itype)(yyvsp[-3].i_val));
			  append_list(l,
  		  	  	append_string(L(), sa_strdup(SA, ident)));
  		  	  append_int(l, FALSE); /* ignore distinct */
			  append_symbol(l, (yyvsp[-1].sym));
		  	  (yyval.sym) = _symbol_create_list( SQL_UNOP, l ); }
#line 13672 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 850: /* datetime_funcs: CURRENT_DATE opt_brackets  */
#line 4248 "sql_parser.y"
                        { dlist *l = L();
			  append_list(l,
			  	append_string(L(), sa_strdup(SA, "current_date")));
			 append_int(l, FALSE); /* ignore distinct */
	  		  (yyval.sym) = _symbol_create_list( SQL_OP, l ); }
#line 13682 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 851: /* datetime_funcs: CURRENT_TIME opt_brackets  */
#line 4254 "sql_parser.y"
                        { dlist *l = L();
			  append_list(l,
			  	append_string(L(), sa_strdup(SA, "current_time")));
			  append_int(l, FALSE); /* ignore distinct */
	  		  (yyval.sym) = _symbol_create_list( SQL_OP, l ); }
#line 13692 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 852: /* datetime_funcs: CURRENT_TIMESTAMP opt_brackets  */
#line 4260 "sql_parser.y"
                        { dlist *l = L();
			  append_list(l,
			  	append_string(L(), sa_strdup(SA, "current_timestamp")));
			  append_int(l, FALSE); /* ignore distinct */
	  		  (yyval.sym) = _symbol_create_list( SQL_OP, l ); }
#line 13702 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 853: /* datetime_funcs: LOCALTIME opt_brackets  */
#line 4266 "sql_parser.y"
                        { dlist *l = L();
			  append_list(l,
			  	append_string(L(), sa_strdup(SA, "localtime")));
			  append_int(l, FALSE); /* ignore distinct */
	  		  (yyval.sym) = _symbol_create_list( SQL_OP, l ); }
#line 13712 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 854: /* datetime_funcs: LOCALTIMESTAMP opt_brackets  */
#line 4272 "sql_parser.y"
                        { dlist *l = L();
			  append_list(l,
			  	append_string(L(), sa_strdup(SA, "localtimestamp")));
			  append_int(l, FALSE); /* ignore distinct */
	  		  (yyval.sym) = _symbol_create_list( SQL_OP, l ); }
#line 13722 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 855: /* opt_brackets: %empty  */
#line 4280 "sql_parser.y"
                { (yyval.bval) = 0; }
#line 13728 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 856: /* opt_brackets: '(' ')'  */
#line 4281 "sql_parser.y"
                { (yyval.bval) = 1; }
#line 13734 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 857: /* string_funcs: SUBSTRING '(' scalar_exp FROM scalar_exp FOR scalar_exp ')'  */
#line 4286 "sql_parser.y"
                        { dlist *l = L();
			  dlist *ops = L();
  		  	  append_list(l,
				append_string(L(), sa_strdup(SA, "substring")));
			  append_int(l, FALSE); /* ignore distinct */
  		  	  append_symbol(ops, (yyvsp[-5].sym));
  		  	  append_symbol(ops, (yyvsp[-3].sym));
  		  	  append_symbol(ops, (yyvsp[-1].sym));
			  append_list(l, ops);
		  	  (yyval.sym) = _symbol_create_list( SQL_NOP, l ); }
#line 13749 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 858: /* string_funcs: SUBSTRING '(' scalar_exp ',' scalar_exp ',' scalar_exp ')'  */
#line 4297 "sql_parser.y"
                        { dlist *l = L();
			  dlist *ops = L();
  		  	  append_list(l,
  		  	  	append_string(L(), sa_strdup(SA, "substring")));
			append_int(l, FALSE); /* ignore distinct */
  		  	  append_symbol(ops, (yyvsp[-5].sym));
  		  	  append_symbol(ops, (yyvsp[-3].sym));
  		  	  append_symbol(ops, (yyvsp[-1].sym));
			  append_list(l, ops);
		  	  (yyval.sym) = _symbol_create_list( SQL_NOP, l ); }
#line 13764 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 859: /* string_funcs: SUBSTRING '(' scalar_exp FROM scalar_exp ')'  */
#line 4308 "sql_parser.y"
                        { dlist *l = L();
  		  	  append_list(l,
  		  	  	append_string(L(), sa_strdup(SA, "substring")));
					  append_int(l, FALSE); /* ignore distinct */
  		  	  append_symbol(l, (yyvsp[-3].sym));
  		  	  append_symbol(l, (yyvsp[-1].sym));
		  	  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 13776 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 860: /* string_funcs: SUBSTRING '(' scalar_exp ',' scalar_exp ')'  */
#line 4316 "sql_parser.y"
                        { dlist *l = L();
  		  	  append_list(l,
  		  	  	append_string(L(), sa_strdup(SA, "substring")));
					  append_int(l, FALSE); /* ignore distinct */
  		  	  append_symbol(l, (yyvsp[-3].sym));
  		  	  append_symbol(l, (yyvsp[-1].sym));
		  	  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 13788 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 861: /* string_funcs: POSITION '(' scalar_exp sqlIN scalar_exp ')'  */
#line 4324 "sql_parser.y"
                        { dlist *l = L();
  		  	  append_list(l,
  		  	  	append_string(L(), sa_strdup(SA, "locate")));
					  append_int(l, FALSE); /* ignore distinct */
  		  	  append_symbol(l, (yyvsp[-3].sym));
  		  	  append_symbol(l, (yyvsp[-1].sym));
		  	  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 13800 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 862: /* string_funcs: scalar_exp CONCATSTRING scalar_exp  */
#line 4332 "sql_parser.y"
                        { dlist *l = L();
  		  	  append_list(l,
  		  	  	append_string(L(), sa_strdup(SA, "concat")));
					  append_int(l, FALSE); /* ignore distinct */
  		  	  append_symbol(l, (yyvsp[-2].sym));
  		  	  append_symbol(l, (yyvsp[0].sym));
		  	  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 13812 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 863: /* string_funcs: SPLIT_PART '(' scalar_exp ',' scalar_exp ',' scalar_exp ')'  */
#line 4340 "sql_parser.y"
                        { dlist *l = L();
			  dlist *ops = L();
  		  	  append_list(l,
				append_string(L(), sa_strdup(SA, "splitpart")));
				append_int(l, FALSE); /* ignore distinct */
  		  	  append_symbol(ops, (yyvsp[-5].sym));
  		  	  append_symbol(ops, (yyvsp[-3].sym));
  		  	  append_symbol(ops, (yyvsp[-1].sym));
			  append_list(l, ops);
		  	  (yyval.sym) = _symbol_create_list( SQL_NOP, l ); }
#line 13827 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 864: /* column_exp_commalist: column_exp  */
#line 4353 "sql_parser.y"
                        { (yyval.l) = append_symbol(L(), (yyvsp[0].sym) ); }
#line 13833 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 865: /* column_exp_commalist: column_exp_commalist ',' column_exp  */
#line 4355 "sql_parser.y"
                        { (yyval.l) = append_symbol( (yyvsp[-2].l), (yyvsp[0].sym) ); }
#line 13839 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 866: /* column_exp: '*'  */
#line 4360 "sql_parser.y"
                { dlist *l = L();
  		  append_string(l, NULL);
  		  append_string(l, NULL);
  		  (yyval.sym) = _symbol_create_list( SQL_TABLE, l ); }
#line 13848 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 867: /* column_exp: ident '.' '*'  */
#line 4365 "sql_parser.y"
                { dlist *l = L();
  		  append_string(l, (yyvsp[-2].sval));
  		  append_string(l, NULL);
  		  (yyval.sym) = _symbol_create_list( SQL_TABLE, l ); }
#line 13857 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 868: /* column_exp: func_ref '.' '*'  */
#line 4370 "sql_parser.y"
                { dlist *l = L();
  		  append_symbol(l, (yyvsp[-2].sym));
  		  append_string(l, NULL);
  		  (yyval.sym) = _symbol_create_list( SQL_TABLE, l ); }
#line 13866 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 869: /* column_exp: search_condition opt_alias_name  */
#line 4375 "sql_parser.y"
                { dlist *l = L();
  		  append_symbol(l, (yyvsp[-1].sym));
  		  append_string(l, (yyvsp[0].sval));
  		  (yyval.sym) = _symbol_create_list( SQL_COLUMN, l ); }
#line 13875 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 870: /* opt_alias_name: %empty  */
#line 4382 "sql_parser.y"
                { (yyval.sval) = NULL; }
#line 13881 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 871: /* opt_alias_name: AS ident  */
#line 4383 "sql_parser.y"
                { (yyval.sval) = (yyvsp[0].sval); }
#line 13887 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 872: /* opt_alias_name: ident  */
#line 4384 "sql_parser.y"
                { (yyval.sval) = (yyvsp[0].sval); }
#line 13893 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 874: /* qrank: RANK  */
#line 4392 "sql_parser.y"
                        { (yyval.l) = append_string(L(), (yyvsp[0].sval)); }
#line 13899 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 875: /* qrank: ident '.' RANK  */
#line 4393 "sql_parser.y"
                        { (yyval.l) = append_string(
			  append_string(L(), (yyvsp[-2].sval)), (yyvsp[0].sval));}
#line 13906 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 876: /* aggr_or_window_ref: qrank '(' ')'  */
#line 4399 "sql_parser.y"
                { dlist *l = L();
  		  append_list(l, (yyvsp[-2].l));
  		  append_int(l, FALSE); /* ignore distinct */
  		  append_list(l, NULL);
  		  (yyval.sym) = _symbol_create_list( SQL_RANK, l ); }
#line 13916 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 877: /* aggr_or_window_ref: qrank '(' search_condition_commalist ')'  */
#line 4405 "sql_parser.y"
                { dlist *l = L();
  		  append_list(l, (yyvsp[-3].l));
  		  append_int(l, FALSE); /* ignore distinct */
  		  append_list(l, (yyvsp[-1].l));
  		  (yyval.sym) = _symbol_create_list( SQL_RANK, l ); }
#line 13926 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 878: /* aggr_or_window_ref: qrank '(' DISTINCT search_condition_commalist ')'  */
#line 4411 "sql_parser.y"
                { dlist *l = L();
  		  append_list(l, (yyvsp[-4].l));
  		  append_int(l, TRUE);
  		  append_list(l, (yyvsp[-1].l));
  		  (yyval.sym) = _symbol_create_list( SQL_RANK, l ); }
#line 13936 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 879: /* aggr_or_window_ref: qrank '(' ALL search_condition_commalist ')'  */
#line 4417 "sql_parser.y"
                { dlist *l = L();
  		  append_list(l, (yyvsp[-4].l));
  		  append_int(l, FALSE);
  		  append_list(l, (yyvsp[-1].l));
  		  (yyval.sym) = _symbol_create_list( SQL_RANK, l ); }
#line 13946 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 880: /* aggr_or_window_ref: qfunc '(' '*' ')'  */
#line 4423 "sql_parser.y"
                { dlist *l = L();
  		  append_list(l, (yyvsp[-3].l));
		  append_int(l, FALSE); /* ignore distinct */
  		  append_symbol(l, NULL);
		  (yyval.sym) = _symbol_create_list( SQL_AGGR, l ); }
#line 13956 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 881: /* aggr_or_window_ref: qfunc '(' ident '.' '*' ')'  */
#line 4429 "sql_parser.y"
                { dlist *l = L();
  		  append_list(l, (yyvsp[-5].l));
		  append_int(l, FALSE); /* ignore distinct */
  		  append_symbol(l, NULL);
		  (yyval.sym) = _symbol_create_list( SQL_AGGR, l ); }
#line 13966 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 882: /* aggr_or_window_ref: qfunc '(' ')'  */
#line 4435 "sql_parser.y"
                { dlist *l = L();
  		  append_list(l, (yyvsp[-2].l));
		  append_int(l, FALSE); /* ignore distinct */
		  append_list(l, NULL);
		  (yyval.sym) = _symbol_create_list( SQL_OP, l ); }
#line 13976 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 883: /* aggr_or_window_ref: qfunc '(' search_condition_commalist ')'  */
#line 4441 "sql_parser.y"
                { dlist *l = L();
		  append_list(l, (yyvsp[-3].l));
		  append_int(l, FALSE); /* ignore distinct */
 		  if (dlist_length((yyvsp[-1].l)) == 1) {
		  	append_symbol(l, (yyvsp[-1].l)->h->data.sym);
			(yyval.sym) = _symbol_create_list( SQL_UNOP, l ); 
		  } else if (dlist_length((yyvsp[-1].l)) == 2) {
		  	append_symbol(l, (yyvsp[-1].l)->h->data.sym);
		  	append_symbol(l, (yyvsp[-1].l)->h->next->data.sym);
			(yyval.sym) = _symbol_create_list( SQL_BINOP, l ); 
		  } else {
		  	append_list(l, (yyvsp[-1].l));
		  	(yyval.sym) = _symbol_create_list( SQL_NOP, l ); 
		  }
		}
#line 13996 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 884: /* aggr_or_window_ref: qfunc '(' DISTINCT search_condition_commalist ')'  */
#line 4457 "sql_parser.y"
                { dlist *l = L();
		  append_list(l, (yyvsp[-4].l));
		  append_int(l, TRUE);
 		  if (dlist_length((yyvsp[-1].l)) == 1) {
		  	append_symbol(l, (yyvsp[-1].l)->h->data.sym);
			(yyval.sym) = _symbol_create_list( SQL_UNOP, l ); 
		  } else if (dlist_length((yyvsp[-1].l)) == 2) {
		  	append_symbol(l, (yyvsp[-1].l)->h->data.sym);
		  	append_symbol(l, (yyvsp[-1].l)->h->next->data.sym);
			(yyval.sym) = _symbol_create_list( SQL_BINOP, l ); 
		  } else {
		  	append_list(l, (yyvsp[-1].l));
		  	(yyval.sym) = _symbol_create_list( SQL_NOP, l ); 
		  }
		}
#line 14016 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 885: /* aggr_or_window_ref: qfunc '(' ALL search_condition_commalist ')'  */
#line 4473 "sql_parser.y"
                { dlist *l = L();
		  append_list(l, (yyvsp[-4].l));
		  append_int(l, FALSE);
 		  if (dlist_length((yyvsp[-1].l)) == 1) {
		  	append_symbol(l, (yyvsp[-1].l)->h->data.sym);
			(yyval.sym) = _symbol_create_list( SQL_UNOP, l ); 
		  } else if (dlist_length((yyvsp[-1].l)) == 2) {
		  	append_symbol(l, (yyvsp[-1].l)->h->data.sym);
		  	append_symbol(l, (yyvsp[-1].l)->h->next->data.sym);
			(yyval.sym) = _symbol_create_list( SQL_BINOP, l ); 
		  } else {
		  	append_list(l, (yyvsp[-1].l));
		  	(yyval.sym) = _symbol_create_list( SQL_NOP, l ); 
		  }
		}
#line 14036 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 887: /* opt_sign: '+'  */
#line 4492 "sql_parser.y"
                { (yyval.i_val) = 1; }
#line 14042 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 888: /* opt_sign: '-'  */
#line 4493 "sql_parser.y"
                { (yyval.i_val) = -1; }
#line 14048 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 889: /* opt_sign: %empty  */
#line 4494 "sql_parser.y"
                { (yyval.i_val) = 1; }
#line 14054 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 890: /* tz: WITH TIME ZONE  */
#line 4498 "sql_parser.y"
                        { (yyval.bval) = 1; }
#line 14060 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 891: /* tz: %empty  */
#line 4499 "sql_parser.y"
                        { (yyval.bval) = 0; }
#line 14066 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 892: /* time_precision: '(' intval ')'  */
#line 4510 "sql_parser.y"
                        { (yyval.i_val) = (yyvsp[-1].i_val)+1; }
#line 14072 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 893: /* time_precision: %empty  */
#line 4512 "sql_parser.y"
                        { (yyval.i_val) = 0+1; }
#line 14078 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 894: /* timestamp_precision: '(' intval ')'  */
#line 4516 "sql_parser.y"
                        { (yyval.i_val) = (yyvsp[-1].i_val)+1; }
#line 14084 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 895: /* timestamp_precision: %empty  */
#line 4518 "sql_parser.y"
                        { (yyval.i_val) = 6+1; }
#line 14090 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 896: /* datetime_type: sqlDATE  */
#line 4522 "sql_parser.y"
                        { sql_find_subtype(&(yyval.type), "date", 0, 0); }
#line 14096 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 897: /* datetime_type: TIME time_precision tz  */
#line 4524 "sql_parser.y"
                        { if ((yyvsp[0].bval))
				sql_find_subtype(&(yyval.type), "timetz", (yyvsp[-1].i_val), 0); 
			  else
				sql_find_subtype(&(yyval.type), "time", (yyvsp[-1].i_val), 0); 
			}
#line 14106 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 898: /* datetime_type: TIMESTAMP timestamp_precision tz  */
#line 4530 "sql_parser.y"
                        { if ((yyvsp[0].bval))
				sql_find_subtype(&(yyval.type), "timestamptz", (yyvsp[-1].i_val), 0); 
			  else
				sql_find_subtype(&(yyval.type), "timestamp", (yyvsp[-1].i_val), 0); 
			}
#line 14116 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 899: /* non_second_datetime_field: YEAR  */
#line 4538 "sql_parser.y"
                        { (yyval.i_val) = iyear; }
#line 14122 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 900: /* non_second_datetime_field: MONTH  */
#line 4539 "sql_parser.y"
                        { (yyval.i_val) = imonth; }
#line 14128 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 901: /* non_second_datetime_field: DAY  */
#line 4540 "sql_parser.y"
                        { (yyval.i_val) = iday; }
#line 14134 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 902: /* non_second_datetime_field: HOUR  */
#line 4541 "sql_parser.y"
                        { (yyval.i_val) = ihour; }
#line 14140 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 903: /* non_second_datetime_field: MINUTE  */
#line 4542 "sql_parser.y"
                        { (yyval.i_val) = imin; }
#line 14146 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 905: /* datetime_field: SECOND  */
#line 4547 "sql_parser.y"
                        { (yyval.i_val) = isec; }
#line 14152 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 907: /* extract_datetime_field: CENTURY  */
#line 4552 "sql_parser.y"
                        { (yyval.i_val) = icentury; }
#line 14158 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 908: /* extract_datetime_field: DECADE  */
#line 4553 "sql_parser.y"
                        { (yyval.i_val) = idecade; }
#line 14164 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 909: /* extract_datetime_field: QUARTER  */
#line 4554 "sql_parser.y"
                        { (yyval.i_val) = iquarter; }
#line 14170 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 910: /* extract_datetime_field: WEEK  */
#line 4555 "sql_parser.y"
                        { (yyval.i_val) = iweek; }
#line 14176 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 911: /* extract_datetime_field: DOW  */
#line 4556 "sql_parser.y"
                        { (yyval.i_val) = idow; }
#line 14182 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 912: /* extract_datetime_field: DOY  */
#line 4558 "sql_parser.y"
                        { (yyval.i_val) = idoy; }
#line 14188 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 913: /* extract_datetime_field: EPOCH  */
#line 4560 "sql_parser.y"
                        { (yyval.i_val) = iepoch; }
#line 14194 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 914: /* start_field: non_second_datetime_field time_precision  */
#line 4565 "sql_parser.y"
                { (yyval.l) = append_int(
			 	append_int( L(), (yyvsp[-1].i_val)), (yyvsp[0].i_val)-1);  }
#line 14201 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 915: /* end_field: non_second_datetime_field  */
#line 4571 "sql_parser.y"
                { (yyval.l) = append_int(
			 	append_int( L(), (yyvsp[0].i_val)), 0);  }
#line 14208 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 916: /* end_field: SECOND timestamp_precision  */
#line 4574 "sql_parser.y"
                { (yyval.l) = append_int(
			 	append_int( L(), isec), (yyvsp[0].i_val)-1);  }
#line 14215 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 917: /* single_datetime_field: non_second_datetime_field time_precision  */
#line 4580 "sql_parser.y"
                { (yyval.l) = append_int(
			 	append_int( L(), (yyvsp[-1].i_val)), (yyvsp[0].i_val)-1);  }
#line 14222 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 918: /* single_datetime_field: SECOND timestamp_precision  */
#line 4583 "sql_parser.y"
                { (yyval.l) = append_int(
			 	append_int( L(), isec), (yyvsp[0].i_val)-1);  }
#line 14229 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 919: /* interval_qualifier: start_field TO end_field  */
#line 4589 "sql_parser.y"
        { (yyval.l) =  append_list(
			append_list( L(), (yyvsp[-2].l)), (yyvsp[0].l) ); }
#line 14236 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 920: /* interval_qualifier: single_datetime_field  */
#line 4592 "sql_parser.y"
        { (yyval.l) =  append_list( L(), (yyvsp[0].l)); }
#line 14242 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 921: /* interval_type: INTERVAL interval_qualifier  */
#line 4596 "sql_parser.y"
                                {
		int sk, ek, sp, ep;
	  	int tpe;

		(yyval.type).type = NULL;
	  	if ( (tpe = parse_interval_qualifier( m, (yyvsp[0].l), &sk, &ek, &sp, &ep )) < 0){
			sqlformaterror(m, SQLSTATE(22006) "%s", "incorrect interval");
			YYABORT;
	  	} else {
			int d = inttype2digits(sk, ek);
			if (tpe == 0){
				sql_find_subtype(&(yyval.type), "month_interval", d, 0);
			} else if (d == 4) {
				sql_find_subtype(&(yyval.type), "day_interval", d, 0);
			} else {
				sql_find_subtype(&(yyval.type), "sec_interval", d, 0);
			}
	  	}
	}
#line 14266 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 931: /* literal: string  */
#line 4639 "sql_parser.y"
                { const char *s = (yyvsp[0].sval);
		  int len = UTF8_strlen(s);
		  sql_subtype t;
		  sql_find_subtype(&t, "char", len, 0 );
		  (yyval.sym) = _newAtomNode( _atom_string(&t, s)); }
#line 14276 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 932: /* literal: HEXADECIMAL  */
#line 4645 "sql_parser.y"
                { int len = _strlen((yyvsp[0].sval)), i = 2, err = 0;
		  char * hexa = (yyvsp[0].sval);
	 	  sql_subtype t;
#ifdef HAVE_HGE
		  hge res = 0;
#else
		  lng res = 0;
#endif
		  /* skip leading '0' */
		  while (i < len && hexa[i] == '0')
		  	i++;

		  /* we only support positive values that fit in a signed 128-bit type,
		   * i.e., max. 63/127 bit => < 2^63/2^127 => < 0x800...
		   * (leading sign (-0x...) is handled separately elsewhere)
		   */
		  if (len - i < MAX_HEX_DIGITS || (len - i == MAX_HEX_DIGITS && hexa[i] < '8'))
		  	while (err == 0 && i < len)
		  	{
				res <<= 4;
				if (isdigit((unsigned char) hexa[i]))
					res = res + (hexa[i] - '0');
				else if ('A' <= hexa[i] && hexa[i] <= 'F')
					res = res + (hexa[i] - 'A' + 10);
				else if ('a' <= hexa[i] && hexa[i] <= 'f')
					res = res + (hexa[i] - 'a' + 10);
				else
					err = 1;
		  		i++;
			}
		  else
			err = 1;

		  if (err == 0) {
		  	assert(res >= 0);

		  	/* use smallest type that can accommodate the given value */
			if (res <= GDK_bte_max)
				sql_find_subtype(&t, "tinyint", 8, 0 );
			else if (res <= GDK_sht_max)
				sql_find_subtype(&t, "smallint", 16, 0 );
		  	else if (res <= GDK_int_max)
				sql_find_subtype(&t, "int", 32, 0 );
			else if (res <= GDK_lng_max)
				sql_find_subtype(&t, "bigint", 64, 0 );
#ifdef HAVE_HGE
			else if (res <= GDK_hge_max)
				sql_find_subtype(&t, "hugeint", 128, 0 );
#endif
			else
				err = 1;
		  }

		  if (err != 0) {
			sqlformaterror(m, SQLSTATE(22003) "Invalid hexadecimal number or hexadecimal too large (%s)", (yyvsp[0].sval));
			(yyval.sym) = NULL;
			YYABORT;
		  } else {
			(yyval.sym) = _newAtomNode( atom_int(SA, &t, res));
		  }
		}
#line 14342 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 933: /* literal: OIDNUM  */
#line 4707 "sql_parser.y"
                { int err = 0;
		  size_t len = sizeof(lng);
		  lng value, *p = &value;
		  sql_subtype t;

		  if (lngFromStr((yyvsp[0].sval), &len, &p, false) < 0 || is_lng_nil(value))
		  	err = 2;

		  if (!err) {
		    if (value >= (lng) GDK_oid_min && value <= (lng) GDK_oid_max)
#if SIZEOF_OID == SIZEOF_INT
		  	  sql_find_subtype(&t, "oid", 31, 0 );
#else
		  	  sql_find_subtype(&t, "oid", 63, 0 );
#endif
		    else
			  err = 1;
		  }

		  if (err) {
			sqlformaterror(m, SQLSTATE(22003) "OID value too large or not a number (%s)", (yyvsp[0].sval));
			(yyval.sym) = NULL;
			YYABORT;
		  } else {
		  	(yyval.sym) = _newAtomNode( atom_int(SA, &t, value));
		  }
		}
#line 14374 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 934: /* literal: sqlINT  */
#line 4735 "sql_parser.y"
                { int digits = _strlen((yyvsp[0].sval)), err = 0;
#ifdef HAVE_HGE
		  hge value, *p = &value;
		  size_t len = sizeof(hge);
		  const hge one = 1;
#else
		  lng value, *p = &value;
		  size_t len = sizeof(lng);
		  const lng one = 1;
#endif
		  sql_subtype t;

#ifdef HAVE_HGE
		  if (hgeFromStr((yyvsp[0].sval), &len, &p, false) < 0 || is_hge_nil(value))
		  	err = 2;
#else
		  if (lngFromStr((yyvsp[0].sval), &len, &p, false) < 0 || is_lng_nil(value))
		  	err = 2;
#endif

		  /* find the most suitable data type for the given number */
		  if (!err) {
		    int bits = (int) digits2bits(digits), obits = bits;

		    while (bits > 0 &&
			   (bits == sizeof(value) * 8 ||
			    (one << (bits - 1)) > value))
			  bits--;

 		    if (bits != obits &&
		       (bits == 8 || bits == 16 || bits == 32 || bits == 64))
				bits++;
		
		    if (value >= GDK_bte_min && value <= GDK_bte_max)
		  	  sql_find_subtype(&t, "tinyint", bits, 0 );
		    else if (value >= GDK_sht_min && value <= GDK_sht_max)
		  	  sql_find_subtype(&t, "smallint", bits, 0 );
		    else if (value >= GDK_int_min && value <= GDK_int_max)
		  	  sql_find_subtype(&t, "int", bits, 0 );
		    else if (value >= GDK_lng_min && value <= GDK_lng_max)
		  	  sql_find_subtype(&t, "bigint", bits, 0 );
#ifdef HAVE_HGE
		    else if (value >= GDK_hge_min && value <= GDK_hge_max)
		  	  sql_find_subtype(&t, "hugeint", bits, 0 );
#endif
		    else
			  err = 1;
		  }

		  if (err) {
			sqlformaterror(m, SQLSTATE(22003) "Integer value too large or not a number (%s)", (yyvsp[0].sval));
			(yyval.sym) = NULL;
			YYABORT;
		  } else {
		  	(yyval.sym) = _newAtomNode( atom_int(SA, &t, value));
		  }
		}
#line 14436 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 935: /* literal: INTNUM  */
#line 4793 "sql_parser.y"
                { char *s = sa_strdup(SA, (yyvsp[0].sval));
			int digits;
			int scale;
			int has_errors;
			sql_subtype t;

			DEC_TPE value = decimal_from_str(s, &digits, &scale, &has_errors);

			if (!has_errors && digits <= MAX_DEC_DIGITS) {
				// The float-like value seems to fit in decimal storage
				sql_find_subtype(&t, "decimal", digits, scale );
				(yyval.sym) = _newAtomNode( atom_dec(SA, &t, value));
			}
			else {
				/*
				* The float-like value either doesn't fit in integer decimal storage
				* or it is not a valid float representation.
				*/
				char *p = (yyvsp[0].sval);
				double val;

				errno = 0;
				val = strtod((yyvsp[0].sval),&p);
				if (p == (yyvsp[0].sval) || is_dbl_nil(val) || (errno == ERANGE && (val < -1 || val > 1))) {
					sqlformaterror(m, SQLSTATE(22003) "Double value too large or not a number (%s)", (yyvsp[0].sval));
					(yyval.sym) = NULL;
					YYABORT;
				} else {
					sql_find_subtype(&t, "double", 51, 0 );
					(yyval.sym) = _newAtomNode(atom_float(SA, &t, val));
				}
		   }
		}
#line 14474 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 936: /* literal: APPROXNUM  */
#line 4827 "sql_parser.y"
                { sql_subtype t;
  		  char *p = (yyvsp[0].sval);
		  double val;

		  errno = 0;
 		  val = strtod((yyvsp[0].sval),&p);
		  if (p == (yyvsp[0].sval) || is_dbl_nil(val) || (errno == ERANGE && (val < -1 || val > 1))) {
			sqlformaterror(m, SQLSTATE(22003) "Double value too large or not a number (%s)", (yyvsp[0].sval));
			(yyval.sym) = NULL;
			YYABORT;
		  }
		  sql_find_subtype(&t, "double", 51, 0 );
		  (yyval.sym) = _newAtomNode(atom_float(SA, &t, val)); }
#line 14492 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 937: /* literal: sqlDATE string  */
#line 4841 "sql_parser.y"
                { sql_subtype t;
		  atom *a;
		  int r;

 		  r = sql_find_subtype(&t, "date", 0, 0 );
		  if (!r || (a = atom_general(SA, &t, (yyvsp[0].sval))) == NULL) {
			sqlformaterror(m, SQLSTATE(22007) "Incorrect date value (%s)", (yyvsp[0].sval));
			(yyval.sym) = NULL;
			YYABORT;
		  } else {
		  	(yyval.sym) = _newAtomNode(a);
		} }
#line 14509 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 938: /* literal: TIME time_precision tz string  */
#line 4854 "sql_parser.y"
                { sql_subtype t;
		  atom *a;
		  int r;

	          r = sql_find_subtype(&t, ((yyvsp[-1].bval))?"timetz":"time", (yyvsp[-2].i_val), 0);
		  if (!r || (a = atom_general(SA, &t, (yyvsp[0].sval))) == NULL) {
			sqlformaterror(m, SQLSTATE(22007) "Incorrect time value (%s)", (yyvsp[0].sval));
			(yyval.sym) = NULL;
			YYABORT;
		  } else {
		  	(yyval.sym) = _newAtomNode(a);
		} }
#line 14526 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 939: /* literal: TIMESTAMP timestamp_precision tz string  */
#line 4867 "sql_parser.y"
                { sql_subtype t;
		  atom *a;
		  int r;

 		  r = sql_find_subtype(&t, ((yyvsp[-1].bval))?"timestamptz":"timestamp",(yyvsp[-2].i_val),0);
		  if (!r || (a = atom_general(SA, &t, (yyvsp[0].sval))) == NULL) {
			sqlformaterror(m, SQLSTATE(22007) "Incorrect timestamp value (%s)", (yyvsp[0].sval));
			(yyval.sym) = NULL;
			YYABORT;
		  } else {
		  	(yyval.sym) = _newAtomNode(a);
		} }
#line 14543 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 941: /* literal: blob string  */
#line 4881 "sql_parser.y"
                { sql_subtype t;
		  atom *a= 0;
		  int r;

		  (yyval.sym) = NULL;
 		  r = sql_find_subtype(&t, "blob", 0, 0);
	          if (r && (a = atom_general(SA, &t, (yyvsp[0].sval))) != NULL)
			(yyval.sym) = _newAtomNode(a);
		  if (!(yyval.sym)) {
			sqlformaterror(m, SQLSTATE(22M28) "Incorrect blob (%s)", (yyvsp[0].sval));
			YYABORT;
		  }
		}
#line 14561 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 942: /* literal: blobstring  */
#line 4895 "sql_parser.y"
                { sql_subtype t;
		  atom *a= 0;
		  int r;

		  (yyval.sym) = NULL;
 		  r = sql_find_subtype(&t, "blob", 0, 0);
	          if (r && (a = atom_general(SA, &t, (yyvsp[0].sval))) != NULL)
			(yyval.sym) = _newAtomNode(a);
		  if (!(yyval.sym)) {
			sqlformaterror(m, SQLSTATE(22M28) "Incorrect blob (%s)", (yyvsp[0].sval));
			YYABORT;
		  }
		}
#line 14579 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 943: /* literal: aTYPE string  */
#line 4909 "sql_parser.y"
                { sql_subtype t;
		  atom *a = NULL;
		  int r;

		  if (!(r = sql_find_subtype(&t, (yyvsp[-1].sval), 0, 0))) {
			sqlformaterror(m, SQLSTATE(22000) "Type (%s) unknown", (yyvsp[-1].sval));
			YYABORT;
		  }
		  if (!(a = atom_general(SA, &t, (yyvsp[0].sval)))) {
			sqlformaterror(m, SQLSTATE(22000) "Incorrect %s (%s)", (yyvsp[-1].sval), (yyvsp[0].sval));
			YYABORT;
		  }
		  (yyval.sym) = _newAtomNode(a);
		}
#line 14598 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 944: /* literal: type_alias string  */
#line 4924 "sql_parser.y"
                { sql_subtype t; 
		  atom *a = NULL;
		  int r;

		  if (!(r = sql_find_subtype(&t, (yyvsp[-1].sval), 0, 0))) {
			sqlformaterror(m, SQLSTATE(22000) "Type (%s) unknown", (yyvsp[-1].sval));
			YYABORT;
		  }
		  if (!(a = atom_general(SA, &t, (yyvsp[0].sval)))) {
			sqlformaterror(m, SQLSTATE(22000) "Incorrect %s (%s)", (yyvsp[-1].sval), (yyvsp[0].sval));
			YYABORT;
		  }
		  (yyval.sym) = _newAtomNode(a);
		}
#line 14617 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 945: /* literal: ident_or_uident string  */
#line 4939 "sql_parser.y"
                {
		  sql_type *t = NULL;
		  sql_subtype tpe;
		  atom *a = NULL;

		  if (!(t = mvc_bind_type(m, (yyvsp[-1].sval)))) {
			sqlformaterror(m, SQLSTATE(22000) "Type (%s) unknown", (yyvsp[-1].sval));
			YYABORT;
		  }
		  sql_init_subtype(&tpe, t, 0, 0);
		  if (!(a = atom_general(SA, &tpe, (yyvsp[0].sval)))) {
			sqlformaterror(m, SQLSTATE(22000) "Incorrect %s (%s)", (yyvsp[-1].sval), (yyvsp[0].sval));
			YYABORT;
		  }
		  (yyval.sym) = _newAtomNode(a);
		}
#line 14638 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 946: /* literal: BOOL_FALSE  */
#line 4956 "sql_parser.y"
                { sql_subtype t;
		  sql_find_subtype(&t, "boolean", 0, 0 );
		  (yyval.sym) = _newAtomNode( atom_bool(SA, &t, FALSE)); }
#line 14646 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 947: /* literal: BOOL_TRUE  */
#line 4960 "sql_parser.y"
                { sql_subtype t;
		  sql_find_subtype(&t, "boolean", 0, 0 );
		  (yyval.sym) = _newAtomNode( atom_bool(SA, &t, TRUE)); }
#line 14654 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 948: /* interval_expression: INTERVAL opt_sign string interval_qualifier  */
#line 4966 "sql_parser.y"
                                               { 
		sql_subtype t;
		int sk, ek, sp, ep, tpe;
	  	lng i = 0;
		int r = 0;

		(yyval.sym) = NULL;
	  	if ( (tpe = parse_interval_qualifier( m, (yyvsp[0].l), &sk, &ek, &sp, &ep )) < 0){
			yyerror(m, "incorrect interval");
			YYABORT;
	  	} else {
			int d = inttype2digits(sk, ek);
			if (tpe == 0){
				r=sql_find_subtype(&t, "month_interval", d, 0);
			} else if (d == 4) {
				r=sql_find_subtype(&t, "day_interval", d, 0);
			} else {
				r=sql_find_subtype(&t, "sec_interval", d, 0);
			}
	  	}
	  	if (!r || (tpe = parse_interval( m, (yyvsp[-2].i_val), (yyvsp[-1].sval), sk, ek, sp, ep, &i)) < 0) { 
			yyerror(m, "incorrect interval");
			(yyval.sym) = NULL;
			YYABORT;
	  	} else {
			/* count the number of digits in the input */
/*
			lng cpyval = i, inlen = 1;

			cpyval /= qualifier2multiplier(ek);
			while (cpyval /= 10)
				inlen++;
		    	if (inlen > t.digits) {
				sqlformaterror(m, SQLSTATE(22006) "incorrect interval (" LLFMT " > %d)", inlen, t.digits);
				$$ = NULL;
				YYABORT;
			}
*/
	  		(yyval.sym) = _newAtomNode( atom_int(SA, &t, i));
	  	}
	}
#line 14700 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 949: /* qname: ident  */
#line 5012 "sql_parser.y"
                                { (yyval.l) = append_string(L(), (yyvsp[0].sval)); }
#line 14706 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 950: /* qname: ident '.' ident  */
#line 5013 "sql_parser.y"
                                {
				  m->scanner.schema = (yyvsp[-2].sval);
				  (yyval.l) = append_string(
					append_string(L(), (yyvsp[-2].sval)), (yyvsp[0].sval));}
#line 14715 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 951: /* qname: ident '.' ident '.' ident  */
#line 5017 "sql_parser.y"
                                {
				  m->scanner.schema = (yyvsp[-4].sval);
				  (yyval.l) = append_string(
					append_string(
						append_string(L(), (yyvsp[-4].sval)), 
						(yyvsp[-2].sval)), 
					(yyvsp[0].sval))
				;}
#line 14728 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 952: /* column_ref: ident  */
#line 5028 "sql_parser.y"
                        { (yyval.l) = append_string(
				L(), (yyvsp[0].sval)); }
#line 14735 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 953: /* column_ref: ident '.' ident  */
#line 5031 "sql_parser.y"
                        { (yyval.l) = append_string(
				append_string(
				 L(), (yyvsp[-2].sval)), (yyvsp[0].sval));}
#line 14743 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 954: /* column_ref: ident '.' ident '.' ident  */
#line 5036 "sql_parser.y"
                        { (yyval.l) = append_string(
				append_string(
				 append_string(
				  L(), (yyvsp[-4].sval)), (yyvsp[-2].sval)), (yyvsp[0].sval));}
#line 14752 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 955: /* variable_ref: ident  */
#line 5043 "sql_parser.y"
                        { (yyval.l) = append_string(
				L(), (yyvsp[0].sval)); }
#line 14759 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 956: /* variable_ref: ident '.' ident  */
#line 5046 "sql_parser.y"
                        { (yyval.l) = append_string(
				append_string(
				 L(), (yyvsp[-2].sval)), (yyvsp[0].sval));}
#line 14767 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 957: /* cast_exp: CAST '(' search_condition AS data_type ')'  */
#line 5053 "sql_parser.y"
        { dlist *l = L();
	  append_symbol(l, (yyvsp[-3].sym));
	  append_type(l, &(yyvsp[-1].type));
	  (yyval.sym) = _symbol_create_list( SQL_CAST, l ); }
#line 14776 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 958: /* cast_exp: CONVERT '(' search_condition ',' data_type ')'  */
#line 5059 "sql_parser.y"
        { dlist *l = L();
	  append_symbol(l, (yyvsp[-3].sym));
	  append_type(l, &(yyvsp[-1].type));
	  (yyval.sym) = _symbol_create_list( SQL_CAST, l ); }
#line 14785 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 959: /* case_exp: NULLIF '(' search_condition ',' search_condition ')'  */
#line 5067 "sql_parser.y"
                { (yyval.sym) = _symbol_create_list(SQL_NULLIF,
		   append_symbol(
		    append_symbol(
		     L(), (yyvsp[-3].sym)), (yyvsp[-1].sym))); }
#line 14794 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 960: /* case_exp: COALESCE '(' case_search_condition_commalist ')'  */
#line 5072 "sql_parser.y"
                { (yyval.sym) = _symbol_create_list(SQL_COALESCE, (yyvsp[-1].l)); }
#line 14800 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 961: /* case_exp: CASE search_condition when_value_list case_opt_else END  */
#line 5074 "sql_parser.y"
                { (yyval.sym) = _symbol_create_list(SQL_CASE,
		   append_symbol(
		    append_list(
		     append_symbol(
		      L(),(yyvsp[-3].sym)),(yyvsp[-2].l)),(yyvsp[-1].sym))); }
#line 14810 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 962: /* case_exp: CASE when_search_list case_opt_else END  */
#line 5080 "sql_parser.y"
                 { (yyval.sym) = _symbol_create_list(SQL_CASE,
		   append_symbol(
		    append_list(
		     L(),(yyvsp[-2].l)),(yyvsp[-1].sym))); }
#line 14819 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 963: /* case_search_condition_commalist: search_condition ',' search_condition  */
#line 5088 "sql_parser.y"
                        { (yyval.l) = append_symbol( L(), (yyvsp[-2].sym));
			  (yyval.l) = append_symbol( (yyval.l), (yyvsp[0].sym));
			}
#line 14827 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 964: /* case_search_condition_commalist: case_search_condition_commalist ',' search_condition  */
#line 5092 "sql_parser.y"
                        { (yyval.l) = append_symbol( (yyvsp[-2].l), (yyvsp[0].sym)); }
#line 14833 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 965: /* when_value: WHEN search_condition THEN search_condition  */
#line 5097 "sql_parser.y"
                        { (yyval.sym) = _symbol_create_list( SQL_WHEN,
			   append_symbol(
			    append_symbol(
			     L(), (yyvsp[-2].sym)),(yyvsp[0].sym))); }
#line 14842 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 966: /* when_value_list: when_value  */
#line 5105 "sql_parser.y"
                        { (yyval.l) = append_symbol( L(), (yyvsp[0].sym));}
#line 14848 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 967: /* when_value_list: when_value_list when_value  */
#line 5107 "sql_parser.y"
                        { (yyval.l) = append_symbol( (yyvsp[-1].l), (yyvsp[0].sym)); }
#line 14854 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 968: /* when_search: WHEN search_condition THEN search_condition  */
#line 5112 "sql_parser.y"
                        { (yyval.sym) = _symbol_create_list( SQL_WHEN,
			   append_symbol(
			    append_symbol(
			     L(), (yyvsp[-2].sym)),(yyvsp[0].sym))); }
#line 14863 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 969: /* when_search_list: when_search  */
#line 5120 "sql_parser.y"
                        { (yyval.l) = append_symbol( L(), (yyvsp[0].sym)); }
#line 14869 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 970: /* when_search_list: when_search_list when_search  */
#line 5122 "sql_parser.y"
                        { (yyval.l) = append_symbol( (yyvsp[-1].l), (yyvsp[0].sym)); }
#line 14875 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 971: /* case_opt_else: %empty  */
#line 5126 "sql_parser.y"
                        { (yyval.sym) = NULL; }
#line 14881 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 972: /* case_opt_else: ELSE search_condition  */
#line 5127 "sql_parser.y"
                                { (yyval.sym) = (yyvsp[0].sym); }
#line 14887 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 973: /* nonzero: intval  */
#line 5134 "sql_parser.y"
                { (yyval.i_val) = (yyvsp[0].i_val);
		  if ((yyval.i_val) <= 0) {
			(yyval.i_val) = -1;
			yyerror(m, "Positive value greater than 0 expected");
			YYABORT;
		  }
		}
#line 14899 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 974: /* nonzerolng: lngval  */
#line 5145 "sql_parser.y"
                { (yyval.l_val) = (yyvsp[0].l_val);
		  if ((yyval.l_val) <= 0) {
			(yyval.l_val) = -1;
			yyerror(m, "Positive value greater than 0 expected");
			YYABORT;
		  }
		}
#line 14911 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 975: /* poslng: lngval  */
#line 5155 "sql_parser.y"
                { (yyval.l_val) = (yyvsp[0].l_val);
		  if ((yyval.l_val) < 0) {
			(yyval.l_val) = -1;
			yyerror(m, "Positive value expected");
			YYABORT;
		  }
		}
#line 14923 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 976: /* posint: intval  */
#line 5165 "sql_parser.y"
                { (yyval.i_val) = (yyvsp[0].i_val);
		  if ((yyval.i_val) < 0) {
			(yyval.i_val) = -1;
			yyerror(m, "Positive value expected");
			YYABORT;
		  }
		}
#line 14935 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 977: /* data_type: CHARACTER  */
#line 5176 "sql_parser.y"
                        { sql_find_subtype(&(yyval.type), "char", 1, 0); }
#line 14941 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 978: /* data_type: varchar  */
#line 5178 "sql_parser.y"
                        { (yyval.type).type = NULL;
			  yyerror(m, "CHARACTER VARYING needs a mandatory length specification");
			  YYABORT;
			}
#line 14950 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 979: /* data_type: clob  */
#line 5182 "sql_parser.y"
                        { sql_find_subtype(&(yyval.type), "clob", 0, 0); }
#line 14956 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 980: /* data_type: CHARACTER '(' nonzero ')'  */
#line 5184 "sql_parser.y"
                        { sql_find_subtype(&(yyval.type), "char", (yyvsp[-1].i_val), 0); }
#line 14962 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 981: /* data_type: varchar '(' nonzero ')'  */
#line 5186 "sql_parser.y"
                        { sql_find_subtype(&(yyval.type), "varchar", (yyvsp[-1].i_val), 0); }
#line 14968 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 982: /* data_type: clob '(' nonzero ')'  */
#line 5188 "sql_parser.y"
                        { sql_find_subtype(&(yyval.type), "clob", (yyvsp[-1].i_val), 0);
			  /* NOTE: CLOB may be called as CLOB(2K) which is equivalent
			   *       to CLOB(2048).  Due to 'nonzero' it is not possible
			   *       to enter this as the parser rejects it.  However it
			   *       might be a ToDo for the future.
			   *       See p. 125 SQL-99
			   */
			}
#line 14981 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 983: /* data_type: blob  */
#line 5196 "sql_parser.y"
                        { sql_find_subtype(&(yyval.type), "blob", 0, 0); }
#line 14987 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 984: /* data_type: blob '(' nonzero ')'  */
#line 5198 "sql_parser.y"
                        { sql_find_subtype(&(yyval.type), "blob", (yyvsp[-1].i_val), 0);
			  /* NOTE: BLOB may be called as BLOB(2K) which is equivalent
			   *       to BLOB(2048).  Due to 'nonzero' it is not possible
			   *       to enter this as the parser rejects it.  However it
			   *       might be a ToDo for the future.
			   *       See p. 85 SQL-99
			   */
			}
#line 15000 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 985: /* data_type: TINYINT  */
#line 5206 "sql_parser.y"
                        { sql_find_subtype(&(yyval.type), "tinyint", 0, 0); }
#line 15006 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 986: /* data_type: SMALLINT  */
#line 5207 "sql_parser.y"
                        { sql_find_subtype(&(yyval.type), "smallint", 0, 0); }
#line 15012 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 987: /* data_type: sqlINTEGER  */
#line 5208 "sql_parser.y"
                        { sql_find_subtype(&(yyval.type), "int", 0, 0); }
#line 15018 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 988: /* data_type: BIGINT  */
#line 5209 "sql_parser.y"
                        { sql_find_subtype(&(yyval.type), "bigint", 0, 0); }
#line 15024 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 989: /* data_type: HUGEINT  */
#line 5210 "sql_parser.y"
                        { sql_find_subtype(&(yyval.type), "hugeint", 0, 0); }
#line 15030 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 990: /* data_type: sqlDECIMAL  */
#line 5212 "sql_parser.y"
                        { sql_find_subtype(&(yyval.type), "decimal", 18, 3); }
#line 15036 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 991: /* data_type: sqlDECIMAL '(' nonzero ')'  */
#line 5214 "sql_parser.y"
                        { 
			  int d = (yyvsp[-1].i_val);
			  if (d > MAX_DEC_DIGITS) {
				sqlformaterror(m, SQLSTATE(22003) "Decimal of %d digits are not supported", d);
				(yyval.type).type = NULL;
				YYABORT;
			  } else {
			        sql_find_subtype(&(yyval.type), "decimal", d, 0); 
			  }
			}
#line 15051 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 992: /* data_type: sqlDECIMAL '(' nonzero ',' posint ')'  */
#line 5225 "sql_parser.y"
                        { 
			  int d = (yyvsp[-3].i_val);
			  int s = (yyvsp[-1].i_val);
			  if (s > d || d > MAX_DEC_DIGITS) {
				if (s > d)
					sqlformaterror(m, SQLSTATE(22003) "Scale (%d) should be less or equal to the precision (%d)", s, d);
				else
					sqlformaterror(m, SQLSTATE(22003) "Decimal(%d,%d) isn't supported because P=%d > %d", d, s, d, MAX_DEC_DIGITS);
				(yyval.type).type = NULL;
				YYABORT;
			  } else {
				sql_find_subtype(&(yyval.type), "decimal", d, s);
			  }
			}
#line 15070 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 993: /* data_type: sqlFLOAT  */
#line 5239 "sql_parser.y"
                        { sql_find_subtype(&(yyval.type), "double", 0, 0); }
#line 15076 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 994: /* data_type: sqlFLOAT '(' nonzero ')'  */
#line 5241 "sql_parser.y"
                        { if ((yyvsp[-1].i_val) > 0 && (yyvsp[-1].i_val) <= 24) {
				sql_find_subtype(&(yyval.type), "real", (yyvsp[-1].i_val), 0);
			  } else if ((yyvsp[-1].i_val) > 24 && (yyvsp[-1].i_val) <= 53) {
				sql_find_subtype(&(yyval.type), "double", (yyvsp[-1].i_val), 0);
			  } else {
				sqlformaterror(m, SQLSTATE(22003) "Number of digits for FLOAT values should be between 1 and 53");
				(yyval.type).type = NULL;
				YYABORT;
			  }
			}
#line 15091 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 995: /* data_type: sqlFLOAT '(' intval ',' intval ')'  */
#line 5252 "sql_parser.y"
                        { if ((yyvsp[-1].i_val) >= (yyvsp[-3].i_val)) {
				sqlformaterror(m, SQLSTATE(22003) "Precision(%d) should be less than number of digits(%d)", (yyvsp[-1].i_val), (yyvsp[-3].i_val));
				(yyval.type).type = NULL;
				YYABORT;
			  } else if ((yyvsp[-3].i_val) > 0 && (yyvsp[-3].i_val) <= 24) {
				sql_find_subtype(&(yyval.type), "real", (yyvsp[-3].i_val), (yyvsp[-1].i_val));
			  } else if ((yyvsp[-3].i_val) > 24 && (yyvsp[-3].i_val) <= 53) {
				sql_find_subtype(&(yyval.type), "double", (yyvsp[-3].i_val), (yyvsp[-1].i_val));
			  } else {
				sqlformaterror(m, SQLSTATE(22003) "Number of digits for FLOAT values should be between 1 and 53");
				(yyval.type).type = NULL;
				YYABORT;
			  }
			}
#line 15110 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 996: /* data_type: sqlDOUBLE  */
#line 5266 "sql_parser.y"
                        { sql_find_subtype(&(yyval.type), "double", 0, 0); }
#line 15116 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 997: /* data_type: sqlDOUBLE PRECISION  */
#line 5267 "sql_parser.y"
                        { sql_find_subtype(&(yyval.type), "double", 0, 0); }
#line 15122 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 998: /* data_type: sqlREAL  */
#line 5268 "sql_parser.y"
                        { sql_find_subtype(&(yyval.type), "real", 0, 0); }
#line 15128 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1001: /* data_type: aTYPE  */
#line 5271 "sql_parser.y"
                        { sql_find_subtype(&(yyval.type), (yyvsp[0].sval), 0, 0); }
#line 15134 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1002: /* data_type: aTYPE '(' nonzero ')'  */
#line 5273 "sql_parser.y"
                        { sql_find_subtype(&(yyval.type), (yyvsp[-3].sval), (yyvsp[-1].i_val), 0); }
#line 15140 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1003: /* data_type: type_alias  */
#line 5274 "sql_parser.y"
                        { sql_find_subtype(&(yyval.type), (yyvsp[0].sval), 0, 0); }
#line 15146 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1004: /* data_type: type_alias '(' nonzero ')'  */
#line 5276 "sql_parser.y"
                        { sql_find_subtype(&(yyval.type), (yyvsp[-3].sval), (yyvsp[-1].i_val), 0); }
#line 15152 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1005: /* data_type: type_alias '(' intval ',' intval ')'  */
#line 5278 "sql_parser.y"
                        { if ((yyvsp[-1].i_val) >= (yyvsp[-3].i_val)) {
				sqlformaterror(m, SQLSTATE(22003) "Precision(%d) should be less than number of digits(%d)", (yyvsp[-1].i_val), (yyvsp[-3].i_val));
				(yyval.type).type = NULL;
				YYABORT;
			  } else {
			 	sql_find_subtype(&(yyval.type), (yyvsp[-5].sval), (yyvsp[-3].i_val), (yyvsp[-1].i_val));
			  }
			}
#line 15165 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1006: /* data_type: ident_or_uident  */
#line 5286 "sql_parser.y"
                        {
			  sql_type *t = mvc_bind_type(m, (yyvsp[0].sval));
			  if (!t) {
				sqlformaterror(m, SQLSTATE(22000) "Type (%s) unknown", (yyvsp[0].sval));
				(yyval.type).type = NULL;
				YYABORT;
			  } else {
				sql_init_subtype(&(yyval.type), t, 0, 0);
			  }
			}
#line 15180 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1007: /* data_type: ident_or_uident '(' nonzero ')'  */
#line 5298 "sql_parser.y"
                        {
			  sql_type *t = mvc_bind_type(m, (yyvsp[-3].sval));
			  if (!t) {
				sqlformaterror(m, SQLSTATE(22000) "Type (%s) unknown", (yyvsp[-3].sval));
				(yyval.type).type = NULL;
				YYABORT;
			  } else {
				sql_init_subtype(&(yyval.type), t, (yyvsp[-1].i_val), 0);
			  }
			}
#line 15195 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1008: /* data_type: GEOMETRY  */
#line 5308 "sql_parser.y"
           {
		if (!sql_find_subtype(&(yyval.type), "geometry", 0, 0 )) {
			sqlformaterror(m, "%s", SQLSTATE(22000) "Type (geometry) unknown");
			(yyval.type).type = NULL;
			YYABORT;
		}
	}
#line 15207 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1009: /* data_type: GEOMETRY '(' subgeometry_type ')'  */
#line 5315 "sql_parser.y"
                                    {
		int geoSubType = (yyvsp[-1].i_val); 

		if(geoSubType == 0) {
			(yyval.type).type = NULL;
			YYABORT;
		} else if (!sql_find_subtype(&(yyval.type), "geometry", geoSubType, 0 )) {
			sqlformaterror(m, SQLSTATE(22000) "Type (%s) unknown", (yyvsp[-3].sval));
			(yyval.type).type = NULL;
			YYABORT;
		}
		
	}
#line 15225 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1010: /* data_type: GEOMETRY '(' subgeometry_type ',' intval ')'  */
#line 5328 "sql_parser.y"
                                               {
		int geoSubType = (yyvsp[-3].i_val); 
		int srid = (yyvsp[-1].i_val); 

		if(geoSubType == 0) {
			(yyval.type).type = NULL;
			YYABORT;
		} else if (!sql_find_subtype(&(yyval.type), "geometry", geoSubType, srid )) {
			sqlformaterror(m, SQLSTATE(22000) "Type (%s) unknown", (yyvsp[-5].sval));
			(yyval.type).type = NULL;
			YYABORT;
		}
	}
#line 15243 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1011: /* data_type: GEOMETRYA  */
#line 5341 "sql_parser.y"
            {
		if (!sql_find_subtype(&(yyval.type), "geometrya", 0, 0 )) {
			sqlformaterror(m, "%s", SQLSTATE(22000) "Type (geometrya) unknown");
			(yyval.type).type = NULL;
			YYABORT;
		}
	}
#line 15255 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1012: /* data_type: GEOMETRYSUBTYPE  */
#line 5348 "sql_parser.y"
                  {
	int geoSubType = find_subgeometry_type(m, (yyvsp[0].sval));

	if(geoSubType == 0) {
		(yyval.type).type = NULL;
		sqlformaterror(m, SQLSTATE(22000) "Type (%s) unknown", (yyvsp[0].sval));
		YYABORT;
	} else if (geoSubType == -1) {
		(yyval.type).type = NULL;
		sqlformaterror(m, SQLSTATE(HY013) "%s", "allocation failure");
		YYABORT;
	}  else if (!sql_find_subtype(&(yyval.type), "geometry", geoSubType, 0 )) {
		sqlformaterror(m, SQLSTATE(22000) "Type (%s) unknown", (yyvsp[0].sval));
		(yyval.type).type = NULL;
		YYABORT;
	}
}
#line 15277 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1013: /* subgeometry_type: GEOMETRYSUBTYPE  */
#line 5368 "sql_parser.y"
                  {
	int subtype = find_subgeometry_type(m, (yyvsp[0].sval));
	char* geoSubType = (yyvsp[0].sval);

	if(subtype == 0) {
		sqlformaterror(m, SQLSTATE(22000) "Type (%s) unknown", geoSubType);
		YYABORT;
	} else if(subtype == -1) {
		sqlformaterror(m, SQLSTATE(HY013) "%s", "allocation failure");
		YYABORT;
	} 
	(yyval.i_val) = subtype;	
}
#line 15295 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1014: /* subgeometry_type: string  */
#line 5381 "sql_parser.y"
         {
	int subtype = find_subgeometry_type(m, (yyvsp[0].sval));
	char* geoSubType = (yyvsp[0].sval);

	if(subtype == 0) {
		sqlformaterror(m, SQLSTATE(22000) "Type (%s) unknown", geoSubType);
		YYABORT;
	} else if (subtype == -1) {
		sqlformaterror(m, SQLSTATE(HY013) "%s", "allocation failure");
		YYABORT;
	} 
	(yyval.i_val) = subtype;	
}
#line 15313 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1015: /* type_alias: ALIAS  */
#line 5398 "sql_parser.y"
        { 	char *t = sql_bind_alias((yyvsp[0].sval));
	  	if (!t) {
			sqlformaterror(m, SQLSTATE(22000) "Type (%s) unknown", (yyvsp[0].sval));
			(yyval.sval) = NULL;
			YYABORT;
		}
		(yyval.sval) = t;
	}
#line 15326 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1016: /* varchar: VARCHAR  */
#line 5409 "sql_parser.y"
                                        { (yyval.sval) = (yyvsp[0].sval); }
#line 15332 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1017: /* varchar: CHARACTER VARYING  */
#line 5410 "sql_parser.y"
                                        { (yyval.sval) = (yyvsp[-1].sval); }
#line 15338 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1018: /* clob: CLOB  */
#line 5414 "sql_parser.y"
                                        { (yyval.sval) = (yyvsp[0].sval); }
#line 15344 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1019: /* clob: sqlTEXT  */
#line 5415 "sql_parser.y"
                                        { (yyval.sval) = (yyvsp[0].sval); }
#line 15350 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1020: /* clob: CHARACTER LARGE OBJECT  */
#line 5416 "sql_parser.y"
                                        { (yyval.sval) = (yyvsp[-2].sval); }
#line 15356 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1021: /* blob: sqlBLOB  */
#line 5419 "sql_parser.y"
                                        { (yyval.sval) = (yyvsp[0].sval); }
#line 15362 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1022: /* blob: BINARY LARGE OBJECT  */
#line 5420 "sql_parser.y"
                                        { (yyval.sval) = (yyvsp[-2].sval); }
#line 15368 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1025: /* calc_restricted_ident: IDENT  */
#line 5428 "sql_parser.y"
                { (yyval.sval) = (yyvsp[0].sval); }
#line 15374 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1026: /* calc_restricted_ident: UIDENT opt_uescape  */
#line 5430 "sql_parser.y"
                { (yyval.sval) = uescape_xform((yyvsp[-1].sval), (yyvsp[0].sval)); }
#line 15380 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1027: /* calc_restricted_ident: aTYPE  */
#line 5431 "sql_parser.y"
                { (yyval.sval) = (yyvsp[0].sval); }
#line 15386 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1028: /* calc_restricted_ident: ALIAS  */
#line 5432 "sql_parser.y"
                { (yyval.sval) = (yyvsp[0].sval); }
#line 15392 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1029: /* calc_restricted_ident: RANK  */
#line 5433 "sql_parser.y"
                { (yyval.sval) = (yyvsp[0].sval); }
#line 15398 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1030: /* restricted_ident: calc_restricted_ident  */
#line 5438 "sql_parser.y"
        {
		(yyval.sval) = (yyvsp[0].sval);
		if (!(yyvsp[0].sval) || _strlen((yyvsp[0].sval)) == 0) {
			sqlformaterror(m, SQLSTATE(42000) "An identifier cannot be empty");
			YYABORT;
		}
	}
#line 15410 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1031: /* calc_ident: IDENT  */
#line 5448 "sql_parser.y"
                { (yyval.sval) = (yyvsp[0].sval); }
#line 15416 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1032: /* calc_ident: UIDENT opt_uescape  */
#line 5450 "sql_parser.y"
                { (yyval.sval) = uescape_xform((yyvsp[-1].sval), (yyvsp[0].sval)); }
#line 15422 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1033: /* calc_ident: aTYPE  */
#line 5451 "sql_parser.y"
                { (yyval.sval) = (yyvsp[0].sval); }
#line 15428 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1034: /* calc_ident: ALIAS  */
#line 5452 "sql_parser.y"
                { (yyval.sval) = (yyvsp[0].sval); }
#line 15434 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1035: /* calc_ident: RANK  */
#line 5453 "sql_parser.y"
                { (yyval.sval) = (yyvsp[0].sval); }
#line 15440 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1037: /* ident: calc_ident  */
#line 5459 "sql_parser.y"
        {
		(yyval.sval) = (yyvsp[0].sval);
		if (!(yyvsp[0].sval) || _strlen((yyvsp[0].sval)) == 0) {
			sqlformaterror(m, SQLSTATE(42000) "An identifier cannot be empty");
			YYABORT;
		}
	}
#line 15452 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1038: /* non_reserved_word: AS  */
#line 5469 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "as"); }
#line 15458 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1039: /* non_reserved_word: AUTHORIZATION  */
#line 5470 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "authorization"); }
#line 15464 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1040: /* non_reserved_word: COLUMN  */
#line 5471 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "column"); }
#line 15470 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1041: /* non_reserved_word: CYCLE  */
#line 5472 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "cycle"); }
#line 15476 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1042: /* non_reserved_word: sqlDATE  */
#line 5473 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "date"); }
#line 15482 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1043: /* non_reserved_word: DEALLOCATE  */
#line 5474 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "deallocate"); }
#line 15488 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1044: /* non_reserved_word: DISTINCT  */
#line 5475 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "distinct"); }
#line 15494 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1045: /* non_reserved_word: EXEC  */
#line 5476 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "exec"); }
#line 15500 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1046: /* non_reserved_word: EXECUTE  */
#line 5477 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "execute"); }
#line 15506 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1047: /* non_reserved_word: FILTER  */
#line 5478 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "filter"); }
#line 15512 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1048: /* non_reserved_word: INTERVAL  */
#line 5479 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "interval"); }
#line 15518 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1049: /* non_reserved_word: LANGUAGE  */
#line 5480 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "language"); }
#line 15524 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1050: /* non_reserved_word: LARGE  */
#line 5481 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "large"); }
#line 15530 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1051: /* non_reserved_word: MATCH  */
#line 5482 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "match"); }
#line 15536 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1052: /* non_reserved_word: NO  */
#line 5483 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "no"); }
#line 15542 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1053: /* non_reserved_word: PRECISION  */
#line 5484 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "precision"); }
#line 15548 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1054: /* non_reserved_word: PREPARE  */
#line 5485 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "prepare"); }
#line 15554 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1055: /* non_reserved_word: RELEASE  */
#line 5486 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "release"); }
#line 15560 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1056: /* non_reserved_word: ROW  */
#line 5487 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "row"); }
#line 15566 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1057: /* non_reserved_word: START  */
#line 5488 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "start"); }
#line 15572 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1058: /* non_reserved_word: TABLE  */
#line 5489 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "table"); }
#line 15578 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1059: /* non_reserved_word: TIME  */
#line 5490 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "time"); }
#line 15584 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1060: /* non_reserved_word: TIMESTAMP  */
#line 5491 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "timestamp"); }
#line 15590 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1061: /* non_reserved_word: UESCAPE  */
#line 5492 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "uescape"); }
#line 15596 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1062: /* non_reserved_word: VALUE  */
#line 5493 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "value"); }
#line 15602 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1063: /* non_reserved_word: ACTION  */
#line 5495 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "action"); }
#line 15608 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1064: /* non_reserved_word: ANALYZE  */
#line 5496 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "analyze"); }
#line 15614 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1065: /* non_reserved_word: AUTO_COMMIT  */
#line 5497 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "auto_commit"); }
#line 15620 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1066: /* non_reserved_word: BIG  */
#line 5498 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "big"); }
#line 15626 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1067: /* non_reserved_word: CACHE  */
#line 5499 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "cache"); }
#line 15632 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1068: /* non_reserved_word: CENTURY  */
#line 5500 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "century"); }
#line 15638 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1069: /* non_reserved_word: CLIENT  */
#line 5501 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "client"); }
#line 15644 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1070: /* non_reserved_word: COMMENT  */
#line 5502 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "comment"); }
#line 15650 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1071: /* non_reserved_word: DATA  */
#line 5503 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "data"); }
#line 15656 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1072: /* non_reserved_word: SQL_DEBUG  */
#line 5504 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "debug"); }
#line 15662 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1073: /* non_reserved_word: DECADE  */
#line 5505 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "decade"); }
#line 15668 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1074: /* non_reserved_word: DIAGNOSTICS  */
#line 5506 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "diagnostics"); }
#line 15674 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1075: /* non_reserved_word: DOW  */
#line 5507 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "dow"); }
#line 15680 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1076: /* non_reserved_word: DOY  */
#line 5508 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "doy"); }
#line 15686 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1077: /* non_reserved_word: ENDIAN  */
#line 5509 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "endian"); }
#line 15692 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1078: /* non_reserved_word: EPOCH  */
#line 5510 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "epoch"); }
#line 15698 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1079: /* non_reserved_word: SQL_EXPLAIN  */
#line 5511 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "explain"); }
#line 15704 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1080: /* non_reserved_word: FIRST  */
#line 5512 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "first"); }
#line 15710 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1081: /* non_reserved_word: GEOMETRY  */
#line 5513 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "geometry"); }
#line 15716 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1082: /* non_reserved_word: IMPRINTS  */
#line 5514 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "imprints"); }
#line 15722 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1083: /* non_reserved_word: INCREMENT  */
#line 5515 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "increment"); }
#line 15728 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1084: /* non_reserved_word: KEY  */
#line 5516 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "key"); }
#line 15734 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1085: /* non_reserved_word: LAST  */
#line 5517 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "last"); }
#line 15740 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1086: /* non_reserved_word: LEVEL  */
#line 5518 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "level"); }
#line 15746 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1087: /* non_reserved_word: LITTLE  */
#line 5519 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "little"); }
#line 15752 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1088: /* non_reserved_word: MAX_MEMORY  */
#line 5520 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "max_memory"); }
#line 15758 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1089: /* non_reserved_word: MAXVALUE  */
#line 5521 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "maxvalue"); }
#line 15764 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1090: /* non_reserved_word: MAX_WORKERS  */
#line 5522 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "max_workers"); }
#line 15770 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1091: /* non_reserved_word: MINMAX  */
#line 5523 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "minmax"); }
#line 15776 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1092: /* non_reserved_word: MINVALUE  */
#line 5524 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "minvalue"); }
#line 15782 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1093: /* non_reserved_word: sqlNAME  */
#line 5525 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "name"); }
#line 15788 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1094: /* non_reserved_word: NATIVE  */
#line 5526 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "native"); }
#line 15794 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1095: /* non_reserved_word: NULLS  */
#line 5527 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "nulls"); }
#line 15800 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1096: /* non_reserved_word: OBJECT  */
#line 5528 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "object"); }
#line 15806 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1097: /* non_reserved_word: OPTIMIZER  */
#line 5529 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "optimizer"); }
#line 15812 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1098: /* non_reserved_word: OPTIONS  */
#line 5530 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "options"); }
#line 15818 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1099: /* non_reserved_word: PASSWORD  */
#line 5531 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "password"); }
#line 15824 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1100: /* non_reserved_word: PATH  */
#line 5532 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "path"); }
#line 15830 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1101: /* non_reserved_word: SQL_PLAN  */
#line 5533 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "plan"); }
#line 15836 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1102: /* non_reserved_word: PREP  */
#line 5534 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "prep"); }
#line 15842 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1103: /* non_reserved_word: PRIVILEGES  */
#line 5535 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "privileges"); }
#line 15848 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1104: /* non_reserved_word: QUARTER  */
#line 5536 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "quarter"); }
#line 15854 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1105: /* non_reserved_word: REPLACE  */
#line 5537 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "replace"); }
#line 15860 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1106: /* non_reserved_word: ROLE  */
#line 5538 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "role"); }
#line 15866 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1107: /* non_reserved_word: SCHEMA  */
#line 5539 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "schema"); }
#line 15872 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1108: /* non_reserved_word: SERVER  */
#line 5540 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "server"); }
#line 15878 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1109: /* non_reserved_word: sqlSESSION  */
#line 5541 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "session"); }
#line 15884 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1110: /* non_reserved_word: sqlSIZE  */
#line 5542 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "size"); }
#line 15890 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1111: /* non_reserved_word: STATEMENT  */
#line 5543 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "statement"); }
#line 15896 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1112: /* non_reserved_word: STORAGE  */
#line 5544 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "storage"); }
#line 15902 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1113: /* non_reserved_word: TEMP  */
#line 5545 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "temp"); }
#line 15908 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1114: /* non_reserved_word: TEMPORARY  */
#line 5546 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "temporary"); }
#line 15914 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1115: /* non_reserved_word: sqlTEXT  */
#line 5547 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "text"); }
#line 15920 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1116: /* non_reserved_word: SQL_TRACE  */
#line 5548 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "trace"); }
#line 15926 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1117: /* non_reserved_word: TYPE  */
#line 5549 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "type"); }
#line 15932 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1118: /* non_reserved_word: UNLOGGED  */
#line 5550 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "unlogged"); }
#line 15938 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1119: /* non_reserved_word: WEEK  */
#line 5551 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "week"); }
#line 15944 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1120: /* non_reserved_word: ZONE  */
#line 5552 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "zone"); }
#line 15950 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1121: /* non_reserved_word: ABSENT  */
#line 5555 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "absent"); }
#line 15956 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1122: /* non_reserved_word: ACCORDING  */
#line 5556 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "according"); }
#line 15962 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1123: /* non_reserved_word: CONTENT  */
#line 5557 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "content"); }
#line 15968 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1124: /* non_reserved_word: DOCUMENT  */
#line 5558 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "document"); }
#line 15974 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1125: /* non_reserved_word: ELEMENT  */
#line 5559 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "element"); }
#line 15980 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1126: /* non_reserved_word: EMPTY  */
#line 5560 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "empty"); }
#line 15986 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1127: /* non_reserved_word: ID  */
#line 5561 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "id"); }
#line 15992 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1128: /* non_reserved_word: LOCATION  */
#line 5562 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "location"); }
#line 15998 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1129: /* non_reserved_word: NAMESPACE  */
#line 5563 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "namespace"); }
#line 16004 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1130: /* non_reserved_word: NIL  */
#line 5564 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "nil"); }
#line 16010 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1131: /* non_reserved_word: PASSING  */
#line 5565 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "passing"); }
#line 16016 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1132: /* non_reserved_word: REF  */
#line 5566 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "ref"); }
#line 16022 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1133: /* non_reserved_word: RETURNING  */
#line 5567 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "returning"); }
#line 16028 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1134: /* non_reserved_word: STRIP  */
#line 5568 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "strip"); }
#line 16034 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1135: /* non_reserved_word: URI  */
#line 5569 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "uri"); }
#line 16040 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1136: /* non_reserved_word: WHITESPACE  */
#line 5570 "sql_parser.y"
                { (yyval.sval) = sa_strdup(SA, "whitespace"); }
#line 16046 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1137: /* lngval: sqlINT  */
#line 5575 "sql_parser.y"
                {
		  char *end = NULL, *s = (yyvsp[0].sval);
		  int l = _strlen(s);
		  // errno might be non-zero due to other people's code
		  errno = 0;
		  if (l <= 19) {
		  	(yyval.l_val) = strtoll(s,&end,10);
		  } else {
			(yyval.l_val) = 0;
		  }
		  if (s+l != end || errno == ERANGE) {
			errno = 0;
			sqlformaterror(m, SQLSTATE(22003) "Integer value too large or not a number (%s)", (yyvsp[0].sval));
			(yyval.l_val) = 0;
			YYABORT;
		  }
		}
#line 16068 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1138: /* ident_or_uident: IDENT  */
#line 5594 "sql_parser.y"
                                { (yyval.sval) = (yyvsp[0].sval); }
#line 16074 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1139: /* ident_or_uident: UIDENT opt_uescape  */
#line 5595 "sql_parser.y"
                                { (yyval.sval) = uescape_xform((yyvsp[-1].sval), (yyvsp[0].sval)); }
#line 16080 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1140: /* intval: sqlINT  */
#line 5600 "sql_parser.y"
                {
		  char *end = NULL, *s = (yyvsp[0].sval);
		  int l = _strlen(s);
		  // errno might be non-zero due to other people's code
		  errno = 0;
		  if (l <= 10) {
		  	(yyval.i_val) = strtol(s,&end,10);
		  } else {
			(yyval.i_val) = 0;
		  }
		  if (s+l != end || errno == ERANGE) {
			errno = 0;
			sqlformaterror(m, SQLSTATE(22003) "Integer value too large or not a number (%s)", (yyvsp[0].sval));
			(yyval.i_val) = 0;
			YYABORT;
		  }
		}
#line 16102 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1141: /* opt_uescape: %empty  */
#line 5620 "sql_parser.y"
                { (yyval.sval) = "\\"; }
#line 16108 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1142: /* opt_uescape: UESCAPE string  */
#line 5622 "sql_parser.y"
                { char *s = (yyvsp[0].sval);
		  if (strlen(s) != 1 || strchr("\"'0123456789abcdefABCDEF+ \t\n\r\f", *s) != NULL) {
			sqlformaterror(m, SQLSTATE(22019) "%s", "UESCAPE must be one character");
			(yyval.sval) = NULL;
			YYABORT;
		  } else {
			(yyval.sval) = s;
		  }
		}
#line 16122 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1143: /* ustring: USTRING  */
#line 5634 "sql_parser.y"
                { (yyval.sval) = (yyvsp[0].sval); }
#line 16128 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1144: /* ustring: USTRING sstring  */
#line 5636 "sql_parser.y"
                { (yyval.sval) = sa_strconcat(SA, (yyvsp[-1].sval), (yyvsp[0].sval)); }
#line 16134 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1145: /* blobstring: XSTRING  */
#line 5641 "sql_parser.y"
                { (yyval.sval) = (yyvsp[0].sval); }
#line 16140 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1146: /* blobstring: XSTRING sstring  */
#line 5643 "sql_parser.y"
                { (yyval.sval) = sa_strconcat(SA, (yyvsp[-1].sval), (yyvsp[0].sval)); }
#line 16146 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1147: /* sstring: STRING  */
#line 5648 "sql_parser.y"
                { (yyval.sval) = (yyvsp[0].sval); }
#line 16152 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1148: /* sstring: STRING sstring  */
#line 5650 "sql_parser.y"
                { (yyval.sval) = sa_strconcat(SA, (yyvsp[-1].sval), (yyvsp[0].sval)); }
#line 16158 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1149: /* string: sstring  */
#line 5654 "sql_parser.y"
                { (yyval.sval) = (yyvsp[0].sval); }
#line 16164 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1150: /* string: ustring opt_uescape  */
#line 5656 "sql_parser.y"
                { (yyval.sval) = uescape_xform((yyvsp[-1].sval), (yyvsp[0].sval));
		  if ((yyval.sval) == NULL) {
			sqlformaterror(m, SQLSTATE(22019) "%s", "Bad Unicode string");
			YYABORT;
		  }
		}
#line 16175 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1151: /* exec: execute exec_ref  */
#line 5666 "sql_parser.y"
                {
		  m->emod |= mod_exec;
		  (yyval.sym) = _symbol_create_symbol(SQL_CALL, (yyvsp[0].sym)); }
#line 16183 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1152: /* dealloc_ref: posint  */
#line 5672 "sql_parser.y"
          { (yyval.i_val) = (yyvsp[0].i_val); }
#line 16189 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1153: /* dealloc_ref: ALL  */
#line 5673 "sql_parser.y"
          { (yyval.i_val) = -1; }
#line 16195 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1154: /* dealloc: deallocate opt_prepare dealloc_ref  */
#line 5678 "sql_parser.y"
                {
		  m->emode = m_deallocate;
		  (yyval.sym) = _newAtomNode(atom_int(SA, sql_bind_localtype("int"), (yyvsp[0].i_val))); }
#line 16203 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1155: /* exec_ref: posint '(' ')'  */
#line 5685 "sql_parser.y"
        { dlist *l = L();
  	  append_int(l, (yyvsp[-2].i_val));
	  append_int(l, FALSE); /* ignore distinct */
  	  append_list(l, NULL);
	  (yyval.sym) = _symbol_create_list( SQL_NOP, l ); }
#line 16213 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1156: /* exec_ref: posint '(' value_commalist ')'  */
#line 5691 "sql_parser.y"
        { dlist *l = L();
  	  append_int(l, (yyvsp[-3].i_val));
  	  append_int(l, FALSE); /* ignore distinct */
  	  append_list(l, (yyvsp[-1].l));
	  (yyval.sym) = _symbol_create_list( SQL_NOP, l ); }
#line 16223 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1157: /* opt_path_specification: %empty  */
#line 5706 "sql_parser.y"
                        { (yyval.sym) = NULL; }
#line 16229 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1159: /* path_specification: PATH schema_name_list  */
#line 5711 "sql_parser.y"
                                { (yyval.sym) = _symbol_create_list( SQL_PATH, (yyvsp[0].l)); }
#line 16235 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1161: /* comment_on_statement: COMMENT ON catalog_object IS string  */
#line 5718 "sql_parser.y"
        { dlist *l = L();
	  append_symbol(l, (yyvsp[-2].sym));
	  append_string(l, (yyvsp[0].sval));
	  (yyval.sym) = _symbol_create_list( SQL_COMMENT, l );
	}
#line 16245 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1162: /* comment_on_statement: COMMENT ON catalog_object IS sqlNULL  */
#line 5724 "sql_parser.y"
        { dlist *l = L();
	  append_symbol(l, (yyvsp[-2].sym));
	  append_string(l, NULL);
	  (yyval.sym) = _symbol_create_list( SQL_COMMENT, l );
	}
#line 16255 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1163: /* catalog_object: SCHEMA ident  */
#line 5732 "sql_parser.y"
                       { (yyval.sym) = _symbol_create( SQL_SCHEMA, (yyvsp[0].sval) ); }
#line 16261 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1164: /* catalog_object: TABLE qname  */
#line 5733 "sql_parser.y"
                      { (yyval.sym) = _symbol_create_list( SQL_TABLE, (yyvsp[0].l) ); }
#line 16267 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1165: /* catalog_object: VIEW qname  */
#line 5734 "sql_parser.y"
                     { (yyval.sym) = _symbol_create_list( SQL_VIEW, (yyvsp[0].l) ); }
#line 16273 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1166: /* catalog_object: COLUMN ident '.' ident  */
#line 5736 "sql_parser.y"
        { dlist *l = L();
	  append_string(l, (yyvsp[-2].sval));
	  append_string(l, (yyvsp[0].sval));
	  (yyval.sym) = _symbol_create_list( SQL_COLUMN, l );
	}
#line 16283 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1167: /* catalog_object: COLUMN ident '.' ident '.' ident  */
#line 5742 "sql_parser.y"
        { dlist *l = L();
	  append_string(l, (yyvsp[-4].sval));
	  append_string(l, (yyvsp[-2].sval));
	  append_string(l, (yyvsp[0].sval));
	  (yyval.sym) = _symbol_create_list( SQL_COLUMN, l );
	}
#line 16294 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1168: /* catalog_object: INDEX qname  */
#line 5748 "sql_parser.y"
                      { (yyval.sym) = _symbol_create_list( SQL_INDEX, (yyvsp[0].l) ); }
#line 16300 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1169: /* catalog_object: SEQUENCE qname  */
#line 5749 "sql_parser.y"
                         { (yyval.sym) = _symbol_create_list( SQL_SEQUENCE, (yyvsp[0].l) ); }
#line 16306 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1170: /* catalog_object: routine_designator  */
#line 5750 "sql_parser.y"
                             { (yyval.sym) = _symbol_create_list( SQL_ROUTINE, (yyvsp[0].l) ); }
#line 16312 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1172: /* XML_value_expression_list: XML_value_expression  */
#line 5759 "sql_parser.y"
                { (yyval.l) = append_symbol(L(), (yyvsp[0].sym)); }
#line 16318 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1173: /* XML_value_expression_list: XML_value_expression_list ',' XML_value_expression  */
#line 5761 "sql_parser.y"
                { (yyval.l) = append_symbol((yyvsp[-2].l), (yyvsp[0].sym)); }
#line 16324 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1185: /* XML_comment: XMLCOMMENT '(' value_exp opt_XML_returning_clause ')'  */
#line 5783 "sql_parser.y"
        { dlist *l = L();
	  append_symbol(l, (yyvsp[-2].sym));
	  append_int(l, (yyvsp[-1].i_val));
	  (yyval.sym) = _symbol_create_list( SQL_XMLCOMMENT, l); }
#line 16333 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1186: /* XML_concatenation: XMLCONCAT '(' XML_value_expression_list opt_XML_returning_clause ')'  */
#line 5791 "sql_parser.y"
        { dlist *l = L();
	  append_list(l, (yyvsp[-2].l));
	  append_int(l, (yyvsp[-1].i_val));
	  (yyval.sym) = _symbol_create_list( SQL_XMLCONCAT, l); }
#line 16342 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1187: /* XML_document: XMLDOCUMENT '(' XML_value_expression opt_XML_returning_clause ')'  */
#line 5799 "sql_parser.y"
        { dlist *l = L();
	  append_symbol(l, (yyvsp[-2].sym));
	  append_int(l, (yyvsp[-1].i_val));
	  (yyval.sym) = _symbol_create_list( SQL_XMLDOCUMENT, l); }
#line 16351 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1188: /* XML_element: XMLELEMENT '(' sqlNAME XML_element_name opt_comma_XML_namespace_declaration_attributes_element_content opt_XML_returning_clause ')'  */
#line 5809 "sql_parser.y"
        { dlist *l = L();
	  append_string(l, (yyvsp[-3].sval));
	  append_list(l, (yyvsp[-2].l));
	  append_int(l, (yyvsp[-1].i_val));
	  (yyval.sym) = _symbol_create_list( SQL_XMLELEMENT, l);
	}
#line 16362 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1189: /* opt_comma_XML_namespace_declaration_attributes_element_content: %empty  */
#line 5819 "sql_parser.y"
        { (yyval.l) = NULL; }
#line 16368 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1190: /* opt_comma_XML_namespace_declaration_attributes_element_content: ',' XML_namespace_declaration  */
#line 5821 "sql_parser.y"
        { (yyval.l) = append_symbol(L(), (yyvsp[0].sym));
	  (yyval.l) = append_symbol((yyval.l), NULL);
	  (yyval.l) = append_list((yyval.l), NULL); }
#line 16376 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1191: /* opt_comma_XML_namespace_declaration_attributes_element_content: ',' XML_namespace_declaration ',' XML_attributes  */
#line 5825 "sql_parser.y"
        { (yyval.l) = append_symbol(L(), (yyvsp[-2].sym));
	  (yyval.l) = append_symbol((yyval.l), (yyvsp[0].sym));
	  (yyval.l) = append_list((yyval.l), NULL); }
#line 16384 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1192: /* opt_comma_XML_namespace_declaration_attributes_element_content: ',' XML_namespace_declaration ',' XML_attributes ',' XML_element_content_and_option  */
#line 5829 "sql_parser.y"
        { (yyval.l) = append_symbol(L(), (yyvsp[-4].sym));
	  (yyval.l) = append_symbol((yyval.l), (yyvsp[-2].sym));
	  (yyval.l) = append_list((yyval.l), (yyvsp[0].l)); }
#line 16392 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1193: /* opt_comma_XML_namespace_declaration_attributes_element_content: ',' XML_namespace_declaration ',' XML_element_content_and_option  */
#line 5833 "sql_parser.y"
        { (yyval.l) = append_symbol(L(), (yyvsp[-2].sym));
	  (yyval.l) = append_symbol((yyval.l), NULL);
	  (yyval.l) = append_list((yyval.l), (yyvsp[0].l)); }
#line 16400 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1194: /* opt_comma_XML_namespace_declaration_attributes_element_content: ',' XML_attributes  */
#line 5837 "sql_parser.y"
        { (yyval.l) = append_symbol(L(), NULL);
	  (yyval.l) = append_symbol((yyval.l), (yyvsp[0].sym));
	  (yyval.l) = append_list((yyval.l), NULL); }
#line 16408 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1195: /* opt_comma_XML_namespace_declaration_attributes_element_content: ',' XML_attributes ',' XML_element_content_and_option  */
#line 5841 "sql_parser.y"
        { (yyval.l) = append_symbol(L(), NULL);
	  (yyval.l) = append_symbol((yyval.l), (yyvsp[-2].sym));
	  (yyval.l) = append_list((yyval.l), (yyvsp[0].l)); }
#line 16416 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1196: /* opt_comma_XML_namespace_declaration_attributes_element_content: ',' XML_element_content_and_option  */
#line 5845 "sql_parser.y"
        { (yyval.l) = append_symbol(L(), NULL);
	  (yyval.l) = append_symbol((yyval.l), NULL);
	  (yyval.l) = append_list((yyval.l), (yyvsp[0].l)); }
#line 16424 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1198: /* XML_attributes: XMLATTRIBUTES '(' XML_attribute_list ')'  */
#line 5855 "sql_parser.y"
                                                { (yyval.sym) = (yyvsp[-1].sym); }
#line 16430 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1199: /* XML_attribute_list: XML_attribute  */
#line 5859 "sql_parser.y"
                                                { (yyval.sym) = (yyvsp[0].sym); }
#line 16436 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1200: /* XML_attribute_list: XML_attribute_list ',' XML_attribute  */
#line 5861 "sql_parser.y"
                { dlist *l = L();
		  append_list(l, 
		  	append_string(L(), sa_strdup(SA, "concat")));
	  	  append_symbol(l, (yyvsp[-2].sym));
	  	  append_symbol(l, (yyvsp[0].sym));
	  	  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 16447 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1201: /* XML_attribute: XML_attribute_value opt_XML_attribute_name  */
#line 5871 "sql_parser.y"
        { dlist *l = L();
	  append_string(l, (yyvsp[0].sval));
	  append_symbol(l, (yyvsp[-1].sym));
	  (yyval.sym) = _symbol_create_list( SQL_XMLATTRIBUTE, l ); }
#line 16456 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1202: /* opt_XML_attribute_name: %empty  */
#line 5878 "sql_parser.y"
                                                { (yyval.sval) = NULL; }
#line 16462 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1203: /* opt_XML_attribute_name: AS XML_attribute_name  */
#line 5879 "sql_parser.y"
                                                { (yyval.sval) = (yyvsp[0].sval); }
#line 16468 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1206: /* XML_element_content_and_option: XML_element_content_list opt_XML_content_option  */
#line 5892 "sql_parser.y"
                { (yyval.l) = L();
		  (yyval.l) = append_list((yyval.l), (yyvsp[-1].l));
		  (yyval.l) = append_int((yyval.l), (yyvsp[0].i_val)); 	}
#line 16476 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1207: /* XML_element_content_list: XML_element_content  */
#line 5899 "sql_parser.y"
                { (yyval.l) = append_symbol(L(), (yyvsp[0].sym)); }
#line 16482 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1208: /* XML_element_content_list: XML_element_content_list ',' XML_element_content  */
#line 5901 "sql_parser.y"
                { (yyval.l) = append_symbol((yyvsp[-2].l), (yyvsp[0].sym)); }
#line 16488 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1210: /* opt_XML_content_option: %empty  */
#line 5909 "sql_parser.y"
                                { (yyval.i_val) = 0; }
#line 16494 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1211: /* opt_XML_content_option: OPTION XML_content_option  */
#line 5910 "sql_parser.y"
                                { (yyval.i_val) = (yyvsp[0].i_val); }
#line 16500 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1212: /* XML_content_option: sqlNULL ON sqlNULL  */
#line 5914 "sql_parser.y"
                                { (yyval.i_val) = 0; }
#line 16506 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1213: /* XML_content_option: EMPTY ON sqlNULL  */
#line 5915 "sql_parser.y"
                                { (yyval.i_val) = 1; }
#line 16512 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1214: /* XML_content_option: ABSENT ON sqlNULL  */
#line 5916 "sql_parser.y"
                                { (yyval.i_val) = 2; }
#line 16518 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1215: /* XML_content_option: NIL ON sqlNULL  */
#line 5917 "sql_parser.y"
                                { (yyval.i_val) = 3; }
#line 16524 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1216: /* XML_content_option: NIL ON NO CONTENT  */
#line 5918 "sql_parser.y"
                                { (yyval.i_val) = 4; }
#line 16530 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1217: /* XML_forest: XMLFOREST '(' opt_XML_namespace_declaration_and_comma forest_element_list opt_XML_content_option opt_XML_returning_clause ')'  */
#line 5925 "sql_parser.y"
        { dlist *l = L();
	  append_symbol(l, (yyvsp[-4].sym));
	  append_list(l, (yyvsp[-3].l));
	  append_int(l, (yyvsp[-2].i_val));
	  append_int(l, (yyvsp[-1].i_val));
	  (yyval.sym) = _symbol_create_list( SQL_XMLFOREST, l);
	}
#line 16542 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1218: /* opt_XML_namespace_declaration_and_comma: %empty  */
#line 5935 "sql_parser.y"
                                        { (yyval.sym) = NULL; }
#line 16548 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1219: /* opt_XML_namespace_declaration_and_comma: XML_namespace_declaration ','  */
#line 5936 "sql_parser.y"
                                        { (yyval.sym) = (yyvsp[-1].sym); }
#line 16554 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1220: /* forest_element_list: forest_element  */
#line 5941 "sql_parser.y"
                { (yyval.l) = append_list(L(), (yyvsp[0].l)); }
#line 16560 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1221: /* forest_element_list: forest_element_list ',' forest_element  */
#line 5943 "sql_parser.y"
                { (yyval.l) = append_list((yyvsp[-2].l), (yyvsp[0].l)); }
#line 16566 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1222: /* forest_element: forest_element_value opt_forest_element_name  */
#line 5948 "sql_parser.y"
                { (yyval.l) = append_symbol(L(), (yyvsp[-1].sym));
		  (yyval.l) = append_string((yyval.l), (yyvsp[0].sval)); }
#line 16573 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1223: /* forest_element_value: scalar_exp  */
#line 5953 "sql_parser.y"
                { (yyval.sym) = (yyvsp[0].sym); }
#line 16579 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1224: /* opt_forest_element_name: %empty  */
#line 5957 "sql_parser.y"
                                { (yyval.sval) = NULL; }
#line 16585 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1225: /* opt_forest_element_name: AS forest_element_name  */
#line 5958 "sql_parser.y"
                                { (yyval.sval) = (yyvsp[0].sval); }
#line 16591 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1226: /* forest_element_name: ident  */
#line 5962 "sql_parser.y"
                                { (yyval.sval) = (yyvsp[0].sval); }
#line 16597 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1227: /* XML_parse: XMLPARSE '(' document_or_content value_exp XML_whitespace_option ')'  */
#line 5969 "sql_parser.y"
        { dlist *l = L();
	  append_int(l, (yyvsp[-3].i_val) );
	  append_symbol(l, (yyvsp[-2].sym));
	  append_int(l, (yyvsp[-1].i_val));
	  (yyval.sym) = _symbol_create_list( SQL_XMLPARSE, l); }
#line 16607 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1228: /* XML_whitespace_option: PRESERVE WHITESPACE  */
#line 5976 "sql_parser.y"
                                { (yyval.i_val) = 0; }
#line 16613 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1229: /* XML_whitespace_option: STRIP WHITESPACE  */
#line 5977 "sql_parser.y"
                                { (yyval.i_val) = 1; }
#line 16619 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1230: /* XML_PI: XMLPI '(' sqlNAME XML_PI_target opt_comma_string_value_expression opt_XML_returning_clause ')'  */
#line 5984 "sql_parser.y"
        { dlist *l = L();
	  append_string(l, (yyvsp[-3].sval));
	  append_symbol(l, (yyvsp[-2].sym));
	  append_int(l, (yyvsp[-1].i_val));
	  (yyval.sym) = _symbol_create_list( SQL_XMLPI, l); }
#line 16629 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1232: /* opt_comma_string_value_expression: %empty  */
#line 5996 "sql_parser.y"
                        { (yyval.sym) = NULL; }
#line 16635 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1233: /* opt_comma_string_value_expression: ',' value_exp  */
#line 5998 "sql_parser.y"
                        { (yyval.sym) = (yyvsp[0].sym); }
#line 16641 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1234: /* XML_query: XMLQUERY '(' XQuery_expression opt_XML_query_argument_list opt_XML_returning_clause opt_XML_query_returning_mechanism XML_query_empty_handling_option ')'  */
#line 6009 "sql_parser.y"
        { (yyval.sym) = NULL; }
#line 16647 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1249: /* XML_text: XMLTEXT '(' value_exp opt_XML_returning_clause ')'  */
#line 6055 "sql_parser.y"
        { dlist *l = L();
	  append_symbol(l, (yyvsp[-2].sym));
	  append_int(l, (yyvsp[-1].i_val));
	  (yyval.sym) = _symbol_create_list( SQL_XMLTEXT, l); }
#line 16656 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1250: /* XML_validate: XMLVALIDATE '(' document_or_content_or_sequence XML_value_expression opt_XML_valid_according_to_clause ')'  */
#line 6066 "sql_parser.y"
        { (yyval.sym) = NULL; }
#line 16662 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1252: /* document_or_content_or_sequence: SEQUENCE  */
#line 6071 "sql_parser.y"
                        { (yyval.i_val) = 2; }
#line 16668 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1253: /* document_or_content: DOCUMENT  */
#line 6075 "sql_parser.y"
                        { (yyval.i_val) = 0; }
#line 16674 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1254: /* document_or_content: CONTENT  */
#line 6076 "sql_parser.y"
                        { (yyval.i_val) = 1; }
#line 16680 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1255: /* opt_XML_returning_clause: %empty  */
#line 6080 "sql_parser.y"
                                { (yyval.i_val) = 0; }
#line 16686 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1256: /* opt_XML_returning_clause: RETURNING CONTENT  */
#line 6081 "sql_parser.y"
                                { (yyval.i_val) = 0; }
#line 16692 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1257: /* opt_XML_returning_clause: RETURNING SEQUENCE  */
#line 6082 "sql_parser.y"
                                { (yyval.i_val) = 1; }
#line 16698 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1258: /* XML_namespace_declaration: XMLNAMESPACES '(' XML_namespace_declaration_item_list ')'  */
#line 6097 "sql_parser.y"
                                                                { (yyval.sym) = (yyvsp[-1].sym); }
#line 16704 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1259: /* XML_namespace_declaration_item_list: XML_namespace_declaration_item  */
#line 6101 "sql_parser.y"
                                        { (yyval.sym) = (yyvsp[0].sym); }
#line 16710 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1260: /* XML_namespace_declaration_item_list: XML_namespace_declaration_item_list ',' XML_namespace_declaration_item  */
#line 6103 "sql_parser.y"
                { dlist *l = L();
		  append_list(l, 
		  	append_string(L(), sa_strdup(SA, "concat")));
	  	  append_symbol(l, (yyvsp[-2].sym));
	  	  append_symbol(l, (yyvsp[0].sym));
	  	  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 16721 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1265: /* XML_regular_namespace_declaration_item: XML_namespace_URI AS XML_namespace_prefix  */
#line 6126 "sql_parser.y"
                                { dlist *l = L();
	  			  append_string(l, sa_strconcat(SA, "xmlns:", (yyvsp[0].sval)));
	  			  append_symbol(l, (yyvsp[-2].sym));
	  			  (yyval.sym) = _symbol_create_list( SQL_XMLATTRIBUTE, l ); }
#line 16730 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1266: /* XML_default_namespace_declaration_item: DEFAULT XML_namespace_URI  */
#line 6133 "sql_parser.y"
                                { dlist *l = L();
	  			  append_string(l, sa_strdup(SA, "xmlns" ));
	  			  append_symbol(l, (yyvsp[0].sym));
	  			  (yyval.sym) = _symbol_create_list( SQL_XMLATTRIBUTE, l ); }
#line 16739 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1267: /* XML_default_namespace_declaration_item: NO DEFAULT  */
#line 6137 "sql_parser.y"
                                { (yyval.sym) = NULL; }
#line 16745 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;

  case 1297: /* XML_aggregate: XMLAGG '(' XML_value_expression opt_order_by_clause opt_XML_returning_clause ')'  */
#line 6232 "sql_parser.y"
        { 
          dlist *aggr = L();

          if ((yyvsp[-2].sym)) {
	  	if ((yyvsp[-3].sym) != NULL && (yyvsp[-3].sym)->token == SQL_SELECT) {
			SelectNode *s = (SelectNode*)(yyvsp[-3].sym);
	
			s->orderby = (yyvsp[-2].sym);
	  	} else {
			yyerror(m, "ORDER BY: missing select operator");
			YYABORT;
		}
	  }
	  append_list(aggr, append_string(append_string(L(), "sys"), "xmlagg"));
	  append_int(aggr, FALSE); /* ignore distinct */
	  append_symbol(aggr, (yyvsp[-3].sym));
	  /* int returning not used */
	  (yyval.sym) = _symbol_create_list( SQL_AGGR, aggr);
	}
#line 16769 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"
    break;


#line 16773 "/Users/nikki/Development/dream-hotel/vendor/monetdb/build/sql/server/sql_parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (m, YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, m);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, m);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (m, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, m);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, m);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 6253 "sql_parser.y"

int find_subgeometry_type(mvc *m, char* geoSubType) {
	int subType = 0;
	if(strcmp(geoSubType, "point") == 0 )
		subType = (1 << 2);
	else if(strcmp(geoSubType, "linestring") == 0)
		subType = (2 << 2);
	else if(strcmp(geoSubType, "polygon") == 0)
		subType = (4 << 2);
	else if(strcmp(geoSubType, "multipoint") == 0)
		subType = (5 << 2);
	else if(strcmp(geoSubType, "multilinestring") == 0)
		subType = (6 << 2);
	else if(strcmp(geoSubType, "multipolygon") == 0)
		subType = (7 << 2);
	else if(strcmp(geoSubType, "geometrycollection") == 0)
		subType = (8 << 2);
	else {
		size_t strLength = strlen(geoSubType);
		if(strLength > 0 ) {
			char *typeSubStr = SA_NEW_ARRAY(m->ta, char, strLength);
			char flag = geoSubType[strLength-1]; 

			if (typeSubStr == NULL) {
				return -1;
			}
			memcpy(typeSubStr, geoSubType, strLength-1);
			typeSubStr[strLength-1]='\0';
			if(flag == 'z' || flag == 'm' ) {
				subType = find_subgeometry_type(m, typeSubStr);
				if (subType == -1) {
					return -1;
				}
				if(flag == 'z')
					SET_Z(subType);
				if(flag == 'm')
					SET_M(subType);
			}
		}
	}
	return subType;	
}

char *token2string(tokens token)
{
	switch (token) {
	// Please keep this list sorted for easy of maintenance
#define SQL(TYPE) case SQL_##TYPE : return #TYPE
	SQL(AGGR);
	SQL(ALTER_SEQ);
	SQL(ALTER_TABLE);
	SQL(ALTER_USER);
	SQL(ANALYZE);
	SQL(AND);
	SQL(ASSIGN);
	SQL(ATOM);
	SQL(BETWEEN);
	SQL(BINCOPYFROM);
	SQL(BINCOPYINTO);
	SQL(BINOP);
	SQL(CACHE);
	SQL(CALL);
	SQL(CASE);
	SQL(CAST);
	SQL(CHARSET);
	SQL(CHECK);
	SQL(COALESCE);
	SQL(COLUMN);
	SQL(COLUMN_GROUP);
	SQL(COLUMN_OPTIONS);
	SQL(COMMENT);
	SQL(COMPARE);
	SQL(CONSTRAINT);
	SQL(COPYFROM);
	SQL(COPYLOADER);
	SQL(COPYINTO);
	SQL(CREATE_FUNC);
	SQL(CREATE_INDEX);
	SQL(CREATE_ROLE);
	SQL(CREATE_SCHEMA);
	SQL(CREATE_SEQ);
	SQL(CREATE_TABLE);
	SQL(CREATE_TABLE_LOADER);
	SQL(CREATE_TRIGGER);
	SQL(CREATE_TYPE);
	SQL(CREATE_USER);
	SQL(CREATE_VIEW);
	SQL(CUBE);
	SQL(CURRENT_ROW);
	SQL(CYCLE);
	SQL(DECLARE);
	SQL(DECLARE_TABLE);
	SQL(DEFAULT);
	SQL(DELETE);
	SQL(DROP_COLUMN);
	SQL(DROP_CONSTRAINT);
	SQL(DROP_DEFAULT);
	SQL(DROP_FUNC);
	SQL(DROP_INDEX);
	SQL(DROP_ROLE);
	SQL(DROP_SCHEMA);
	SQL(DROP_SEQ);
	SQL(DROP_TABLE);
	SQL(DROP_TRIGGER);
	SQL(DROP_TYPE);
	SQL(DROP_USER);
	SQL(DROP_VIEW);
	SQL(ELSE);
	SQL(ESCAPE);
	SQL(EXCEPT);
	SQL(EXECUTE);
	SQL(EXISTS);
	SQL(FILTER);
	SQL(FOLLOWING);
	SQL(FOREIGN_KEY);
	SQL(FRAME);
	SQL(FROM);
	SQL(FUNC);
	SQL(GRANT);
	SQL(GRANT_ROLES);
	SQL(GROUPBY);
	SQL(GROUPING_SETS);
	SQL(IDENT);
	SQL(IF);
	SQL(IN);
	SQL(INC);
	SQL(INDEX);
	SQL(INSERT);
	SQL(INTERSECT);
	SQL(IS_NOT_NULL);
	SQL(IS_NULL);
	SQL(JOIN);
	SQL(LIKE);
	SQL(MAXVALUE);
	SQL(MERGE);
	SQL(MERGE_MATCH);
	SQL(MERGE_NO_MATCH);
	SQL(MERGE_PARTITION);
	SQL(MINVALUE);
	SQL(MULSTMT);
	SQL(NAME);
	SQL(NEXT);
	SQL(NOP);
	SQL(NOT);
	SQL(NOT_BETWEEN);
	SQL(NOT_EXISTS);
	SQL(NOT_IN);
	SQL(NOT_LIKE);
	SQL(NOT_NULL);
	SQL(NULL);
	SQL(NULLIF);
	SQL(OP);
	SQL(OR);
	SQL(ORDERBY);
	SQL(PARAMETER);
	SQL(PARTITION_COLUMN);
	SQL(PARTITION_EXPRESSION);
	SQL(PARTITION_LIST);
	SQL(PARTITION_RANGE);
	SQL(PATH);
	SQL(PRECEDING);
	SQL(PREP);
	SQL(PRIMARY_KEY);
	SQL(PW_ENCRYPTED);
	SQL(PW_UNENCRYPTED);
	SQL(RANK);
	SQL(RENAME_COLUMN);
	SQL(RENAME_SCHEMA);
	SQL(RENAME_TABLE);
	SQL(RENAME_USER);
	SQL(RETURN);
	SQL(REVOKE);
	SQL(REVOKE_ROLES);
	SQL(ROLLUP);
	SQL(ROUTINE);
	SQL(SCHEMA);
	SQL(SELECT);
	SQL(SEQUENCE);
	SQL(SET);
	SQL(SET_TABLE_SCHEMA);
	SQL(START);
	SQL(STORAGE);
	SQL(TABLE);
	SQL(TRUNCATE);
	SQL(TYPE);
	SQL(UNION);
	SQL(UNIQUE);
	SQL(UNOP);
	SQL(UPDATE);
	SQL(USING);
	SQL(VALUES);
	SQL(VIEW);
	SQL(WHEN);
	SQL(WHILE);
	SQL(WINDOW);
	SQL(WITH);
	SQL(XMLATTRIBUTE);
	SQL(XMLCOMMENT);
	SQL(XMLCONCAT);
	SQL(XMLDOCUMENT);
	SQL(XMLELEMENT);
	SQL(XMLFOREST);
	SQL(XMLPARSE);
	SQL(XMLPI);
	SQL(XMLTEXT);
#define TR(TYPE) case TR_##TYPE : return #TYPE
	TR(COMMIT);
	TR(MODE);
	TR(RELEASE);
	TR(ROLLBACK);
	TR(SAVEPOINT);
	TR(START);
	// Please keep this list sorted for easy of maintenance
	}
	return "unknown";	/* just needed for broken compilers ! */
}

void *sql_error( mvc * sql, int error_code, char *format, ... )
{
	va_list	ap;

	va_start (ap,format);
	if (sql->errstr[0] == '\0' || error_code == 5 || error_code == ERR_NOTFOUND)
		vsnprintf(sql->errstr, ERRSIZE-1, _(format), ap);
	if (!sql->session->status || error_code == 5 || error_code == ERR_NOTFOUND)
		sql->session->status = -error_code;
	va_end (ap);
	return NULL;
}

static int 
sqlformaterror(mvc * sql, _In_z_ _Printf_format_string_ const char *format, ...)
{
	va_list	ap;
	const char *sqlstate = NULL;
	size_t len = 0;

	va_start (ap,format);
	if (format && strlen(format) > 6 && format[5] == '!') {
		/* sql state provided */
		sqlstate = NULL;
	} else {
		/* default: Syntax error or access rule violation */
		sqlstate = SQLSTATE(42000);
	}
	//assert(sql->scanner.errstr == NULL);
	if (sql->errstr[0] == '\0') {
		if (sqlstate)
			len += snprintf(sql->errstr+len, ERRSIZE-1-len, "%s", sqlstate);
		len += vsnprintf(sql->errstr+len, ERRSIZE-1-len, _(format), ap);
		snprintf(sql->errstr+len, ERRSIZE-1-len, " in: \"%.80s\"\n", QUERY(sql->scanner));
	}
	if (!sql->session->status)
		sql->session->status = -4;
	va_end (ap);
	return 1;
}

static int 
sqlerror(mvc * sql, const char *err)
{
	return sqlformaterror(sql, "%s", err);
}

static void *ma_alloc(sql_allocator *sa, size_t sz)
{
	return sa_alloc(sa, sz);
}
static void ma_free(void *p)
{
	(void)p;
}
