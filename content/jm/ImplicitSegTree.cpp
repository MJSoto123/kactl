/**
 * Author: Juanma
 * Description: Sparse segment tree: point add and range sum on [L, R).
 * Nodes are created only when an update visits them.
 * Time: O(log(R-L)) per operation, O(U log(R-L)) memory.
 */

struct Vertex{
    int mx;
    Vertex *lc = nullptr, *rc = nullptr;
    Vertex(int val = 0) : mx(val) {}
};

struct Seg{
    int n; 
    Vertex *root = nullptr;

    void init(int _n){
        n = _n;
    }

    void upd(Vertex *&v, int l, int r, int pos, int val){
        if(!v) v = new Vertex();
        if(pos < l || pos > r) return;
        if(l == r){
            v->mx = val;
            return;
        }
        int mid = l + r >> 1;
        upd(v->lc, l, mid, pos, val);
        upd(v->rc, mid + 1, r, pos, val);
        v->mx = max(v->lc->mx, v->rc->mx);
    }
    void upd(int pos, int val){ upd(root, 0, n - 1, pos, val); }

    int q(Vertex *v, int l, int r, int lq, int rq){
        if(!v || r < lq || rq < l) return 0;
        if(lq <= l && r <= rq) return v->mx;
        int mid = l + r >> 1;
        return max(
            q(v->lc, l, mid, lq, rq),
            q(v->rc, mid + 1, r, lq, rq)
        );
    }
    int q(int lq, int rq){ return q(root, 0, n - 1, lq, rq); }
};