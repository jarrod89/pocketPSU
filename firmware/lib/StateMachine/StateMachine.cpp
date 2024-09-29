#include "StateMachine.hpp"
#include <Arduino.h>

StateMachine::StateMachine() : currentState{
        SettingState::IDLE,     // Default to IDLE state for settingState
        KnobState::COARSE,      // Default to COARSE for knobState
        ChannelState::IDLE,    // Default to IDLE for channel1State
        ChannelState::IDLE     // Default to IDLE for channel2State
    } {}

void StateMachine::handleCh1OnBt() {
    switch (currentState.channel1State) {
        case ChannelState::IDLE:
            currentState.channel1State = ChannelState::ON;
            break;
        case ChannelState::ON:
            currentState.channel1State = ChannelState::IDLE;
            break;
    }
}

void StateMachine::handleCh2OnBt() {
    switch (currentState.channel2State) {
        case ChannelState::IDLE:
            currentState.channel2State = ChannelState::ON;
            break;
        case ChannelState::ON:
            currentState.channel2State = ChannelState::IDLE;
            break;
    }
}

void StateMachine::handleCh1SetBt() {
    switch (currentState.settingState) {
        case SettingState::IDLE:
            currentState.settingState = SettingState::SET_CURRENT_CH_2;
            break;
        case SettingState::SET_CURRENT_CH_1:
            currentState.settingState = SettingState::SET_CURRENT_CH_2;
            break;
        case SettingState::SET_VOLTAGE_CH_1:
            currentState.settingState = SettingState::SET_CURRENT_CH_2;
            break;
        case SettingState::SET_CURRENT_CH_2:
            currentState.settingState = SettingState::SET_VOLTAGE_CH_2;
            break;
        case SettingState::SET_VOLTAGE_CH_2:
            currentState.settingState = SettingState::IDLE;
            break;
    }
}

void StateMachine::handleCh2SetBt() {
    switch (currentState.settingState) {
        case SettingState::IDLE:
            currentState.settingState = SettingState::SET_CURRENT_CH_1;
            break;
        case SettingState::SET_CURRENT_CH_1:
            currentState.settingState = SettingState::SET_VOLTAGE_CH_1;
            break;
        case SettingState::SET_VOLTAGE_CH_1:
            currentState.settingState = SettingState::IDLE;
            break;
        case SettingState::SET_CURRENT_CH_2:
            currentState.settingState = SettingState::SET_CURRENT_CH_1;
            break;
        case SettingState::SET_VOLTAGE_CH_2:
            currentState.settingState = SettingState::SET_CURRENT_CH_1;
            break;
    }
}