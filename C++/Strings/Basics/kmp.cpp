//Knuth-Patt-Morris Algorithm for pattern searching in given string
//Overall Complexity is O(n+k), n = text.size and k = pattern.size

//Returns all positions of matching (0-based indexing)
vector<int> kmp(string &t, string &p) {
	string s = p + '$' + t;
	int n = s.length(), l = p.length();
	vector<int> prefix(n, 0);
	int k = 0;
	for(int i = 1; i < n; ++i) {
		while(k > 0 && s[i] != s[k]) {
			k = prefix[k-1];
		}
		if (s[i] == s[k]) ++k;
		prefix[i] = k;
	}
	vector<int> pos;
	for(int i = l; i < n; ++i) {
		if (prefix[i] == l) {
			pos.push_back(i - l);
		}
	}
	return pos;
}