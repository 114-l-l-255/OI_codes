#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 100001;
int Tree[MAXN + 100], ans[MAXN];
int n;
pair<int, int> Stars[MAXN];
int lowbit(int a) {
	return a & -a;
}
void change(int a) {
	while (a <= n) {
		Tree[a]++;
		a += lowbit(a);
	}
}
int search(int a) {
	int ans = 0;
	while (a) {
		ans += Tree[a];
		a -= lowbit(a);
	}
	return ans;
}
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &Stars[i].first, &Stars[i].second);
	}
	sort(Stars, Stars + n);
	for (int i = 0; i < n; i++) {
		ans[search(Stars[i].second + 1)]++;
		change(Stars[i].second + 1);
	}
	for (int i = 0; i < n; i++) {
		printf("%d\n", ans[i]);
	}
	return 0;
}