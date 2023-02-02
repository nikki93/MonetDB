unsigned char _18_index_sql[219] = {
"create procedure sys.createorderindex(sys string, tab string, col string)\n"
"	external name sql.createorderindex;\n"
"create procedure sys.droporderindex(sys string, tab string, col string)\n"
"	external name sql.droporderindex;\n"
};
#include "monetdb_config.h"
#include "sql_import.h"
#ifdef _MSC_VER
#undef read
#pragma section(".CRT$XCU",read)
#endif
LIB_STARTUP_FUNC(init_18_index_sql)
{ sql_register("18_index", _18_index_sql); }
