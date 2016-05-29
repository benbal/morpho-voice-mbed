#ifndef DEF_CAPTEURPRESSION
#define DEF_CAPTEURPRESSION
#include "mbed.h"
#include "variableGlobal.h"
    unsigned char poiteurpression;
    void les10PremieresValeurs(AnalogIn);
    void tempsMort(AnalogIn);
    float lectureEtMesure(AnalogIn);
#endif