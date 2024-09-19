#include <Arduino.h>
// #include <ESP32-TWAI-CAN.hpp>
#include <TFT_eSPI.h>

#include "Free_Fonts.h" // Include the header file attached to this sketch
#define TEXT "aA MWyz~12" // Text that will be printed on screen in any font

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
#include <Encoder.h>
Encoder myEnc(ENCODER_A, ENCODER_B);

TFT_eSPI tft = TFT_eSPI();

// #define CAN_TX		40
// #define CAN_RX		41
// CanFrame rxFrame;
// static uint64_t u64_from_can_msg(const uint8_t m[8]);
// static void u64_to_can_msg(const uint64_t u, uint8_t m[8]);
void fontdemo();

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
    tft.setRotation(3);
    tft.fillScreen(TFT_BLACK);
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);
    pinMode(LED_CH1, OUTPUT);
    digitalWrite(LED_CH1, HIGH);
    pinMode(LED_CH2, OUTPUT);
    digitalWrite(LED_CH2, HIGH);
    // Setup Buttons
    pinMode(CH_1_SET_BT, INPUT_PULLUP);
    pinMode(CH_2_SET_BT, INPUT_PULLUP);
    pinMode(CH_1_ON_BT, INPUT_PULLUP);
    pinMode(CH_2_ON_BT, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(CH_1_SET_BT), handleCh1SetBt, FALLING);
    attachInterrupt(digitalPinToInterrupt(CH_2_SET_BT), handleCh2SetBt, FALLING);
    attachInterrupt(digitalPinToInterrupt(CH_1_ON_BT), handleCh1OnBt, FALLING);
    attachInterrupt(digitalPinToInterrupt(CH_2_ON_BT), handleCh2OnBt, FALLING);
    
  tft.println("Hello World!");
  Serial.println("Hello World!");
  Serial0.println("test");
}

void loop() {
  static long oldPosition  = -999;
  long newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    tft.setCursor(0,0);
    tft.setTextSize(4);
    tft.print(newPosition);
    tft.print("     ");
  }
  digitalWrite(LED_RED,!digitalRead(LED_RED));
  digitalWrite(LED_CH1,!digitalRead(LED_CH1));
  digitalWrite(LED_CH2,!digitalRead(LED_CH2));
  // if (Serial.available()) {      // If anything comes in Serial (USB),
  //   Serial0.write(Serial.read());   // read it and send it out Serial1 
  // }
  // if (Serial0.available()) {     // If anything comes in Serial1 
  //   Serial.write(Serial0.read());   // read it and send it out Serial (USB)
  // }
}

void fontdemo()
{
    
  // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  // Show all 48 fonts in centre of screen ( x,y coordinate 160,120)
  // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

  // Where font sizes increase the screen is not cleared as the larger fonts overwrite
  // the smaller one with the background colour.

  // Set text datum to middle centre
  tft.setTextDatum(MC_DATUM);

  // Set text colour to orange with black background
  tft.setTextColor(TFT_GREENYELLOW, TFT_BLACK);
  
  tft.fillScreen(TFT_BLACK);            // Clear screen
  tft.setFreeFont(FF18);                 // Select the font
  tft.drawString(sFF1, 160, 60, GFXFF);// Print the string name of the font
  tft.setFreeFont(FF1);                 // Select the font
  tft.drawString(TEXT, 160, 120, GFXFF);// Print the string name of the font
  delay(1000);
  
  tft.setFreeFont(FF18);                 // Select the font
  tft.drawString(sFF2, 160, 60, GFXFF);// Print the string name of the font
  tft.setFreeFont(FF2);
  tft.drawString(TEXT, 160, 120, GFXFF);
  delay(1000);
  
  tft.setFreeFont(FF18);                 // Select the font
  tft.drawString(sFF3, 160, 60, GFXFF);// Print the string name of the font
  tft.setFreeFont(FF3);
  tft.drawString(TEXT, 160, 120, GFXFF);
  delay(1000);
  
  tft.setFreeFont(FF18);                 // Select the font
  tft.drawString(sFF4, 160, 60, GFXFF);// Print the string name of the font
  tft.setFreeFont(FF4);
  tft.drawString(TEXT, 160, 120, GFXFF);
  delay(1000);
  
  tft.fillScreen(TFT_BLACK);
  tft.setFreeFont(FF18);                 // Select the font
  tft.drawString(sFF5, 160, 60, GFXFF);// Print the string name of the font
  tft.setFreeFont(FF5);
  tft.drawString(TEXT, 160, 120, GFXFF);
  delay(1000);
  
  tft.setFreeFont(FF18);                 // Select the font
  tft.drawString(sFF6, 160, 60, GFXFF);// Print the string name of the font
  tft.setFreeFont(FF6);
  tft.drawString(TEXT, 160, 120, GFXFF);
  delay(1000);
  
  tft.setFreeFont(FF18);                 // Select the font
  tft.drawString(sFF7, 160, 60, GFXFF);// Print the string name of the font
  tft.setFreeFont(FF7);
  tft.drawString(TEXT, 160, 120, GFXFF);
  delay(1000);
  
  tft.setFreeFont(FF18);                 // Select the font
  tft.drawString(sFF8, 160, 60, GFXFF);// Print the string name of the font
  tft.setFreeFont(FF8);
  tft.drawString(TEXT, 160, 120, GFXFF);
  delay(1000);
  
  tft.fillScreen(TFT_BLACK);
  tft.setFreeFont(FF18);                 // Select the font
  tft.drawString(sFF9, 160, 60, GFXFF);// Print the string name of the font
  tft.setFreeFont(FF9);
  tft.drawString(TEXT, 160, 120, GFXFF);
  delay(1000);
  
  tft.setFreeFont(FF18);                 // Select the font
  tft.drawString(sFF10, 160, 60, GFXFF);// Print the string name of the font
  tft.setFreeFont(FF10);
  tft.drawString(TEXT, 160, 120, GFXFF);
  delay(1000);
  
  tft.setFreeFont(FF18);                 // Select the font
  tft.drawString(sFF11, 160, 60, GFXFF);// Print the string name of the font
  tft.setFreeFont(FF11);
  tft.drawString(TEXT, 160, 120, GFXFF);
  delay(1000);
  
  tft.setFreeFont(FF18);                 // Select the font
  tft.drawString(sFF12, 160, 60, GFXFF);// Print the string name of the font
  tft.setFreeFont(FF12);
    tft.drawString(TEXT, 160, 120, GFXFF);
  delay(1000);
  
  tft.fillScreen(TFT_BLACK);
  tft.setFreeFont(FF18);                 // Select the font
  tft.drawString(sFF13, 160, 60, GFXFF);// Print the string name of the font
  tft.setFreeFont(FF13);
  tft.drawString(TEXT, 160, 120, GFXFF);
  delay(1000);
  
  tft.setFreeFont(FF18);                 // Select the font
  tft.drawString(sFF14, 160, 60, GFXFF);// Print the string name of the font
  tft.setFreeFont(FF14);
  tft.drawString(TEXT, 160, 120, GFXFF);
  delay(1000);
  
  tft.setFreeFont(FF18);                 // Select the font
  tft.drawString(sFF15, 160, 60, GFXFF);// Print the string name of the font
  tft.setFreeFont(FF15);
  tft.drawString(TEXT, 160, 120, GFXFF);
  delay(1000);
  
  tft.setFreeFont(FF18);                 // Select the font
  tft.drawString(sFF16, 160, 60, GFXFF);// Print the string name of the font
  tft.setFreeFont(FF16);
    tft.drawString(TEXT, 160, 120, GFXFF);
  delay(1000);
  
  tft.fillScreen(TFT_BLACK);
  tft.setFreeFont(FF18);                 // Select the font
  tft.drawString(sFF17, 160, 60, GFXFF);// Print the string name of the font
  tft.setFreeFont(FF17);
  tft.drawString(TEXT, 160, 120, GFXFF);
  delay(1000);
  
  tft.setFreeFont(FF18);                 // Select the font
  tft.drawString(sFF18, 160, 60, GFXFF);// Print the string name of the font
  tft.setFreeFont(FF18);
  tft.drawString(TEXT, 160, 120, GFXFF);
  delay(1000);
  
  tft.setFreeFont(FF18);                 // Select the font
  tft.drawString(sFF19, 160, 60, GFXFF);// Print the string name of the font
  tft.setFreeFont(FF19);
  tft.drawString(TEXT, 160, 120, GFXFF);
  delay(1000);
  
  tft.setFreeFont(FF18);                 // Select the font
  tft.drawString(sFF20, 160, 60, GFXFF);// Print the string name of the font
  tft.setFreeFont(FF20);
    tft.drawString(TEXT, 160, 120, GFXFF);
  delay(1000);
  
  tft.fillScreen(TFT_BLACK);
  tft.setFreeFont(FF18);                 // Select the font
  tft.drawString(sFF21, 160, 60, GFXFF);// Print the string name of the font
  tft.setFreeFont(FF21);
  tft.drawString(TEXT, 160, 120, GFXFF);
  delay(1000);
  
  tft.setFreeFont(FF18);                 // Select the font
  tft.drawString(sFF22, 160, 60, GFXFF);// Print the string name of the font
  tft.setFreeFont(FF22);
  tft.drawString(TEXT, 160, 120, GFXFF);
  delay(1000);
  
  tft.setFreeFont(FF18);                 // Select the font
  tft.drawString(sFF23, 160, 60, GFXFF);// Print the string name of the font
  tft.setFreeFont(FF23);
  tft.drawString(TEXT, 160, 120, GFXFF);
  delay(1000);
  
  tft.setFreeFont(FF18);                 // Select the font
  tft.drawString(sFF24, 160, 60, GFXFF);// Print the string name of the font
  tft.setFreeFont(FF24);
  tft.drawString(TEXT, 160, 120, GFXFF);
  delay(1000);
  
  tft.fillScreen(TFT_BLACK);
  tft.setFreeFont(FF18);                 // Select the font
  tft.drawString(sFF25, 160, 60, GFXFF);// Print the string name of the font
  tft.setFreeFont(FF25);
  tft.drawString(TEXT, 160, 120, GFXFF);
  delay(1000);
  
  tft.setFreeFont(FF18);                 // Select the font
  tft.drawString(sFF26, 160, 60, GFXFF);// Print the string name of the font
  tft.setFreeFont(FF26);
  tft.drawString(TEXT, 160, 120, GFXFF);
  delay(1000);
  
  tft.setFreeFont(FF18);                 // Select the font
  tft.drawString(sFF27, 160, 60, GFXFF);// Print the string name of the font
  tft.setFreeFont(FF27);
  tft.drawString(TEXT, 160, 120, GFXFF);
  delay(1000);
  
  tft.setFreeFont(FF18);                 // Select the font
  tft.drawString(sFF28, 160, 60, GFXFF);// Print the string name of the font
  tft.setFreeFont(FF28);
  tft.drawString(TEXT, 160, 120, GFXFF);
  delay(1000);
  
  tft.fillScreen(TFT_BLACK);
  tft.setFreeFont(FF18);                 // Select the font
  tft.drawString(sFF29, 160, 60, GFXFF);// Print the string name of the font
  tft.setFreeFont(FF29);
  tft.drawString(TEXT, 160, 120, GFXFF);
  delay(1000);
  
  tft.setFreeFont(FF18);                 // Select the font
  tft.drawString(sFF30, 160, 60, GFXFF);// Print the string name of the font
  tft.setFreeFont(FF30);
  tft.drawString(TEXT, 160, 120, GFXFF);
  delay(1000);
  
  tft.setFreeFont(FF18);                 // Select the font
  tft.drawString(sFF31, 160, 60, GFXFF);// Print the string name of the font
  tft.setFreeFont(FF31);
  tft.drawString(TEXT, 160, 120, GFXFF);
  delay(1000);
  
  tft.setFreeFont(FF18);                 // Select the font
  tft.drawString(sFF32, 160, 60, GFXFF);// Print the string name of the font
  tft.setFreeFont(FF32);
  tft.drawString(TEXT, 160, 120, GFXFF);
  delay(1000);
  
  tft.fillScreen(TFT_BLACK);
  tft.setFreeFont(FF18);                 // Select the font
  tft.drawString(sFF33, 160, 60, GFXFF);// Print the string name of the font
  tft.setFreeFont(FF33);
  tft.drawString(TEXT, 160, 120, GFXFF);
  delay(1000);
  
  tft.setFreeFont(FF18);                 // Select the font
  tft.drawString(sFF34, 160, 60, GFXFF);// Print the string name of the font
  tft.setFreeFont(FF34);
  tft.drawString(TEXT, 160, 120, GFXFF);
  delay(1000);
  
  tft.setFreeFont(FF18);                 // Select the font
  tft.drawString(sFF35, 160, 60, GFXFF);// Print the string name of the font
  tft.setFreeFont(FF35);
  tft.drawString(TEXT, 160, 120, GFXFF);
  delay(1000);
  
  tft.setFreeFont(FF18);                 // Select the font
  tft.drawString(sFF36, 160, 60, GFXFF);// Print the string name of the font
  tft.setFreeFont(FF36);
  tft.drawString(TEXT, 160, 120, GFXFF);
  delay(1000);
  
  tft.fillScreen(TFT_BLACK);
  tft.setFreeFont(FF18);                 // Select the font
  tft.drawString(sFF37, 160, 60, GFXFF);// Print the string name of the font
  tft.setFreeFont(FF37);
  tft.drawString(TEXT, 160, 120, GFXFF);
  delay(1000);
  
  tft.setFreeFont(FF18);                 // Select the font
  tft.drawString(sFF38, 160, 60, GFXFF);// Print the string name of the font
  tft.setFreeFont(FF38);
  tft.drawString(TEXT, 160, 120, GFXFF);
  delay(1000);
  
  tft.setFreeFont(FF18);                 // Select the font
  tft.drawString(sFF39, 160, 60, GFXFF);// Print the string name of the font
  tft.setFreeFont(FF39);
  tft.drawString(TEXT, 160, 120, GFXFF);
  delay(1000);
  
  tft.setFreeFont(FF18);                 // Select the font
  tft.drawString(sFF40, 160, 60, GFXFF);// Print the string name of the font
  tft.setFreeFont(FF40);
  tft.drawString(TEXT, 160, 120, GFXFF);
  delay(1000);
  
  tft.fillScreen(TFT_BLACK);
  tft.setFreeFont(FF18);                 // Select the font
  tft.drawString(sFF41, 160, 60, GFXFF);// Print the string name of the font
  tft.setFreeFont(FF41);
  tft.drawString(TEXT, 160, 120, GFXFF);
  delay(1000);
  
  tft.setFreeFont(FF18);                 // Select the font
  tft.drawString(sFF42, 160, 60, GFXFF);// Print the string name of the font
  tft.setFreeFont(FF42);
  tft.drawString(TEXT, 160, 120, GFXFF);
  delay(1000);
  
  tft.setFreeFont(FF18);                 // Select the font
  tft.drawString(sFF43, 160, 60, GFXFF);// Print the string name of the font
  tft.setFreeFont(FF43);
  tft.drawString(TEXT, 160, 120, GFXFF);
  delay(1000);
  
  tft.setFreeFont(FF18);                 // Select the font
  tft.drawString(sFF44, 160, 60, GFXFF);// Print the string name of the font
  tft.setFreeFont(FF44);
  tft.drawString(TEXT, 160, 120, GFXFF);
  delay(1000);
  
  tft.fillScreen(TFT_BLACK);
  tft.setFreeFont(FF18);                 // Select the font
  tft.drawString(sFF45, 160, 60, GFXFF);// Print the string name of the font
  tft.setFreeFont(FF45);
  tft.drawString(TEXT, 160, 120, GFXFF);
  delay(1000);
  
  tft.setFreeFont(FF18);                 // Select the font
  tft.drawString(sFF46, 160, 60, GFXFF);// Print the string name of the font
  tft.setFreeFont(FF46);
  tft.drawString(TEXT, 160, 120, GFXFF);
  delay(1000);
  
  tft.setFreeFont(FF18);                 // Select the font
  tft.drawString(sFF47, 160, 60, GFXFF);// Print the string name of the font
  tft.setFreeFont(FF47);
  tft.drawString(TEXT, 160, 120, GFXFF);
  delay(1000);
  
  tft.setFreeFont(FF18);                 // Select the font
  tft.drawString(sFF48, 160, 60, GFXFF);// Print the string name of the font
  tft.setFreeFont(FF48);
  tft.drawString(TEXT, 160, 120, GFXFF);
  delay(1000);
    
}