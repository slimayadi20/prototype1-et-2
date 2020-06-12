
/**
* @struct case
* @brief struct for case

*/

#define FONCTIONS_H_

#define NB_COLONNES 7
#define NB_LIGNES 6

#define  VIDE ' '
#define ROUGE 'x'
#define JAUNE 'o'

#define TRUE 1
#define FALSE 0

typedef struct
{
    int dg;
    int vert;
    int dd;
    int horz;
}Case ;
int joueur1IA(int player, char grille[NB_COLONNES][NB_LIGNES]) ; 
int joueur2IA(int player, char grille[NB_COLONNES][NB_LIGNES]) ; 
int coupvalide(char grille[NB_COLONNES][NB_LIGNES], int colonne)  ;
void Init(char grille[NB_COLONNES][NB_LIGNES]);
void AfficheGrille(char tableau[NB_COLONNES][NB_LIGNES]) ; 
int check(char grille[NB_COLONNES][NB_LIGNES]) ; 
void joue(int player, char grille[NB_COLONNES][NB_LIGNES], int colonne ) ; 
int demande(int player, char grille[NB_COLONNES][NB_LIGNES]) ;
