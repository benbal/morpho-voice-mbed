#include "selectionfonction.h"
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
