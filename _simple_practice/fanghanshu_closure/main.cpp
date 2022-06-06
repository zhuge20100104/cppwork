#include <iostream>
using std::cout;
using std::endl;

#include <cstdlib>
#include <string>
using std::string;

// MyAdd 加法仿函数
class MyAdd {
    public:
        int operator() (int a, int b) {
            return a + b;
        }
};

class MyPrint{
    private:
        int m_count = 0;
        
    public:
        void operator()(string test) {
            cout << test << endl;
            m_count ++;
        }

        int getCount() const {
            return m_count;
        }
};

int main(void) {

    cout << "1 + 2 =" << MyAdd()(1, 2) << endl;

    // 仿函数可以保存状态，类似闭包
    MyPrint print;
    print("测试1");
    print("测试2");
    print("测试3");
    cout << "一共调用print函数: " << print.getCount() << "次" << endl;

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}