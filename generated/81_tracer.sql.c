unsigned char _81_tracer_sql[1137] = {
"CREATE SCHEMA logging;\n"
"CREATE PROCEDURE logging.flush()\n"
"	EXTERNAL NAME logging.flush;\n"
"CREATE PROCEDURE logging.setcomplevel(comp_id STRING, lvl_id STRING)\n"
"	EXTERNAL NAME logging.setcomplevel;\n"
"CREATE PROCEDURE logging.resetcomplevel(comp_id STRING)\n"
"	EXTERNAL NAME logging.resetcomplevel;\n"
"CREATE PROCEDURE logging.setlayerlevel(layer_id STRING, lvl_id STRING)\n"
"	EXTERNAL NAME logging.setlayerlevel;\n"
"CREATE PROCEDURE logging.resetlayerlevel(layer_id STRING)\n"
"	EXTERNAL NAME logging.resetlayerlevel;\n"
"CREATE PROCEDURE logging.setflushlevel(lvl_id STRING)\n"
"	EXTERNAL NAME logging.setflushlevel;\n"
"CREATE PROCEDURE logging.resetflushlevel()\n"
"	EXTERNAL NAME logging.resetflushlevel;\n"
"CREATE PROCEDURE logging.setadapter(adapter_id STRING)\n"
"	EXTERNAL NAME logging.setadapter;\n"
"CREATE PROCEDURE logging.resetadapter()\n"
"	EXTERNAL NAME logging.resetadapter;\n"
"CREATE FUNCTION logging.compinfo()\n"
"RETURNS TABLE(\n"
"	\"id\" int,\n"
"	\"component\" string,\n"
"	\"log_level\" string\n"
")\n"
"EXTERNAL NAME logging.compinfo;\n"
"GRANT EXECUTE ON FUNCTION logging.compinfo TO public;\n"
"CREATE view logging.compinfo AS SELECT * FROM logging.compinfo();\n"
"GRANT SELECT ON logging.compinfo TO public;\n"
};
#include "monetdb_config.h"
#include "sql_import.h"
#ifdef _MSC_VER
#undef read
#pragma section(".CRT$XCU",read)
#endif
LIB_STARTUP_FUNC(init_81_tracer_sql)
{ sql_register("81_tracer", _81_tracer_sql); }
