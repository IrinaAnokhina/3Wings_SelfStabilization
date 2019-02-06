/*
 * fuzzy.h
 *
 *  Created on: 6 февр. 2019 г.
 *      Author: »рина
 */

#ifndef FUZZY_H_
#define FUZZY_H_

#include <math.h>
#include <stdint.h>


#define fVLN -125  //
#define fLN -90    //
#define fMN -55    //
#define fSN -20    //
#define fNO 0      //
#define fSP 20     //
#define fMP 55     //
#define fLP 90     //
#define fVLP 125   //

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

typedef enum {
    AND,
    OR
} op_type;

uint8_t numofrules;

struct rule {
    int8_t fe;
    op_type op;
    int8_t fde;
    int8_t z;
};
struct rule rules[12];

double mu(int8_t x, int8_t A);


void addrule(int8_t fe, op_type op, int8_t fde, int8_t z);


float getFuzzyConclusion(int8_t e, int8_t de);

void Fuzzy_Init();

#endif /* FUZZY_H_ */
