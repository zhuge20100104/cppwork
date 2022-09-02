#ifndef DEMO_CC_COMMON_CPT_H
#define DEMO_CC_COMMON_CPT_H

#include "cyber/component/component.h"

#include "cyber/demo_base_proto/student.pb.h"

using apollo::cyber::Component;
using apollo::cyber::demo_base_proto::Student;

class CommonCpt: public Component<Student> {
public:
    bool Init() override;
    bool Proc(std::shared_ptr<Student> const& stu) override;
};

CYBER_REGISTER_COMPONENT(CommonCpt)

#endif