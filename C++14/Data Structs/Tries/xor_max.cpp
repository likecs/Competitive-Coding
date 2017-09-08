//Trie implementation for finding xor maximisation & minimisation

const int MAX = 1<<20;
const int LN = 20;

struct node {
	node *child[2];
};
static node trie_alloc[MAX*LN] = {};
static int trie_sz = 0;

node *trie;

node *get_node() {
	node *temp = trie_alloc + (trie_sz++);
	temp->child[0] = NULL;
	temp->child[1] = NULL;
	return temp;
}

//O(log A_MAX)
void insert(node *root, int n) {
	for(int i = LN-1; i >= 0; --i) {
		int x = (n&(1<<i)) ? 1 : 0;
		if (root->child[x] == NULL) {
			root->child[x] = get_node();
		}
		root = root->child[x];
	}
}

//O(log A_MAX)
int query_min(node *root, int n) {
	int ans = 0;
	for(int i = LN-1; i >= 0; --i) {
		int x = (n&(1<<i)) ? 1 : 0;
		assert(root != NULL);
		if (root->child[x] != NULL) {
			root = root->child[x];
		}
		else {
			ans ^= (1<<i);
			root = root->child[1^x];
		}
	}
	return ans;
}

//O(log A_MAX)
int query_max(node *root, int n) {
	int ans = 0;
	for(int i = LN-1; i >= 0; --i) {
		int x = (n&(1<<i)) ? 1 : 0;
		assert(root != NULL);
		if (root->child[1^x] != NULL) {
			ans ^= (1<<i);
			root = root->child[1^x];
		}
		else {
			root = root->child[x];
		}
	}
	return ans;
}