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
        mp.baud(vitesseMp);
    //reglage fonction de call back
        //communication
        pc.attach(&fonctionserial);
        ax.attach(&fonctionSerialAx);
        //fin de capteur course
        finDeCourse.rise(&commandeFinDeCourse);
        finDeCourse2.rise(&commandeFinDeCourse);
        //Appel du tempsEcoule
        //tempsEnSecondeAttenduEntreChaqueEchantillon = 0.1;
        tempsEcoule.attach(&tempsMort,tempsEnSecondeAttenduEntreChaqueEchantillon);
        //temps 1 seconde
        unsigned char starMoteur[7]={0x31,0x2C,0x73,0x74,0x61,0x72,0x73};// 1,start
        envoieMoteur(starMoteur,7);
        moteurCommandeTime.attach(&moteurCommande,1);
        
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