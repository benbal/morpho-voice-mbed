#ifndef DEF_COMMUNICATION
#define DEF_COMMUNICATION
    #include "mbed.h"
    #include "Serial.h"
    #include "fonction.h"
    #include "reglage.h"
    #include "capteurPression.h"
    #include "variableGlobal.h"
    #include "selectionfonction.h"
    void communication(Ticker);
    void envoieTrameAx12(char [100]);
    void envoieTramePc(Serial, char [17]);
    void envoieMoteur(char mouvement);
    void fonctionserialPc ();
    void fonctionSerialAx ();
    void tempsMort(AnalogIn );
#endif