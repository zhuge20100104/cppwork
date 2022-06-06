#include "utils/computer.h"
#include "utils/intel.h"
#include "utils/lenovo.h"

#include <cstdlib>

int main(int argc, char* argv[]) {

    // Intel电脑
    Computer interC(CPUPtr(new IntelCPU), MemoryPtr(new IntelMemory()), VideoPtr(new IntelVideocard));
    interC.work();
    cout << "---------------------------------------------------------------" << endl;

    // 联想电脑
    Computer lenovoC(CPUPtr(new LenovoCPU), MemoryPtr(new LenovoMemory), VideoPtr(new LenovoVideocard));
    lenovoC.work();
    cout << "---------------------------------------------------------------" << endl;
    
    // 组装电脑
    Computer mixC(CPUPtr(new LenovoCPU), MemoryPtr(new IntelMemory), VideoPtr(new LenovoVideocard));
    mixC.work();
    cout << "---------------------------------------------------------------" << endl;
    
    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}
