/*
 * flightcontrol.c
 *
 *  Created on: 6 февр. 2019 г.
 *      Author: »рина
 */

#include"flightcontrol.h"
#include"Accel.h"
#include"fuzzy.h"
#include"PID.h"

extern int16_t dMThX, dMThY, dMThZ;
extern int16_t xval, yval, zval;
extern int8_t buffer_str[22];
void selfStabilizing() {

	 int16_t _iRollError = (int16_t)((acRoll - xval) * 8);  // 125/8 = 15.6 degree = max
	    int16_t _iPitchError = (int16_t)((acPitch - yval) * 8);  // 125/8 = 15.6 degree = max
	    int16_t _iYawError = (int16_t)((acYaw - zval) * 8);
	    //
	    int8_t iRollError = constrain(_iRollError, -125, 125);
	    int8_t iDeltaRError = constrain(iRollError - iprevRollError, -125, 125);
	    int8_t iPitchError = constrain(_iPitchError, -125, 125);
	    int8_t iDeltaPError = constrain(iPitchError - iprevPitchError, -125, 125);
	    int8_t iYawError = constrain(_iYawError, -125, 125);
	    int8_t iDeltaYError = constrain(iYawError - iprevYawError, -125, 125);
	    //
	    iprevRollError = iRollError;
	    iprevPitchError = iPitchError;
	    iprevYawError = iYawError;

	    integrRError += iRollError*90/125;
	    integrPError += iPitchError*90/125;
	    integrYError += iYawError*90/125;
	    integrRError /= 10;
	   	integrPError /= 10;
	   	integrYError /= 10;

	    dMThX = getPID(iRollError, integrRError, iDeltaRError);
	    dMThY = getPID(iPitchError, integrPError, iDeltaPError);
	    dMThZ = getPID(iYawError, integrYError, iDeltaYError);
	    dMThX = constrain(dMThX, -125, 125) *90/125;
	    dMThY = constrain(dMThY, -125, 125)*90/125;
	    dMThZ = constrain(dMThZ, -125, 125)*90/125;
	    /*
	        dMThX = getFuzzyConclusion(iRollError, iDeltaRError) * 90 / 125; //
	        dMThY = getFuzzyConclusion(iPitchError, iDeltaPError) * 90 / 125;
	        dMThZ = getFuzzyConclusion(iYawError, iDeltaYError) * 90 / 125;*/


	    buffer_str[0] = 10;
	    buffer_str[1] = xval;
	    buffer_str[2] =	iRollError;
	    buffer_str[3] = iDeltaRError;
	    buffer_str[4] = integrRError;
	    buffer_str[5] = dMThX;
	    buffer_str[6] =	yval;
	    buffer_str[7] = iPitchError;
	    buffer_str[8] = iDeltaPError;
	    buffer_str[9] = integrPError;
	    buffer_str[10] = dMThY;
	    buffer_str[11] = zval;
	    buffer_str[12] = iYawError;
	    buffer_str[13] = iDeltaYError;
	    buffer_str[14] = integrYError;
	    buffer_str[15] = dMThZ;

 }
