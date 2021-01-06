#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int nex[5][2] = {{0, 0}, {1, 0}, {0, 1}, {-1, 0}, {0, -1}};
int n = 5, num = 0x7fffffff, ma[5][5], temp[5][5], ans[5][5];
void reverse(int x, int y) {
	for (int i = 0; i < 5; i++) {
		int tx = x + nex[i][0], ty = y + nex[i][1];
		if (tx < 0 || tx >= n || ty < 0 || ty >= n) continue;
		temp[tx][ty] ^= 1;
	}
}
int pd() {
	int t = 0;
	memcpy(temp, ma, sizeof(ma));
	for (int i = 0; i < n; i++)
		if (ans[0][i]) {
			reverse(0, i);
			t++;
		}
	for (int i = 1; i < n; i++)
		for (int j = 0; j < n; j++) {
			ans[i][j] = (temp[i - 1][j] == 0);
			if (ans[i][j]) {
				reverse(i, j);
				t++;
			}
		}
	for (int i = 0; i < n; i++)
		if (temp[n - 1][i] == 0)
			return 0x7fffffff;
	return t;
}
void dfs(int s) {
	if (s >= n) {
		num = min(num, pd());
		return;
	}
	for (ans[0][s] = 0; ans[0][s] < 2; ans[0][s]++)
		dfs(s + 1);
}
int main() {
	int kkk;
	scanf("%d", &kkk);
	while (kkk--) {
		num = 0x7fffffff;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				scanf("%1d", &ma[i][j]);
		dfs(0);
		printf("%d\n", num > 6 ? -1 : num);
	}
	return 0;
}