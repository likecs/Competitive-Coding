/*
Given a string containing just the characters '(' and ')', find the length of the longest valid parentheses substring.
Required space complexity O(|s|) and time complexity O(|s|) where |s| = length of given string.
Example 1:
Input: "(()"
Output: 2
Explanation: "()"

Example 2:
Input: ")()())"
Output: 4
Explanation:"()()"
*/

/* 0 based indexing is used */

int longestValidParentheses(string s)
{
    int n=s.length();
    if(n<2)
    {
        return 0;
    }
    int dp[n];
    int max1=0;
    for(int i=0; i<n; i++)
    {
        dp[i]=0;
    }
    for(int i=1; i<n; i++)
    {
        if(s[i]==')')
        {
            if(s[i-1]=='(')
            {
                if(i-2>=0)
                    dp[i]=dp[i-2]+2;
                else
                    dp[i]=2;
            }
            else
            {
                int ind=i-dp[i-1]-1;
                if(ind>=0&& s[ind]=='(')
                {
                    if(ind-1>=0)
                    {
                        dp[i]=dp[i-1]+dp[ind-1]+2;
                    }
                    else
                    {
                        dp[i]=dp[i-1]+2;
                    }
                }
            }
        }
        max1=max(max1,dp[i]);
    }
    return max1;
}
