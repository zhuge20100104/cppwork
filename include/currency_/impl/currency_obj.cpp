#include "currency_/currency_obj.h"
#include "currency_/currency_cfg.h"

bool currency::is_sign_valid() {
    auto sign_it = currency_sign_map.find(locale);
    // Not find the locale, skip check
    if(sign_it == currency_sign_map.end()) {
        return true;
    } else {
        auto expect_sign = sign_it->second;
        // Find, but sign not match
        return currency_sign.find(expect_sign) != std::string::npos;
    }
}

bool currency::is_price_valid() {
    return price >= 0;
}
