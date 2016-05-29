//--------------------------------------------------------------------------
//envoie une trame a AX-12A
void envoieTrame(){
    unsigned int decimalNumber;
    decimalNumber = charToInt(bufferreception[3],bufferreception[4],bufferreception[5]);
    bufferenvoie[6]=decimalNumber;
    bufferenvoie[7]=decimalNumber>>8;
    bufferenvoie [8]=checkSum(bufferenvoie[2],bufferenvoie[3],bufferenvoie[4],
                              bufferenvoie[5],bufferenvoie[6],bufferenvoie[7]);
    for(int b=0;b<sizeof(bufferenvoie);b++){ 
        /*while(pc.writeable()==0){
        }     */
        ax.putc(bufferenvoie[b]);
    }
}


//--------------------------------------------------------------------------
void fonctionserial (){
//fonction callback enregitre tram   
    char octotrecu=pc.getc();
    if (octotrecu==0x24){
        confirme=true;
    }
    if (confirme==true){
        bufferreception[position]=octotrecu;
    }
    if (position==5){
        pc.putc(bufferreception[1]);
        position=-1;
        confirme=false;
        selection(bufferreception);
    }
    position++;
} 
//--------------------------------------------------------------------------
unsigned int charToInt( unsigned int decimalNumber1,unsigned int decimalNumber2,unsigned int decimalNumber3){
//tranforme 3 char en unsigned int tel que ex: 150 => 0x313530 => 150
    unsigned int decimalNumber4;
    decimalNumber1= (decimalNumber1-0x30)*100;
    decimalNumber2=(decimalNumber2-0x30)*10;
    decimalNumber3=(decimalNumber3-0x30);
    decimalNumber4=floor((decimalNumber1+decimalNumber2+decimalNumber3)/0.29296875);
    if(decimalNumber4==1024){
        decimalNumber4--;   
    }
    return (decimalNumber4);
}
//--------------------------------------------------------------------------
char checkSum(char element1,char element2,char element3,char element4,char element5,char element6){
//calcul le checksum      
    char somme=~((element1+element2+element3+element4+element5+element6)%256);
    return (somme);
}

