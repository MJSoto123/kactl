/**
 * Author: Julio
 * Date: 2025-11-06
 * License: Unknown
 * Source: CP algo  
 * Description: Calculates the faces of a planar graph
 * Time: $O(N \log N)$, because of sorting 
 * Status: tested  
 */
#pragma once
vvi find_faces(vector<P> vertices, vvi& adj) {
    int n = vertices.size();
    std::vector<std::vector<char>> used(n);
    rep(i,0,n) {
        used[i].assign(sz(adj[i]), 0);
        auto compare = [&](size_t l, size_t r) {
            P pl = vertices[l] - vertices[i];
            P pr = vertices[r] - vertices[i];
            if (pl.half() != pr.half())
                return pl.half() < pr.half();
            return pl.cross(pr) > 0;
        };
        sort(all(adj[i]), compare);
    }
    vvi faces;
    rep(i,0,n) {
        rep(edge_id,0,sz(adj[i]))  {
            if (used[i][edge_id]) continue;
            vi face;
            int v = i, e = edge_id;
            while (!used[v][e]) {
                used[v][e] = true;
                face.push_back(v);
                int u = adj[v][e];
                int e1 = std::lower_bound(adj[u].begin(), adj[u].end(), v, [&](int l, int r) {
                    Point pl = vertices[l] - vertices[u];
                    Point pr = vertices[r] - vertices[u];
                    if (pl.half() != pr.half())
                        return pl.half() < pr.half();
                    return pl.cross(pr) > 0;
                }) - adj[u].begin() + 1;
                if (e1 == sz(adj[u])) e1 = 0;
                v = u;
                e = e1;
            }
            reverse(all(face));
            Point p1 = vertices[face[0]];
            __int128 sum = 0;
            for (int j = 0; j < face.size(); ++j) {
                Point p2 = vertices[face[j]];
                Point p3 = vertices[face[(j + 1) % face.size()]];
                sum += (p2 - p1).cross(p3 - p2);
            }
            if (sum <= 0) faces.insert(faces.begin(), face);
            else faces.emplace_back(face);
        }
    }
    return faces;
}