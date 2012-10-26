//
// Rabin Miller primality test
// Important: The long long variables really must be long long
// Even if the prime being tested is only one million, the numbers
// used in the calculations are much larger.
//
// Also includes a function that calculates
// a^b % c  in log[b] time
//

#include <cstdlib> //for rand

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
		int a = 2 + (rand() % (n-2));
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
	//if a or b can be negative:
	//a = abs(a);
	//b = abs(b);
	int r;
	while(b)
	{
		int r = a % b;
		a = b;
		b = r;
	}
	return a;
}

//
//
//TEST SECTION
//
//

#include <math.h>

bool isPrimeBrute(int n)
{
	if( n < 2 ) return false;
	if( n == 2 ) return true;
	if( (n&1) == 0 ) return false;

	int maxn = (int)sqrt(n) + 1;
	for(int d = 3; d <= maxn; d += 2)
	{
		if( n % d == 0 ) return false;
	}
	return true;
}

#include <iostream>

using namespace std;

int main()
{
	//int n;
	//cout << "Please enter a number to test for primality (max 2³¹):" << endl;
	//cin >> n;
	//bool prime = isPrime(n);
	//cout << "Result: " << n << " is ";
	//if(prime) cout << "prime!" << endl;
	//else cout << "not prime." << endl;

	//cout << "Nearby primes:" << endl;
	//for(int k = max(n-20,2); k < n+20; ++k)
	//	if( isPrime(k) ) cout << k << endl;

	cout << "Testing all primes from 2 till 1.000.000.000" << endl;
	int count = 1; //we start at 3 so we can do +2 every time
	for(int i = 3; i < 1000000000; i += 2)
	{
		if( isPrime(i) )
		{
			++count;
			//Check if it was correct. Note that Miller can only mismatch composites as primes, not the other way around
			if( !isPrimeBrute(i) ) cout << "MISMATCH at number " << i << ". The Rabin Miller test detected it as prime but it is not!" << endl;
		}
		if( (i % 1000000) == 1 ) cout << "Now at " << i << ". Found " << count << " primes so far." << endl;
	}
	cout << "Done!" << endl;
	cout << "Found " << count << " primes under 1.000.000.000" << endl;

	cin.get();
	return 0;
}
