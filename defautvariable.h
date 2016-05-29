/*
                            reglage par defaut
*/
//serial
    //serial canal 0:pc
        #define vitessePC 115200; 
    //serial canal 1:ax-12A
        #define vitesseAX 9600; //1000000
    //serial canal 1:ax-12A
        #define vitesseMP 9600;
//buffer
    //buffer à zero
        #define setZero {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    //buffer de reception Pc
        #define bufferReception {0x81,0x82,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    //buffer d'envoie Ax
        #define bufferEnvoie {0xFF,0xFF,0x06,0x05,0x03,0x1E,0x00,0x00,0x00};
    //buffer d'envoie Ax
        #define bufferEnvoie2 {0xFF,0xFF,0x06,0x02,0x01,0x00,0x00,0x00,0x00};
    //buffer d'envoie Pc
        #define bufferEnvoiePc {0x24,0x00,0x3A,0x00,0x3A,0x00,0x3A,0x00,0x00,0x00,0x00,0x2E,0x00,0x00,0x3A,0x00,0x26};
//id
    //ax-12A
        //ax-12A: 0
            #define ax_12A_00 0x00;
        //ax-12A: 1
            #define ax_12A_01 0x01;
        //ax-12A: 2
            #define ax_12A_02 0x02;
        //ax-12A: 3
            #define ax_12A_03 0x03;
            //ax-12A: 1
            #define ax_12A_04 0x04;
        //ax-12A: 2
            #define ax_12A_05 0x05;
        //ax-12A: 3
            #define ax_12A_06 0x05;
//index des commande ax12A
    //ping
        #define indexCommandePing 0x01;
    //ReadData
        #define indexCommandeReadData 0x02;
    //WriteData
        #define indexCommandeWriteData 0x03;
    //RegWrite
        #define indexCommandeRegWrite 0x04;
    //Action
        #define indexCommandeAction 0x05;
    //Reset
        #define indexCommandeReset 0x06;
    //SyncWrite
        #define indexCommandeSyncWrite 0x83;
//index des commande pc
    //ping
        #define indexCommandePingPc 0x01;
    //ReadData
        #define indexCommandeReadDataPc 0x02;
    //WriteData
        #define indexCommandeWriteDataPc 0x03;
    //RegWrite
        #define indexCommandeRegWritePc 0x04;
    //Action
        #define indexCommandeActionPc 0x05;
    //Reset
        #define indexCommandeResetPc 0x06;
    //SyncWrite
        #define indexCommandeSyncWritePc 0x83;
//index des adresse ax12A
//a complet et integer au code 
    //position
        #define indexAdresseGoalPosition 0x1E;
    //vitesse
        #define indexAdresseMovingSpeed 0x20;
//constantes 
    //capteur de pression
        // quantum conversion ADC Mbed 12bits
        #define COEFF 0.0008056640;
        //(1/Gain de l'ampli) / (quantum de conversion hPa = 18uV/0.06895hPa)
        #define COEFF2 32.02481923;
        //float temps En Seconde Attendu Entre Chaque Echantillon
        //#define tempsEnSecondeAttenduEntreChaqueEchantillon = 0.1;