#include "cyber/cyber.h"
#include "cyber/parameter/parameter_client.h"

using apollo::cyber::Parameter;
using apollo::cyber::ParameterClient;

int main(int argc, char *argv[]) {
    apollo::cyber::Init(argv[0]);
    AINFO << "参数客户端";

    auto param_client_node = apollo::cyber::CreateNode("param_client");
    auto param_client = std::make_shared<ParameterClient>(std::move(param_client_node), "param");

    Parameter temp;
    param_client->GetParameter("type", &temp);
    AINFO << temp.Name() << "=" << temp.AsString();
    param_client->GetParameter("height", &temp);
    AINFO << temp.Name() << "=" << temp.AsDouble();
    param_client->GetParameter("lasers", &temp);
    AINFO << temp.Name() << "=" << temp.AsInt64();

    std::vector<Parameter> ps;
    param_client->ListParameters(&ps);
    for(auto const& p: ps) {
        AINFO << p.Name() << "=" << p.TypeName() << "=" << p.DebugString();
    }
    return EXIT_SUCCESS;
}
