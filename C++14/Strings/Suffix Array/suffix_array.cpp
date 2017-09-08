#include <bits/stdc++.h>
using namespace std ;

// http://apps.topcoder.com/forums/?module=RevisionHistory&messageID=1171511
template <size_t max_size, typename char_type> struct suffix_array {
	char_type str[max_size];
	// rank[i] stores the rank of suffix at position i when stored in sorted order
	// pos[i] records starting position of the ith suffix in sorted order
	int rank[max_size], pos[max_size];
	// lcp of suffix[i, i-1], lcp[0] = 0
	int lcp[max_size];
	// lcp[i] length of longest prefix of ith and (i - 1)th suffix in sorted order
	int cnt[max_size], next[max_size];
	bool bh[max_size], b2h[max_size];

	void reset() {
		for(int i = 0 ; i < max_size ; i++) {
			rank[i] = pos[i] = lcp[i] = cnt[i] = next[i] = bh[i] = b2h[i] = 0 ;
		}
	}

	void build(int n) {
		for(int i = 0; i < n; ++i) pos[i] = i;
		sort(pos, pos + n, ord_by_first_char(str));
		for(int i = 0; i < n; ++i) {
			bh[i] = (i == 0 || str[pos[i]] != str[pos[i-1]]);
			b2h[i] = false;
		}
		// Complexity : O(nlogn)
		for(int h = 1; h < n; h <<= 1) {
			int buckets = 0;
			for(int i = 0, j; i < n; i = j) {
				j = i + 1;
				while(j < n && !bh[j]) ++j;
				next[i] = j;
				++buckets;
			}
			if(buckets==n) break;
			for(int i = 0; i < n; i = next[i]) {
				cnt[i] = 0;
				for(int j = i; j < next[i]; ++j) rank[pos[j]] = i;
			}
			++cnt[rank[n-h]];
			b2h[rank[n-h]] = true;
			for(int i = 0; i < n; i = next[i]) {
				for(int j = i; j < next[i]; ++j) {
					int s = pos[j]-h;
					if(s >= 0) {
						int head = rank[s];
						rank[s] = head + cnt[head]++;
						b2h[rank[s]] = true;
					}
				}
				for(int j = i; j < next[i]; ++j) {
					int s = pos[j]-h;
					if(s >= 0 && b2h[rank[s]])
						for(int k = rank[s]+1; !bh[k] && b2h[k]; ++k)
							b2h[k]=false;
				}
			}
			for(int i = 0; i < n; ++i) {
				pos[rank[i]] = i;
				bh[i]| = b2h[i];
			}
		}
		for(int i = 0; i < n; ++i) rank[pos[i]] = i;
		lcp[0] = 0;
		//Lcp array using Kasai algorithm
		//Complexity : O(n)
		for(int i = 0, h = 0; i < n; ++i) {
			if (rank[i] > 0) {
				int j = pos[rank[i]-1];
				while(i+h < n && j+h < n && str[i+h]==str[j+h]) ++h;
				lcp[rank[i]] = h;
				if(h > 0) --h;
			}
		}
	}

	struct ord_by_first_char {
		ord_by_first_char(char_type const *_s): s(_s) {}
		bool operator() (int a, int b) {
			return s[a] < s[b];
		}
		char_type const *s;
	};
};

int main() {
	suffix_array<100002 , char> sa;
	scanf("%s", sa.str );
	sa.build(strlen(sa.str));
	return 0;
}
