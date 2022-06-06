#include <boost/function.hpp>

#include <functional>

typedef void (*func_t) (int);

void process_integers(func_t f);

// 函数对象
class int_processor: public std::unary_function<int, void> {
    const int min_;
    const int max_;
    bool& triggered_;

public:
    int_processor(int min, int max, bool& triggered):
        min_(min),
        max_(max),
        triggered_(triggered) {
    }

    void operator()(int i) const {
        if(i < min_ || i > max_) {
            triggered_ = true;
        }
    }
};

// 定义函数对象别名
typedef boost::function<void(int)> fobject_t;

void process_integers(const fobject_t& f);

int main(int argc, char* argv[]) {
    bool is_triggered = false;
    int_processor fo(0, 200, is_triggered);
    process_integers(fo);
    assert(is_triggered);
}

void process_integers(const fobject_t& f) {
    static const int data[] = {1, 2, 3, 4, 5, 250};
    std::for_each(data, data + sizeof(data)/sizeof(int), f);
}

