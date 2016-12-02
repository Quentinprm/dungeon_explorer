
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_getenv.h>
#include <SDL/SDL_ttf.h>

#include "constantes.h"
#include "jeu.h"
#include "editeur.h"

int main(int argc, char *argv[])
{
    SDL_Surface *ecran = NULL, *menu = NULL;
    SDL_Rect positionMenu;
    SDL_Event event;

    int continuer = 1;

    SDL_Init(SDL_INIT_VIDEO| SDL_INIT_TIMER);
    putenv("SDL_VIDEO_WINDOW_POS=center"); //pour centrer la fenêtre
    SDL_WM_SetIcon(IMG_Load("icone.png"), NULL); // L'icône doit être chargée avant SDL_SetVideoMode
    ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Dungeon Explorer", NULL);

    menu = IMG_Load("acceuil.png");
    positionMenu.x = 0;
    positionMenu.y = 0;
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
                afficherListe(ecran);
                break;
            case SDLK_KP2: // Demande l'éditeur de niveaux
                editeur(ecran);
                break;
            }
            break;
        }

        // Effacement de l'écran
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
        SDL_BlitSurface(menu, NULL, ecran, &positionMenu);
        SDL_Flip(ecran);
    }

    SDL_FreeSurface(menu);
    SDL_Quit();

    return EXIT_SUCCESS;
}
