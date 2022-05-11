#include <iostream>


class RuleOfFive {
    public:
        RuleOfFive(const RuleOfFive& rof) {
            std::cout << "拷贝构造函数被调用..." << std::endl;
        }

        RuleOfFive& operator=(const RuleOfFive& rof) {
            return *this;
        }

        RuleOfFive() {
            std::cout << "默认构造函数被调用..." << std::endl;
        }

        ~RuleOfFive() {}
};
int main() {
    RuleOfFive r1;
    RuleOfFive r2 = std::move(r1);
}
