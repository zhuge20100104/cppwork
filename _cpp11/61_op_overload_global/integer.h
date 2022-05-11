#ifndef _FREDRIC_INTEGER_H_
#define _FREDRIC_INTEGER_H_
class Integer {
    int* m_pint;
    public:
        Integer();
        Integer(int value);
        Integer(Integer const& obj);
        Integer& operator=(Integer const& obj); 
        Integer(Integer&& obj);
        Integer& operator=(Integer&& obj) ;

        Integer operator+(Integer const& a) const;
        // 左加操作符重载，加在当前值身上，返回一个引用
        Integer& operator++();

        // 右加操作符重载，返回一个临时值，是加之前的值
        Integer operator++(int);

        // 相等操作符重载
        bool operator==(Integer const& other);
        int get_value() const;
        void set_value(int value);
        ~Integer();
};
#endif