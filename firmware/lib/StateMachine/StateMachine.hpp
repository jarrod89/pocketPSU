#pragma once

#include "State.hpp"

class StateMachine {
    public:
        StateMachine();
        static void handleCh1OnBt();
        static void handleCh2OnBt();
        static void handleCh1SetBt();
        static void handleCh2SetBt();
        void getState();

    private:
        SettingState settingState;
        KnobState knobState;
        Channel1State channel1State;
        Channel2State channel2State;
};

// Constructor definition
StateMachine::StateMachine()
    : settingState(SettingState::IDLE),
      knobState(KnobState::COARSE),
      channel1State(Channel1State::IDLE),
      channel2State(Channel2State::IDLE)
{}