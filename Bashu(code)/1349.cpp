#include <stdio.h>
#include <string.h>
const int MAXN = 1000002;
int t[MAXN], A[MAXN];
char str1[MAXN], str2[MAXN];
int ctoi(char ch) {
	if (ch >= '0' && ch <= '9') return ch - '0';
	else if (ch >= 'A' && ch <= 'Z') return ch - 'A' + 10;
	else return ch - 'a' + 36;
}
char itoc(int ch) {
	if (ch >= 0 && ch <= 9) return ch + '0';
	else if (ch >= 10 && ch <= 35) return ch + 'A' - 10;
	else return ch + 'a' - 36;
}
int main() {
	int n, m;
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d %s", &n, &m, str1);
		int len = strlen(str1);
		for (int i = len; i >= 0; --i) t[len - 1 - i] = ctoi(str1[i]);
		int newlen;
		for (newlen = 0; len; ) {
			for (int i = len; i; --i) {
				t[i-1] += t[i] % m * n;
				t[i] /= m;
			}
			A[newlen++] = t[0] % m;
			t[0] /= m;
			while (len && !t[len - 1])  len--;
		}
		str2[newlen] = '\0';
		for (int i = 0; i < newlen; i++)
			str2[newlen - 1 - i] = itoc(A[i]);
		printf("%d %s\n%d %s\n\n", n, str1, m, str2);
	}
	return 0;
}