/**
 * Author: Lechugon 
 * Date: 2025-11-06
 * License: Unknown
 * Source: coderats 
 * Description: $(x1,y1)(x2,y2)$ querys in $O(Q log^2 N)$.
 * Time: $O(Q \log^2 N)$ 
 * Status: tested  
 */
const int N = 1000 + 100;
inline int lso(int nm){return (nm & (-nm));}
vector<vi> ft(N , vi(N, 0));
 
void update(int x, int y, int val){
    for(; x < N ; x += lso(x))
        for(int j = y; j < N; j += lso(j))
            ft[x][j] += val;
}
 
int query(int x , int y){
    int ans = 0;
    for(; x ; x -= lso(x))
        for(int j = y; j; j -= lso(j))
            ans += ft[x][j];
    return ans;
}
 
int get(int x1, int y1 , int x2 , int y2){
    return query(x2 , y2) - query(x1 - 1 , y2) - query(x2 , y1 - 1) + query(x1 - 1 , y1 - 1);
}