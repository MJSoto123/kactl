/**
 * Author: Lechugon 
 * Date: 2025-11-06
 * License: Unknown
 * Source: coderats 
 * Description: Get the HLD from a tree.
 * Time: $O(N \log N)$ 
 * Status: tested  
 */
const int N = 1e5 + 10 ; // Nro de Nodos
const int LOG = 18;
int up[N][LOG];
int subt[N];
int h[N];
int chain[N];
int pos;
int in[N];
vi G[N];

/*NSQ -> Funcion de consulta en rango del segment tree */
/*UPD -> Funcion de actualizacion en rango del segment tree*/
struct node{

};

void dfs(int u = 0, int pt = -1){
    subt[u] = 1;
    for(int v: G[u]){if(v == pt) continue;
        h[v] = h[u] + 1;
        up[v][0] = u;
        for(int i = 1; i < LOG; i++) up[v][i] = up[up[v][i - 1]][i - 1];
        dfs(v , u);
        subt[u] += subt[v];
    }
}
 
void HLD(int u = 0, int pt = -1){
    in[u] = ++pos;
    /*Actualizacion segun logica*/
    //idx[pos] = u;
 
    //ids[vals[u]].insert(pos);
    
    int heavy = -1;
    int mx = 0;
    for(int v : G[u]){ if(v == pt) continue;
        if(subt[v] > mx){
            heavy = v;
            mx = subt[v];
        }
    }
    if(heavy != -1){
        chain[heavy] = chain[u];
        HLD(heavy , u);
    }
    for(int v : G[u]){if(v == pt || v == heavy) continue;
        HLD(v , u);
    }
}
 
int kth(int u , int k){
    for(int i = 0; i < LOG; i++) if((k >> i) & 1) u = up[u][i];
    return u;
}
 
int lca(int u , int v){
    if(h[u] < h[v]) swap(u , v);
    u = kth(u , h[u] - h[v]);
    if(u == v) return v;
    for(int i = LOG - 1; i >= 0; i--){
        if(up[u][i] != up[v][i]){
            u = up[u][i];
            v = up[v][i];
        }
    }
    return up[u][0];
}
 
node pathquery(int u , int anc){
    node res;
    while(h[u] > h[anc]){
        int top = chain[u];
        if(h[top] <= h[anc]) /*Acumulacion de la respuesta sin tomar en cuenta al LCA */
            top = kth(u , h[u] - h[anc] - 1);
        // res = res + nsq(in[top] , in[u]);
        u = up[top][0];
    }
    return res;    
}
/*Query en path u y v*/
int query(int u, int v){
    int  anc  = lca(u , v);
    node left  = pathquery(u, anc);
    node right = rsq(in[anc], in[anc]) + pathquery(v , anc);
    return merge({right.ans , left.ans , left.pref + right.pref});
}
/*Update de u al LCA */
void pathUpd(int u , int anc, int val){
    while(h[anc] < h[u]){
        int top = chain[u];
        if(h[top] <= h[anc]){ /*Update sin actualizar el valor del LCA*/
            top = kth(u, h[u] - h[anc] - 1);
        }
        upd(in[top], in[u], val);
        u = up[top][0];
    }
}
/*Update en path u y v*/
void updQuery(int u, int v, int val){
    int anc = lca(u , v);
    upd(in[anc] , in[anc] , val);
    pathUpd(u , anc, val);
    pathUpd(v , anc, val);
}