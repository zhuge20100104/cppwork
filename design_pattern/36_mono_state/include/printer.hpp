#ifndef _FREDRIC_MONO_PRINTER_HPP_
#define _FREDRIC_MONO_PRINTER_HPP_

#include <iostream>

// 别这么干，原因有二
// 1. static字段无法继承，只能继承 get/set方法
// 2. 客户也不知道这是单例，你也无法通知客户
class Printer {
    static int id;
public:
    int get_id() const {
        return Printer::id;
    }
    void set_id(int value) {
        Printer::id = value;
    }
};

int Printer::id = 0;

#endif