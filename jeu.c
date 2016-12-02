
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "constantes.h"
#include "jeu.h"
#include "fichiers.h"
#include "player.h"

void  jouer(SDL_Surface* ecran,int lvl)
{
    SDL_Surface *player[5] = {NULL}; // 4 surfaces pour chacune des directions
    SDL_Surface *monstre=NULL;
    SDL_Surface *texte= NULL,*mur = NULL,  *objectif = NULL, *playerActuel = NULL,*vide=NULL,*sortie=NULL,*previousattack=NULL;
    SDL_Rect position, positionJoueur,positionsortie,positionmonstre,positionTexte;
    SDL_Event event;
    positionTexte.x=0;
    positionTexte.y=0;
    int continuer = 1, objectifsRestants = 0, i = 0, j = 0;
    int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = {0};
    int nbmonstre=0;
    int tempsPrecedent = 0, tempsActuel = 0;
    personnage *joueur1=malloc(sizeof(personnage));
    joueur1->life=100;
    joueur1->orientation=DROITE;
    // Chargement des sprites (décors, personnage...)
    vide=IMG_Load("vide.png");
    mur = IMG_Load("mur.png");
    monstre=IMG_Load("monstre-attack.png");
    sortie = IMG_Load("sortie.png");
    objectif = IMG_Load("objectif.gif");
    player[BAS] = IMG_Load("zelda-bas.png");
    player[GAUCHE] = IMG_Load("zelda-gauche.png");
    player[HAUT] = IMG_Load("zelda-haut.png");
    player[DROITE] = IMG_Load("zelda-droite.png");
    player[ATTACK]=IMG_Load("attack.png");
    playerActuel = player[DROITE]; // le joueur sera dirigé vers la droite au départ
    // Chargement du niveau
    if (!chargerNiveau(carte,lvl))
        exit(EXIT_FAILURE); // On arrête le jeu si on n'a pas pu charger le niveau

    // Recherche de la position du joueur au départ
    for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
    {
        for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
        {
            if (carte[i][j] == PLAYER) // Si le joueur se trouve à cette position sur la carte
            {
                positionJoueur.x = i;
                positionJoueur.y = j;
                carte[i][j] = VIDE;
            }
            else
            {
                if (carte[i][j] == SORTIE)
                {
                    positionsortie.x = i;
                    positionsortie.y = j;
                }
                else
                {
                    if (carte[i][j]==MONSTRE)
                    {
                        nbmonstre=nbmonstre+1;
                    }
                }
            }
        }
    }
    monster listemonstres[nbmonstre];
    int k=0;
    for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
    {
        for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
        {
            if (carte[i][j] == MONSTRE)
            {
                monster inter;
                inter.life=2;
                inter.degat=20;
                inter.orientation=DROITE;
                inter.posX=i;
                inter.posY=j;
                carte[i][j]=VIDE;
                listemonstres[k]=inter;
                k++;
            }
        }
    }
    int ilyamonstre;
    // Activation de la répétition des touches

    TTF_Init();
    TTF_Font *police = NULL;
    SDL_Color couleurNoire = {0, 0, 0};
    police = TTF_OpenFont("Denominator.ttf", 65);

    while (continuer)
    {
        SDL_PollEvent(&event);
        switch(event.type)
        {
        case SDL_QUIT:
            continuer = 0;
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                continuer = 0;
                break;
            case SDLK_SPACE:
                previousattack=playerActuel;
                playerActuel=player[ATTACK];
                switch(joueur1->orientation)
                {
                case DROITE:
                    for(ilyamonstre=0; ilyamonstre<nbmonstre; ilyamonstre++)
                    {
                        if(positionJoueur.x+1==listemonstres[ilyamonstre].posX && positionJoueur.y==listemonstres[ilyamonstre].posY)
                        {
                            attaquerMonstre(joueur1,&listemonstres[ilyamonstre]);
                        }
                    }
                    break;
                case GAUCHE:
                    for(ilyamonstre=0; ilyamonstre<nbmonstre; ilyamonstre++)
                    {
                        if(positionJoueur.x-1==listemonstres[ilyamonstre].posX && positionJoueur.y==listemonstres[ilyamonstre].posY)
                        {
                            attaquerMonstre(joueur1,&listemonstres[ilyamonstre]);
                        }
                    }
                    break;
                case HAUT:
                    for(ilyamonstre=0; ilyamonstre<nbmonstre; ilyamonstre++)
                    {
                        if(positionJoueur.x==listemonstres[ilyamonstre].posX && positionJoueur.y+1==listemonstres[ilyamonstre].posY)
                        {
                            attaquerMonstre(joueur1,&listemonstres[ilyamonstre]);
                        }
                    }
                    break;
                case BAS:
                    for(ilyamonstre=0; ilyamonstre<nbmonstre; ilyamonstre++)
                    {
                        if(positionJoueur.x==listemonstres[ilyamonstre].posX && positionJoueur.y-1==listemonstres[ilyamonstre].posY)
                        {
                            attaquerMonstre(joueur1,&listemonstres[ilyamonstre]);
                        }
                    }
                    break;
                }

                break;
            case SDLK_UP:
                playerActuel = player[HAUT];
                joueur1->orientation=HAUT;
                deplacerJoueur(carte, &positionJoueur, HAUT,listemonstres,nbmonstre,joueur1);
                if(carte[positionJoueur.x][positionJoueur.y]==OBJECTIF)
                {
                    if(prendreObjet(joueur1))
                        carte[positionJoueur.x][positionJoueur.y]=VIDE;
                }
                break;
            case SDLK_DOWN:
                playerActuel = player[BAS];
                joueur1->orientation=BAS;
                deplacerJoueur(carte, &positionJoueur, BAS,listemonstres,nbmonstre,joueur1);
                if(carte[positionJoueur.x][positionJoueur.y]==OBJECTIF)
                {
                    if(prendreObjet(joueur1))
                        carte[positionJoueur.x][positionJoueur.y]=VIDE;
                }
                break;
            case SDLK_RIGHT:
                playerActuel = player[DROITE];
                joueur1->orientation=DROITE;
                deplacerJoueur(carte, &positionJoueur, DROITE,listemonstres,nbmonstre,joueur1);
                if(carte[positionJoueur.x][positionJoueur.y]==OBJECTIF)
                {
                    if(prendreObjet(joueur1))
                        carte[positionJoueur.x][positionJoueur.y]=VIDE;
                }
                break;
            case SDLK_LEFT:
                playerActuel = player[GAUCHE];
                joueur1->orientation=GAUCHE;
                deplacerJoueur(carte, &positionJoueur, GAUCHE,listemonstres,nbmonstre,joueur1);
                if(carte[positionJoueur.x][positionJoueur.y]==OBJECTIF)
                {
                    if(prendreObjet(joueur1))
                        carte[positionJoueur.x][positionJoueur.y]=VIDE;
                }
                break;
            }
            break;
        }
        tempsActuel = SDL_GetTicks();
        if (tempsActuel - tempsPrecedent > 100) /* Si 30 ms se sont écoulées depuis le dernier tour de boucle */
        {
            for(i=0; i<nbmonstre; i++)
            {
                int k=deplacerMonstre(&listemonstres[i],&positionJoueur,carte,joueur1);
            }
            tempsPrecedent = tempsActuel;
        }

        // Effacement de l'écran
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

        // Placement des objets à l'écran
        objectifsRestants = 0;

        for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
        {
            for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
            {
                position.x = i * TAILLE_BLOC;
                position.y = j * TAILLE_BLOC;

                switch(carte[i][j])
                {
                case MUR:
                    SDL_BlitSurface(mur, NULL, ecran, &position);
                    break;
                case SORTIE:
                    SDL_BlitSurface(sortie, NULL, ecran, &position);
                    break;
                case OBJECTIF:
                    SDL_BlitSurface(vide,NULL,ecran,&position);
                    SDL_BlitSurface(objectif, NULL, ecran, &position);
                    objectifsRestants = 1;
                    break;
                case VIDE:
                    SDL_BlitSurface(vide,NULL,ecran,&position);
                    break;
                }
            }
        }

        int m;
        for(m=0; m<nbmonstre; m++)
        {
            if(listemonstres[m].life>0)
            {
                int posx=listemonstres[m].posX;
                int posy=listemonstres[m].posY;
                positionmonstre.x=posx*TAILLE_BLOC;
                positionmonstre.y=posy*TAILLE_BLOC;

                SDL_BlitSurface(monstre,NULL,ecran,&positionmonstre);

            }

        }




        // On place le joueur à la bonne position
        position.x = positionJoueur.x * TAILLE_BLOC;
        position.y = positionJoueur.y * TAILLE_BLOC;
        SDL_BlitSurface(playerActuel, NULL, ecran, &position);
        char v[3];
        if(joueur1->life<100)
        {
            sprintf(v,"0%d",joueur1->life);
        }
        else
        {
            sprintf(v,"%d",joueur1->life);
        }

        texte=TTF_RenderText_Solid(police,v,couleurNoire);
        texte->w=75;
        texte->h=50;
        SDL_BlitSurface(texte,NULL,ecran,&positionTexte);
        SDL_Flip(ecran);
        if(playerActuel==player[ATTACK])
        {
            playerActuel=previousattack;
            SDL_BlitSurface(playerActuel, NULL, ecran, &position);
        }
        // Si on n'a trouvé aucun objectif sur la carte, c'est qu'on a gagné
        if ((joueur1->key==1&& positionJoueur.x==positionsortie.x && positionJoueur.y==positionsortie.y))
        {
            continuer = 0;
            afficherVictoire(ecran);
        }
        else
        {
            if(joueur1->life<=0)
            {
                continuer=0;
                afficherDefaite(ecran);
            }
        }
    }

    // Désactivation de la répétition des touches (remise à 0)
    SDL_EnableKeyRepeat(0, 0);

    // Libération des surfaces chargées
    SDL_FreeSurface(mur);
    SDL_FreeSurface(monstre);
    SDL_FreeSurface(sortie);
    SDL_FreeSurface(objectif);
    SDL_FreeSurface(vide);
    for (i = 0 ; i < 5 ; i++)
        SDL_FreeSurface(player[i]);
    TTF_CloseFont(police);
    TTF_Quit();
}

void deplacerJoueur(int carte[][NB_BLOCS_HAUTEUR], SDL_Rect *pos, int direction,monster *lm,int l,personnage  *p)
{
    int i;
    int deplacable=1;
    switch(direction)
    {
    case HAUT:
        if (pos->y - 1 < 0) // Si le joueur dépasse l'écran, on arrête
            deplacable=0;
        if (carte[pos->x][pos->y - 1] == MUR) // S'il y a un mur ou un monstre, on arrête
            deplacable=0;
        // Si on arrive là, c'est qu'on peut déplacer le joueur !
        for(i=0; i<l; i++)
        {
            if(pos->x==lm[i].posX && pos->y-1==lm[i].posY&&lm[i].life>0)
            {
                attaquer(p,&lm[i]);
                deplacable=0;
            }
        }
        if (deplacable)
        {
            p->orientation=HAUT;
            pos->y--; // On peut enfin faire monter le joueur
        }
        break;


    case BAS:
        if (pos->y + 1 >= NB_BLOCS_HAUTEUR)
            deplacable=0;
        if (carte[pos->x][pos->y + 1] == MUR)
            deplacable=0;
        for(i=0; i<l; i++)
        {

            if(pos->x==lm[i].posX && pos->y+1==lm[i].posY&&lm[i].life>0)
            {
                attaquer(p,&lm[i]);
                deplacable=0;
            }

        }
        if(deplacable)
        {
            p->orientation=HAUT;
            pos->y++;
        }
        break;


    case GAUCHE:
        if (pos->x - 1 < 0)
            deplacable=0;
        if (carte[pos->x - 1][pos->y] == MUR)
            deplacable=0;
        for(i=0; i<l; i++)
        {
            if(pos->x-1==lm[i].posX && pos->y==lm[i].posY&&lm[i].life>0)
            {
                deplacable=0;
                attaquer(p,&lm[i]);
            }
        }
        if(deplacable)
        {
            p->orientation=HAUT;
            pos->x--;
        }
        break;


    case DROITE:
        if (pos->x + 1 >= NB_BLOCS_LARGEUR)
            deplacable=0;
        if (carte[pos->x + 1][pos->y] == MUR)
            deplacable=0;
        for(i=0; i<l; i++)
        {
            if(pos->x+1==lm[i].posX && pos->y==lm[i].posY&&lm[i].life>0)
            {
                attaquer(p,&lm[i]);
                deplacable=0;
            }
        }
        if(deplacable)
        {
            p->orientation=HAUT;
            pos->x++;
        }
        break;
    }
}

int deplacerMonstre(monster *listemonstre,SDL_Rect *pos,int carte[][NB_BLOCS_HAUTEUR],personnage *p)
{

    int deplacable=1;
    int attack=0;
    if(listemonstre->life>0)
    {
        switch(listemonstre->orientation)
        {
        case GAUCHE:
            if (listemonstre->posX - 1 < 0)
            {
                deplacable=0;
                listemonstre->orientation=DROITE;
            }
            if (carte[listemonstre->posX - 1][listemonstre->posY] == MUR)
            {
                deplacable=0;
                listemonstre->orientation=DROITE;
            }
            if(listemonstre->posX-1==pos->x&& pos->y==listemonstre->posY)
            {
                attaquer(p,listemonstre);
                attack=1;
                deplacable=0;
            }
            if(deplacable)
            {
                listemonstre->posX=listemonstre->posX-1;
            }
            break;


        case DROITE:
            if (listemonstre->posX +1 > NB_BLOCS_LARGEUR)
            {
                deplacable=0;
                listemonstre->orientation=GAUCHE;
            }
            if (carte[listemonstre->posX + 1][listemonstre->posY] == MUR)
            {
                deplacable=0;
                listemonstre->orientation=GAUCHE;
            }
            if(listemonstre->posX+1==pos->x&& pos->y==listemonstre->posY)
            {
                attaquer(p,listemonstre);
                attack=1;
                deplacable=0;
            }
            if(deplacable)
            {
                listemonstre->posX=listemonstre->posX+1;
            }
            break;
        }
    }
}




