
#include "sf_db_lib/sf_db_lib.h"

#include <exception>
#include <iostream>

#include "nanodbc/convert.h"

using std::cout;
using std::endl;

sf_connection::sf_connection(const std::string& conn_str) {
    conn_ = nanodbc::connection{convert(conn_str)};
}

db_result sf_connection::exec_raw_query(const std::string& raw_query) {
    auto res = execute(conn_, NANODBC_TEXT(raw_query));
    return std::move(res);
}

void sf_connection::bind_params(nanodbc::statement& stmt, const short index,
                                const std::any& param) {
    if (param.type() == typeid(nullptr)) {
        stmt.bind_null(index);
    } else if (param.type() == typeid(int)) {
        auto val = std::any_cast<int>(param);
        std::vector<std::string> v{std::to_string(val)};
        stmt.bind_strings(index, v);
    } else if (param.type() == typeid(long)) {
        auto val = std::any_cast<long>(param);
        std::vector<std::string> v{std::to_string(val)};
        stmt.bind_strings(index, v);
    } else if (param.type() == typeid(double)) {
        auto val = std::any_cast<double>(param);
        std::vector<std::string> v{std::to_string(val)};
        stmt.bind_strings(index, v);
    } else if (param.type() == typeid(float)) {
        auto val = std::any_cast<float>(param);
        std::vector<std::string> v{std::to_string(val)};
        stmt.bind_strings(index, v);
    } else if (param.type() == typeid(const char*)) {
        auto val = std::any_cast<const char*>(param);
        stmt.bind(index, val);
    } else if (param.type() == typeid(std::string)) {
        auto val = std::any_cast<std::string>(param);
        stmt.bind(index, val.c_str());
    } else {
        throw std::runtime_error("not supported data types!");
    }
}

db_result sf_connection::exec_prpare_statement(
    const std::string& pre_stmt, const std::vector<std::any>& params) {
    nanodbc::statement statement(conn_);
    std::cout << pre_stmt << std::endl;
    prepare(statement, NANODBC_TEXT(pre_stmt));
    for (short i = 0; i < params.size(); ++i) {
        bind_params(statement, i, params[i]);
    }
    auto res = execute(statement);
    return std::move(res);
}

sf_connection::~sf_connection() {}