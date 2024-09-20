#include <Arduino.h>
// #include <ESP32-TWAI-CAN.hpp>
#include <TFT_eSPI.h>
#include <TFT_eWidget.h>  // Widget library

#include "StateMachine.hpp"
#define CH_1_SET_BT 5
#define CH_2_SET_BT 8
#define CH_1_ON_BT 7
#define CH_2_ON_BT 34
#define ALL_ON_OFF 21
#define KNOB_BT 26
#define ENCODER_A 47
#define ENCODER_B 48
#define LED_CH1 6
#define LED_CH2 33
#define LED_RED 42
// #include <Encoder.h>
// Encoder myEnc(ENCODER_A, ENCODER_B);

TFT_eSPI tft = TFT_eSPI();

MeterWidget   amps  = MeterWidget(&tft);
MeterWidget   volts = MeterWidget(&tft);
MeterWidget   ohms  = MeterWidget(&tft);
// #define CAN_TX		40
// #define CAN_RX		41
// CanFrame rxFrame;
// static uint64_t u64_from_can_msg(const uint8_t m[8]);
// static void u64_to_can_msg(const uint64_t u, uint8_t m[8]);
float mapValue(float ip, float ipmin, float ipmax, float tomin, float tomax);

long encoderCtr = 0;
void handleEncoder() {
  if(digitalRead(ENCODER_A))
  {
    if(digitalRead(ENCODER_B))
      encoderCtr++;
    else
      encoderCtr--;
  }
  else
  {
    if(digitalRead(ENCODER_B))
      encoderCtr--;
    else
      encoderCtr++;
  }
}

void handleOnOffBt() {
  digitalWrite(LED_RED,!digitalRead(LED_RED));
}

void handleCh1SetBt() {
    StateMachine::handleCh1SetBt;
}

void handleCh2SetBt() {
    StateMachine::handleCh2SetBt;
}

void handleCh1OnBt() {

  digitalWrite(LED_CH1,!digitalRead(LED_CH1));
    StateMachine::handleCh1OnBt;
}

void handleCh2OnBt() {

  digitalWrite(LED_CH2,!digitalRead(LED_CH2));
    StateMachine::handleCh2OnBt;
}


void setup() {
    pinMode(LED_RED,OUTPUT);
    digitalWrite(LED_RED,1);
    // Setup serial for debbuging.
    Serial.begin(115200); // USB serial
    Serial0.begin(612500);  // TTL serial

    // if(ESP32Can.begin(ESP32Can.convertSpeed(250), CAN_TX, CAN_RX, 10, 10)) {
    //     Serial.println("CAN bus started!");
    // } else {
    //     Serial.println("CAN bus failed!");
    // }
    tft.init();
    tft.setRotation(2);
    tft.fillScreen(TFT_BLACK);
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);
    pinMode(LED_CH1, OUTPUT);
    digitalWrite(LED_CH1, LOW);
    pinMode(LED_CH2, OUTPUT);
    digitalWrite(LED_CH2, LOW);
    // Setup Buttons
    pinMode(CH_1_SET_BT, INPUT_PULLUP);
    pinMode(CH_2_SET_BT, INPUT_PULLUP);
    pinMode(CH_1_ON_BT, INPUT_PULLUP);
    pinMode(CH_2_ON_BT, INPUT_PULLUP);
    pinMode(ALL_ON_OFF, INPUT_PULLUP);
    pinMode(ENCODER_A, INPUT);
    pinMode(ENCODER_B, INPUT);
    attachInterrupt(digitalPinToInterrupt(ENCODER_A), handleEncoder,CHANGE);
    attachInterrupt(digitalPinToInterrupt(CH_1_SET_BT), handleCh1SetBt, FALLING);
    attachInterrupt(digitalPinToInterrupt(CH_2_SET_BT), handleCh2SetBt, FALLING);
    attachInterrupt(digitalPinToInterrupt(CH_1_ON_BT), handleCh1OnBt, FALLING);
    attachInterrupt(digitalPinToInterrupt(CH_2_ON_BT), handleCh2OnBt, FALLING);
    attachInterrupt(digitalPinToInterrupt(ALL_ON_OFF), handleOnOffBt, FALLING);
    
  tft.println("Hello World!");
  Serial.println("Hello World!");
  Serial0.println("test");

  
  // Colour zones are set as a start and end percentage of full scale (0-100)
  // If start and end of a colour zone are the same then that colour is not used
  //            --Red--  -Org-   -Yell-  -Grn-
  amps.setZones(75, 100, 50, 75, 25, 50, 0, 25); // Example here red starts at 75% and ends at 100% of full scale
  // Meter is 239 pixels wide and 126 pixels high
  amps.analogMeter(0, 0, 5.0, "A", "0", "1.0", "2.0", "3.0", "4.0");    // Draw analogue meter at 0, 0

  // Colour draw order is red, orange, yellow, green. So red can be full scale with green drawn
  // last on top to indicate a "safe" zone.
  //             -Red-   -Org-  -Yell-  -Grn-
  volts.setZones(75, 100, 50, 75, 25, 50, 0, 25);
  volts.analogMeter(0, 128, 30.0, "V", "0", "7.5", "15", "22.5", "30"); // Draw analogue meter at 0, 128
}

void loop() {
  static long oldPosition  = -999;
  long newPosition = encoderCtr;
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    // tft.setCursor(0,0);
    // tft.setTextSize(4);
    // tft.print(newPosition);
    // tft.print("     ");
    float voltage;
    voltage = mapValue(newPosition, (float)0.0, (float)100.0, (float)0.0, (float)10.0);
    volts.updateNeedle(voltage, 0);
  }
  // if (Serial.available()) {      // If anything comes in Serial (USB),
  //   Serial0.write(Serial.read());   // read it and send it out Serial1 
  // }
  // if (Serial0.available()) {     // If anything comes in Serial1 
  //   Serial.write(Serial0.read());   // read it and send it out Serial (USB)
  // }
}

float mapValue(float ip, float ipmin, float ipmax, float tomin, float tomax)
{
  return tomin + (((tomax - tomin) * (ip - ipmin))/ (ipmax - ipmin));
}