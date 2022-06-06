#ifndef _FREDRIC_INTEGER_H_
#define _FREDRIC_INTEGER_H_

class Integer {
    int *m_pInt;

    public:
        Integer();
        Integer(int value);
        int get_value() const;
        void set_value(int value);

        Integer(Integer const& rhs);
        Integer& operator=(Integer const& rhs);
        Integer(Integer&& rhs);
        Integer& operator=(Integer&& rhs);
        ~Integer();
};

#endif