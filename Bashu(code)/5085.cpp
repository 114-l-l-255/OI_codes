#include <cstdio>
#include <algorithm>
#define int long long
using namespace std;
const int MAXN = 100005;
int dp1[MAXN], dp2[MAXN];
pair<int, int> Tree[MAXN];
//    |    |
// 方案数 答案  答案大的优先, 方案数累加. 
int n;
int lowbit(int x) {
	return x & -x;
}
void ADDEQ(pair<int, int>& F, const pair<int, int>& S) {
	if (F.second < S.second) {
		F.second = S.second;
		F.first = S.first;
	}
	else if (F.second == S.second) {
		F.first += S.first;
	}
}
void change(int x, int xxx) {
	pair<int, int> xx = make_pair(dp1[xxx], dp2[xxx]);
	while (x <= 100001) {
		ADDEQ(Tree[x], xx);
		Tree[x].first %= 123456789;
		x += lowbit(x);
	}
}
pair<int, int> search(int x) {
	pair<int, int> ans = make_pair(0, 0);
	while (x) {
		ADDEQ(ans, Tree[x]);
		ans.first %= 123456789;
		x -= lowbit(x);
	}
	ans.second++;
	return ans;
}
signed main() {
//	freopen("hamon.in", "r", stdin);
//	freopen("hamon.out", "w", stdout);
	int T;
	scanf("%lld %lld", &n, &T);
	pair<int, int> ANS = make_pair(1, 1);
	for (int i = 1; i <= n; i++) {
		int A;
		scanf("%lld", &A);
		A++;
		pair<int, int> AA = make_pair(1, 1);
		ADDEQ(AA, search(A - 1));
		ADDEQ(ANS, AA);
		ANS.first %= 123456789;
		dp1[i] = AA.first % 123456789;
		dp2[i] = AA.second;
		change(A, i);
//		printf("%lld %lld %lld\n", dp1[i], dp2[i], A);
//		for (int i = 1; i <= n; i++) {
//			printf("|--%d %d\n", Tree[i].first, Tree[i].second);
//		}
	}
	if (T == 1) {
		printf("%lld\n%lld", ANS.second, ANS.first);
	}
	else {
		printf("%lld", ANS.second);
	}
	return 0;
}
/*

...#.
....#
.#...
..#..
#....

*/