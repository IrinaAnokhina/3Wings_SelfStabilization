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

int8_t iprevRollError;
float _acPitch;
float _acRoll;


void FC_Init();
void FlightControl();
void selfStabilizing();
#endif /* FLIGHTCONTROL_H_ */
