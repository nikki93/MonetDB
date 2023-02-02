unsigned char _80_udf_hge_sql[86] = {
"create function fuse(one bigint, two bigint)\n"
"returns hugeint external name udf.fuse;\n"
};
#include "monetdb_config.h"
#include "sql_import.h"
#ifdef _MSC_VER
#undef read
#pragma section(".CRT$XCU",read)
#endif
LIB_STARTUP_FUNC(init_80_udf_hge_sql)
{ sql_register("80_udf_hge", _80_udf_hge_sql); }
