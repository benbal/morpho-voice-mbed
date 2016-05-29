//--------------------------------------------------------------------------
void fonctionAx(char bufferenvoie[]){
//selection fonction
    if (check(bufferreception)==bufferreception[15]){ 
        switch (bufferenvoie[5]){
            case '0':
                bufferenvoie[5]=memoireAx06.goalPosition.adresse;
                commandeWriteData(bufferenvoie);
                envoieTrameAx12(bufferenvoie, selectionRxTx);
                break;
            case '1':
                bufferenvoie[5]=0x20;
                commandeWriteData(bufferenvoie);
                envoieTrameAx12(bufferenvoie, selectionRxTx);
                break;
            case '2':
                //pc.putc(0x03);
                envoieTrameAx12(bufferenvoie2, selectionRxTx);
                //envoieTrame3();
                //code
                break;
        }
          
    }
}
//--------------------------------------------------------------------------
void fonctionPc(char test[]){
//selection fonction
    if (checkSum2(test[1]+1,test)==test[3]){
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
 
    bufferenvoie2 [8]=checkSum(bufferenvoie2[2],bufferenvoie2[3],bufferenvoie2[4],
                              bufferenvoie2[5],bufferenvoie2[6],bufferenvoie2[7]);
    bufferenvoie2[5]=bufferenvoie2 [8];
                envoieTrameAx12(bufferenvoie2, selectionRxTx);
                //envoieTrame3();
                //code
                break;
        }
          
    }
}