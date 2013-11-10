struct Edge
{
    Edge(int _from, int _to, int _w){ from = _from; to = _to; w = _w; }
    int from, to, w;
};

vector<Edge> edges;
vector<int> distances(N_MAX);

void bellman_ford()
{
    fill(distances.begin(), distances.end(), 10000);
    distances[0] = 0;

    bool updated = true;
    while(updated){
        updated = false;
        for(int i = 0; i < edges.size(); ++i)
        {
            if( distances[edges[i].to] > distances[edges[i].from] + edges[i].w){
                distances[edges[i].to] = distances[edges[i].from] + edges[i].w;
                updated = true;
            }
            //if bidirectional:
            if( distances[edges[i].from] > distances[edges[i].to] + edges[i].w){
                distances[edges[i].from] = distances[edges[i].to] + edges[i].w;
                updated = true;
            }
        }
    }
}
