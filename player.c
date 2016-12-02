#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "player.h"
int
prendreObjet(personnage *p)
{
    if(p->life>0)
    {
        p->key=1;
        return 1;
    }
    else
    {
        return 0;
    }
}
void perdreVie(personnage *p,int vie)
{
    p->life=p->life-vie;
    printf("%d",p->life);
    if (p->life<0)
    {
        p->life=0;
    }
}
void perdrevie(monster *p,int vie)
{
    p->life=p->life-vie;
    if (p->life<0)
    {
        p->life=0;
    }
}
void deplacer(monster p,int x,int y)
{
    if(p.life>0)
    {
        p.posX=x;
        p.posY=y;
    }
}
void attaquer(personnage *p,monster *m)
{
    if(m->life>0)
        perdreVie(p,m->degat);
    perdrevie(m,2);
}

void attaquerMonstre(personnage *p,monster *m)
{
    if(p->life>0)
        perdrevie(m,2);
    if(m->life==0)
    {
        if(p->life+5<100)
        {
            p->life=p->life+5;
        }
        else
        {
            p->life=100;
        }
    }
}
