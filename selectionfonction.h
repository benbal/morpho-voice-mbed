//--------------------------------------------------------------------------
void fonctionAx(char bufferenvoie[]){
//selection fonction pc to ax
    //if (check(bufferreception)==bufferreception[15]){ 
        trame trameStandard;
        trameStandard=tramePcToTrameStandard(bufferenvoie);
        char adresseDebut;
        char trameEnvoie[50];
        switch (trameStandard.instruction){
            case '0':
                //commande position
                pc.putc(0x00);
                adresseDebut=indexAdresseGoalPosition;
                trameStandard=commandeWriteAx(trameStandard,adresseDebut);
                creeTrameAx(trameStandard,trameEnvoie);
                envoieTrameAx12(trameEnvoie, selectionRxTx);
                break;
            case '1':
                //commande vitesse
                pc.putc(0x01);
                adresseDebut=indexAdresseMovingSpeed;
                trameStandard=commandeWriteAx(trameStandard,adresseDebut);
                creeTrameAx(trameStandard,trameEnvoie);
                envoieTrameAx12(trameEnvoie, selectionRxTx);
                break;
            case '2':
                //commande ping
                pc.putc(0x02);
                trameStandard=commandePingAx(trameStandard);
                creeTrameAx(trameStandard,trameEnvoie);
                envoieTrameAx12(trameEnvoie, selectionRxTx);
                break;
            case '3':
                //commande read
                trameStandard=commandeReadAx(trameStandard,0x1E,0x02);
                creeTrameAx(trameStandard,trameEnvoie);
                envoieTrameAx12(trameEnvoie, selectionRxTx);
                break;
            case '4':
                //commande reg write
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
        char testswitch=0;
        switch (trameStandard.id){
            case 0:
                trameStandard.nParametres=4;
                trameStandard=commandePingPc(trameStandard);
                creeTramePc(trameStandard,bufferenvoiePc);
                envoieTramePc(bufferenvoiePc);
                break;
            case 6:
                trameStandard=commandeReadPc(trameStandard);
                creeTramePc(trameStandard,bufferenvoiePc);
                envoieTramePc(bufferenvoiePc);
                break;
            case '2':
                
                //code
                break;
        }   
    }
}