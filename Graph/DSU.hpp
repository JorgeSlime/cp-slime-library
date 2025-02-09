struct DSU {
    std::vector<i32> fa, siz;
    DSU() {}
    DSU(i32 n) {
        init(n);
    }
    void init(i32 n) {
        fa.resize(n);
        std::iota(begin(fa),end(fa),0);
        //sum -> iota 
        siz.assign(n, 1);
    }
    i32 find(i32 x) {
        while (x != fa[x]) {
            x = fa[x] = fa[fa[x]];
        }
        return x;
    }
    bool same(i32 x, i32 y) {
        return find(x) == find(y);
    }
    bool unite(i32 x, i32 y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        if(siz[x] < siz[y]) std::swap(x,y);
        siz[x] += siz[y];
        // sum[x]+= sum[y];
        fa[y] = x;
        return true;
    }
    i32 size(i32 x) {
        return siz[find(x)];
    }
};

