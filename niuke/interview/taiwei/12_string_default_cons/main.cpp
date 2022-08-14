#include <algorithm>
#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include <string.h>

using namespace std;

class String {
public:
    String(const char* str=nullptr) {
        if(!str) {
            m_data = nullptr;
            return;
        }

        int len = strlen(str)+1;
        m_data = new char[len];
        memcpy(m_data, str, len);
    }

    size_t get_size() const {
        if(!m_data) {
            return 0;
        }
        int len = strlen(m_data)+1;
        return len;
    }

    char* get_data() const{
        return m_data;
    } 

    ~String() {
        if(m_data) {
            delete [] m_data;
            m_data = nullptr;
        }
        
    }

    String(String const& src) {
        auto size_ = src.get_size();
        m_data = new char[size_];
        memcpy(m_data, src.get_data(), size_);
    }

    String& operator= (String const& src) {
        // 自己给自己赋值, return
        if(src.get_data() == m_data) {
            return *this;
        }

        delete [] m_data;
        m_data = nullptr;
        
        if(!src.m_data) {    
            return *this;
        }
        
        auto size_ = src.get_size();
        m_data = new char[size_];
        memcpy(m_data, src.get_data(), size_);
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, String const& str) {
        os << str.m_data;
        return os;
    }
private:
    char* m_data;
};

int main(int argc, char* argv[]) {
    String s = "Hello";
    String s1 = s;
    String s2(s1);

    cout << "s: " << s << endl;
    cout << "s1: " << s1 << endl;
    cout << "s2: " << s2 << endl;
    return EXIT_SUCCESS;
}