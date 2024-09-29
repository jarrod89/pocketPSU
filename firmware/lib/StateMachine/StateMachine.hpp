#pragma once

#include "State.hpp"

class StateMachine {
    public:
        StateMachine();
        void handleCh1OnBt();
        void handleCh2OnBt();
        void handleCh1SetBt();
        void handleCh2SetBt();
        StateStruct getState() const { return currentState; };

    private:
        StateStruct currentState;
};