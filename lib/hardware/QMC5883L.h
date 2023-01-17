#ifndef __QMC5883L_h
#define __QMC5883L_h

#include <Arduino.h>
#include "pins.h"

struct QMC5883L_DataPackage
{
    double x, y, z;
};

void QMC5883L_Init(void);
QMC5883L_DataPackage QMC5883L_GetData(void);
uint16_t QMC5883L_GetXData(void);
uint16_t QMC5883L_GetYData(void);
uint16_t QMC5883L_GetZData(void);
void QMC5883L_Start(void);
void QMC5883L_Stop(void);

/* 采样率 */
#define QMC5883L_OSR_512                        0x0
#define QMC5883L_OSR_256                        0x1
#define QMC5883L_OSR_128                        0x2
#define QMC5883L_OSR_64                         0X3

/* 量程 */
#define QMC5883L_RNG_2                          0x0
#define QMC5883L_RNG_8                          0x1

/* 输出频率 */
#define QMC5883L_ODR_10HZ                       0x0
#define QMC5883L_ODR_50HZ                       0x1
#define QMC5883L_ODR_100HZ                      0x2
#define QMC5883L_ODR_200HZ                      0x3

/* 工作模式选择 */
#define QMC5883L_MODE_STOP                      0x0
#define QMC5883L_MODE_CONTINOUS                 0x1

/* 工作设置*/
#define QMC5883L_SETTING (QMC5883L_OSR_512 << 6) | \
                        (QMC5883L_RNG_8 << 4) | \
                        (QMC5883L_ODR_100HZ << 2) | \
                        (0x0)   // 工作模式位，此处应置零

/* 器件地址：设备从地址+读写选择 */
#define	QMC5883L_ADDR_WRITE                     0x1A
#define	QMC5883L_ADDR_READ	                    0x1B


/* 设备寄存器地址 */
#define	QMC5883L_ADDR_XOUTL                     0x00
#define	QMC5883L_ADDR_XOUTH                     0x01
#define	QMC5883L_ADDR_YOUTL                     0x02
#define	QMC5883L_ADDR_YOUTH                     0x03
#define	QMC5883L_ADDR_ZOUTL                     0x04
#define QMC5883L_ADDR_ZOUTH                     0x05
#define	QMC5883L_ADDR_STATUS                    0x06
#define	QMC5883L_ADDR_TEMPL                     0x07
#define	QMC5883L_ADDR_TEMPH                     0x08
#define	QMC5883L_ADDR_CFGA                      0x09
#define	QMC5883L_ADDR_CFGB                      0x0A
#define QMC5883L_ADDR_PERIORC                   0x0B
#define QMC5883L_ADDR_CHIPID                    0x0D
#define	QMC5883L_ADDR_CFGC                      0x20
#define	QMC5883L_ADDR_CFGD                      0x21

#endif // __QMC5883L_h
