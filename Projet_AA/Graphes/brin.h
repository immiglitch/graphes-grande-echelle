#ifndef BRIN_H
#define BRIN_H

#include "triplets.h"


typedef struct {
    int nbs;        // Nombre de sommets
    int nba;        // Nombre d'arêtes
    int *S;         // Sommets : index de début dans B pour chaque sommet (taille nbs + 1)
    int *B;         // Brins : les voisins (taille nba)
    int *W;         // Poids : poids des arêtes (taille nba)
} grapheB;

grapheB* convertir_triplets_vers_brin(grapheT *gt);
void free_grapheB(grapheB *g);
void CC_brin(grapheB *g);
void dijkstra_brin(grapheB *g, int src);

#endif