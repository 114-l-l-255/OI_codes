#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
const int MAXN = 1000001;
int q1[MAXN], q2[MAXN];
int a[MAXN];
int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	int l = 0, r = -1;
	for (int i = 0; i < m; i++) {
		scanf("%d", &a[i]);
		while (l <= r && a[q1[r]] > a[i]) r--;
		q1[++r] = i;
	}
	for (int i = m; i < n; i++) {
		scanf("%d", &a[i]);
		printf("%d ", a[q1[l]]);
		while (l <= r && q1[l] < i - m + 1) l++;
		while (l <= r && a[q1[r]] > a[i]) r--;
		q1[++r] = i;
	}
	printf("%d\n", a[q1[l]]);
	l = 0, r = -1;
	for (int i = 0; i < m; i++) {
		while (l <= r && a[q1[r]] < a[i]) r--;
		q1[++r] = i;
	}
	for (int i = m; i < n; i++) {
		printf("%d ", a[q1[l]]);
		while (l <= r && q1[l] < i - m + 1) l++;
		while (l <= r && a[q1[r]] < a[i]) r--;
		q1[++r] = i;
	}
	printf("%d ", a[q1[l]]);
}