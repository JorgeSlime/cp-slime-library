inline namespace DIVISORES {
//precomputacion de cant de divs 
std::vector<i32> cribe_divisors(const i32 N){
    static std::vector<i32> D(N + 1,0); 
    for(i32 i = 1;i<=N;i++){
        for(i32 j = i;j<=N;j+=i){
            ++D[j];
        }
    }
    return D;
}
//simple divs in O(sqrt(N));
template<typename T> //sorted
std::vector<T> divisors(T n){
    std::vector<T> res = {1}; 
    for(i32 i = 2; i*i <= n;i++){
        if(n%i == 0){
            res.emplace_back(i); 
            if(i != n/i) res.emplace_back(n/i); 
        }
    }
    res.emplace_back(n);
    std::sort(begin(res),end(res));
    return res;
}
//atraves de factores primos 
template<typename T> 
std::vector<T> divisors_by_pf(const std::vector<std::pair<T,i32>>& fact){
    std::vector<T> res={1}; 
    for(auto&& [p,e]:fact){
        i32 tam = sz(res); 
        i64 pp = 1; 
        for(i32 i = 1;i<=e;i++){
            pp *= p; 
            for(i32 j = 0;j<tam;j++){
                res.emplace_back(res[j] * pp);
            }
        }
    }
    return res;
}
//suma de divisores atraves de factores primos
template<typename T>
i64 sum_divs(const std::vector<std::pair<T,i32>>& fact){
    i64 ans = 1; 
    for(auto&&[p,exp] : fact){
        i64 sum = 0, pot = 1; 
        for(i32 i = 0;i<=exp; i++){
            sum += pot; 
            pot *= p; 
        }
        ans *= sum; 
    }
    return ans; 
}
template<typename T>
i32 cnt_divs(const std::vector<std::pair<T,i32>>& fact){
    i32 res = 1; 
    for(auto &&[p,e]:fact){
        res *= (e + 1);
    }
    return res;
}
} // DIVISORES

