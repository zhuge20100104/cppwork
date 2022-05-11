#ifndef _FREDRIC_ACCOUNT_H_
#define _FREDRIC_ACCOUNT_H_

#include <string>

class Account {
    std::string m_Name; //用户名
    int m_AccNo; // 用户账号
    static int m_ANGenerator; // 账号生成数

protected:
    float m_Balance;   //余额

public:
    Account(const std::string& name, float balance);
    virtual ~Account(); 

    const std::string GetName() const; 
    int GetAccountNo() const;
    float GetBalance() const;

    virtual void Deposit(float amount);  // 存款
    virtual void WithDraw(float amount);  //取款

    virtual float GetInterestRate() const; //获取利息率
    virtual void AccumulateInterest(); //计算利息
    
};
#endif