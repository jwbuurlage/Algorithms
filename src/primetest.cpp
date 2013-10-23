//Calculate a^b % c in log[b] time
int powmod(int a, int b, int c)
{
	int res = 1;
	long long k = a;
	while(b)
	{
		if( b & 1 ) res = (k*res)%c;
		k = (k*k)%c;
		b >>= 1;
	}
	return res;
}

bool isPrime(int n)
{
	if( n < 2 ) return false;
	if( n == 2 ) return true;
	if( (n&1) == 0 ) return false; //if n is even
	//Decompose (n-1) as d*2^s with d odd, so take out the maximum power of 2
	int d = n-1, s = 0;
	while( (d&1) == 0 ){ ++s; d >>= 1; }
	//Now check at least 10 possible witnesses between 2 and n-1 (inclusive)
	//If we check 5 it works on all numbers below 1 million but we check 10 to be sure
	srand(0);
	int count = 10;
	while(count--)
	{
		int a = 2 + (rand() % (n-2)); //#include <cstdlib>
		//Now check if a is a composite witness
		long long k = powmod(a, d, n); //k = a^d % n
		if( k == 1 ) continue; //probably prime
		bool prime = false;
		for(int r = 0; r < s; ++r)
		{
			//k is now a^(d*2^r) % n
			if( k == n-1 ){ prime = true; break; } //for primes, this MUST become -1 mod n at some point for 0 <= r < s
			k = (k*k)%n;
		}
		if( prime ) continue; //probably prime
		return false; //definitely composite
	}
	return true;
}

int gcd(int a, int b)
{
	if( b == 0 ) return a;
    if( a < 0 ) a = -a;
    if( b < 0 ) b = -b;
	int r;
	while(b)
	{
		int r = a % b;
		a = b;
		b = r;
	}
	return a;
}
