#include <iostream>
#include <vector>
#include <limits.h>
#include <string.h>

using namespace std;

struct Edge;

struct Edge
{
  Edge(int _a, int _b, int _c, int _f) { 
    a = _a; b = _b; c = _c; f = _f; 
  }
  ~Edge() { };

  int a;
  int b;
  int c;
  int f;
  Edge* r;
};

struct Node
{
  Node(int _x, int _y, int _m, int _i)
  {
    x = _x; y = _y; m = _m; i = _i;
  }
  ~Node() { }

  int x;
  int y;
  int m;
  int i;
};

vector< vector<Edge*> > adj;
bool* visited;
int node_count;

void reset_visited()
{
  memset(visited, false, node_count * sizeof(bool));
}

void reset_flow()
{
  for(int i = 0; i < adj.size(); ++i)
    for(int j = 0; j < adj[i].size(); ++j)
      adj[i][j]->f = 0;
}

vector<Edge*>* find_path(int from, int to, vector<Edge*>* current_path)
{
  if(!current_path) current_path = new vector<Edge*>();
  if(from == to)
    return current_path;
  // DFS
  visited[from] = true;
  for(int i = 0; i < adj[from].size(); ++i) {
    Edge* e = adj[from][i];
    int rest = e->c - e->f;
    vector<Edge*>* result = 0;
    if(rest > 0 && !visited[e->b]) {
      current_path->push_back(e);
      visited[e->b] = true;
      result = find_path(e->b, to, current_path); 
    }
    if(result) return result;
  }
  current_path->pop_back();
  return 0;
}

int max_flow(int source, int sink)
{
  vector<Edge*>* p = find_path(source, sink, 0);
  while(p) {
    int flow = INT_MAX;
    for(int i = 0; i < p->size(); ++i)
      if((*p)[i]->c - (*p)[i]->f < flow) flow = (*p)[i]->c - (*p)[i]->f;

    for(int i = 0; i < p->size(); ++i) {
      (*p)[i]->f += flow;
      (*p)[i]->r->f -= flow;
    }

    reset_visited();
    p = find_path(source, sink, 0);
  }

  int total_flow = 0;
  for(int i = 0; i < adj[source].size(); ++i)
  {
    total_flow += adj[source][i]->f;
  }
  return total_flow;
}

void add_edge(int a, int b, int c)
{
  Edge* e = new Edge(a, b, c, 0);
  Edge* re = new Edge(b, a, 0, 0);
  e->r = re;
  re->r = e;
  adj[a].push_back(e);
  adj[b].push_back(re);
}

void run()
{
  node_count = 6;
  adj.clear();
  adj.resize(node_count);

  add_edge(0, 5, 3);
  add_edge(0, 1, 3);
  add_edge(1, 5, 2);
  add_edge(1, 2, 3);
  add_edge(5, 4, 2);
  add_edge(2, 4, 4);
  add_edge(2, 3, 2);
  add_edge(4, 3, 3);

  visited = new bool[node_count];
  reset_visited();

  int m = max_flow(0, node_count - 1);

  cout << m << endl;

  delete[] visited;
}

int main()
{
  int runs;
  cin >> runs;
  while(runs--) {
    run();
  }
  return 0;
}
