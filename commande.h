//moteur 
//--------------------------------------------------------------------------
void commandeMouvementMoteur(trame trameStandard){
//config commande mouvement pour le moteur
    //mouvementMoteur=intToShort(charToInt(trameStandard.parametres,0,3));
    unsigned char n=0;
    nMax=6;
    if(trameStandard.parametres[0]==0x31){
        n=1;
        //2D = "-"
        possitionMoteur[4]=0x2D;
        vitesseMoteur[3]=0x2D;
        nMax=7;
    }
    for(unsigned char tour=n; tour<8;tour++){
        possitionMoteur[tour+4]=trameStandard.parametres[tour];
        vitesseMoteur[tour+3]=trameStandard.parametres[tour];
    }
    envoieMoteur(possitionMoteur,(nMax));
    envoieMoteur(vitesseMoteur,(nMax+1));
}
 //--------------------------------------------------------------------------
void commandeFinDeCourse (){
//fonction callback fin de course 
     trame trameStandard;
     for(char i=0; i<4;i++){
         trameStandard.parametres[i]=0x30;
    }
     commandeMouvementMoteur(trameStandard);
}
 //--------------------------------------------------------------------------
void moteurCommande (){
//fonction 
    envoieMoteur(possitionMoteur,(nMax));
    envoieMoteur(vitesseMoteur,(nMax+1));
}

//capteur de pression
//--------------------------------------------------------------------------
float lectureEtMesure(AnalogIn SignalDePressionAmplifie){
    //prise de mesure 
    float coeff,coeff2;
    coeff= 0.0008056640;
    coeff2= 32.02481923;
    unsigned int pressionNumerique;
    float TensionP20, V,PressionEnHpa;
    pressionNumerique = SignalDePressionAmplifie.read_u16();
    V = pressionNumerique;
    TensionP20 = (V/16) * coeff;
    PressionEnHpa= TensionP20*coeff2;
    return PressionEnHpa;
}
//--------------------------------------------------------------------------
void les10PremieresValeurs(AnalogIn SignalDePressionAmplifie){
//set 10 tableau de presion
    for(poiteurpression=0;poiteurpression<10;poiteurpression++){
        tableauPressions[poiteurpression]= lectureEtMesure(SignalDePressionAmplifie);
    }
}
//--------------------------------------------------------------------------
void tempsMort(AnalogIn SignalDePressionAmplifie=SignalDePressionAmplifie){
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
//ax12
//--------------------------------------------------------------------------
trame commandePingAx(trame trameStandard){
    //config commande ping pour Ax
    trameStandard.instruction=indexCommandePing;
    trameStandard.nParametres=0;
    return (trameStandard);
}
//--------------------------------------------------------------------------
trame commandeReadAx(trame trameStandard,char adresseDebut,char adresseLongeur){
    //config commande read pour Ax
    trameStandard.instruction=indexCommandeReadData;
    trameStandard.parametres[0]=adresseDebut;
    trameStandard.parametres[1]=adresseLongeur;
    trameStandard.nParametres=2;
    return (trameStandard);
}
//--------------------------------------------------------------------------
trame commandeRegWriteAx(trame trameStandard,char adresseDebut){
    //config commande reg write pour Ax
    //a revoir
    unsigned int decimalNumber=0;
    trameStandard.instruction=indexCommandeRegWrite;
    decimalNumber = charToInt(trameStandard.parametres,0,3);
    decimalNumber = degreToLong(decimalNumber);
    trameStandard.parametres[0]=adresseDebut;
    trameStandard.parametres[1]=decimalNumber;
    trameStandard.parametres[2]=decimalNumber>>8;
    trameStandard.nParametres=3;
    return (trameStandard);
}
//--------------------------------------------------------------------------
trame commandeWriteAx(trame trameStandard,char adresseDebut){
    //config commande write pour Ax
    //a revoir
    unsigned int decimalNumber=0;
    trameStandard.instruction=indexCommandeWriteData;
    decimalNumber = charToInt(trameStandard.parametres,0,3);
    decimalNumber = degreToLong(decimalNumber);
    trameStandard.parametres[0]=adresseDebut;
    trameStandard.parametres[1]=decimalNumber;
    trameStandard.parametres[2]=decimalNumber>>8;
    trameStandard.nParametres=3;
    return (trameStandard);
}
//--------------------------------------------------------------------------
trame commandeActionAx(trame trameStandard){
    //config commande ping pour Ax
    trameStandard.id=254;
    trameStandard.instruction=indexCommandeAction;
    trameStandard.nParametres=0;
    return (trameStandard);
}
//--------------------------------------------------------------------------
trame commandeSyncWriteAx(trame trameStandard){
    //config commande sync write pour Ax
    unsigned int decimalNumber=0;
    //parametre
    trameStandard.instruction=indexCommandeSyncWrite;
    trameStandard.parametres[0]=0x1E;
    trameStandard.parametres[1]=0x02;
    decimalNumber = charToInt(trameStandard.parametres,0,3);
    decimalNumber = degreToLong(decimalNumber);
    
    if(trameStandard.nParametres>0){
    trameStandard.parametres[2]=trameStandard.id;   
    trameStandard.parametres[3]=decimalNumber;
    trameStandard.parametres[4]=decimalNumber>>8;
    trameStandard.nParametres=5;
    }
    else{
        trameStandard.parametres[trameStandard.nParametres]=trameStandard.id;   
        trameStandard.parametres[trameStandard.nParametres+1]=decimalNumber;
        trameStandard.parametres[trameStandard.nParametres+2]=decimalNumber>>8;
        trameStandard.nParametres+=3; 
    }
    trameStandard.id=0xFE; //broadcasting
    return (trameStandard);
}
//--------------------------------------------------------------------------
trame commandePingPc(trame trameStandard){
    //config commande ping pour Ax
    trameStandard.nParametres=6;
    trameStandard.groupe=indexCommandePingPc;
    trameStandard.instruction=0x00;
    return (trameStandard);
}

//--------------------------------------------------------------------------
trame commandeErrorPc(trame trameStandard){
    //config commande ping pour Ax
    trameStandard.nParametres=6;
    trameStandard.groupe=indexCommandePingPc;
    if(trameStandard.parametres[0]<0x09){
        trameStandard.parametres[4]=0x09;
        trameStandard.parametres[5]=trameStandard.parametres[0];
    }
    else{
        trameStandard.parametres[4]=trameStandard.parametres[0]>>4;
        trameStandard.parametres[5]=0x09;
    }
    trameStandard.parametres[0]=0x09;
    trameStandard.parametres[1]=0x09;
    trameStandard.parametres[2]=0x09;
    trameStandard.parametres[3]=0x09;
    trameStandard.instruction=0x00;
    return (trameStandard);
}
//--------------------------------------------------------------------------
trame commandePressionPc(trame trameStandard){
    //config commande ping pour Ax
    char test[6];
    unsigned int pressionEnHPA;
    pressionEnHPA= floor(moyenne);
    trameStandard.nParametres=6;
    trameStandard.groupe=indexCommandePingPc;
    trameStandard.groupe=0x32;
    trameStandard.instruction=0x32;
    trameStandard.id=0x30;
    intToChar(test, pressionEnHPA);
    trameStandard.parametres[0]=test[0];
    trameStandard.parametres[1]=test[1];
    trameStandard.parametres[2]=test[2];
    trameStandard.parametres[3]=test[3];
    trameStandard.parametres[4]=test[4];
    trameStandard.parametres[5]=test[5];
    return (trameStandard);
}
//--------------------------------------------------------------------------
trame commandeReadPc(trame trameStandard){
    //config commande read pour Ax
    char donneesAConvertire[6];
    trameStandard.nParametres=6;
    unsigned int degrees=trameStandard.parametres[2]<<8;
    degrees+=trameStandard.parametres[1];
    intToChar( donneesAConvertire,longToDegre(degrees));
    for(char x=0;x<trameStandard.nParametres;x++){
        trameStandard.parametres[x]=donneesAConvertire[x];
    }
    trameStandard.instruction=indexCommandeReadData;
    return (trameStandard);
}


//--------------------------------------------------------------------------
void creeTrameAx(trame trameEnvoieAx,char trameEnvoie[]){
    //cree la trame Ax
    trameEnvoie[0]=0xFF;
    trameEnvoie[1]=0xFF;
    trameEnvoie[2]=trameEnvoieAx.id;
    trameEnvoie[3]=trameEnvoieAx.nParametres+2;
    trameEnvoie[4]=trameEnvoieAx.instruction;
    if(trameEnvoieAx.nParametres>0){
        for(char x=0;x<trameEnvoieAx.nParametres;x++){
            trameEnvoie[5+x]=trameEnvoieAx.parametres[x];   
        }
    }
    trameEnvoie[trameEnvoieAx.nParametres+5]=checkSum2(2,trameEnvoieAx.nParametres+5,trameEnvoie); 
}
//--------------------------------------------------------------------------
void creeTramePc(trame trameEnvoiePc,char trameEnvoie[]){
    //cree la trame Pc avec une trame standard 
    trameEnvoie[0]=0x24;
    trameEnvoie[1]=trameEnvoiePc.groupe;
    trameEnvoie[2]=0x3A;
    trameEnvoie[3]=trameEnvoiePc.id;
    trameEnvoie[4]=0x3A;
    trameEnvoie[5]=trameEnvoiePc.instruction;
    trameEnvoie[6]=0x3A;
    for(char x=0;x<trameEnvoiePc.nParametres-2;x++){
            trameEnvoie[7+x]=trameEnvoiePc.parametres[x]+0x30;
    }
    trameEnvoie[11]=0x2E;
    trameEnvoie[12]=trameEnvoiePc.parametres[trameEnvoiePc.nParametres-2]+0x30;
    trameEnvoie[13]=trameEnvoiePc.parametres[trameEnvoiePc.nParametres-1]+0x30;
    trameEnvoie[14]=0x3A;
    trameEnvoie[15]=check(trameEnvoie);
    trameEnvoie[16]=0x26;   
}
//--------------------------------------------------------------------------
trame tramePcToTrameStandard(char bufferreception[]){
    //memorice la trame pc sous une trame standard
    trame trameStandard;
    trameStandard.groupe=bufferreception[1];
    trameStandard.id=bufferreception[3]-0x30;
    trameStandard.instruction=bufferreception[5];
    trameStandard.parametres[0]=bufferreception[7];
    trameStandard.parametres[1]=bufferreception[8];
    trameStandard.parametres[2]=bufferreception[9];
    trameStandard.parametres[3]=bufferreception[10];
    trameStandard.parametres[4]=bufferreception[12];
    trameStandard.parametres[5]=bufferreception[13];
    trameStandard.controleErreur=bufferreception[15];
    return (trameStandard);    
}
//--------------------------------------------------------------------------
trame trameAxToTrameStandard(char bufferenvoie[]){
    //memorice la trame ax sous une trame standard
    trame trameStandard;
    trameStandard.groupe=0;
    trameStandard.id=bufferenvoie[0];
    pc.putc(bufferenvoie[1]-1);
    trameStandard.nParametres=bufferenvoie[1]-1;
    for(char x=0;x<trameStandard.nParametres;x++){
        trameStandard.parametres[x]=bufferenvoie[2+x];
    }
    trameStandard.controleErreur=bufferenvoie[trameStandard.nParametres+1];
    return (trameStandard);
}
//--------------------------------------------------------------------------