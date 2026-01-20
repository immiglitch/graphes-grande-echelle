#include "fifo.h"

int is_empty_fifo(fifo *F){
    if (F->taille == 0 && F->debut == NULL && F->fin == NULL)
        return 1;
    else
        return 0;
}

fifo *new_fifo(){
   fifo *F = malloc(sizeof(*F));
   if (F == NULL)
        printf("Erreur d'allocation.");
   F->taille = 0;
   F->debut = NULL;
   F->fin = NULL;
   return F;
}

void push(fifo *F, int s){
    if (F == NULL)
        printf ("La file n'existe pas - On ne peut empiler.");
    element *e = malloc(sizeof(*e));
    if (e == NULL)
        printf("Erreur d'allocation");
    e->valeur = s;
    e->suivant = NULL;
    if (F->taille == 0){
        F->debut = e;
        F->fin = e;
    }
    else{
        F->fin->suivant = e;
        F->fin = e;
    }
    F->taille+=1;
}

void enqueue(fifo *F){
    element *e = malloc(sizeof(*e));
    if (F == NULL || F->taille == 0)
        printf("Erreur dépilement.");
    e = F->debut;
    if (F->taille == 1)
        F->debut = F->fin = NULL;
    else
        F->debut= F->debut->suivant;
   F->taille -= 1;
}

int get_first(fifo *F){
    if (is_empty_fifo(F) == 1){
        printf("La file est vide. Pas de première valeur.");
        return 0;
    }
    else
        return F->debut->valeur;
}

void print_fifo(fifo *F){
   element *e;
   if (F == NULL)
        printf("Erreur; pas d'affichage possible. \n");
   e = F->debut;
   while (e != NULL){
      printf("%d ", e->valeur);
      e = e->suivant;
   }
   printf("\n");
}