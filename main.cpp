#include "mbed.h"
#include "Serial.h"
//#include "buffered_serial.h"
DigitalOut LedV(p21),LedR(p22),Led1(LED1)/*,Led2(LED2),Led3(LED3),Led4(LED4)*/;
//InterruptIn button(p5);
Serial pc(p9,p10 );//USBRX
//Buffer pcbuffer(USBTX, USBRX);
//unsigned char c [1]={};
char buffer[9]={0xFF,0xFF,0x06,0x05,0x03,0x1E,0x00,0x02,0xD1};
int vitesse=1000000;
char id=6;
short lenght=5;
short intruction=6;
int m=0;
 //short parametre1=;
 //short parametre2=;
 
 //int test[] = { 1 , 2 ,3  ,4  , 5 };
 bool b=false;
/*void a (){
    //pc.putc(pc.getc());
    short op=pc.getc();
    //pc.putc(op);
    //pc.printf("Ma variable=%.hu  \\ \n\r ",op);

} */
int main() {
     //pc.read(c,1,, &a, 77);
    id = (short) id;
    pc.baud(vitesse);
    //pc.attach(&a);
    while(1){
    for(int b=0;b<sizeof(buffer);b++){ 
        /*while(pc.writeable()==0){
        }     */
        pc.putc(buffer[b]);
    }
    wait(2);
    }
}
