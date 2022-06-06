#ifndef _FREDRIC_ZEPPLIN_MIG_CFG_H_
#define _FREDRIC_ZEPPLIN_MIG_CFG_H_
#include <map>
#include <string>

extern std::string zepplin_js_path;
extern std::string ipynbs_test_path;
extern std::string conn_str;
extern std::string databricks_ws_host;
extern std::string ws_create_dir_url_path;
extern std::string ws_import_url_path;

extern std::map<std::string, std::string> headers;
#endif