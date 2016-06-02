//Knuth-Patt-Morris Algorithm for pattern searching in given string
//Overall Complexity is O(n+k), n = text.size and k = pattern.size

//Complexity is O(k)
void prefix_function(vector<int>& pre, const string& str) {
	pre[0] = -1;
	int j = -1;
	for (int i=1 ; i<str.size(); ++i) {
		while (j>=0 && str[i]!=str[j+1]) {
			j = pre[j];
		}
		if (str[i] == str[j + 1]) pre[i] = ++j;
		else pre[i] = -1;
	}
}

//returns all positions of matched in given text
vector<int> kmp(string text, string pattern) {
	vector<int> pre(pattern.size());
	vector<int> ans;
	if (pattern.size() == 0) return ans;
	prefix_function(pre, pattern);
	int j = -1;
	//Complexity is O(n)
	for (int i=0 ; i<text.size(); ++i) {
		while (j>=0 && text[i]!=pattern[j + 1]) {
			j = pre[j];
		}
		if (text[i] == pattern[j + 1]) {
			j++;
			if (j+1 == pattern.size()) {
				ans.push_back(i - j);
				j = pre[j];
			}
		}
	}
	return ans;
}