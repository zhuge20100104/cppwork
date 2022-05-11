#include "utils/zepplin_mig_cfg.h"

std::string zepplin_js_path = "../nbooks";

std::string ipynbs_test_path = "../ipynbs";

std::string conn_str = "dsn=test_odbc;pwd=Lily870104";
std::string databricks_ws_host = "app-annie-p-qa-data-testing.cloud.databricks.com";

std::string ws_create_dir_url_path = "/api/2.0/workspace/mkdirs";
std::string ws_import_url_path = "/api/2.0/workspace/import";

std::map<std::string, std::string> headers {{"Authorization", "Bearer dapi393f6c929d47c6e75b9f21ed1c3b8709"}};