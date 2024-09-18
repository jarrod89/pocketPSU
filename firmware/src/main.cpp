#include <Arduino.h>
// #include <ESP32-TWAI-CAN.hpp>
#include <TFT_eSPI.h>

#include "StateMachine.hpp"

#define CH_1_SET_BT 17
#define CH_2_SET_BT 18
#define CH_1_ON_BT 19
#define CH_2_ON_BT 14
#define KNOB_BT 5


TFT_eSPI tft = TFT_eSPI();

// #define CAN_TX		40
// #define CAN_RX		41
// CanFrame rxFrame;
// static uint64_t u64_from_can_msg(const uint8_t m[8]);
// static void u64_to_can_msg(const uint64_t u, uint8_t m[8]);

void handleCh1SetBt() {
    StateMachine::handleCh1SetBt;
}

void handleCh2SetBt() {
    StateMachine::handleCh2SetBt;
}

void handleCh1OnBt() {
    StateMachine::handleCh1OnBt;
}

void handleCh2OnBt() {
    StateMachine::handleCh2OnBt;
}


void setup() {
    
    // Setup serial for debbuging.
    Serial.begin(115200); // USB serial
    // Serial0.begin(612500);  // TTL serial

    // if(ESP32Can.begin(ESP32Can.convertSpeed(250), CAN_TX, CAN_RX, 10, 10)) {
    //     Serial.println("CAN bus started!");
    // } else {
    //     Serial.println("CAN bus failed!");
    // }
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);
    tft.setCursor(100, 100);
    tft.setTextSize(10);
    delay(1000);
    tft.println("Hello World!");

    // Setup Buttons
    pinMode(CH_1_SET_BT, INPUT_PULLUP);
    pinMode(CH_2_SET_BT, INPUT_PULLUP);
    pinMode(CH_1_ON_BT, INPUT_PULLUP);
    pinMode(CH_2_ON_BT, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(CH_1_SET_BT), handleCh1SetBt, FALLING);
    attachInterrupt(digitalPinToInterrupt(CH_2_SET_BT), handleCh2SetBt, FALLING);
    attachInterrupt(digitalPinToInterrupt(CH_1_ON_BT), handleCh1OnBt, FALLING);
    attachInterrupt(digitalPinToInterrupt(CH_2_ON_BT), handleCh2OnBt, FALLING);
}

void loop() {
  Serial.println("Hello World!");
  delay(1000);
  // if (Serial.available()) {      // If anything comes in Serial (USB),
  //   Serial0.write(Serial.read());   // read it and send it out Serial1 
  // }
  // if (Serial0.available()) {     // If anything comes in Serial1 
  //   Serial.write(Serial0.read());   // read it and send it out Serial (USB)
  // }
}