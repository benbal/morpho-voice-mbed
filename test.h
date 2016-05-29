
void les10PremieresValeurs(){
    for(poiteurpression=0;poiteurpression<10;poiteurpression++){
        lectureEtMesure();
        tableauPressions[poiteurpression]= lectureEtMesure();
    }
}
void tempsMort(){
       float somme;
       unsigned char x;
       tableauPressions[poiteurpression%10]= lectureEtMesure();
       for(x=0;x<10;x++){
           somme = tableauPressions[x] + somme;
        }
       moyenne = somme/10;
       somme=0;
       poiteurpression++;
}

float lectureEtMesure(){
    //prise de mesure 
    unsigned int pressionNumerique;
    float TensionP20, V,PressionEnHpa;
    pressionNumerique = SignalDePressionAmplifie.read_u16();
    V = pressionNumerique;
    TensionP20 = (V/16) * COEFF;
    PressionEnHpa= TensionP20*COEFF2;
    return PressionEnHpa;
}