
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "constantes.h"
#include "editeur.h"
#include "fichiers.h"

void editeur(SDL_Surface* ecran)
{
    SDL_Surface *learn=NULL;
    SDL_Rect positionMenu;
    positionMenu.x = 0;
    positionMenu.y = 0;
    SDL_Event event;
    int continuer = 1;
    learn=IMG_Load("learn.png");





    // Boucle infinie de l'éditeur
    while (continuer)
    {
        SDL_WaitEvent(&event);
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
            }
        }
        // Effacement de l'écran
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        SDL_BlitSurface(learn, NULL, ecran, &positionMenu);
        // Mise à jour de l'écran
        SDL_Flip(ecran);
    }


    SDL_FreeSurface(learn);
}

void afficherDefaite(SDL_Surface* ecran)
{
    SDL_Surface *learn=NULL;
    SDL_Rect positionMenu;
    positionMenu.x = 0;
    positionMenu.y = 0;
    SDL_Event event;
    int continuer = 1;
    learn=IMG_Load("defeat.png");





    // Boucle infinie de l'éditeur
    while (continuer)
    {
        SDL_WaitEvent(&event);
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
            }
        }
        // Effacement de l'écran
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        SDL_BlitSurface(learn, NULL, ecran, &positionMenu);
        // Mise à jour de l'écran
        SDL_Flip(ecran);
    }


    SDL_FreeSurface(learn);
}

void afficherVictoire(SDL_Surface* ecran)
{
    SDL_Surface *learn=NULL;
    SDL_Rect positionMenu;
    positionMenu.x = 0;
    positionMenu.y = 0;
    SDL_Event event;
    int continuer = 1;
    learn=IMG_Load("victory.png");





    // Boucle infinie de l'éditeur
    while (continuer)
    {
        SDL_WaitEvent(&event);
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
            }
        }
        // Effacement de l'écran
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        SDL_BlitSurface(learn, NULL, ecran, &positionMenu);
        // Mise à jour de l'écran
        SDL_Flip(ecran);
    }


    SDL_FreeSurface(learn);
}

void afficherListe(SDL_Surface *ecran)
{
    SDL_Surface *learn=NULL;
    SDL_Rect positionMenu;
    positionMenu.x = 0;
    positionMenu.y = 0;
    SDL_Event event;
    int continuer = 1;
    learn=IMG_Load("lvl.png");





    // Boucle infinie de l'éditeur
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_QUIT:
            continuer = 0;
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE: // Veut arrêter le jeu
                continuer = 0;
                break;
            case SDLK_KP1: // Demande à jouer
                jouer(ecran,1);
                break;
            case SDLK_KP2: // Demande l'éditeur de niveaux
                jouer(ecran,2);
                break;
            case SDLK_KP3: // Demande l'éditeur de niveaux
                jouer(ecran,3);
                break;
            }
            break;
        }


        // Effacement de l'écran
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        SDL_BlitSurface(learn, NULL, ecran, &positionMenu);
        // Mise à jour de l'écran
        SDL_Flip(ecran);
    }


    SDL_FreeSurface(learn);

}

