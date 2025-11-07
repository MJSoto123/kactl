/**
 * Author: Julio
 * Date: 2025-11-06
 * License: Unknown
 * Source: me
 * Description: Process the virtual tree of some vertices. Needs to process tin,lca, and is ancestor.  
 * Time: $O(N \log N)$, because of sorting 
 * Status: tested on kingdom and its cities  
 */
#pragma once
int query(vi &v) { 
    sort(all(v), [](int i, int j) { return tin[i] < tin[j]; });
    int siz = sz(v); 
    rep(i,1,siz) v.push_back(LCA(v[i], v[i - 1])) ;
    
    sort(all(v), [](int i, int j) { return tin[i] < tin[j]; });
    v.erase(unique(v.begin(), v.end()), v.end()); 
 
    int root = v[0]; 
    vi st(1, root); 
    rep(i,1,sz(v)) { 
        while(st.size() && !anc(st.back(), v[i])) st.pop_back(); 
        vt[st.back()].push_back(v[i]); 
        st.push_back(v[i]); 
    }

    // solve
    int ans = 0 ; 
    dfs2(root); 
    // clear 
    for(int i : v) vt[i].clear(); 
    return ans; 
}