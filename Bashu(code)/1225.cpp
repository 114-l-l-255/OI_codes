#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXN = 100001;
int Tree[MAXN + 100], ans[MAXN];
pair<int, pair<int, int> > Stars[MAXN];
int lowbit(int a) {
	return a & -a;
}
void change(int a) {
	while (a <= 100000) {
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
	int n;
	while (~scanf("%d", &n) && n) {
		memset(Tree, 0, sizeof Tree);
		for (int i = 0; i < n; i++) {
			scanf("%d %d", &Stars[i].first, &Stars[i].second.first);
			Stars[i].second.second = i;
			Stars[i].second.first = -Stars[i].second.first;
		}
		sort(Stars, Stars + n);
		int aa = -1, bb = -1, cc = 0;
		for (int i = 0; i < n; i++) {
			ans[Stars[i].second.second] = i - search(-Stars[i].second.first);
			if (aa == Stars[i].first && bb == -Stars[i].second.first) cc++, ans[Stars[i].second.second] -= cc;
			else aa = Stars[i].first, bb = -Stars[i].second.first, cc = 0;
			change(-Stars[i].second.first + 1);
		} 
		for (int i = 0; i < n; i++) {
			printf("%d ", ans[i]);
		}
		printf("\n");
	}
	return 0;
}