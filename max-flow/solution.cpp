#include <iostream>
#include <vector>
#include <stack>
#include <climits>
#include <cstring>

using namespace std;

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

vector< vector<Edge*> > adj;
bool* visited;
int node_count;

bool recursiveDFS(int from, int to, vector<Edge*>& path)
{
    if(from == to) return true;
    visited[from] = true;
    for(int i = 0; i < adj[from].size(); ++i)
    {
        Edge* e = adj[from][i];
        if(visited[e->b]) continue;
        if(e->f >= e->c) continue;
        visited[e->b] = true;
        path.push_back(e);
        if( recursiveDFS(e->b, to, path) ) return true;
        path.pop_back();
    }
    return false;
}

bool find_path(int from, int to, vector<Edge*>& output)
{
    output.clear();
    memset(visited, false, node_count * sizeof(bool));
    return recursiveDFS(from, to, output);
}

int max_flow(int source, int sink)
{
    vector<Edge*> p;
    while(find_path(source, sink, p))
    {
        int flow = INT_MAX;
        for(int i = 0; i < p.size(); ++i)
            if(p[i]->c - p[i]->f < flow) flow = p[i]->c - p[i]->f;

        for(int i = 0; i < p.size(); ++i) {
            p[i]->f += flow;
            p[i]->r->f -= flow;
        }
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

  int m = max_flow(0, node_count - 1);

  cout << m << endl;

  for(unsigned int i = 0; i < adj.size(); ++i)
      for(unsigned int j = 0; j < adj[i].size(); ++j)
          delete adj[i][j];
  adj.clear();
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
