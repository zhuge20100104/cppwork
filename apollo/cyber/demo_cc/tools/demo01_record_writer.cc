#include "cyber/cyber.h"
#include "cyber/record/record_writer.h"
#include "cyber/demo_base_proto/student.pb.h"

using apollo::cyber::record::RecordWriter;

int main(int argc, char *argv[]) {
    apollo::cyber::Init(argv[0]);
    AINFO << "record写操作演示...";
    RecordWriter writer;

    // 不按文件大小分割，也不按时间分割
    writer.SetSizeOfFileSegmentation(0);
    writer.SetIntervalOfFileSegmentation(0);

    writer.Open("/apollo/cyber/demo_cc/tools/mytest.record");
    AINFO << "file: " << writer.GetFile();

    std::string channel = "chatter";

    // test... 是对channel的描述信息
    writer.WriteChannel(channel, "apollo.cyber.demo_base_proto.Student", "test...");
    
    // 总共写100条消息
    for(std::size_t i=0; i<100; ++i) {
        auto stu = std::make_shared<apollo::cyber::demo_base_proto::Student>();
        stu->set_name("huluwa");
        stu->add_books("english");
        stu->add_books("chinese");

        std::string content;
        stu->SerializeToString(&content);
        writer.WriteMessage(channel, content, i);
    }

    writer.Close();
    return EXIT_SUCCESS;
}

