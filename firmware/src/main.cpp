#include <Arduino.h>
#include <ESP32-TWAI-CAN.hpp>
#include <lvgl.h>
#if LV_USE_TFT_ESPI
#include <TFT_eSPI.h>
#endif

#include <Wire.h>
#include <PD_UFP.h>

#define PIN_FUSB302_INT   4

class PD_UFP_Log_c PD_UFP;

#define SERIAL_DEBUG 1

#include "StateMachine.hpp"

#define TFT_HOR_RES   240
#define TFT_VER_RES   320
#define TFT_ROTATION  LV_DISPLAY_ROTATION_270

#define SDA_PIN 2
#define SCL_PIN 3


// /*LVGL draw into this buffer, 1/10 screen size usually works well. The size is in bytes*/
// #define DRAW_BUF_SIZE (TFT_HOR_RES * TFT_VER_RES / 10 * (LV_COLOR_DEPTH / 8))
// uint32_t draw_buf[DRAW_BUF_SIZE / 4];

// /* LVGL calls it when a rendered image needs to copied to the display*/
// void my_disp_flush( lv_display_t *disp, const lv_area_t *area, uint8_t * px_map)
// {
//     /*Call it to tell LVGL you are ready*/
//     lv_display_flush_ready(disp);
// }

// /*use Arduinos millis() as tick source*/
// static uint32_t my_tick(void)
// {
//     return millis();
// }


// StateMachine state_machine;

// float voltage_limit_ch1;
// float current_limit_ch1;
// float voltage_limit_ch2;
// float current_limit_ch2;
// float voltage_ch1;
// float current_ch1;
// float power_ch1;
// float voltage_ch2;
// float current_ch2;
// float power_ch2;

// lv_obj_t *voltage_limit_ch1_label;
// lv_obj_t *current_limit_ch1_label;
// lv_obj_t *voltage_limit_ch2_label;
// lv_obj_t *current_limit_ch2_label;
// lv_obj_t *voltage_ch1_label;
// lv_obj_t *current_ch1_label;
// lv_obj_t *power_ch1_label;
// lv_obj_t *voltage_ch2_label;
// lv_obj_t *current_ch2_label;
// lv_obj_t *power_ch2_label;

// static lv_style_t style_normal;
// static lv_style_t style_active;


// volatile long encoderCtr = 0;

// void handleEncoder() {
//     if(digitalRead(ENCODER_A))
//     {
//         if(digitalRead(ENCODER_B))
//         encoderCtr++;
//         else
//         encoderCtr--;
//     }
//     else
//     {
//         if(digitalRead(ENCODER_B))
//         encoderCtr--;
//         else
//         encoderCtr++;
//     }
// }
// volatile unsigned long lastDebounceTimeCh1Set = 0;  // Variables to store last debounce time
// volatile unsigned long lastDebounceTimeCh2Set = 0;
// volatile unsigned long lastDebounceTimeCh1On = 0;
// volatile unsigned long lastDebounceTimeCh2On = 0;
// volatile unsigned long lastDebounceTimeOnOff = 0;

// const unsigned long debounceDelay = 200;  // Set debounce delay to 50ms

// void handleCh1SetBt() {
//     if ((millis() - lastDebounceTimeCh1Set) > debounceDelay) {
//         lastDebounceTimeCh1Set = millis();  // Update last debounce time
//         state_machine.handleCh1SetBt();  // Your existing function
//     }
// }

// void handleCh2SetBt() {
//     if ((millis() - lastDebounceTimeCh2Set) > debounceDelay) {
//         lastDebounceTimeCh2Set = millis();
//         state_machine.handleCh2SetBt();
//     }
// }

// void handleCh1OnBt() {
//     if ((millis() - lastDebounceTimeCh1On) > debounceDelay) {
//         lastDebounceTimeCh1On = millis();
//         state_machine.handleCh1OnBt();  // Call your state handling logic
//     }
// }

// void handleCh2OnBt() {
//     if ((millis() - lastDebounceTimeCh2On) > debounceDelay) {
//         lastDebounceTimeCh2On = millis();
//         state_machine.handleCh2OnBt();
//     }
// }

// void handleOnOffBt() {
//     if ((millis() - lastDebounceTimeOnOff) > debounceDelay) {
//         lastDebounceTimeOnOff = millis();
//         digitalWrite(LED_RED, !digitalRead(LED_RED));  // Toggle LED state
//     }
// }

// // void handleKnobBt() {
// //     digitalWrite(LED_RED, !digitalRead(LED_RED));  // Toggle LED state
// // }

// void highlight_active_label(lv_obj_t *label) {
//   // Apply the active style (black background, white text)
//   lv_obj_add_style(label, &style_active, LV_PART_MAIN);
// }

// // remove the highlight after update
// void remove_highlights() {
//     lv_obj_add_style(voltage_limit_ch1_label, &style_normal, LV_PART_MAIN);
//     lv_obj_add_style(current_limit_ch1_label, &style_normal, LV_PART_MAIN);
//     lv_obj_add_style(voltage_limit_ch2_label, &style_normal, LV_PART_MAIN);
//     lv_obj_add_style(current_limit_ch2_label, &style_normal, LV_PART_MAIN);
// }



void setup() {
    pinMode(LED_RED, OUTPUT);
    digitalWrite(LED_RED, 1);
    delay(100);
    // pinMode(LED_CH1, OUTPUT);
    // pinMode(LED_CH2, OUTPUT);

    // pinMode(CH_1_SET_BT, INPUT_PULLUP);
    // pinMode(CH_2_SET_BT, INPUT_PULLUP);
    // pinMode(CH_1_ON_BT, INPUT_PULLUP);
    // pinMode(CH_2_ON_BT, INPUT_PULLUP);
    // pinMode(ALL_ON_OFF, INPUT_PULLUP);
    // // pinMode(KNOB_BT, INPUT);
    // pinMode(ENCODER_A, INPUT);
    // pinMode(ENCODER_B, INPUT);
    // attachInterrupt(digitalPinToInterrupt(ENCODER_A), handleEncoder,CHANGE);
    // attachInterrupt(digitalPinToInterrupt(CH_1_SET_BT), handleCh1SetBt, FALLING);
    // attachInterrupt(digitalPinToInterrupt(CH_2_SET_BT), handleCh2SetBt, FALLING);
    // attachInterrupt(digitalPinToInterrupt(CH_1_ON_BT), handleCh1OnBt, FALLING);
    // attachInterrupt(digitalPinToInterrupt(CH_2_ON_BT), handleCh2OnBt, FALLING);
    // attachInterrupt(digitalPinToInterrupt(ALL_ON_OFF), handleOnOffBt, FALLING);
    // attachInterrupt(digitalPinToInterrupt(KNOB_BT), handleKnobBt, FALLING);

    #if SERIAL_DEBUG
    // Setup serial for debbuging.
    Serial.begin(115200);
    // tft.println("Hello World!");
    Serial.println("Hello World!");
    #endif

    // Setup UART0 for debugging
    Serial0.begin(115200);
    Serial0.println("Startup");

    Wire.begin(SDA_PIN, SCL_PIN, 100000);
    PD_UFP.init(PIN_FUSB302_INT, PD_POWER_OPTION_MAX_9V);
    // PD_UFP.init_PPS(PIN_FUSB302_INT, PPS_V(5.5), PPS_A(.5));
    PD_UFP.init_PPS(PIN_FUSB302_INT, PPS_V(9.0), PPS_A(5.0));

    // // //Initialize the LVGL library
    // lv_init();

    // /*Set a tick source so that LVGL will know how much time elapsed. */
    // lv_tick_set_cb(my_tick);

    // lv_style_init(&style_normal);
    // lv_style_set_bg_opa(&style_normal, LV_OPA_TRANSP);  // No background
    // lv_style_set_text_color(&style_normal, lv_color_hex(0x000000));  // White text

    // lv_style_init(&style_active);
    // lv_style_set_bg_opa(&style_active, LV_OPA_COVER);  // Opaque background
    // lv_style_set_bg_color(&style_active, lv_color_hex(0x000000));  // Black background
    // lv_style_set_text_color(&style_active, lv_color_hex(0xFFFFFF));  // White text

    // // alternative function: lv_obj_set_style_text_color(thing, lv_color_black(), LV_PART_MAIN);


    // lv_display_t * disp;
    // /*TFT_eSPI can be enabled lv_conf.h to initialize the display in a simple way*/
    // disp = lv_tft_espi_create(TFT_HOR_RES, TFT_VER_RES, draw_buf, sizeof(draw_buf));
    // lv_display_set_rotation(disp, TFT_ROTATION);

    // // Initialize the labels on screen
    // // CH1
    // voltage_ch1_label = lv_label_create(lv_scr_act());
    // lv_label_set_text_fmt(voltage_ch1_label, "%.3fV", voltage_ch1);
    // lv_obj_align(voltage_ch1_label, LV_ALIGN_TOP_LEFT, 10, 50);

    // current_ch1_label = lv_label_create(lv_scr_act());
    // lv_label_set_text_fmt(current_ch1_label, "%.3fV", current_ch1);
    // lv_obj_align(current_ch1_label, LV_ALIGN_TOP_LEFT, 10, 80);

    // lv_obj_t *set_txt_ch1 = lv_label_create(lv_scr_act());
    // lv_label_set_text(set_txt_ch1, "set");
    // lv_obj_align(set_txt_ch1, LV_ALIGN_TOP_LEFT, 5, 200);

    // voltage_limit_ch1_label = lv_label_create(lv_scr_act());
    // lv_label_set_text_fmt(voltage_limit_ch1_label, "%fV", voltage_limit_ch1);
    // lv_obj_align(voltage_limit_ch1_label, LV_ALIGN_TOP_LEFT, 30, 200);

    // current_limit_ch1_label = lv_label_create(lv_scr_act());
    // lv_label_set_text_fmt(current_limit_ch1_label, "%fA", current_limit_ch1);
    // lv_obj_align(current_limit_ch1_label, LV_ALIGN_TOP_LEFT, 90, 200);

    // // CH2

    // voltage_ch2_label = lv_label_create(lv_scr_act());
    // lv_label_set_text_fmt(voltage_ch2_label, "%fV", voltage_ch2);
    // lv_obj_align(voltage_ch2_label, LV_ALIGN_TOP_LEFT, 170, 50);

    // current_ch2_label = lv_label_create(lv_scr_act());
    // lv_label_set_text_fmt(current_ch2_label, "%fV", current_ch2);
    // lv_obj_align(current_ch2_label, LV_ALIGN_TOP_LEFT, 170, 80);

    // lv_obj_t *set_txt_ch2 = lv_label_create(lv_scr_act());
    // lv_label_set_text(set_txt_ch2, "set");
    // lv_obj_align(set_txt_ch2, LV_ALIGN_TOP_LEFT, 165, 200);

    // voltage_limit_ch2_label = lv_label_create(lv_scr_act());
    // lv_label_set_text_fmt(voltage_limit_ch2_label, "%fV", voltage_limit_ch2);
    // lv_obj_align(voltage_limit_ch2_label, LV_ALIGN_TOP_LEFT, 190, 200);  // Position the label

    // current_limit_ch2_label = lv_label_create(lv_scr_act());
    // lv_label_set_text_fmt(current_limit_ch2_label, "%fA", current_limit_ch2);
    // lv_obj_align(current_limit_ch2_label, LV_ALIGN_TOP_LEFT, 250, 200);  // Position the label

    // // CH2

    // voltage_limit_ch2_label = lv_label_create(lv_scr_act());
    // lv_label_set_text_fmt(voltage_limit_ch2_label, "Voltage ch2: %d V", voltage_limit_ch2);
    // lv_obj_align(voltage_limit_ch2_label, LV_ALIGN_TOP_LEFT, 160, 10);  // Position the label

    // current_limit_ch2_label = lv_label_create(lv_scr_act());
    // lv_label_set_text_fmt(current_limit_ch2_label, "Current ch2: %d A", current_limit_ch2);
    // lv_obj_align(current_limit_ch2_label, LV_ALIGN_TOP_LEFT, 160, 40);  // Position the label
}

void loop() {

    // StateStruct currentState = state_machine.getState();
    // switch (currentState.settingState) {
    //     case SettingState::IDLE:
    //         #if SERIAL_DEBUG
    //         Serial.println("IDLE");
    //         #endif
    //         // flush the encoder values
    //         encoderCtr = 0;
    //         remove_highlights();
    //         break;
    //     case SettingState::SET_VOLTAGE_CH_1:
    //         #if SERIAL_DEBUG
    //         Serial.print("SET_VOLTAGE_CH_1: ");
    //         Serial.println(voltage_limit_ch1);
    //         #endif
    //         voltage_limit_ch1 += encoderCtr;
    //         encoderCtr = 0;
    //         remove_highlights();
    //         highlight_active_label(voltage_limit_ch1_label);
    //         break;
    //     case SettingState::SET_CURRENT_CH_1:
    //         #if SERIAL_DEBUG
    //         Serial.print("SET_CURRENT_CH_1: ");
    //         Serial.println(current_limit_ch1);
    //         #endif
    //         current_limit_ch1 += encoderCtr;
    //         encoderCtr = 0;
    //         remove_highlights();
    //         highlight_active_label(current_limit_ch1_label);
    //         break;
    //     case SettingState::SET_VOLTAGE_CH_2:
    //         #if SERIAL_DEBUG
    //         Serial.print("SET_VOLTAGE_CH_2: ");
    //         Serial.println(voltage_limit_ch2);
    //         #endif
    //         voltage_limit_ch2 += encoderCtr;
    //         encoderCtr = 0;
    //         remove_highlights();
    //         highlight_active_label(voltage_limit_ch2_label);
    //         break;
    //     case SettingState::SET_CURRENT_CH_2:
    //         #if SERIAL_DEBUG
    //         Serial.print("SET_CURRENT_CH_2: ");
    //         Serial.println(current_limit_ch2);
    //         #endif
    //         current_limit_ch2 += encoderCtr;
    //         encoderCtr = 0;
    //         remove_highlights();
    //         highlight_active_label(current_limit_ch2_label);
    //         break;
    // }
    // switch (currentState.channel1State) {
    //     case ChannelState::IDLE:
    //         digitalWrite(LED_CH1, LOW);
    //         break;
    //     case ChannelState::ON:
    //         digitalWrite(LED_CH1, HIGH);
    //         break;
    // }
    // switch (currentState.channel2State) {
    //     case ChannelState::IDLE:
    //         digitalWrite(LED_CH2, LOW);
    //         break;
    //     case ChannelState::ON:
    //         digitalWrite(LED_CH2, HIGH);
    //         break;
    // }
    // lv_label_set_text_fmt(voltage_limit_ch1_label, "%.3fV", voltage_limit_ch1);
    // lv_label_set_text_fmt(current_limit_ch1_label, "%.3fA", current_limit_ch1);
    // lv_label_set_text_fmt(voltage_limit_ch2_label, "%.3fV", voltage_limit_ch2);
    // lv_label_set_text_fmt(current_limit_ch2_label, "%.3fA", current_limit_ch2);
    // lv_timer_handler(); /* let the GUI do its work */

    PD_UFP.run();
    static int pd_status = 0;
    // // Serial0.println("run");
    PD_UFP.print_status(Serial0);
    if (PD_UFP.is_PPS_ready())
    {
      if (pd_status != 1){
      pd_status = 1;
      Serial0.println("PPS trigger success");
      }
    }
    else if (PD_UFP.is_power_ready())
    {
      if (pd_status != 2){
      pd_status = 2;
      Serial0.println("Fail to trigger PPS, fall back");
      }
    }
    else
    {
      if (pd_status != 3){
      pd_status = 3;
      Serial0.println("PD not ready");
      }
    }
    //delay(10);
    digitalWrite(LED_RED, !digitalRead(LED_RED));  // Toggle LED state  
}

float mapValue(float ip, float ipmin, float ipmax, float tomin, float tomax)
{
    return tomin + (((tomax - tomin) * (ip - ipmin))/ (ipmax - ipmin));
}