#include "cyber/cyber.h"
#include "cyber/demo_base_proto/addints.pb.h"

using Request = apollo::cyber::demo_base_proto::AddInts_Request;
using Response = apollo::cyber::demo_base_proto::AddInts_Response;


void cb(std::shared_ptr<Request> const& request, std::shared_ptr<Response> const& response) {
    int64_t num1 = request->num1();
    int64_t num2 = request->num2();
    AINFO << "客户端请求 num1=" << num1 <<", num2=" << num2;
    int64_t sum = num1 + num2;
    response->set_sum(sum); 
}

int main(int argc, char* argv[]) {
    apollo::cyber::Init(argv[0]);
    AINFO << "服务端执行...";
    auto server_node = apollo::cyber::CreateNode("server_node");
    auto server = server_node->CreateService<Request, Response>("addints", cb);
    apollo::cyber::WaitForShutdown();
    return EXIT_SUCCESS;
}