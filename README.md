# j3-5days

Ce code est un programme en C++ qui résout un problème de parcours de graphe en utilisant l'algorithme de parcours en profondeur (Depth-First Search ou DFS) pour trouver le chemin le plus court, le chemin le plus rapide et le chemin le plus efficace dans un graphe pondéré non orienté.

La structure de données du graphe est définie à l'aide de deux structures, Vertex et Edge. Vertex représente un sommet dans le graphe et contient un vecteur de ses voisins qui sont stockés dans la structure Edge. Edge représente une arête qui connecte deux sommets voisins et contient le coût, la distance et l'efficacité de l'arête.

La fonction createGraph prend en entrée un nom de fichier qui contient les données du graphe au format CSV et renvoie une représentation sous forme de vecteur de la structure Vertex et Edge. La première partie de la fonction lit le fichier ligne par ligne, extrait les informations et calcule le nombre maximal de sommets dans le graphe. Ensuite, elle initialise les sommets du graphe en fonction de ce nombre maximal et les bords en ajoutant les voisins appropriés.

La fonction dfs est la fonction principale qui implémente l'algorithme DFS. Il commence par visiter un sommet de départ et explore récursivement tous ses voisins, en ajoutant le coût, la distance et l'efficacité de chaque bord traversé jusqu'à ce que tous les sommets du graphe soient visités. Il conserve ensuite les chemins minimums pour chaque critère de recherche (coût, distance et efficacité) ainsi que leur coût total respectif. Les résultats sont stockés dans les vecteurs min_path_cost, min_path_dist et min_path_efficiency, respectivement, avec le coût total stocké dans min_cost, min_dist et min_efficiency.

Enfin, le code demande à l'utilisateur de saisir le nom du fichier csv qui contient les données du graphe, commence le timer et utilise la fonction dfs pour résoudre le problème de parcours de graphe. Le résultat est affiché à la fin avec le temps d'exécution total du programme.
