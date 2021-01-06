#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
const int MAXN = 100001;
struct node {
	int l, r;
	bool operator < (const node& sec) const {
		return r > sec.r;
	}
} mineral[MAXN];
int pos[MAXN];
bool cmp(node a, node b) {
	return a.l < b.l;
}
priority_queue<node> pq;
int pow2[MAXN];
int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &mineral[i].l, &mineral[i].r);
	}
	for (int i = 1; i <= m; i++) {
		scanf("%d", &pos[i]);
	}
	sort(mineral + 1, mineral + 1 + n, cmp);
	sort(pos + 1, pos + 1 + m);
	pow2[0] = 1;
	for (int i = 1; i <= n; i++) {
		pow2[i] = (pow2[i - 1] * 2) % 998244353;
		pow2[i - 1]--;
	}
	pow2[n]--;
	int ans = 0;
	for (int i = 1, j = 1; i <= m; i++) {
		while (!pq.empty()) {
			if (pq.top().r < pos[i]) pq.pop();
			else break;
		}
		int Q = pq.size(), w;
		while (mineral[j].l <= pos[i] && j <= n) {
			if (mineral[j].r >= pos[i]) pq.push(mineral[j]);
			j++;
		}
		w = pq.size();
		ans = ans + pow2[w] - pow2[Q];
		ans %= 998244353;
//		printf("%d\n", ans);
	}
	ans = (ans % 998244353 + 998244353) % 998244353;
	printf("%d", ans);
}