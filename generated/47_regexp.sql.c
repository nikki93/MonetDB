unsigned char _47_regexp_sql[434] = {
"create function sys.regexp_replace(ori string, pat string, rep string, flg string)\n"
"returns string external name pcre.replace;\n"
"grant execute on function regexp_replace(string, string, string, string) to public;\n"
"create function sys.regexp_replace(ori string, pat string, rep string)\n"
"returns string\n"
"begin\n"
"    return sys.regexp_replace(ori, pat, rep, '');\n"
"end;\n"
"grant execute on function regexp_replace(string, string, string) to public;\n"
};
#include "monetdb_config.h"
#include "sql_import.h"
#ifdef _MSC_VER
#undef read
#pragma section(".CRT$XCU",read)
#endif
LIB_STARTUP_FUNC(init_47_regexp_sql)
{ sql_register("47_regexp", _47_regexp_sql); }
