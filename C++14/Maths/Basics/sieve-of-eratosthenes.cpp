#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define endl '\n'
#define mod 1000000007

bool prime[1000001];
void sieve(int n)
{
	for(int i=2;i<=n;i++)
		prime[i]=true;					// setting all values as true
	for(int i=2;i<=sqrt(n);i++)
	{
		if(prime[i])
		{
			// Update all multiples of i greater than or equal to the square of it 
            		// numbers which are multiple of i and are less than i^2 are already been marked.  
			for(int j=i*i;j<=n;j+=i)
				prime[j]=false;
		}
	}
}
int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    #ifndef ONLINE_JUDGE
    // for getting input from input.txt
    freopen("input.txt", "r", stdin);
    // for writing output to output.txt
    freopen("output.txt", "w", stdout);
    #endif

    int n;
    cin>>n;
    sieve(n);
    for(int i=1;i<=n;i++)
    {
    	if(prime[i])
    		cout<<i<<" ";			// printing the prime numbers till n
    }
	return 0;
}
