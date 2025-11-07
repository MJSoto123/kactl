/**
 * Author: Julio
 * Date: 2025-11-06
 * License: Unlicense
 * Source: YouKn0wWho algo lib
 * Description: Gaussian elimination mod 2. 
 * Returns -1 if there aren't solutions. 
 * Returns number of free variables otherwise. 
 * n = number of equations, m = number of variables
 * Time: O((N ^ 3) / 64)
 * Status: Tested on icpc brazil-2020: Between Us
 */

#pragma once 
const int N = 100 + 6; 
int Gauss(int n, int m, vector<bitset<N>> a, bitset<N> &ans) {
    int rank = 0, det = 1;
    vi pos(N, -1);
    for(int col = 0, row = 0; col < m && row < n; ++col) {
        int mx = row;
        rep(i,row,n) if(a[i][col]) { mx = i; break; }
        if(!a[mx][col]) { det = 0; continue; }
        swap(a[mx], a[row]);
        if(row != mx) det = det == 0 ? 0 : 1;
        det &= a[row][col];
        pos[col] = row;
        //forward elimination
        rep(i,row+1,n) if (a[i][col]) a[i] ^= a[row];
        ++row, ++rank;
    }
    ans.reset();
    //backward substituition
    for (int i = m - 1; i >= 0; i--) {
        if (pos[i] == -1) ans[i] = true;
        else {
            int k = pos[i];
            rep(j,i+1,m) if (a[k][j]) ans[i] = ans[i] ^ ans[j];
            ans[i] = ans[i] ^ a[k][m];
        }
    }

    rep(i,rank,n) if(a[i][m]) return -1; //no solution
    
    int free_var = 0;
    rep(i,0,m) if(pos[i] == -1) free_var++;
    return free_var; //has solution
} 