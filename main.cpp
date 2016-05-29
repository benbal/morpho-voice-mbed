#include "mbed.h"
#include "Serial.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "registrefonction.h"
#include "defautvariable.h"
#include "variableGlobal.h"
#include "reglage.h"
#include "fonction.h"
#include "commande.h"
#include "selectionfonction.h"
int main() {
//reglage 
    ax.baud(vitesseAx);
    pc.baud(vitessePc);
    mp.baud(vitessePc);
    pc.attach(&fonctionserial);
    ax.attach(&fonctionSerialAx);
    selectionRxTx=0;
    finDeCourse.rise(&fonctionFinDeCourse);
    finDeCourse2.rise(&fonctionFinDeCourse);
/*CODE RESERVE
FILE* fichier = NULL;
fichier = fopen("test.txt", "r+");
char szNumbers[] = "B";
char * pEnd;
long int li1, li2, li3, li4;
li1=strtol (szNumbers,&pEnd,16);
int i ;
i=int (szNumbers);*/
    while(1){
        //pas de code ici
    }
    
}