unsigned char _46_profiler_sql[406] = {
"create schema profiler;\n"
"create procedure profiler.start() external name profiler.\"start\";\n"
"create procedure profiler.stop() external name profiler.stop;\n"
"create procedure profiler.setheartbeat(beat int) external name profiler.setheartbeat;\n"
"create function profiler.getlimit() returns integer external name profiler.getlimit;\n"
"create procedure  profiler.setlimit(lim integer) external name profiler.setlimit;\n"
};
#include "monetdb_config.h"
#include "sql_import.h"
#ifdef _MSC_VER
#undef read
#pragma section(".CRT$XCU",read)
#endif
LIB_STARTUP_FUNC(init_46_profiler_sql)
{ sql_register("46_profiler", _46_profiler_sql); }
