#include "mbed.h"
#include "Serial.h"
char bufferrecption[9]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
int position=0;
bool confirme =false;
char buffer[9]={0xFF,0xFF,0x06,0x05,0x03,0x1E,0x00,0x00,0x00};
int vitessepc=9600;
int vitesseax=1000000;
char id= 6;
short lenght=5;
short intruction=6;
int m=0;
 //short parametre1=;
 //short parametre2=;
 
 //int test[] = { 1 , 2 ,3  ,4  , 5 };
 bool b=false;
//serial
    //serial canal 0:pc
        Serial pc(USBTX,USBRX);
    //serial canal 1:ax-12A
        Serial ax(p9,p10 );
//
void positionvoulue(char test[9]){
  //pc.putc(0x44);
  buffer[6]=test[3];
  buffer[7]=test[2];
  long somme=buffer[2]+buffer[3]+buffer[4]+buffer[5]+buffer[6]+buffer[7];
    char somme2=~(somme%256);
    buffer [8]=somme2;
    for(int b=0;b<sizeof(buffer);b++){ 
        while(pc.writeable()==0){
        }     
        ax.putc(buffer[b]);
     }
}
 
 
 
 void selection(char test[9]){
    if(test[1]==0x41){
        positionvoulue(test);
    }
}
void fonctionserial (){
    //pc.putc(0x42);
    char octotrecu=pc.getc();
    if (octotrecu==0x24){
        confirme=true;
    }
    if (confirme==true){
        bufferrecption[position]=octotrecu;
    }
    if (octotrecu==0x3B){
        pc.putc(bufferrecption[1]);
        position=-1;
        confirme=false;
        selection(bufferrecption);
       
    }
    position++;
} 
int main() {
     //pc.read(c,1,, &a, 77);
    ax.baud(vitesseax);
    pc.baud(vitessepc);
    pc.attach(&fonctionserial);
    
    while(1){
   
    }
    
}
//$A00;