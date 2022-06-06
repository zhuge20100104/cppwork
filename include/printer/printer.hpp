#ifndef _FREDRIC_PRINTER_HPP_
#define _FREDRIC_PRINTER_HPP_

#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using std::ostream;
using std::stringstream;
using std::vector;
using std::string;

/**
 * Function used to print vector of vectors
 * */
template<typename T>
ostream& operator<<(ostream& os, vector<vector<T>> const& points) {
    stringstream ss;
    for(auto v: points) {
        stringstream inner_ss;
        inner_ss << "[";
        for(auto ele: v) {
            inner_ss << ele << ",";
        }

        // 去掉最右边的逗号
        string inner_str = inner_ss.str();
        inner_str = inner_str.substr(0, inner_str.size()-1);
        ss << inner_str;
        ss << "],";
    }
    // 再次去掉最右边的逗号
    string out_str = ss.str();
    out_str = out_str.substr(0, out_str.size()-1); 
    return os << out_str;
}

/** 
 * Function used to print a std::vector
*/
template <typename T>
ostream& operator<<(ostream& os, vector<T> const& eles) {
    stringstream ss;
    for(auto&& ele: eles) {
        ss << ele << ",";
    }
    string res_str = ss.str();
    res_str = res_str.substr(0, res_str.size()-1);
    return os << res_str;
}

#endif