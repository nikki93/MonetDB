unsigned char _27_rejects_sql[317] = {
"create function sys.rejects()\n"
"returns table(\n"
"	rowid bigint,\n"
"	fldid int,\n"
"	\"message\" string,\n"
"	\"input\" string\n"
")\n"
"external name sql.copy_rejects;\n"
"grant execute on function rejects to public;\n"
"create view sys.rejects as select * from sys.rejects();\n"
"create procedure sys.clearrejects()\n"
"external name sql.copy_rejects_clear;\n"
};
#include "monetdb_config.h"
#include "sql_import.h"
#ifdef _MSC_VER
#undef read
#pragma section(".CRT$XCU",read)
#endif
LIB_STARTUP_FUNC(init_27_rejects_sql)
{ sql_register("27_rejects", _27_rejects_sql); }
