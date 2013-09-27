
//Longest common subsequence.
//IS NOT longest common subSTRING
//substring is consecutive characters, subsequence is not

int table[1024][1024];

int LCSLength(const string& word1, const string& word2)
{
    for(int i = 0; i <= (int)word1.size(); ++i) table[i,0] = 0;
    for(int j = 0; j <= (int)word2.size(); ++j) table[0,j] = 0;

    for(int i = 1; i < (int)word1.size(); ++i)
    {
        for(int j = 1; j < (int)word2.size(); ++j)
        {
            if( word1[i-1] == word2[j-1] ) table[i][j] = table[i-1][j-1] + 1;
            else table[i][j] = max( table[i-1][j] , table[i][j-1] );
        }
    }
    return table[word1.size()][word2.size()];
}

//Get the actual LCS by backtracking through the table
string word1;
string word2;

string getLCS(int i, int j)
{
    if( i == 0 || j == 0 ) return "";
    if( word1[i-1] == word2[j-1] ) return getLCS(i-1, j-1) + word1[i-1];
    if( table[i][j-1] > table[i-1][j] ) return getLCS(i, j-1);
    else return getLCS(i-1, j);
}
