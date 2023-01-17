/**
 * @file TimerInfo.h
 * @author Jensentsts (jensentsts@163.com)
 * @brief 定时器有关设定
 * @version 1.0.0
 * @date 2023-01-18
 * 
 * @copyright CC4.0 BY-NC-SA
 * 
 */

#ifndef __TimerInfo_h
#define __TimerInfo_h

// 关机用时钟
#define POWER_TIMER 0
#define POWER_TIMER_DIV 8000
#define POWER_INTERVAL 2333

// lvgl tick
#define TFTLCD_TIMER 1
#define TFTLCD_TIMER_DIV 8000
#define TFTLCD_TIMEOUT 1

// 系统计时时钟
#define SYS_TIMER 2
#define SYS_TIMER_DIV 8000
#define SYS_TIMEOUT 1

#endif // __TimerInfo_h
