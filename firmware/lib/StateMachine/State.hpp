#pragma once

enum class SettingState {
    IDLE,
    SET_CURRENT_CH_1,
    SET_VOLTAGE_CH_1,
    SET_CURRENT_CH_2,
    SET_VOLTAGE_CH_2
};

enum class KnobState {
    FINE,
    COARSE
};

enum class ChannelState {
    IDLE,
    ON
};

struct StateStruct {
    SettingState settingState;
    KnobState knobState;
    ChannelState channel1State;
    ChannelState channel2State;
};