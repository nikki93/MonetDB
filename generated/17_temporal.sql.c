unsigned char _17_temporal_sql[883] = {
"create function sys.epoch(sec DECIMAL(18,3)) returns TIMESTAMP WITH TIME ZONE\n"
"	external name mtime.epoch;\n"
"create function sys.epoch(sec INT) returns TIMESTAMP WITH TIME ZONE\n"
"	external name mtime.epoch;\n"
"create function sys.epoch(ts TIMESTAMP WITH TIME ZONE) returns INT\n"
"	external name mtime.epoch;\n"
"grant execute on function sys.epoch (DECIMAL(18,3)) to public;\n"
"grant execute on function sys.epoch (INT) to public;\n"
"grant execute on function sys.epoch (TIMESTAMP WITH TIME ZONE) to public;\n"
"create function sys.date_trunc(txt string, t timestamp)\n"
"returns timestamp\n"
"external name sql.date_trunc;\n"
"grant execute on function sys.date_trunc(string, timestamp) to public;\n"
"create function sys.date_trunc(txt string, t timestamp with time zone)\n"
"returns timestamp with time zone\n"
"external name sql.date_trunc;\n"
"grant execute on function sys.date_trunc(string, timestamp with time zone) to public;\n"
};
#include "monetdb_config.h"
#include "sql_import.h"
#ifdef _MSC_VER
#undef read
#pragma section(".CRT$XCU",read)
#endif
LIB_STARTUP_FUNC(init_17_temporal_sql)
{ sql_register("17_temporal", _17_temporal_sql); }
