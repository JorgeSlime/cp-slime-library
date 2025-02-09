inline namespace MOD_INT{
template<typename T,T MOD>
requires std::unsigned_integral<T>
class Modular_Integer{
public:
    using mod = Modular_Integer;
    constexpr Modular_Integer(): value{0} {}
    constexpr Modular_Integer(T v) : value(norm(v % T{MOD})){}
    constexpr static T norm(T x) {
        if ((x >> (8 * sizeof(T) - 1) & 1) == 1) {
            x += MOD;  
        }
        if (x >= MOD) {
            x -= MOD;
        }
        return x;
    }
    constexpr T val(){
        return value;
    }
    constexpr mod& operator+=(const mod& other) & {
        value = norm(value + other.value);
        return *this;
    }
    constexpr mod& operator-=(const mod& other) & {
        value = norm(value - other.value);
        return *this;
    }
    constexpr mod& operator*=(const mod& other) & {
        value = value * other.value % MOD;
        return *this;
    }
    constexpr mod& operator/=(const mod& other) & {
        return *this *= other.inv(); 
    }
    constexpr mod operator-() const {
        mod res;
        res.value = norm(-value);
        return res;
    }
    constexpr mod inv() const {
        return binpow(MOD - 2);
    }
    constexpr mod binpow(i64 exp) const {
        mod result = 1;
        mod base = value;
        while (exp > 0) {
            if (exp & 1) result *= base;
            base *= base;
            exp>>=1;
        }
        return result;
    }
    friend constexpr mod operator+(mod a, const mod& b) { return a += b; }
    friend constexpr mod operator-(mod a, const mod& b) { return a -= b; }
    friend constexpr mod operator*(mod a, const mod& b) { return a *= b; }
    friend constexpr mod operator/(mod a, const mod& b) { return a /= b; }
    friend constexpr bool operator==(mod a, mod& b) { return a.value == b.value;}
    friend constexpr bool operator!=(mod a, mod& b) { return a.value != b.value;}
    friend constexpr bool operator<(mod a, mod& b) { return a.value < b.value;}
    friend constexpr bool operator>(mod a, mod& b) { return a.value > b.value;}
    // output
    friend constexpr std::ostream& operator<<(std::ostream& os, const mod& m) {
        return os << m.value;
    }
    // input
    friend constexpr std::istream& operator>>(std::istream& is, mod& m) {
        T temp;
        is >> temp;
        m.value = norm(temp % MOD);
        return is;
    }
private: 
    T value;
};
template<uint32_t M> using Mint_32 = Modular_Integer<uint32_t,M>;
template<uint64_t M> using Mint_64 = Modular_Integer<uint64_t,M>;
constexpr uint64_t MOD = static_cast<i64>(1e9+7);
using Mint  = Mint_64<MOD>;
// other case 
template<typename T> inline constexpr T add(T& a, const T& b) {
    a+=b; 
    if(a > MOD) a-=MOD; 
    return a;
}
template<typename T> inline constexpr T mul(const T& a, const T& b) {
    return (a * b) % MOD;
}
}; // namespace MOD_INT

