#include <cstdio>
#include <algorithm>
#include <set>
#define lson (o << 1)
#define rson (o << 1 | 1)
using namespace std;
const int MAXN = 50001;
struct node {
	int s, t;
	bool operator < (const node& sec) const {
		return this->s < sec.s;
	}
} line[MAXN];
int data[1000001 << 2], lazy[1000001 << 2], L[1000001 << 2], R[1000001 << 2];
void pushup(int o) {
	data[o] = max(data[lson], data[rson]);
}
void pushdown(int o) {
	data[lson] += lazy[o];
	lazy[lson] += lazy[o]; 
	data[rson] += lazy[o];
	lazy[rson] += lazy[o]; 
	lazy[o] = 0;
}
void build(int o, int l, int r) {
	lazy[o] = 0;
	L[o] = l;
	R[o] = r;
	if (l != r) {
		int mid = l + r >> 1;
		build(lson, l, mid);
		build(rson, mid + 1, r);
		pushup(o);
	}
	else {
		data[o] = 0;
	}
}
void change(int o, int l, int r) {
	if (L[o] > r || R[o] < l) return;
	if (L[o] >= l && R[o] <= r) {
		lazy[o]++;
		data[o]++;
		return;
	}
	pushdown(o);
	change(lson, l, r);
	change(rson, l, r);
	pushup(o);
}
int ask(int o, int l, int r) {
	if (L[o] > r || R[o] < l) return -0x7fffffff;
	if (L[o] >= l && R[o] <= r) return data[o];
	pushdown(o);
	int ans = -0x7fffffff;
	ans = max(ans, ask(lson, l, r));
	ans = max(ans, ask(rson, l, r));
	return ans;
}
int main() {
//	freopen("a.in", "r", stdin);
//	freopen("a.out", "w", stdout);
	int n;
	scanf("%d", &n);
	build(1, 0, 1000000);
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &line[i].s, &line[i].t);
	}
	sort(line + 1, line + 1 + n);
	int Stall = 0;
	for (int i = 1; i <= n; i++) {
		change(1, line[i].s, line[i].t);
	}
	printf("%d", ask(1, 0, 1000000));
	return 0;
}