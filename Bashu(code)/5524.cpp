#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5, maxh = 30;
int xortag, n, m;
struct trie {
	int ch[maxn * maxh][2];
	int sz[maxn * maxh];
	int sum[maxn * maxh][maxh];
	int root = 0;
	int len = 0;
	int tag = 0;
	void insert(int x) {
		int u = root;
		for (int i = maxh - 1; i >= 0; --i) {
			int id = ((x & (1 << i)) > 0);
			if (!ch[u][id]) ch[u][id] = ++len;
			u = ch[u][id];
			++sz[u];
			for (int j = 0; j < maxh; ++j)
				if (x & (1 << j)) sum[u][j]++;
		}
	}
	long long getsum(int x) {
		long long ans = 0;
		for (int i = 0; i < maxh; ++i)
			if (xortag & (1 << i)) ans += (sz[x] - sum[x][i]) * (1LL << i);
			else ans += sum[x][i] * (1LL << i);
		return ans;
	}
	long long query(int x) {
		if (x == 0) return 0;
		int u = root;
		long long ans = 0;
		for (int i = maxh - 1; i >= 0; --i) {
			int l = 0, r = 1;
			if (tag & (1 << i)) swap(l, r);
			if (x <= sz[ch[u][l]]) u = ch[u][l];
			else {
				ans += getsum(ch[u][l]);
				x -= sz[ch[u][l]];
				u = ch[u][r];
			}
		}
		ans += getsum(u) / sz[u] * x;
		return ans;
	}
	int getsize() {
		return sz[ch[root][0]] + sz[ch[root][1]];
	}
} Trie;
struct array {
	int a[maxn + 50];
	int sum[maxn + 50][maxh];
	int len = 0;
	void insert(int x) {
		x ^= xortag;
		a[++len] = x;
		for (int i = 0; i < maxh; ++i)
			sum[len][i] = sum[len - 1][i] + ((x & (1 << i)) > 0);
	}
	long long query(int x) {
		long long ans = 0;
		for (int i = 0; i < maxh; ++i)
			if (xortag & (1 << i)) ans += (x - sum[x][i]) * (1LL << i);
			else ans += sum[x][i] * (1LL << i);
		return ans;
	}
	void transfer() {
		Trie.tag = xortag;
		for (int i = 1; i <= len; ++i)
			Trie.insert(a[i]);
		len = 0;
	}
} Array;
long long query(int x) {
	if (x <= Trie.getsize()) return Trie.query(x);
	else return Trie.query(Trie.getsize()) + Array.query(x - Trie.getsize());
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		int x;
		scanf("%d", &x);
		Array.insert(x);
	}
	scanf("%d", &m);
	for (int i = 1; i <= m; ++i) {
		int op, x, y;
		scanf("%d", &op);
		if (op == 1) {
			scanf("%d", &x);
			Array.insert(x);
		}
		if (op == 2) {
			scanf("%d %d", &x, &y);
			printf("%lld\n", query(y) - query(x - 1));
		}
		if (op == 3) {
			scanf("%d", &x);
			xortag ^= x;
		}
		if (op == 4) Array.transfer();
	}
	return 0;
}