/**
 * Author: Lechugon 
 * Date: 2025-11-06
 * License: Unknown
 * Source: coderats 
 * Description: Ans querys offline in N * SQRT(Q).
 * Time: $O(N \sqrt Q)$ 
 * Status: tested  
 */

const int N = 2e5 + 10;
int arr[N];
int cnt[1000020];
int BLOCK_SIZE; // 450 aprox for N = 2e5 , 350 for N = 1e5
struct query{
    int l;
    int r;
    int idx;
    query(){}
    query(int l,  int r , int idx) : l(l) , r(r) , idx(idx){}
    bool operator<(const query& rhs) const {
        if(l / BLOCK_SIZE == rhs.l / BLOCK_SIZE)
            return r < rhs.r;
        return l / BLOCK_SIZE < rhs.l / BLOCK_SIZE;
    }
};
ll ans = 0;
void add(int id){
    int x = arr[id];
    ans -= 1ll * cnt[x] * cnt[x] * x;
    cnt[x]++;
    ans += 1ll * cnt[x] * cnt[x] * x;
}
void remove(int id){
    int x = arr[id];
    ans -= 1ll * cnt[x] * cnt[x] * x;
    cnt[x]--;
    ans += 1ll * cnt[x] * cnt[x] * x;
}   

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n; cin >> n;
    int q; cin >> q;
    BLOCK_SIZE = static_cast<int>(sqrt(n));
    for(int i = 0; i < n; i++) cin >> arr[i];
    vl res(q);
    vector<query> QS;
    for(int i = 0; i < q; i++){
        int l,r; cin >> l >> r;
        --l ; --r;
        QS.emplace_back(l,r,i);
    }
    sort(all(QS));
    int left = 0;
    int right = -1;
    for(auto [l,r,id] : QS){
        while(left > l)  add(--left);
        while(right < r) add(++right);
        while(left < l)  remove(left++);
        while(right > r) remove(right--);
        res[id] = ans;
    }
}