#include <cstdlib>
#include <iostream>

#include "utils/func.h"
#include "utils/consts.h"

int main(int argc, char* argv[]) {
    int select = 0;

    while (true) {
        std::cout << "===================欢迎来到Fredric的机房预约系统========="
                     "=============="
                  << std::endl;
        std::cout << std::endl << "请输入您的身份" << std::endl;
        std::cout << "\t\t---------------------------------------------\n";
        std::cout << "\t\t|                                            |\n";
        std::cout << "\t\t|               1.学生代表                    |\n";
        std::cout << "\t\t|                                            |\n";
        std::cout << "\t\t|               2.老师                        |\n";
        std::cout << "\t\t|                                            |\n";
        std::cout << "\t\t|               3.管理员                      |\n";
        std::cout << "\t\t|                                            |\n";
        std::cout << "\t\t|               0.退出                        |\n";
        std::cout << "\t\t---------------------------------------------\n";
        std::cout << "请输入您的选择: ";

        std::cin >> select;
        switch(select) {
            case 1:  // 学生身份
                Funcs::login_in(student_file, 1);
                break;
            case 2:  // 老师身份
                Funcs::login_in(teacher_file, 2);
                break;
            case 3:  //  管理员
                Funcs::login_in(admin_file, 3);
                break;
            case 0:  //  退出系统
                std::cout << "欢迎下次使用" << std::endl;
                Funcs::pause();
                return EXIT_SUCCESS;
                break;
            default:
                std::cout << "输入有误，请重新选择!" << std::endl;
                Funcs::pause();
                Funcs::clear();
                break;
        }

    }

    Funcs::pause();
    return EXIT_SUCCESS;
}
