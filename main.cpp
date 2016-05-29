#include "mbed.h"
#include "Serial.h"
//#include "buffered_serial.h"
DigitalOut LedV(p21),LedR(p22),Led1(LED1)/*,Led2(LED2),Led3(LED3),Led4(LED4)*/;
//InterruptIn button(p5);
Serial pc(USBTX, USBRX);
//Buffer pcbuffer(USBTX, USBRX);
//unsigned char c [1]={};
 int vitesse=9600;
 //int test[] = { 1 , 2 ,3  ,4  , 5 };
 bool b=false;
void a (){
    //pc.putc(pc.getc());
    int op=pc.getc();
    if(op==77){
        b=true;
        Led1=1;
        }
    if(op==65){
        b=false;
        Led1=0;
        }
} 
int main() {
     //pc.read(c,1,, &a, 77);
    pc.baud(vitesse);
    pc.attach(&a);
    while(1){
        if (b){
            LedV = 1;
            wait(0.05);
            LedV=0;
            LedR=1;
            wait (0.2);
            LedR=0;
           //pc.putc(c[1]);
        }
    }
}
