#ifndef _FREDRIC_D_OP_H_
#define _FREDRIC_D_OP_H_
#include <vector>
#include <string>

struct d_op {
    static std::vector<std::string> get_bdp_bucket_list();
    static std::vector<std::string> get_databricks_bucket_list();
    static std::vector<std::string> get_missing_bucket_list(std::vector<std::string> const& bdp_final, std::vector<std::string> const& db_final);
    static std::vector<std::string> fx_missing_results(std::vector<std::string> const& missing_results);

    static bool write_to_csv(std::vector<std::string> const& missing_final);
};

#endif