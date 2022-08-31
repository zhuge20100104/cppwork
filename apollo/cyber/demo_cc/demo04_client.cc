#include "cyber/cyber.h"
#include "cyber/demo_base_proto/addints.pb.h"

using Request = apollo::cyber::demo_base_proto::AddInts_Request;
using Response = apollo::cyber::demo_base_proto::AddInts_Response;

int main(int argc, char *argv[]) {
    apollo::cyber::Init(argv[0]);

    if(argc != 3) {
        AINFO << "执行程序时请输入两个数字作为参数";
        return EXIT_FAILURE;
    }

    AINFO << "客户端启动...";
    auto client_node = apollo::cyber::CreateNode("client_node");
    auto client = client_node->CreateClient<Request, Response>("addints");
    AINFO << "等待服务启动...";
    auto request = std::make_shared<Request>();
    request->set_num1(std::atoll(argv[1]));
    request->set_num2(std::atoll(argv[2]));
    auto response = client->SendRequest(request);
    AINFO << "响应结果: sum=" << response->sum();
    return EXIT_SUCCESS;
}
