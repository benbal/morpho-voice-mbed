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
//--------------------------------------------------------------------------
void communication(){
//reglage 
//serial
    //serial canal 0:pc
        //reglage vitesse serial
        pc.baud(115200);
    //serial canal 1:ax-12A
    //reglage vitesse serial
        //reglage vitesse serial
        ax.baud(9600);
    //serial canal 2:moteur poumon
        Serial mp(p28,p27 );
        //reglage vitesse serial
        mp.baud(9600);
    //mode serial simplifie switches 2 et 4 a off les autre sur on
//Sortie Digital
    //selection sortie
        selectionRxTx=0;
        selectionSyRen=0;
    //Voyant
        led1=0;
        led2=0; 
//time
    //temps entre deux mesure de pression
    
    //reglage fonction de call back
        //communication
        pc.attach(&fonctionserialPc);
        ax.attach(&fonctionSerialAx);
        //fin de capteur course
        finDeCourse.rise(&fonctionFinDeCourse);
        finDeCourse2.rise(&fonctionFinDeCourse);

    
}
//--------------------------------------------------------------------------
void envoieTrameAx12(char bufferenvoie[100]){
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
void envoieTramePc(Serial pc, char bufferenvoie[17]){
    //envoie une trame a Pc
    for(int b=0;b<17/*sizeof(bufferenvoie)*/;b++){ 
        /*while(pc.writeable()==0){
        }*/     
        pc.putc(bufferenvoie[b]);
    }
}
//--------------------------------------------------------------------------
void envoieMoteur(char mouvement){
//controle moteur
    selectionRxTx=1;
    selectionSyRen=1;
    wait(0.001);
    mp.putc(mouvement);
    wait(0.002);
    selectionSyRen=0;
    selectionRxTx=0;
}
//--------------------------------------------------------------------------
void fonctionserialpc (char bufferreception[], classAx12 trameSyncWrite){
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
        position=0;
        confirme=false;
        fonctionAx(bufferreception, trameSyncWrite);
    }
    position++;
}
//--------------------------------------------------------------------------
void fonctionSerialAx (){
//fonction callback enregitre tram ax 
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
void fonctionAx(char bufferenvoie[],classAx12 trameSyncWrite){
//selection fonction pc to ax
    //if (check(bufferreception)==bufferreception[15]){ 
    //verification checksun
        led1 = !led1;
        //mise en mise en forme de la trame pc
        classAx12 trameStandard;
        trameStandard.tramePcToTrameStandard(bufferenvoie);
        char adresseDebut;
        char trameEnvoie[50];
        if(trameStandard.groupe=='0'){
        //commande ax-12
            switch (trameStandard.instruction){
                case '0':
                    //commande position
                    adresseDebut=indexAdresseGoalPosition;
                    trameStandard.commandeWriteAx(adresseDebut);
                    trameStandard.creeTrameAx(trameEnvoie);
                    envoieTrameAx12(trameEnvoie);
                    break;
                case '1':
                    //commande vitesse
                    adresseDebut=indexAdresseMovingSpeed;
                    trameStandard.commandeWriteAx(adresseDebut);
                    trameStandard.creeTrameAx(trameEnvoie);
                    envoieTrameAx12(trameEnvoie);
                    break;
                case '2':
                    //commande ping
                    trameStandard.commandePingAx();
                    trameStandard.creeTrameAx(trameEnvoie);
                    envoieTrameAx12(trameEnvoie);
                    break;
                case '3':
                    //commande reg write position
                    adresseDebut=indexAdresseGoalPosition;
                    trameStandard.commandeRegWriteAx(adresseDebut);
                    trameStandard.creeTrameAx(trameEnvoie);
                    envoieTrameAx12(trameEnvoie);
                    break;
                case '4':
                    //commande action
                    trameStandard.commandeActionAx(0xFE);
                    trameStandard.creeTrameAx(trameEnvoie);
                    envoieTrameAx12(trameEnvoie);
                    break;
                case '5':
                    //commande reponse
                    trameStandard.instruction=indexCommandeWriteData;
                    trameStandard.parametres[0]=0x10;
                    trameStandard.parametres[1]=0x02;
                    trameStandard.nParametres=2;
                    trameStandard.creeTrameAx(trameEnvoie);
                    envoieTrameAx12(trameEnvoie);
                    break;
                case '6':
                    //commande SyncWrite
                    trameStandard.commandeSyncWriteAx();
                    trameSyncWrite=trameStandard;
                    break;
                case '7':
                    //commande action SyncWrite
                    trameSyncWrite.creeTrameAx(trameEnvoie);
                    envoieTrameAx12(trameEnvoie);
                    break;
            }
        }
        //
        else if(trameStandard.groupe=='1'){
        //commande pour pour le moteur poumon
            switch (trameStandard.instruction){
            //commande vitesse et direction
                unsigned char mouvement;
                case '0':
                //commande marche avant
                    mouvement = 127+trameStandard.commandeMouvementMoteur();   
                    envoieMoteur(mouvement);
                    
                    break;
                case '1':
                //commande marche arriere
                    mouvement = 127-trameStandard.commandeMouvementMoteur();   
                    envoieMoteur(mouvement);
                    break;
            }
        }
        else if(trameStandard.groupe=='2'){
        //commande pour ensemble des capteur ax-12 compris
            switch (trameStandard.instruction){
                case '0':
                        //commande read position ax-12
                        trameStandard.commandeReadAx(0x1E,0x02);
                        trameStandard.creeTrameAx(trameEnvoie);
                        envoieTrameAx12(trameEnvoie);
                        break;
                case '1':
                        //commande read vitesse ax-12
                        trameStandard.commandeReadAx(0x26,0x02);
                        trameStandard.creeTrameAx(trameEnvoie);
                        envoieTrameAx12(trameEnvoie);
                        break;
                case '2':
                        //commande read capteur de pression
                        /*trameStandard=commandePingPc(trameStandard);
                        creeTramePc(trameStandard,trameEnvoie);
                        //test45=moyenne;
                        test45=15;
                        trameEnvoie[8];
                        envoieTramePc(trameEnvoie);*/
                        
                       break;
            }
        }
        else{
        //erreur a faire
        }        
    //}
}
//--------------------------------------------------------------------------
/*void fonctionPc(char test[]){
//selection fonction ax to pc
    if (checkSum2(0,test[1]+1,test)==test[test[1]+1]){ 
    //verification checksum
        classAx12 trameStandard;
        trameStandard.trameAxToTrameStandard(test);
        char trameEnvoie[50];
        if(trameStandard.parametres[0]==0x00){
            if (trameStandard.nParametres==1){
                trameStandard.commandePingPc();
                trameStandard.creeTramePc(trameEnvoie);
                envoieTramePc(pc,trameEnvoie);
            }
            else{
                trameStandard.commandeReadPc();
                trameStandard.creeTramePc(trameEnvoie);
                envoieTramePc(pc,trameEnvoie);
            }
        }
        else{
            trameStandard.commandeErrorPc();
            trameStandard.creeTramePc(trameEnvoie);
            envoieTramePc(pc,trameEnvoie);
        }   
    }
}*/
//--------------------------------------------------------------------------
void fonctionFinDeCourse (){
//fonction callback fin de course 
     envoieMoteur(0x7f);//stop = 0x7f= 127
}
