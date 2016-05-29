#ifndef DEF_VARIABLEGLOBAL
#define DEF_VARIABLEGLOBAL
#include "classAx12.h"

//provisoire pour les pointeurs
//char bufferreception[20];
unsigned char position;
int position2;
bool confirme;
bool confirme2;
char conp;
char lenghttrameax;
char bufferenvoie[9]={0xFF,0xFF,0x06,0x05,0x03,0x1E,0x00,0x00,0x00};
char bufferenvoie2[9]={0xFF,0xFF,0x06,0x02,0x01,0x00,0x00,0x00,0x00};
char bufferenvoie3[9]={0};
char bufferenvoiePc[17]={0x24,0x00,0x3A,0x00,0x3A,0x00,0x3A,0x00,0x00,0x00,0x00,0x2E,0x00,0x00,0x3A,0x00,0x26};
float tableauPressions[10];
int vitessePc;
int vitesseAx;
short lenght;
short intruction;
//int m;
float moyenne;
//Appel du tempsEcoule
float tempsEnSecondeAttenduEntreChaqueEchantillon;
//format trame pour simplifier la programation 

bool b=false;
#endif