#ifndef _FREDRIC_CURRENCY_H_
#define _FREDRIC_CURRENCY_H_

#include "sf_db2/sf_db2.h"

const std::string conn_str = "dsn=product_odbc;pwd=Lily870104";

struct currency_util {
    static sf_connection conn_;
    static bool check_currencies();
};

#endif