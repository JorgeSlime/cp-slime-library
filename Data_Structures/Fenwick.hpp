template <typename T>
struct BinaryIndexedTree{
    i32 N;
    std::vector<T> data;
    BinaryIndexedTree() = default;
    BinaryIndexedTree(i32 size) { init(size); }
    void init(i32 size) {
        N = size + 2;
        data.assign(N + 1, {});
    }
    // get sum of [0,k]
    T sum(i32 k) const {
        if (k < 0) return T{};  // return 0 if k < 0
        T ret{};
        for (++k; k > 0; k -= k & -k) ret += data[k];
        return ret;
    }
    // getsum of [l,r]
    inline T sum(i32 l, i32 r) const { return sum(r) - sum(l - 1); }

    // get value of k use -> bit[k]
    // sirve para corregir la adicion en pos ->add(l,r - bit[l]);
    inline T operator[](i32 k) const { return sum(k) - sum(k - 1); }
    // data[k] += x
    void add(i32 k, T x) {
      for (++k; k < N; k += k & -k) data[k] += x;
    }

    // range add x to [l,r]
    void add_range(i32 l, i32 r, T x) {
      add(l, x);
      add(r + 1, -x);
    }

    // index for sum(i) >= w
    i32 lower_bound(T w) {
        if (w <= 0) return 0;
        i32 x = 0;
        i32 lg = static_cast<i32>(std::log2(N));
        for (i32 k = 1 << lg; k; k >>= 1) {
          if (x + k <= N - 1 && data[x + k] < w) {
            w -= data[x + k];
            x += k;
          }
        }
        return x;
    }

    // index for  sum(i) > w
    i32 upper_bound(T w) {
        if (w < 0) return 0;
        i32 x = 0;
        i32 lg = static_cast<i32>(std::log2(N));
        for (i32 k = 1 << lg; k; k >>= 1) {
          if (x + k <= N - 1 && data[x + k] <= w) {
            w -= data[x + k];
            x += k;
          }
        }
        return x;
    }
};

