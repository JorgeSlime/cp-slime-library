template <i32 N, bool compute_primes = false>
struct fast_sieve {
    std::bitset<N / 3 + 1> sieve;
    std::vector<i32> primes;
    inline bool is_prime(i32 n) {
        return n == 2 || n == 3 || ((n & 1) && (n % 3) && (sieve[n / 3]));
    }
    void fill_sieve() {
        sieve.set();
        for (i32 p = 5, d = 4, i = 1, sqn = i32(std::sqrt(N)); p <= sqn;
             p += d = 6 - d, i++) {
            if (!sieve[i]) continue;
            for (i32 q = p * p / 3, r = d * p / 3 + (d * p % 3 == 2), s = 2 * p,
                     qe = (i32)sieve.size();
                 q < qe; q += r = s - r)
                sieve[q] = 0;
        }
    }
    std::vector<i32> get_primes() {
        std::vector<i32> ret{2, 3};
        for (i32 p = 5, d = 4, i = 1; p <= N; p += d = 6 - d, i++)
            if (sieve[i]) ret.push_back(p);
        while (!ret.empty() && ret.back() > N) ret.pop_back();
        return ret;
    }
    fast_sieve() {
        fill_sieve();
        if (compute_primes) primes = get_primes();
    }
};
const i32 N = 1000000 + 1;
fast_sieve<N,true> sv; // true or false for primes 
