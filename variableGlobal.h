//provisoire pour les pointeurs
char bufferreception[20]=bufferReception;
int position=0;
int position2=0;
bool confirme =false;
bool confirme2 =false;
char conp=0;
char lenghttrameax=3;
bool b=false;
//buffer
char bufferenvoie[9]=bufferEnvoie;
char bufferenvoie2[9]=bufferEnvoie2;
char bufferenvoie3[9]={0};
char bufferenvoiePc[17]=bufferEnvoiePc;
//Vitesse communication
int vitessePc=vitessePC;
int vitesseAx=vitesseAX;
int vitesseMp=vitesseMP;
//
short lenght=5;
short intruction=6;
int m=0;
//capteur de pression
float moyenne;
float tempsEnSecondeAttenduEntreChaqueEchantillon = 0.1;
float tableauPressions[10];
unsigned char poiteurpression;
//moteur
unsigned char vitesseMoteur[8];
unsigned char possitionMoteur[8];
unsigned char nMax=6;
//types perso
typedef struct Adresse Adresse;
struct Adresse{
    char adresse;
    char longeur;
    char valeurs[2];    
};
typedef struct ax12A ax12A;
struct ax12A
{
     Adresse goalPosition;
     Adresse moving;  
};
//format trame pour simplifier la programation 
typedef struct trame trame;
struct trame
{   
    char groupe;
    char id;
    char instruction;
    char nParametres;
    char parametres[100];
    char controleErreur;
};
//syncwrite
trame trameSyncWrite;

 
