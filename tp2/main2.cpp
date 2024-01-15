//Morais Pereira David
//J'ai repris votre code de Graph.hpp et j'ai reppris en grande partie et remixer votre code de dom-cplex.cpp
//j'ai mis un decompte de 5 min car c'est ecris dans le pdf que l'on a le droit de mettre 5 min par fichier

#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <random>
#include <algorithm>
#include <set>
#include <map>
#include "graph.hpp"
#include <ilcplex/ilocplex.h>

using namespace std;

void save(const string s, const set<vert> dom) {
    ofstream outfile(s);
    if (outfile.is_open()){
        for(vert i : dom) {
            outfile << i << endl;
        }
    }
    outfile.close();
}

set<vert> Solution(const Graph &g) {
    IloEnv env;

    map<vert, IloNumVar> variables;
    IloModel model(env);

    for (vert i : g.vertices()) {
        variables[i] = IloNumVar(env, 0, 1, ILOINT);
        model.add(variables[i]);
    }

    // Ajouter les contraintes
    for (vert v : g.vertices()) {
        for (vert u : g.neighbors(v)) {
            model.add(variables[v] + variables[u] <= 1);
        }
    }

    // Maximiser le nombre de sommets sélectionnés
    IloExpr objective(env);
    for (vert i : g.vertices()) {
        objective += variables[i];
    }
    model.add(IloMaximize(env, objective));

    // Résolution du modèle
    IloCplex cplex(model);
    cplex.setOut(env.getNullStream());
    cplex.setParam(IloCplex::Param::TimeLimit, 300);
    bool solved = cplex.solve();

    // Récupération de l'ensemble des sommets indépendants
    set<vert> dom;
    
    if (solved) {
        for (vert i : g.vertices()) {
            if (cplex.getValue(variables[i]) > .5) {
                dom.insert(i);
            }
        }
    }

    env.end();
    return dom;
}


int main(){
    vector<string> files={
        "00030_000109_random_udg.edges",
        "00100_001156_qatar_udg.edges",
        "00300_001484_euronight_8nn.edges",
        "01000_002980_greece_del.edges",
        "03000_010884_paris_6nn.edges",
        "10000_024317_italy_4nn.edges",
        "20000_107456_jupiter_9nn.edges",
        "30000_089977_usnight_del.edges",
        "40000_119960_protein_del.edges"
    };
    vector<string> soluce={
        "00030_000109_random_udg.ind",
        "00100_001156_qatar_udg.ind",
        "00300_001484_euronight_8nn.ind",
        "01000_002980_greece_del.ind",
        "03000_010884_paris_6nn.ind",
        "10000_024317_italy_4nn.ind",
        "20000_107456_jupiter_9nn.ind",
        "30000_089977_usnight_del.ind",
        "40000_119960_protein_del.ind"
    };

    for(long unsigned int i=0; i<files.size(); i++){
        Graph g(files[i]);
        set<vert> l2 = Solution(g);
        cout << "Saved dominating set of size " << l2.size() << " to " << soluce[i] << endl;
        save(soluce[i], l2);
    }

    return 0;
}