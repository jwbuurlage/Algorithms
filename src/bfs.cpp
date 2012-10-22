vector<vector<Edge> > adj(N_MAX);
vector<int> parent(N_MAX, -1);
vector<int> distances(N_MAX);
vector<bool> visited(N_MAX, false);

void bfs(int root, int target) {//Distance:distances[target], Path:Volg parent[target] tot -1
    fill(distances.begin(), distances.end(), INT_MAX/2);//Init
    fill(visited.begin(), visited.end(), false);
    distances[root]=0;
    parent[root]=-1;
    visited[root]=true;

    queue<int> q;//DFS: stack<int> q;
    q.push(root);
    while(!q.empty()) {
        int curr=q.front();//DFS: int curr=q.top();
        q.pop();
        int depth=distances[curr];
        for(int i=0; i<adj[curr].size(); i++) {
            int neigh=adj[curr][i].to;
            if(!visited[neigh]) {
                visited[neigh]=true;
                parent[neigh]=curr;
                distances[neigh]=depth+1;
                if(neigh == target)    return;
                q.push(neigh);
            }
        }
    }
}
