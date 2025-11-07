/**
 * Author: Julio 
 * Date: 2025-11-06
 * License: Unlicense 
 * Source: CP Algorithms 
 * Description: Calculates primitive root modulo p. 
 * p is prime, to make it work with any number, add the calculation of phi(p)
 * Status: tested 
 */
#pragma once

int p_root(int p) { 
    // divisores de phi (p primo -> phi = p - 1)
    vi facts;  
    int phi = p - 1, n = phi; 
    for(int i = 2; i * i <= n; i++) { 
        if(n % i == 0) { 
            facts.push_back(i); 
            while(n % i == 0) n /= i; 
        }
    }
    if(n > 1) facts.push_back(n); 

    auto bp = [&](int a, int b) { 
        int res = 1; 
        while(b) { 
            if(b & 1) res = 1LL * res * a % p; 
            a = 1LL * a * a % p; 
            b >>= 1; 
        }
        return res; 
    };

    rep(res,2,p+1) { 
        bool ok = true; 
        for(int f : facts) { 
            // binpow modulo p 
            ok &= (bp(res,phi/f) != 1); 
            if(!ok) break; 
        }
        if(ok) return res; 
    }
    assert(false); // por si acaso 
}
