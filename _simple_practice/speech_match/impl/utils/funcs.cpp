#include "utils/funcs.h"

#include <iostream>

void Funcs::pause() {
#ifdef WINDOWS
    (void)std::system("pause");
#else
    (void)std::system("read");
#endif
}

void Funcs::clear() {
#ifdef WINDOWS
    (void)std::system("cls");
#else
    (void)std::system("clear");
#endif
}