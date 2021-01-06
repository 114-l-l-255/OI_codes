#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 1001;
int T, N, Q, Ans;
bool A[MAXN << 2][MAXN << 2];
void Modify_y(int ox, int oy, int l, int r, int x, int y) {
	if (x <= l && r <= y) {
		A[ox][oy] ^= 1;
		return;
	}
	int mid = (l + r) >> 1;
	if (x <= mid) Modify_y(ox, oy << 1, l, mid, x, y);
	if (y > mid) Modify_y(ox, (oy << 1) | 1, mid + 1, r, x, y);
}
void Modify_x(int ox, int l, int r, int x1, int x2, int y1, int y2) {
	if (x1 <= l && r <= x2) {
		Modify_y(ox, 1, 1, N, y1, y2);
		return;
	}
	int mid = (l + r) >> 1;
	if (x1 <= mid) Modify_x(ox << 1, l, mid, x1, x2, y1, y2);
	if (x2 > mid) Modify_x((ox << 1) | 1, mid + 1, r, x1, x2, y1, y2);
}
void Query_y(int ox, int oy, int l, int r, int y) {
	Ans ^= A[ox][oy];
	if (l == r) return;
	int mid = (l + r) >> 1;
	if (y <= mid) Query_y(ox, oy << 1, l, mid, y);
	if (y > mid) Query_y(ox, (oy << 1) | 1, mid + 1, r, y);
}
void Query_x (int ox, int l, int r, int x, int y) {
	Query_y(ox, 1, 1, N, y);
	if (l == r) return;
	int mid = (l + r) >> 1;
	if (x <= mid) Query_x(ox << 1, l, mid, x, y);
	if (x > mid) Query_x((ox << 1) | 1, mid + 1, r, x, y);
}
int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &N, &Q);
		for (int i = 1; i <= N << 2; i++) {
			for (int j = 1; j <= N << 2; j++) {
				A[i][j] = 0;
			}
		}
		while (Q--) {
			char ch;
			do {
				ch = getchar();	
			} while (ch < 'A' || ch > 'Z');
			if (ch == 'C') {
				int x1, y1, x2, y2;
				scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
				Modify_x(1, 1, N, x1, x2, y1, y2);
			} else {
				int x, y;
				scanf("%d %d", &x, &y);
				Ans = 0;
				Query_x(1, 1, N, x, y);
				printf("%d\n", Ans);
			}
		}
		if (T) printf("\n");
	}
	return 0;
}