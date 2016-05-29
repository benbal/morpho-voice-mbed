#include "fonction.h"
//--------------------------------------------------------------------------
void fonctionAx(char bufferenvoie[],classAx12 trameSyncWrite){
//selection fonction pc to ax
    //if (check(bufferreception)==bufferreception[15]){ 
    //verification checksun
        led1 = !led1;
        //mise en mise en forme de la trame pc
        classAx12 trameStandard;
        trameStandard.tramePcToTrameStandard(bufferenvoie);
        char adresseDebut;
        char trameEnvoie[50];
        if(trameStandard.groupe=='0'){
        //commande ax-12
            switch (trameStandard.instruction){
                case '0':
                    //commande position
                    adresseDebut=indexAdresseGoalPosition;
                    trameStandard.commandeWriteAx(adresseDebut);
                    trameStandard.creeTrameAx(trameEnvoie);
                    envoieTrameAx12(trameEnvoie);
                    break;
                case '1':
                    //commande vitesse
                    adresseDebut=indexAdresseMovingSpeed;
                    trameStandard.commandeWriteAx(adresseDebut);
                    trameStandard.creeTrameAx(trameEnvoie);
                    envoieTrameAx12(trameEnvoie);
                    break;
                case '2':
                    //commande ping
                    trameStandard.commandePingAx();
                    trameStandard.creeTrameAx(trameEnvoie);
                    envoieTrameAx12(trameEnvoie);
                    break;
                case '3':
                    //commande reg write position
                    adresseDebut=indexAdresseGoalPosition;
                    trameStandard.commandeRegWriteAx(adresseDebut);
                    trameStandard.creeTrameAx(trameEnvoie);
                    envoieTrameAx12(trameEnvoie);
                    break;
                case '4':
                    //commande action
                    trameStandard.commandeActionAx(0xFE);
                    trameStandard.creeTrameAx(trameEnvoie);
                    envoieTrameAx12(trameEnvoie);
                    break;
                case '5':
                    //commande reponse
                    trameStandard.instruction=indexCommandeWriteData;
                    trameStandard.parametres[0]=0x10;
                    trameStandard.parametres[1]=0x02;
                    trameStandard.nParametres=2;
                    trameStandard.creeTrameAx(trameEnvoie);
                    envoieTrameAx12(trameEnvoie);
                    break;
                case '6':
                    //commande SyncWrite
                    trameStandard.commandeSyncWriteAx();
                    trameSyncWrite=trameStandard;
                    break;
                case '7':
                    //commande action SyncWrite
                    trameSyncWrite.creeTrameAx(trameEnvoie);
                    envoieTrameAx12(trameEnvoie);
                    break;
            }
        }
        //
        else if(trameStandard.groupe=='1'){
        //commande pour pour le moteur poumon
            switch (trameStandard.instruction){
            //commande vitesse et direction
                unsigned char mouvement;
                case '0':
                //commande marche avant
                    mouvement = 127+trameStandard.commandeMouvementMoteur();   
                    envoieMoteur(mouvement);
                    
                    break;
                case '1':
                //commande marche arriere
                    mouvement = 127-trameStandard.commandeMouvementMoteur();   
                    envoieMoteur(mouvement);
                    break;
            }
        }
        else if(trameStandard.groupe=='2'){
        //commande pour ensemble des capteur ax-12 compris
            switch (trameStandard.instruction){
                case '0':
                        //commande read position ax-12
                        trameStandard.commandeReadAx(0x1E,0x02);
                        trameStandard.creeTrameAx(trameEnvoie);
                        envoieTrameAx12(trameEnvoie);
                        break;
                case '1':
                        //commande read vitesse ax-12
                        trameStandard.commandeReadAx(0x26,0x02);
                        trameStandard.creeTrameAx(trameEnvoie);
                        envoieTrameAx12(trameEnvoie);
                        break;
                case '2':
                        //commande read capteur de pression
                        /*trameStandard=commandePingPc(trameStandard);
                        creeTramePc(trameStandard,trameEnvoie);
                        //test45=moyenne;
                        test45=15;
                        trameEnvoie[8];
                        envoieTramePc(trameEnvoie);*/
                        
                       break;
            }
        }
        else{
        //erreur a faire
        }        
    //}
}
//--------------------------------------------------------------------------
/*void fonctionPc(char test[]){
//selection fonction ax to pc
    if (checkSum2(0,test[1]+1,test)==test[test[1]+1]){ 
    //verification checksum
        classAx12 trameStandard;
        trameStandard.trameAxToTrameStandard(test);
        char trameEnvoie[50];
        if(trameStandard.parametres[0]==0x00){
            if (trameStandard.nParametres==1){
                trameStandard.commandePingPc();
                trameStandard.creeTramePc(trameEnvoie);
                envoieTramePc(pc,trameEnvoie);
            }
            else{
                trameStandard.commandeReadPc();
                trameStandard.creeTramePc(trameEnvoie);
                envoieTramePc(pc,trameEnvoie);
            }
        }
        else{
            trameStandard.commandeErrorPc();
            trameStandard.creeTramePc(trameEnvoie);
            envoieTramePc(pc,trameEnvoie);
        }   
    }
}*/

//--------------------------------------------------------------------------
void fonctionFinDeCourse (){
//fonction callback fin de course 
     //envoieMoteur(0x7f);//stop = 0x7f= 127
}
//--------------------------------------------------------------------------
unsigned int charToInt(char donneesAConvertire[], char debutDonnees,char finDonnees){
//tranforme 3 char en unsigned int tel que ex:0x30,0x31,0x35,0x30,0x30,0x30=> 0150,00
    unsigned int decimalNumber=0,decimalTotal=0,multiplicateur=1;
    int y=0;
    for (int x=finDonnees;x>=debutDonnees;x--){
        decimalNumber=(donneesAConvertire[finDonnees-y]-0x30)*multiplicateur;
        decimalTotal+=decimalNumber;
        multiplicateur*=10;    
        y++;
    }
    return (decimalTotal);
}
//--------------------------------------------------------------------------
void intToChar(char donneesAConvertire[],unsigned int degrees){
//tranforme unsigned int en 3 char tel que ex:0150,00 => 0x00 0x01 0x05 0x00 0x00 0x0
//a mettre au propre
    float us1=0,us2=0,us3=0,us4=0;
    float ux1=0,ux2=0,ux3=0;
    us1=degrees/1000;
    ux1=us1*1000;
    us2=floor((degrees-ux1)/100);
    ux2=us2*100;
    us3=floor((degrees-(ux1+ux2))/10);
    ux3=us3*10;
    us4=floor((degrees-(ux1+ux2+ux3)));
    donneesAConvertire[0]=us1;
    donneesAConvertire[1]=us2;
    donneesAConvertire[2]=us3;
    donneesAConvertire[3]=us4;
    donneesAConvertire[4]=0;
    donneesAConvertire[5]=0;
}
//--------------------------------------------------------------------------
unsigned int degreToLong(unsigned int degrees){
//transforme un entier en degre 0->300° en long de 0->1024
    unsigned int longDegrees;
    longDegrees=floor((degrees)/0.29296875);
    if(longDegrees>=1024){
        longDegrees=1023;   
    }
    return (longDegrees);
}
//--------------------------------------------------------------------------
unsigned int longToDegre(unsigned int longDegrees){
    //transforme un long de 0->1024 entier en degre 0->300°  
    unsigned int degrees;
    degrees=floor((longDegrees)*0.29296875);
    return (degrees);
}
//--------------------------------------------------------------------------
unsigned char intToShort(unsigned int mouvement){
//transforme un entier en degre 0->100 en short de 0->127
    unsigned char longDegrees;
    longDegrees=floor((mouvement)*1.27);
    if(longDegrees>=128){
        longDegrees=127;   
    }
    return (longDegrees);
}
//--------------------------------------------------------------------------
char checkSum2(char debutElement,char finElement, char element[50]){
//calcul le checksum trame ax
    int somme=0;
    for (char i=debutElement;i<finElement;i++){
    somme+=element[i];
    somme%= 256;
    }
    somme=~somme;
    return (somme);
}
//--------------------------------------------------------------------------
char check(char bufferreception [17]){
//calcul le checksum trame pc
    int somme2=0;
    for(int b=0;b<=14;b++){ 
        somme2+=bufferreception[b];
    }   
    char somme=(somme2%128);
    return (somme);
}