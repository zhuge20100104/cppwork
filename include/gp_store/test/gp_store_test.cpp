#include "gp_store/gp_store_opener.h"

#include <gtest/gtest.h>

GTEST_TEST(GPStoreTests, ReadAllLanguageCode) {
    gp_store_opener op;
    auto lang_codes = op.read_all_language_code();
    ASSERT_EQ(65, lang_codes.size());
}

GTEST_TEST(GPStoreTests, GetCountries) {
    gp_store_opener op;
    auto lang_codes = op.read_all_language_code();
    std::vector<std::string> failed_countries{};
    for(auto&& lang_code: lang_codes) {
        std::cout << "Checking [" << lang_code << " ]..." << std::endl;
        bool check_gp_res = op.get_a_country(lang_code);
        if(!check_gp_res) {
            std::cout << "Check [" << lang_code << "] failed!" << std::endl; 
            failed_countries.emplace_back(std::move(lang_code));
        }
        
    }
    ASSERT_TRUE(failed_countries.size() == 0);
}