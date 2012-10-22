#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

#define N_MAX 6
typedef pair<int, int> pii;

struct Edge
{
  Edge(int _to, int _w)
  {
    to = _to;
    w = _w;
  }

  int to;
  int w;
};

// vector<Vertex> vert;
vector<vector<Edge> > adj(N_MAX);
vector<int> distances(N_MAX);
vector<bool> visited(N_MAX, false);

void dijkstra()
{
  fill(visited.begin(), visited.end(), false);

  priority_queue<pii, vector<pii>, greater<pii> > q; // dist, id
  q.push(make_pair(0, 0));
  pii v;

  while(!q.empty())
  {
    v = q.top();
    q.pop();

    if(visited[v.second])
      continue;

    visited[v.second] = true;
    for(int i = 0; i < adj[v.second].size(); ++i)
      q.push(make_pair(v.first + adj[v.second][i].w, adj[v.second][i].to));

    distances[v.second] = v.first;
  }

  // OUTPUT
  for(int i = 0; i < N_MAX; ++i)
    cout << "Distance to " << i << " is " << distances[i] << endl;
}

int main()
{
  int num_vertices, num_edges, node, distance;
  cin >> num_vertices;
  for(int i = 0; i < num_vertices; ++i)
  {
     cin >> num_edges;
     for(int j = 0; j < num_edges; ++j)
     {
       cin >> node >> distance;
       adj[i].push_back(Edge(node, distance));
     }
  }

  dijkstra();

  return 0;
}
