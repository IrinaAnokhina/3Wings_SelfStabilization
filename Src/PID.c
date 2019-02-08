/*
 * PID.c
 *
 *  Created on: 8 февр. 2019 г.
 *      Author: »рина
 */

#include"PID.h"

int16_t getPID(int8_t error, int32_t sumErr, int8_t deltaErr)
{
	P_koef = 0.7;
	I_koef = 0.2;
	D_koef = 0.4;

	return P_koef*error + I_koef*sumErr + D_koef*deltaErr;
}
