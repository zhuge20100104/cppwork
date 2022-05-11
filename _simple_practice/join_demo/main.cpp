#include <thread>
#include <iostream>
#include <vector>
#include <chrono>

void print_id(int i) {
    for(int j=0; j<10; ++j) {
        std::cerr << "Current Thread: " << i << "\n";
        std::cerr << "Current Thread Id: " << std::this_thread::get_id() << "\n";

        std::this_thread::sleep_for(std::chrono::seconds(10));
    }
}


int main(int argc, char* argv[]) {

    std::vector<std::thread> t_groups;
    t_groups.reserve(10);

    for(int i=0; i<10; ++i) {
        t_groups.emplace_back(std::move(
            std::thread(print_id, (i+1))
        ));
    }

    for(int i=0; i<10; ++i) {
         t_groups[i].join();
    }
    return EXIT_SUCCESS;
}

