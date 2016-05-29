#include "mbed.h"
#include "Serial.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "registrefonction.h"
#include "defautvariable.h"
#include "variableGlobal.h"
#include "reglage.h"
#include "test.h"
#include "fonction.h"
#include "commande.h"
#include "selectionfonction.h"
int main() {
//reglage 
selectionRxTx=0;
    //reglage vitesse serial
        ax.baud(vitesseAx);
        pc.baud(vitessePc);
        mp.baud(vitessePc);
    //reglage fonction de call back
        //communication
        pc.attach(&fonctionserial);
        ax.attach(&fonctionSerialAx);
        //fin de capteur course
        finDeCourse.rise(&fonctionFinDeCourse);
        finDeCourse2.rise(&fonctionFinDeCourse);
        //Appel du tempsEcoule
        //float tempsEnSecondeAttenduEntreChaqueEchantillon = 0.1;
        tempsEcoule.attach(&tempsMort,tempsEnSecondeAttenduEntreChaqueEchantillon);
    //Appel de la fonction qui initialise les 10 premières valeurs du Capteur
        les10PremieresValeurs();
    
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