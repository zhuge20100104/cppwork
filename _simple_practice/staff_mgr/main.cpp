#include "utils/work_manager.h"
#include "utils/boss.h"
#include "utils/employee.h"
#include "utils/manager.h"
using std::cin;
#include <cstdlib>

int main(int argc, char* argv[]) {
    
    WorkManager wm;

    int choice = 0;

    while(true) {
        wm.showMenu();
        cout << "请输入您的选择: " << endl;
        cin >> choice;

        switch (choice)
        {
        case 0:  // 退出系统
            wm.exitSystem();
            break;
        
        case 1:  // 添加职工
            wm.Add_Emp();
            break;
        
        case 2:  // 显示职工
            wm.show_Emp();
            break;

        case 3:  // 删除职工 
            wm.Del_Emp();
            break;
        
        case 4: // 修改职工
            wm.Mod_Emp();
            break;
        
        case 5: // 查找职工
            wm.Find_Emp();
            break;
        
        case 6: // 排序职工
            wm.Sort_Emp();
            break;
        
        case 7: // 清空文件
            wm.Clean_File();
            break;
            
        default:
            // 默认清屏
            wm.clearScreen();
            break;
        }
    }

    wm.pause();
    return 0;
}