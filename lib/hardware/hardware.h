#ifndef __hardware_h
#define __hardware_h

typedef enum
{
    BATTERY,
    BATTERY_LOW_POWER,
    USB
}PowerStatue;

void Power_On();
void Power_Off();
double Power_Quantity(void);
PowerStatue Power_GetStatue();

#endif // __hardware_h
