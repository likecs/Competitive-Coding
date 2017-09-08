//Chinese Remainder theorem implementations

//Rem contains the remainder
//Mod contains the modulos vaules
//Modulus values should be pairwise co-prime
vector<int> rem, mods;
vector<pair<int,pair<int,int>>> crt;

int mod_neg(int a, int b, int c) {
	int res; if(abs(a-b) < c) res = a - b;
	else res = (a-b) % c;
	return (res < 0 ? res + c : res);
}

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
	crt.clear();
	int a = 1, b = 1, m = mods[0];
	crt.push_back({mods[0], {a, b}});
	for(int i = 1; i < mods.size(); ++i) {
		a = mod_inverse(m, mods[i]);
		b = mod_inverse(mods[i], m);
		crt.push_back({m, {a, b}});
		m *= mods[i];
	}
}

int find_crt() {
	int ans = rem[0], m = crt[0].first, a, b;
	for(int i = 1; i < mods.size(); ++i) {
		a = crt[i].second.first;
		b = crt[i].second.second;
		m = crt[i].first;
		ans = (1ll*ans * b * mods[i] + 1ll*rem[i] * a * m) % (m * mods[i]);
	}
	return ans;
}