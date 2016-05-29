#include "mbed.h"

DigitalOut LedV(p21),LedR(p22);
DigitalIn button(p5);
int m = 0,h=1;
bool l = true;
int main () {
    while(1) {
        if (button==0){
           h=2;
        } 
        else {
           h=1; 
        }
        LedV = 1;
        wait(0.125*h);
        LedV=0;
        LedR=1;
        wait (0.125*h);
        LedR=0;
        }
   }