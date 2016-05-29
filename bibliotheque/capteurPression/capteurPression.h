#ifndef DEF_CAPTEURPRESSION
#include "mbed.h"
#include "variableGlobal.h"
#define DEF_CAPTEURPRESSION
    unsigned char poiteurpression;
    void les10PremieresValeurs(AnalogIn);
    void tempsMort(AnalogIn);
    float lectureEtMesure(AnalogIn);
#endif