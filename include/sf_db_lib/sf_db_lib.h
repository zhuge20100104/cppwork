#ifndef _FREDRIC_SF_DB_LIB_H_
#define _FREDRIC_SF_DB_LIB_H_

#include "nanodbc/nanodbc.h"

#include <any>
#include <string>

using db_result = nanodbc::result;

struct sf_connection {
    nanodbc::connection conn_;

    sf_connection(const std::string& conn_str);
    db_result exec_raw_query(const std::string& raw_query);
    db_result exec_prpare_statement(const std::string& pre_stmt,
                                    const std::vector<std::any>& params);
    virtual ~sf_connection();

   private:
    void bind_params(nanodbc::statement& stmt, const short index,
                     const std::any& param);
};

#endif