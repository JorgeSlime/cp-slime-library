//SegmentTree_Base 
template<class Info>
class SegTree{ 
public: 
    using inf = Info;
    using T = typename inf::Type;
    using TP = typename inf::Type_pos;
    #define left node << 1 
    #define right node << 1 | 1 
    // --------------- datos---------------------
    std::vector<Info> Tree;
    TP log,size;
    // ------------------------------------------
    explicit SegTree() : size(TP(0)) {}
    explicit SegTree(TP tam) : size(tam) {
        log = 1;
        while((1<<log) < size) ++log;
        size = 1<<log;
        Tree.assign(size<<1,{inf::neutral()});
    }
    explicit SegTree(std::vector<T> &ar){
        size = sz(ar);    
        log = 1;
        while((1<<log)<size) ++log;
        size = 1<<log;
        Tree.assign(size<<1,{inf::neutral()});
        init(ar);
    }
    void set(int k, Info x) { Tree[k + size] = x; }

    Info &operator[](const TP &pos) { return Tree[pos + size]; }

    inline constexpr void modify(T node){
        Tree[node] = inf::Merge(Tree[left],Tree[right]);
    }

    void init(const std::vector<T> &ar){
        i32 tam = (i32)ar.size();
        for(auto i = 0; i<tam ; i++) Tree[size + i]={
            ar[i]
        }; // cantidad de operaciones
        for(int i = size - 1 ; i ; i--) modify(i);
    }

    void update(TP node, TP nl, TP nr, TP pos,T v) {
        if(nl > pos || nr < pos) return;
        if(nr==nl) {
            Tree[node] = {v}; //asignacion 
        } 
        else {
            T mid = (nl + nr) >> 1;
            if(pos <= mid) update(left, nl, mid, pos, v);
            else update(right, mid + 1, nr, pos, v);
            modify(node);
        }
    }

    void update(TP pos ,TP val){
        update(1, 0, size-1, pos, val);
    }

    Info query(TP node, TP nl, TP nr, TP ql, TP qr) {
        if (ql <= nl && nr <= qr)  return Tree[node];
        TP mid = (nl + nr) >> 1;
        if (qr <= mid) return query(left, nl, mid, ql, qr);
        if (ql > mid) return query(right, mid + 1, nr, ql, qr);
        return inf::Merge(query(left, nl, mid, ql, qr), query(right, mid + 1, nr, ql, qr));
    }

    Info query(TP l, TP r){
        return query(1, 0, size-1, l, r);
    }
    

    // nos falta aprender min_right  & max_left :(
};
//-------------------Monoides----------------------

//-------------------------------------------------
template <typename X>
class Node{
public: 
    using Type=X;
    using Type_pos=i32;
    //-------------------Monoides----------------------
    using op = 
    //-------------------------------------------------
    static constexpr Node Merge(const Node &x, const Node &y) noexcept{
        return {
            op::(x.val,y.val)
        };
    }
    //NULL val para cada tipo de operacion 
    static constexpr Node neutral() { 
        return{
            op::neutral()
        };
    }
    //----------------variables----------------
    X val;
};
