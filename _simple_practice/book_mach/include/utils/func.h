#ifndef _FREDIRC_FUNCS1_H_
#define _FREDIRC_FUNCS1_H_

#include <string>
#include "beans/identity.h"

namespace Funcs {
    void pause();
    void clear();
    void login_in(std::string file_name, int type);
    void manager_menu(identity* & man_);
    void student_menu(identity* & stu_);
    void teacher_menu(identity* & tea_);
};

#endif