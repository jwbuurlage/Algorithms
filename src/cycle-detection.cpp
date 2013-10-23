// assumes bidirected graph, adjust accordingly

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
