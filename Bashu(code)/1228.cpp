#include <cstdio>
#include <algorithm>
using namespace std;
int Tree[105][105][105], n;
int lowbit(int a) {
	return a & -a;
}
void change(int x, int y, int z) {
	int yy, zz;
	while (x <= n + 1) {
		yy = y;
		while (yy <= n + 1) {
			zz = z;
			while (zz <= n + 1) {
				Tree[x][yy][zz] ^= 1;
				zz += lowbit(zz);
			}
			yy += lowbit(yy);
		}
		x += lowbit(x);
	}
} 
void change(int x1, int x2, int y1, int y2, int z1, int z2) {
	change(x1, y1, z1);
//	printf("%d %d %d\n", x1, y1, z1);
	change(x1, y1, z2 + 1);
//	printf("%d %d %d\n", x1, y1, z2 + 1);
	change(x1, y2 + 1, z1);
//	printf("%d %d %d\n", x1, y2 + 1, z1);
	change(x1, y2 + 1, z2 + 1);
//	printf("%d %d %d\n", x1, y2 + 1, z2 + 1);
	change(x2 + 1, y1, z1);
//	printf("%d %d %d\n", x2 + 1, y1, z1);
	change(x2 + 1, y1, z2 + 1);
//	printf("%d %d %d\n", x2 + 1, y1, z2 + 1);
	change(x2 + 1, y2 + 1, z1);
//	printf("%d %d %d\n", x2 + 1, y2 + 1, z1);
	change(x2 + 1, y2 + 1, z2 + 1);
//	printf("%d %d %d\n", x2 + 1, y2 + 1, z2 + 1);
}
int search(int x, int y, int z) {
	int yy, zz;
	int ans = 0;
	while (x) {
		yy = y;
		while (yy) {
			zz = z;
			while (zz) {
				ans ^= Tree[x][yy][zz];
				zz -= lowbit(zz);
			}
			yy -= lowbit(yy);
		}
		x -= lowbit(x);
	}
	return ans;
}
int main() {
	int m;
	while (~scanf("%d %d", &n, &m)) {
		for (int i = 1; i <= n + 1; i++) {
			for (int j = 1; j <= n + 1; j++) {
				for (int k = 1; k <= n + 1; k++) {
					Tree[i][j][k] = 0;
				}
			}
		}
		for (int i = 0; i < m; i++) {
			int X, x1, x2, y1, y2, z1, z2;
			scanf("%d", &X);
			if (X == 1) {
				scanf("%d %d %d %d %d %d", &x1, &y1, &z1, &x2, &y2, &z2);
				x1++, y1++, z1++, x2++, y2++, z2++;
				change(x1, x2, y1, y2, z1, z2);
			}
			else {
				scanf("%d %d %d", &x1, &y1, &z1);
				x1++, y1++, z1++;
				printf("%d\n", search(x1, y1, z1));
			}
	//		for (int i = 1; i <= 5; i++) {
	//			for (int j = 1; j <= 5; j++) {
	//				for (int k = 1; k <= 5; k++) {
	//					printf("%d ", Tree[i][j][k]);
	//				}
	//				printf("\n");
	//			}
	//			printf("\n");
	//		}
		}
	}
	return 0;
}