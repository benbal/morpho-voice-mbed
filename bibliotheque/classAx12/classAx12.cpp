#include "classAx12.h"

    //index des commande ax12A
    //ping
        #define indexCommandePing 0x01;
    //ReadData
        #define indexCommandeReadData 0x02;
    //WriteData
        #define indexCommandeWriteData 0x03;
    //RegWrite
        #define indexCommandeRegWrite 0x04;
    //Action
        #define indexCommandeAction 0x05;
    //Reset
        #define indexCommandeReset 0x06;
    //SyncWrite
        #define indexCommandeSyncWrite 0x83;
//--------------------------------------------------------------------------
 void classAx12::commandePingAx(){
    //config commande ping pour Ax
    instruction=0x01;
    nParametres=0;
}

//--------------------------------------------------------------------------
void classAx12::commandeReadAx(char adresseDebut,char adresseLongeur){
    //config commande read pour Ax
    instruction=indexCommandeReadData;
    parametres[0]=adresseDebut;
    parametres[1]=adresseLongeur;
    nParametres=2;
}
//--------------------------------------------------------------------------
void classAx12::commandeRegWriteAx(char adresseDebut){
    //config commande reg write pour Ax
    //a revoir
    unsigned int decimalNumber=0;
    instruction=indexCommandeRegWrite;
    decimalNumber = charToInt(parametres,0,3);
    decimalNumber = degreToLong(decimalNumber);
    parametres[0]=adresseDebut;
    parametres[1]=decimalNumber;
    parametres[2]=decimalNumber>>8;
    nParametres=3;
}
//--------------------------------------------------------------------------
void classAx12::commandeWriteAx(char adresseDebut){
    //config commande write pour Ax
    //a revoir
    unsigned int decimalNumber=0;
    instruction=indexCommandeWriteData;
    decimalNumber = charToInt(parametres,0,3);
    decimalNumber = degreToLong(decimalNumber);
    parametres[0]=adresseDebut;
    parametres[1]=decimalNumber;
    parametres[2]=decimalNumber>>8;
    nParametres=3;
}
//--------------------------------------------------------------------------
void classAx12::commandeActionAx(char adresseDebut){
    //config commande ping pour Ax
    id=adresseDebut;
    instruction=indexCommandeAction;
    nParametres=0;
}
//--------------------------------------------------------------------------
void classAx12::commandeSyncWriteAx(){
    //config commande sync write pour Ax
    unsigned int decimalNumber=0;
    //parametre
    instruction=indexCommandeSyncWrite;
    parametres[0]=0x1E;
    parametres[1]=0x02;
    decimalNumber = charToInt(parametres,0,3);
    decimalNumber = degreToLong(decimalNumber);
    
    if(nParametres>0){
    parametres[2]=id;   
    parametres[3]=decimalNumber;
    parametres[4]=decimalNumber>>8;
    nParametres=5;
    }
    else{
        parametres[nParametres]=id;   
        parametres[nParametres+1]=decimalNumber;
        parametres[nParametres+2]=decimalNumber>>8;
        nParametres+=3; 
    }
    id=0xFE; //broadcasting
}
//--------------------------------------------------------------------------
void classAx12::commandePingPc(){
    //config commande ping pour Ax
    nParametres=6;
    groupe=indexCommandePing;
    instruction=0x00;
}

//--------------------------------------------------------------------------
void classAx12::commandeErrorPc(){
    //config commande ping pour Ax
    nParametres=6;
    groupe=indexCommandePing;
    if(parametres[0]<0x09){
        parametres[4]=0x09;
        parametres[5]=parametres[0];
    }
    else{
        parametres[4]=parametres[0]>>4;
        parametres[5]=0x09;
    }
    parametres[0]=0x09;
    parametres[1]=0x09;
    parametres[2]=0x09;
    parametres[3]=0x09;
    instruction=0x00;
}
//--------------------------------------------------------------------------
void classAx12::commandeReadPc(){
    //config commande read pour Ax
    char donneesAConvertire[6];
    nParametres=6;
    unsigned int degrees=parametres[2]<<8;
    degrees+=parametres[1];
    intToChar( donneesAConvertire,longToDegre(degrees));
    for(char x=0;x<nParametres;x++){
        parametres[x]=donneesAConvertire[x];
    }
    instruction=indexCommandeReadData;
}
//--------------------------------------------------------------------------
unsigned char classAx12::commandeMouvementMoteur(){
//config commande mouvement pour le moteur
    unsigned char mouvementMoteur;
    mouvementMoteur=intToShort(charToInt(parametres,0,3));
    return (mouvementMoteur);
}
//--------------------------------------------------------------------------
void classAx12::creeTrameAx(char trameEnvoie[]){
    //cree la trame Ax
    trameEnvoie[0]=0xFF;
    trameEnvoie[1]=0xFF;
    trameEnvoie[2]=id;
    trameEnvoie[3]=nParametres+2;
    trameEnvoie[4]=instruction;
    if(nParametres>0){
        for(char x=0;x<nParametres;x++){
            trameEnvoie[5+x]=parametres[x];    
        }
    }
    trameEnvoie[nParametres+5]=checkSum2(2,nParametres+5,trameEnvoie); 
}
//--------------------------------------------------------------------------
void classAx12::creeTramePc(char trameEnvoie[]){
    //cree la trame Pc avec une trame standard 
    trameEnvoie[0]=0x24;
    trameEnvoie[1]=groupe;
    trameEnvoie[2]=0x3A;
    trameEnvoie[3]=id;
    trameEnvoie[4]=0x3A;
    trameEnvoie[5]=instruction;
    trameEnvoie[6]=0x3A;
    for(char x=0;x<nParametres-2;x++){
            trameEnvoie[7+x]=parametres[x]+0x30;
    }
    trameEnvoie[11]=0x2E;
    trameEnvoie[12]=parametres[nParametres-2]+0x30;
    trameEnvoie[13]=parametres[nParametres-1]+0x30;
    trameEnvoie[14]=0x3A;
    trameEnvoie[15]=check(trameEnvoie);
    trameEnvoie[16]=0x26;   
}
//--------------------------------------------------------------------------
void classAx12::tramePcToTrameStandard(char bufferreception[]){
    //memorice la trame pc sous une trame standard
    groupe=bufferreception[1];
    id=bufferreception[3]-0x30;
    instruction=bufferreception[5];
    parametres[0]=bufferreception[7];
    parametres[1]=bufferreception[8];
    parametres[2]=bufferreception[9];
    parametres[3]=bufferreception[10];
    parametres[4]=bufferreception[12];
    parametres[5]=bufferreception[13];
    controleErreur=bufferreception[15];    
}
//--------------------------------------------------------------------------
void classAx12::trameAxToTrameStandard(char bufferenvoie[]){
    //memorice la trame ax sous une trame standard
    groupe=0;
    id=bufferenvoie[0];
    nParametres=bufferenvoie[1]-1;
    for(char x=0;x<nParametres;x++){
        parametres[x]=bufferenvoie[2+x];
    }
    controleErreur=bufferenvoie[nParametres+1];
}
//--------------------------------------------------------------------------
