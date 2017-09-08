//Really fast I/O for C++
//If unlocked version is supported on ONLINE JUDGES, just remove the comments below
//Codechef, Hackerearth and Spoj support unlocked versions, but Codeforces doesn't

#define inchar			getchar//_unlocked
#define outchar(x)		putchar(x)//_unlocked(x)

//General I/O, works for both int and long long (signed and unsigned versions)
template<typename T> void inpos(T &x) {
	x = 0;
	register T c = inchar();
	while(((c < 48) || (c > 57)) && (c != '-')) c = inchar();
	bool neg = false;
	if (c=='-') neg = true;
	for(; c < 48 || c > 57; c = inchar()) ;
	for(; c > 47 && c < 58; c = inchar()) {
		x = (x<<3) + (x<<1) + (c&15);
	}
	if(neg) x = -x;
}

template<typename T> void outpos(T n) {
	if(n < 0) { outchar('-'); n *= -1; }
	char snum[65];
	int i = 0;
	do {
		snum[i++] = n % 10 + '0';
		n /= 10;
	} while(n);
	i = i - 1;
	while (i >= 0) outchar(snum[i--]);
	outchar('\n');			//change this to ouchar(' '), if you want space separated output
}

//Fast I/O for character arrays (not for stings in c++)
inline void instr(char *str) {
	register char c = 0;
	register int i = 0;
	while (c < 33) c = inchar();
	while (c != '\n' && c != ' ' && c != EOF) {
		str[i] = c;
		c = inchar(); ++i;
	}
	str[i] = '\0';
}