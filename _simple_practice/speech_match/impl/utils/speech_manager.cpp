#include "utils/speech_manager.h"
#include "utils/funcs.h"
#include "pystring/pystring.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <functional>
#include <random>
#include <deque>

speech_manager::speech_manager() {
    // 初始化属性
    init_speech();
    // 创建选手
    create_speaker();
    // 读取往届记录
    load_record();
}

speech_manager::~speech_manager() {

}

void speech_manager::show_menu() {
    std::cout << "****************************************" << std::endl;
    std::cout << "************   欢迎参加演讲比赛   *********" << std::endl;
    std::cout << "************   1.开始演讲比赛    *********" << std::endl;
    std::cout << "************   2.查看往届记录    *********" << std::endl;
    std::cout << "************   3.清空比赛记录    *********" << std::endl;
    std::cout << "************   0.退出比赛程序    *********" << std::endl;
    std::cout << std::endl;
}

void speech_manager::exit_system() {
    std::cout << "欢迎下次使用" << std::endl;
    Funcs::pause();
    ::exit(0);
}
    
void speech_manager::init_speech() {
    v1.clear();
    v2.clear();
    v_victory.clear();

    m_speakers.clear();
    m_index = 1;
    m_record.clear();
}

void speech_manager::create_speaker() {
    std::string name_seed = "ABCDEFGHIJKL";
    std::string name_prefix = "选手";
    for(int i=0; i<name_seed.size(); ++i) {
        std::stringstream name_ss;
        name_ss << name_prefix << name_seed[i];
        std::string name = name_ss.str();
        
        speaker sp;
        sp.m_name = name;
        for(int i=0; i<2; ++i) {
            sp.m_score[i] = 0;
        }

        v1.emplace_back(i+10001);
        m_speakers.insert({i+10001, std::move(sp)});
    }
}

void speech_manager::start_speech() {
    // 第一轮比赛
    // 1.抽签
    speech_draw();
    // 2.比赛
    speech_contest();
    // 3.显示晋级结果
    show_score();

    // 4.第二轮比赛
    ++m_index;
    // 5.抽签
    speech_draw();
    // 6.比赛
    speech_contest();
    // 7.显示最终结果
    show_score();
    // 保存分数
    save_record();

    std::cout << "本届比赛完毕" << std::endl;

    // 重新初始化比赛
    init_speech();
    create_speaker();
    // 比赛完成之后，往届记录列表更新
    load_record();
    Funcs::pause();
    Funcs::clear();
}

void speech_manager::speech_contest() {
    std::cout << "---------第 " << m_index << " 轮比赛正式开始: ---------------" << std::endl;
    // 临时容器，保存key分数， value 选手编号
    std::multimap<double, int, std::greater<double>> group_score;
    int num = 0; // 记录人员数，6个为一组
    std::vector<int> v_src; // 比赛的人员容器

    if(m_index == 1) {
        v_src = v1;
    } else {
        v_src = v2;
    }
    for(auto&& sp_index: v_src) {
        ++num;

        // 评委打分
        std::deque<double> d;
        for(int i=0; i<10; ++i) {
            double score = (rand()%401 + 600)/ 10.0f; // 60 - 100
            d.emplace_back(std::move(score));
        }

        std::sort(d.begin(), d.end(), std::greater<double>());
        d.pop_front(); // 去掉最高分
        d.pop_back(); //去掉最低分

        double sum = std::accumulate(d.begin(), d.end(), 0.0f);
        double avg = sum/(double)(d.size()); 
        m_speakers[sp_index].m_score[m_index-1] = avg;
        // 6人一组，用临时容器保存
        group_score.insert({avg, sp_index});
        if(num % 6==0) {
            std::cout << "第 " << num / 6 << "小组比赛名次" << std::endl;
            int count = 0;
            for(auto&& score_index: group_score) {
                if(count < 3) {
                    if(m_index == 1) {
                        v2.emplace_back(score_index.second);
                    } else {
                        v_victory.emplace_back(score_index.second);
                    }
                }
                std::cout << "编号: " << score_index.second << " 姓名: " << m_speakers[score_index.second].m_name << " 成绩: " << m_speakers[score_index.second].m_score[m_index-1] << std::endl;
                ++count;
            }

            group_score.clear();
            std::cout << std::endl;
        }
    }

    std::cout << "---------第 " << m_index << " 轮比赛完毕: ---------------" << std::endl;
    Funcs::pause();
}

void speech_manager::speech_draw() {
    std::cout << "第 << " << m_index << " >> 轮比赛选手正在抽签" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    std::cout << "抽签后演讲顺序如下: " << std::endl;

    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    if(m_index == 1) {
        std::shuffle(v1.begin(), v1.end(), std::default_random_engine(seed));

        for(auto&& sp_index: v1) {
            std::cout << sp_index << " ";
        }
        std::cout << std::endl;
    } else {
        std::shuffle(v2.begin(), v2.end(), std::default_random_engine(seed));
        for(auto&& sp_index: v2) {
            std::cout << sp_index << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "--------------------------------" << std::endl;
    Funcs::pause();
}

void speech_manager::show_score() {
    std::cout << "----------第" << m_index << "轮晋级选手信息如下: -------------" << std::endl;
    std::vector<int> v;
    if(m_index == 1) {
        v = v2;
    }else {
        v = v_victory;
    }

    for(auto&& speech_index: v) {
         std::cout << "选手编号: " << speech_index << " 选手姓名: " << m_speakers[speech_index].m_name << " 得分: "
            << m_speakers[speech_index].m_score[m_index-1] << std::endl;
    }

    std::cout << std::endl;
    Funcs::pause();
    Funcs::clear();
}

void speech_manager::save_record() {
    std::ofstream ofs;
    ofs.open("speech.csv", std::ios::out | std::ios::app);
    for(auto&& speech_index: v_victory) {
        ofs << speech_index << "," << m_speakers[speech_index].m_score[1] << ",";
    }
    ofs << std::endl;
    ofs.close();
    std::cout << "记录已经保存" << std::endl;
    m_file_empty = false;
}

void speech_manager::load_record() {
    std::ifstream ifs {"speech.csv", std::ios::in};
    if(!ifs.is_open()) {
        m_file_empty = true;
        std::cout << "往届记录文件不存在" << std::endl;
        ifs.close();
        return;
    }

    char ch;
    ifs >> ch;
    if(ifs.eof()) {
        std::cout << "文件为空" << std::endl;
        m_file_empty = true;
        ifs.close();
        return;
    }

    m_file_empty = false;
    // 刚才读的那个字符放回去
    ifs.putback(ch);

    std::string line;
    int index = 0;
    while(ifs >> line) {
        std::vector<std::string> v{};
        pystring::split(line, v, ",");
        m_record.insert({index, v});
        ++index;
    }
    ifs.close();
}

void speech_manager::show_record() {

    if(m_file_empty) {
        std::cout << "文件不存在，或记录为空" << std::endl;
        return;
    }

    for(int i=0; i<m_record.size(); ++i) {
        std::cout << "第" << i+1 << "届 "
            << "冠军编号: " << m_record[i][0] << " 得分: " << m_record[i][1] 
            << " 亚军编号: " << m_record[i][2] << " 得分: " << m_record[i][3]
            << " 季军编号: " << m_record[i][4] << " 得分: " << m_record[i][5]
            << std::endl;
    }
    Funcs::pause();
    Funcs::clear(); 
}

void speech_manager::clear_record() {
    std::cout << "确认清空?" << std::endl;
    std::cout << "1.确认" << std::endl;
    std::cout << "2.返回" << std::endl;
    int select;
    std::cin >> select;
    // 选择确认清空
    if(select == 1) {
        std::ofstream ofs {"speech.csv", std::ios::trunc};
        ofs.close();
        init_speech();
        create_speaker();
        load_record();
        std::cout << "清空成功" << std::endl;
    }
    Funcs::pause();
    Funcs::clear();
}