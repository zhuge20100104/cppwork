#include "cal.h"

int AddCal::getResult() {
    return m_Num1 + m_Num2;    
}

int SubCal::getResult() {
    return m_Num1 - m_Num2;
}

int MulCal::getResult() {
    return m_Num1 * m_Num2;
}