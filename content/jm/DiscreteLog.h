/**
 * Author: coderats
 * Date: 2025-11-07
 * License: Unknown
 * Source: coderats
 * Description: Extended Baby Step Giant Step and Handles non-coprime.
 * Time: $O(\sqrt{\text{mod}})$ per query
 * Status: tested
 */

 // Returns minimal x >= 0 with a ^ x  b (mod mod), or -1 if none.
ll discrete_log(int a, int b){
    a %= mod; b %= mod;

    if (mod == 1) return 0;
    if (b == 1 % mod) return 0; // x = 0 works

    int remain = 1, extra = 0;
    int g = gcd(a, mod);

    // Strip gcd factors while possible
    while (g != 1){
        if (b == remain) return extra;      // matched already
        if (b % g) return -1;               // impossible
        b /= g; mod /= g;                   // reduce modulus and target
        remain = mul(remain, a / g);        // accumulate factor
        ++extra;
        g = std::gcd(a, mod);
    }

    // Now gcd(a, mod) == 1 -> standard BSGS
    int n = sqrt(mod) + 1;

    // Baby steps: store b * a^j
    vii baby; baby.reserve(n);
    int cur = b;
    rep(j, 0, n){
        baby.emplace_back(cur, j);
        cur = mul(cur, a);
    }
    sort(all(baby)); // sort by first (value)

    // Giant steps: multiply remain * (a^n)^i and binary search
    int step = binpow(a, n);
    int giant = remain;
    rep(i, 1, n + 1){
        giant = mul(giant, step);

        int l = -1, r = sz(baby);
        while (r - l > 1){
            int mid = l + r >> 1;
            if (baby[mid].first <= giant) l = mid;
            else r = mid;
        }
        if (l != -1 && baby[l].first == giant){
            ll x = 1LL * i * n - baby[l].second + extra;
            if (x >= 0) return x; // minimal by construction
        }
    }
    return -1;
}
