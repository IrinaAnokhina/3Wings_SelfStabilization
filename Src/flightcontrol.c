/*
 * flightcontrol.c
 *
 *  Created on: 6 ����. 2019 �.
 *      Author: �����
 */

#include"flightcontrol.h"

_acRoll = 0;

void selfStabilizing() {
    //
    //TODO:
    int16_t _iRollError = (int16_t)((_acRoll - RP_Data.aRoll) * 8);  //
    //
    int8_t iRollError = constrain(_iRollError, -125, 125);
    int8_t iDeltaError = constrain(iRollError - iprevRollError, -125, 125);
    //
    iprevRollError = iRollError;

    //
    double dMTh = getFuzzyConclusion(iRollError, iDeltaError) * 16;  // 16 = 2000/125 - максимальное исправление в 1000 при 125

    //
    //
    int16_t iPart = (int16_t)(dMTh * 0.5);
    lmSpeed = stallSpeed - iPart;
    rmSpeed = stallSpeed + iPart;

    // проверка для невылета за максимальный диапазон
    if (lmSpeed > BLDC_MAX_PWM) {
        int16_t _d = lmSpeed - BLDC_MAX_PWM;
        lmSpeed = BLDC_MAX_PWM;
        rmSpeed -= _d;
    }
    if (rmSpeed > BLDC_MAX_PWM) {
        int16_t _d = rmSpeed - BLDC_MAX_PWM;
        rmSpeed = BLDC_MAX_PWM;
        lmSpeed -= _d;
    }

    char msg[40];
    uint16_t len = sprintf(msg, "iMTh: %i iRollError:%i lmSpeed:%i rmSpeed:%i  \r\n", (int16_t)(floor(dMTh)), (int16_t)(floor(iRollError)), lmSpeed, rmSpeed);
    HAL_UART_Transmit(&huart1, (uint8_t *)msg, len, HAL_MAX_DELAY);
}
