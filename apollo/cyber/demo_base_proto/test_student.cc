#include "cyber/demo_base_proto/student.pb.h"
#include <iostream>


int main(int argc, char* argv[]) {
    apollo::cyber::demo_base_proto::Student stu;
    // 写数据
    stu.set_name("张三");
    stu.set_age(18);
    stu.set_height(1.75);
    stu.add_books("语文");
    stu.add_books("python");
    stu.add_books("C++");
    stu.add_books("Matlab");

    // 读数据
    auto name = stu.name();
    auto age = stu.age();
    auto height = stu.height();
    std::cout << name << " == " << age << " == " << height << " == ";
    std::cout << std::endl;
    
    for(auto const& book: stu.books()) {
        std::cout << book << " - "; 
    }

    std::cout << std::endl;
    return EXIT_SUCCESS;
}