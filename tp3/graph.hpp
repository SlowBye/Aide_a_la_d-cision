#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <algorithm> // For max
#include <vector>
#include <queue>
#include <cassert>

typedef long long int vert; // Type of a vertex

class Graph {
  std::map<vert, std::set<vert>> adj;
  
public:
  Graph() {
  }  
  void addVertex(vert v) {
    adj[v];
  }
  
  Graph(std::string filename) {
    std::ifstream infile(filename);
    vert u,v;
    while(infile >> u >> v) {
      addEdge(u,v);
    }
  }

  void addEdge(vert u, vert v) {
    if(u != v) {
      adj[u].insert(v);
      adj[v].insert(u);
    }
  }
  
  bool containsVertex(vert v) const {
    return adj.count(v) != 0;
  }
  
  bool containsEdge(vert u, vert v) const {
    return containsVertex(u) && adj.at(u).count(v) != 0;
  }
  
  int degree(vert v) const {
    return containsVertex(v) ? adj.at(v).size() : -1;
  }
  
  int maxDegree() const {
    int ret = -1;
    for(const auto &[v, neigh] : adj) {
      ret = std::max(ret,(int)neigh.size());
    }
    
    return ret;
  }
  
  int countVertices() const {
    return adj.size();
  }
  
  int countEdges() const {
    int ret = 0;
    for(const auto &[v, neigh] : adj) {
      ret += neigh.size();
    }
    assert(ret % 2 == 0);
    return ret / 2;
  }
  
  void removeEdge(vert u, vert v) {
    if(containsEdge(u,v)) {
      adj.at(u).erase(v);
      adj.at(v).erase(u);
    }
  }
  
  void removeVertex(vert v) {
    if(containsVertex(v)) {
      std::set<vert> neigh(adj.at(v)); // Copy because changing the data structure invalidades the iterator
      for(vert u : neigh) {
        removeEdge(u,v);
      }
      adj.erase(v);
    }
  }

  void clear() {
    adj.clear();
  }
  
  void renameVertex(vert v0, vert v1) {
    for(vert v : adj.at(v0)) {
      adj.at(v).erase(v0);
      adj.at(v).insert(v1);          
    }
    adj[v1] = adj[v0];
    adj.erase(v0);
  }

  std::set<vert> vertices() const {
    std::set<vert> ret;
    for(const auto &[v, neigh] : adj) {
      ret.insert(v);
    }
    return ret;
  }
  
  std::set<std::pair<vert,vert>> edges() const {
    std::set<std::pair<vert,vert>> ret;
    
    for(const auto &[v, neigh] : adj) {
      for(vert u : neigh) {
        if(u < v)
          ret.insert(std::make_pair(u,v));
      }
    }
    return ret;    
  }
  
  std::set<vert> neighbors(vert v) const {
    return adj.at(v);
  }

  std::set<vert> commonNeighbors(vert u, vert v) const {
    std::set<vert> nu = neighbors(u);
    std::set<vert> nv = neighbors(v);
    std::set<vert> ret;
    std::set_intersection(nu.begin(), nu.end(),
                                 nv.begin(), nv.end(),
                                 std::inserter(ret, ret.begin()));
    return ret;
  }
  
  Graph compressed() const {
    std::map<vert,vert> conv;
    int i = 0;
    
    for(vert v : vertices()) {
      conv[v] = i;
      i++;
    }
    
    Graph ret;

    for(const auto &[v, neigh] : adj) {
      ret.adj[conv[v]];
      for(vert u : neigh)
        ret.adj.at(conv[v]).insert(conv[u]);
    }
    
    return ret;
  }
  
  std::vector<vert> bfs(vert v, int maxv = 0) const {
    std::set<vert> visited;
    std::vector<vert> ret;
    std::queue<vert> fifo;
    
    if(maxv == 0)
      maxv = countVertices();
    
    fifo.push(v);
    while(!fifo.empty() && ret.size() < (size_t) maxv) {
      vert u = fifo.front();
      fifo.pop();
      if(visited.count(u) != 0)
        continue;
      ret.push_back(u);
      visited.insert(u);
      for(vert w : neighbors(u))
        fifo.push(w);
    }
    
    return ret;
  }
};


#endif