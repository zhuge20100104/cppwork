#include "timer.hpp"
#include <iostream>
using std::cout;
using std::endl;

void func() {
    cout << "Hello World" << endl;
}

void Test() {
    cout << "\nTest()\n";
    auto now = _time::system_clk::now();
    
    _time::Timer t;
    
    // 测试字符串格式化
    std::string res;
    t.to_string(now, _time::TIME_FORMAT, res);
    cout << res << endl;

    // 测试字符串转时间
    _time::_time_point pt;
    t.from_string("2020-12-13 09:30:35", _time::TIME_FORMAT, pt);
    t.to_string(pt, _time::TIME_FORMAT, res);
    cout << res << endl;

    // 测试计算函数运行时间
    t.reset();
    func();
    cout << t.elapsed_micro() << " 微秒" << endl;
    cout << t.elapsed() << " 毫秒" << endl;
    cout << t.elapsed_nano() << " 纳秒" << endl;
}

int main(void) {
    Test();

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}