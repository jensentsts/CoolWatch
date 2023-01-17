#include "Power.h"
#include "hardware.h"
#include "Mgr.h"
#include <Arduino.h>
#include <driver/gpio.h>
// #include <driver/adc.h>

hw_timer_t *power_timer = nullptr;

void Key_Power_TimerIntr(void)
{
    hardwareio_mgr.Shutdown();
}

void IRAM_ATTR Key_Power_Intr(void)
{
    if (timerStarted(power_timer))
    {
        timerStop(power_timer);
    }
    else
    {
        timerWrite(power_timer, 0);
        timerStart(power_timer);
    }
}

void Power_Init()
{
    pinMode(POWER_IO, OUTPUT);

    pinMode(KEY_POWER, INPUT_PULLUP);
    attachInterrupt(KEY_POWER, Key_Power_Intr, GPIO_INTR_ANYEDGE);

    analogSetPinAttenuation(ADC_BAT, ADC_11db);
    analogReadResolution(12);
    adcAttachPin(ADC_BAT);
    adcStart();

    power_timer = timerBegin(0, 8000, true);
    timerAttachInterrupt(power_timer, Key_Power_TimerIntr, true);
    timerAlarmWrite(power_timer, POWER_INTERVAL * 1000, false);
    timerAlarmEnable(power_timer);
}

void Power_On()
{
    digitalWrite(POWER_IO, HIGH);
}

void Power_Off()
{
    digitalWrite(POWER_IO, LOW);
}

double Power_Quantity()
{
    auto vol = analogRead(ADC_BAT);
    return (double)vol / 4096.0 * 2.6 * 2.0;
}

PowerStatue Power_GetStatue()
{
    double vol = Power_Quantity();
    if (vol <= 3.1)
    {
        return BATTERY_LOW_POWER;
    }
    if (vol >= 4.8)
    {
        return USB_CONNECTED;
    }
    return BATTERY;
}
