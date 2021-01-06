#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 1001;
int Up[MAXN][MAXN], Down[MAXN][MAXN];
int a[MAXN][MAXN];
int maxx[MAXN][2];
int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= i; j++) {
			scanf("%d", &a[i][j]);
			Up[i][j] = Down[i][j] = a[i][j];
			if (j != 1) Down[i][j] = max(Down[i][j], Down[i - 1][j - 1] + a[i][j]);
			if (j != i) Down[i][j] = max(Down[i][j], Down[i - 1][j] + a[i][j]);
		}
	}
	for (int i = n - 1; i; i--) {
		for (int j = 1; j <= i; j++) {
			Up[i][j] = max(max(Up[i][j], Up[i + 1][j] + a[i][j]), Up[i + 1][j + 1] + a[i][j]);
		}
	}
	for (int i = 1; i <= n; i++) {
		maxx[i][0] = maxx[i][1] = -1;
		for (int j = 1; j <= i; j++) {
			int volvo = Up[i][j] + Down[i][j] - a[i][j];
			if (volvo >= maxx[i][0]) {
				maxx[i][1] = maxx[i][0];
				maxx[i][0] = volvo;
			}
			else if (volvo > maxx[i][1]) {
				maxx[i][1] = volvo;
			}
		}
	}
	for (int i = 1; i <= m; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		int volvo = Up[x][y] + Down[x][y] - a[x][y];
		if (volvo == maxx[x][0]) printf("%d\n", maxx[x][1]);
		else printf("%d\n", maxx[x][0]);
	}
	return 0;
}