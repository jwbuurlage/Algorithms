#define min(a,b)	((a)<(b) ? (a) : (b))

int main()
{
	int n = 100; //aantal edges
	int d[n][n];

	//initialize heel d op INT_MAX / 3
	//initialize d[a][b] als er een edge is tussen a,b op de edge-waarde

	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			for(int k = 0; k < n; ++k)
				d[j][k] = min( d[j][k] , d[j][i] + d[i][k] );

	return 0;
}
