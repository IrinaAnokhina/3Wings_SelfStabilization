/*
 * PID.c
 *
 *  Created on: 8 февр. 2019 г.
 *      Author: »рина
 */

#include"PID.h"

extern int8_t buffer_str[22];

int16_t getPID(int8_t error, int32_t sumErr, int8_t deltaErr)
{
	P_koef = 0.8;
	I_koef = 0.1;
	D_koef = 0.2;

	 buffer_str[16] = P_koef*10;
	 buffer_str[17] = I_koef*10;
	 buffer_str[18] = D_koef*10;
	return P_koef*error + I_koef*sumErr + D_koef*deltaErr;
}
