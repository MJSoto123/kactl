/**
 * Author: coderats 
 * Date: 2025-11-06
 * License: Unknown
 * Source: coderats 
 * Description: Save the entire sorted array in every node of the segment tree
 * Time: $O(N \log N)$ 
 * Status: tested  
 */
#pragma once
void build(int v, int tl, int tr) {
	if(tl == tr) {
		tree[v] = vi(1, arr[tl]);
		return; 
	}
	int tm = (tl + tr) / 2;
	build(2 * v, tl, tm);
	build(2 * v + 1, tm + 1, tr);
	merge(tree[v * 2].begin(), tree[v * 2].end(), 
			tree[v * 2 + 1].begin(), tree[v * 2 + 1].end(), 
			back_inserter(tree[v]));
	
}
// use lower/upper bound on queries
