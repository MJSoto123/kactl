/**
 * Author: coderats 
 * Date: 2025-11-07
 * License: Unknown
 * Source: coderats 
 * Description: DigitDP and save the path
 * Time: $O(N)$ 
 * Status: tested  
 */

int low[20], high[20];
ll best[20][2][2][2];
int choose[20][2][2][2];

void init(){
    memset(best, -1, sizeof(best));
    memset(choose, -1, sizeof(choose));
}

ll dfs(int pos, int positive = 0, int smaller = 0, int bigger = 0){
    if(pos < 0){ return 1; }
    auto &memo = best[pos][positive][smaller][bigger];
    if(memo != -1) return memo;

    int mxd = smaller ? 9 : high[pos];
    int mnd = bigger  ? 0 : low[pos];
    
    ll mxprod = 0;
    rep(d, mnd, mxd + 1){
        int phere = positive || d;
        int shere = smaller || d < high[pos];
        int bhere = bigger || d > low[pos];

        ll anshere = dfs(pos - 1, phere, shere, bhere);
        if(phere) anshere *= d;

        if(mxprod < anshere){
            choose[pos][positive][smaller][bigger] = d;
            mxprod = anshere;
        }
    }
    return memo = mxprod;
}