#include "cyber/demo_cc/component_common02/lasers_cpt.h"

bool LaserCpt::Init() {
    // 创建一个发布者，接着往下发布消息
    seq = 0;
    writer = node_->CreateWriter<Lasers>("laser");
    return true;
}

bool LaserCpt::Proc(std::shared_ptr<Lasers> const& front, std::shared_ptr<Lasers> const& back) {
    uint64_t front_seq = front->seq();
    uint64_t front_count = front->count();
    uint64_t back_seq = back->seq();
    uint64_t back_count = back->count();
    uint64_t sum = front_count + back_count;

    AINFO << "front_seq = " << front_seq << " back_seq = " << back_seq << " sum = " << sum;

    // 重新组织消息写出
    ++seq;
    auto laser_ptr = std::make_shared<Lasers>();
    laser_ptr->set_count(sum);
    laser_ptr->set_seq(seq);
    writer->Write(laser_ptr);
    return true;
}
