#include "chat_client.h"
#include "utils/cfg_reader.h"
#include "tasks/task_reader.h"
#include "tasks/task_summary.h"

int slave_count = 0;

std::map<std::string, std::string> master_cfg {};

class master : public chat_client {
   public:
    master(boost::asio::io_service& io_service,
           tcp::resolver::iterator endpoint_iterator)
        : chat_client(io_service, endpoint_iterator) {}

   private:
    std::vector<std::string> task_result_strs;

    bool receive_msg(const boost::system::error_code& ec) {
        // 有ec 直接return true退出
        if (ec) {
            socket_.close();
            return true;
        }

        // 校验一下消息长度和消息类型，
        // 证明确实发过来的是RomInformation消息
        if (read_msg_.type() != MT_SEND_TASK_INFO_MSG) {
            return false;
        }

        auto json_obj = to_json();

        auto task_result_s = json_obj["information"].get<std::string>();

        std::cout << "slave ";
        std::cout << json_obj["name"].get<std::string>();
        std::cout << " says: ";
        std::cout << task_result_s;
        std::cout << "\n";

        task_result_strs.push_back(task_result_s);
        // 还没到那么多slave个数，不用计算，return false,接着等
        ++receive_slave_cout;
        if (receive_slave_cout != slave_count) {
            return false;
        }

        // Add summary result logic
        // 汇总计算结果
        std::cerr << "开始汇总计算性能测试结果" << std::endl;
        task_summary t_summary{task_result_strs};
        std::cerr << "结束汇总计算性能测试结果" << std::endl;

        std::cerr << "性能结果汇总: " << std::endl;
        t_summary.dump_summary_results();
        
        close();
        return true;
    }

    int receive_slave_cout{0};
};

int main(int argc, char* argv[]) {
    try {
        
        bool read_res = cfg_reader::read_file(master_cfg_file_path, master_cfg);

        if(!read_res) {
            std::cerr << "读取配置文件失败!" << std::endl;
            return 1;
        }

        slave_count = std::atoi(master_cfg["slave"].c_str());

        boost::asio::io_service io_service;
        tcp::resolver resolver(io_service);

        auto endpoint_iterator = resolver.resolve({master_cfg["host"], master_cfg["port"]});

        auto c = std::make_shared<master>(io_service, endpoint_iterator);

        std::thread t([&io_service]() { io_service.run(); });

        auto type = 0;
        std::string master_name = master_cfg["name"];
        std::string bind_name_cmd = "BindName " + master_name; 

        auto total_count = std::atoi(master_cfg["total_count"].c_str());
        auto thread_count = total_count / slave_count;
        auto stress_hold_on_time = std::atoi(master_cfg["stress_hold_on_time"].c_str());

        task task_{thread_count, stress_hold_on_time};
        task_reader tr {task_};
        auto task_str = tr.parse_tasks(cases_file_path);
        std::string launch_task_str = "LaunchTask " + task_str;
        std::string msgs_[] = {bind_name_cmd, launch_task_str};

        for (const auto& msg_str : msgs_) {
            parse_and_send_a_message(*c, msg_str);
        }

        t.join();
    } catch (std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
    }

    return 0;
}
