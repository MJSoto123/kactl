/**
 * Author: coderats 
 * Date: 2025-11-07
 * License: Unknown
 * Source: coderats 
 * Description: Suffix Automaton
 * Time: $O(|s|)$ 
 * Status: tested  
 */

struct SuffixAutomaton {
	int nodes;
	vector<int> link; // suffix link
	vector<int> len; // max length of the state
	vector<int> firstpos; // last position of first occurrence of state
	vector<vector<int>> nxt; // transitions
	vector<bool> is_clone; // clone attribute (for counting)

	SuffixAutomaton() {
		len.emplace_back(0);
		link.emplace_back(-1);
		nxt.emplace_back(vector<int>(26, 0));
		firstpos.emplace_back(-1);
		is_clone.emplace_back(false);
		nodes = 1;
	}

	void add_node(int new_len, int new_link, int new_fp, bool new_clone) {
		len.emplace_back(new_len);
		link.emplace_back(new_link);
		nxt.emplace_back(vector<int>(26, 0));
		firstpos.emplace_back(new_fp);
		is_clone.emplace_back(new_clone);
	}

	int add(int p, int c) {
		auto getNxt = [&] () {
			if (p == -1) return 0;
			int q = nxt[p][c]; 
			if (len[p] + 1 == len[q]) return q;
			int clone = nodes++;
			add_node(len[p] + 1, link[q], firstpos[q], true);
			nxt[nodes - 1] = nxt[q];
			link[q] = clone;
			while(~p and nxt[p][c] == q) {
				nxt[p][c] = clone;
				p = link[p];
			}
			return clone;
		};
		// if (nxt[c][p]) return getNxt();
		// ^ need if adding > 1 string
		int cur = nodes++; // make new state
		add_node(len[p] + 1, -1, firstpos[p] + 1, false);
		while(~p and !nxt[p][c]) {
			nxt[p][c] = cur;
			p = link[p];
		}
		int x = getNxt(); 
		link[cur] = x; 
		return cur;
	}

	void init(string s) { // add string to automaton
		int p = 0; 
		for(auto c : s) {
			p = add(p, c - 'a');
		}
	} 

    void print(int u){
        for(int i = 0; i < 26; i++){
            if(!nxt[u][i]) continue;
            cout << u << " " << nxt[u][i] << " " << char(i + 'a') << "\n";
            print(nxt[u][i]);
        } 
    }

    void countDistinctSubstrings(int n) {
		vector<long long> dis(nodes, 0);
		vector<int> vis(nodes, 0);
		queue<int> q;
		q.emplace(0);
		while(!q.empty()){
			int u = q.front(); q.pop();
			for(int c = 0; c < 26; c++){
				if(!nxt[u][c]) continue;
				if(vis[nxt[u][c]]) continue;
				vis[nxt[u][c]] = 1;
				dis[nxt[u][c]] = dis[u] + 1;
				q.emplace(nxt[u][c]);
			}
		}

		vector<int> ans(n + 2, 0);
		for(int i = 1; i < nodes; i++) {
			ans[dis[i]]++;
			ans[len[i] + 1]--;
		}

		for(int i = 1; i <= n; i++) ans[i] += ans[i - 1];

		for(int i = 1; i <= n; i++) cout << ans[i] << " ";
		cout << "\n";
    }

};