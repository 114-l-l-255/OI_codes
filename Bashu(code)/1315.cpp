#include <cstdio>
#include <cstring>
using namespace std;
const int MAXN = 352;
int catalan[2][MAXN][301];
void add(int* ans, int* a, int* b) {
	memset(ans, 0, sizeof(int) * 301);
	for (int i = 0; i < 300; i++) {
		ans[i] += a[i] + b[i];
		if (ans[i] >= 10) ans[i + 1]++, ans[i] -= 10;
	}
}
int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	bool flg = 0;
	catalan[0][0][0] = 1;
	for (int i = 0; i < n - m + 1; i++) {
		int bini = i & 1;
		for (int j = 0; j < i + m; j++) {
			if (i == 0 && j == 0) continue;
			else if (j == 0) add(catalan[bini][j], catalan[1 - bini][j], catalan[0][351]);
			else add(catalan[bini][j], catalan[1 - bini][j], catalan[bini][j - 1]);
			flg = 0;
			// for (int ij = 300; ~ij; ij--) {
			// 	if (catalan[bini][j][ij]) flg = 1;
			// 	if (flg) printf("%d", catalan[bini][j][ij]);
			// }
			// printf("\n");
		}
	}
	flg = 0;
	for (int i = 300; ~i; i--) {
		if (catalan[(n - m) & 1][n - 2][i]) flg = 1;
		if (flg) printf("%d", catalan[(n - m) & 1][n - 2][i]);
	}
	return 0;
}