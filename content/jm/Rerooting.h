/**
 * Author: coderats 
 * Date: 2025-11-07
 * License: Unknown
 * Source: coderats 
 * Description: Rerooting
 * Time: $O(N)$ 
 * Status: tested  
*/

struct elem{
    ll subt; 
    ll ans;
};

elem E() { return {0, 0}; }

// add this vertex info
elem take_vertex(elem DP, int v) { return {DP.subt + 1, DP.ans}; }

// e: edge idx, (0 mod 2) => parent
// up root
elem up_root(elem DP, int e) { return {DP.subt, DP.subt + DP.ans}; }

// merge childrens
elem merge(elem u, elem v) { return {u.subt + v.subt, u.ans + v.ans}; }

void dfs(int x, vector<vector<pii>> &gph, vector<int> &ord, vector<int> &pae) {
	ord.push_back(x);
	for (auto &[i, y] : gph[x]) {
		gph[y].erase(find(all(gph[y]), pii{i ^ 1, x}));
		pae[y] = (i ^ 1);
		dfs(y, gph, ord, pae);
	}
}

vector<elem> solve(int n, vector<pii> edges) {
	vector<vector<pii>> gph(n);
	gph.resize(n);
	for (int i = 0; i < n - 1; i++) {
		gph[edges[i].first].push_back({2 * i, edges[i].second});
		gph[edges[i].second].push_back({2 * i + 1, edges[i].first});
	}
	vector<int> ord;
	vector<int> pae(n, -1);
	dfs(0, gph, ord, pae);
	vector<elem> dp(n, E());
	reverse(all(ord));
	for (auto &z : ord) {
		for (auto &[i, y] : gph[z]) {
			dp[z] = merge(dp[z], up_root(dp[y], i));
		}
		dp[z] = take_vertex(dp[z], z);
	}
	vector<elem> rev_dp(n, E());
	reverse(all(ord));
	for (auto &z : ord) {
		vector<elem> pref(sz(gph[z]) + 1, E());
		vector<elem> suff(sz(gph[z]) + 1, E());
		if (~pae[z])
			pref[0] = up_root(rev_dp[z], pae[z]);
		for (int i = 0; i < sz(gph[z]); i++) {
			pref[i + 1] = suff[i] = up_root(dp[gph[z][i].second], gph[z][i].first);
		}
		for (int i = 1; i <= sz(gph[z]); i++)
			pref[i] = merge(pref[i - 1], pref[i]);
		for (int i = sz(gph[z]) - 1; i >= 0; i--)
			suff[i] = merge(suff[i], suff[i + 1]);
		for (int i = 0; i < sz(gph[z]); i++) {
			rev_dp[gph[z][i].second] = take_vertex(merge(pref[i], suff[i + 1]), z);
		}
	}
	vector<elem> sln(n, E());
	for (int x = 0; x < n; x++) {
		if (~pae[x])
			sln[x] = up_root(rev_dp[x], pae[x]);
		for (auto &[i, y] : gph[x]) {
			sln[x] = merge(sln[x], up_root(dp[y], i));
		}
		sln[x] = take_vertex(sln[x], x);
	}
	return sln;
}