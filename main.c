/**
* @file main.c
* @brief Testing Program.
* @author slimayadi
* @version 1.1
* @date june 11 2020
*
* Testing program for ai
*
*/


#include "ai.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL_image.h>
int main (int argc, char *argv[])
{
    int col;
    int gameover = 0;// false
    int nbcoups = 0;
    char grille[NB_COLONNES][NB_LIGNES];
    int player = 1;// true

    Init(grille);
    AfficheGrille(grille);

    while (!gameover)
    {
        do
        {
            col = demande(player, grille);
        }while(coupvalide(grille, col)==0); // tant qu'il n'est pas possible de jouer là, on redemande
        joue(player, grille, col);
        printf("Joueur %s a joue:\n", player == 0 ? "JAUNE" : "ROUGE");
        AfficheGrille(grille);
        nbcoups++;
        if (check(grille)==1)
        {
            gameover = 1;
            printf("Victoire de %s au %dieme coups!", player == 0 ? "JAUNE" : "ROUGE", nbcoups);
        }
        else if (nbcoups == NB_COLONNES*NB_LIGNES)
        {
            gameover = 1;
            printf("Match NUL (%d coups)\n", nbcoups);
        }
        player = !player; // au joueur suivant de jouer
    }
    return 0;
}
