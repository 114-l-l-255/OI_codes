#include <cstdio>
//#pragma GCC optimize(2, 3, 5, "Ofast", "inline", "-fgcse", "-fgcse-lm", "-fipa-sra", "-ftree-pre", "-ftree-vrp", "-fpeephole2", "-ffast-math", "-fsched-spec", "unroll-loops", "-falign-jumps", "-falign-loops", "-falign-labels", "-fdevirtualize", "-fcaller-saves", "-fcrossjumping", "-fthread-jumps", "-funroll-loops", "-fwhole-program", "-freorder-blocks", "-fschedule-insns", "inline-functions", "-ftree-tail-merge", "-fschedule-insns2", "-fstrict-aliasing", "-fstrict-overflow", "-falign-functions", "-fcse-skip-blocks", "-fcse-follow-jumps", "-fsched-interblock", "-fpartial-inlining", "no-stack-protector", "-freorder-functions", "-findirect-inlining", "-fhoist-adjacent-loads", "-frerun-cse-after-loop", "inline-small-functions", "-finline-small-functions", "-ftree-switch-conversion", "-foptimize-sibling-calls", "-fexpensive-optimizations", "-funsafe-loop-optimizations", "inline-functions-called-once", "-fdelete-null-pointer-checks")
#define MAXN 1005
#define MAXT 4000005
int N, M;
int rt[MAXN], ls[MAXT], rs[MAXT], tot, lazy[MAXT], a[MAXT], b[MAXT], sum[MAXT];
//inline void Build(int p, int x, int y) {
//	a[p] = x;
//	b[p] = y;
//	if (x == y) return;
//	int mid = x + y >> 1;
//	ls[p] = ++tot;
//	Build(ls[p], x, mid);
//	rs[p] = ++tot;
//	Build(rs[p], mid + 1, y);
//}
inline void Update(int p) {
	sum[p] = sum[ls[p]] + sum[rs[p]];
}
inline void Putdown(int p) {
	int l = ls[p], r = rs[p];
	if (lazy[p]==-1) {
		sum[l] = sum[r] = 0;
		lazy[l] = lazy[r] = -1;
	}
	else {
		if (lazy[l] == -1) {
			lazy[l] = lazy[p];
			lazy[ls[l]] = lazy[rs[l]] = -1;
			sum[ls[l]] = sum[rs[l]] = 0;
			sum[l] = (b[l] - a[l] + 1) * lazy[p];
		}
		else {
			lazy[l] += lazy[p];
			sum[l] += (b[l] - a[l] + 1) * lazy[p];
		}
		if (lazy[r] == -1) {
			lazy[r] = lazy[p];
			lazy[ls[r]] = lazy[rs[r]]=-1;
			sum[ls[r]] = sum[rs[r]]=0;
			sum[r] = (b[r] - a[r] + 1) * lazy[p];
		}
		else {
			lazy[r] += lazy[p];
			sum[r] += (b[r] - a[r] + 1) * lazy[p];
		}
	}
	lazy[p] = 0;
}
inline void Add(int &p, int l, int r, int x, int y) {
	int mid = l + r >> 1;
	if (p == 0) {
		p = ++tot;
		a[p] = l;
		b[p] = r;
	}
	if (l != r && ls[p] == 0) {
		ls[p] = ++tot;
		a[ls[p]] = l;
		b[ls[p]] = mid;
		rs[p] = ++tot;
		a[rs[p]] = mid + 1;
		b[rs[p]] = r;
	}
	if (r < x || l > y) return;
	if (lazy[p]) Putdown(p);
	if (r <= y && l >= x) {
		lazy[p]++;
		sum[p] += (r - l + 1);
		return;
	}
	Add(ls[p], l, mid, x, y);
	Add(rs[p], mid + 1, r, x, y);
	Update(p);
}
inline int GetSum(int &p, int l, int r, int x, int y) {
	int mid = l + r >> 1;
	if (p == 0) {
		p = ++tot;
		a[p] = l;
		b[p] = r;
	}
	if (l != r && ls[p] == 0) {
		ls[p] = ++tot;
		a[ls[p]] = l;
		b[ls[p]] = mid;
		rs[p] = ++tot;
		a[rs[p]] = mid + 1;
		b[rs[p]] = r;
	}
	if (r < x || l > y) return 0;
	if (lazy[p]) Putdown(p);
//	printf("%d %d %d %d-\n", l, r,lazy[p],sum[p]);
	int L = 0, R = 0;
	if (r <= y && l >= x) {
		L = sum[p];
		lazy[p] = -1;
		sum[p] = 0;
		
		return L;
	}
	L = GetSum(ls[p], l, mid, x, y);
	R = GetSum(rs[p], mid + 1, r, x, y);
	Update(p);
	return L + R;
}
int main() {
	int i, j, k, v, x, y, Ans = 0;
	scanf("%d %d", &N, &M);
//	for (i = 1; i <= 1000; i++) {
//		rt[i] = ++tot;
//		Build(rt[i], 1, N);
//	}
	for (i = 1; i <= M; i++) {
		scanf("%d %d %d %d", &k, &x, &y, &v);
		if(x>y){int z;z=y;y=x;x=z;}
		if (k == 1) {
			for (j = 1; j <= v; j++) {
				Add(rt[j], 1, N, x, y);
			}
		}
		else {
			Ans = 0;
			for (j = 1; j <= v; j++) {
				Ans += GetSum(rt[j], 1, N, x, y);
//				printf("%d---\n", Ans);
			}
			printf("%d\n", Ans);
		}
	}
}