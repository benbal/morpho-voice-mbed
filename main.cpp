#include "mbed.h"
#include "Serial.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "registrefonction.h"
#include "defautvariable.h"
#include "variableGlobal.h"
#include "reglage.h"
#include "fonction.h"
#include "commandeAx.h"
#include "selectionfonction.h"
int main() {
ax.baud(vitesseAx);
pc.baud(vitessePc);
pc.attach(&fonctionserial);
ax.attach(&fonctionSerialAx);
selectionRxTx=0;
/*char szNumbers[] = "B";
  char * pEnd;
  long int li1, li2, li3, li4;
  li1=strtol (szNumbers,&pEnd,16);
  int i ;
  i=int (szNumbers);
  
  printf ("The decimal equivalents are: %ld %i\n",li1 ,i);*/
  
    while(1){
        
   
    }
    
}
//$A00;