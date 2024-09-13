#include <Arduino.h>
// #include <ESP32-TWAI-CAN.hpp>
#include <TFT_eSPI.h>


TFT_eSPI tft = TFT_eSPI();

// #define CAN_TX		40
// #define CAN_RX		41
// CanFrame rxFrame;
// static uint64_t u64_from_can_msg(const uint8_t m[8]);
// static void u64_to_can_msg(const uint64_t u, uint8_t m[8]);

void setup() {
  
  // Setup serial for debbuging.
  Serial.begin(115200); // USB serial
  Serial0.begin(612500);  // TTL serial

  tft.begin();
  tft.setRotation(1); 
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_GREENYELLOW,TFT_BLACK);
  // Set "cursor" at top left corner of display (0,0) and select font 2
  tft.setCursor(0, 0, 1);
  tft.println("Hello World!");
  
  // if(ESP32Can.begin(ESP32Can.convertSpeed(250), CAN_TX, CAN_RX, 10, 10)) {
  //     Serial.println("CAN bus started!");
  // } else {
  //     Serial.println("CAN bus failed!");
  // }
}

void loop() {
  if (Serial.available()) {      // If anything comes in Serial (USB),
    Serial0.write(Serial.read());   // read it and send it out Serial1 
  }
  if (Serial0.available()) {     // If anything comes in Serial1 
    Serial.write(Serial0.read());   // read it and send it out Serial (USB)
  }
}