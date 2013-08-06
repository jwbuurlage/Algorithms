#include <iostream>
#include <vector>
#include <limits.h>
#include <queue>
#include <string.h>
#include <algorithm>
#include <math.h>
#include <iomanip>
#include <cmath>

#define N_MAX 51
using namespace std;

struct Edge;

struct Edge
{
  Edge(int _a, int _b, int _w)
  {
    a = _a; b = _b; w = _w;
  }
  ~Edge() { }

  int a;
  int b;
  int w;
};

typedef pair<double, int> pii;

vector< vector<Edge*> > adj(N_MAX);
vector<bool> visited(N_MAX, false);
int node_count;

void add_edge(int a, int b, double w)
{
  Edge* e = new Edge(a, b, w);
  Edge* re = new Edge(b, a, w);
  adj[a].push_back(e);
  adj[b].push_back(re);
}

double dijkstra(int source, int target)
{
  fill(visited.begin(), visited.end(), false);
  priority_queue<pii, vector<pii>, greater<pii> > q; // dist id

  q.push(make_pair(0.0, source));
  pii v;
  while(!q.empty())
  {
    v = q.top();
    q.pop();

    if(visited[v.second]) continue;
    visited[v.second] = true;

    if(v.second == target) break;

    for(int i = 0; i < adj[v.second].size(); ++i)
      q.push(make_pair(v.first + adj[v.second][i]->w, adj[v.second][i]->b));
  }
    
  return v.first;
}

void run()
{
  // dijkstra
}

int main()
{
  int runs;
  cin >> runs;
  while(runs--)
  {
    run();
  }
  return 0;
}
