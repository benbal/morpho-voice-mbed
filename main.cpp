#include "mbed.h"

DigitalOut LedV(p21),LedR(p22), Led1(LED1),Led2(LED2),Led3(LED3),Led4(LED4);
DigitalIn BP(p5);
int main () {
    int m = 0;
    bool l = true;
    while(1) {
        if (BP==1){     
                if (l==true){
                    LedV=0,LedR=0,Led1=0,Led2=0,Led3=0,Led4=0;
                    m+=1;
                    if (m==1){
                        LedV=1,Led1=1;
                    }
                    if (m==2){
                        LedR=1,Led2=1;
                    }
                    if (m==3){
                        LedR=1,LedV=1,Led3=1;
                        }
                    if (m>3){
                        Led4=1;
                        m=0;
                    }
                    l = false;
                }  
                wait (0.01);              
        }
        if (BP==0){
            l=true ;
        }
        
   }
}