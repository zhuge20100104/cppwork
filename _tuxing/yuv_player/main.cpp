#include "player.h"

int main(int argc, char* argv[]) {
    if(argc < 2) {
        std::cerr << "Usage: cmd {filename} " << std::endl;
        return -1;
    }
    std::string video_name = argv[1];

    Player p {video_name};
    PlayerErrors err = PlayerErrors::NO_ERROR;
    p.main_loop(err);
    if(err != PlayerErrors::NO_ERROR) {
        std::cerr << "视频播放失败" << std::endl;
        return -2;
    }
    return 0;
}