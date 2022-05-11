#ifndef _FREDRIC_LOCALE2_H_
#define _FREDRIC_LOCALE2_H_

#include <string>
#include <map>
#include <set>

std::string get_country_by_locale(const std::string& locale);

bool compare_locales_and_country_code_ios();

bool compare_locales_and_country_code_ios_timeline();

bool compare_locales_and_country_code_gp();

bool compare_locales_and_country_code_gp_timeline();

std::map<std::string, std::string> read_js_to_map(const std::string& js_file_name);

bool check_locales_and_currencies();

std::set<std::string> get_available_ios_countries();

std::set<std::string> get_available_gp_countries();
#endif