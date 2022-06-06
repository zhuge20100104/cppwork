#include "utils/speech_manager.h"
#include "utils/funcs.h"

#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[]) {

    srand((unsigned int)time(nullptr));
    speech_manager sm;

    int choice {};
    while(true) {
        sm.show_menu();
        std::cout << "请输入您的选择: " << std::endl;
        std::cin >> choice;
        switch (choice) {
        case 1:
            sm.start_speech();
            break;
        case 2:
            sm.show_record();
            break;
        case 3:
            sm.clear_record();
            break;
        case 0:
            sm.exit_system();
            break;
        default:
            Funcs::clear();
            break;
        }
    }
    

    Funcs::pause();
    
    return EXIT_SUCCESS;
}