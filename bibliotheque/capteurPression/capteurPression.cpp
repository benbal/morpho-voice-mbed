#include "capteurPression.h"
//--------------------------------------------------------------------------
void les10PremieresValeurs(AnalogIn SignalDePressionAmplifie){
//set 10 tableau de presion
    for(poiteurpression=0;poiteurpression<10;poiteurpression++){
        tableauPressions[poiteurpression]= lectureEtMesure(SignalDePressionAmplifie);
    }
}
//--------------------------------------------------------------------------
float lectureEtMesure(AnalogIn SignalDePressionAmplifie){
    //prise de mesure 
    float COEFF= 0.0008056640,COEFF2= 32.02481923;
    unsigned int pressionNumerique;
    float TensionP20, V,PressionEnHpa;
    pressionNumerique = SignalDePressionAmplifie.read_u16();
    V = pressionNumerique;
    TensionP20 = (V/16) * COEFF;
    PressionEnHpa= TensionP20*COEFF2;
    return PressionEnHpa;
}
//--------------------------------------------------------------------------
void tempsMort(AnalogIn SignalDePressionAmplifie){
       float somme;
       unsigned char x;
       tableauPressions[poiteurpression%10]= lectureEtMesure(SignalDePressionAmplifie);
       for(x=0;x<10;x++){
           somme = tableauPressions[x] + somme;
        }
       moyenne = somme/10;
       somme=0;
       poiteurpression++;
}