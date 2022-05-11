#include "chat_client.h"
#include "utils/cfg_reader.h"
#include "utils/guid_gen.h"
#include "tasks/task_launcher.h"

std::map<std::string, std::string> slave_cfg {};

class slave : public chat_client {
   public:
    slave(boost::asio::io_service& io_service,
          tcp::resolver::iterator endpoint_iterator)
        : chat_client(io_service, endpoint_iterator) {}

   private:
    bool receive_msg(const boost::system::error_code& ec) {
        // 有ec return true 退出
        if (ec) {
            socket_.close();
            return true;
        }

        // 没有ec 消息不对， 接着等
        if (read_msg_.type() != MT_LAUNCH_TASK_MSG) {
            return false;
        }

        // 没有ec，消息正确，做事儿，return true 退出
        // 启动性能测试，完事以后发送
        // send_task_info_msg
        auto json_obj = to_json();
        std::cout << "master ";
        std::cout << json_obj["name"].get<std::string>();
        std::cout << " says: ";
        std::cout << json_obj["information"].get<std::string>();
        std::cout << "\n";

        std::cerr << "开始做性能测试..." << std::endl;

        auto task_info = json_obj["information"].get<std::string>();
        task_launcher launcher {task_info};
        launcher.dump_requests();
        launcher.run();
        auto task_run_results_ = launcher.dump_results();
        
        std::cerr << "结束做性能测试..." << std::endl;

        chat_message msg;
        auto type = 0;

        std::string input("SendTaskInfo ");
        input = input + task_run_results_;
        std::string output;
        
        if (parseMessage(input, &type, output)) {
            msg.setMessage(type, output.data(), output.size());
            write(msg);
        }
        close();
        return true;
    }
};

int main(int argc, char* argv[]) {
    try {
        
        bool read_res = cfg_reader::read_file(slave_cfg_file_path, slave_cfg);
        if(!read_res) {
            std::cerr << "Read slave config file failed!" << std::endl;
            return 1;
        }

        boost::asio::io_service io_service;
        tcp::resolver resolver(io_service);
        auto endpoint_iterator = resolver.resolve({slave_cfg["host"], slave_cfg["port"]});
        auto c = std::make_shared<slave>(io_service, endpoint_iterator);

        std::string slave_name_prefix = slave_cfg["name"];
        std::string guid_str = GUIDGen::gen_uuid_str();
        std::string slave_name = slave_name_prefix + "_";
        slave_name = slave_name + guid_str;

        std::string input = "BindName " + slave_name;

        parse_and_send_a_message(*c, input);

        std::thread t([&io_service]() { io_service.run(); });

        t.join();
    } catch (std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
    }

    return 0;
}
