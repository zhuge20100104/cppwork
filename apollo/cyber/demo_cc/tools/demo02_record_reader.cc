#include "cyber/cyber.h"
#include "cyber/record/record_reader.h"
#include "cyber/record/record_message.h"
#include "cyber/demo_base_proto/student.pb.h"

using apollo::cyber::record::RecordReader;
using apollo::cyber::record::RecordMessage;
using apollo::cyber::demo_base_proto::Student;

int main(int argc, char *argv[]) {
    apollo::cyber::Init(argv[0]);

    AINFO << "record读操作演示...";

    RecordReader reader("/apollo/cyber/demo_cc/tools/mytest.record");
    std::string channel = "chatter";
    uint64_t msg_count = reader.GetMessageNumber(channel);
    AINFO << "总共有 " << msg_count << " 条消息";
    auto msg_type = reader.GetMessageType(channel);
    auto msg_desc = reader.GetProtoDesc(channel);
    AINFO << "消息类型: " << msg_type;
    AINFO << "消息描述: " << msg_desc;

    RecordMessage msg;

    for(std::size_t i=0; i<msg_count; ++i) {
        if(reader.ReadMessage(&msg)) {
            AINFO << "第 " << i << " 条消息 ->"
                << "channel name: " << msg.channel_name;
            Student stu;
            stu.ParseFromString(msg.content);
            AINFO << ";content: " << stu.name() << ",";
            for(auto const& book: stu.books()) {
                AINFO << book << " ";
            }
            AINFO << "; msg time: " << msg.time;
        } else {
            AINFO << "消息读取失败...";
        }
    }
    return EXIT_SUCCESS;
}
