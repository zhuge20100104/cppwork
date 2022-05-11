#ifndef _FREDRIC_HTML__H_
#define _FREDRIC_HTML__H_
#include "html-parser/HTMLDocument.h"

#include <fstream>

struct Html {
    static HTMLDocument get_html_doc(std::ifstream& fs);
    static HTMLDocument get_html_doc(const std::string& s);
};
#endif