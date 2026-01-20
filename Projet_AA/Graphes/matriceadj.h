#ifndef MAT_H
#define MAT_H
#include "main.h"
#include "fifo.h"
#include "matriceadj.h"


#define INF 9999

// Structure de graphe avec matrice d'adjacence //

typedef struct grapheM{
    int vertices;
    int **adj;
}grapheM;


grapheM *new_grapheM(int n);
void free_graphM(grapheM *grph);
void print_graphe(grapheM *grph);
void add_edge_weight(grapheM *grph, int i, int j, int weight);
void add_edge(grapheM *grph, int i, int j);

int minDistanceM(grapheM *grph, int dist[], int access[]);
void dijkstra_mat_silencieux(grapheM *grph, int src);
void CC_mat(grapheM *grph);

#endif