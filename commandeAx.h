//--------------------------------------------------------------------------
void commandeWriteData(char bufferenvoie[]){
    unsigned int decimalNumber=0;
    bufferenvoie[2]=bufferreception[3];
    decimalNumber = charToInt(bufferreception[8],bufferreception[9],bufferreception[10]);
    bufferenvoie[6]=decimalNumber;
    bufferenvoie[7]=decimalNumber>>8;
    bufferenvoie [8]=checkSum2(bufferenvoie[3]+1,bufferenvoie);
}
//--------------------------------------------------------------------------
void commandeReadData(char bufferenvoie[]){
    unsigned int decimalNumber=0;
    bufferenvoie[2]=bufferreception[3];
    decimalNumber = charToInt(bufferreception[8],bufferreception[9],bufferreception[10]);
    bufferenvoie[6]=decimalNumber;
    bufferenvoie[7]=decimalNumber>>8;
    bufferenvoie [8]=checkSum2(bufferenvoie[3]+1,bufferenvoie);
}
//--------------------------------------------------------------------------
void commandePing(char bufferenvoie[]){
    bufferenvoie2[5]=0x00;
    bufferenvoie2[6]=0x00;
    bufferenvoie2[7]=0x00;
    bufferenvoie2 [8]=checkSum(bufferenvoie2[2],bufferenvoie2[3],bufferenvoie2[4],
                              bufferenvoie2[5],bufferenvoie2[6],bufferenvoie2[7]);
    bufferenvoie2[5]=bufferenvoie2 [8];
}
//--------------------------------------------------------------------------