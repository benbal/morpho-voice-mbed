#include "mbed.h"
#include "Serial.h"
//#include "buffered_serial.h"
DigitalOut LedV(p21),LedR(p22), Led1(LED1),Led2(LED2),Led3(LED3),Led4(LED4);
InterruptIn button(p5);
Serial pc(USBTX, USBRX);
//Buffer pcbuffer(USBTX, USBRX);
unsigned char c [1]={};
 int vitesse=9600;
 bool test[] = {};
  bool b=false;
 void a (){   
    int op=pc.getc();  
    switch (op){
        case '1':
            //pc.putc(op);
            LedV=!LedV;
            break;
        case '2':
            LedR=!LedR;
            break;
        case '3':
            Led1=!Led1;
            break;
        case '4':
            Led2=!Led2;
            break;
        case '5':
            Led3=!Led3;
            break;
        case '6':
            Led4=!Led4;
            break;
    }
 } 
int main() {
     //pc.read(c,1,, &a, 77);
    pc.baud(vitesse);
    pc.attach(&a);
    while(1){
        if (b){
            /*LedV = 1;
            wait(0.05);
            LedV=0;
            LedR=1;
            wait (0.2);
            LedR=0;*/
           //pc.putc(c[1]);
        }
    }
   
}
