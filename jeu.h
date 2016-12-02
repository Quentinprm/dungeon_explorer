#include "player.h"
#ifndef DEF_JEU
#define DEF_JEU

void jouer(SDL_Surface* ecran,int lvl);
void deplacerJoueur(int carte[][NB_BLOCS_HAUTEUR], SDL_Rect *pos, int direction,monster *lm,int l,personnage *p);
int deplacerMonstre(monster *listemonstre,SDL_Rect *pos,int carte[][NB_BLOCS_HAUTEUR],personnage *p);

#endif
