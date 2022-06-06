#ifndef _COMPUTER_H_
#define _COMPUTER_H_
#include <memory>


class CPU;
class VideoCard;
class Memory;

using CPUPtr = std::shared_ptr<CPU>;
using MemoryPtr = std::shared_ptr<Memory>;
using VideoPtr = std::shared_ptr<VideoCard>; 

class CPU {
    public:
        // 抽象的计算函数
        virtual void calculate() = 0;
};

class VideoCard {
    public:
        // 抽象的显示函数
        virtual void display() = 0;
};

class Memory {
    public:
        // 抽象的存储函数
        virtual void storage() = 0;
};


class Computer{
    public:
        Computer(CPUPtr cpu, MemoryPtr memory, VideoPtr video): m_CPU(cpu), m_Memory(memory), m_Video(video) {
        }

        void work();
    private:
        CPUPtr m_CPU;
        MemoryPtr m_Memory;
        VideoPtr m_Video;
};

void Computer::work() {
    m_CPU->calculate();
    m_Memory->storage();
    m_Video->display();
}

#endif