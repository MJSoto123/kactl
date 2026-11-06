
/**
 * Author: Juanma
 * Description: Centroid Decomposition with collect.
 * Time: O(N log N), excluding processing.
 */

#pragma once

struct CentroidCollect {
    int n;
    vvi g;
    vi sub, dead, par;

    CentroidCollect(int n) :
        n(n), g(n), sub(n), dead(n), par(n, -1) {}

    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int dfs(int u, int p = -1) {
        sub[u] = 1;
        for(int v : g[u]) {
            if(v == p || dead[v]) continue;
            sub[u] += dfs(v, u);
        }
        return sub[u];
    }

    int find_centroid(int u, int p, int total) {
        for(int v : g[u]) {
            if(v == p || dead[v]) continue;
            if(sub[v] > total / 2)
                return find_centroid(v, u, total);
        }
        return u;
    }

    void collect(int u, int p, int d, vii &v) {
        v.push_back({u, d});
        for(int to : g[u]) {
            if(to == p || dead[to]) continue;
            collect(to, u, d + 1, v);
        }
    }

    void process(int c, vii &all, vector<vii> &branches) {
        // Compute the contribution of centroid c here.
    }

    void decompose(int u, int p = -1) {
        int total = dfs(u);
        int c = find_centroid(u, -1, total);
        par[c] = p;
        dead[c] = 1;

        vii all = {{c, 0}};
        vector<vii> branches;

        for(int v : g[c]) {
            if(dead[v]) continue;

            vii here;
            collect(v, c, 1, here);

            all.insert(all.end(), here.begin(), here.end());
            branches.push_back(move(here));
        }

        process(c, all, branches);

        for(int v : g[c]) {
            if(!dead[v]) decompose(v, c);
        }
    }

    void solve() {
        fill(all(dead), 0);
        fill(all(par), -1);
        if(n) decompose(0);
    }
};
