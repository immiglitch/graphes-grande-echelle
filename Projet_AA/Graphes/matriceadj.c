#include "matriceadj.h"

#define INF 9999

grapheM *new_grapheM(int n){
    int i,j;
    grapheM *grph = malloc(sizeof(*grph));
    grph->vertices = n;
    grph->adj= malloc(sizeof(int*) * n);
    for (i=0; i<n; i++){
        grph->adj[i] = malloc(n* sizeof(int));
    }
    for (i=0; i < n; i++){
        for (j=0; j < n; j++){
           grph->adj[i][j] = 0;
        }
    }
    return grph;
}

void free_graphM(grapheM *grph){
    int n=grph->vertices;
    for(int i = 0;i < n;i++){
        free(grph->adj[i]);
    }
    free(grph->adj);
    free(grph);
}

void print_graphe(grapheM *grph){
    printf("Nombre de sommets : %d. \n",grph->vertices);
    printf("Matrice d'adjacence : \n");
    int i,j;
    int n=grph->vertices;
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            printf("%d",grph->adj[i][j]);
            printf(j<n-1?"\t":"\n");
            }
    }
}

void add_edge_weight(grapheM *grph, int i, int j, int weight){
    grph->adj[i][j] += weight;
}

void add_edge(grapheM *grph, int i, int j){
    grph->adj[i][j] += 1;
}


/* Fonction permettant de trouver le sommet à plus petite distance parmis les sommets pas encore parcourus,
sans utiliser de file de priorité */
int minDistanceM(grapheM *grph, int dist[], int access[]){
    int n = grph->vertices;
    int min = INF;
    int min_index;
    int i;
    for (int i = 0; i < n; i++){
        if (access[i] == 0 && dist[i] <= min){
            min = dist[i];
            min_index = i;
        }
    }
    return min_index;
}

void CC_mat(grapheM *grph) {
    int n = grph->vertices; // Récupère le nombre de sommets
    int *composante = calloc(n, sizeof(int)); // Tableau pour stocker le numéro de CC de chaque sommet (0 = non visité)
    int num_cc = 0;

    for (int i = 0; i < n; i++) {
        // Si le sommet i n'appartient encore à aucune composante
        if (composante[i] == 0) {
            num_cc++; // On a trouvé une nouvelle composante
            
            // Initialisation de la file pour le parcours BFS
            fifo *file = new_fifo();
            push(file, i);
            composante[i] = num_cc;

            while (!is_empty_fifo(file)) {
                int u = get_first(file); // Récupère le sommet en tête
                enqueue(file); // Retire le sommet de la file

                // On explore tous les voisins possibles dans la matrice
                for (int v = 0; v < n; v++) {
                    // Si une arête existe (poids > 0) et que le voisin n'est pas visité
                    if (grph->adj[u][v] > 0 && composante[v] == 0) {
                        composante[v] = num_cc;
                        push(file, v); // Ajoute le voisin à la file pour exploration future
                    }
                }
            }
        }
    }

    printf("\nNombre total de composantes connexes (Matrice) : %d\n", num_cc);
    free(composante);
}

/* Dijkstra silencieux (pour benchmark) */
void dijkstra_mat_silencieux(grapheM *grph, int src) {
    int n = grph->vertices;
    int *dist   = malloc(n * sizeof(int));
    int *access = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        access[i] = 0;
    }
    dist[src] = 0;

    for (int c = 0; c < n - 1; c++) {
        int u = minDistanceM(grph, dist, access);
        if (u == -1) break;
        access[u] = 1;

        for (int v = 0; v < n; v++) {
            int w = grph->adj[u][v];
            if (!access[v] && w > 0 && dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }
    free(access);
    free(dist);
}