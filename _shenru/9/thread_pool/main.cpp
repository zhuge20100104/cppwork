#include "thread_pool.hpp"

#include <iostream>
#include <fstream>
#include <chrono>
#include <string>


int main() {

    ThreadPool pool;

    for(int i=0; i<20; ++i) {
        pool.AddTask(
                    [i] ()  {
                        std::string fname = std::to_string(i);
                        fname += ".txt";

                        std::ofstream ofs(fname, std::ios::out | std::ios::app);

                        ofs << std::this_thread::get_id() << ": ["<< i << "]" << std::endl;

                        ofs.close();
                    }
                );
    }
    
    // 真正的服务器程序是不会退出的，这里不用sleep  
    std::this_thread::sleep_for(std::chrono::seconds(2));
}


