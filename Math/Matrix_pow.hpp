inline namespace MATRIX_POW{
using Matrix = std::vector<std::vector<Mint>>;
Matrix ones(int n) {
    Matrix r(n, std::vector<Mint>(n, Mint(0)));
    for (int i = 0; i < n; i++) {
        r[i][i] = Mint(1);
    }
    return r;
}
Matrix operator*(const Matrix& a, const Matrix& b) {
    int n = a.size(), m = b[0].size(), z = a[0].size();
    Matrix r(n, std::vector<Mint>(m, Mint(0)));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < z; k++) {
                r[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return r;
}
Matrix matrix_pow(Matrix b, i64 e) {
    int n = b.size();
    Matrix r = ones(n);
    while (e > 0) {
        if (e & 1LL) r = r * b;
        b = b * b;
        e /= 2;
    }
    return r;
}
} // MATRIX_POW 

