//Chinese Remainder theorem implementations

//Rem contains the remainder
//Mod contains the modulos vaules
//Modulus values should be pairwise co-prime
vector<int> rem, mod;

template<typename T> T extended_euclid(T a, T b, T &x, T &y) {
	T xx = 0, yy = 1; y = 0; x = 1;
	while(b) {
		T q = a / b, t = b;
		b = a % b; a = t;
		t = xx; xx = x - q * xx;
		x = t; t = yy;
		yy = y - q * yy; y = t;
	}
	return a;
}
 
template<typename T> T mod_inverse(T a, T n) {
	T x, y, z = 0; 
	T d = extended_euclid(a, n, x, y);
	return (d > 1 ? -1 : mod_neg(x, z, n));
}

void pre_process() {
	int a = 1, b = 1, m = mod[0];
	crt.push_back({mod[0], {a, b}});
	for(int i = 1; i < mod.size(); ++i) {
		a = mod_inverse(m, mod[i]);
		b = mod_inverse(mod[i], m);
		crt.push_back({m, {a, b}});
		m *= mod[i];
	}
}
 
int find_crt() {
	int ans = rem[0], m = crt[0].first, a, b;
	for(int i = 1; i < mod.size(); ++i) {
		a = crt[i].second.first;
		b = crt[i].second.second;
		m = crt[i].first;
		ans = (1LL*ans * b * mod[i] + 1LL*rem[i] * a * m) % (m * mod[i]);
	}
	return ans;
}