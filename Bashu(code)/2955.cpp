#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXN = 1000005;
char s2[MAXN];
int n, m, tot;
int nxt[MAXN];
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
void Getnxt() {
	nxt[0] = -1;
	int i = 0, j = -1;
	while (i < m) {
		if (j == -1 || s2[i] == s2[j]) {
			nxt[++i] = ++j;
		}
		else j = nxt[j];
	}
}
int main() {
	int tt = 0;
	while (1) {
		tt++;
		int d;
		memset(s2, 0, sizeof s2);
		memset(nxt, 0, sizeof nxt);
		scanf("%d", &d);
		if (d == 0) break;
		scanf("%s", s2);
		m = d;
		tot = 0;
		Getnxt();
		printf("Test case #%d\n", tt);
		for (int i = 1; i <= m; i++) {
			if (nxt[i]) {
				int gc = gcd(i, nxt[i]);
				if (nxt[i] % gc == 0 && nxt[i] + gc == i) {
					printf("%d %d\n", i, i / gc);
				}
			}
		}
		puts("");
	}
	return 0;
}