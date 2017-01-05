//Karger's randomised algorithm for finding Min-cut in undirected graph
//Probabiltity of finding correct min-cut is 2/(V*(V-1))
//This can be improved by performing the same many times
//In code below we can set iterations as per choice

const int MAX = 1e4 + 4;

//Union find implementations
class UnionFind {
private:
	int n, set_size, *parent, *rank;
public:
	UnionFind(int a) {
		n = set_size = a;
		parent = new int[n+1];
		rank = new int[n+1];
		for(int i=1; i<=n; ++i) parent[i]=i, rank[i]=1;
	}
	void print() {
		for(int i=1; i<=n; ++i) printf("%d -> %d\n", i, parent[i]);
	}
	int find(int x) {
		if (x!=parent[x]) return parent[x] = find(parent[x]);
		return x;
	}
	void unite(int x, int y) {
		int xroot = find(x), yroot = find(y);
		if (xroot!=yroot) {
			if (rank[xroot] >= rank[yroot]) {
				parent[yroot] = xroot;
				rank[xroot] += rank[yroot];
			}
			else {
				parent[xroot] = yroot;
				rank[yroot] += rank[xroot];
			}
			set_size -= 1;
		}
	}
	bool same_set(int x, int y) {
		return find(x) == find(y);
	}
	int size() {
		return set_size;
	}
	~UnionFind() {
		delete rank;
		delete parent;
	}
};

class Karger {
private:
	struct edge {
		int from, to;
	};
	int V;
	vector<edge> e;
public:
	Karger (int a) {
		V = a;
	}
	void add_edge(int a, int b) {
		edge temp = {a, b};
		e.push_back(temp);
	}
	int solve() {
		srand(unsigned(time(NULL)));
		UnionFind subsets(V);
		int vertices = V;
		int E = (int)e.size();
		while(vertices > 2) {
			int id = rand() % E;
			subsets.unite(e[id].from, e[id].to);
			vertices = subsets.size();
		}
		int cut_edges = 0;
		for(int i=0; i<E; ++i) {
			if (!subsets.same_set(e[i].from, e[i].to)) {
				cut_edges += 1;
			}
		}
		return cut_edges;
	}
	#define iterations 10
	int min_cut() {
		int ans = (int)e.size();
		for(int i=0; i<iterations; ++i) {
			ans = min(ans, solve());
		}
		return ans;
	}
};
