/*
 * flightcontrol.h
 *
 *  Created on: 6 февр. 2019 г.
 *      Author: »рина
 */

#ifndef FLIGHTCONTROL_H_
#define FLIGHTCONTROL_H_

#include "fuzzy.h"

#define constrain(amt, low, high) ((amt) < (low) ? (low) : ((amt) > (high) ? (high) : (amt)))

int16_t iprevRollError;
int16_t iprevPitchError;
int16_t iprevYawError;
float acPitch;
float acRoll;
float acYaw;

void FC_Init();
void FlightControl();
void selfStabilizing();
#endif /* FLIGHTCONTROL_H_ */
