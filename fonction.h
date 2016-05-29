#ifndef DEF_NOMDUFICHIER 
#define DEF_NOMDUFICHIER 
//--------------------------------------------------------------------------
void envoieTrameAx12(char bufferenvoie[100],DigitalOut selectionRxTx){
    //envoie une trame a AX-12A
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
void envoieTramePc(char bufferenvoie[17]){
    //envoie une trame a Pc
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
    if (octotrecu==0x24){
        bufferreception[position]=octotrecu;
        confirme=true;
    }
    if (confirme==true){
        bufferreception[position]=octotrecu;
    }
    if (octotrecu==0x26 && confirme==true){
        position=-1;
        confirme=false;
        fonctionAx(bufferreception);
    }
    position++;
} 

//--------------------------------------------------------------------------
void fonctionSerialAx (){
//fonction callback enregitre tram ax 
    pc.putc(0x80);
    char octotrecu=ax.getc();
    pc.putc(octotrecu);
    if (octotrecu==0xFF){
        confirme2=true;
        lenghttrameax=2;
    }
    else if  (confirme2==true && conp==1){
        bufferenvoie3[conp]=octotrecu;
        lenghttrameax+=octotrecu;
        conp++;
    }
    else if (confirme2==true && conp<(lenghttrameax-1)){
        bufferenvoie3[conp]=octotrecu;
        conp++;
    }
    else if(confirme2==true && conp==(lenghttrameax-1)){
       bufferenvoie3[conp]=octotrecu;
       confirme2=false;
       conp=0;
       pc.putc(0x81);
       fonctionPc(bufferenvoie3);
    }
    else{
        confirme2=false;
        conp=0;
    }
} 
//--------------------------------------------------------------------------
unsigned int charToInt(char donneesAConvertire[], char debutDonnees,char finDonnees){
//tranforme 3 char en unsigned int tel que ex:0x30,0x31,0x35,0x30,0x30,0x30=> 0150,00
    unsigned int decimalNumber=0,decimalTotal=0,multiplicateur=1;
    int y=0;
    for (int x=finDonnees;x>=debutDonnees;x--){
        decimalNumber=(donneesAConvertire[finDonnees-y]-0x30)*multiplicateur;
        decimalTotal+=decimalNumber;
        multiplicateur*=10;    
        y++;
    }
    return (decimalTotal);
}
//--------------------------------------------------------------------------
unsigned int degreToLong(unsigned int degrees){
    //transforme un entier en degre 0->300° en long de 0->1024
    unsigned int longDegrees;
    longDegrees=floor((degrees)/0.29296875);
    if(longDegrees==1024){
        longDegrees--;   
    }
    return (longDegrees);
}
//--------------------------------------------------------------------------
unsigned int longToDegre(unsigned int longDegrees){
    //transforme un long de 0->1024 entier en degre 0->300°  
    unsigned int degrees;
    degrees=floor((longDegrees)*0.29296875);
    return (degrees);
}
//--------------------------------------------------------------------------
void intToChar(char donneesAConvertire[],unsigned int degrees){
    //tranforme 3 char en unsigned int tel que ex:0x303135303030 => 0150,00
    //a mettre aux propre
    float us1=0,us2=0,us3=0,us4=0;
    float ux1=0,ux2=0,ux3=0;
    us1=degrees/1000;
    ux1=us1*1000;
    us2=floor((degrees-ux1)/100);
    ux2=us2*100;
    us3=floor((degrees-(ux1+ux2))/10);
    ux3=us3*10;
    us4=floor((degrees-(ux1+ux2+ux3)));
    donneesAConvertire[0]=us1;
    donneesAConvertire[1]=us2;
    donneesAConvertire[2]=us3;
    donneesAConvertire[3]=us4;
    donneesAConvertire[4]=0;
    donneesAConvertire[5]=0;
}
//--------------------------------------------------------------------------
char checkSum2(char debutElement,char finElement, char element[50]){
//calcul le checksum trame ax
 int somme=0;
for (char i=debutElement;i<finElement;i++){
    somme+=element[i];
    somme%= 256;
    }
    somme=~somme;
    return (somme);
}
//--------------------------------------------------------------------------
char check(char bufferreception [17]){
//calcul le checksum trame pc
    int somme2=0;
    for(int b=0;b<=14;b++){ 
        somme2+=bufferreception[b];
    }   
    char somme=(somme2%128);
    return (somme);
}
#endif 