#prime sieve where prime[i] stores a prime factor of i

primes=[0]*1000000

#Complexity: O(n * log2(log2(n)))
def sieve():
	primes[1]=1
	primes[2]=2
	j=4
	while(j<1000000):
		primes[j]=2
		j+=2
	j=3
	while(j<1000000):
		if primes[j]==0:
			primes[j]=j
			i=j*j
			k=j<<1
			while(i<1000000):
				primes[i]=j
				i+=k
		j+=2
