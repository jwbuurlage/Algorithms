#include <string>
#include <vector>

using namespace std;

int KMPsearch(const string& word, const string& text)
{
	vector<int> table(word.size()+1, 0);
	
	//First fill the table
	//NOTE: If you search for the SAME word in different texts
	//then only fill this table ONCE
	
	unsigned int i = 1;
	unsigned int j = 0;
	while(i < word.size())
	{
		if( word[i] == word[j] )
		{
			++i;
			++j;
			table[i] = j;
		}
		else if( j > 0 )
		{
			j = table[j];
		}
		else
		{
			++i;
		}
	}

	//If we want the amount of matches
	int matchcount = 0;

	//Now search the string
	i = 0;
	j = 0;
	while(i < text.size())
	{
		if( text[i] == word[j] )
		{
			++i;
			++j;
			if( j == word.size() )
			{
				//MATCH FOUND!
				++matchcount;
				//Match is at text[i-j] till text[i-1] both inclusive
				//output position if needed
				//cout << "Match " << matchcount << " at position " << (i-j) << endl;

				j = table[j];
			}
		}
		else if( j > 0 )
		{
			j = table[j];
		}
		else
		{
			++i;
		}
	}
	return matchcount;
}
