#include "utils/conv_util.h"
#include "utils/ipy_consts.h"
#include "utils/zepplin_mig_cfg.h"

#include "pystring/pystring.h"
#include "sf_db2/sf_db2.h"

#include "json/json.hpp"
#include "api_accuracy/utils/io_util.h"

#include <filesystem>
#include <iostream>
#include <sstream>

namespace fs = std::filesystem;
using json = nlohmann::json;

Notebook make_a_notebook(std::string const& nb_content) {
    auto nb_js = json::parse(nb_content);
    auto name_ = nb_js["name"].get<std::string>();
    
    std::vector<std::string> name_list;
    pystring::split(name_, name_list, "/");

    std::stringstream ss_name {};
    for(auto& name_seg: name_list) {
        if(!name_seg.empty()) {
            ss_name << name_seg;
            ss_name << "#";
        }
    }

    auto final_name = ss_name.str();
    final_name = final_name.substr(0, final_name.size()-1);

    auto book_name = final_name  + ".py";
    auto ipy_book_name = final_name  + ".ipynb";
    
    return Notebook{nb_content, book_name, ipy_book_name};
}


std::vector<Notebook> get_all_note_books_from_local_dir(std::string const& note_path) {
    std::vector<Notebook> ret_books{}; 
    for(auto const& entry: fs::directory_iterator(note_path)) {
        std::string path_ = entry.path();
        // 不是json文件
        if(!pystring::endswith(path_, ".json")) {
            continue;
        }
        auto nb_content = IOUtil::read_file(path_);
        ret_books.emplace_back(std::move(make_a_notebook(nb_content)));
    }
    return ret_books;
}

std::vector<Notebook> get_all_note_books_from_db() {
    std::vector<Notebook> ret_books{};
    sf_connection sf{conn_str};
    std::string raw_query = "select NOTE from ONE_SERVICE_TEST_DB_AABJFZHU_DATA.PUBLIC.zeppelin_notes;";
    auto res = sf.exec_raw_query(raw_query);
    const std::string null_value = "null";
    const auto columns = res.columns();

    while (res.next()) {
        auto const value = res.get<std::string>("NOTE", null_value);
        std::cout << value << "\n";
        ret_books.emplace_back(std::move(make_a_notebook(value)));
    }
    return ret_books;
}

std::vector<Notebook> ConvUtil::get_all_note_books(std::string const& note_path, DataSource const& source) {   
    if(source == DataSource::LOCAL) {
        return get_all_note_books_from_local_dir(note_path);
    } else {
        return get_all_note_books_from_db();
    }
}  


bool ConvUtil::conv_notebook_2_py(std::vector<Notebook> const& note_books) {
    for(auto const& nb: note_books) {
        auto nb_content = nb.nb_content;
        auto nb_js = json::parse(nb_content);
        auto nb_paragraphs= nb_js["paragraphs"];
        std::stringstream ss;
        auto i {0};
        for(auto const& nb_para: nb_paragraphs) {
            if(nb_para.contains("text")) {
                auto un_format_para = nb_para["text"].get<std::string>();
                if(!pystring::startswith(un_format_para, "%sh")) {
                    un_format_para = pystring::replace(un_format_para, "%pyspark", "");
                    ss << "## Section " << ++i << " : \r\n" << un_format_para << "\r\n\r\n";
                }
            }
        }
        std::string out_file_name = "../pybooks/" + nb.py_name;
        IOUtil::write_file(out_file_name, ss.str());
    }
    return true;
}

bool ConvUtil::conv_notebook_2_ipynb(std::vector<Notebook> const& note_books) {
    for(auto const& nb: note_books) {
        auto ipynb_temp = json::parse(ipynb_template);
        auto meta_temp = json::parse(meta_template);
        ipynb_temp["metadata"] = meta_temp;

        auto nb_content = nb.nb_content;
        auto nb_js = json::parse(nb_content);
        auto nb_paragraphs= nb_js["paragraphs"];
        auto i {0};
        for(auto const& nb_para: nb_paragraphs) {
            if(nb_para.find("text") == nb_para.end()) {
                continue;
            }
            
            auto un_format_para = nb_para["text"].get<std::string>();
          
            std::stringstream ss;
            auto ipy_nb_cell_temp = json::parse(cell_template);
            auto id = nb_para["id"].get<std::string>();
            ipy_nb_cell_temp["id"] = id;

            if(pystring::startswith(un_format_para, "%sh")) {
                un_format_para = pystring::replace(un_format_para, "%sh", "%%sh");
            } else {
                un_format_para = pystring::replace(un_format_para, "%pyspark", "");
            }
            
            ss << un_format_para;

            ipy_nb_cell_temp["source"].emplace_back(std::move(ss.str()));
            ipynb_temp["cells"].emplace_back(std::move(ipy_nb_cell_temp));
        }
        std::string out_file_name = "../ipynbs/" + nb.ipy_name;
        IOUtil::write_file(out_file_name, ipynb_temp.dump());
    }
    return true;
}