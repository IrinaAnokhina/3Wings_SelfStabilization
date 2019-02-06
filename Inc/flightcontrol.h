/*
 * flightcontrol.h
 *
 *  Created on: 6 ����. 2019 �.
 *      Author: �����
 */

#ifndef FLIGHTCONTROL_H_
#define FLIGHTCONTROL_H_

#include "fuzzy.h"

#define constrain(amt, low, high) ((amt) < (low) ? (low) : ((amt) > (high) ? (high) : (amt)))

int16_t iprevRollError;
int16_t iprevPitchError;
float acPitch;
float acRoll;


void FC_Init();
void FlightControl();
void selfStabilizing();
#endif /* FLIGHTCONTROL_H_ */
