unsigned char _45_uuid_sql[415] = {
"create type uuid external name uuid;\n"
"create function sys.uuid()\n"
"returns uuid external name uuid.\"new\";\n"
"GRANT EXECUTE ON FUNCTION sys.uuid() TO PUBLIC;\n"
"create function sys.uuid(d int)\n"
"returns uuid external name uuid.\"new\";\n"
"GRANT EXECUTE ON FUNCTION sys.uuid(int) TO PUBLIC;\n"
"create function sys.isaUUID(s string)\n"
"returns boolean external name uuid.\"isaUUID\";\n"
"GRANT EXECUTE ON FUNCTION sys.isaUUID(string) TO PUBLIC;\n"
};
#include "monetdb_config.h"
#include "sql_import.h"
#ifdef _MSC_VER
#undef read
#pragma section(".CRT$XCU",read)
#endif
LIB_STARTUP_FUNC(init_45_uuid_sql)
{ sql_register("45_uuid", _45_uuid_sql); }
