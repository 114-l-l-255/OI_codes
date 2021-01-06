#include <cstdio>
#include <stack>
#define N 1005
#define inf 0x7fffffff
using namespace std;
struct Node {
	int val, pos;
};
int n, m, ans = -inf;
int h[N], l[N], r[N];
int a[N][N];
int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			char c[3];
			scanf("%s", c);
			if (c[0] == 'R') a[i][j] = 1;
			else a[i][j] = 2;
		}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++)
			if (a[i][j] == 1) h[j] = 0;
			else h[j]++;
		stack<Node> stk1, stk2;
		stk1.push((Node) {
			-inf, 0
		});
		for (int j = 1; j <= m; j++) {
			while (stk1.top().val >= h[j]) stk1.pop();
			l[j] = stk1.top().pos + 1;
			stk1.push((Node) {
				h[j], j
			});
		}
		stk2.push((Node) {
			-inf, m + 1
		});
		for (int j = m; j >= 1; j--) {
			while(stk2.top().val >= h[j]) stk2.pop();
			r[j] = stk2.top().pos - 1;
			stk2.push((Node) {
				h[j], j
			});
		}
		for (int j = 1; j <= m; j++) {
			int tmp = h[j] * (r[j] - l[j] + 1);
			ans = max(ans, tmp);
		}
	}
	printf("%d", 3 * ans);
	return 0;
}