#include "cyber/cyber.h"
#include "cyber/demo_base_proto/lasers.pb.h"

using apollo::cyber::demo_base_proto::Lasers;

int main(int argc, char *argv[]) {
    apollo::cyber::Init(argv[0]);
    AINFO << "模拟前雷达节点...";
    auto pub_node = apollo::cyber::CreateNode("front_laser_node");
    auto pub = pub_node->CreateWriter<Lasers>("/front/laser");
    apollo::cyber::Rate rate(1.0);
    auto lasers = std::make_shared<Lasers>();
    lasers->set_count(2);
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
