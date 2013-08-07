#include <iostream>
#include <vector>

using namespace std;

#define abs(a)  ((a) < 0 ? -(a) : (a))

struct Implication
{
    Implication(int _id, char _val) : id(_id), value(_val) {};

    int id; //variable id
    char value; //0 or 1
};

struct VariableValue
{
    VariableValue() : value(-1) {}; //this constructor is important!
    char value; //-1 is unkown, 0 is false, 1 is true
};

struct VariableNode
{
    //imply[0] is the implications when this variable is false
    //imply[1] is the implications when this variable is true
    vector<Implication> imply[2];
};

typedef vector<VariableValue> ValueList;
typedef vector<VariableNode> ImplyList;
typedef vector<Implication>::const_iterator ImplyIter;

//return false if a contradiction occurred
//in both cases, the ValueList will be modified, so caller must save
//it in case the result is false, and then restore the original
bool propagate(ValueList& varlist, const ImplyList& implylist, int id, char value)
{
    if(varlist[id].value != -1) return varlist[id].value == value;
    varlist[id].value = value;

    for(ImplyIter iter = implylist[id].imply[value].begin(); iter != implylist[id].imply[value].end(); ++iter)
    {
        if(!propagate(varlist, implylist, iter->id, iter->value))
            return false;
    }
    return true;
}

//assumes ImplyList is already filled with (empty) entries
void addCondition(ImplyList& implylist, int id1, char value1, int id2, char value2)
{
    implylist[id1].imply[1-value1].push_back( Implication(id2, value2) );
    implylist[id2].imply[1-value2].push_back( Implication(id1, value1) );
}

int main()
{
    while(true)
    {
        int n, m; //variables, conditions
        cin >> n >> m;
        if(!cin.good()) break;
        
        ValueList variables(n+1); //1-based index
        ImplyList implications(n+1);

        for(int i = 0, a, b; i < m; ++i)
        {
            cin >> a >> b;
            addCondition(implications, abs(a), a < 0 ? 0 : 1, abs(b), b < 0 ? 0 : 1);
        }
        
        if(!propagate(variables, implications, 1, 1)) cout << "no" << endl; //Karl must win
        else
        {
            bool success = true;
            for(int i = 2; i <= n; ++i)
            {
                if(variables[i].value != -1) continue; //already filled in
                //backup the state
                ValueList backup(variables);
                if( propagate(variables, implications, i, 1) ) continue;
                //restore state
                variables = backup;
                if( propagate(variables, implications, i, 0) ) continue;
                success = false;
                cout << "no" << endl;
                break;
            }
            if(success) cout << "yes" << endl;
        }
    }
    return 0;
}

