#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "fifo.h"
#include "heap.h"
#include "matriceadj.h"
#include "triplets.h"
#include "brin.h"

#define SECTION 4


void exporter_resultats(int n, double t_mat, double t_brin, double mem_mat, double mem_brin) {
    FILE *f = fopen("resultats_benchmark.csv", "a");
    if (f == NULL) return;

    // Si le fichier est vide, on écrit l'en-tête
    fseek(f, 0, SEEK_END);
    if (ftell(f) == 0) {
        fprintf(f, "n;temps_mat;temps_brin;mem_mat;mem_brin\n");
    }
    fprintf(f, "%d;%.4f;%.4f;%.2f;%.2f\n", n, t_mat, t_brin, mem_mat, mem_brin);
    fclose(f);
}


int main() {
    srand(time(NULL));

    #if SECTION == 1
    // --- TESTS BASIQUES MATRICE ---
    printf("SECTION 1 : Tests Matrice d'adjacence\n");
    grapheM *grph = new_grapheM(6);
    add_edge_weight(grph, 0, 1, 10);
    add_edge_weight(grph, 1, 2, 8);
    add_edge_weight(grph, 0, 3, 7);
    add_edge_weight(grph, 1, 3, 2);
    add_edge_weight(grph, 3, 2, 4);
    print_graphe(grph);
    CC_mat(grph);
    free_graphM(grph);

    #elif SECTION == 2
    // --- TESTS TRIPLETS ---
    printf("SECTION 2 : Tests Triplets\n");
    grapheT *grphT = new_grapheT(6);
    add_edge_weightT(grphT, 0, 1, 10);
    add_edge_weightT(grphT, 0, 2, 5);
    delete_grapheT(grphT);

    #elif SECTION == 3
    printf("SECTION 3 : Tests Structure Brin (Tableau de brins / CSR)\n");

    // 1. Création d'un petit graphe de test via Triplets
    grapheT *gTriSimple = new_grapheT(6);
    add_edge_weightT(gTriSimple, 0, 1, 10);
    add_edge_weightT(gTriSimple, 0, 2, 5);
    add_edge_weightT(gTriSimple, 1, 3, 1);
    add_edge_weightT(gTriSimple, 2, 1, 3);
    add_edge_weightT(gTriSimple, 2, 3, 8);
    add_edge_weightT(gTriSimple, 3, 4, 2);
    add_edge_weightT(gTriSimple, 4, 5, 4);

    // 2. Conversion vers la structure Brin
    grapheB *gBrinSimple = convertir_triplets_vers_brin(gTriSimple);

    // 3. Test des Composantes Connexes (CC)
    printf("\n--- Test des Composantes Connexes ---\n");
    CC_brin(gBrinSimple);

    // 4. Test de Dijkstra
    printf("\n--- Test Dijkstra (Sommet source : 0) ---\n");
    dijkstra_brin(gBrinSimple, 0);
    printf("Dijkstra Brin terminé avec succès.\n");

    // 5. Libération de la mémoire
    delete_grapheT(gTriSimple);
    free_grapheB(gBrinSimple);

    #elif SECTION == 4
    // ==========================================================
    //        PROJET FINAL : ANALYSE DES STRUCTURES DE GRAPHES  
    //           (Matrice d'adjacence vs Tableau de Brins)      
    // ==========================================================
    printf("==========================================================\n");
    printf("        PROJET FINAL : ANALYSE DES STRUCTURES DE GRAPHES  \n");
    printf("==========================================================\n\n");

    // Tailles de tests supérieures à 10 000 sommets
    int tailles[] = {10000, 15000, 20000}; 
    int nb_tests = sizeof(tailles) / sizeof(tailles[0]);
    double densite = 0.01; // Densité de 1% (graphe creux)
    int source = 0;

    for (int t = 0; t < nb_tests; t++) {
        int n = tailles[t];
        printf(">>> TEST POUR N = %d SOMMETS (Densité: %.1f%%)\n", n, densite * 100.0);
        printf("----------------------------------------------------------\n");

        // 1. Génération des données de base via Triplets
        grapheT *gTri =  remplir_grapheT_densite(n, densite);
        int m = gTri->nba;

        // 2. Initialisation de la Matrice avec protection contre le manque de RAM
        double estimation_mo = (double)(n * n * sizeof(int)) / (1024 * 1024);
        grapheM *gMat = NULL;
        
        // On n'alloue la matrice que si elle consomme moins de 2 Go
        if (estimation_mo < 2048.0) { 
            gMat = new_grapheM(n);
            for(int k = 0; k < m; k++) {
                add_edge_weight(gMat, gTri->aretes[k].i, gTri->aretes[k].j, gTri->aretes[k].poids);
            }
        }

        // 3. Initialisation du Tableau de Brins (CSR) par conversion
        grapheB *gBrin = convertir_triplets_vers_brin(gTri);

        // --- AFFICHAGE DE LA MÉMOIRE UTILISÉE ---
        printf("[Mémoire] Matrice: %.2f Mo | Brin: %.2f Mo\n", 
                estimation_mo, (double)((n + 1 + 2 * m) * sizeof(int)) / (1024 * 1024));

        clock_t debut, fin;
        double t_mat, t_brin;

        // --- PARTIE A : COMPOSANTES CONNEXES (CC) ---
        printf("[CC] Calcul en cours...\n");
        if (gMat) {
            debut = clock();
            CC_mat(gMat);
            fin = clock();
            t_mat = (double)(fin - debut) / CLOCKS_PER_SEC;
            printf("  > Temps CC Matrice : %.4f s\n", t_mat);
        }

        debut = clock();
        CC_brin(gBrin);
        fin = clock();
        t_brin = (double)(fin - debut) / CLOCKS_PER_SEC;
        printf("  > Temps CC Brin    : %.4f s\n", t_brin);

        // --- PARTIE B : PLUS COURT CHEMIN (DIJKSTRA) ---
        printf("\n[Dijkstra] Calcul depuis le sommet %d...\n", source);
        if (gMat) {
            debut = clock();
            dijkstra_mat_silencieux(gMat, source);
            fin = clock();
            t_mat = (double)(fin - debut) / CLOCKS_PER_SEC;
            printf("  > Temps Dijkstra Matrice : %.4f s\n", t_mat);
        }

        debut = clock();
        dijkstra_brin(gBrin, source);
        fin = clock();
        t_brin = (double)(fin - debut) / CLOCKS_PER_SEC;
        printf("  > Temps Dijkstra Brin    : %.4f s\n", t_brin);
        
        printf("\n");

        exporter_resultats(n, t_mat, t_brin, estimation_mo, (double)((n + 1 + 2 * m) * sizeof(int)) / (1024 * 1024));

        // Libération de la mémoire
        if (gMat) free_graphM(gMat);
        delete_grapheT(gTri);
        free_grapheB(gBrin);
    }

    printf("==========================================================\n");
    printf("              FIN DU BENCHMARK COMPARATIF                 \n");
    printf("==========================================================\n");
    #endif

    return 0;
}

