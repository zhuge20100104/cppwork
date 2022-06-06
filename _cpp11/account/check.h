#ifndef _FREDRIC_CHECK_H_
#define _FREDRIC_CHECK_H_

#include "account.h"

class Checking: public Account {
    float m_MiniumBalance;

public:
    Checking(const std::string& name, float balance, float minBalance);
    ~Checking();
    virtual void WithDraw(float amount) override;
    float GetMiniumBalance() const;
};

#endif