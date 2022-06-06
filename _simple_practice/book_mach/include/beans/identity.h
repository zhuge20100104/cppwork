#ifndef _FREDRIC_IDENTITY_H_
#define _FREDRIC_IDENTITY_H_

#include <string>

struct identity {
    // 操作菜单
    virtual void oper_menu() = 0;
    
    std::string m_name;
    std::string m_pwd;
}; 
#endif