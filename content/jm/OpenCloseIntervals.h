/**
 * Author: coderats 
 * Date: 2025-11-07
 * License: Unknown
 * Source: coderats 
 * Description: DP Open-Close
 * Time: $O(M * N * N)$
 * Status: tested  
*/

// dp[i][j], i: opened, j: closed
void solve(){
    vvi dp(n + 2, vi (n + 2));
    dp[0][0] = 1;
    rep(pos, 1, m + 1){
        vvi ndp(n + 2, vi(n + 2));
        rep(i, 0, n + 1){
            rep(j, 0, n + 1){
                if(pos != x){
                    // nada
                    add(ndp[i][j], dp[i][j]);
                    // cerrar
                    if(i > j) add(ndp[i][j + 1], dp[i][j]);
                }
                // abrir
                add(ndp[i + 1][j], dp[i][j]);
                // abrir cerrar
                add(ndp[i + 1][j + 1], dp[i][j]);
            }
        }

        swap(dp, ndp);
    }

    int ans = dp[n][n];
    for(int i = 1; i <= n; i++) ans = mul(ans, i);
}