#ifndef _FREDRIC_INTEGER_H_
#define _FREDRIC_INTEGER_H_
class Integer {
    int* m_pint;
    public:
        Integer();
        Integer(int value);
        Integer(Integer const& obj);
        Integer(Integer&& obj);
        int get_value() const;
        void set_value(int value);
        ~Integer();
};
#endif