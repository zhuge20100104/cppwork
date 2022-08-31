#include "cyber/cyber.h"
#include "cyber/demo_base_proto/student.pb.h"

int main(int argc, char* argv[]) {
    apollo::cyber::Init(argv[0]);

    // 创建节点
    auto talker_node = apollo::cyber::CreateNode("talker");
    // 创建发布者. topic名称为chatter
    auto talker = talker_node->CreateWriter<apollo::cyber::demo_base_proto::Student>("chatter");
    // 组织数据并发布
    uint64_t seq = 0;
    apollo::cyber::Rate rate(0.5);

    while(apollo::cyber::OK()) {
        ++seq;
        AINFO << "发布第" << seq << "条数据！";
        auto msg = std::make_shared<apollo::cyber::demo_base_proto::Student>();
        msg->set_name("张三");
        msg->set_age(seq);
        msg->set_height(1.72);
        msg->add_books("chinese");
        msg->add_books("math");
        msg->add_books("english");

        talker->Write(msg);
        rate.Sleep();
    }

    // 等待关闭
    apollo::cyber::WaitForShutdown();
    return EXIT_SUCCESS;
}