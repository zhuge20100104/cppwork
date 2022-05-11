#include "locale2_/locale2_.h"

#include <gtest/gtest.h>

#include <sstream>

GTEST_TEST(LocaleTests, CompareLocaleAndCountryCodeIos) {
    ASSERT_TRUE(compare_locales_and_country_code_ios());
}

GTEST_TEST(LocaleTests, CompareLocaleAndCountryCodeIosTimeline) {
    ASSERT_TRUE(compare_locales_and_country_code_ios_timeline());
}

GTEST_TEST(LocaleTests, CompareLocaleAndCountryCodeGp) {
    ASSERT_TRUE(compare_locales_and_country_code_gp());
}

GTEST_TEST(LocaleTests, CompareLocaleAndCountryCodeGPTimeline) {
    ASSERT_TRUE(compare_locales_and_country_code_gp_timeline());
}

GTEST_TEST(LocaleTests, CheckLocalesAndCurrencies) {
    ASSERT_TRUE(check_locales_and_currencies());
}

GTEST_TEST(LocaleTest, ReadJsToMap) {
    const std::string currency_sign_map_path = "../data/currency_sign_map.js";
    auto res = read_js_to_map(currency_sign_map_path);
    ASSERT_EQ("$", res["USD"]);
    ASSERT_EQ(173, res.size());

    const std::string currency_name_map_path = "../data/currency_name_map.js";
    auto res_name_map = read_js_to_map(currency_name_map_path);
    ASSERT_EQ("AFN", res_name_map["AF"]);
    ASSERT_EQ(248, res_name_map.size());
}

GTEST_TEST(LocaleTests, GetCountryByLocale) {
    std::string locale = "zh-CN";
    auto country = get_country_by_locale(locale);
    ASSERT_EQ("CN", country);
}


GTEST_TEST(LocaleTests, GetAvailableIosCountries) {
    auto countries = get_available_ios_countries();
    std::stringstream ss {};
    ss << "IOS Countries: " << "\n";
    for(auto&& country: countries) {
        ss << country << ",";
    }
    std::string s = ss.str();
    s = s.substr(0, s.size()-1);
    std::cout << s << std::endl;
}

GTEST_TEST(LocaleTests, GetAvailableGPCountries) {
    auto countries = get_available_gp_countries();
    std::stringstream ss {};
    ss << "GP Countries: " << "\n";
    for(auto&& country: countries) {
        ss << country << ",";
    }
    std::string s = ss.str();
    s = s.substr(0, s.size()-1);
    std::cout << s << std::endl;
}



