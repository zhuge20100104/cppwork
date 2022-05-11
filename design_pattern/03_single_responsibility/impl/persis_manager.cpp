#include "persis_manager.h"
 
#include <fstream>

void PersisManager::save(Journal const& j, std::string const& file_name) {
    std::ofstream ofs {file_name};
    ofs << j.title << std::endl;
    for(auto& e: j.entries) {
        ofs << e << std::endl;
    }
}