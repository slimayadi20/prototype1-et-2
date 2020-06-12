/**
* @file ai.c
*@author slimayadi
*@brief intelligence artificielle
*@date 11 juin 2020
*@version 1.1
*/
#include "ai.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL_image.h>


/**
* @brief choisir colonne .
* @param player le joueur 
* @param grille la grille ou on mets les jetons
* @return entier col 
*/

int joueur1IA(int player, char grille[NB_COLONNES][NB_LIGNES])
{
    int col=1;
    printf("JOUEUR: %s - quelle colonne voulez vous jouer?\n" , player == FALSE ? "JAUNE" : "ROUGE");
    scanf("%d", &col);
    return col;

}
/**
* @brief le pc met le jetons aleatoirement .
* @param player le joueur
* @param grille la grille ou on mets les jetons
* @return entier col 
*/
int joueur2IA(int player, char grille[NB_COLONNES][NB_LIGNES])
{
    int col;
    static int once = FALSE;
    if (once == FALSE)
    {
        srand(time(NULL));
        once = TRUE;
    }
    col = (rand() % NB_COLONNES) + 1; // donne un nombre entre 1 et NB_COLONNES:
    return col;

}
/**
* @brief verifier si le coup est valide ou non   .
* @param colonne 
* @param grille la grille ou on mets les jetons
* @return entier voir si la position est valide
*/
int coupvalide(char grille[NB_COLONNES][NB_LIGNES], int colonne) // numero entre 0 et 6 indiquant la colonne jouée
{
    int y;
    int lignefree=-1; // contient le numero de ligne de la case qui est libre pour cette colonne, -1 si la colonne est pleine

    colonne -=1; // pour passer de 1..NB_COLONNES à 0..NB_COLONNES-1

    if (colonne < 0 || colonne >= NB_COLONNES)
    {
        return FALSE; // si le numero de colonne est en dehors des bornes, le coup n'est pas valide
    }

    for ( y = NB_LIGNES-1; y >=0 ; y--)
    {
        if (grille[colonne][y] == VIDE)
            lignefree = y;
    }

    if (lignefree== -1)
    {
        return FALSE; // si la colonne est pleine, le coup n'est pas valide
    }
    return TRUE;
}
/**
* @brief To initialize thegrille .
* @param grille la grille ou on mets les jetons
* @return Nothing
*/
void Init(char grille[NB_COLONNES][NB_LIGNES])
{
    int w, h;
    for(w = 0; w < NB_COLONNES; w++)
    {
        for(h = 0; h < NB_LIGNES; h++)
        {
            grille[w][h]=VIDE; // on initialise la tableau pour qu'il soit vide au debut
        }
    }
}
/**
* @brief afficher la grille .
* @param tableau la matrice ou on mets les jetons

* @return Nothing
*/
void AfficheGrille(char tableau[NB_COLONNES][NB_LIGNES])
{
    int w, h;

    printf("|");
    for(w = 0; w < NB_COLONNES; w++)
        printf(" %d ", w+1);  // on affiche le numero de la colonne
    printf("|\n");

    printf("|");
    for(w = 0; w < NB_COLONNES; w++)
        printf("___", w+1); // une ligne 'souligné' pour dessiner le cadre
    printf("|\n");

    for(h = NB_LIGNES-1 ; h >= 0; h--) // on affiche la ligne du haut en haut et on descend pour avoir l'afficgage dans le bon sens
    {
        printf("|");
        for(w = 0; w< NB_COLONNES; w++)
        {
            printf(" %c ", tableau[w][h]);
        }
        printf("|\n");
    }
    printf("|");
    for(w = 0; w < NB_COLONNES; w++)
        printf("___", w+1); // une ligne 'souligné' pour dessiner le cadre
    printf("|\n");
}
/**
* @brief verifier si vous avez gagne ou non  .
* @param grille la grille ou on mets les jetons

* @return entier false si il na pas gagne 
*/
int check(char grille[NB_COLONNES][NB_LIGNES])
/*
    Principe:
    Additioner le contenu de la case adjacente correcte (->meme couleur)
    au contenu de la case courante.
*/

{
    Case game[NB_COLONNES][NB_LIGNES];
    int ligne, colonne;
    for ( ligne = 0; ligne < NB_LIGNES ; ligne++)
    {
        for ( colonne = 0; colonne < NB_COLONNES; colonne++)
        {
            /*
            Par defaut il y a 1 pion sur 4 d'aligner correctement
            */
            game[colonne][ligne].horz=1;
            game[colonne][ligne].vert=1;
            game[colonne][ligne].dg=1;
            game[colonne][ligne].dd=1;
        }
    }

    // pour le horizontal
    for ( ligne = 0; ligne < NB_LIGNES ; ligne++)
    {
        for ( colonne = 1; colonne < NB_COLONNES; colonne++)
        {
            if ((grille[colonne][ligne]==grille[colonne-1][ligne])&&(grille[colonne][ligne]!=VIDE))
                // meme couleur
            {
                game[colonne][ligne].horz=game[colonne-1][ligne].horz+1;
                if (game[colonne][ligne].horz==4)
                    return TRUE;
            }
        }
    }
    // pour le vertical
    for ( ligne = 1; ligne < NB_LIGNES ; ligne++)
    {
        for ( colonne = 0; colonne < NB_COLONNES; colonne++)
        {
            if ((grille[colonne][ligne]==grille[colonne][ligne-1])&&(grille[colonne][ligne]!=VIDE))
                // meme couleur
            {
                game[colonne][ligne].vert=game[colonne][ligne-1].vert+1;
                if (game[colonne][ligne].vert==4)
                    return TRUE;
            }
        }
    }
    // pour le diagonal gauche:de bas à gauche vers haut à droite
    for ( ligne = 1; ligne < NB_LIGNES ; ligne++)
    {
        for ( colonne = 0; colonne < NB_COLONNES-1; colonne++)
        {
            if ((grille[colonne][ligne]==grille[colonne+1][ligne-1])&&(grille[colonne][ligne]!=VIDE))
                // meme couleur
            {
                game[colonne][ligne].dg=game[colonne+1][ligne-1].dg+1;
                if (game[colonne][ligne].dg==4)
                    return TRUE;
            }
        }
    }
    // pour le diagonal droite:de haut à gauche vers bas à droite
    for ( ligne = 1; ligne < NB_LIGNES ; ligne++)
    {
        for ( colonne = 1; colonne < NB_COLONNES; colonne++)
        {
            if ((grille[colonne][ligne]==grille[colonne-1][ligne-1])&&(grille[colonne][ligne]!=VIDE))
                // meme couleur
            {
                game[colonne][ligne].dd=game[colonne-1][ligne-1].dd+1;
                if (game[colonne][ligne].dd==4)
                    return TRUE;
            }
        }
    }
    return FALSE;
}
/**
* @brief voir si la position est vide ou non  .
* @param player joueur
* @param grille la grille ou on mets les jetons
* @return Nothing
*/
void joue(int player, char grille[NB_COLONNES][NB_LIGNES], int colonne )
/*
  colonne entre 1 et 7 inclus
*/
{
    int lignefree=-1; // contient le numero de ligne de la case qui est libre pour cette colonne, -1 si la colonne est pleine
    int y;
    colonne -=1;

    if (colonne < 0 || colonne >= NB_COLONNES)  // ne devrait pas arriver à ce stade si coupvalide() a été appelé avant cette fonction
    {
        return ; // si le numero de colonne est en dehors des bornes, le coup n'est pas valide
    }

    for ( y = NB_LIGNES-1; y >=0 ; y--)
    {
        if (grille[colonne][y] == VIDE)
            lignefree = y;
    }
    if (lignefree== -1) // ne devrait pas arriver a ce stade si coupvalide() a été appelé avant cette fonction
    {
        return;
    }

    grille[colonne][lignefree]= (player == FALSE) ? JAUNE:ROUGE;
    printf("%s a joue grille[%d][%d]\n", (player == FALSE) ? "JAUNE":"ROUGE", colonne+1, lignefree+1);
}
/**
* @brief demander au joueur de jouer .
* @param player le joueur 
* @param grille la grille ou on mets les jetons
* @return entier la colonne ou il va jouer
*/
int demande(int player, char grille[NB_COLONNES][NB_LIGNES])
{
    int col;
    printf("JOUEUR: %s - A votre tour...\n" , player == FALSE ? "JAUNE" : "ROUGE");
    switch (player)
    {
        case TRUE:
            col = joueur1IA(player, grille);
            break;
        case FALSE:
            col = joueur2IA(player, grille);
            break;
    }
    printf("JOUEUR: %s - joue colonne %d\n" , player == FALSE ? "JAUNE" : "ROUGE", col);
    return col;
}
