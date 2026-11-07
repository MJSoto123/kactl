/**
 * Author: Juanma
 * Description: Append x and replace all current x by y (Replace Numbers).
 * root[x] points to the active DSU representative of value x.
 * Time: O(log N) amortized with path compression (no size heuristic).
 */
#pragma once

struct DSUIndirection {
    vi par, root, val, pos;

    DSUIndirection(int N) : root(N + 1, -1) {}

    int make(int x) {
        int u = sz(par);
        par.push_back(u);
        val.push_back(x);
        return u;
    }

    int get(int u) {
        int r = u;
        while(par[r] != r) r = par[r];
        while(par[u] != u) {
            int v = par[u];
            par[u] = r;
            u = v;
        }
        return r;
    }

    void add(int x) { // Append x
        if(root[x] == -1) root[x] = make(x);
        pos.push_back(root[x]);
    }

    void replace(int x, int y) { // Replace all current x by y
        if(x == y || root[x] == -1) return;
        if(root[y] == -1) {
            root[y] = root[x];
            val[root[y]] = y;
        } else {
            par[root[x]] = root[y];
        }
        root[x] = -1;
    }

    vi result() {
        vi ans;
        for(int u : pos) ans.push_back(val[get(u)]);
        return ans;
    }
};