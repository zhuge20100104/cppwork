#ifndef _FREDRIC_CONFIG_H_
#define _FREDRIC_CONFIG_H_

#include <string>
#include <map>

std::string status_io_host = "api.status.io";

std::string component_list_url =
    "/v2/component/list/60d2e2a46a05640530c4aec9";

std::map<std::string, std::string> headers{
    {"x-api-id", "e3829d61-70f3-4a15-aaf1-e470bf453d0c"},
    {"x-api-key", "4nW0hl2LPbXeWXN2vtw+Z3qCuA4plpSNlHkg/nn4WOmB6apYt8hT3qZA00GWL2lMRCWNN7eTdtrODkgaN9EnDA=="}};

std::string result_file_path = "../yaml/status_io.yaml";

namespace http {
    std::string error_yes = "yes";
    std::string error_no = "no";
};
#endif