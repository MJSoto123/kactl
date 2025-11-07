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
struct HP {
    P a, b;  
    HP() {}
    HP(P a, P b) : a(a), b(b) {}
    HP(const HP& rhs) : a(rhs.a), b(rhs.b) {}
    int operator < (const HP& rhs) const {
        P p = b - a;
        P q = rhs.b - rhs.a;
        int fp = (p.y < 0 || (fabsl(p.y) < eps && p.x < 0));
        int fq = (q.y < 0 || (fabsl(q.y) < eps && q.x < 0));
        if (fp != fq) return fp == 0;
        if (p.cross(q)) return p.cross(q) > 0;
        return p.cross(rhs.b - a) < 0;
    }
    P line_line_intersection(P a, P b, P c, P d) {
        b = b - a; d = c - d; c = c - a;
        return a + b * c.cross(d) / b.cross(d);
    }
    P intersection(const HP &v) {
        return line_line_intersection(a, b, v.a, v.b);
    }
};

int check(HP a, HP b, HP c) {
    return (a.b - a.a).cross(b.intersection(c) - a.a) > -eps; 
}

vector<P> half_plane_intersection(vector<HP> h) {
    sort(all(h));
    vector<HP> tmp;
    rep(i,0,sz(h)) { 
        if(!i || (h[i].b - h[i].a).cross(h[i - 1].b - h[i - 1].a)) {
            tmp.push_back(h[i]);
        }
    }

    h = tmp;
    vector<HP> q(sz(h) + 10);
    int qh = 0, qe = 0;
    rep(i,0,sz(h)) { 
        while (qe - qh > 1 && !check(h[i], q[qe - 2], q[qe - 1])) qe--;
        while (qe - qh > 1 && !check(h[i], q[qh], q[qh + 1])) qh++;
        q[qe++] = h[i];
    }
    
    while (qe - qh > 2 && !check(q[qh], q[qe - 2], q[qe - 1])) qe--;
    while (qe - qh > 2 && !check(q[qe - 1], q[qh], q[qh + 1])) qh++;

    vector<HP> res; rep(i,qh,qe) res.push_back(q[i]);
    vector<P> hull;
    if (sz(res) > 2) {
        rep(i,0,sz(res)) 
            hull.push_back(res[i].intersection(res[(i + 1) % ((int)res.size())]));
    }
    return hull;
}