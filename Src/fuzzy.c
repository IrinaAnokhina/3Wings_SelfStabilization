/*
 * fuzzy.c
 *
 *  Created on: 6 февр. 2019 г.
 *      Author: »рина
 */

#include "fuzzy.h"

double mu(int8_t x, int8_t A) {
    return exp(-(pow(x - A, 2) / (2 * pow(30, 2))));
}

void addrule(int8_t fe, op_type op, int8_t fde, int8_t z) {
    rules[numofrules].fe = fe;
    rules[numofrules].op = op;
    rules[numofrules].fde = fde;
    rules[numofrules].z = z;
    numofrules++;
}

double getFuzzyConclusion(int8_t e, int8_t de) {
    double summ_alpha_c = 0, summ_alpha = 0;
    //
    for (int i = 0; i < (int)(numofrules); i++) {
        double alpha = 0, mue = 0, mude = 0;
        //
        mue = mu(e, rules[i].fe);
        //
        mude = mu(de, rules[i].fde);
        //
        alpha = rules[i].op == 0 ? MIN(mue, mude) : MAX(mue, mude);
        //
        //
        summ_alpha_c += (alpha * rules[i].z);
        summ_alpha += alpha;
    }

    //
    return summ_alpha_c / summ_alpha;
}

void Fuzzy_Init() {
    numofrules = 0;

    addrule(fNO, AND, fNO, fNO);
    addrule(fVLN, OR, fVLN, fVLP);
    addrule(fVLP, OR, fVLP, fVLN);
    addrule(fLN, AND, fSN, fVLP);
    addrule(fLP, AND, fSP, fVLN);
    addrule(fSN, AND, fSN, fSP);
    addrule(fSP, AND, fSP, fSN);

    addrule(fMN, AND, fMP, fSP);
    addrule(fMN, AND, fMN, fLP);
    addrule(fMP, AND, fMN, fSN);
    addrule(fMP, AND, fMP, fLN);
}

