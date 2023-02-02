unsigned char _42_md5sum_sql[121] = {
"create function sys.md5(v string)\n"
"returns string external name clients.md5sum;\n"
"grant execute on function md5 to public;\n"
};
#include "monetdb_config.h"
#include "sql_import.h"
#ifdef _MSC_VER
#undef read
#pragma section(".CRT$XCU",read)
#endif
LIB_STARTUP_FUNC(init_42_md5sum_sql)
{ sql_register("42_md5sum", _42_md5sum_sql); }
