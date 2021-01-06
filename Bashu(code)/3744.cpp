#include <cstdio>
const int MAXN = 20001;
unsigned long long bs[MAXN], h[MAXN];
int a[MAXN];
struct edge {
	int hd;
	int val;
	unsigned long long to;
	int nxt;
} edges[MAXN];
int head[20090314], tot;
unsigned long long Hash(int l, int r) {
	return h[r] - h[l - 1] * bs[r - l + 1];
}
void cl() {
	for (int i = 0; i < tot; i++) head[edges[i].hd] = 0;
	tot = 0;
}
void insert(unsigned long long x) {
	int hed = x % 20090314;
	for (int i = head[hed]; i; i = edges[i].nxt) {
		if (edges[i].to == x) {
			edges[i].val++;
			return;
		}
	}
	edges[++tot].hd = hed;
	edges[tot].val = 1;
	edges[tot].to = x;
	edges[tot].nxt = head[hed];
	head[hed] = tot;
}
int find(unsigned long long x) {
	int hed = x % 20090314;
	for (int i = head[hed]; i; i = edges[i].nxt) {
		if (edges[i].to == x) {
			return edges[i].val;
		}
	}
	return 0;
}
int main() {
	int n, k;
	scanf("%d %d", &n, &k);
	bs[0] = 1;
	for (int i = 1; i < n; i++) {
		bs[i] = bs[i - 1] * 1145141;
	}
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		if (i) h[i] = h[i - 1] * 1145141 + a[i];
		else h[i] = a[i]; 
	}
	int l = 1, r = n;
	while (l + 1 < r) {
		int mid = l + r >> 1;
		cl();
		int ansd = 0;
		for (int i = 0; i + mid - 1 < n; i++) {
			unsigned long long has = Hash(i, i + mid - 1);
			int times = find(has);
			ansd = ansd > times + 1 ? ansd : times + 1;
			insert(has);
		} 
		if (ansd >= k) l = mid;
		else r = mid;
	}
	printf("%d", l);
	return 0;
}