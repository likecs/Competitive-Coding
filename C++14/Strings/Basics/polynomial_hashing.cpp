#include <bits/stdc++.h>
using namespace std ;

//uses natural mod 2^64 , assume 0 based indexing everywhere
struct PolynomialHashing {
	int N;
	string s;
	char offset = 0;
	long long prime;
	long long *fHash, *rHash, *pk;

	//declare two instances with different primes as base to be more certain of not falling for anti hash cases
	PolynomialHashing(string str, long long pri = 257) : s(str), prime(pri) {
		N = s.size();
		fHash = new long long[N], rHash = new  long long[N], pk = new  long long[N];
		fHash[0] = s[0] - offset + 1;
		pk[0] = 1;
		rHash[N - 1] = s[N - 1] - offset + 1;
		//Complexity : O(n)
		for(int i = 1; i < N; i++) {
			fHash[i] = fHash[i - 1] * prime + s[i] - offset + 1;
			pk[i] = pk[i - 1] * prime;
			rHash[N - 1 - i] = rHash[N - i] * prime + s[N - i - 1] - offset + 1;
		}
	}
	//front hash of subtring from (l,r)
	long long getFrontHash (long long l, long long r) {
		if(l == 0) return fHash[r];
		if(l > r) return 0;
		return fHash[r] - fHash[l - 1] * pk[r - l + 1];
	}
	//reverse hash of subtring from (l,r)
	long long getReverseHash(long long l, long long r) {
		if(r == N - 1) return rHash[l];
		if(l > r) return 0;
		return rHash[l] - rHash[r + 1] * pk[r - l + 1];
	}
};

int main(){
	string s = "akshitchopra" ;
	PolynomialHashing ph(s,31) ;
	cout << ph.getFrontHash(0,4) << endl ;
	return 0 ;
}