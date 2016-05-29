#ifndef DEF_NOMDUFICHIER 
#define DEF_NOMDUFICHIER 

//--------------------------------------------------------------------------
//envoie une trame a AX-12A
void envoieTrameAx12(char bufferenvoie[100],DigitalOut selectionRxTx){
    selectionRxTx=1;
    wait(0.0000024);
    char longeurTrame = bufferenvoie[3]+4;
    for(int b=0;b<longeurTrame;b++){ 
        /*while(pc.writeable()==0){
        }*/   
        ax.putc(bufferenvoie[b]);  
        //ax.putc(bufferenvoie[b]);
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
   /* pc.putc(lenghttrameax);
    pc.putc(conp);*/
    char octotrecu=ax.getc();
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
       fonctionPc(bufferenvoie3);
    }
    else{
        confirme2=false;
        conp=0;
    }
} 
//--------------------------------------------------------------------------
unsigned int charToInt(char donneesAConvertire[], char debutDonnees,char finDonnees){
//tranforme 3 char en unsigned int tel que ex:0x303135303030 => 0150,00
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
    unsigned int goalPosition;
    goalPosition=floor((degrees)/0.29296875);
    if(goalPosition==1024){
        goalPosition--;   
    }
    return (goalPosition);
}
//--------------------------------------------------------------------------
char checkSum2(char debutElement,char finElement, char element[50]){
//calcul le checksum  
 int somme=0; 
for (char i=debutElement;i<finElement;i++){
    pc.putc(element[i]);
    somme+=element[i];
    somme%= 256;
    }
    somme=~somme;
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
#endif 