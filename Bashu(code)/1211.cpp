#include <cstdio>
using namespace std;
const int MAXN = 1025;
int val[MAXN << 2][MAXN << 2];
int Ans, S;
void ChangeY(int ox, int oy, int l, int r, int y, int a) {
	val[ox][oy] += a;
	if (l != r) {
		int mid = l + r >> 1;
		if (y <= mid) ChangeY(ox, oy << 1, l, mid, y, a);
		if (y > mid) ChangeY(ox, (oy << 1) | 1, mid + 1, r, y, a);
		val[ox][oy] = val[ox][oy << 1] + val[ox][(oy << 1) | 1];
	}
}
void ChangeX(int ox, int l, int r, int x, int y, int a) {
	ChangeY(ox, 1, 1, S, y, a);
	if (l != r) {
		int mid = l + r >> 1;
		if (x <= mid) ChangeX(ox << 1, l, mid, x, y, a);
		if (x > mid) ChangeX((ox << 1) | 1, mid + 1, r, x, y, a);
		val[ox][1] = val[ox << 1][1] + val[(ox << 1) | 1][1];
	}
}
void SearchY(int ox, int oy, int l, int r, int y1, int y2) {
	if (l >= y1 && r <= y2) {
		Ans += val[ox][oy];
	}
	else {
		int mid = l + r >> 1;
		if (y1 <= mid) SearchY(ox, oy << 1, l, mid, y1, y2);
		if (y2 > mid) SearchY(ox, (oy << 1) | 1, mid + 1, r, y1, y2);
	}
}
void SearchX(int ox, int l, int r, int x1, int x2, int y1, int y2) {
	if (l >= x1 && r <= x2) {
		SearchY(ox, 1, 1, S, y1, y2);
	}
	else {
		int mid = l + r >> 1;
		if (x1 <= mid) SearchX(ox << 1, l, mid, x1, x2, y1, y2);
		if (x2 > mid) SearchX((ox << 1) | 1, mid + 1, r, x1, x2, y1, y2);
	}
}
int main() {
	scanf("%*d %d", &S);
	while (1) {
		int T;
		scanf("%d", &T);
		if (T == 1) {
			int x, y, a;
			scanf("%d %d %d", &x, &y, &a);
			x++, y++;
			ChangeX(1, 1, S, x, y, a);
		}
		if (T == 2) {
			int x1, y1, x2, y2;
			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
			x1++, y1++, x2++, y2++;
			Ans = 0;
			SearchX(1, 1, S, x1, x2, y1, y2);
			printf("%d\n", Ans);
		}
		if (T == 3) break;
		// for (int i = 1; i < 9; i++) {
		// 	for (int j = 1; j < 9; j++) {
		// 		printf("%d ", val[i][j]);
		// 	}
		// 	printf("\n");
		// }
	}
	return 0;
}