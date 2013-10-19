//Tarjan's algorithm for finding Strongly Connected Components
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

//Graph
vector< vector<int> > adj;

//Algorithm internals
vector<int> index;
vector<int> lowlink; //lowest index reachable
vector<bool> inStack; //true iff in tarjanStack
stack<int> tarjanStack;
int newId;

//Output
vector< vector<int> > strongComponents; //collection of vertex sets

void tarjan(int v)
{
    index[v] = newId;
    lowlink[v] = newId;
    ++newId;
    tarjanStack.push(v);
    inStack[v] = true;

    for(int i = 0; i < (int)adj[v].size(); ++i)
    {
        int w = adj[v][i];
        if( index[w] == 0 )
        {
            tarjan(w);
            if( lowlink[w] < lowlink[v] ) lowlink[v] = lowlink[w];
        }
        else if( inStack[w] )
        {
            if( index[w] < lowlink[v] ) lowlink[v] = index[w];
        }
    }

    if( lowlink[v] == index[v] )
    {
        strongComponents.push_back(vector<int>());
        while(true)
        {
            int w = tarjanStack.top();
            strongComponents.back().push_back(w);
            inStack[w] = false;
            tarjanStack.pop();
            if(w == v) break;
        }
    }
}

void run()
{
    int n, m;
    cin >> n >> m;

    adj.clear(); adj.resize(n);
    for(int i = 0; i < m; ++i)
    {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
    }

    //Initialize
    newId = 1;
    index.clear(); index.resize(n+1, 0);
    lowlink.clear(); lowlink.resize(n+1,0);
    inStack.clear(); inStack.resize(n+1, false);
    while(!tarjanStack.empty()) tarjanStack.pop();
    strongComponents.clear();
    //Start
    for(int i = 0; i < n; ++i)
        if(index[i] == 0)
            tarjan(i);

    cout << strongComponents.size() << endl;
}

