#ifndef _FREDRIC_CHECK_API_H_
#define _FREDRIC_CHECK_API_H_

#include <vector>
#include <string>
const std::string BEARER_TOKEN = "Bearer 0fde144b7a220b7c76fe3077b01c1e231fe738fe";

bool check_top_apps(const std::vector<std::string>& countries);

bool check_v12_app_rank_history(const std::vector<std::string>& countries);

bool check_top_publisher(const std::vector<std::string>& countries);

bool check_publisher_history(const std::vector<std::string>& countries);

bool check_top_apps_mobile(const std::vector<std::string>& countries);

bool check_top_publisher_mobile(const std::vector<std::string>& countries);

bool check_app_rank_history_mobile(const std::vector<std::string>& countries);

bool check_publisher_history_mobile(const std::vector<std::string>& countries);
#endif