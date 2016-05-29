//--------------------------------------------------------------------------
void fonctionAx(char bufferenvoie[]){
//selection fonction pc to ax
    if (check(bufferreception)==bufferreception[15]){ 
        trame trameStandard;
        trameStandard=tramePcToTrameStandard(bufferenvoie);
        char adresseDebut;
        char trameEnvoie[50];
        switch (trameStandard.instruction){
            case '0':
                //commande position
                adresseDebut=indexAdresseGoalPosition;
                trameStandard=commandeWriteAx(trameStandard,adresseDebut);
                creeTrame(trameStandard,trameEnvoie);
                envoieTrameAx12(trameEnvoie, selectionRxTx);
                break;
            case '1':
                //commande vitesse
                adresseDebut=indexAdresseMovingSpeed;
                trameStandard=commandeWriteAx(trameStandard,adresseDebut);
                creeTrame(trameStandard,trameEnvoie);
                envoieTrameAx12(trameEnvoie, selectionRxTx);
                break;
            case '2':
                //commande ping
                pc.putc(0x42);
                trameStandard=commandePingAx(trameStandard);
                creeTrame(trameStandard,trameEnvoie);
                envoieTrameAx12(trameEnvoie, selectionRxTx);
                break;
            case '3':
                //commande ping
                //commandeReadAx(trameStandard);
                creeTrame(trameStandard,trameEnvoie);
                envoieTrameAx12(bufferenvoie, selectionRxTx);
                break;
            case '4':
                //commande reg write
                adresseDebut=indexAdresseGoalPosition;
                trameStandard=commandeRegWriteAx(trameStandard,adresseDebut);
                creeTrame(trameStandard,trameEnvoie);
                envoieTrameAx12(trameEnvoie, selectionRxTx);
                break;
            case '5':
                //commande action
                trameStandard=commandeActionAx(trameStandard);
                creeTrame(trameStandard,trameEnvoie);
                envoieTrameAx12(trameEnvoie, selectionRxTx);
                break;
        }         
    }
}
//--------------------------------------------------------------------------
void fonctionPc(char test[]){
//selection fonction ax to pc
pc.putc(test[3]);

    if (checkSum2(0,test[1]+1,test)==test[3]){ 
        trame trameStandard;
        trameStandard=trameAxToTrameStandard(bufferenvoie);
        switch (test[5]){
            case 0:
                envoieTramePc(bufferenvoiePc);
                //code
                break;
            case '1':
               
                //code
                //envoieTrame2();
                break;
            case '2':
                //pc.putc(0x03);
                bufferenvoie2[5]=0x00;
    bufferenvoie2[6]=0x00;
    bufferenvoie2[7]=0x00;
 
    //bufferenvoie2 [8]=checkSum(bufferenvoie2[2],bufferenvoie2[3],bufferenvoie2[4],
     //                         bufferenvoie2[5],bufferenvoie2[6],bufferenvoie2[7]);
    bufferenvoie2[5]=bufferenvoie2 [8];
                envoieTrameAx12(bufferenvoie2, selectionRxTx);
                //envoieTrame3();
                //code
                break;
        }
          
    }
}