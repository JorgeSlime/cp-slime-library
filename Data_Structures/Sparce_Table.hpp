struct SparseTable {
    i32 n;
    vector<vector<i32>> st;
    SparseTable(const vector<i32>& arr) {
        n =(i32)arr.size();
        i32 logn = 32 - __builtin_clz(n);
        st.assign(n, vector<i32>(logn));
        for (i32 i = 0; i < n; i++) {
            st[i][0] = arr[i];
        }
        for (i32 j = 1; (1 << j) <= n; j++) {
            for (i32 i = 0; i + (1 << j) <= n; i++) {
                st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
    i32 query(i32 l, i32 r) {
        i32 j = 31 - __builtin_clz(r - l + 1);
        return min(st[l][j], st[r - (1 << j) + 1][j]);
    }
};
