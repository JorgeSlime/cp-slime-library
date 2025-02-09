//Depende of INF 
template<typename T,typename GT>
std::pair<std::vector<T>,std::vector<i32>> Dijkstra(std::vector<std::vector<std::pair<GT,GT>>>& G,i32 s){
    auto N=(i32)G.size();
    std::vector<T> dist(N,INF<T>);
    std::vector<int> par(N,-1);
    std::priority_queue<std::pair<T,i32>,std::vector<std::pair<T,i32>>, std::greater<std::pair<T,i32>>> q;
    dist[s]=0;
    q.emplace(0,s);
    while(!q.empty()){
        auto[dv,v]=q.top();
        q.pop();
        if(dv>dist[v]) continue;
        for(auto u:G[v]){
            auto [to,cost]=u;
            if(dist[v]+cost<dist[to]){
                dist[to]=dist[v]+cost;
                par[to]=v;
                q.emplace(dist[to],to);
            }
        }      
    }
    return{dist,par};
} 
std::vector<i32> camino(std::vector<i32> &p,i32 t){
    std::vector<i32> v={t};
    while (p[v.back()] != -1) v.pb(p[v.back()]);
    reverse(all(v));
    return v;
}
//declaracion:
//auto [dist,par]=Dijkstra<type>(G,1);
//if(dist[n]==INF) -1
//auto ans=camino(p,n);
