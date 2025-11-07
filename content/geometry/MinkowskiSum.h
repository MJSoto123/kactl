/**
 * Author: Julio
 * Date: 2025-11-06
 * License: Unknown
 * Source: CP algo
 * Description: Calculates the Minkowski sum of two polygons. 
 * Be careful with precision issues, use sgn with epsilons instead of c <= 0 
 * Time: $O(N + M)$, where N and M are the size of the polygons. 
 * Status: tested 
 */
#pragma once

#include "Point.h"

void fix(poly &a) { 
    int pos = 0; 
    rep(i,0,sz(a)) { 
        if(a[i].y < a[pos].y || (a[i].y == a[pos].y && a[i].x < a[pos].x)) pos = i; 
    }
    rotate(a.begin(), a.begin() + pos, a.end()); 
}
poly minkowski_sum(poly a, poly b) { 
    fix(a); fix(b); 
    rep(it,0,2) a.push_back(a[it]), b.push_back(b[it]); 
    int i = 0, j = 0; 
    poly res; 
    while(i < sz(a) - 2 || j < sz(b) - 2) { 
        res.push_back(a[i] + b[j]); 
        auto c = (a[i + 1] - a[i]).cross(b[j + 1] - b[j]);
        // a veces solo se necesita la segunda comprobacion 
        if(i < sz(a) - 2 && c >= 0) i++; 
        if(j < sz(b) - 2 && c <= 0) j++; 
    }
    return res; 
}