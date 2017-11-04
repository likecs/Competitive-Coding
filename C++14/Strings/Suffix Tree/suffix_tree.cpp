/*	Suffix Tree implementation using Ukkonen's Algorithm
	Taken from http://codeforces.com/contest/873/submission/31255069
	Asuuming 0-base indexing and Root = 0.
	par[node] : refers to parent node.
	to[node][alpha] : pointer to child node.
	[L, R] of parent edge is calculated as:
	L = st[node], R = min(S.length() - 1, L + len[node] - 1)
	link[node] : refers to suffix link in tree
	suff[node] : refers to index of suffix which ends at this node.

	Number of nodes in suffix tree are bounded by 2*(String length)
*/

// O(N log(ALPHABET)) construction & use.
namespace SuffixTree {
	const int INF = 1e9, MAX = 1e6 + 10, dollar = 257;
	int S[MAX];
	map<int, int> to[MAX];
	int sz, N, node, pos, remain;
	int len[MAX], st[MAX], link[MAX], suff[MAX], par[MAX];
	void reset(int ST = MAX) {
		sz = 1;
		node = pos = remain = N = 0;
		for(int i = 0; i < 2 * ST; ++i) {
			to[i].clear();
			len[i] = INF;
			st[i] = 0;
			link[i] = 0;
			suff[i] = 0;
			par[i] = 0;
		}
	}
	int make_node(int _pos, int _len,int _par){
		st[sz] =  _pos;
		len[sz] = _len;
		par[sz] = _par;
		suff[sz] = N - remain;
		return sz++;
	}
	void go_edge(){
		while(pos > len[to[node][S[N - pos]]]){
			node = to[node][S[N - pos]];
			pos -= len[node];
		}
	}
	void add_letter(int c){
		S[N++] = c;int last = 0;
		for(++remain, ++pos; pos > 0; --remain) {
			go_edge();
			int edge = S[N - pos];
			int &v = to[node][edge];
			int t = S[st[v] + pos - 1];
			if (v == 0) {	// at root
				v = make_node(N - pos, INF,node);
				link[last] = node;
				last = 0;
			}
			else if (t == c) {	// rule 3 : everything forward already done
				link[last] = node;
				return;
			}
			else {	// rule 2 : creation of node by split of edge/extending node
				int u = make_node(st[v], pos - 1,node);
				to[u][c] = make_node(N - 1, INF,u);
				to[u][t] = v;
				par[v] = u;
				st[v] += pos - 1;
				len [v] -= pos - 1;
				v = u;
				link[last] = u;
				last = u;
			}
			if(node == 0) {	// at root : check next suffix
				--pos;
			}
			else {	// traverse the suffix link
				node = link[node];
			}
		}
	}
	void build(string &s, bool add_dollar = 0) {
		for(int i = 0; i < s.length(); ++i) {
			add_letter(s[i]);
		}
		if (add_dollar) {
			add_letter(dollar);
		}
	}
}
using namespace SuffixTree;