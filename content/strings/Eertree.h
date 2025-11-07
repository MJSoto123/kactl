/**
 * Author: Julio
 * Source: unknown 
 * Description: Get the number of unique palindromic substrings online. 
 * Time: O(N)
 * Status: tested
 */
#pragma once

struct palindromic_tree{
	struct node{
		int next[26],fail,len;
		int cnt,num,st,ed;
		node(int l=0):fail(0),len(l),cnt(0),num(0){
			for(int i=0;i<26;++i)next[i]=0;
		}
	};
	vector<node> state;
	vector<char> s;
	int last,n;
  
	void init(){
		state.clear();
		s.clear();
		last=1;
		n=0;
		state.push_back(0);
		state.push_back(-1);
		state[0].fail=1;
		s.push_back(-1);
	}
	int get_fail(int x){
		while(s[n-state[x].len-1]!=s[n])x=state[x].fail;
		return x;
	}
	void add(int c){
		s.push_back(c-='a');
		++n;
		int cur=get_fail(last);
		if(!state[cur].next[c]){
			int now=state.size();
			state.push_back(state[cur].len+2);
			state[now].fail=state[get_fail(state[cur].fail)].next[c];
			state[cur].next[c]=now;
			state[now].num=state[state[now].fail].num+1;
		}
		last=state[cur].next[c];
		++state[last].cnt;
	}
	int size(){
		return state.size()-2;
	}
} pt;