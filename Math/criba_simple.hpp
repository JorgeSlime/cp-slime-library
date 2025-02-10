constexpr i32 N = 1e6 + 7; 
const size_t TS = (N / std::log(N)) * 2;
std::vector<i32> primes; 
std::bitset<N> used;
void criba(){
    primes.reserve(TS);
    used[0] = used[1] = true; 
    const i32 R = i32(std::sqrt(N)); 
    for(i32 i{2}; i<=R;i++){
        if(not used[i]){
            for(i64 j{i * i};j<=N;j+=i){
                used[j] = true;
            }
        }
    }
    for(i32 i{2};i<N;i++){
        if(not used[i]) 
            primes.emplace_back(i);
    }
}

