/*
Counts the number of triangles in undiredted graph

algorithm from
https://www.quora.com/How-would-one-find-a-number-of-triangles-in-a-given-undirected-graph/answer/Roman-Iedemskyi?srid=Zh26
*/

const int MAX = 1e5 + 5;

int n, m;
int mark[MAX];
pii edge[MAX];					//edge respresentation
vector<int> adj[MAX];			//adjacency list representation
vector<int> heavy, light;

//Complexity O(M*1.5)
LL cnt_triangles() {
	int cut = ceil(sqrt(m));
	heavy.clear();
	light.clear();
	for(int i = 1; i <= n; ++i) {
		if (adj[i].size() >= cut) {
			mark[i] = 1;
			heavy.push_back(i);
		}
		else {
			mark[i] = 0;
			light.push_back(i);
		}
		sort(adj[i].begin(), adj[i].end());
	}
	LL ans = 0;
	for(int i = 0; i < heavy.size(); ++i) {
		for(int j = i+1; j < heavy.size(); ++j) {
			for(int k = j+1; k < heavy.size(); ++k) {
				int x = heavy[i], y = heavy[j], z = heavy[k];
				if (binary_search(adj[x].begin(), adj[x].end(), y)) {
					if (binary_search(adj[x].begin(), adj[x].end(), z)) {
						if (binary_search(adj[y].begin(), adj[y].end(), z)) {
							ans += 3;
						}
					}
				}
			}
		}
	}
	LL temp = 0;
	for(int i = 0; i < heavy.size(); ++i) {
		int x = heavy[i];
		for(int j = 1; j <= m; ++j) {
			int y = edge[j].fi, z = edge[j].sec;
			if (mark[y] && mark[z]) {
				continue;
			}
			if (binary_search(adj[y].begin(), adj[y].end(), x)) {
				if (binary_search(adj[z].begin(), adj[z].end(), x)) {
					ans += 3;
					if (mark[y] || mark[z]) {
						temp += 3;
					}
				}
			}
		}
	}
	ans -= (temp/2);
	for(int i = 1; i <= m; ++i) {
		int x = edge[i].fi, y = edge[i].sec;
		if (mark[x] == 0 && mark[y] == 0) {
			if (adj[x].size() > adj[y].size()) {
				swap(x, y);
			}
			for(auto z : adj[x]) {
				if (mark[z] == 0) {
					if (binary_search(adj[y].begin(), adj[y].end(), z)) {
						ans += 1;
					}
				}
			}
		}
	}
	ans /= 3;
	return ans;
}
