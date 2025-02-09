//Bits utils
inline namespace UTIL_BITS{
#define TEM template<typename T> inline 
#define st32(x) static_cast<uint32_t>(x) 
#define st64(x) static_cast<uint64_t>(x) 
//te dice el el numero de bits encedidos espedico 3 = 111 -> 7
TEM i32 pop_count(const T& x) {return (sizeof(T)<=4)?__builtin_popcount(st32(x)):__builtin_popcountll(st64(x));}
// si el total de bits activos es impar o par 
TEM i32 pop_parity(const T& x) {return (sizeof(T)<=4)?__builtin_parity(st32(x)):__builtin_parityll(st64(x));}
// pos de bit activo mas alto [0,1,2,3,4,5]->[-1,0,1,1,2] 
TEM i32 topbit(const T& x) {return (x==0)?-1:(sizeof(T)<=4)?31-__builtin_clz(st32(x)):63-__builtin_clzll(st64(x));}
// pos de bit activo mas bajo [0,1,2,3,4]->[-1,31,30,30,29]
TEM i32 lowbit(const T& x) {return (x==0)?-1:(sizeof(T)<=4)?__builtin_clz(st32(x)):__builtin_clzll(st64(x));}
//te dice si es potencia de dos
TEM bool ispow2(const T& i){return i&&(i&-i)==i;}
//calcula la potecia de dos mayor o igual a  n 
TEM T minpot2(const T& n){return T(1)<<(topbit(n-1)+1);}
//Apaga (pone en 0) el bit en la pos p 
TEM T off_bit(T& n, i32 p) {return n & ~(T(1) << p);}
//Enciende (pone en 1) el bit en la pos p 
TEM T on_bit(T n, i32 p) {return n | (T(1)<< p);}
//invierte el estado del bit en la pos p 
TEM T change_bit(T n, i32 p) {return n ^ (T(1)<< p);}
//retorna el valor del bit en la pos p 
TEM bool has_pos_bit(T& n, i32 p){return n & (T(1)<< p);}
//retorna el valor total del bit mas peque 18 = 10010 -> 10 = 2
TEM T lowest_bit(const T& n) {return n & -n;}
// retorna el rango dado con bits activos
TEM T create_mask(i32 l, i32 r) {return ((1U << (r - l + 1)) - 1) << l;}
#undef sp32 
#undef sp64 
#undef TEM
}// namespace UTIL_BITS
