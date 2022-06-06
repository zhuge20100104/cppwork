#ifndef _FREDRIC_CLASSIC_STATE_IMPL_HPP_
#define _FREDRIC_CLASSIC_STATE_IMPL_HPP_

#include <iostream>
#include <string>

class LightSwitch;

struct State {
    // 在on的时候再on，调用默认行为
    virtual void on(LightSwitch* ls) {
        std::cout << "Light is already on\n";
    }

    // 在off的时候再off，调用默认行为
    virtual void off(LightSwitch* ls) {
        std::cout << "Light is already off\n";
    }
};

struct OnState: State{
    OnState() {
        std::cout << "Light turned on\n";
    }

    void off(LightSwitch* ls) override;
};

struct OffState: State{
    OffState() {
        std::cout << "Light turned off\n";
    }

    void on(LightSwitch* ls) override;
};

class LightSwitch {
    State* state; 
public:
    LightSwitch() {
        state = new OffState();
    }

    void set_state(State* state) {
        this->state = state;
    }

    void on() {
        state->on(this);
    }

    void off() {
        state->off(this);
    }
};

// On状态off,会去掉子类的off方法
void OnState::off(LightSwitch* ls) {
    std::cout << "Switching light off...\n";
    ls->set_state(new OffState());
    delete this;
}

// Off状态on, 会去掉子类的on方法
void OffState::on(LightSwitch* ls) {
    std::cout << "Switching light on...\n";
    ls->set_state(new OnState());
    delete this;
}
#endif