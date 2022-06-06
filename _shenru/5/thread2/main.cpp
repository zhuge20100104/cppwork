#include <iostream>
#include <mutex>
#include <cstdlib>

using std::ostream;
using std::cout;
using std::endl;

class Complex {
    friend ostream& operator<< (ostream& os, const Complex& c);
    public:
        Complex(): m_i(0) {}
        Complex(int i): m_i(i) {}
        Complex(const Complex& c): m_i(c.m_i) {}
        Complex& operator=(const Complex& c) {
            m_i = c.m_i;
            return *this;
        }

        void mulWithHolder(int x) {
            m_i *= x;
        }

        void mul(int x) {
            std::lock_guard<std::mutex> lock(m_mutex);
            mulWithHolder(x);
        }

        void divWithHolder(int x) {
            m_i /= x;
        }

        void div(int x) {
            std::lock_guard<std::mutex> lock(m_mutex);
            divWithHolder(x);
        }

        void both(int x, int y) {
            std::lock_guard<std::mutex> lock(m_mutex);
            mulWithHolder(x);
            divWithHolder(y);
        }


    private:
        int m_i;
        std::mutex m_mutex;
};

ostream& operator<< (ostream& os, const Complex& c) {
    os << c.m_i;
    return os;
}

int main(void) {
    Complex c = 10;
    c.both(32, 23);
    cout << c << endl;

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}
