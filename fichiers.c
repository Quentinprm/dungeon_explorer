
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "constantes.h"
#include "fichiers.h"

int chargerNiveau(int niveau[][NB_BLOCS_HAUTEUR],int lvl)
{
    FILE* fichier = NULL;
    char ligneFichier[NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR + 1] = {0};
    int i = 0, j = 0;
    switch(lvl)
    {
    case 1:
        fichier = fopen("niveaux1.lvl", "r");
        break;
    case 2:
        fichier = fopen("niveaux2.lvl", "r");
        break;
    case 3:
        fichier = fopen("niveaux3.lvl", "r");
        break;
    }
    if (fichier == NULL)
        return 0;

    fgets(ligneFichier, NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR + 1, fichier);

    for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
    {
        for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
        {
            switch (ligneFichier[(i * NB_BLOCS_LARGEUR) + j])
            {
            case '0':
                niveau[j][i] = 0;
                break;
            case '1':
                niveau[j][i] = 1;
                break;
            case '2':
                niveau[j][i] = 2;
                break;
            case '3':
                niveau[j][i] = 3;
                break;
            case '4':
                niveau[j][i] = 4;
                break;
            case'5':
                niveau[j][i]=5;
                break;
            }
        }
    }

    fclose(fichier);
    return 1;
}


