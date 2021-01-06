#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
long double pi = 3.14159265358979323846264338327950;
using namespace std;
struct Matrix {
	double a[3][3];
	Matrix() {
		memset(a, 0, sizeof(a));
		a[0][0] = 1;
		a[1][1] = 1;
		a[2][2] = 1;
	}
} Mat, c[400001], st;
double x[100001], y[100001];
char s[10001];
int n, m;
Matrix operator * (const Matrix &x, const Matrix &y) {
	Matrix res;
	int i, j, k;
	memset(res.a, 0, sizeof(res.a));
	for (j = 0; j <= 2; j++) {
		for (k = 0; k <= 2; k++)
			if (y.a[k][j]) {
				for (i = 0; i <= 2; i++) {
					res.a[i][j] += x.a[i][k] * y.a[k][j];
				}
			}
	}
	return res;
}
void pushdown(int rt) {
	c[rt << 1] = c[rt << 1] * c[rt];
	c[rt << 1 | 1] = c[rt << 1 | 1] * c[rt];
	c[rt] = st;
}
void update(int rt, int l, int r, int L, int R) {
	if (l >= L && r <= R) {
		c[rt] = c[rt] * Mat;
		return;
	}
	pushdown(rt);
	int mid = (l + r) >> 1;
	if (L <= mid) update(rt << 1, l, mid, L, R);
	if (R > mid) update(rt << 1 | 1, mid + 1, r, L, R);
}
void dfs(int rt, int l, int r) {
	if (l == r) {
		printf("%.2lf %.2lf\n", x[l] * c[rt].a[0][0] + y[l] * c[rt].a[1][0] + c[rt].a[2][0], y[l] * c[rt].a[1][1] + x[l] * c[rt].a[0][1] + c[rt].a[2][1]);
		return;
	}
	pushdown(rt);
	int mid = (l + r) >> 1;
	dfs(rt << 1, l, mid);
	dfs(rt << 1 | 1, mid + 1, r);
}
int main() {
	int i, j, l, r;
	double p, q, a;
	scanf("%d", &n);
	for (i = 1; i <= n; i++) {
		scanf("%lf %lf", &x[i], &y[i]);
	}
	scanf("%d", &m);
	for (i = 1; i <= m; i++) {
		scanf("%s", s);
		scanf("%d %d", &l, &r);
		if (s[0] == 'M') {
			scanf("%lf %lf", &p, &q);
			memset(Mat.a, 0, sizeof(Mat.a));
			Mat.a[0][0] = 1;
			Mat.a[2][0] = p;
			Mat.a[1][1] = 1;
			Mat.a[2][1] = q;
			Mat.a[2][2] = 1;
			update(1, 1, n, l, r);
		}
		if (s[0] == 'X') {
			memset(Mat.a, 0, sizeof(Mat.a));
			Mat.a[1][1] = -1;
			Mat.a[0][0] = 1;
			Mat.a[2][2] = 1;
			update(1, 1, n, l, r);
		}
		if (s[0] == 'Y') {
			memset(Mat.a, 0, sizeof(Mat.a));
			Mat.a[1][1] = 1;
			Mat.a[0][0] = -1;
			Mat.a[2][2] = 1;
			update(1, 1, n, l, r);
		}
		if (s[0]=='O') {
			memset(Mat.a, 0, sizeof(Mat.a));
			Mat.a[1][0] = 1;
			Mat.a[0][1] = 1;
			Mat.a[2][2] = 1;
			update(1, 1, n, l, r);
		}
		if (s[0] == 'R') {
			memset(Mat.a, 0, sizeof(Mat.a));
			scanf("%lf", &a);
			Mat.a[0][0] = Mat.a[1][1] = cos(a * pi / 180);
			Mat.a[0][1] = sin(a * pi / 180);
			Mat.a[1][0] = -sin(a * pi / 180);
			Mat.a[2][2] = 1;
			update(1, 1, n, l, r);
		}
	}
	dfs(1, 1, n);
	return 0;
}