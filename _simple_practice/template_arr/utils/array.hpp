#ifndef _ARRAY_HPP_
#define _ARRAY_HPP_
#include <iostream>
using std::cout;
using std::endl;

namespace utils {
    template <class T>
    class Array{
        public:
            // 默认构造函数
            Array(int capacity): m_Capacity(capacity), m_Size(0), pAddress(new T[capacity]) {}

            // 析构函数
            ~Array() {
                if(this->pAddress != nullptr) {
                    delete [] pAddress;
                    pAddress = nullptr;
                    m_Capacity = 0;
                    m_Size = 0;
                }
            }

            // 拷贝构造函数
            Array(const Array& arr) {
                this->m_Capacity = arr.getCapacity();
                this->m_Size = arr.getSize();
                this->pAddress = new T[this->m_Capacity];

                for(int i=0; i<this->m_Size; i++) {
                    this->pAddress[i] = arr.pAddress[i];
                }
            }

            // 重载=操作符，避免浅拷贝
            Array& operator=(const Array& arr) {
                if(this->pAddress != nullptr) {
                    delete [] pAddress;
                    pAddress = nullptr;
                    this->m_Capacity = 0;
                    this->m_Size = 0;
                }
                this->m_Capacity = arr.getCapacity();
                this->m_Size = arr.getSize();

                pAddress = new T[this->m_Capacity];
                for(int i=0; i<this->m_Size; i++) {
                    this->pAddress[i] = arr.pAddress[i];
                }
                return *this;
            }

            // 重载 [] 操作符
            T& operator[](int index) const {
                return pAddress[index];
            }

            // 尾插法
            void push_back(const T& val) {
                if(this->m_Capacity == m_Size) {
                    cout << "数组已满" << endl;
                    return;
                }
                this->pAddress[m_Size] = val;
                m_Size++;
            }

            // 尾删法
            void pop_back() {
                if(this->m_Size == 0) {
                    cout << "数组已空" << endl;
                    return;
                }
                this->m_Size --;
            } 

            // 获取容量大小
            int getCapacity() const {
                return this->m_Capacity;
            }

            // 获取当前数组大小
            int getSize() const {
                return this->m_Size;
            }

        private:
            T* pAddress; // 指向一个堆空间，这个空间存储真正的数据
            int m_Capacity;  // 数组容量大小
            int m_Size; // 指向数组大小
    };
};

#endif