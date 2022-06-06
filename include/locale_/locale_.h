#ifndef _FREDRIC_LOCALE_H_
#define _FREDRIC_LOCALE_H_

#include <vector>
#include <string>

bool get_and_compare_ios_countries(const std::vector<std::string>& source_locales);

bool get_and_compare_ios_countries_timeline(const std::vector<std::string>& source_locales);

bool get_and_compare_gp_countries(const std::vector<std::string>& source_locales);

bool get_and_compare_gp_countries_timeline(const std::vector<std::string>& source_locales);


#endif