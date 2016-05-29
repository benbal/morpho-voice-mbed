//--------------------------------------------------------------------------
void fonctionAx(char test[]){
//selection fonction
unsigned int decimalNumber=0;
    if (check(bufferreception)==bufferreception[15]){
                   
        switch (test[5]){
            case '0':
                //pc.putc(0x00);
                
    bufferenvoie[5]=memoireAx06.goalPosition.adresse;
    bufferenvoie[2]=bufferreception[3];
    decimalNumber = charToInt(bufferreception[8],bufferreception[9],bufferreception[10]);
    bufferenvoie[6]=decimalNumber;
    bufferenvoie[7]=decimalNumber>>8;
    bufferenvoie [8]=checkSum(bufferenvoie[2],bufferenvoie[3],bufferenvoie[4],
                              bufferenvoie[5],bufferenvoie[6],bufferenvoie[7]);
                envoieTrameAx12(bufferenvoie);
                //code
                break;
            case '1':
                //pc.putc(0x01);
                
    bufferenvoie[5]=0x20;
    bufferenvoie[2]=bufferreception[3];
    decimalNumber = charToInt(bufferreception[8],bufferreception[9],bufferreception[10]);
    bufferenvoie[6]=decimalNumber;
    bufferenvoie[7]=decimalNumber>>8;
    bufferenvoie [8]=checkSum(bufferenvoie[2],bufferenvoie[3],bufferenvoie[4],
                              bufferenvoie[5],bufferenvoie[6],bufferenvoie[7]);
                envoieTrameAx12(bufferenvoie);
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
                envoieTrameAx12(bufferenvoie2);
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
                envoieTrameAx12(bufferenvoie2);
                //envoieTrame3();
                //code
                break;
        }
          
    }
}