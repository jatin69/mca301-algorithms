/*
 * Author : Jatin Rohilla
 * Date   : Nov-2018
 *
 * Editor   : Dev c++ 5.11
 * Compiler : g++ 5.1.0
 * flags    : -std=c++14
 *
 
Objective : Implement Dijkstra's Single source shortest Path (SSSP) algorithm

Appropriate Data structure :

Requirements :
1. Need smallest element at all stages
2. Need to be able to update the value of the vertex node

Consideration :

1. Normal array : ( REJECTED )
will take order N to extract min

2. priority_queue : ( REJECTED )
will get min at all stages
But does not support updation of random vertices because it is a list

3. Set : ( REJECTED )
will get min at all stages because set is sorted
also supports linear access, so updation is also possible
But overall time taken is very much
 
4. Min Heap : ( ACCEPTED )
will get min i.e. the top element
also supports update key

TRICK :

Min Heap in STL is implemented by priority queue.
So we are back to consideration number 2.
In practice, if we choose the
insert-again version of dikstra's ( doable with priority queue )
instead of
update-key version ( will need update key )
the time complexity turns out to be better
Because priority queue is a logN data structure
and a few extra items do not degrade its expected performance.

Refer -
https://stackoverflow.com/a/31123108/5371996
https://stackoverflow.com/questions/9255620/why-does-dijkstras-algorithm-use-decrease-key

so, we use
priority_queue of STL ( a heap, but without the decrease-key operation)
with the
insert-again version of Djikstra's algorithm.

This version works because we keep track of the extracted-vertex,
once it has been extracted as min, we can ignore all its future occurences in queue.

Time complexity is :
Refer - https://youtu.be/xhG2DyCX3uA?t=4716

|V| * extractMin + |E| * decrease key

Array           : O(V^2)
Binary Heap     : O( (V+E) logV)
Fibonacci Heap  : O( VlogV + E)

Note that -
A decrease key takes logV in a binary heap, but here
we are using priority_queue.
Interestingly, the amortized cost of inserting ( and popping )
an element from priority queue is also logN
so the resultant time complexity is same as that of a binary heap.

so we have here, (V+E)logV
Because edges > vertices, we can take (E+E)logV = 2E(logV)
i.e. Time = O( ElogV )

*/

#include <iostream>
#include <list>
#include <queue>
#include <vector>
#include <limits.h>
//#include <typeinfo>

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
  // Because it is an undirected graph
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

// Djikstra's Single source shortest Path Algorithm
void Graph::shortest_path(int src) {

  // using priority queue to reduce the time complexity

  /*
    priority queue stores a pair of integers
	first  : distance from source to this vertex
	second : the vertex label
  */
  
// using the default nature of greater on a custom type `pii` : not a good practice
// priority_queue<pii, vector<pii>, greater<pii>> pq;
  
//  readily providing greater<> functionality to custom type : STL way
//  auto comparer = [](const auto& a, const auto& b) { return a.first > b.first; };
//  priority_queue<pii, vector<pii>, decltype(comparer)> pq(comparer);
//  cout << "\n\n" << typeid(comparer).name() << "\n\n";

//  readily providing greater<> functionality to custom type with struct as template type
  struct comparer{
  	bool operator()(const pii& a, const pii& b) { return a.first > b.first; }
  };
  priority_queue<pii, vector<pii>, comparer> pq;

  // distance to each vertex
  vector<int> dist(V, INT_MAX);

  dist[src] = 0;             // distance from source to source always zero
  pq.push({dist[src], src}); // pair of (distance from source to V, V)

  vector<int> parent(V); // create a parent to store path info
  parent[src] = -1;      // parent of source is base case

  // In Djikstra, vertex is extracted only once, thereafter it is not updated
  vector<bool> firstExtraction(V, true);

  // loop until all vertices have been extracted
  while (!pq.empty()) {

    // extract minimum distance vertex from pq
    int u = pq.top().second;    // .second gives the vertex label
    pq.pop();
    firstExtraction[u] = false;

    // iterate all adjacent vertices to `u`
    for (auto x : adjList[u]) {

      int v = x.first;      // dest of edge
      int w = x.second;     // weight of the edge

      // if already extracted, do not proceed
      // update cost of all adjacent vertices
      if (firstExtraction[v] && (dist[u] + w < dist[v])) {
        dist[v] = dist[u] + w;
		parent[v] = u;
		
		pq.push({dist[v], v});
		
		/* if `v` is not already present in pq, simply push it
	     * else
		 *     1. either update the value (not doable with this data structure)
		 *     2. reinsert in priority queue ( Accepted approach )
		 */
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

  cout << "****** Dijkstra's SSSP Algorithm ******\n\n";
  
  int V = 9;
  Graph g(V, "undirected");

  // sample undirected graph
  // g.add(src, dest, weight)
  g.add_edge(0, 1, 4);
  g.add_edge(0, 7, 8);
  g.add_edge(1, 2, 8);
  g.add_edge(1, 7, 11);
  g.add_edge(2, 3, 7);
  g.add_edge(2, 8, 2);
  g.add_edge(2, 5, 4);
  g.add_edge(3, 4, 9);
  g.add_edge(3, 5, 14);
  g.add_edge(4, 5, 10);
  g.add_edge(5, 6, 2);
  g.add_edge(6, 7, 1);
  g.add_edge(6, 8, 6);
  g.add_edge(7, 8, 7);

  g.shortest_path(0);

  return 0;
}

/* Output -

****** Dijkstra's SSSP Algorithm ******

  Vertex    Cost    Path
     0        0     0
     1        4     0 1
     2       12     0 1 2
     3       19     0 1 2 3
     4       21     0 7 6 5 4
     5       11     0 7 6 5
     6        9     0 7 6
     7        8     0 7
     8       14     0 1 2 8

*/
