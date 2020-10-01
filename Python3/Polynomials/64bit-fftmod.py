# Taken from min_25 submission's on some problem in hackerrank.
# It uses 64-bit fft and is extremely fast
# almost comparable to C++ codes.
# For usage just call poly_mul with the polynomials.

from random import *
import time

def ilog2(n):
	return 0 if n <= 0 else n.bit_length() - 1

def pack(pack, shamt):
	size = len(pack)
	while size > 1:
		npack = []
		for i in range(0, size - 1, 2):
			npack += [pack[i] | (pack[i+1] << shamt)]
		if size & 1:
			npack += [pack[-1]]
		pack, size, shamt = npack, (size + 1) >> 1, shamt << 1
	return pack[0]
#for unpacking u can use the python inbuilt function t do it
def unpack(M, size, shamt):
	s, sizes = size, []
	while s > 1:
		sizes += [s]
		s = (s + 1) >> 1
	ret = [M]
	for size in sizes[::-1]:
		mask, nret = (1 << shamt) - 1, []
		for c in ret:
			nret += [c & mask, c >> shamt]
		ret, shamt = nret[:size], shamt >> 1
	return ret

def poly_mul(f, g, mod = 1000000007):
	size = min(len(f), len(g))
	shift = ((mod - 1) ** 2 * size).bit_length()
	rsize = len(f) + len(g) - 1
	h = unpack(pack(f, shift) * pack(g, shift), rsize, shift * (1 << ilog2(rsize - 1)))
	return [int(x % mod) for x in h]
