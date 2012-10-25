#include <iostream>

#include <limits.h>
#include <math.h>

#include <cstring>
#include <string>

#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <list>
#include <map>

// assumes bidirected graph, adjust accordingly

using namespace std;

#define N_MAX 7

vector<vector<int> > adj;
vector<bool> visited(N_MAX, false);
vector<int> parent(N_MAX, 0);

void cycle_detection() {

  stack<int> s;
  s.push(0);
  int current;
  while(!s.empty())
  {
    current = s.top();
    s.pop();

    for(int i = 0; i < adj[current].size(); ++i)
    {
      if(visited[i])
        if(parent[current] != i)
          cout << "cycle!!!" << endl;

      s.push(adj[current][i]);
      parent[i] = current;

      visited[i] = true;
    }
  }
}

int main() {

  cycle_detection();

	return 0;
}
