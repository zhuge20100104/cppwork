#ifndef _COPY_H_
#define _COPY_H_


class Copy {
    // 编译器默认生成 默认构造函数
    // 拷贝构造函数
    // 默认赋值操作符
    int * m_A; 


    public:
    explicit Copy(int* a):m_A(a) {}


        ~Copy() {
            if(m_A!=nullptr) {
                delete m_A;
                m_A = nullptr;
            }
        }
};


class DeepCopy {

    int m_A;
    public:
        
    explicit DeepCopy(int* a):m_A(a) {}

    DeepCopy(const DeepCopy& rhs)  {
        this->m_A = new int(*rhs.m_A);
    }

    DeepCopy& operator=(const DeepCopy& rhs) {
        if(this->m_A != nullptr) {
            delete this->m_A;
            this->m_A = nullptr;
        }
        this->m_A = new int(*rhs.m_A);
        return *this;
    }
    ~DeepCopy() {
        if(m_A!=nullptr) {
            delete m_A;
            m_A = nullptr;
        }
    }
        



        
};
#endif 
