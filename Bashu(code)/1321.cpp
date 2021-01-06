#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
struct Node {
	double s, e;
};
int n, d, k;
Node area[1010];
int cmp(Node a, Node b) {
	return a.e < b.e;
}
int change(int x, int y) {
	if (y > d) return 0;
	double m = sqrt(d * d - y * y);
	area[k].s = x - m;
	area[k].e = x + m;
	k++;
	return 1;
}
int main() {
	int x, y, flg, temp, num;
	while (scanf("%d %d", &n, &d), n || d) {
		k = 0;
		flg = 1;
		temp = 0;
		num = 1;
		for (int i = 0; i < n; i++) {
			scanf("%d %d", &x, &y);
			int tmp = change(x, y);
			if (!tmp) flg = 0;
		}
		if (!flg) {
			printf("%d\n", -1);
			continue;
		}
		sort(area, area + k, cmp);
		for (int i = 0; i < k; i++) {
			if (area[i].s > area[temp].e) temp = i, num++;
		}
		printf("%d\n", num);
	}
	return 0;
}