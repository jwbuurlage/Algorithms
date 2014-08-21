#define MAXN 10000001
bool is_prime[MAXN];
vector<int> primes;

void sieve() {
    for(int i = 0; i < MAXN; ++i)
        is_prime[i] = true;

    for(int i = 2; i <= MAXN; ++i) {
        if(!is_prime[i]) continue;
        primes.push_back(i);
        for(int k = i*i; k <= sqrt(MAXN); k += i)
            is_prime[k] = false;
    }
}
