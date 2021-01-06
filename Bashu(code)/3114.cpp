#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 10000001;
bool use[MAXN];
int a[MAXN];
int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++) {
		scanf("%d", &a[i]);
		use[a[i]] = 1;
	}
	int jj = 1;
	for (int i = 0, j = 1; i < m; i++) {
		while (j < a[i]) {
			if (!use[j]) {
				printf("%d\n", j);
			}
			j++;
		}
		printf("%d\n", a[i]);
		jj = j;
	}
	for (int i = jj + 1; i <= n; i++) {
		printf("%d\n", i);
	}
	return 0;
}