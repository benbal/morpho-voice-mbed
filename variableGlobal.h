//provisoire pour les pointeurs
char bufferreception[20]=bufferReception;
int position=0;
int position2=0;
bool confirme =false;
bool confirme2 =false;
char conp=0;
char lenghttrameax=3;
char bufferenvoie[9]=bufferEnvoie;
char bufferenvoie2[9]=bufferEnvoie2;
char bufferenvoie3[9]={0};
char bufferenvoiePc[17]=bufferEnvoiePc;
int vitessePc=vitessePC;
int vitesseAx=vitesseAX;
short lenght=5;
short intruction=6;
int m=0;
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
//trame pour simplifier la programation simplifier
typedef struct trame trame;
struct trame
{   
    char groupe;
    char id;
    char instruction;
    char nParametres;
    char parametres[10];
    char controleErreur;
};
bool b=false;
 
