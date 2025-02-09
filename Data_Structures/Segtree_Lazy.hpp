//Lazy_SegTree Base 
template<typename Info>
class Lazy_SegTree { 
public:
    using inf = Info;
    using T = typename Info::Type;
    using TP = typename Info::Type_Pos;
    #define left node << 1 
    #define right node << 1 | 1
    // --------------- datos---------------------
    std::vector<Info> Tree;
    TP size, log;
    //-------------------------------------------
    explicit Lazy_SegTree() : size(TP(0)) {}
    explicit Lazy_SegTree(TP tam) : size(tam){
        log = 1;
        while ((1 << log) < size) ++log;
        size = 1 << log;
        Tree.assign(size << 2, {inf::neutral()});   
    }
    explicit Lazy_SegTree(const std::vector<T> &ar){
        log = 1;
        size = sz(ar);
        while ((1 << log) < size) ++log;
        size = 1 << log;
        Tree.assign(size << 1, {inf::neutral()});
        build(ar);
    }
    inline constexpr void modify(TP node) {
        Tree[node] = inf::Merge(Tree[left], Tree[right]);
    }
    inline void init(TP n){
        size = n;
        log = 1;
        while ((1 << log) < size) ++log;
        size = 1 << log;
        Tree.assign(size << 2, {inf::neutral()});
    }
    void build(const std::vector<T> &ar) {
        TP tam = (i32)ar.size();
        for (auto i = 0; i < tam; i++) Tree[size + i] = {
            ar[i]
        };// se aumenta depende la cantidad de operaciones 
        for (auto i = size - 1; i; i--) modify(i);
    }
    void apply(TP node, T val, TP child) {
        // verificar que tipo de acumulacion tiene
        Tree[node].val += val * child; // para este caso es incremento 
        if (node < size) {
            Tree[node].Has_Lazy = true;
            Tree[node].Lazy_Value += val; // para este caso es incremento 
        }
    }
    void propagate(TP node, TP l, TP r) {
        if(Tree[node].Has_Lazy){
            TP mid = (l + r) >> 1;
            if(l != r){
                apply(left, Tree[node].Lazy_Value, mid - l + 1);
                apply(right, Tree[node].Lazy_Value, r - mid);
            }
            Tree[node].Has_Lazy = false;
            Tree[node].Lazy_Value = inf::init();
        }
    }
    void update(TP node, TP nl, TP nr, TP ql, TP qr, T v) {
        if (nr < ql || qr < nl) return;
        if (ql <= nl && nr <= qr) {
            apply(node, v, nr - nl + 1);
            return;
        }
        propagate(node, nl, nr);
        TP mid = (nl + nr) >> 1;
        if (ql <= mid) update(left, nl, mid, ql, qr, v);
        if (qr > mid) update(right, mid + 1, nr, ql, qr, v);
        modify(node);
    }
    void update(TP l, TP r, T v) {
        update(1, 0, size - 1, l, r, v);
    }
    Info query(TP node, TP nl, TP nr, TP ql, TP qr) {
        propagate(node,nl,nr);
        if (ql <= nl && nr <= qr) return Tree[node];
        TP mid = (nl + nr) >> 1;
        if (qr <= mid) return query(left, nl, mid, ql, qr);
        if (ql > mid) return query(right, mid + 1, nr, ql, qr);
        return inf::Merge(query(left, nl, mid, ql, qr), query(right, mid + 1, nr, ql, qr));
    }
    Info query(TP l, TP r) {
        return query(1, 0, size - 1, l, r);
    }
};
//-------------------Monoides----------------------

//-------------------------------------------------
template <typename X>
class Node {
public:
    using Type = X;
    using Type_Pos = i32;
    //--------------------Monoides-----------------------
    using op = 
    //- ------------------------------------------
    static constexpr Node Merge(const Node& x, const Node& y) noexcept {
        return {
            op::(x.val , y.val), 
            init(), // pa los hijos 
            false // para el lazy
        };
    }
    static constexpr X init() { return X(0); }
    //NULL Por cada operacion
    static constexpr Node neutral() { 
        return {
            init(), init(), false
        };
    }
    // ------------------variables------------------------
    X val;
    //----------------------Lazy--------------------------
    X Lazy_Value;
    bool Has_Lazy;
};
