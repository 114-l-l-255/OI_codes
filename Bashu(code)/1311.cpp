#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXN = 250001;
int c[MAXN];
int lowbit(int x) { return x & -x; }
void add(int x) { for (int i = x; i <= 250000; i += lowbit(i)) c[i]++; }
int ask(int x) { int ans = 0; for (int i = x; i; i -= lowbit(i)) ans += c[i]; return ans; }
int main() {
	int n;
	while (~scanf("%d", &n)) {
		if (n == 0) continue;
		int ans1 = 0, ans2 = 0;
		memset(c, 0, sizeof c);
		for (int i = 1; i < n * n; ) {
			int x;
			scanf("%d", &x);
			if (x == 0) continue;
			ans1 += ask(x);
			add(x);
			i++;
		}
		memset(c, 0, sizeof c);
		for (int i = 1; i < n * n; ) {
			int x;
			scanf("%d", &x);
			if (x == 0) continue;
			ans2 += ask(x);
			add(x);
			i++;
		}
		if (((ans1 ^ ans2) & 1) == 0) puts("TAK");
		else puts("NIE");
	}
	return 0;
}