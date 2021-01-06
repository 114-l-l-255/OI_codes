#include <cstdio>
char str[10001][76];
int n, m;
int nxt1[76], nxt2[10001];
void Getnxt1() {
	nxt1[0] = -1;
	int i = 0, j = -1;
	while (i < m) {
		bool flg = 1;
		for (int k = 0; k < n; k++) {
			if (str[k][i] != str[k][j]) {
				flg = 0;
				break;
			}
		}
		if (j == -1 || flg) {
			nxt1[++i] = ++j;
		}
		else j = nxt1[j];
	}
}
void Getnxt2() {
	nxt2[0] = -1;
	int i = 0, j = -1;
	while (i < n) {
		bool flg = 1;
		for (int k = 0; k < m; k++) {
			if (str[i][k] != str[j][k]) {
				flg = 0;
				break;
			}
		}
		if (j == -1 || flg) {
			nxt2[++i] = ++j;
		}
		else j = nxt2[j];
	}
}
int main() {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%s", str[i]);
	}
	Getnxt1();
	Getnxt2();
	printf("%d", (m - nxt1[m]) * (n - nxt2[n]));
	return 0;
}