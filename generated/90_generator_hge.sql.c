unsigned char _90_generator_hge_sql[279] = {
"create function sys.generate_series(first hugeint, \"limit\" hugeint)\n"
"returns table (value hugeint)\n"
"external name generator.series;\n"
"create function sys.generate_series(first hugeint, \"limit\" hugeint, stepsize hugeint)\n"
"returns table (value hugeint)\n"
"external name generator.series;\n"
};
#include "monetdb_config.h"
#include "sql_import.h"
#ifdef _MSC_VER
#undef read
#pragma section(".CRT$XCU",read)
#endif
LIB_STARTUP_FUNC(init_90_generator_hge_sql)
{ sql_register("90_generator_hge", _90_generator_hge_sql); }
