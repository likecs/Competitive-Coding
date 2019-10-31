/*
    
Input: "bbbab"
Output: 4

Input: "cbbd"

Output: 2
*/

class Solution {
public:
    int dp[1000][1000];
    int solve(string &s,int i, int j)
    {
        if(i==j)
        {
            return 1;
        }
        else if(i>j)
        {
            return 0;
        }
        else if(dp[i][j]!=-1)
        {
            return dp[i][j];
        }
        else
        {
            if(s[i]==s[j])
            {
                dp[i][j]=2+solve(s,i+1,j-1);
            }
            else
            {
                dp[i][j]=max(solve(s,i+1,j),solve(s,i,j-1));
            }
            return dp[i][j];
        }
    }
    int longestPalindromeSubseq(string s) {
        int n=s.length();
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                dp[i][j]=-1;
            }
        }
        int ans=solve(s,0,n-1);
        return ans;
    }
};