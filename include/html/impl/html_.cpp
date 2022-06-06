#include "html/html_.h"


HTMLDocument Html::get_html_doc(std::ifstream& fs) {
    HTMLDocument doc(fs);
    doc.inspect();
    return std::move(doc);
}

HTMLDocument Html::get_html_doc(const std::string& s) {
     HTMLDocument doc(s.c_str());
     return std::move(doc);
}