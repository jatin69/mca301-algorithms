/*
 * Author : Jatin Rohilla
 * Date   : Nov-2018
 *
 * Editor   : Dev c++ 5.11
 * Compiler : g++ 5.1.0
 * flags    : -std=c++14
 *

Objective : Implement BellmanFord's Single source shortest Path (SSSP) algorithm

*/

#include <iostream>
#include <list>
#include <queue>
#include <vector>
#include <limits.h>

#include <iomanip>
using namespace std;

typedef pair<int, int> pii;
typedef list<pii> lpii;

class Graph {

private:
  int V;         // no of vertices
  int E;         // no of Edges
  lpii *adjList; // adjacent List Representation
  void print_path(vector<int> &, int);
  string graphType; // directed or undirected

public:
  Graph(int, string);
  ~Graph();
  void add_edge(int, int, int);
  void shortest_path(int);
};

Graph::Graph(int _V, string _graphType) {
  this->V = _V;
  this->E = 0;
  this->graphType = _graphType;
  adjList = new lpii[_V];
}

Graph::~Graph() { delete[] adjList; }

void Graph::add_edge(int u, int v, int w) {

  // Because it is a directed graph
  adjList[u].push_back({v, w});

  if ((this->graphType).compare("undirected") == 0) {
    adjList[v].push_back({u, w});
  }

  // edge count increases
  (this->E)++;
}

void Graph::print_path(vector<int> &parent, int v) {
  if (v == -1) {
    return;
  }
  print_path(parent, parent[v]);
  cout << v << ' ';
}

// BellmanFord's Single source shortest Path Algorithm
void Graph::shortest_path(int src) {

  int V = this->V;
  int E = this->E;

  // distance to each vertex
  vector<int> dist(V, INT_MAX);
  dist[src] = 0; // distance from source to source always zero

  vector<int> parent(V); // create a parent to store path info
  parent[src] = -1;      // parent of source is base case

  // outer loop executes V-1 times
  for (int count = 1; count <= V - 1; ++count) {

    // Inner loop executes E times
    // Adjacency List Representation of the Graph, essentially traverses all E's
    for (int i = 0; i < V; ++i) {
      for (auto x : adjList[i]) {

        int u = i;        // source of the edge
        int v = x.first;  // dest of edge
        int w = x.second; // weight of the edge

        if (dist[u] != INT_MAX && (dist[u] + w < dist[v])) {
          dist[v] = dist[u] + w;
          parent[v] = u;
        }
      }
    }
  }

  // traverse all Edges once more,
  // if anything gets updated, it contains a negative cycle.
  for (int i = 0; i < V; ++i) {
    for (auto x : adjList[i]) {
      int u = i;
      int v = x.first;
      int w = x.second;

      if (dist[u] != INT_MAX && (dist[u] + w < dist[v])) {
        cerr << "\nNegative Cycle Detected\n";
        exit(0);
      }
    }
  }

  /* print the final result */
  cout << setw(8) << "Vertex" << setw(8) << "Cost";
  cout << setw(8) << "Path";
  cout << "\n";
  for (int i = 0; i < V; i++) {
    cout << setw(6) << i << setw(9) << dist[i];
    cout << setw(6);
    print_path(parent, i);
    cout << "\n";
  }
}

int main() {

  cout << "****** Bellman Ford's SSSP Algorithm ******\n\n";

  int V = 5;
  Graph g(V, "directed");

  // sample directed graph
  // g.add(src, dest, weight)
  g.add_edge(0, 1, -1); // A->B
  g.add_edge(0, 2, 4);  // A->C
  g.add_edge(1, 2, 3);  // B->C
  g.add_edge(1, 3, 2);  // B->D
  g.add_edge(1, 4, 2);  // A->E
  g.add_edge(3, 2, 5);  // D->C
  g.add_edge(3, 1, 1);  // D->B
  g.add_edge(4, 3, -3); // E->D

  g.shortest_path(0);

  return 0;
}

/* Output -

****** Bellman Ford's SSSP Algorithm ******

  Vertex    Cost    Path
     0        0     0
     1       -1     0 1
     2        2     0 1 2
     3       -2     0 1 4 3
     4        1     0 1 4

*/
