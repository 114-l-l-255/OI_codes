#include <cstdio>
const int MAXL = 1000001;
int son[MAXL + 1][26], flg[MAXL], cnt;
char re[MAXL + 1];
int strlen(char* str) {
	for (int i = 0; ; i++) if (str[i] == 0) return i;
}
void memset(char* str) {
	for (int i = 0; i < sizeof(str) / sizeof(char); i++) str[i] = 0;
}
void insert(char* str) {
	int n = strlen(str), root = 1;
	for (int i = 0; i < n; i++) {
		if (son[root][str[i] - 'a'] == 0) son[root][str[i] - 'a'] = ++cnt;
		root = son[root][str[i] - 'a'];
	}
	flg[root]++;
}
int find(char* str) {
	int n = strlen(str), root = 1, ans = 0;
	for (int i = 0; i < n; i++) {
		ans += flg[root];
		if (son[root][str[i] - 'a'] == 0) return ans;
		root = son[root][str[i] - 'a'];
	}
	return ans + flg[root];
}
int main() {
	cnt = 1;
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		memset(re);
		scanf("%s", re);
		insert(re);
	}
	for (int i = 0; i < m; i++) {
		memset(re);
		scanf("%s", re);
		printf("%d\n", find(re));
	}
	return 0;
}