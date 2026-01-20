#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "triplets.h"
#include "brin.h"

/* Création d'un triplet */
triplet *new_triplet(int i,int j,int poids){
    triplet *t = (triplet*)malloc(sizeof(*t));
    if (!t) return NULL;
    t->i = i; t->j = j; t->poids = poids;
    return t;
}

/* Création / destruction du graphe triplet */
grapheT *new_grapheT(int n) {
    grapheT *g = (grapheT*)malloc(sizeof(*g));
    if (!g) return NULL;
    g->nbs = n;
    g->nba = 0;
    g->aretes = NULL;
    return g;
}

void delete_grapheT(grapheT *g) {
    if (!g) return;
    free(g->aretes);
    free(g);
}

/* Ajout d’arêtes dirigées (i -> j, poids) */
void add_edge_weightT(grapheT *g, int i, int j, int poids) {
    g->nba++;
    triplet *nv = (triplet*)realloc(g->aretes, (size_t)g->nba * sizeof(triplet));
    if (!nv) { /* si realloc échoue, on n’augmente pas nba */
        g->nba--;
        return;
    }
    g->aretes = nv;
    g->aretes[g->nba - 1].i = i;
    g->aretes[g->nba - 1].j = j;
    g->aretes[g->nba - 1].poids = poids;
}

/* Génération aléatoire (densité paramétrée) */
grapheT *remplir_grapheT_densite(int n, double taux) {
    grapheT *g = new_grapheT(n);
    if (!g) return NULL;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            double r = (double)rand() / RAND_MAX;
            if (r < taux) {
                int poids = 1 + rand() % 100;
                add_edge_weightT(g, i, j, poids);
            }
        }
    }
    return g;
}
