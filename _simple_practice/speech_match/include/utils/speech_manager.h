#ifndef _FREDIRC_SPEECH_MANAGER_H_
#define _FREDIRC_SPEECH_MANAGER_H_

#include "beans/speaker.h"

#include <vector>
#include <map>
#include <string>

class speech_manager {
    public:
        speech_manager();
        ~speech_manager();

        void show_menu();
        void exit_system();

        void init_speech();
        void create_speaker();
        void start_speech();
        void speech_contest();

        // 显示比赛得分
        void show_score();
        // 保存记录
        void save_record();
        // 读取往届记录
        void load_record();
        // 查看往届记录
        void show_record();
        // 清空记录
        void clear_record();

        // 抽签
        void speech_draw();
    // private:
        // 第一轮比赛选手容器12人
        std::vector<int> v1;
        // 第一轮晋级容器6人
        std::vector<int> v2;
        // 胜利前3名容器
        std::vector<int> v_victory;

        std::map<int, speaker> m_speakers;

        // 记录比赛轮数
        int m_index;
        // 文件是否为空指示符
        bool m_file_empty;
        // 往届记录数据
        std::map<int, std::vector<std::string>> m_record;
};
#endif