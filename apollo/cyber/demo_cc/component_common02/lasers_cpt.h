#ifndef COMPONENT_COMMON02_LASERS_CPT_H
#define COMPONENT_COMMON02_LASERS_CPT_H
#include "cyber/component/component.h"
#include "cyber/demo_base_proto/lasers.pb.h"

using apollo::cyber::Component;
using apollo::cyber::demo_base_proto::Lasers;

class LaserCpt: public Component<Lasers, Lasers> {
public:
    bool Init() override;
    bool Proc(std::shared_ptr<Lasers> const& front, std::shared_ptr<Lasers> const& back) override;
private:
    std::shared_ptr<apollo::cyber::Writer<Lasers>> writer = nullptr;
    uint64_t seq;
};

CYBER_REGISTER_COMPONENT(LaserCpt)
#endif