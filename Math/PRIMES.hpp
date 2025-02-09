inline namespace PRIMES{
//Criba Lineal O(N);
std::vector<i32> criba_lineal(const i32 N = (i32)1e6){
    const i32 LIM = static_cast<i32>(1e6 + 7); 
    static std::vector<i32> primes;
    static std::array<bool,LIM> vis;
    for (i32 i = 2; i < N; ++i) {
        if (!vis[i]) primes.push_back (i);
        for (i32 j = 0; j < (i32)primes.size() && (i * primes[j]*1LL) < N; ++j) {
            vis[i * primes[j]] = 1;
            if (i % primes[j] == 0) break;
        }
    }
    return primes;
}
// decente hasta N = 1e9 -> sqrt(N) 
template <typename T = i64>
std::vector<T> primetable(i64 LIM) {
    ++LIM;
    const i32 S = 32768;
    static i32 done = 2;
    static std::vector<T> primes = {2}, sieve(S + 1);
 
    if (done < LIM) {
        done = LIM;
 
        primes = {2}, sieve.assign(S + 1, 0);
        const i32 R = LIM / 2;
        primes.reserve(i32(LIM / std::log(LIM) * 1.1));
        std::vector<std::pair<i32, i32>> cp;
        for (i32 i = 3; i <= S; i += 2) {
            if (!sieve[i]) {
                cp.emplace_back(i, i * i / 2);
                for (i32 j = i * i; j <= S; j += 2 * i) sieve[j] = 1;
            }
        }
        for (i32 L = 1; L <= R; L += S) {
            std::array<bool, S> block{};
            for (auto& [p, idx]: cp)
                for (i32 i = idx; i < S + L; idx = (i += p)) 
                    block[i - L] = 1;
            for(i32 i  = 0;i<std::min(S,R - L);i++)
                if (!block[i]) primes.emplace_back((L + i) * 2 + 1);
        }
    }
    i32 k = std::lower_bound(begin(primes),end(primes),LIM + 1) - begin(primes);
    return {primes.begin(), primes.begin() + k};
}
// least prime factor table 
std::vector<i32> lpf_table(const i32 N = 1e6 + 1){
    const i32 R = static_cast<i32>(std::sqrt(N)); 
    std::vector<i32> prime(N); 
    for(int i = 1; i <= N ; i++){
        prime[i] = i;
    }
    for(int i = 2; i <= R; i++){
        if(prime[i] == i){
            for(int j = i * i; j <= N; j += i){
                if(prime[j] == j) prime[j] = i;
            }
        }
    }
    return prime;
}
// (R - L  + 1) <= 1e6 -> NMAX = 1e12
std::vector<i64> range_prime(i64 L, i64  R){
    const i32 RA = static_cast<i32>(std::sqrt(R)); 
    std::vector<i64> prime(R - L + 1),ans;
    for(i64 i = L; i <= R; i++) prime[i - L] = 1;
    for(i64 i = 2; i <= RA; i++){
        for(i64 j=std::max(i*i,(L+i-1)/i*i);j<=R;j+=i){
            prime[j - L] = 0;
        }
    }
    for(i64 dos = 2,i = std::max(dos, L); i <= R; i++){
        if(prime[i - L]) ans.emplace_back(i);
    }
    return ans;
}

// N <= 1e6 for cribe 
std::vector<std::pair<i64,i32>> factor(const std::vector<i32>& primes,i64 n){
    std::vector<std::pair<i64,i32>> res; 
    for(auto&& p: primes){
        if(p * p > n) break; 
        i32 exp = 0;
        while(n % p == 0){
            ++exp; 
            n /= p;
        }
        if(exp) res.emplace_back(p,exp); 
    }
    if(n > 1) res.emplace_back(n,1);
    return res;
}
// N >1e6
std::vector<std::pair<i64,i32>> factor_by_lpf(const std::vector<i32>& lpf,i64 n){
    std::vector<std::pair<i64,i32>> res; 
    while(n > 1){
        i32 p = lpf[n]; 
        i32 e = 0; 
        while(n % p == 0){
            ++e; 
            n /= p; 
        }
        res.emplace_back(p,e);
    }
    //if(n > 1) res.emplace_back(n,1);
    return res;
}
} //PRIMES

