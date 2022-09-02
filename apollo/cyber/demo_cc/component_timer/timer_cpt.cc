#include "cyber/demo_cc/component_timer/timer_cpt.h"

bool MyTimer::Init() {
    AINFO << "Timer component init ...";
    seq = 0;
    return true;
}

bool MyTimer::Proc() {
    ++seq;
    AINFO << "------------------------------" << seq;
    if(!(seq%10)) {
        AINFO << "trigger a 10 time seq";
    }
    return true;
}

