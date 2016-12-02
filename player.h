#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

typedef struct personnage
{
    int life;
    int key;
    int orientation;
} personnage;
typedef struct monster
{
    int life;
    int degat;
    int orientation;
    int posX;
    int posY;
} monster;

int prendreObjet(personnage *p);
void perdreVie(personnage *p,int vie);
void perdrevie(monster *p,int vie);
void deplacer(monster p,int x,int y);
void attaquer(personnage *p,monster *m);
void attaquerMonstre(personnage *p,monster *m);

#endif // PLAYER_H_INCLUDED
