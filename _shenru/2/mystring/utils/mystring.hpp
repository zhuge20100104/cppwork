#include <iostream>
#include <vector>
#include <cstring>

using std::ostream;
using std::cout;
using std::endl;

class MyString {
    friend ostream& operator<<(ostream& cout, const MyString& str);
    private:
        char *m_data;
        size_t m_len;

        void copy_data(const char* s) {
            m_data = new char[m_len+1];
            memcpy(m_data, s, m_len);
            m_data[m_len] = '\0';
        }

    public:
        MyString() {
            m_data = nullptr;
            m_len = 0;
        }

        MyString(const char* p) {
            m_len = strlen(p);
            copy_data(p);
        }

        MyString(const MyString& str) {
            m_len = str.m_len;
            copy_data(str.m_data);
            cout << "Copy Contructor is called!Source: " << str.m_data << endl;
        }
        
        MyString operator=(const MyString& str) {
            // 说明不是同一个string，可以做赋值
            if(this != &str) {
                this->m_len = str.m_len;
                copy_data(str.m_data);
            }
            cout << "Copy assignment called, source: " << str.m_data << endl;
            return *this;
        }

        // 移动构造函数
        MyString(MyString&& str) {
            m_data = str.m_data;
            m_len = str.m_len;

            str.m_data = nullptr;
            str.m_len = 0;
        }

        // 移动赋值操作符重载
        MyString operator=(MyString&& str) {
            // 说明两个不是同一个对象
            if(this != &str) {
                this->m_data = str.m_data;
                this->m_len = str.m_len;
                str.m_data = nullptr;
                str.m_len = 0;
            }
            return *this;
        }

        virtual ~MyString() {
            if(m_data != nullptr) {
                delete [] m_data;
                m_data = nullptr;
                m_len = 0;
            } 
        }



};

ostream& operator<<(ostream& cout, const MyString& s) {
    cout << s.m_data;
    return cout;
}
