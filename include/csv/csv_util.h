#ifndef _CSV_UTIL_H_
#define _CSV_UTIL_H_

#include "csv.h"
#include "csv/entity.h"

#include <vector>
#include <map>
#include <string>

class CSVUtil {
    public:
        template<typename ... T>
        static std::vector<Entity> read_csv(std::string file_path, T ... columns) {
            io::CSVReader<sizeof...(columns)> in {file_path};
            in.read_header(io::ignore_extra_column, columns...);
            Entity entity;
            std::vector<Entity> results;
            while (in.read_row(entity.product_id, entity.old_url, entity.new_url, entity.date)){
                results.emplace_back(std::move(entity));
            }
            return std::move(results);
        }
};

#endif