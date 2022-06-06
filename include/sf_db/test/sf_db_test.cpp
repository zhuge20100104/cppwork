#include "sf_db/sf_db.h"

#include <array>
#include <gtest/gtest.h>

GTEST_TEST(SFDBTests, TestExecQuery) {
    DBAuthorization auth {"product_odbc", "Lily870104"};
    SFConnection sf_conn {auth};
    std::string query_string = "select  product_key,change_time,EVENT_TYPE_NAME, change_column, old_value, new_value,meta from AA_INTELLIGENCE_PRODUCTION.ADL_MASTER.dim_event_service_v1 where  event_type_name='screenshot_change' and product_key=20600000009072 order by change_time desc limit 10;";

    auto results = sf_conn.exec_query(query_string);
    ASSERT_EQ(10, results.size());

    auto results2 = sf_conn.exec_query(query_string);
    ASSERT_EQ(10, results2.size());
}


GTEST_TEST(SFDBTests, TestExecQueryAndPrintValue) {
    DBAuthorization auth {"product_odbc", "Lily870104"};
    SFConnection sf_conn {auth};
    std::string query_string = "select  product_key,change_time,event_type_name, change_column, old_value, new_value,meta from ADL_MASTER.DIM_EVENT_V2_CLUSTER_BY_PRODUCT_KEY  where (change_time >= '2016-09-27')  and (change_time <= '2018-08-29') and  event_type_name='screenshot_change'  and  product_key=20600000009072  limit 2;";

    auto results = sf_conn.exec_query(query_string);
    ASSERT_EQ(2, results.size());
    std::cout << "product_key,  change_time,  event_type_name,  change_column,  old_value,  new_value,  meta" 
        << std::endl;
    
    for(auto&& result: results) {
        std::cout << " " << result["product_key"] << " " << result["change_time"] <<
            " " << result["event_type_name"] << " " << result["change_column"] <<
            " " << result["old_value"] << " " << result["new_value"] << 
            " " << result["meta"] << std::endl;
    }
}


GTEST_TEST(SFDBTests, TestParseFields) {
    DBAuthorization auth {"product_odbc", "Lily870104"};
    SFConnection sf_conn {auth};
    std::string query_string = "select product_key, meta from AA_INTELLIGENCE_PRODUCTION.ADL_MASTER.dim_event_service_v1 where  event_type_name='screenshot_change' and product_key=20600000009072 order by change_time desc limit 10;";

    auto res = sf_conn.parse_fields_from_query_string(query_string);
    ASSERT_EQ(2, res.size());
    ASSERT_EQ("product_key", res[0]);
    ASSERT_EQ("meta", res[1]);
}
