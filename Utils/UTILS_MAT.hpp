inline namespace UTIL_MATH{
    //raiz estable
    template <typename T> inline T sqrt_(T n){
        T x=sqrtl(n)+1;
        while(x*x>n) x--;
        return x;
    }
    //redondeo a piso 
    template <typename T>
    T floor(T a, T b) {
      return a / b - (a % b && (a ^ b) < 0);
    }
    //redondeo a techo 
    template <typename T>
    T ceil(T x, T y) {
      return floor(x + y - 1, y);
    }
    //maximo comun divisor
    template <typename T>
    T lcm(T a, T b) {
        return (a / std::gcd(a, b)) * b;
    }

} //namespace UTIL_MATH

