/*
Optimising the MOD operations using ASM code injection.
source : https://www.codechef.com/viewsolution/8323651
usage:
Let res = (a * b) % m and dummy is any unused "unsigned int"
variable. Then use the below line-
fasterLLDivMod((unsigned long long)a * b, m, dummy, res);
*/

inline void fasterLLDivMod(unsigned long long x, unsigned y, unsigned &out_d, unsigned &out_m) {
	unsigned xh = (unsigned)(x >> 32), xl = (unsigned)x, d, m;
#ifdef __GNUC__
	asm (
		"divl %4; \n\t"
		: "=a" (d), "=d" (m)
		: "d" (xh), "a" (xl), "r" (y)
		);
#else
	__asm {
		mov edx, dword ptr [xh];
		mov eax, dword ptr [xl];
		div dword ptr [y];
		mov dword ptr [d], eax;
		mov dword ptr [m], edx;
	};
#endif
	out_d = d; out_m = m;
}
