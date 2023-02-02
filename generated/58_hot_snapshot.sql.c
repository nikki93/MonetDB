unsigned char _58_hot_snapshot_sql[539] = {
"create procedure sys.hot_snapshot(tarfile string)\n"
"	external name sql.hot_snapshot;\n"
"create procedure sys.hot_snapshot(tarfile string, onserver bool)\n"
"	external name sql.hot_snapshot;\n"
"create user \".snapshot\"\n"
"	with encrypted password '00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000'\n"
"	name 'Snapshot User'\n"
"	schema sys;\n"
"grant execute on procedure sys.hot_snapshot(string) to \".snapshot\";\n"
"grant execute on procedure sys.hot_snapshot(string, bool) to \".snapshot\";\n"
};
#include "monetdb_config.h"
#include "sql_import.h"
#ifdef _MSC_VER
#undef read
#pragma section(".CRT$XCU",read)
#endif
LIB_STARTUP_FUNC(init_58_hot_snapshot_sql)
{ sql_register("58_hot_snapshot", _58_hot_snapshot_sql); }
