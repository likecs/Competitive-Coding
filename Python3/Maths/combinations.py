#General library for finding nCr modulo m
#where m, n, r can be any integer without any limits
#For usge just call the function ncr(n, r, m)

def factorise(m):
	ans = []
	p = 2
	while(m != 1):
		if (m%p != 0):
			p += 1
			continue
		e = 0
		while(m % p == 0) :
			m //= p
			e += 1
		ans.append([p, e])
		p += 1
	return ans

def mulmod(a, b, c):
	res = a * b
	if (res >= c):
		res %= c
	return res

def mod_inverse(a, n):
	N = n
	xx = 0
	yy = 1
	y = 0
	x = 1
	while(n > 0):
		q = a // n
		t = n
		n = a % n
		a = t
		t = xx
		xx = x - q * xx
		x = t
		t = yy
		yy = y - q * yy
		y = t
	x %= N
	x += N
	x %= N
	return x

def expo(a, b):
	x = 1
	y = a
	while(b > 0):
		if (b&1):
			x = x * y
		y = y * y
		b >>= 1
	return x

def power(a, b, c):
	x = 1
	y = a
	while(b > 0):
		if (b&1):
			x = mulmod(x, y, c)
		y = mulmod(y, y, c)
		b >>= 1
	return x

def init(p, pk):
	fact = []
	fact.append(1)
	for i in range(1, pk):
		red = i
		if (red % p == 0):
			red = 1
		fact.append(mulmod(fact[i-1], red, pk))
	return fact

def fact_mod(n, p, pk, fact):
	res = 1
	while(n > 0):
		times = n//pk
		res = mulmod(res, power(fact[pk-1], times, pk), pk)
		res = mulmod(res, fact[n%pk], pk)
		n //= p
	return res

def count_fact(n, p):
	ans = 0
	while(n > 0):
		ans += n//p
		n //= p
	return ans

def ncr_pk(n, r, p, e):
	if (r > n or r < 0):
		return 0
	if (r == 0 or n == r):
		return 1
	_e = count_fact(n, p) - count_fact(r, p) - count_fact(n-r, p)
	assert(_e >= 0)
	if (_e >= e):
		return 0
	pk = expo(p, e)
	fact = init(p, pk)
	ans = fact_mod(n, p, pk, fact)
	ans = mulmod(ans, mod_inverse(fact_mod(r, p, pk, fact), pk), pk)
	ans = mulmod(ans, mod_inverse(fact_mod(n-r, p, pk, fact), pk), pk)
	ans = mulmod(ans, expo(p, _e), pk)
	return ans

def pre_process(rem, mods):
	crt = []
	a = 1
	b = 1
	m = mods[0]
	crt.append([mods[0], a, b])
	L =	len(mods)
	for i in range(1, L):
		a = mod_inverse(m, mods[i])
		b = mod_inverse(mods[i], m)
		crt.append([m, a, b])
		m *= mods[i]
	assert(len(crt) == len(mods))
	return crt

def find_crt(rem, mods, crt):
	assert(len(crt) == len(mods))
	ans = rem[0]
	m = crt[0][0]
	L = len(mods)
	for i in range(1, L):
		a = crt[i][1]
		b = crt[i][2]
		m = crt[i][0]
		_m = m * mods[i]
		ans = mulmod(ans, b * mods[i], _m)
		ans = (ans + mulmod(rem[i], a * m, _m)) % (_m)
	return ans

def ncr(n, r, m):
	pf = factorise(m)
	rem = []
	mods = []
	L = len(pf)
	for i in range(L):
		get = ncr_pk(n, r, pf[i][0], pf[i][1])
		rem.append(get)
		mods.append(expo(pf[i][0], pf[i][1]))
	crt = pre_process(rem, mods)
	ans = find_crt(rem, mods, crt)
	return ans
