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
	while (1) {
		memset(s2, 0, sizeof s2);
		memset(nxt, 0, sizeof nxt);
		scanf("%s", s2);
		if (s2[0] == '.') break;
		m = strlen(s2);
		tot = 0;
		Getnxt();
		if (nxt[m] == 0) puts("1");
		else {
			int gc = gcd(m, nxt[m]);
			if (nxt[m] % gc == 0 && nxt[m] + gc == m) {
				printf("%d\n", m / gc);
			}
			else puts("1");
		}
	}
	return 0;
}