/**
 * Author: Julio
 * Source: CP algo 
 * Description: For each position in a string, computes half length of
 *  longest even palindrome around pos i
 * Time: O(N)
 * Status: tested
 */
#pragma once

vi manacher_odd(string s) {
    int n = s.size();
    s = "@" + s + "$";
    vi len(n + 1);
    int l = 1, r = 1;
    for(int i = 1; i <= n; i++) {
        len[i] = min(r - i, len[l + (r - i)]);
        while(s[i - len[i]] == s[i + len[i]]) len[i]++;
        if(i + len[i] > r) {
            l = i - len[i];
            r = i + len[i];
        }
    }
    len.erase(begin(len));
    return len;
}

// para verificar si un substring es palindromo
// return pal[l + r] >= (r - l + 1) + 1; indexando en 0
vi manacher(string s) {
    string ns(1, '#'); 
    for(char c : s) {
        ns.push_back(c);
        ns.push_back('#');
    }
    auto res = manacher_odd(ns);
    return vi(res.begin() + 1, res.end() - 1);
}
