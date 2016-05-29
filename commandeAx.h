//--------------------------------------------------------------------------
trame commandePingAx(trame trameStandard){
    //config commande ping pour Ax
    trameStandard.instruction=indexCommandePing;
    trameStandard.nParametres=0;
    return (trameStandard);
}
//--------------------------------------------------------------------------
void commandeReadAx(trame trameStandard,char adresseDebut,char adresseLongeur){
    //config commande read pour Ax
    trameStandard.instruction=indexCommandeReadData;
    trameStandard.parametres[0]=adresseDebut;
    trameStandard.parametres[1]=adresseLongeur;
    trameStandard.nParametres=2;
}
//--------------------------------------------------------------------------
trame commandeRegWriteAx(trame trameStandard,char adresseDebut){
    //config commande reg write pour Ax
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
void creeTrame(trame trameEnvoieAx,char trameEnvoie[]){
    //cree la trame Ax
    pc.putc(0x44);
    trameEnvoie[0]=0xFF;
    trameEnvoie[1]=0xFF;
    trameEnvoie[2]=trameEnvoieAx.id;
    pc.putc(trameEnvoieAx.nParametres+2);
    trameEnvoie[3]=trameEnvoieAx.nParametres+2;
    trameEnvoie[4]=trameEnvoieAx.instruction;
    if(trameEnvoieAx.nParametres>0){
        pc.putc(0x42);
        
        
        for(char x=0;x<trameEnvoieAx.nParametres;x++){
            trameEnvoie[5+x]=trameEnvoieAx.parametres[x];
        }
    }
    for(char x=0;x<15;x++){
        pc.putc(trameEnvoie[x]);
    }
    pc.putc(0x44);
    trameEnvoie[trameEnvoieAx.nParametres+5]=checkSum2(2,trameEnvoieAx.nParametres+5,trameEnvoie);
    
}
//--------------------------------------------------------------------------
trame tramePcToTrameStandard(char bufferenvoie[]){
    trame trameStandard;
    trameStandard.groupe=bufferreception[1];
    trameStandard.id=bufferreception[3];
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
    trame trameStandard;
    trameStandard.groupe=0;
    trameStandard.id=bufferreception[0];
    trameStandard.nParametres=bufferreception[1]-1;
    for(char x=0;x<trameStandard.nParametres;x++){
        trameStandard.parametres[x]=bufferenvoie[2+x];
    }
    trameStandard.controleErreur=bufferreception[trameStandard.nParametres+1];
    return (trameStandard);
}

