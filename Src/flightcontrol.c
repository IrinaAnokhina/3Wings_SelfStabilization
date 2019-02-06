/*
 * flightcontrol.c
 *
 *  Created on: 6 февр. 2019 г.
 *      Author: »рина
 */

#include"flightcontrol.h"
#include"Accel.h"
#include"fuzzy.h"

extern int16_t dMThX, dMThY;
extern int16_t xval, yval, zval;

void selfStabilizing() {
    //
    //TODO:
    int16_t _iRollError = (int16_t)((acRoll - xval) * 8);  // 125/8 = 15.6 degree = max
    int16_t _iPitchError = (int16_t)((acPitch - yval) * 8);  // 125/8 = 15.6 degree = max
    //
    int8_t iRollError = constrain(_iRollError, -125, 125);
    int8_t iDeltaRError = constrain(iRollError - iprevRollError, -125, 125);
    int8_t iPitchError = constrain(_iPitchError, -125, 125);
    int8_t iDeltaPError = constrain(iPitchError - iprevPitchError, -125, 125);

    //
    iprevRollError = iRollError;
    iprevPitchError = iPitchError;
    //
     dMThX = getFuzzyConclusion(iRollError, iDeltaRError) * 90 / 125; //
     dMThY = getFuzzyConclusion(iPitchError, iDeltaPError) * 90 / 125;
    //dMTh = constrain(dMTh, 0, 2000);
    //
    //

}
