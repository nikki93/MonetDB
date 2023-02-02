unsigned char _41_json_hge_sql[156] = {
"create function json.filter(js json, name hugeint)\n"
"returns json external name json.filter;\n"
"GRANT EXECUTE ON FUNCTION json.filter(json, hugeint) TO PUBLIC;\n"
};
#include "monetdb_config.h"
#include "sql_import.h"
#ifdef _MSC_VER
#undef read
#pragma section(".CRT$XCU",read)
#endif
LIB_STARTUP_FUNC(init_41_json_hge_sql)
{ sql_register("41_json_hge", _41_json_hge_sql); }
