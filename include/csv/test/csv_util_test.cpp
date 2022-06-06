#include "csv/csv_util.h"

#include <gtest/gtest.h>

GTEST_TEST(CSVReaderTests, ReadEntity) {
    std::string file_path = "./among-gp.csv";

    auto entities = CSVUtil::read_csv(file_path, "PRODUCT_KEY", "OLD_VALUE",
                                      "NEW_VALUE", "CHANGE_TIME");

    ASSERT_EQ(1, entities.size());
    Entity expectEntity{20600010026980,

                        "gp/20600010026980/"
                        "VHB9bVB8cTcnqwnu0nJqKYbiutRclnbGxTpwnayKB4vMxZj8pk1220"
                        "Rg-6oQ68DwAkqO=s300",

                        "gp/20600010026980/"
                        "8ddL1kuoNUB5vUvgDVjYY3_6HwQcrg1K2fd_R8soD-"
                        "e2QYj8fT9cfhfh3G0hnSruLKec=s300",
                        
                        "2021-07-08 00:00:00.000"};
    ASSERT_EQ(expectEntity.product_id, entities[0].product_id);
    ASSERT_EQ(expectEntity.old_url, entities[0].old_url);
    ASSERT_EQ(expectEntity.new_url, entities[0].new_url);
    ASSERT_EQ(expectEntity.date, entities[0].date);
}