#ifndef COMPONENT_TIMER_TIMER_CPT_H
#define COMPONENT_TIMER_TIMER_CPT_H
#include "cyber/component/component.h"
#include "cyber/component/timer_component.h"

using apollo::cyber::Component;
using apollo::cyber::TimerComponent;

class MyTimer: public TimerComponent {
public:
    bool Init() override;
    bool Proc() override;
private:
    int seq;
};

CYBER_REGISTER_COMPONENT(MyTimer)

#endif