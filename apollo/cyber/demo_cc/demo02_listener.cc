#include "cyber/cyber.h"
#include "cyber/demo_base_proto/student.pb.h"

void cb(std::shared_ptr<apollo::cyber::demo_base_proto::Student> const& stu) {
    AINFO << "name: " <<stu->name();
    AINFO << "age: " << stu->age();
    AINFO << "height: " << stu->height();
    for(auto const& book: stu->books()) {
        AINFO << "books: " << book;
    } 
    AINFO << "-------------------------------------------------";
} 

int main(int argc, char *argv[]) {
    apollo::cyber::Init(argv[0]);
    AINFO << "订阅方创建...";
    // 创建节点
    auto listener_node = apollo::cyber::CreateNode("listener");
    auto listener = listener_node->CreateReader<apollo::cyber::demo_base_proto::Student>("chatter", cb);
    apollo::cyber::WaitForShutdown();
    return EXIT_SUCCESS;
}
