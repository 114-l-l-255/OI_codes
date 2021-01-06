#include <cstdio>
#include <algorithm>
//#include <windows.h>
#define int long long
#define mod 1000000007
using namespace std;
const int MAXN = 50001;
const int MAXK = 11;
long long jie[MAXN];
long long ni[MAXN];
long long C(int down, int up) {
	return jie[down] * ni[down - up] % mod * ni[up] % mod;
}
long long ans[MAXK];
struct SegmentTree {
	int l, r;
	long long val[MAXK], lazyadd, lazymul;
	//first mul than add
} TreeNode[MAXN << 2];
long long arr[MAXN];
void pushup(int o) {
	for (int i = 1; i <= 10ll; i++) {
		TreeNode[o].val[i] = 0;
		for (int j = 0ll; j <= i; j++) {
			TreeNode[o].val[i] += (TreeNode[o << 1].val[j] * TreeNode[o << 1 | 1].val[i - j] % mod + mod) % mod;
			TreeNode[o].val[i] = (TreeNode[o].val[i] % mod + (mod % mod));
		}
	}
}
void pushdown(int o) {
	if (TreeNode[o].lazymul == mod - 1) {
		for (int i = 1; i <= min(10ll, TreeNode[o << 1].r - TreeNode[o << 1].l + 1); i += 2) TreeNode[o << 1].val[i] = (TreeNode[o].lazymul * TreeNode[o << 1].val[i] % mod + mod) % mod;
		for (int i = 1; i <= min(10ll, TreeNode[o << 1 | 1].r - TreeNode[o << 1 | 1].l + 1); i += 2) TreeNode[o << 1 | 1].val[i] = (TreeNode[o].lazymul * TreeNode[o << 1 | 1].val[i] % mod + mod) % mod;
		TreeNode[o << 1].lazyadd = ((mod - TreeNode[o << 1].lazyadd) % mod + mod) % mod; TreeNode[o << 1].lazymul = ((mod - TreeNode[o << 1].lazymul) % mod + mod) % mod;
		TreeNode[o << 1 | 1].lazyadd = ((mod - TreeNode[o << 1 | 1].lazyadd) % mod + mod) % mod; TreeNode[o << 1 | 1].lazymul = ((mod - TreeNode[o << 1 | 1].lazymul) % mod + mod) % mod;
		TreeNode[o].lazymul = 1;
	}
	if (TreeNode[o].lazyadd != 0) {
		long long dp[MAXK];
		for (int i = 0; i <= 10; i++) {
			dp[i] = TreeNode[o << 1].val[i];
			TreeNode[o << 1].val[i] = 0;
		}
		for (int i = 0; i <= min(10ll, TreeNode[o << 1].r - TreeNode[o << 1].l + 1); i++) {
			long long pw = 1;
			for (int j = i; ~j; j--, pw = pw * TreeNode[o].lazyadd % mod) {
				TreeNode[o << 1].val[i] = (TreeNode[o << 1].val[i] + pw * dp[j] % mod * C(TreeNode[o << 1].r - TreeNode[o << 1].l + 1 - j, i - j) % mod) % mod;
			}
		}
		TreeNode[o << 1].lazyadd = ((TreeNode[o << 1].lazyadd + TreeNode[o].lazyadd) % mod + mod) % mod;
		for (int i = 0; i <= 10; i++) {
			dp[i] = TreeNode[o << 1 | 1].val[i];
			TreeNode[o << 1 | 1].val[i] = 0;
		}
		for (int i = 0; i <= min(10ll, TreeNode[o << 1 | 1].r - TreeNode[o << 1 | 1].l + 1); i++) {
			long long pw = 1;
			for (int j = i; ~j; j--, pw = pw * TreeNode[o].lazyadd % mod) {
				TreeNode[o << 1 | 1].val[i] = (TreeNode[o << 1 | 1].val[i] + pw * dp[j] % mod * C(TreeNode[o << 1 | 1].r - TreeNode[o << 1 | 1].l + 1 - j, i - j) % mod) % mod;
			}
		}
		TreeNode[o << 1 | 1].lazyadd = ((TreeNode[o << 1 | 1].lazyadd + TreeNode[o].lazyadd) % mod + mod) % mod;
		TreeNode[o].lazyadd = 0;
	}
}
void build(int l, int r, int o) {
	TreeNode[o].l = l;
	TreeNode[o].r = r;
	TreeNode[o].val[0] = 1;
	TreeNode[o].lazymul = 1;
	if (l == r) {
		TreeNode[o].val[1] = arr[l];
	}
	else {
		int mid = l + r >> 1;
		build(l, mid, o << 1);
		build(mid + 1, r, o << 1 | 1);
		pushup(o);
	}
}
void change(int l, int r, long long x, int type, int o) {
	if (r < TreeNode[o].l || TreeNode[o].r < l) return;
	if (l <= TreeNode[o].l && TreeNode[o].r <= r) {
		if (type) {
			for (int i = 1; i <= min(10ll, TreeNode[o].r - TreeNode[o].l + 1); i += 2) TreeNode[o].val[i] = ((mod - 1) * TreeNode[o].val[i] % mod + mod) % mod;
			TreeNode[o].lazyadd = ((mod - TreeNode[o].lazyadd) % mod + mod) % mod; TreeNode[o].lazymul = ((mod - TreeNode[o].lazymul) % mod + mod) % mod;
 		}
		else {
			long long dp[MAXK];
			for (int i = 0; i <= 10; i++) {
				dp[i] = TreeNode[o].val[i];
				TreeNode[o].val[i] = 0;
			}
			for (int i = 0; i <= min(10ll, TreeNode[o].r - TreeNode[o].l + 1); i++) {
				long long pw = 1;
				for (int j = i; ~j; j--, pw = (pw * x % mod + mod) % mod) {
					TreeNode[o].val[i] = (TreeNode[o].val[i] + pw * dp[j] % mod * C(TreeNode[o].r - TreeNode[o].l + 1 - j, i - j) % mod) % mod;
				}
			}
			TreeNode[o].lazyadd = ((TreeNode[o].lazyadd + x) % mod + mod) % mod;
		}
		return;
	}
	pushdown(o);
	change(l, r, x, type, o << 1);
	change(l, r, x, type, o << 1 | 1);
	pushup(o);
}
void search(int l, int r, int o) {
	if (r < TreeNode[o].l || TreeNode[o].r < l) return;
	if (l <= TreeNode[o].l && TreeNode[o].r <= r) {
//		printf("------------%d %d\n", TreeNode[o].l, TreeNode[o].r);
		int NIT[MAXK];
		for (int i = 0; i < MAXK; i++) {
			NIT[i] = 0;
			for (int j = 0; j <= i; j++) { 
//				if (i == MAXK - 1) printf("%lld ", TreeNode[o].val[j]);
				NIT[i] = (NIT[i] + ans[j] * TreeNode[o].val[i - j] % mod) % mod;
			}
		}
//		printf("\n");
		for (int i = 0; i < MAXK; i++) {
			ans[i] = NIT[i];
//			printf("%lld ", ans[i]);
		}
//		printf("\n");
		return;
	}
	pushdown(o);
	search(l, r, o << 1);
	search(l, r, o << 1 | 1);
}
signed main() {
//	system("fc shik.out game3.out"); return 0;
//	freopen("game3.in", "r", stdin); freopen("shik.out", "w", stdout);
	jie[0] = 1;
	ni[0] = 1;
	for (int i = 1; i <= 50000; i++) {
		jie[i] = (jie[i - 1] * i % mod + mod) % mod;
		long long pw = 1;
		long long a = jie[i];
		long long b = mod - 2;
		while (b) {
			if (b & 1) {
				pw = (pw * a % mod + mod) % mod;
			}
			a = (a * a % mod + mod) % mod;
			b >>= 1;
		}
		ni[i] = pw;
	}
	int n, m;
	scanf("%lld %lld", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &arr[i]);
	}
	build(1, n, 1);
	for (int i = 1; i <= m; i++) {
		int a, b, c, d;
		scanf("%lld %lld %lld", &a, &b, &c);
		if (a == 1) {
			scanf("%lld", &d);
			change(b, c, (long long)d, 0, 1);
		}
		if (a == 2) {
			change(b, c, 1145141919810ll, 1, 1);
		}
		if (a == 3) {
			scanf("%lld", &d);
			for (int i = 0; i < MAXK; i++) {
				ans[i] = 0;
			}
			ans[0] = 1;
			search(b, c, 1);
			printf("%lld\n", ans[d]);
		}
	}
	return 0;
}