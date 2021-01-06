#include <iostream>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
pair<ll, ll> calc(ll n, ll m) {
	if (n == 0) {
		return make_pair(0, 0);
	}
	ll len = 1ll << (n - 1), cnt = 1ll << (2 * n - 2);
	pair<ll, ll> pos = calc(n - 1, m % cnt);
	ll x = pos.first, y = pos.second;
	ll z = m / cnt;
	if (z == 0) return make_pair(y, x);
	if (z == 1) return make_pair(x, y + len);
	if (z == 2) return make_pair(x + len, y + len);
	if (z == 3) return make_pair(2 * len - y - 1, len - x - 1);
}
int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		ll n, a, b;
		scanf("%lld %lld %lld", &n, &a, &b);
		pair<ll, ll> posa, posb;
		posa = calc(n, a - 1);
		posb = calc(n, b - 1);
		double ans = (double)sqrt((posa.first - posb.first) * 1.0 * (posa.first - posb.first) + (posa.second - posb.second) * 1.0 * (posa.second - posb.second)) * 10;
		printf("%.0lf\n", ans);
	}
	return 0;
}