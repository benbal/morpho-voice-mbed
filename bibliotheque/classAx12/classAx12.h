#ifndef DEF_AX12
#include "mbed.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fonction.h"
#include "reglage.h"
#include "variableGlobal.h"
#define DEF_AX12
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
//
        void fonctionAx(char[],class classAx12);
        void fonctionPc(char[]);
        //
        void communication(Ticker);
        void envoieTrameAx12(char [100]);
        void envoieTramePc(Serial, char [17]);
        void envoieMoteur(char mouvement);
        void fonctionFinDeCourse();
        void fonctionserialPc ();
        void fonctionSerialAx ();
        void tempsMort(AnalogIn );


#endif