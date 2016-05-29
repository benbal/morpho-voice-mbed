
//--------------------------------------------------------------------------
void fonctionAx(char bufferenvoie[]){
//selection fonction pc to ax
    //if (check(bufferreception)==bufferreception[15]){ 
    //verification checksun
        //led1 = !led1;
        trame trameStandard;
        trameStandard=tramePcToTrameStandard(bufferenvoie);
        char adresseDebut;
        char trameEnvoie[50];
        if(trameStandard.groupe=='0'){
        //commande ax-12
            switch (trameStandard.instruction){
                case '0':
                    //commande position
                    adresseDebut=indexAdresseGoalPosition;
                    trameStandard=commandeWriteAx(trameStandard,adresseDebut);
                    creeTrameAx(trameStandard,trameEnvoie);
                    envoieTrameAx12(trameEnvoie, selectionRxTx);
                    break;
                case '1':
                    //commande vitesse
                    adresseDebut=indexAdresseMovingSpeed;
                    trameStandard=commandeWriteAx(trameStandard,adresseDebut);
                    creeTrameAx(trameStandard,trameEnvoie);
                    envoieTrameAx12(trameEnvoie, selectionRxTx);
                    break;
                case '2':
                    //commande ping
                    trameStandard=commandePingAx(trameStandard);
                    creeTrameAx(trameStandard,trameEnvoie);
                    envoieTrameAx12(trameEnvoie, selectionRxTx);
                    break;
                case '3':
                    //commande reg write position
                    adresseDebut=indexAdresseGoalPosition;
                    trameStandard=commandeRegWriteAx(trameStandard,adresseDebut);
                    creeTrameAx(trameStandard,trameEnvoie);
                    envoieTrameAx12(trameEnvoie, selectionRxTx);
                    break;
                case '4':
                    //commande action
                    trameStandard=commandeActionAx(trameStandard);
                    creeTrameAx(trameStandard,trameEnvoie);
                    envoieTrameAx12(trameEnvoie, selectionRxTx);
                    break;
                case '5':
                    //commande reponse
                    trameStandard.instruction=indexCommandeWriteData;
                    trameStandard.parametres[0]=0x10;
                    trameStandard.parametres[1]=0x02;
                    trameStandard.nParametres=2;
                    creeTrameAx(trameStandard,trameEnvoie);
                    envoieTrameAx12(trameEnvoie, selectionRxTx);
                    break;
                case '6':
                    //commande SyncWrite
                    trameSyncWrite=commandeSyncWriteAx(trameStandard);
                    break;
                case '7':
                    //commande action SyncWrite
                    creeTrameAx(trameStandard,trameEnvoie);
                    envoieTrameAx12(trameEnvoie, selectionRxTx);
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
                    mouvement = 127+commandeMouvementMoteur(trameStandard);   
                    envoieMoteur(mouvement);
                    break;
                case '1':
                //commande marche arriere
                    mouvement = 127-commandeMouvementMoteur(trameStandard);   
                    envoieMoteur(mouvement);
                    break;
            }
        }
        else if(trameStandard.groupe=='2'){
        //commande pour ensemble des capteur ax-12 compris
            switch (trameStandard.instruction){
                case '0':
                        //commande read position ax-12
                        trameStandard=commandeReadAx(trameStandard,0x1E,0x02);
                        creeTrameAx(trameStandard,trameEnvoie);
                        envoieTrameAx12(trameEnvoie, selectionRxTx);
                        break;
                case '1':
                        //commande read vitesse ax-12
                        trameStandard=commandeReadAx(trameStandard,0x26,0x02);
                        creeTrameAx(trameStandard,trameEnvoie);
                        envoieTrameAx12(trameEnvoie, selectionRxTx);
                        break;
                case '2':
                        //commande read capteur de pression
                        trameStandard=commandePressionPc(trameStandard);
                        creeTramePc(trameStandard,trameEnvoie);
                        envoieTramePc(trameEnvoie);
                        break;
            }
        }
        else{
        //erreur a faire
        }        
    //}
}
//--------------------------------------------------------------------------
void fonctionPc(char test[]){
//selection fonction ax to pc
    if (checkSum2(0,test[1]+1,test)==test[test[1]+1]){ 
    //verification checksum
        trame trameStandard;
        trameStandard=trameAxToTrameStandard(test);
        char trameEnvoie[50];
        if(trameStandard.parametres[0]==0x00){
            if (trameStandard.nParametres==1){
                trameStandard=commandePingPc(trameStandard);
                creeTramePc(trameStandard,trameEnvoie);
                envoieTramePc(trameEnvoie);
            }
            else{
                //retour d'un read
                trameStandard=commandeReadPc(trameStandard);
                creeTramePc(trameStandard,trameEnvoie);
                envoieTramePc(trameEnvoie);
            }
        }
        else{
            trameStandard=commandeErrorPc(trameStandard);
            creeTramePc(trameStandard,trameEnvoie);
            envoieTramePc(trameEnvoie);
        }   
    }
}
