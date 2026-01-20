# Graphes à grande échelle — Composantes connexes & Dijkstra (C)

Projet universitaire (UE **Algorithme Avancée**) : étude de l’impact des **structures de données** sur les performances (mémoire/temps) pour des graphes pondérés de grande taille (**> 10 000 nœuds**).

Rapport: 'Rapport_AA.pdf'
Présentation: 


## Objectifs
- Comparer plusieurs représentations de graphe pour le passage à l’échelle :
  - **Vecteur de triplets** (intermédiaire pour générer le graphe)
  - **Matrice d’adjacence** (simple mais très coûteuse en mémoire)
  - **Brins / CSR (Compressed Sparse Row)** (compact et efficace)
- Implémenter et mesurer :
  - **Composantes connexes** via **BFS**
  - **Plus courts chemins** via **Dijkstra** (optimisé avec **tas binaire min-heap**)

## Résumé des résultats (exemple n=10 000, densité 1%)
- Matrice : ~381 Mo, CC ~0.17s, Dijkstra ~0.66s  
- CSR (Brins) : ~7.67 Mo, CC ~0.0026s, Dijkstra ~0.01s  
➡️ CSR ~50x plus léger et ~66x plus rapide (dans ces conditions)

## Technologies
- Langage : **C**
- Mesure temps : `clock()`
- Structures : file FIFO (BFS), tas binaire (Dijkstra)

## Organisation (fichiers principaux)

- `triplets.c` : génération/stockage intermédiaire en triplets
- `matriceadj.c` : graphe en matrice d’adjacence
- `brin.c` : conversion triplets -> **CSR** et parcours voisins
- `fifo.c` : file pour BFS
- `heap.c` : **min-heap** pour Dijkstra (extract-min / decrease-key)
- `main.c` : génération + benchmarks (10k / 15k / 20k nœuds)

## Compilation
### Option A — avec Makefile
make


### Option A — compilation simple
gcc -O2 -Wall -Wextra -o graphe main.c triplets.c matriceadj.c brin.c fifo.c heap.c

```bash
