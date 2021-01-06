#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
struct node {
	int x, y;
};
node ms[100005], level[100005];
int cmp(node a, node b) {
	if (a.x != b.x)
		return a.x > b.x;
	return a.y > b.y;
}
int main() {
	int n, m, i, j, cnt;
	long long sum;
	while (~scanf("%d %d", &n, &m)) {
		for (i = 0; i < n; i++)
			scanf("%d %d", &ms[i].x, &ms[i].y);
		for (j = 0; j < m; j++)
			scanf("%d %d", &level[j].x, &level[j].y);
		sort(ms, ms + n, cmp);
		sort(level, level + m, cmp);
		cnt = sum = 0;
		int s[105] = {0};
		for (i = 0, j = 0; i < m; i++) {
			while (j < n && ms[j].x >= level[i].x) {
				s[ms[j].y]++;
				j++;
			}
			for (int k = level[i].y; k <= 100; k++) {
				if (s[k]) {
					s[k]--;
					sum += 500 * level[i].x + 2 * level[i].y;
					cnt++;
					break;
				}
			}
		}
		printf("%d %lld\n", cnt, sum);
	}
	return 0;
}