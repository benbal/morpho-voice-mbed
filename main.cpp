#include "mbed.h"
DigitalOut LedV(p21),LedR(p22), Led1(LED1),Led2(LED2),Led3(LED3),Led4(LED4);
InterruptIn button(p5);
int m = 0,h=1;
bool l = true;
void test(){
if (l==true){
    m+=1;
    if (m==1){
        h=2;
    }
    else {
        h=1;
        m=0;
    }
    l = false;
}  
wait(0.2);
}
int main () {
    button.rise(&test);
     while(1) {
        l = true ;    
        LedV = 1;
        wait(0.05*h);
        LedV=0;
        LedR=1;
        wait (0.2*h);
        LedR=0;
   }
}