#include <cstdio>
int son[1000002][10], flg[1000002], cnt;
char re[100001][102];
int strlen(char* str) {
	for (int i = 0; ; i++) if (str[i] == 0) return i;
}
void memset(char* str) {
	for (int i = 0; i < 102; i++) str[i] = 0;
}
void cls() {
	for (int i = 0; i <= 1000001; i++) {
		for (int j = 0; j < 10; j++) {
			son[i][j] = 0;
		}
		flg[i] = 0;
	}
}
void insert(char* str) {
	int n = strlen(str), root = 1;
	for (int i = 0; i < n; i++) {
		if (son[root][str[i] - '0'] == 0) son[root][str[i] - '0'] = ++cnt;
		root = son[root][str[i] - '0'];
	}
	flg[root]++;
}
int find(char* str) {
	int n = strlen(str), root = 1, ans = 0;
	for (int i = 0; i < n; i++) {
		ans += flg[root];
		if (son[root][str[i] - '0'] == 0) return ans;
		root = son[root][str[i] - '0'];
	}
	return ans + flg[root];
}
int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		cls();
		cnt = 1;
		int n, m;
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			memset(re[i]);
			scanf("%s", re[i]);
			insert(re[i]);
		}
		for (int i = 0; i < n; i++) {
			if (find(re[i]) > 1) {
				puts("NO");
				goto enn;
			}
		}
		puts("YES");
		enn:;
	}
	return 0;
}