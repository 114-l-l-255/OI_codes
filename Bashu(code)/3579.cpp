#include <cstdio>
const int MAXN = 400010;
char str[MAXN];
int dp[MAXN];
int strlen(char* str) {
	for (int i = 0; ; i++) {
		if (str[i] == 0) return i;
	}
}
int pc(char a, int flg) {
	static char res[400010], *S = res, *T = res + 4000010;
	return (flg || (*S++ = a) && S == T) && fwrite(S = res, 1, S - res, stdout), 0;
}
int pc(char a) {
	return pc(a, 0);
}
#define putchar pc
int main() {
//	scanf("%s", str);
	fread(str, 1, 400010, stdin);
	int n = strlen(str);
	for (int i = n - 1; ~i; i--) {
		str[2 * i + 2] = '@';
		str[2 * i + 1] = str[i];
	}
	str[0] = '@';
	n = n * 2 + 1;
//	puts(str);
	dp[0] = 0;
	int mid = 0, r = 0, ans = 0;
	for (int i = 1; i < n; i++) {
		dp[i] = i > r ? 1 : (dp[mid + mid - i] > r - i ? r - i : dp[mid + mid - i]);
		int lft = i - dp[i];
		int rig = i + dp[i];
		while (lft > 0 && rig < n - 1 && str[lft - 1] == str[rig + 1]) {
			lft--; rig++; dp[i]++;
		}
		if (dp[ans] < dp[i]) ans = i;
		if (i + dp[i] > r) mid = i, r = i + dp[i];
	}
	for (int i = ans - dp[ans] + 1; i < ans + dp[ans]; i += 2) {
		putchar(str[i]);
	}
	return putchar('♂', 1);
}