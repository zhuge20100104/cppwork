#include <iostream>
using std::cout;
using std::endl;
#include <thread>
#include <utility>
#include <future>
#include <vector>
#include <cstdlib>

int func(int x) {
    return x+2;
}

int main(void) {
    std::packaged_task<int(int)> task(func);
    std::future<int> fu = task.get_future();
    std::thread(std::move(task), 2).detach();

    int value = fu.get(); // 等待task完成并获取返回值
    cout << "The result is: " << value << endl;

    std::vector<std::shared_future<int> > v;
    std::shared_future<int> f = std::async(std::launch::async, [](int a, int b) {return a+b; }, 2, 3);
    v.emplace_back(f);

    cout << "The shared feature result is: " << v[0].get() << endl;
    
    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}
