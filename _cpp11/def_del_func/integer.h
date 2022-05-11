#ifndef _FREDIRC_INTEGER_H_
#define _FREDIRC_INTEGER_H_

class Inetger {
    int m_value {0};

    public:
        Inetger() = default;
        Inetger(int value): m_value{value} {}

        // 不允许拷贝构造
        Inetger(Inetger const& rhs) = delete;

        void set_value(int value) {
            m_value = value;
        }
        // 不允许设置浮点数
        void set_value(float value) = delete;

        int get_value() const {
            return m_value;
        }
};

#endif