//--------------------------------------------------------------------------
//envoie une trame a AX-12A
/*void envoieTrame(){
    selectionRxTx=1;
    wait(0.0000001);
    unsigned int decimalNumber;
    bufferenvoie[5]=ax06.goalposition.x;
    bufferenvoie[2]=bufferreception[3];
    decimalNumber = charToInt(bufferreception[8],bufferreception[9],bufferreception[10]);
    bufferenvoie[6]=decimalNumber;
    bufferenvoie[7]=decimalNumber>>8;
    bufferenvoie [8]=checkSum(bufferenvoie[2],bufferenvoie[3],bufferenvoie[4],
                              bufferenvoie[5],bufferenvoie[6],bufferenvoie[7]);
    for(int b=0;b<sizeof(bufferenvoie);b++){ 
        while(pc.writeable()==0){
        }    
        ax.putc(bufferenvoie[b]);
    }
    wait(0.000030);
    selectionRxTx=0;
}*/
//--------------------------------------------------------------------------
//envoie une trame a AX-12A
/*void envoieTrame2(){
    selectionRxTx=1;
    wait(0.0000001);
    unsigned int decimalNumber;
    bufferenvoie[5]=0x20;
    bufferenvoie[2]=bufferreception[3];
    decimalNumber = charToInt(bufferreception[8],bufferreception[9],bufferreception[10]);
    bufferenvoie[6]=decimalNumber;
    bufferenvoie[7]=decimalNumber>>8;
    bufferenvoie [8]=checkSum(bufferenvoie[2],bufferenvoie[3],bufferenvoie[4],
                              bufferenvoie[5],bufferenvoie[6],bufferenvoie[7]);
    for(int b=0;b<sizeof(bufferenvoie);b++){ 
        while(pc.writeable()==0){
        }    
        ax.putc(bufferenvoie[b]);
    }
    wait(0.00003);
    selectionRxTx=0;
    
}*/
//--------------------------------------------------------------------------
//envoie une trame a AX-12A
/*void envoieTrame3(){
    //pc.putc(0x99);
    selectionRxTx=1;
    wait(0.0000001);
    //bufferenvoie2[5]=0x02;
    //bufferenvoie2[2]=bufferreception[3];
    //decimalNumber = charToInt(bufferreception[8],bufferreception[9],bufferreception[10]);
    bufferenvoie2[5]=0x00;
    bufferenvoie2[6]=0x00;
    bufferenvoie2[7]=0x00;
 
    bufferenvoie2 [8]=checkSum(bufferenvoie2[2],bufferenvoie2[3],bufferenvoie2[4],
                              bufferenvoie2[5],bufferenvoie2[6],bufferenvoie2[7]);
    bufferenvoie2[5]=bufferenvoie2 [8];
    for(int b=0;b<6;b++){ 
        while(pc.writeable()==0){
        }     
        ax.putc(bufferenvoie2[b]);
    }
    wait(0.000025);
    selectionRxTx=0;
}*/
