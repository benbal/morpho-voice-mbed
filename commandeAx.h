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
trame commandePingPc(trame trameStandard){
    //config commande ping pour Ax
    trameStandard.groupe=indexCommandePingPc;
    trameStandard.instruction=0x00;
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
    trameStandard.nParametres=bufferenvoie[1]-1;
    for(char x=0;x<trameStandard.nParametres;x++){
        trameStandard.parametres[x]=bufferenvoie[2+x];
    }
    trameStandard.controleErreur=bufferenvoie[trameStandard.nParametres+1];
    return (trameStandard);
}

