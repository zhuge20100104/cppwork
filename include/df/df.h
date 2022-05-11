#ifndef _FREDRIC_DF_H_
#define _FREDRIC_DF_H_

#include "json/json.hpp"

#include <DataFrame/DataFrame.h>
#include <DataFrame/DataFrameFinancialVisitors.h>
#include <DataFrame/DataFrameMLVisitors.h>
#include <DataFrame/DataFrameOperators.h>
#include <DataFrame/DataFrameStatsVisitors.h>

#include <vector>


using json = nlohmann::json;

// 主键为unsigned int的DataFrame
using CDataFrame = hmdf::StdDataFrame<unsigned int>;
// 主键为unsigned long的DataFrame
using CLDataFrame = hmdf::StdDataFrame<unsigned long>;

// DataFrame Iterator type
template <typename T>
using CDFIdxIteratorT = typename hmdf::StdDataFrame<T>::IndexVecType::iterator;

using CDataFrameIdxItType = CDFIdxIteratorT<unsigned int>;
using CLDataFrameIdxItType = CDFIdxIteratorT<unsigned long>;

using concat_policy = hmdf::concat_policy;
using join_policy = hmdf::join_policy;

const std::string Keys = "keys_";

struct df_op {
    static CDataFrame convert_json_to_df(const json& js, const std::vector<std::string>& pri_keys_);
    static std::vector<std::string> get_df_keys(const json& js);
    static CDataFrame remove_duplicate(const CDataFrame& df, const std::vector<std::string>& keys_);
    static bool write_to_csv(const CDataFrame& df, const std::string& csv_file_name);
}; 

#endif


