/*
            reglage par defaut
*/
//serial
    //serial canal 0:pc
        Serial pc(USBTX,USBRX);
    //serial canal 1:ax-12A
        Serial ax(p9,p10 );
    //serial canal 2:moteur poumon
        Serial mp(p28,p27 );
        //mode serial simplifie switches 2 et 4 a off les autre sur on
//Sortie Digital
        DigitalOut selectionRxTx (p21);
//Voyant
        DigitalOut led1(LED1);
        DigitalOut led2(LED2);    