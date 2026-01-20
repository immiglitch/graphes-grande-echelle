#include "brin.h"
#include "fifo.h"
#include "heap.h"
#include "matriceadj.h"
#include "triplets.h"


grapheB* convertir_triplets_vers_brin(grapheT *gt) {
    grapheB *gb = malloc(sizeof(grapheB));
    gb->nbs = gt->nbs;
    gb->nba = gt->nba;
    gb->S = calloc(gt->nbs + 1, sizeof(int));
    gb->B = malloc(gt->nba * sizeof(int));
    gb->W = malloc(gt->nba * sizeof(int));

    // 1. Compter le nombre d'arêtes sortantes par sommet
    for (int k = 0; k < gt->nba; k++) gb->S[gt->aretes[k].i + 1]++;
    // 2. Transformer S en index cumulés
    for (int i = 0; i < gt->nbs; i++) gb->S[i+1] += gb->S[i];
    // 3. Remplir B et W en utilisant un tableau temporaire de positions
    int *pos = malloc(gt->nbs * sizeof(int));

    for(int i=0; i < gt->nbs; i++) pos[i] = gb->S[i];

    for (int k = 0; k < gt->nba; k++) {
        int u = gt->aretes[k].i;
        int p = pos[u]++;
        gb->B[p] = gt->aretes[k].j;
        gb->W[p] = gt->aretes[k].poids;
    }
    free(pos);
    return gb;
}

void CC_brin(grapheB *g) {
    int *marked = calloc(g->nbs, sizeof(int));
    int count = 0;
    fifo *q = new_fifo();
    for (int i = 0; i < g->nbs; i++) {
        if (!marked[i]) {
            count++;
            push(q, i); marked[i] = 1;
            while (!is_empty_fifo(q)) {
                int u = get_first(q); enqueue(q);
                // On ne parcourt QUE les voisins réels, pas toute la matrice
                for (int j = g->S[u]; j < g->S[u+1]; j++) {
                    int v = g->B[j];
                    if (!marked[v]) { marked[v] = 1; push(q, v); }
                }
            }
        }
    }
    printf("Nombre de composantes connexes (Brin) : %d\n", count);
    free(marked);
}

void dijkstra_brin(grapheB *g, int src) {
    int n = g->nbs;
    int *dist = malloc(n * sizeof(int));
    Tas *tas = creer_tas(n);
    
    for (int i = 0; i < n; i++) {
        dist[i] = (i == src) ? 0 : INF;
        tas->array[i] = new_noeudTas(i, dist[i]);
        tas->pos[i] = i;
    }
    tas->taille = n;
    decrease_value(tas, src, 0);

    while (!is_empty_tas(tas)) {
        noeudTas *minNode = extract_min(tas);
        int u = minNode->v;
        for (int j = g->S[u]; j < g->S[u+1]; j++) {
            int v = g->B[j];
            int w = g->W[j];
            if (is_in_tas(tas, v) && dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                decrease_value(tas, v, dist[v]);
            }
        }
    }
    free(dist);
}

void free_grapheB(grapheB *g) {
    free(g->S); free(g->B); free(g->W); free(g);
}