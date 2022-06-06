#include "sf_db2/sf_db2.h"

#include <gtest/gtest.h>

const std::string ConnStr = "dsn=product_odbc;pwd=Lily870104";

GTEST_TEST(SFDBTests, TestExecQuery) {
    auto conn_str = ConnStr;
    auto raw_query =
        "select  product_key,change_time,EVENT_TYPE_NAME, change_column, "
        "old_value, new_value,meta from "
        "AA_INTELLIGENCE_PRODUCTION.ADL_MASTER.dim_event_service_v1 where  "
        "event_type_name='screenshot_change' and product_key=20600000009072 "
        "order by change_time desc limit 2;";
    sf_connection sf{conn_str};
    auto res = sf.exec_raw_query(raw_query);
    ASSERT_EQ(2, res.affected_rows());

    const auto columns = res.columns();
    for (short i = 0; i < columns; ++i) std::cout << res.column_name(i) << "\t";

    std::cout << std::endl;

    const std::string null_value = "null";
    while (res.next()) {
        for (short col = 0; col < columns; ++col) {
            auto const value = res.get<std::string>(col, null_value);
            std::cout << "(" << value << ")\t";
        }
        std::cout << std::endl;
    }
}

GTEST_TEST(SFDBTests, TestExecPreStatement) {
    auto conn_str = ConnStr;
    auto pre_query =
        "select  product_key,change_time,EVENT_TYPE_NAME, change_column, "
        "old_value, new_value,meta from "
        "AA_INTELLIGENCE_PRODUCTION.ADL_MASTER.dim_event_service_v1 where  "
        "event_type_name=? and product_key=? and change_time=? order by "
        "change_time desc limit 2;";

    sf_connection sf{conn_str};

    auto res = sf.exec_prpare_statement(pre_query, "screenshot_change",
                                        20600000009072, "2021-06-07");
    ASSERT_EQ(1, res.affected_rows());

    const auto columns = res.columns();
    for (short i = 0; i < columns; ++i) std::cout << res.column_name(i) << "\t";

    std::cout << std::endl;

    const std::string null_value = "null";
    while (res.next()) {
        for (short col = 0; col < columns; ++col) {
            auto const value = res.get<std::string>(col, null_value);
            std::cout << "(" << value << ")\t";
        }
        std::cout << std::endl;
    }
}
