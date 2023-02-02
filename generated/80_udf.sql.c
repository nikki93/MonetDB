unsigned char _80_udf_sql[342] = {
"create function reverse(src string)\n"
"returns string external name udf.reverse;\n"
"create function fuse(one tinyint, two tinyint)\n"
"returns smallint external name udf.fuse;\n"
"create function fuse(one smallint, two smallint)\n"
"returns integer external name udf.fuse;\n"
"create function fuse(one integer, two integer)\n"
"returns bigint external name udf.fuse;\n"
};
#include "monetdb_config.h"
#include "sql_import.h"
#ifdef _MSC_VER
#undef read
#pragma section(".CRT$XCU",read)
#endif
LIB_STARTUP_FUNC(init_80_udf_sql)
{ sql_register("80_udf", _80_udf_sql); }
