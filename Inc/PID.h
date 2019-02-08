/*
 * PID.h
 *
 *  Created on: 8 февр. 2019 г.
 *      Author: »рина
 */

#ifndef PID_H_
#define PID_H_

#include"stdint.h"

float P_koef;
float I_koef;
float D_koef;

int16_t getPID(int8_t, int32_t, int8_t);
#endif /* PID_H_ */
