#ifndef _FREDRIC_ZEPPLIN_MIG_CONV_UTIL_H_
#define _FREDRIC_ZEPPLIN_MIG_CONV_UTIL_H_

#include <vector>
#include <string>

enum class DataSource {
    LOCAL,
    DB
};

struct Notebook {
    std::string nb_content;
    std::string py_name;
    std::string ipy_name;
};

struct ConvUtil {
    static std::vector<Notebook> get_all_note_books(std::string const& note_path, DataSource const& source);

    static bool conv_notebook_2_py(std::vector<Notebook> const& note_books);

    static bool conv_notebook_2_ipynb(std::vector<Notebook> const& note_books);
};

#endif