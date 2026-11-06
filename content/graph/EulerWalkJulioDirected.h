/**
 * Author: Julio
 * Date: 2016-11-06
 * License: CC0
 * Source: me
 * Description: Eulerian walk on directed graphs, returns path
 * Time: O(N+M)
 * Status:  tested
 */
struct EulerianDirected { 
    int n, m; 
    vvi g;
    vi in, out;  
    vi path; 

    EulerianDirected(int n_, int m_) : n(n_), m(m_) {
        g.resize(n);
        in.resize(n);
        out.resize(n);
    } 

    void add_edge(int u, int v) {
        g[u].push_back(v);
        in[v]++; 
        out[u]++;
    }

    void dfs(int node) {
        while(!g[node].empty()) {
            int son = g[node].back();
            g[node].pop_back();
            dfs(son);
        }
        path.push_back(node);
    }

    vi solve() {
        int in_out = -1, out_in = -1; 
        for(int i = 0; i < n; i++) {
            if(abs(in[i] - out[i]) > 1) return {}; 
            if(in[i] == out[i] + 1) {
                if(in_out == -1) in_out = i; 
                else return {}; 
            }
            if(out[i] == in[i] + 1) {
                if(out_in == -1) out_in = i; 
                else return {}; 
            }
        }
        if(in_out != -1) {
            if(out_in == -1) return {}; 
            dfs(out_in);
        }else{
            for(int i = 0; i < n; i++) {
                if(in[i]) {
                    dfs(i);
                    break;
                }
            }
        }
        if((int)path.size() != m + 1) return {}; 
        reverse(path.begin(), path.end());
        return path; 
    }

};
