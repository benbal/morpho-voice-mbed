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
int vitessepc=vitessePC;
int vitesseax=vitesseAX;
char id= ax_12A_06;
short lenght=5;
short intruction=6;
int m=0;
typedef struct Adresse Adresse;
struct Adresse{
    int adresse;
    int longeur;
};
typedef struct ax12A ax12A;
struct ax12A
{
     Adresse goalPosition;
     Adresse moving;
    
};
typedef struct commandeax12A commandeax12A;
struct commandeax12A
{
     char ping;
     char readData;
     char writeData;
     char regWrite;
     char action;
     char reset;
     char syncWrite;
};

ax12A memoireAx06 ;
ax12A commandeAx06 ;
 //short parametre1=;
 //short parametre2=;
 
 //int test[] = { 1 , 2 ,3  ,4  , 5 };
 bool b=false;
 
