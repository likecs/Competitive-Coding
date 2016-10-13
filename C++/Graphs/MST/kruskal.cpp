//Implementation of Kruskal algorithm for minimum spanning tree

//Union fin data stucture
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

// Complexity : O(Alpha(V)), Alpha is Inverse Ackermann function
class Kruskal {
private:
	struct edge {
		int u, v;
		int weight;
		friend bool operator < (const edge& one, const edge& two) {
			return one.weight < two.weight;
		}
	};
	int V, E;
public:
	vector<edge> adj;
	vector<edge> MST;
	Kruskal (int n, int m, bool type=false) {
		V = n;
		E = m;
	}
	void clear() {
		adj.clear();
		MST.clear();
	}
	void add_edge(int a, int b, int c) {
		edge e = {a, b, c};
		adj.push_back(e);
	}
	int solve(int source) {
		sort(adj.begin(), adj.end());
		UnionFind temp(V);
		MST.clear();
		int cnt = 0;
		int mst_weight = 0;
		for(int i=0; i<E; ++i) {
			if (!temp.same_set(adj[i].u, adj[i].v)) {
				temp.unite(adj[i].u, adj[i].v);
				MST.push_back(adj[i]);
				cnt += 1;
				mst_weight += adj[i].weight;
			}
		}
		return mst_weight;
	}
	void print() {
		printf("Edges in MST are : \n");
		for(int i=0; i<V-1; ++i) {
			printf("%d : %d %d %d\n", i, MST[i].u, MST[i].v, MST[i].weight);
		}
		printf("\n");
	}
};
