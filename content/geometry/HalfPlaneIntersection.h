/**
 * Author: Julio
 * Date: 2025-11-06
 * License: Unlicense
 * Source: YouKn0wWho algo library   
 * Description: Returns a convex polygon, the intersection of some half-planes. 
 * You can add a bounding box at the beginning.
 * Status: Tested on Uttara IUPC-The Perfect Spider Web 
 * Time: O(n \log n)
 */

#pragma once
#include "Point.h"

struct line { P p, q; }
bool HPintersect(vector<line> v) { 
    auto side = [](line &l, P p) {
        return sideOf(l.p, l.q, p) >= 0;  
    };

    auto crosspoint = [](const line &l, const line &m, P &x) { 
        auto inter = lineInter(l.p, l.q, m.p, m.q); 
        if(inter.first <= 0) return false; 
        x = inter.second; 
        return true; 
    };

    shuffle(all(v), mt19937(time(0))); 
    P cen(0,1e9); 
    rep(i,0,sz(v)) { 
        line &S = v[i]; 
        if(side(S, cen)) continue; 
        P d = (S.q - S.p).unit(); 
        P A = S.p - d * 1e8, B = S.p + d * 1e8; 
        rep(j,0,i) { 
            P x; 
            line &T = v[j]; 
            if(crosspoint(T, S, x)) { 
                int cnt = 0; 
                if(!side(T, A)) A = x, cnt++; 
                if(!side(T, B)) B = x, cnt++;
                if(cnt == 2) return false; 
            }else if(!side(T, A)) return false; 
        }
        if(B.y > A.y) swap(A, B); 
        cen = A; 
    }
    return true; 
} 