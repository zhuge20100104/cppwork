#include "beans/order_file.h"
#include "utils/consts.h"
#include "pystring/pystring.h"

#include <fstream>
#include <vector>

order_file::order_file() {
    std::ifstream ifs;
    ifs.open(s_order_file, std::ios::in);
    
    std::string date, interval, stu_id, stu_name, room_id, status;

    m_size = 0;

    while(ifs >> date && ifs >> interval && ifs >> stu_id && ifs >> stu_name && ifs >> room_id && ifs >> status) {
        std::map<std::string, std::string> m;

        std::vector<std::string> res_arr{};
        pystring::split(date, res_arr, ":");
        if(res_arr.size() == 2) {
            m.insert({res_arr[0], res_arr[1]});
        }

        pystring::split(interval, res_arr, ":");
        if(res_arr.size() == 2) {
            m.insert({res_arr[0], res_arr[1]});
        }

        pystring::split(stu_id, res_arr, ":");
        if(res_arr.size() == 2) {
            m.insert({res_arr[0], res_arr[1]});
        }

        pystring::split(stu_name, res_arr, ":");
        if(res_arr.size() == 2) {
            m.insert({res_arr[0], res_arr[1]});
        }

        pystring::split(room_id, res_arr, ":");
        if(res_arr.size() == 2) {
            m.insert({res_arr[0], res_arr[1]});
        }

        pystring::split(status, res_arr, ":");
        if(res_arr.size() == 2) {
            m.insert({res_arr[0], res_arr[1]});
        }

        m_order_data.insert({m_size, std::move(m)});
        ++m_size;
    }
}

// 更新预约记录
void order_file::update_order() {
    if(m_size == 0) {
        return;
    }

    std::ofstream ofs {s_order_file, std::ios::out | std::ios::trunc};
    for(int i=0; i<m_size; ++i) {
        ofs << "date:" << m_order_data[i]["date"] << " ";
        ofs << "interval:" << m_order_data[i]["interval"] << " ";
        ofs << "stu_id:" <<  m_order_data[i]["stu_id"] << " ";
        ofs << "stu_name:" << m_order_data[i]["stu_name"]  << " ";
        ofs << "room_id:" << m_order_data[i]["room_id"]  << " ";
        ofs << "status:" << m_order_data[i]["status"]  << std::endl;
    }
    ofs.close();
}