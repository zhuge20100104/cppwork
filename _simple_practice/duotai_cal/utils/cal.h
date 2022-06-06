#ifndef _CAL_H_
#define _CAL_H_

class AbsCal {
    public:
        int m_Num1;
        int m_Num2;

        virtual int getResult()=0;
};


class AddCal: public AbsCal {
    public:
        int getResult();
};


class SubCal: public AbsCal {
    public:
        int getResult();
};

class MulCal: public AbsCal {
    public:
        int getResult();
};

#endif