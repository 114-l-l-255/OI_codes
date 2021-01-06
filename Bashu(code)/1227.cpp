#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 100003;
int CF[MAXN];
int main() {
	int n;
	while (~scanf("%d", &n) && n) {
		for (int i = 0; i <= n + 1; i++) {
			CF[i] = 0;
		}
		for (int i = 0; i < n; i++) {
			int a, b;
			scanf("%d %d", &a, &b);
			CF[a]++;
			CF[b + 1]--;
		}
		int ans = 0;
		for (int i = 1; i <= n; i++) {
			ans += CF[i];
			printf("%d ", ans);
		}
		printf("\n");
	}
	return 0;
}