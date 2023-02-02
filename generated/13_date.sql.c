unsigned char _13_date_sql[1007] = {
"create function str_to_date(s string, format string) returns date\n"
"	external name mtime.\"str_to_date\";\n"
"create function date_to_str(d date, format string) returns string\n"
"	external name mtime.\"date_to_str\";\n"
"create function str_to_time(s string, format string) returns time with time zone\n"
"	external name mtime.\"str_to_time\";\n"
"create function time_to_str(d time with time zone, format string) returns string\n"
"	external name mtime.\"time_to_str\";\n"
"create function str_to_timestamp(s string, format string) returns timestamp with time zone\n"
"	external name mtime.\"str_to_timestamp\";\n"
"create function timestamp_to_str(d timestamp with time zone, format string) returns string\n"
"	external name mtime.\"timestamp_to_str\";\n"
"grant execute on function str_to_date to public;\n"
"grant execute on function date_to_str to public;\n"
"grant execute on function str_to_time to public;\n"
"grant execute on function time_to_str to public;\n"
"grant execute on function str_to_timestamp to public;\n"
"grant execute on function timestamp_to_str to public;\n"
};
#include "monetdb_config.h"
#include "sql_import.h"
#ifdef _MSC_VER
#undef read
#pragma section(".CRT$XCU",read)
#endif
LIB_STARTUP_FUNC(init_13_date_sql)
{ sql_register("13_date", _13_date_sql); }
