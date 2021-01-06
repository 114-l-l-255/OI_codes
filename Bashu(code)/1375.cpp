#include <bits/stdc++.h>
#define MAXN 200005
#define mod 1000000007
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
ll n, m, q;
char s1[MAXN], s2[MAXN];
ull h1[MAXN], h2[MAXN], bs[MAXN];
map<ll, ll> mp;
int check(ll dex, ll len) {
	return h1[dex + len - 1] - h1[dex - 1] * bs[len] == h2[len];
}
int main() {
	cin >> n >> m >> q;
	cin >> s1 + 1 >> s2 + 1;
	bs[0] = 1;
	for (int i = 1; i <= n; i++) {
		h1[i] = h1[i - 1] * 131 + s1[i] - 'a' + 1;
		bs[i] = bs[i - 1] * 131;
	}
	for (int i = 1; i <= m; i++) {
		h2[i] = h2[i - 1] * 131 + s2[i] - 'a' + 1;
	}
	for (ll i = 1; i <= n; i++) {
		ll l = 0, r = m + 1, mn = 0;
		while (l < r) {
			ll mid = (l + r) / 2;
			if (check(i, mid)) {
				mn = mid;
				l = mid + 1;
			} else {
				r = mid;
			}
		}
		mp[mn]++;
	}
	int x;
	for (int i = 0; i < q; i++) {
		cin >> x;
		cout << mp[x] << '\n';
	}
}
/*
6 2 5
aabcde
ab
0
1
2
3
4
5
*/