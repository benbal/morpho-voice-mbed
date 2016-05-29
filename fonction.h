#ifndef DEF_NOMDUFICHIER 
#define DEF_NOMDUFICHIER 

//--------------------------------------------------------------------------
//envoie une trame a AX-12A
void envoieTrameAx12(char bufferenvoie[100]){
    selectionRxTx=1;
    wait(0.0000024);
    char longeurTrame = bufferenvoie[3]+4;
    for(int b=0;b<longeurTrame;b++){ 
        /*while(pc.writeable()==0){
        }*/     
        ax.putc(bufferenvoie[b]);
    }
    wait(0.000030);
    selectionRxTx=0;
}

//--------------------------------------------------------------------------
//envoie une trame a Pc
void envoieTramePc(char bufferenvoie[17]){
    
    
    for(int b=0;b<sizeof(bufferenvoiePc);b++){ 
        /*while(pc.writeable()==0){
        }*/     
        pc.putc(bufferenvoie[b]);
    }
    
}
//--------------------------------------------------------------------------
void fonctionserial (){
//fonction callback enregitre tram pc   
    char octotrecu=pc.getc();
    //pc.putc(octotrecu);
    if (octotrecu==0x24){
        confirme=true;
    }
    if (confirme==true){
        bufferreception[position]=octotrecu;
    }
    if (octotrecu==0x26 && confirme==true){
        //pc.putc(bufferreception[1]);
        position=-1;
        confirme=false;
        fonctionAx(bufferreception);
    }
    position++;
} 

//--------------------------------------------------------------------------
void fonctionSerialAx (){
//fonction callback enregitre tram ax 
   /* pc.putc(lenghttrameax);
    pc.putc(conp);*/
    
    char octotrecu=ax.getc();
    pc.putc(octotrecu);
    if (octotrecu==0xFF){
        pc.putc(0x80);
        //pc.putc(octotrecu);
        confirme2=true;
        lenghttrameax=2;
        
    }
    else if  (confirme2==true && conp==1){
        pc.putc(0x81);
        bufferenvoie3[conp]=octotrecu;
        lenghttrameax+=octotrecu;
        conp++;
    }
    else if (confirme2==true && conp<(lenghttrameax-1)){
        pc.putc(0x82);
        bufferenvoie3[conp]=octotrecu;
        conp++;
    }
    else if(confirme2==true && conp==(lenghttrameax-1)){
       pc.putc(0x83);
       //pc.putc(octotrecu);
       bufferenvoie3[conp]=octotrecu;
       
       confirme2=false;
       conp=0;
       fonctionPc(bufferenvoie3);
    }
    else{
        pc.putc(0x84);
        
        confirme2=false;
        conp=0;
    }
    
} 

//--------------------------------------------------------------------------
unsigned int charToInt( unsigned int decimalNumber1,unsigned int decimalNumber2,unsigned int decimalNumber3){
//tranforme 3 char en unsigned int tel que ex: 150 => 0x313530 => 150
    unsigned int decimalNumber4;
    decimalNumber1= (decimalNumber1-0x30)*100;
    decimalNumber2=(decimalNumber2-0x30)*10;
    decimalNumber3=(decimalNumber3-0x30); 
    //cut eventuel
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
//--------------------------------------------------------------------------
char checkSum2(char stopElement, char element[50]){
//calcul le checksum  
 char somme=0;
/* for(int b=0;b<9;b++){ 
        pc.putc(element[b]);
    }   
 pc.putc(stopElement);*/
for (char i=0;i<stopElement;i++){
    somme+=element[i];
    somme%= 256;
    }
    somme=~somme;
    //pc.putc(somme);
    return (somme);
}
//--------------------------------------------------------------------------
char check(char bufferreception [17]){
//calcul le checksum

    int somme2=0;
    for(int b=0;b<=14;b++){ 
        somme2+=bufferreception[b];
    }   
    char somme=(somme2%128);
    return (somme);
}
/* Contenu de votre fichier .h (autres include, prototypes, define...) */
#endif 