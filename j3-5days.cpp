#include <iostream>      // bibliothèque d'entrées/sorties
#include <fstream>       // bibliothèque de gestion de fichiers
#include <sstream>       // bibliothèque de gestion de chaînes de caractères
#include <vector>        // bibliothèque de gestion de tableaux dynamiques
#include <unordered_set> // bibliothèque de gestion de tableaux de hachage
#include <ctime>         // bibliothèque de gestion du temps

using namespace std;

// Structure de données représentant une arête d'un graphe
struct Edge
{
    int dest;         // l'identifiant du sommet destination
    int cost;         // le coût de l'arête
    int dist;         // la distance entre les deux sommets
    float efficiency; // l'efficacité de l'arête (coût/distance)
};

// Structure de données représentant un sommet d'un graphe
struct Vertex
{
    int id;                 // l'identifiant du sommet
    vector<Edge> neighbors; // la liste des arêtes adjacentes à ce sommet
};

// Fonction qui crée un graphe à partir d'un fichier CSV
vector<Vertex> createGraph(string filename)
{
    // Ouverture du fichier
    ifstream file(filename);
    if (!file)
    {
        cout << "Erreur lors de l'ouverture du fichier." << endl;
        exit(-1);
    }

    // Lecture du fichier ligne par ligne
    string line;
    int max_vertex_id = 0;
    while (getline(file, line))
    {
        // Traitement de chaque ligne pour récupérer les informations de l'arête
        istringstream iss(line);
        string origin_str, dest_str, cost_str, dist_str;
        getline(iss, origin_str, ';');
        getline(iss, dest_str, ';');
        getline(iss, cost_str, ';');
        getline(iss, dist_str, ';');

        // Conversion des chaînes de caractères en entiers
        int origin_index = stoi(origin_str) - 1;
        int dest_index = stoi(dest_str) - 1;
        int cost = stoi(cost_str);
        int dist = stoi(dist_str);

        // Mise à jour de l'identifiant maximum de sommet
        max_vertex_id = max(max_vertex_id, max(origin_index, dest_index));
    }
    file.close();

    // Création des sommets du graphe
    vector<Vertex> graph(max_vertex_id + 1);
    for (int i = 0; i <= max_vertex_id; i++)
    {
        graph[i].id = i;
    }

    // Ajout des arêtes dans le graphe
    file.open(filename);
    while (getline(file, line))
    {
        istringstream iss(line);
        string origin_str, dest_str, cost_str, dist_str;
        getline(iss, origin_str, ';');
        getline(iss, dest_str, ';');
        getline(iss, cost_str, ';');
        getline(iss, dist_str, ';');

        // Conversion des chaînes de caractères en entiers
        int origin_index = stoi(origin_str) - 1;
        int dest_index = stoi(dest_str) - 1;
        int cost = stoi(cost_str);
        int dist = stoi(dist_str);

        // Association des arretes à un sommet
        Edge a = {dest_index, cost, dist, (float)cost / (float)dist};
        Edge b = {origin_index, cost, dist, (float)cost / (float)dist};
        graph[origin_index].neighbors.push_back(a);
        graph[dest_index].neighbors.push_back(b);
    }
    file.close();
    return graph;
}

/*La fonction commence par vérifier si tous les sommets ont été visités. 
Si c'est le cas, elle parcourt tous les voisins du sommet actuel pour 
vérifier s'il existe une arête reliant le sommet actuel au sommet de départ.
Si c'est le cas, elle met à jour les valeurs minimales de coût, de distance
et d'efficacité trouvées jusqu'à présent et stocke le chemin correspondant.

Si tous les sommets n'ont pas encore été visités, la fonction parcourt les
voisins du sommet actuel et vérifie si le sommet voisin n'a pas déjà été visité.
Si le sommet voisin n'a pas été visité, il est ajouté à l'ensemble des
sommets visités, et la fonction est appelée récursivement avec le sommet voisin
comme nouveau sommet actuel.

Une fois que toutes les itérations sont terminées pour le sommet actuel, 
le sommet voisin est supprimé de l'ensemble des sommets visités pour que
la fonction puisse explorer d'autres chemins possibles.*/
void dfs(int start, int curr, int total_cost, int total_dist, float total_efficiency, unordered_set<int> &visited, vector<Vertex> &graph, int &min_cost, vector<int> &min_path_cost, int &min_dist, vector<int> &min_path_dist, float &min_efficiency, vector<int> &min_path_efficiency)
{
    if (visited.size() == graph.size())
    {
        for (Edge &e : graph[curr].neighbors)
        {
            if (e.dest == start)
            {

                if (total_cost + e.cost < min_cost)
                {
                    min_cost = total_cost + e.cost;
                    min_path_cost.clear();
                    min_path_cost.push_back(start);
                    for (int v : visited)
                    {
                        min_path_cost.push_back(v);
                    }
                }

                if (total_dist + e.dist < min_dist)
                {
                    min_dist = total_dist + e.dist;
                    min_path_dist.clear();
                    min_path_dist.push_back(start);
                    for (int v : visited)
                    {
                        min_path_dist.push_back(v);
                    }
                }

                if (total_efficiency + e.efficiency < min_efficiency)
                {
                    min_efficiency = total_efficiency + e.efficiency;
                    min_path_efficiency.clear();
                    min_path_efficiency.push_back(start);
                    for (int v : visited)
                    {
                        min_path_efficiency.push_back(v);
                    }
                }

                return;
            }
        }
    }

    for (Edge &e : graph[curr].neighbors)
    {
        if (visited.count(e.dest) == 0)
        {
            visited.insert(e.dest);
            dfs(start, e.dest, total_cost + e.cost, total_dist + e.dist, total_efficiency + e.efficiency, visited, graph, min_cost, min_path_cost, min_dist, min_path_dist, min_efficiency, min_path_efficiency);
            visited.erase(e.dest);
        }
    }
}

int main()
{
    string file;

    // Acquisition des donnees
    cout << "Entrez le nom du fichier csv que vous voulez (assurez vous qu'il soit dans ce repertoire) : ";
    cin >> file;
    // Début du timer
    clock_t timerStart = clock();

    vector<Vertex> graph = createGraph(file);
    int start = graph[0].id;
    unordered_set<int> visited;
    visited.insert(start);
    int min_cost = std::numeric_limits<int>::max();
    vector<int> min_path_cost;

    int min_dist = std::numeric_limits<int>::max();
    vector<int> min_path_dist;

    float min_efficiency = std::numeric_limits<float>::max();
    vector<int> min_path_efficiency;

    dfs(start, start, 0, 0, 0.0, visited, graph, min_cost, min_path_cost, min_dist, min_path_dist, min_efficiency, min_path_efficiency);

    cout << "---------------COUT----------------" << endl;
    cout << "Chemin le plus court trouvé :" << endl;
    cout << min_path_cost[0] + 1;
    for (int i = 1; i < min_path_cost.size(); i++)
    {
        cout << " -> " << min_path_cost[i] + 1;
    }
    cout << endl;
    cout << "Cout total: " << min_cost << endl;
    cout << "------------------------------------" << endl;

    cout << endl;

    cout << "--------------DISTANCE--------------" << endl;
    cout << "Chemin le plus court trouvé :" << endl;
    cout << min_path_dist[0] + 1;
    for (int i = 1; i < min_path_dist.size(); i++)
    {
        cout << " -> " << min_path_dist[i] + 1;
    }
    cout << endl;
    cout << "Distance total: " << min_dist << endl;
    cout << "---------------------------------------" << endl;

    cout << endl;

    cout << "---------------EFFICIENCY--------------" << endl;
    cout << "Chemin le plus court trouvé :" << endl;
    cout << min_path_efficiency[0] + 1;
    for (int i = 1; i < min_path_efficiency.size(); i++)
    {
        cout << " -> " << min_path_efficiency[i] + 1;
    }
    cout << endl;
    cout << "Efficience total (cout/distance) : " << min_efficiency << endl;
    cout << "---------------------------------------" << endl;

    // Fin du timer
    clock_t timerStop = clock();

    // Calcul de la durée d'exécution en secondes
    double duration = double(timerStop - timerStart) / CLOCKS_PER_SEC;

    // Affichage de la durée d'exécution
    cout << endl
         << "Temps du programme: " << duration * 1000 << " milliseconds" << endl;
    return 0;
}
