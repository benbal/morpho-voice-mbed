//--------------------------------------------------------------------------
void fonctionAx(char bufferenvoie[]){
    //selection fonction pc to ax
    //if (check(bufferreception)==bufferreception[15]){ 
            led1 = 1;
            wait(0.2);
            led1 = 0;
        trame trameStandard;
        trameStandard=tramePcToTrameStandard(bufferenvoie);

        char adresseDebut;
        char trameEnvoie[50];
        if(trameStandard.groupe=='0'){
            led1 = 1;
            wait(0.2);
            led1 = 0;
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
                    //commande read
                    trameStandard=commandeReadAx(trameStandard,0xE1,0x02);
                    creeTrameAx(trameStandard,trameEnvoie);
                    envoieTrameAx12(trameEnvoie, selectionRxTx);
                    break;
                case '4':
                    //commande reg write position
                    adresseDebut=indexAdresseGoalPosition;
                    trameStandard=commandeRegWriteAx(trameStandard,adresseDebut);
                    creeTrameAx(trameStandard,trameEnvoie);
                    envoieTrameAx12(trameEnvoie, selectionRxTx);
                    break;
                case '5':
                    //commande action
                    trameStandard=commandeActionAx(trameStandard);
                    creeTrameAx(trameStandard,trameEnvoie);
                    envoieTrameAx12(trameEnvoie, selectionRxTx);
                    break;
                case '6':
                    //commande reponse
                    adresseDebut=0x10;
                    trameStandard.instruction=indexCommandeWriteData;
                    trameStandard.parametres[0]=adresseDebut;
                    trameStandard.parametres[1]=0x02;
                    trameStandard.nParametres=2;
                    creeTrameAx(trameStandard,trameEnvoie);
                    envoieTrameAx12(trameEnvoie, selectionRxTx);
                    break;
                case '7':
                    //commande action
                    trameStandard=commandeActionAx(trameStandard);
                    creeTrameAx(trameStandard,trameEnvoie);
                    envoieTrameAx12(trameEnvoie, selectionRxTx);
                    break;
                case '8':
                    //commande action
                    trameStandard=commandeActionAx(trameStandard);
                    creeTrameAx(trameStandard,trameEnvoie);
                    envoieTrameAx12(trameEnvoie, selectionRxTx);
                    break;
            }
        }
        if(trameStandard.groupe=='2'){
            led1 = 1;
            wait(0.2);
            led1 = 0;
            switch (trameStandard.instruction){
                case '0':
                        //commande read
                        pc.putc(0x42);
                        trameStandard=commandeReadAx(trameStandard,0x1E,0x02);
                        creeTrameAx(trameStandard,trameEnvoie);
                        envoieTrameAx12(trameEnvoie, selectionRxTx);
                        break;
                case '1':
                        //commande read
                        trameStandard=commandeReadAx(trameStandard,0x26,0x02);
                        creeTrameAx(trameStandard,trameEnvoie);
                        envoieTrameAx12(trameEnvoie, selectionRxTx);
                        break;
            }
        }        
    //}
}
//--------------------------------------------------------------------------
void fonctionPc(char test[]){
//selection fonction ax to pc
    if (checkSum2(0,test[1]+1,test)==test[test[1]+1]){ 
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