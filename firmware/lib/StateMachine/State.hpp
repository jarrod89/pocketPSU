#pragma once

enum class SettingState {
    IDLE,
    SET_CURRENT_CH_1,
    SET_VOTLAGE_CH_1,
    SET_CURRENT_CH_2,
    SET_VOLTAGE_CH_2
};

enum class KnobState {
    FINE,
    COARSE
};

enum class Channel1State {
    IDLE,
    ON
};

enum class Channel2State {
    IDLE,
    ON
};

struct StateStruct {
    SettingState settingState;
    KnobState knobState;
    Channel1State channel1State;
    Channel2State channel2State;
};