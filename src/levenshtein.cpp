int costs[1002][1002];

int levDistance(const string& word1, const string& word2)
{
    for(unsigned int i = 0; i <= word1.length(); ++i)
        costs[i][0] = i; //removal_cost * i
    for(unsigned int j = 0; j <= word2.length(); ++j)
        costs[0][j] = j; //insertion_cost * j

	int a, b, c;
    for(unsigned int i = 1; i <= word1.length(); ++i)
        for(unsigned int j = 1; j <= word2.length(); ++j)
        {
			a = costs[i-1][j]+1; //removal cost of word1[i-1]
			b = costs[i][j-1]+1; //insertion cost of word2[j-1]
			c = costs[i-1][j-1] + (word1[i-1]!=word2[j-1] ? 1 : 0); //replacement cost
            costs[i][j] = min(min(a, b), c);
        }

    return costs[word1.length()][word2.length()];
}
