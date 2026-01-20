#include <stdio.h>
#include <stdlib.h>
#include<time.h>

/* Structure de tas et fonctions utiles */
typedef struct noeudTas{
    int  v;
    int dist;
} noeudTas;

typedef struct Tas{
    int taille;
    int capacite;
    int *pos;
    struct noeudTas **array;
} Tas;


// Créer un nouveau noeud de tas binaire.
noeudTas * new_noeudTas(int v, int dist);
// Créer un tas de capacité max n.
Tas * creer_tas(int n);
// Echanger les valeurs de deux neouds (nécessaire pour garder la structure)
void echange_noeud(noeudTas **a, noeudTas **b);
// Réorganise le sous-arbre du tas à partir de l’indice donné pour restaurer la propriété de tas binaire.
void entasser(Tas* tas, int idx);
// Tester si un tas est vide
int is_empty_tas(struct Tas* tas);
// Récupérer la valeur minimale (la plus prioritaire)
noeudTas* extract_min(Tas* tas);
// Pour mettre à jour les valeurs dans le tas
void decrease_value(struct Tas* tas, int v, int dist);
// Tester si un sommet est dans le tas.
int is_in_tas(Tas *tas, int v);
