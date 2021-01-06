#include <cstdio>
using namespace std;
struct WTMXXN {
	int x1, x2;
} f[101][4];
long long ans;
bool judge(int x1, int x2, int y1, int y2, int z1, int z2, int k) {
	return !(x1 >= f[k][1].x2 || x2 <= f[k][1].x1 || y1 >= f[k][2].x2 || y2 <= f[k][2].x1 || z1 >= f[k][3].x2 || z2 <= f[k][3].x1);
}
void dfs(int x1, int x2, int y1, int y2, int z1, int z2, int k) {
	while (k >= 0 && !judge(x1, x2, y1, y2, z1, z2, k)) --k;
	if (k < 0) {
		ans += (x2 - x1) * (y2 - y1) * (z2 - z1);
		return;
	}
	if (x1 < f[k][1].x1) {
		dfs(x1, f[k][1].x1, y1, y2, z1, z2, k - 1);
		x1 = f[k][1].x1;
	}
	if (x2 > f[k][1].x2) {
		dfs(f[k][1].x2, x2, y1, y2, z1, z2, k - 1);
		x2 = f[k][1].x2;
	}
	if (y1 < f[k][2].x1) {
		dfs(x1, x2, y1, f[k][2].x1, z1, z2, k - 1);
		y1 = f[k][2].x1;
	}
	if (y2 > f[k][2].x2) {
		dfs(x1, x2, f[k][2].x2, y2, z1, z2, k - 1);
		y2 = f[k][2].x2;
	}
	if (z1 < f[k][3].x1) {
		dfs(x1, x2, y1, y2, z1, f[k][3].x1, k - 1);
		z1 = f[k][3].x1;
	}
	if (z2 > f[k][3].x2) {
		dfs(x1, x2, y1, y2, f[k][3].x2, z2, k - 1);
		z2 = f[k][3].x2;
	}
}
int main() {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		int x, y, z, r;
		scanf("%d %d %d %d", &x, &y, &z, &r);
		f[i][1].x1 = x - r; f[i][1].x2 = x + r;
		f[i][2].x1 = y - r; f[i][2].x2 = y + r;
		f[i][3].x1 = z - r; f[i][3].x2 = z + r;
		dfs(f[i][1].x1, f[i][1].x2, f[i][2].x1, f[i][2].x2, f[i][3].x1, f[i][3].x2, i - 1);
	}
	printf("%d\n", ans);
	return 0;
}