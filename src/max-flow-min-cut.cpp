#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <cstring>
#include <algorithm>
#include <limits.h>

// "ASSUMES" DIRECTED GRAPH
// but gets converted to bidirected by "relieving" flow

using namespace std;

#define N_MAX 7

typedef pair<int, int> pii;

struct Edge
{
  Edge(int _from, int _to, int _c)
  {
    from = _from;
    to = _to;
    c = _c;
    f = 0;
  }

  int from;
  int to;
  int c;
  int f;
};

bool adj[N_MAX][N_MAX]; // from to
int c[N_MAX][N_MAX]; // from to
int f[N_MAX][N_MAX]; // from to
int parent[N_MAX];
bool visited[N_MAX];

int max_flow(int source, int target)
{
  memset(f, 0, sizeof(f));

  int flow = 0;

  while(true)
  {
    memset(parent, 0, sizeof(parent));
    memset(visited, false, sizeof(visited));

    queue<int> q;
    q.push(source);
    int current;

    bool found_path = false;

    while(!q.empty())
    {
      current = q.front();
      q.pop();

      visited[current] = true;

      for(int i = 0; i < N_MAX; ++i)
      {
        if(visited[i])
          continue;

        if(adj[current][i])
        {
          if(c[current][i] - f[current][i] == 0)
            continue;

          q.push(i);
          parent[i] = current;

          if(i == target)
          {
            found_path = true;

            int back = target;
            int min_c = c[back][parent[back]] - f[back][parent[back]];

            while(back = parent[back])
              if(c[back][parent[back]] < min_c)
                min_c = c[back][parent[back]] - f[back][parent[back]];

            back = target;
            f[back][parent[back]] -= min_c;
            f[parent[back]][back] += min_c;
            while(back == parent[back])
            {
              f[back][parent[back]] -= min_c;
              f[parent[back]][back] += min_c;
            }
          }
        }
      }
    }

    if(!found_path)
      break;
  }

  return flow;
}

int main()
{
  int num_vertices, num_edges, from, to, weight;
  cin >> num_vertices;
  cin >> num_edges;
  for(int j = 0; j < num_edges; ++j)
  {
    cin >> from >> to >> weight;
    edges.push_back(Edge(from, to, weight));
  }

  max_flow(0, 6);

  return 0;
}
