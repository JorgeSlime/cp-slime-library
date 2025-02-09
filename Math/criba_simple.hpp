const i32 N = 1e6 + 7; 
std::vector<i32> primes; 
std::array<bool,N> vis;
void criba(){
    vis[0] = vis[1] = true; 
    const i32 R = (i32)std::sqrt(N); 
    for(i32 i = 2; i<=R;i++){
        if(!vis[i]){
            for(i64 j = i*i;j<=N;j+=i){
                vis[j] = true;
            }
        }
    }
    for(auto i = 0;i<N;i++){
        if(!vis[i]) primes.emplace_back(i);
    }
}
