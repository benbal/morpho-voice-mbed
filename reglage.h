/*
            reglage par defaut
*/
//serial
    //serial canal 0:pc
        Serial pc(USBTX,USBRX);
    //serial canal 1:ax-12A
        Serial ax(p9,p10 );
//
char chaine[100];
int TAILLE_MAX=100;
FILE* fichier = NULL;

      