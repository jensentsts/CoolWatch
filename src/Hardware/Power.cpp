#include "Power.h"
#include <Arduino.h>
#include <driver/gpio.h>
#include <driver/adc.h>
#include "hardware.h"
#include "TimerConf.h"
#include "Mgr.h"

hw_timer_t *power_timer = nullptr;

void Key_Power_TimerIntr(void)
{
    hardwareio_mgr.Close();
    Power_Off();
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
    adc_digi_start();

    power_timer = timerBegin(POWER_TIMER, POWER_TIMER_DIV, true);
    timerAttachInterrupt(power_timer, Key_Power_TimerIntr, true);
    timerAlarmWrite(power_timer, POWER_INTERVAL * 1000, false);
    timerAlarmEnable(power_timer);
    timerSetAutoReload(power_timer, false);
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
    if (vol <= POWER_LOW_VOLTAGE_LEVEL)
    {
        return BATTERY_LOW_POWER;
    }
    if (vol >= POWER_USB_CONNECTED_VOLTAGE_LEVEL)
    {
        return USB_CONNECTED;
    }
    return BATTERY;
}
