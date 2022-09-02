#include "cyber/cyber.h"
#include "cyber/parameter/parameter_server.h"

using apollo::cyber::ParameterServer;
using apollo::cyber::Parameter;

int main(int argc, char *argv[]) {
    apollo::cyber::Init(argv[0]);
    AINFO << "参数服务端";
    auto param_service_node = apollo::cyber::CreateNode("param");
    auto param_service = std::make_shared<ParameterServer>(std::move(param_service_node));

    param_service->SetParameter(Parameter("type", "apollo_car"));
    param_service->SetParameter(Parameter("height", 1.65));
    param_service->SetParameter(Parameter("lasers", 4));

    // 获取指定参数
    Parameter temp;
    param_service->GetParameter("type", &temp);
    AINFO << temp.Name() << ":" << temp.AsString();
    param_service->GetParameter("height", &temp);
    AINFO << temp.Name() << ":" << temp.AsDouble();
    param_service->GetParameter("lasers", &temp); 
    AINFO << temp.Name() << ":" << temp.AsInt64();

    std::vector<Parameter> params;
    param_service->ListParameters(&params);
    for(auto const& param: params) {
        AINFO << param.Name() << "=" << param.TypeName() << "=" << param.DebugString();
    }

    apollo::cyber::WaitForShutdown();
    return EXIT_SUCCESS;
}
