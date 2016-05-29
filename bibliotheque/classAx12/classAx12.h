#ifndef DEF_AX12
#define DEF_AX12
#include "mbed.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fonction.h"
class classAx12
{
    private:
    public:
        //trame trameStandard;
        char groupe;
        char id;
        char instruction;
        char nParametres;
        char parametres[10];
        char controleErreur;
        //
        void commandePingAx();
        void commandeReadAx(char,char );
        void commandeRegWriteAx(char);
        void commandeWriteAx(char);
        void commandeActionAx(char);
        void commandeSyncWriteAx();
        void commandePingPc();
        void commandeErrorPc();
        void commandeReadPc();
        unsigned char commandeMouvementMoteur();
        void creeTrameAx(char[]);
        void creeTramePc(char[]);
        void tramePcToTrameStandard(char[]);
        void trameAxToTrameStandard(char[]);
   
};


#endif