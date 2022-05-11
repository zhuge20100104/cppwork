#ifndef _FREDRIC_SF_DB_H_
#define _FREDRIC_SF_DB_H_

#include "sf_odbc.h"
#include "sql.h"
#include "sqlext.h"

#include <vector>
#include <string>
#include <iostream>
#include <map>

#include <cassert>

struct DBAuthorization {
    std::string dataSource{};
    std::string password{};
};

/**
 * iodbc
 * /usr/local/iODBC/include
 * /usr/local/iODBC/lib
 * */

struct SFConnection {

    using DB_RETURN_TYPE = std::vector<std::map<std::string, std::string>>;

    SFConnection(DBAuthorization auth);
    ~SFConnection();

    /** 
     * 执行查询的函数
     * @param query_string 原始查询字符串，注意这里不支持select *, 一般也不会用select * 因为性能比较差
     * @return 返回查询的结果集
     * 
     * example:
     *  select product_key, device_code from dim_product_v1 limit 2 将会返回
     *  std::vector { std::map
     *      {"product_key": "111", "device_code": "ios-all"},
     *      {"product_key": "111", "device_code": "google-play"}
     *  }
     */
    DB_RETURN_TYPE exec_query(std::string query_string);

    /**
     * 从Query String里面解析出要查询哪些字段的函数
     * @param query_string 原始查询字符串，注意这里不支持select *, 一般也不会用select * 因为性能比较差
     * @return 返回解析出的查询字段
     * 
     * example:
     *  select product_key, device_code from dim_product_v1 将会解析出 std::vector {"product_key", "device_code"}
     */
    std::vector<std::string> parse_fields_from_query_string(std::string query_string);

    private:
        
        DBAuthorization m_auth{};
        SQLHENV henv;
        SQLHDBC hdbc;
        SQLRETURN henv_ret{-1};
        SQLRETURN hdbc_conn_ret{-1};
        SQLRETURN hdbc_ret{-1};
};


#endif