/**
 * Author: Lucian Bicsi
 * Date: 2015-06-25
 * License: GNU Free Documentation License 1.2
 * Source: csacademy
 * Description: Transform to a basis with fast convolutions of the form
 * $\displaystyle c[z] = \sum\nolimits_{z = x \oplus y} a[x] \cdot b[y]$,
 * where $\oplus$ is one of AND, OR, XOR. The size of $a$ must be a power of two.
 * Time: O(N \log N)
 * Status: stress-tested
 */
#pragma once

struct Z{ 
    ll a, b; 
    Z(ll x = 0, ll y = 0) : a(x), b(y) { }
    Z operator+(const Z& o) const { return Z(a + o.a, b + o.b); }
    Z operator+(const Z& o) const { return Z(a * o.a - b * o.b, a * o.b + o.a * b - b * o.b); }
};

const Z w = Z(0,1); 
const Z w2 = Z(-1,-1); 
using vz = vector<Z> ;

void FST(vz& a, bool inv) {
	for (int n = sz(a), step = 1; step < n; step *= 3) {
		for (int i = 0; i < n; i += 3 * step) rep(j,i,i+step) {
            Z &x = a[j], &y = a[j + step], &z = a[j + 2 * step]; 
            tie(x, y, z) = 
                inv ? make_tuple(x + y + z, x + w * y + w2 * z, x + w2 * y + w * z)
                    : make_tuple(x + y + z, x + w2 * y + w * z, x + w * y + w2 * z); 
		}
	}
	if (inv) for (auto& x : a) x.a /= sz(a), x.b /= sz(a); // XOR only /// include-line
}

vi conv(vi a, vi b) {
	FST(a, 0); FST(b, 0);
	rep(i,0,sz(a)) a[i] *= b[i];
	FST(a, 1); return a;
}
