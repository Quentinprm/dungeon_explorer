

#ifndef DEF_CONSTANTES
#define DEF_CONSTANTES

#define TAILLE_BLOC         50 // Taille d'un bloc (carré) en pixels
#define NB_BLOCS_LARGEUR    20
#define NB_BLOCS_HAUTEUR    20
#define LARGEUR_FENETRE     TAILLE_BLOC * NB_BLOCS_LARGEUR
#define HAUTEUR_FENETRE     TAILLE_BLOC * NB_BLOCS_HAUTEUR
#define RAND_MAX            32767

enum {HAUT, BAS, GAUCHE, DROITE,ATTACK};
enum {VIDE, MUR, MONSTRE, OBJECTIF, PLAYER, SORTIE};

#endif
