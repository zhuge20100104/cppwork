#include <boost/function.hpp>

#include <deque>
#include <cassert>
#include <algorithm>

using fobject_t = boost::function<void(int)>;

// 接受函数对象的函数，处理整型
void process_integers(const fobject_t& f);

int main(int argc, char* argv[]) {
    // 空的lambda 表达式，啥也不干
    process_integers([](int /*i*/){});
    // 存储引用的lambda表达式
    std::deque<int> ints;
    process_integers([&ints](int i){
        ints.push_back(i);
    });

    // 修改内容并获取匹配个数的lambda表达式
    std::size_t matched_count = 0;
    process_integers([ints, &matched_count](int i) mutable {
        if(ints.front() == i) {
            ++ matched_count;
        }
        ints.pop_front();
    });
    // 验证从前到后共有 6 个元素相等
    assert(matched_count == 6); 
}

void process_integers(const fobject_t& f) {
    static const int data[] = {1, 2, 3, 4, 5, 200, 0};
    // 在这个例子中，我们仅仅使用前6个元素
    std::for_each(data, data + 6, f);
}


