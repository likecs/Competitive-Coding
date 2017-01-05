const int MAX = 1003;

int dp[MAX], prev[MAX], a[MAX];

// DYNAMIC PROGRAMMING APPROACH - O(n^2)
// dp[i] to be the length of the LIS(Longest increasing subsequence) which is ending at element with index i
int increasingSubsequece(int n) {
    int maxLength = 1, bestEnd = 0;
    dp[0] = 1;
    prev[0] = -1;
    for (int i = 1; i < n; ++i) {
        dp[i] = 1;
        prev[i] = -1;
        for (int j = i-1; j >= 0; --j) {
            if (dp[j] + 1 > dp[i] && a[j] < a[i]) {
                dp[i] = dp[j] + 1;
                prev[i] = j;
            }
        }
        if (dp[i] > maxLength) {
            bestEnd = i;
            maxLength = dp[i];
        }
    }
    // constructing the longest increasing subsequence from prev[] array
    /*
        vector <int> lis;
        for (int j = 0; j < maxLength; ++j)
        {
            lis.push_back(a[bestEnd]);
            bestEnd = prev[bestEnd];
        }
        reverse(lis.begin(), lis.end());
        for (int i = 0; i < lis.size(); ++i)
            printf("%d ", lis[i]);
        printf("\n");
    */
    return maxLength;
}

// BINARY SEARCH, GREEDY ALGORITHM - O(n logn)
// link wikipedia.org/wiki/Longest_increasing_subsequence
int increasingSubsequece2(int n) {
    vector<int> temp;
    vector<int>::iterator v;
    temp.push_back(a[0]);
    for (int i = 1; i < n; ++i) {
        if (a[i] > temp.back()) temp.push_back(a[i]);
        else {
            v = upper_bound(temp.begin(), temp.end(), a[i]);
            *v = a[i];
        }
    }
    //for (int i=0; i<temp.size(); ++i) printf("%d ", temp[i]);
    return temp.size();
}