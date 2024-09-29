#include <Arduino.h>
// #include <ESP32-TWAI-CAN.hpp>
#include <lvgl.h>
#if LV_USE_TFT_ESPI
#include <TFT_eSPI.h>
#endif

#include "StateMachine.hpp"

#define TFT_HOR_RES   240
#define TFT_VER_RES   320
#define TFT_ROTATION  LV_DISPLAY_ROTATION_0

/*LVGL draw into this buffer, 1/10 screen size usually works well. The size is in bytes*/
#define DRAW_BUF_SIZE (TFT_HOR_RES * TFT_VER_RES / 10 * (LV_COLOR_DEPTH / 8))
uint32_t draw_buf[DRAW_BUF_SIZE / 4];

/* LVGL calls it when a rendered image needs to copied to the display*/
void my_disp_flush( lv_display_t *disp, const lv_area_t *area, uint8_t * px_map)
{
    /*Call it to tell LVGL you are ready*/
    lv_display_flush_ready(disp);
}

/*use Arduinos millis() as tick source*/
static uint32_t my_tick(void)
{
    return millis();
}


TFT_eSPI tft = TFT_eSPI();

StateMachine state_machine;


// #define CAN_TX    40
// #define CAN_RX    41
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
volatile unsigned long lastDebounceTimeCh1Set = 0;  // Variables to store last debounce time
volatile unsigned long lastDebounceTimeCh2Set = 0;
volatile unsigned long lastDebounceTimeCh1On = 0;
volatile unsigned long lastDebounceTimeCh2On = 0;
volatile unsigned long lastDebounceTimeOnOff = 0;

const unsigned long debounceDelay = 200;  // Set debounce delay to 50ms

void handleCh1SetBt() {
    if ((millis() - lastDebounceTimeCh1Set) > debounceDelay) {
        lastDebounceTimeCh1Set = millis();  // Update last debounce time
        state_machine.handleCh1SetBt();  // Your existing function
    }
}

void handleCh2SetBt() {
    if ((millis() - lastDebounceTimeCh2Set) > debounceDelay) {
        lastDebounceTimeCh2Set = millis();
        state_machine.handleCh2SetBt();
    }
}

void handleCh1OnBt() {
    if ((millis() - lastDebounceTimeCh1On) > debounceDelay) {
        lastDebounceTimeCh1On = millis();
        digitalWrite(LED_CH1, !digitalRead(LED_CH1));  // Toggle LED state
        state_machine.handleCh1OnBt();  // Call your state handling logic
    }
}

void handleCh2OnBt() {
    if ((millis() - lastDebounceTimeCh2On) > debounceDelay) {
        lastDebounceTimeCh2On = millis();
        state_machine.handleCh2OnBt();
    }
}

void handleOnOffBt() {
    if ((millis() - lastDebounceTimeOnOff) > debounceDelay) {
        lastDebounceTimeOnOff = millis();
        digitalWrite(LED_RED, !digitalRead(LED_RED));  // Toggle LED state
    }
}


void setup() {
    pinMode(LED_RED,OUTPUT);
    digitalWrite(LED_RED,1);
    // Setup serial for debbuging.
    Serial.begin(115200); // USB serial
    // #ifdef ESP32
    // Serial0.begin(612500);  // TTL serial
    // Serial0.println("test");
    // #endif
    // if(ESP32Can.begin(ESP32Can.convertSpeed(250), CAN_TX, CAN_RX, 10, 10)) {
    //     Serial.println("CAN bus started!");
    // } else {
    //     Serial.println("CAN bus failed!");
    // }
    // tft.init();
    // tft.setRotation(2);
    // tft.fillScreen(TFT_BLACK);
    // pinMode(TFT_BL, OUTPUT);
    // digitalWrite(TFT_BL, HIGH);
    // pinMode(LED_CH1, OUTPUT);
    // digitalWrite(LED_CH1, LOW);
    // pinMode(LED_CH2, OUTPUT);
    // digitalWrite(LED_CH2, LOW);
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

    // tft.println("Hello World!");
    Serial.println("Hello World!");


    lv_init();

    /*Set a tick source so that LVGL will know how much time elapsed. */
    lv_tick_set_cb(my_tick);


    lv_display_t * disp;
    /*TFT_eSPI can be enabled lv_conf.h to initialize the display in a simple way*/
    disp = lv_tft_espi_create(TFT_HOR_RES, TFT_VER_RES, draw_buf, sizeof(draw_buf));
    lv_display_set_rotation(disp, TFT_ROTATION);


    lv_obj_t *label = lv_label_create( lv_screen_active() );
    lv_label_set_text( label, "Hello Arduino, I'm LVGL!" );
    lv_obj_align( label, LV_ALIGN_CENTER, 0, 0 );
}

void loop() {
    static long oldPosition  = -999;
    long newPosition = encoderCtr;
    // if (newPosition != oldPosition) {
    //     oldPosition = newPosition;
    //     // tft.setCursor(0,0);
    //     // tft.setTextSize(4);
    //     // tft.print(newPosition);
    //     // tft.print("     ");
    //     float voltage;
    //     voltage = mapValue(newPosition, (float)0.0, (float)100.0, (float)0.0, (float)10.0);
    //     volts.updateNeedle(voltage, 0);
    // }
    StateStruct currentState = state_machine.getState();
    switch (currentState.settingState) {
        case SettingState::IDLE:
            Serial.println("IDLE");
            break;
        case SettingState::SET_CURRENT_CH_1:
            Serial.println("SET_CURRENT_CH_1");
            break;
        case SettingState::SET_VOLTAGE_CH_1:
            Serial.println("SET_VOLTAGE_CH_1");
            break;
        case SettingState::SET_CURRENT_CH_2:
            Serial.println("SET_CURRENT_CH_2");
            break;
        case SettingState::SET_VOLTAGE_CH_2:
            Serial.println("SET_VOLTAGE_CH_2");
            break;
    }
    switch (currentState.channel1State) {
        case ChannelState::IDLE:
            digitalWrite(LED_CH1, 0);
            break;
        case ChannelState::ON:
            digitalWrite(LED_CH1, 1);
            break;
    }
    switch (currentState.channel2State) {
        case ChannelState::IDLE:
            digitalWrite(LED_CH2, 0);
            break;
        case ChannelState::ON:
            digitalWrite(LED_CH2, 1);
            break;
    }
    lv_timer_handler(); /* let the GUI do its work */
    delay(500);
}

float mapValue(float ip, float ipmin, float ipmax, float tomin, float tomax)
{
    return tomin + (((tomax - tomin) * (ip - ipmin))/ (ipmax - ipmin));
}



// /*Using LVGL with Arduino requires some extra steps:
//  *Be sure to read the docs here: https://docs.lvgl.io/master/integration/framework/arduino.html  */
// #include <Arduino.h>
// #include "TFT_eSPI.h"
// #include <lvgl.h>
// #include <SPI.h>
// #include <FS.h>
// #include <SPIFFS.h>

// #if LV_USE_TFT_ESPI
// #include <TFT_eSPI.h>
// #endif

// // #define LV_CONF_PATH "lib/lv_conf.h"

// /*To use the built-in examples and demos of LVGL uncomment the includes below respectively.
//  *You also need to copy `lvgl/examples` to `lvgl/src/examples`. Similarly for the demos `lvgl/demos` to `lvgl/src/demos`.
//  *Note that the `lv_examples` library is for LVGL v7 and you shouldn't install it for this version (since LVGL v8)
//  *as the examples and demos are now part of the main LVGL library. */

// //#include <examples/lv_examples.h>
// //#include <demos/lv_demos.h>

// /*Set to your screen resolution and rotation*/
// #define TFT_HOR_RES   240
// #define TFT_VER_RES   320
// #define TFT_ROTATION  LV_DISPLAY_ROTATION_0

// /*LVGL draw into this buffer, 1/10 screen size usually works well. The size is in bytes*/
// #define DRAW_BUF_SIZE (TFT_HOR_RES * TFT_VER_RES / 10 * (LV_COLOR_DEPTH / 8))
// uint32_t draw_buf[DRAW_BUF_SIZE / 4];

// #if LV_USE_LOG != 0
// void my_print( lv_log_level_t level, const char * buf )
// {
//     LV_UNUSED(level);
//     Serial.println(buf);
//     Serial.flush();
// }
// #endif

// /* LVGL calls it when a rendered image needs to copied to the display*/
// void my_disp_flush( lv_display_t *disp, const lv_area_t *area, uint8_t * px_map)
// {
//     /*Copy `px map` to the `area`*/

//     /*For example ("my_..." functions needs to be implemented by you)
//     uint32_t w = lv_area_get_width(area);
//     uint32_t h = lv_area_get_height(area);

//     my_set_window(area->x1, area->y1, w, h);
//     my_draw_bitmaps(px_map, w * h);
//      */

//     /*Call it to tell LVGL you are ready*/
//     lv_display_flush_ready(disp);
// }

// /*use Arduinos millis() as tick source*/
// static uint32_t my_tick(void)
// {
//     return millis();
// }

// void setup()
// {
//     String LVGL_Arduino = "Hello Arduino! ";
//     LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();

//     Serial.begin( 115200 );
//     Serial.println( LVGL_Arduino );

//     lv_init();

//     /*Set a tick source so that LVGL will know how much time elapsed. */
//     lv_tick_set_cb(my_tick);

//     /* register print function for debugging */
// #if LV_USE_LOG != 0
//     lv_log_register_print_cb( my_print );
// #endif

//     lv_display_t * disp;
// #if LV_USE_TFT_ESPI
//     /*TFT_eSPI can be enabled lv_conf.h to initialize the display in a simple way*/
//     disp = lv_tft_espi_create(TFT_HOR_RES, TFT_VER_RES, draw_buf, sizeof(draw_buf));
//     lv_display_set_rotation(disp, TFT_ROTATION);

// #else
//     /*Else create a display yourself*/
//     disp = lv_display_create(TFT_HOR_RES, TFT_VER_RES);
//     lv_display_set_flush_cb(disp, my_disp_flush);
//     lv_display_set_buffers(disp, draw_buf, NULL, sizeof(draw_buf), LV_DISPLAY_RENDER_MODE_PARTIAL);
// #endif

//     /*Initialize the (dummy) input device driver*/
//     // lv_indev_t * indev = lv_indev_create();
//     // lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER); /*Touchpad should have POINTER type*/
//     // lv_indev_set_read_cb(indev, my_touchpad_read);

//     /* Create a simple label
//      * ---------------------
//      lv_obj_t *label = lv_label_create( lv_screen_active() );
//      lv_label_set_text( label, "Hello Arduino, I'm LVGL!" );
//      lv_obj_align( label, LV_ALIGN_CENTER, 0, 0 );

//      * Try an example. See all the examples
//      *  - Online: https://docs.lvgl.io/master/examples.html
//      *  - Source codes: https://github.com/lvgl/lvgl/tree/master/examples
//      * ----------------------------------------------------------------

//      lv_example_btn_1();

//      * Or try out a demo. Don't forget to enable the demos in lv_conf.h. E.g. LV_USE_DEMO_WIDGETS
//      * -------------------------------------------------------------------------------------------

//      lv_demo_widgets();
//      */

//     lv_obj_t *label = lv_label_create( lv_screen_active() );
//     lv_label_set_text( label, "Hello Arduino, I'm LVGL!" );
//     lv_obj_align( label, LV_ALIGN_CENTER, 0, 0 );

//     Serial.println( "Setup done" );
// }

// void loop()
// {
//     lv_timer_handler(); /* let the GUI do its work */
//     delay(5); /* let this time pass */
// }
