#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <cstring>
#include <algorithm>

// GAAT ER VANUIT DAT JE EEN CONNECTED GRAPH HEBT
// anders toepassingen op elke component

using namespace std;

int N_MAX = 7;
typedef pair<int, int> pii;

struct Edge
{
  Edge(int _from, int _to, int _w)
  {
    from = _from;
    to = _to;
    w = _w;
  }

  bool operator <(const Edge& b) const
  {
    return w < b.w;
  }

  bool operator >(const Edge& b) const
  {
    return b.w < w;
  }

  int from;
  int to;
  int w;
};

vector<Edge> edges;
vector<int> group(N_MAX);
vector<vector<int> > groups(N_MAX);

void kruskal()
{
  for(int i = 0; i < N_MAX; ++i)
  {
    groups[i].push_back(i);
    group[i] = i;
  }

  vector<Edge> mst;
  int total_length = 0;

  stack<Edge> s;

  const Edge* e;
  while(!s.empty())
  {
    e = &s.top();

    if(group[e->from] != group[e->to])
    {
      int size = groups[group[e->from]].size();
      for(int i = 0; i < size; ++i)
      {
        group[groups[group[e->from]][i]] = group[e->to];
        groups[group[e->to]].push_back(groups[group[e->from]][i]);
      }
      groups[group[e->from]].empty();

      mst.push_back(*e);
      total_length += e->w;

      cout << groups[e->to].size() << endl;

      // we're done if every vertex is in one single group
      if(groups[e->to].size() == N_MAX)
        break;
    }

    s.pop();
  }

  // OUTPUT
  cout << "Length: " << total_length << endl;
  for(int i = 0; i < mst.size(); ++i)
    cout << "Edge: " << mst[i].from << " " << mst[i].to << endl;
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

  N_MAX = num_vertices;

  kruskal();

  return 0;
}
