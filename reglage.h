/*
            reglage par defaut
*/
//serial
    //serial canal 0:pc
        Serial pc(USBTX,USBRX);
    //serial canal 1:ax-12A
        Serial ax(p9,p10 );
Serial *testp=&ax;
//Sortie Digital
        DigitalOut selectionRxTx (p21);    