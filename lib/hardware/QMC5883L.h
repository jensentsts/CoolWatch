/**
 * @file QMC5883L.h
 * @author Jensentsts (jensentsts@163.com)
 * @brief 
 * @version 1.0.0
 * @date 2023-01-16
 * 
 * @copyright CC4.0 BY-NC-SA
 * 
 */

#ifndef __QMC5883L_h
#define __QMC5883L_h

#include <Arduino.h>
#include "pins.h"

struct QMC5883L_DataPackage
{
    double x, y, z;
};

void QMC5883L_I2C_Start(void);
void QMC5883L_I2C_Stop(void);
void QMC5883L_I2C_SendByte(uint8_t dat);
void QMC5883L_Init(void);
void QMC5883L_SendData(uint8_t dat);
void QMC5883L_SendCmd(uint8_t cmd);
QMC5883L_DataPackage QMC5883L_GetData(void);

#endif // __QMC5883L_h
