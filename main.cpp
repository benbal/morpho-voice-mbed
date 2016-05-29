#include "mbed.h"
DigitalOut LedV(p21),LedR(p22), Led1(LED1),Led2(LED2),Led3(LED3),Led4(LED4);
InterruptIn button(p5);
Serial pc(USBTX, USBRX);
int m = 0;
char  b=255;
//string mastring="Ma variable=";
void test(){
m=0;
}
int main () {
    button.rise(&test);
    b=~b;
     while(1) {
        pc.printf("Ma variable=%.i  \\ \n\r ",b);
        wait (2);
        
   }
}