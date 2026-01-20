#ifndef TRIPLETS_H
#define TRIPLETS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef INF
#define INF 9999
#endif

/* Structure de graphe (liste d'arêtes / “triplets”) */


typedef struct triplet{
    int i;
    int j;
    int poids;
} triplet;

typedef struct grapheT {
    int nbs; /* nombre de sommets */
    int nba; /* nombre d'arêtes  */
    triplet *aretes; /* tableau d'arêtes (taille nba) */
} grapheT;

/* Prototypes */
triplet *new_triplet(int i,int j,int poids);
grapheT *new_grapheT(int n);
void delete_grapheT(grapheT *g);
void add_edge_weightT(grapheT *g, int i, int j, int poids);

grapheT *remplir_grapheT_densite(int n, double taux);
#endif /* TRIPLETS_H */