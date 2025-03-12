/**
 * Author: Coderats al Fallo
 * Date: 2024-03-11
 * License: CC0
 * Source: ?
 * Description: Todo
 */

 #pragma once
 const int INF = 1e6; 
 const int LOG = 18;
 struct CentroidDecomposition{
     vvi tree, cd; 
     vi subt, par, ans, dep; 
     vector<bool> removed; 
     vvi up; 
     int root; 
     CentroidDecomposition(int n) : tree(n), cd(n), root(-1), subt(n), par(n), ans(n, INF), dep(n), removed(n) {
         up.assign(LOG, vi(n, -1));
     }
 
     void add_edge(int u, int v) {
         tree[u].push_back(v);
         tree[v].push_back(u);
     }
 
     int dfs(int u, int p = -1) {
         subt[u] = 1; 
         for(int v : tree[u]) {
             if(removed[v] || v == p) continue;  
             subt[u] += dfs(v, u);
         }
         return subt[u]; 
     }
 
     int find_centroid(int u, int comp_sz, int p = -1) {
         for(int v : tree[u]) {
             if(removed[v] || v == p) continue;
             if(2 * subt[v] > comp_sz) return find_centroid(v, comp_sz, u);
         }
         return u; 
     }
 
     void decompose(int u, int p = -1) {
         int comp_sz = dfs(u);
         int centroid = find_centroid(u, comp_sz);
         if(root == -1) root = centroid; 
         par[centroid] = p; 
         if(p != -1) {
             cd[p].push_back(centroid);
             cd[centroid].push_back(p);
         }
         removed[centroid] = true;   
         for(int v : tree[centroid]) {
             if(!removed[v]) decompose(v, centroid);
         }
     }   
 
     void dfs_LCA(int u, int p = -1) {
         if(p != -1) dep[u] = dep[p] + 1;
         up[0][u] = p; 
         for(int v : tree[u]) if(v != p) {
             dfs_LCA(v, u);
         }
     }
 
     void init_LCA(int n) {
         dfs_LCA(0);
         for(int lg = 1; lg < LOG; lg++) {
             for(int i = 0; i < n; i++) {
                 if(up[lg - 1][i] != -1) 
                     up[lg][i] = up[lg - 1][up[lg - 1][i]]; 
             }
         }
     }
 
     int lift(int u, int len) {
         while(len) {
             int jump = __builtin_ctz(len);
             u = up[jump][u]; 
             len &= (len - 1);
         }
         return u; 
     }
 
     int LCA(int u, int v) {
         if(dep[u] > dep[v]) swap(u, v);
         v = lift(v, dep[v] - dep[u]);
         if(u == v) return u; 
         for(int lg = LOG - 1; lg >= 0; lg--) {
             if(up[lg][u] != up[lg][v]){
                 u = up[lg][u]; 
                 v = up[lg][v]; 
             }
         }
         return up[0][u]; 
     }
 
     int dist(int u, int v) {
         int lca = LCA(u, v);
         return dep[u] + dep[v] - 2 * dep[lca]; 
     }
 
     void update(int u) {
         int fu = u; 
         while(u != -1) {
             ans[u] = min(ans[u], dist(fu, u));
             u = par[u]; 
         }
     }
 
     int query(int u) {
         int fu = u; 
         int res = INF; 
         while(u != -1) {
             res = min(res, ans[u] + dist(u, fu));
             u = par[u]; 
         }
         return res; 
     }
 
 };