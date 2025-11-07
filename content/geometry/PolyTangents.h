/**
 * Author: Julio
 * Date: 2025-11-06
 * License: Unknown
 * Source: YouKn0wWho algo lib 
 * Description: Calculates the tangent from a point to a polygon
 * The polygon must be given in CCW order.
 * Time: $O(\log N)$
 * Status: Tested on toph: cover the points  
 */
#pragma once

#include "Point.h"

template<class Fun> 
// tangent from p to poly 
// auto t = extreme(poly, [&](const P q) { return p - q; }); 
int extreme(const vector<P>& poly, Fun dir) { 
    int n = sz(poly), low = 0, low_sgn; 
    auto nx = [&](int i) { return i + 1 == n ? 0 : i + 1 ; };
    auto pr = [&](int i) { return i ? i - 1 : n - 1; };
    auto vertexCmp = [&](int i, int j) { 
        return sgn(dir(poly[j]).cross(poly[j] - poly[i]));
    };
    auto isExtreme = [&](int i , int &i_sgn) { 
        return (i_sgn = vertexCmp(nx(i), i)) >= 0 && vertexCmp(i, pr(i)) < 0 ; 
    };

    for(int high = isExtreme(0, low_sgn) ? 1 : n; low + 1 < high;) { 
        int mid = (low + high) / 2, mid_sgn; 
        if(isExtreme(mid, mid_sgn)) return mid; 
        if(low_sgn != mid_sgn ? low_sgn < mid_sgn
                : low_sgn == vertexCmp(low, mid)) high = mid; 
        else low = mid, low_sgn = mid_sgn; 
    }
    return low ; 
}

