/*
 * Accel.h
 *
 *  Created on: 4 окт. 2018 г.
 *      Author: AnokhinaIrina
 */

#ifndef ACCEL_H_
#define ACCEL_H_

#include"stdint.h"
#include "i2c.h"

#define adress 0xD0
#define R2DEG 57.29577951308232087679815481410517033f
#define KOEF_COMPL 0.2

typedef struct  {
    float aRoll;// X-data
    float aPitch;//  Y-data
    float aYaw;//    Z-data
} tsRP_Data;


void Accel_ini();
void Accel_ReadAcc(void);
void ReadGyro();
void GyroCalibrate();
void deriveGyro();

#endif /* ACCEL_H_ */
