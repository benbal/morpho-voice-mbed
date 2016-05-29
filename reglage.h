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
    //selection sortie
        DigitalOut selectionRxTx (p21);
        DigitalOut selectionSyRen (p22);
    //Voyant
        DigitalOut led1(LED1);
        DigitalOut led2(LED2); 
//Entre Digital
    //capteur de fin de course
        InterruptIn finDeCourse(p29);
        InterruptIn finDeCourse2(p30);
//Entre Analogique
    //capteur de pression
        AnalogIn   SignalDePressionAmplifie(p20);
//time
    //temps entre deux mesure de pression
        Ticker  tempsEcoule;
