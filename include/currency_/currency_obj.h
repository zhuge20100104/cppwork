#ifndef _FREDRIC_CURRENCY_OBJ_H_
#define _FREDRIC_CURRENCY_OBJ_H_
#include <map>
#include <string>

struct currency {
    std::string product_key;
    std::string name;
    std::string currency_sign;
    double price;
    std::string locale;
    bool is_sign_valid(); 
    bool is_price_valid();      
};
#endif