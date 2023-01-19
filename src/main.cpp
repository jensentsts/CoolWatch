
#define DEBUG 1

#include <Arduino.h>

#include "hardware.h"
#include "CoolSystem.h"
#include "CoolApp.h"
#include "img.h"

void setup() {
    #if DEBUG == 1
    Serial.begin(115400);
    Serial.printf("Loading...\n\r");
    #endif // DEBUG

    hardwareio_mgr.Load();
}

void loop() {
    // @todo 睡眠管理
    // @todo 将时钟都放到小核里去
    if (lv_disp_get_inactive_time(NULL) < 3000)
    {
        lv_timer_handler();
    }
    else
    {
        TFTLCD_TickStop();
    }
    delay(5);
}