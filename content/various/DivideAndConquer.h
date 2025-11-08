/**
 * Author: coderats 
 * Date: 2025-11-07
 * License: Unknown
 * Source: coderats 
 * Description: $dp[k][i] = min(dp[k-1][j-1], cost(j, i))$
 * Time: $O(N)$ 
 * Status: tested  
 */

void go(int k, int l, int r, int optl, int optr){
    if(l > r) return;
    
    int mid = l + r >> 1;
    ll best = NIL; // neutro
    int opt = -1;

    for(int i = optl; i <= min(mid, optr); i++){
        // fix(i, mid); // fix this range(L, R) in O(n)
        ll here = dp[k - 1][i - 1] + cost(i, mid);
        if(here < best){ // act
            best = here;
            opt = i;
        }
    }
    dp[k][mid] = best;

    go(k, l, mid - 1, optl, opt);
    go(k, mid + 1, r, opt, optr);
}

int solve(){
    // precompute cost function

    // init
    rep(i, 0, k + 1) rep(j, 1, n + 1) dp[i][j] = NIL;
    rep(i, 1, n + 1) dp[1][i] = cost(1, i);

    rep(i, 2, k + 1) go(i, 1, n, 1, n);
    cout << dp[k][n] << "\n";
}