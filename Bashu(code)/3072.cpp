#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 1001;
int row[MAXN], rowtime[MAXN];
int col[MAXN], coltime[MAXN];
int main() {
	int n, m, q;
	scanf("%d %d %d", &n, &m, &q);
	for (int i = 1; i <= q; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		if (a == 1) {
			row[b] = c;
			rowtime[b] = i;
		}
		if (a == 2) {
			col[b] = c;
			coltime[b] = i;
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			printf("%d ", rowtime[i] > coltime[j] ? row[i] : col[j]);
		}
		printf("\n");
	}
	return 0;
}