/**
 * Author: Julio
 * Date: 2016-11-06
 * License: CC0
 * Source: me
 * Description: Eulerian walk on undirected graphs, returns path
 * Time: O(N+M)
 * Status:  tested
 */
struct EulerianUndirected { // eulerian walk(Hierholzer) 
    int n, m; 
    vector<vii> g; 
    vi path, degree; 
    vector<bool> seen; 

    EulerianUndirected(int n_, int m_) : n(n_), m(m_) {
        g.resize(n);
        seen.assign(m, false);
        degree.resize(n);
    } 

    void add_edge(int u, int v, int i) {
        g[u].emplace_back(v, i);
        g[v].emplace_back(u, i);
        degree[u]++; 
        degree[v]++; 
    }

    void dfs(int node) {
        while(!g[node].empty()) {
            auto [son, idx] = g[node].back();
            g[node].pop_back();
            if(seen[idx]) continue;
            seen[idx] = true; 
            dfs(son);
        }
        path.push_back(node);
    }

    vi solve() {
        int cnt_odd = 0; 
        for(int i = 0; i < n; i++) {
            if(degree[i] % 2) {
                cnt_odd++; 
            }
        }
        if(cnt_odd > 2) return {}; 
        int start = -1; 
        if(cnt_odd == 2) {
            for(int i = 0; i < n; i++) {
                if(degree[i] % 2) start = i; 
            }
        }else{
            for(int i = 0; i < n; i++) {
                if(degree[i]) start = i; 
            }
        }
        assert(start != -1);
        dfs(start);
        if((int)path.size() != m + 1) return {}; 
        return path; 
    }

};