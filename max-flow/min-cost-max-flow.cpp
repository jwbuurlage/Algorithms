struct Edge
{
    Edge(int _a, int _b, int _c, int _f, int _w) { 
        a = _a; b = _b; c = _c; f = _f; w = _w; 
    }
    ~Edge() { };
    int a; //from
    int b; //to
    int c; //capacity
    int f; //flow
    int w; //weight
    Edge* r;
};

const int MAX_NODES = 2000;
const int MAX_DIST = 2000000; //do not choose INT_MAX because you are adding weights to it
vector<Edge*> adj[MAX_NODES];
int distances[MAX_NODES];
Edge* parents[MAX_NODES];

int node_count;

bool find_path(int from, int to, vector<Edge*>& output)
{
    fill(distances, distances+nodecount, MAX_DIST);
    fill(parents, parents+nodecount, (Edge*)0);
    distances[from] = 0;

    bool updated = true;
    while(updated)
    {
        updated = false;
        for(int j = 0; j < nodecount; ++j)
            for(int k = 0; k < (int)adj[j].size(); ++k){
                Edge* e = adj[j][k];
                if( e->f >= e->c ) continue;
                if( distances[e->b] > distances[e->a] + e->w )
                {
                    distances[e->b] = distances[e->a] + e->w;
                    parents[e->b] = e;
                    updated = true;
                }
            }
    }
    output.clear();
    if(distances[to] == MAX_DIST) return false;
    int cur = to;
    while(parents[cur])
    {
        output.push_back(parents[cur]);
        cur = parents[cur]->a;
    }
    return true;
}

int min_cost_max_flow(int source, int sink)
{
    int total_cost = 0;
    vector<Edge*> p;
    while(find_path(source, sink, p))
    {
        int flow = INT_MAX;
        for(int i = 0; i < p.size(); ++i)
            if(p[i]->c - p[i]->f < flow) flow = p[i]->c - p[i]->f;

        int cost = 0;
        for(int i = 0; i < p.size(); ++i) {
            cost += p[i]->w;
            p[i]->f += flow;
            p[i]->r->f -= flow;
        }
        cost *= flow; //cost per flow
        total_cost += cost;
    }
    return total_cost;
}

void add_edge(int a, int b, int c, int w)
{
    Edge* e = new Edge(a, b, c, 0, w);
    Edge* re = new Edge(b, a, 0, 0, -w);
    e->r = re;
    re->r = e;
    adj[a].push_back(e);
    adj[b].push_back(re);
}

void run()
{
    //node_count
    //add_edge
    cout << min_cost_max_flow(source, sink) << endl;
    for(int i = 0; i < nodecount; ++i){
        for(unsigned int j = 0; j < adj[i].size(); ++j)
            delete adj[i][j];
        adj[i].clear();
    }
}
