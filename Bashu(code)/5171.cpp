#include <cstdio>
#include <algorithm>
#define int long long
using namespace std;
const int MAXN = 200001;
struct edge {
	int to, nxt;
} edges[MAXN];
struct sol {
	int b, l;
} s[MAXN];
int head[MAXN], tot;
int timet, dfn[MAXN], dfn_[MAXN];
bool leaf[MAXN];
int val[MAXN << 2], val2[MAXN << 2];
int Fst[MAXN], Scd[MAXN], Th[MAXN];
void build(int l, int r, int o) {
	if (l == r) {
		val[o] = s[l].l;
		val2[o] = -1;
	}
	else {
		int mid = l + r >> 1;
		build(l, mid, o << 1);
		build(mid + 1, r, o << 1 | 1);
		val[o] = val2[o] = -1;
		if (val[o << 1] > val[o]) {
			val2[o] = val[o];
			val[o] = val[o << 1];
		}
		else if (val[o << 1] != val[o] && val[o << 1] > val2[o]) {
			val2[o] = val[o << 1];
		}
		if (val2[o << 1] != val[o] && val2[o << 1] > val2[o]) {
			val2[o] = val2[o << 1];
		}
		
		if (val[o << 1 | 1] > val[o]) {
			val2[o] = val[o];
			val[o] = val[o << 1 | 1];
		}
		else if (val[o << 1 | 1] != val[o] && val[o << 1 | 1] > val2[o]) {
			val2[o] = val[o << 1 | 1];
		}
		if (val2[o << 1 | 1] != val[o] && val2[o << 1 | 1] > val2[o]) {
			val2[o] = val2[o << 1 | 1];
		}
//		val[o] = max(val[o << 1], val[o << 1 | 1]);
//		val[o] = max(val)
	}
}
pair<int, int> search(int l, int r, int a, int b, int o) {
	if (a <= l && r <= b) {
		return make_pair(val[o], val2[o]);
	}
	else {
		int mid = l + r >> 1;
		int ans = -1, ans2 = -1;
		if (a <= mid) {
			pair<int, int> vala = search(l, mid, a, b, o << 1);
			if (vala.first > ans) {
				ans2 = ans;
				ans = vala.first;
			}
			else if (vala.first != ans && vala.first > ans2) {
				ans2 = vala.first;
			}
			if (vala.second != ans && vala.second > ans2) {
				ans2 = vala.second;
			}
		}
		if (mid < b) {
			pair<int, int> vala = search(mid + 1, r, a, b, o << 1 | 1);
			if (vala.first > ans) {
				ans2 = ans;
				ans = vala.first;
			}
			else if (vala.first != ans && vala.first > ans2) {
				ans2 = vala.first;
			}
			if (vala.second != ans && vala.second > ans2) {
				ans2 = vala.second;
			}
		}
		return make_pair(ans, ans2);
	}
}
void add(int u, int v) {
	edges[++tot].to = v;
	edges[tot].nxt = head[u];
	head[u] = tot;
}
void dfs(int x) {
	timet++;
	dfn[x] = timet;
	for (int i = head[x]; i; i = edges[i].nxt) {
		dfs(edges[i].to);
	} 
	dfn_[x] = timet;
}
void dfs_(int x) {
	Fst[x] = s[dfn[x]].b;
	Scd[x] = -1;
	Th[x] = -1;
	for (int i = head[x]; i; i = edges[i].nxt) {
		dfs_(edges[i].to);
		int v = edges[i].to;
		if (Fst[v] >= Fst[x]) {
			if (Fst[x] != Scd[x]) Th[x] = Scd[x];
			Scd[x] = Fst[x];
			Fst[x] = Fst[v];
		}
		else if (Fst[v] > Scd[x]) {
			Th[x] = Scd[x];
			Scd[x] = Fst[v];
		}
		else if (Fst[v] != Scd[x] && Fst[v] > Th[x]) {
			Th[x] = Fst[v];
		}
		
		
		if (Scd[v] > Scd[x]) {
			Th[x] = Scd[x];
			Scd[x] = Scd[v];
		}
		else if (Scd[v] != Scd[x] && Scd[v] > Th[x]) {
			Th[x] = Scd[v];
		}
		
		
		if (Th[v] != Scd[x] && Th[v] > Th[x]) {
			Th[x] = Th[v];
		}
	}
}
signed main() {
//	freopen("soldier.in", "r", stdin);
//	freopen("soldier.out", "w", stdout);
	int n, q;
	scanf("%lld %lld", &n, &q);
	for (int i = 2; i <= n; i++) {
		int f;
		scanf("%lld", &f);
		add(f, i);
	}
	dfs(1);
	for (int i = 1; i <= n; i++) {
		scanf("%lld %lld", &s[dfn[i]].b, &s[dfn[i]].l);
	}
	dfs_(1);
	build(1, n, 1);
//	for (int i = 1; i <= n; i++) {
//		printf("%d %d\n", Fst[i], Scd[i]);
//	}
	for (int i = 0; i < q; i++) {
		int Q;
		scanf("%lld", &Q);
		int FST = Fst[Q];
		int SCD = Scd[Q];
		int TH = Th[Q];
		//FST >= SCD > TH
		pair<int, int> Some = make_pair(-1, -1);
		//Some.first > Some.second
		if (dfn[Q] != 1) {
			Some = search(1, n, 1, dfn[Q] - 1, 1);
		}
		if (dfn_[Q] != n) {
			pair<int, int> vala = search(1, n, dfn_[Q] + 1, n, 1);
			if (vala.first > Some.first) {
				Some.second = Some.first;
				Some.first = vala.first;
			}
			else if (vala.first != Some.first && vala.first > Some.second) {
				Some.second = vala.first;
			}
			
			
			if (vala.second != Some.first && vala.second > Some.second) {
				Some.second = vala.second;
			}
		}
		int Arr[3] = {FST, SCD, TH};
		int Brr[3] = {0, Some.first, Some.second};
		int ans = 0;
		for (int i = 1; i < 3; i++) {
			if (Arr[i] == -1) continue;
			for (int j = 0; j < 3; j++) {
				if (Brr[j] == -1) continue;
				if (Arr[i] + Brr[j] == Arr[0]) continue;
				ans = max(ans, min(Arr[i] + Brr[j], Arr[0]));
			}
		}
		printf("%lld\n", ans);
//		printf("%lld %lld %lld %lld %lld %lld\n", Arr[0], Arr[1], Arr[2], Brr[0], Brr[1], Brr[2]);
	}
	return 0;
}
/*
当从大到小排序(个毛线)

贪心

Ans = min(a[2] + max_help, a[1])

      (2,1)
       / \
   (1,5) (4,2)
    / \
(2,3) (3,1)

Ans2 = (...

5 2
1 1 2 2
2 1
1 5
4 2
2 3
3 1
1
2

7 3
1 1 2 2 3 3
3 0
1 3
5 2
2 0
4 1
3 1
2 2
1 2 3

*/