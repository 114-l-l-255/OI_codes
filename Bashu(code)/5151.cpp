#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#define ll long long
using namespace std;
const ll inf = 0x7fffffff;
const ll maxn = 100008, maxm = maxn * 2, mo = 1000000007;
ll t, m, n, i, j, k;
ll f[maxn], F[maxn], g[maxn], G[maxn], h[maxn], H[maxn];
ll fi[maxn], la[maxm], ne[maxm], tot = 0;
void add_line(ll a, ll b) {
	tot++;
	ne[tot] = fi[a];
	la[tot] = b;
	fi[a] = tot;
}
ll read() {
	ll x = 0;
	char ch = getchar();
	while (ch < '0' && ch > '9') ch = getchar();
	while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
	return x;
}
ll qpower(ll a, ll b) {
	ll c = 1;
	while (b) {
		if (b & 1) c = c * a % mo;
		a = a * a % mo;
		b >>= 1;
	}
	return c;
}
ll N(ll a) {
	return qpower(a, mo - 2);
}
void dfs(ll v, ll from) {
	ll i, j = 0, k, sum = 0, times = 1;
	f[v] = 0;
	F[v] = 0;
	g[v] = 0;
	G[v] = 1;
	for (k = fi[v]; k; k = ne[k])
		if (la[k] != from) {
			dfs(la[k], v);
			g[v] += h[la[k]];
			G[v] = G[v] * H[la[k]] % mo;
			sum += h[la[k]];
			times = times * H[la[k]] % mo;
			j = 1;
		}
	for (k = fi[v]; k; k = ne[k]) {
		if (la[k] != from) {
			if (f[v] < sum - h[la[k]] + g[la[k]] + 1) {
				f[v] = sum - h[la[k]] + g[la[k]] + 1;
				F[v] = times * N(H[la[k]]) % mo * G[la[k]] % mo;
			} else if (f[v] == sum - h[la[k]] + g[la[k]] + 1) F[v] = (F[v] + times * N(H[la[k]]) % mo * G[la[k]] % mo) % mo;
		}
	}
	if (f[v] > g[v]) h[v] = f[v], H[v] = F[v];
	else if (f[v] < g[v]) h[v] = g[v], H[v] = G[v];
	else h[v] = f[v], H[v] = (F[v] + G[v]) % mo;
}
int main() {
	t = read();
	m = read();
	while (t--) {
		tot = 0;
		memset(fi, 0, sizeof(fi));
		n = read();
		for (i = 1; i < n; i++) {
			j = read();
			k = read();
			add_line(j, k);
			add_line(k, j);
		}
		dfs(1, 0);
		printf("%lld", h[1]);
		if (m == 2) printf(" %lld", H[1]);
		printf("\n");
	}
	return 0;
}
//https://s3m1.nzwgs.com/galileo/fc101ca3656486c1ba0f7e77a7a824bb.gif