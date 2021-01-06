#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#define mod 1000000007
using namespace std;
const int MAXN = 100001;
int n, head[MAXN], s[MAXN], id[MAXN], f[MAXN][21], t1, t2, tot = 1;
int x[MAXN], y[MAXN], v[MAXN], ans, f1, f2, be[MAXN];
int deep[MAXN], d[MAXN];
long long A[MAXN];
struct edge {
	int v, nex;
} edges[MAXN << 1];
void add(int t1, int t2) {
	edges[++tot].v = t2;
	edges[tot].nex = head[t1];
	head[t1] = tot;
}
void dfs(int k, int fa) {
	f[k][0] = fa;
	deep[k] = deep[fa] + 1;
	d[k] = d[fa] + s[k];
	for (int i = head[k]; i; i = edges[i].nex) {
		if (edges[i].v != fa) dfs(edges[i].v, k);
	}
}
int find_fa(int k) {
	if (be[k] == k) return k;
	be[k] = find_fa(be[k]);
	return be[k];
}
int Lca(int a, int b) {
	if (deep[a] < deep[b]) swap(a, b);
	for (int x = 20; x >= 0; x--) if (deep[f[a][x]] >= deep[b]) a = f[a][x];
	for (int x = 20; x >= 0; x--) if (f[a][x] != f[b][x]) a = f[a][x], b = f[b][x];
	if (a == b) return a;
	else return f[a][0];
}
int Len(int a, int b) {
	int lca = Lca(a, b);
	return d[a] + d[b] - d[lca] - d[f[lca][0]];
}
long long qkpow(int k, int num) {
	long long ss = 1, p = k;
	while (num) {
		if (num & 1) ss = ss * p;
		p = p * p;
		p %= mod;
		ss = ss % mod;
		num >>= 1;
	}
	return ss;
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &s[i]);
	for (int i = 1; i < n; i++) {
		scanf("%d %d", &t1, &t2);
		add(t1, t2);
		add(t2, t1);
	}
	for (int i = 1; i < n; i++) scanf("%d", &id[i]);
	dfs(1, 0);
	for (int j = 1; j <= 20; j++) {
		for (int i = 1; i <= n; i++) {
			f[i][j] = f[f[i][j - 1]][j - 1];
		}
	}
	long long ans = 1;
	for (int i = 1; i <= n; i++) {
		x[i] = y[i] = i;
		v[i] = s[i];
		ans = ans * s[i] % mod;
		be[i] = i;
	}
	A[n] = ans;
	for (int num = n - 1; num >= 1; num--) {
		int t1 = edges[id[num] * 2].v, t2 = edges[id[num] * 2+1].v;
		if (f[t1][0] != t2) swap(t1, t2);
		f1 = find_fa(t1);
		f2 = find_fa(t2);
		be[f1] = f2;
		int ax = x[f1], ay = y[f1], bx = x[f2], by = y[f2];
		int ansx, ansy, ansv, T;
		if (v[f1] > v[f2]) ansv = v[f1], ansx = ax, ansy = ay;
		else ansv = v[f2], ansx = bx, ansy = by;
		T = Len(ax, bx);
		if (T > ansv) ansv = T, ansx = ax, ansy = bx;
		T = Len(ax, by);
		if (T > ansv) ansv = T, ansx = ax, ansy = by;
		T = Len(ay, bx);
		if (T > ansv) ansv = T, ansx = ay, ansy = bx;
		T = Len(ay, by);
		if (T > ansv) ansv = T, ansx = ay, ansy = by;
		ans = ans * qkpow(v[f1], mod - 2) % mod * qkpow(v[f2], mod - 2) % mod;
		v[f2] = ansv;
		x[f2] = ansx, y[f2] = ansy;
		ans = ans * ansv % mod;
		A[num] = ans;
	}
	for (int i = 1; i <= n; i++) {
		printf("%lld\n", A[i]);
	}
	return 0;
}