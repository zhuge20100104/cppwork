#include "utils/coffee.h"
#include "utils/tea.h"
#include <cstdlib>
#include <memory>

using DrinkPtr = std::shared_ptr<AbsDrink>;

void DoWork(const DrinkPtr & ptr) {
    ptr->MakeDrink();
}

int main(int argc, char* argv[]) {

    DoWork(DrinkPtr(new Coffee));

    cout << "------------------------------------" << endl;

    DoWork(DrinkPtr(new Tea));

    cout << "请按任意键继续..." << endl;
    getchar();
    return 0;
}