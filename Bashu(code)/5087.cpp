#include <cstdio>
#include <algorithm>
//#define a -(y * 1.0 / x)
//#define b y
//y = a * x + b
using namespace std;
const int MAXN = 100001;
struct L {
	int x, y;
} l[MAXN]; int X[MAXN], Y[MAXN];
bool check(int x, int y, int id) {
	if (x < 0 || y < 0) return 0;
	double y2 = -(l[id].y * 1.0 / l[id].x) * x + l[id].y;
	if (y2 > y) return 0;
	else return 1;
}
int BinSer(int x, int y, int n) {
	if (check(x, y, n) == 1) return n;
	if (check(x, y, 1) == 0) return 0;
	int l = 1, r = n;
	while (l + 1 < r) {
		int mid = l + r >> 1;
		if (check(x, y, mid) == 0) r = mid;
		else l = mid;
	}
	return l;
}
int main() {
//	freopen("geometry.in", "r", stdin);
//	freopen("geometry.out", "w", stdout);
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &X[i]);
	}
	for (int i = 1; i <= n; i++) {
		scanf("%d", &Y[i]);
	}
	sort(X + 1, X + n + 1);
	sort(Y + 1, Y + n + 1);
	for (int i = 1; i <= n; i++) {
		l[i].x = X[i];
		l[i].y = Y[i];
	}
	int m;
	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		int XX, YY;
		scanf("%d %d", &XX, &YY);
		printf("%d\n", BinSer(XX, YY, n));
	}
	return 0;
}