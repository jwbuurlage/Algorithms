int distanceTable[1002][1002];

int levDistance(const string& word1, const string& word2)
{
    for(unsigned int i = 0; i <= word1.length(); ++i)
        distanceTable[i][0] = i;
    for(unsigned int j = 0; j <= word2.length(); ++j)
        distanceTable[0][j] = j;

    for(unsigned int i = 1; i <= word1.length(); ++i)
        for(unsigned int j = 1; j <= word2.length(); ++j)
            distanceTable[i][j] = min(min(distanceTable[i-1][j]+1, distanceTable[i][j-1]+1),
                                distanceTable[i-1][j-1] + (word1[i-1]!=word2[j-1] ? 1 : 0) );

    return distanceTable[word1.length()][word2.length()];
}
