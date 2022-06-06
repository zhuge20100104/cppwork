#include "myint.h"


MyInt::MyInt(): mNum(0) {

}

MyInt::MyInt(int a): mNum(a) {

}

MyInt& MyInt::operator++(){
    this->mNum++;
    return *this;
}

MyInt MyInt::operator++(int){
    MyInt tmp = *this; // 保存上一次的值 
    this->mNum++;
    return tmp;
}
