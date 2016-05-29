#include "mbed.h"
DigitalOut Led1(p21),Led2(p22); // work ex1
DigitalIn BP(p20);
int main () {
    int h = 2;
    while(1) {
      
        Led1 = 1;
        wait(0.05*h);
        Led1=0;
        Led2=1;
        wait (0.2*h);
        Led2=0;
    }
}