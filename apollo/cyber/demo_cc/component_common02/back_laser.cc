#include "cyber/cyber.h"
#include "cyber/demo_base_proto/lasers.pb.h"

using apollo::cyber::demo_base_proto::Lasers;

int main(int argc, char *argv[]) {
    apollo::cyber::Init(argv[0]);
    AINFO << "模拟后雷达节点...";
    auto pub_node = apollo::cyber::CreateNode("back_laser_node");
    auto pub = pub_node->CreateWriter<Lasers>("/back/laser");

    apollo::cyber::Rate rate(0.2);
    auto lasers = std::make_shared<Lasers>();
    lasers->set_count(3);
    uint64_t seq = 0;

    while(apollo::cyber::OK()) {
        ++seq;
        lasers->set_seq(seq);
        pub->Write(lasers);
        rate.Sleep();
    }
    apollo::cyber::WaitForShutdown();
    return EXIT_SUCCESS;
}
