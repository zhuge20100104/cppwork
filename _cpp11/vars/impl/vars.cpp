#include "vars/vars.h"

#include <iostream>


Vars def_vars() {
    Vars vars;
    return std::move(vars);
}