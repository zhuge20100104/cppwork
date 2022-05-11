#ifndef _FREDRIC_ORDER_FILE_H_
#define _FREDRIC_ORDER_FILE_H_

#include <map>
#include <string>

struct order_file {
    order_file();

    // 更新预约记录
    void update_order();

    // key 记录的条数   value 具体记录的键值对
    std::map<int, std::map<std::string, std::string>> m_order_data;

    // 预约记录的条数
    int m_size;
};
#endif