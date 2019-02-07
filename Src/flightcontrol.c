/*
 * flightcontrol.c
 *
 *  Created on: 6 февр. 2019 г.
 *      Author: »рина
 */

#include"flightcontrol.h"
#include"Accel.h"
#include"fuzzy.h"

extern int16_t dMThX, dMThY, dMThZ;
extern int16_t xval, yval, zval;

void selfStabilizing() {
    //
    //TODO:
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
    //
     dMThX = getFuzzyConclusion(iRollError, iDeltaRError) * 90 / 125; //
     dMThY = getFuzzyConclusion(iPitchError, iDeltaPError) * 90 / 125;
     dMThZ = getFuzzyConclusion(iYawError, iDeltaYError) * 90 / 125;
    //dMTh = constrain(dMTh, 0, 2000);
    //
    //

}
