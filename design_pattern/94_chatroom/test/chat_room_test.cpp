#include "person.h"
#include "chatroom.h"

#include <glog/logging.h>
#include <gtest/gtest.h>

#include <fstream>
#include <memory>
#include <algorithm>

#include "death_handler/death_handler.h"

int main(int argc, char** argv) {
    FLAGS_log_dir = "./";
    FLAGS_alsologtostderr = true;
    // 日志级别 INFO, WARNING, ERROR, FATAL 的值分别为0、1、2、3
    FLAGS_minloglevel = 0;

    Debug::DeathHandler dh;

    google::InitGoogleLogging("./logs.log");
    testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}

// ChatRoom中结者模式简单演示
GTEST_TEST(ChatRoomTests, ChatRoom) {
    ChatRoom room;

    Person john {"john"};
    Person jane {"jane"};
    room.join(&john);
    room.join(&jane);

    john.say("hi room");
    jane.say("oh, hey john");

    Person simon {"simon"};
    room.join(&simon);
    simon.say("hi everyone");

    jane.pm("simon", "glad you could join us, simon");
}
