#include <cstdio>
const int MAXN = 1001;
char str[MAXN];
int border[MAXN];
int n;
int strlen(char* s) {
	for (int i = 0; ; i++) if (s[i] == 0) return i;
}
void Getnxt() {
	border[0] = -1;
	int i = 0, j = -1;
	while (i < n) {
		if (j == -1 || str[i] == str[j]) {
			border[++i] = ++j;
		}
		else {
			j = border[j];
		}
	}
}
int main() {
	scanf("%s", str);
	n = strlen(str);
	Getnxt();
	if (n % (n - border[n]) == 0) {
		printf("%d", n - border[n]);
	}
	else {
		printf("%d\n", n);
	}
	return 0;
}
