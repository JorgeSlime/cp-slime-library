// Depends of Modular_Integer 
class NcK{   
    public:  
    T N;
    std::vector<Mint> Factorial;
    explicit NcK(T n) : N(n){
        Factorial.assign(N + 1, 1);
        Factorial[0] = 1;
        for(auto i = 1; i <= N; i++){
            Factorial[i] = Factorial[i - 1] * i;
        }
    }
    Mint binom(T n, T k) noexcept{
        if(k > n) return 0;
        Mint numerator = Factorial[n];
        Mint denominator= Factorial[k] * Factorial[n - k];
        return numerator / denominator ;
    }
};
