#include "cyber/demo_cc/component_common01/common_cpt.h"

bool CommonCpt::Init() {
    AINFO << ".........................Init.........................";
    return true;
}

bool CommonCpt::Proc(std::shared_ptr<Student> const& stu) {
    AINFO << "do message:" << stu->name() << "--" << stu->age();
    return true;
}