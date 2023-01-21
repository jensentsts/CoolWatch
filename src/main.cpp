
#define DEBUG 0

#include <Arduino.h>

#include "hardware.h"
#include "CoolSystem.h"
#include "CoolApp.h"
#include "img.h"

void setup() {
    hardwareio_mgr.Load();
}

void loop() {
    // @todo 睡眠管理
    // @todo 将时钟都放到小核里去
    if (lv_disp_get_inactive_time(NULL) < SYS_TICK_STOP_TIME)
    {
        lv_timer_handler();
    }
    task_mgr.ActivityMonitor();
    delay(5);
}