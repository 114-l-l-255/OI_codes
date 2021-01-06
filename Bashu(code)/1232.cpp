#include <cstdio>
#include <algorithm>
#include <cstring>
#define LL long long
#define inf 0x3f3f3f3f
using namespace std;
int n, m, k;
struct de {
	int x, y;
	bool operator < (const de &other)const {
		if (x == other.x)
			return y < other.y;
		return x < other.x;
	}
};
de qiao[500 * 1010];
LL run[10100];
int lowbit(int i) {
	return i & (-i);
}
void update(int i) {
	while (i <= m) {
		run[i]++;
		i += lowbit(i);
	}
}
LL sum(int i) {
	LL s = 0;
	while (i > 0) {
		s += run[i];
		i -= lowbit(i);
	}
	return s;
}
int main() {
	int t;
	scanf("%d", &t);
	for (int p = 1; p <= t; p++) {
		scanf("%d %d %d", &n, &m, &k);
		memset(qiao ,0, sizeof(qiao));
		memset(run, 0, sizeof(run));
		for (int i = 1; i <= k; i++)
			scanf("%d %d", &qiao[i].x, &qiao[i].y);
		sort(qiao + 1, qiao + 1 + k);
		LL ans = 0;
		for (int i = 1; i <= k; i++) {
			ans += sum(m) - sum(qiao[i].y);
			update(qiao[i].y);
		}
		printf("Test case %d: %lld\n", p, ans);
	}
	return 0;
}