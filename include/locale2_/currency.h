#ifndef _FREDRIC_CURRENCY_H_
#define _FREDRIC_CURRENCY_H_

#include <string>

struct currency {
    // 国家名 CN
    std::string country_name;
    // currency名 CNY
    std::string currency_name;
    // 货币样式代表 ¥
    std::string currency_sign;

    // Locale信息 zh-CN
    std::string locale;
    // db里面的货币样式，raw_price_string等
    std::string db_sign;
};

#endif