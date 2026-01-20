#include "heap.h"

noeudTas * new_noeudTas(int v, int dist){
    noeudTas *node = malloc(sizeof(*node));
    node->v = v;
    node->dist = dist;
    return node;
}

Tas * creer_tas(int n){
    Tas *tas = malloc(sizeof(*tas));
    tas->pos = (int *) malloc(n * sizeof(int));
    tas->taille = 0;
    tas->capacite = n;
    tas->array = malloc(n *sizeof(noeudTas*));
    return tas;
}

void echange_noeud(noeudTas **a, noeudTas **b){
    noeudTas * t = *a;
    *a = *b;
    *b = t;
}


/* Une fonction pour entasser un noeud dans un tas */
void entasser(Tas* tas, int idx){
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;
    if (left < tas->taille && tas->array[left]->dist < tas->array[smallest]->dist)
        smallest = left;
    if (right < tas->taille && tas->array[right]->dist <tas->array[smallest]->dist )
        smallest = right;
    if (smallest != idx){
        noeudTas *smnode = tas->array[smallest];
        noeudTas *idxnode = tas->array[idx];
        tas->pos[smnode->v] = idx;
        tas->pos[idxnode->v] = smallest;
        echange_noeud(&tas->array[smallest], &tas->array[idx]);
        entasser(tas, smallest);
    }
}

int is_empty_tas(struct Tas* tas){
    return tas->taille == 0;
}

/* Fonction pour extraire le minimum d'un tas. */
noeudTas* extract_min(Tas* tas){
    if (tas -> taille == 0)
        return NULL;
    noeudTas* root = tas->array[0];
    noeudTas* lastnode = tas->array[tas->taille - 1];
    tas->array[0] = lastnode;
    tas->pos[root->v] = tas->taille-1;
    tas->pos[lastnode->v] = 0;
    tas->taille -= 1;
    entasser(tas, 0);
    return root;
}

/* Fonction pour diminuer la valeur d'un certain noeud. */
void decrease_value(struct Tas* tas, int v, int dist){
    int i = tas->pos[v];
    tas->array[i]->dist = dist;
    while (i && tas->array[i]->dist < tas->array[(i - 1) / 2]->dist){
        tas->pos[tas->array[i]->v] = (i-1)/2;
        tas->pos[tas->array[(i-1)/2]->v] = i;
        echange_noeud(&tas->array[i], &tas->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

/* Fonction pour tester si un noeud est dans un tas. */
int is_in_tas(Tas *tas, int v){
    if (tas->pos[v] < tas->taille)
        return 1;
    return 0;
}
