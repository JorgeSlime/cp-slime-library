// incluye test de primalidad millet rabin 
inline namespace POLLAR_RHO{
// Random number generator
const uint64_t SEED = std::chrono::steady_clock::now().time_since_epoch().count();
std::mt19937_64 rng(SEED);
template<typename T>
inline T rnd(T low, T high) {
    return std::uniform_int_distribution<T>{low, high}(rng);
}
struct m64 { //Mongotmery Modular 
    using u128 = __uint128_t;
    inline static u64 m, r, n2; // r * m = -1 (mod 1<<64), n2 = 1<<128 (mod m)
    static void set_mod(u64 m) {
        assert((m & 1) == 1);
        m64::m = m;
        n2 = -u128(m) % m;
        r = m;
        for(i32 i = 0 ; i<5 ; i++) r *= 2 - m * r;
        r = -r;
        assert(r * m == -1ull);
    }
    static u64 reduce(u128 b) { return (b + u128(u64(b) * r) * m) >> 64; }
    u64 x;
    m64() : x(0) {}
    m64(u64 x) : x(reduce(u128(x) * n2)){};
    u64 val() const {
      u64 y = reduce(x);
      return y >= m ? y - m : y;
    }
    m64 &operator+=(m64 y) {
      x += y.x - (m << 1);
      x = (i64(x) < 0 ? x + (m << 1) : x);
      return *this;
    }
    m64 &operator-=(m64 y) {
      x -= y.x;
      x = (i64(x) < 0 ? x + (m << 1) : x);
      return *this;
    }
    m64 &operator*=(m64 y) {
      x = reduce(u128(x) * y.x);
      return *this;
    }
    m64 operator+(m64 y) const { return m64(*this) += y; }
    m64 operator-(m64 y) const { return m64(*this) -= y; }
    m64 operator*(m64 y) const { return m64(*this) *= y; }
    bool operator==(m64 y) const {
      return (x >= m ? x - m : x) == (y.x >= m ? y.x - m : y.x);
    }
    bool operator!=(m64 y) const { return not operator==(y); }
    m64 pow(u64 n) const {
        m64 y = 1, z = *this;
        for (; n; n >>= 1, z *= z)
            if (n & 1) y *= z;
        return y;
    }
};
bool primetest(const uint64_t x) { //Miller rabin 
    using u64 = uint64_t;
    if (x == 2 or x == 3 or x == 5 or x == 7) return true;
    if (x % 2 == 0 or x % 3 == 0 or x % 5 == 0 or x % 7 == 0) return false;
    if (x < 121) return x > 1;
    const u64 d = (x - 1) >> __builtin_ctzll(x - 1);
    m64::set_mod(x);
    const m64 one(1), minus_one(x - 1);
    auto ok = [&](u64 a) {
        auto y = m64(a).pow(d);
        u64 t = d;
        while (y != one and y != minus_one and t != x - 1) y *= y, t <<= 1;
        if (y != minus_one and t % 2 == 0) return false;
        return true;
    };
    if (x < (1ull << 32)) {
        for (u64 a: {2, 7, 61})
            if (not ok(a)) return false;
    } else {
        for (u64 a: {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
            if (x <= a) return true;
            if (not ok(a)) return false;
        }
    }
    return true;
}
i64 rho(i64 n, i64 c) {
    m64::set_mod(n);
    assert(n > 1);
    const m64 cc(c);
    auto f = [&](m64 x) { return x * x + cc; };
    m64 x = 1, y = 2, z = 1, q = 1;
    i64 g = 1;
    const i64 m = 1LL << (std::__lg(n) / 5); // ?
    for (i64 r = 1; g == 1; r <<= 1) {
        x = y;
        for(i32 _= 0;_<r;_++)  y = f(y);
        for (i64 k = 0; k < r and g == 1; k += m) {
            z = y;
            for(i32 _=0;_<std::min(m,r-k);_++) y = f(y), q *= x - y;
            g = std::gcd(q.val(), n);
        }
    }
    if (g == n) do {
        z = f(z);
        g = std::gcd((x - z).val(), n);
    }while (g == 1);
    return g;
}
 
i64 find_prime_factor(i64 n) {
    assert(n > 1);
    if (primetest(n)) return n;
    for(i32 i= 0; i<100; i++) {
      i64 m = rho(n, rnd<i64>(0,n));
      if (primetest(m)) return m;
      n = m;
    }
    return -1;
}
std::vector<std::pair<i64, i32>> factor(i64 n) {
    assert(n >= 1);
    std::vector<std::pair<i64, int>> pf;
    for(i32 p = 2;p<100;p++){
        if (p * p > n) break;
        if (n % p == 0) {
          i64 e = 0;
          do { n /= p, e += 1; } while (n % p == 0);
          pf.emplace_back(p, e);
        }
    }
    while (n > 1) {
      i64 p = find_prime_factor(n);
      i64 e = 0;
      do { n /= p, e += 1; } while (n % p == 0);
      pf.emplace_back(p, e);
    }
    std::sort(begin(pf),end(pf));
    return pf;
}
//sum of divisores 
} //POLLAR_RHO

