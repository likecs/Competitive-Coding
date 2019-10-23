

// Length of Longest Inceasing Subsequence
// DYNAMIC PROGRAMMING APPROACH - O(m*n) where m and n are the length of strings



int lcs(string s, string t) {
	int m = (int)s.length();
	int n = (int)t.length();


	vector<vector<int> > dp(m+1, vector<int>(n+1));

	for(int i=0; i<=m; i++) {
		for(int j=0; j<=n; j++) {			// dp[i][j] stores the length of lcs of {s[0:i-1] and t[0:j-1]}
			if(i==0 || j==0) 				
				dp[i][j] = 0;
			else if(s[i-1] == t[j-1])		//s[i-1] == t[j-1] , then length (lcs of {s[0:i] and t[0:j]}) =  length(lcs of {s[0:i-1] and t[0:j-1]});
				dp[i][j] = dp[i-1][j-1]+1;
			}
			else 							// s[i-1] != t[j-1], then length (lcs of {s[0:i] and t[0:j]}) =  max(length(lcs of {s[0:i] and t[0:j-1]}), length(lcs of {s[0:i-1] and t[0:j]}));
				dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
		}
	}


	return dp[m][n];

}
