#include "communication.h"
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
