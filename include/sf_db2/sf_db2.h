#ifndef _FREDRIC_SF_DB2_H_
#define _FREDRIC_SF_DB2_H_

#include "nanodbc/convert.h"
#include "nanodbc/nanodbc.h"

#include <any>
#include <exception>
#include <iostream>
#include <string>


using db_result = nanodbc::result;

struct sf_connection {
    nanodbc::connection conn_;

    sf_connection(const std::string& conn_str) {
        conn_ = nanodbc::connection{convert(conn_str)};
    }

    db_result exec_raw_query(const std::string& raw_query) {
        auto res = execute(conn_, NANODBC_TEXT(raw_query));
        return std::move(res);
    }

    template <typename... Params>
    db_result exec_prpare_statement(const std::string& pre_stmt,
                                    Params... params) {
        nanodbc::statement statement(conn_);
        std::cout << pre_stmt << std::endl;
        prepare(statement, NANODBC_TEXT(pre_stmt));
        int index = 0;
        int bind_arr[] = {(bind(statement, index, params), ++index)...};

        auto res = execute(statement);
        return std::move(res);
    }

    virtual ~sf_connection() {}

   private:
    template <typename T>
    void bind(nanodbc::statement& stmt, int index, T param) {
        std::vector<std::string> v{std::to_string(param)};
        stmt.bind_strings(index, v);
    }

    void bind(nanodbc::statement& stmt, int index, const char* param) {
        stmt.bind(index, param);
    }

    void bind(nanodbc::statement& stmt, int index, std::string param) {
        stmt.bind(index, param.c_str());
    }
};

#endif