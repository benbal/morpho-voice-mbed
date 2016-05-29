#ifndef DEF_FONCTION
#include "mbed.h"
#include "Serial.h"
#include "defautvariable.h"
#define DEF_FONCTION
        unsigned int charToInt(char[],char,char);
        void intToChar(char[],unsigned int);
        unsigned int degreToLong(unsigned int);
        unsigned int longToDegre(unsigned int );
        unsigned char intToShort(unsigned int );
        char checkSum2(char ,char, char[50]);
        char check(char bufferreception [17]);
        
#endif