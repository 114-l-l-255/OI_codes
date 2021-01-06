#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;
const int MAXN = 25001;
const int MAXL = 17;
struct node {
	int son[26], x;
} nd[MAXN * MAXL];
int tot;
void add(char* str, int addt) {
	int np = strlen(str);
	int rt = 1;
	for (int i = 0; i < np; i++) {
		if (nd[rt].son[str[i] - 'a'] == 0) nd[rt].son[str[i] - 'a'] = ++tot, nd[tot].x = 0;
		rt = nd[rt].son[str[i] - 'a'];
//		printf("goto %d 1\n", rt);
	}
	nd[rt].x = addt;
//	printf("add %d\n", rt);
}
int ask(char* str) {
	int np = strlen(str);
	int rt = 1;
	for (int i = 0; i < np; i++) {
		if (nd[rt].son[str[i] - 'a'] == 0) return 0;
		rt = nd[rt].son[str[i] - 'a'];
//		printf("goto %d 2\n", rt);
	}
//	printf("at %d\n", rt);
	return nd[rt].x;
}
int ask_del(char* str, int del) {
	int np = strlen(str);
	int rt = 1;
	for (int i = 0; i < np; i++) {
		if (i == del) continue;
		if (nd[rt].son[str[i] - 'a'] == 0) return 0;
		rt = nd[rt].son[str[i] - 'a'];
	}
	return nd[rt].x;
}
int ask_add(char* str, int add, char newx) {
	int np = strlen(str);
	int rt = 1;
	for (int i = 0; i < np; i++) {
		if (i == add) {
			if (nd[rt].son[newx - 'a'] == 0) return 0;
			rt = nd[rt].son[newx - 'a'];
		}
		if (nd[rt].son[str[i] - 'a'] == 0) return 0;
		rt = nd[rt].son[str[i] - 'a'];
	}
	if (np == add) {
		if (nd[rt].son[newx - 'a'] == 0) return 0;
		rt = nd[rt].son[newx - 'a'];
	}
	return nd[rt].x;
}
int ask_chg(char* str, int chg, char newx) {
	int np = strlen(str);
	int rt = 1;
	for (int i = 0; i < np; i++) {
		if (i == chg) {
			if (nd[rt].son[newx - 'a'] == 0) return 0;
			rt = nd[rt].son[newx - 'a'];
		}
		else {
			if (nd[rt].son[str[i] - 'a'] == 0) return 0;
			rt = nd[rt].son[str[i] - 'a'];
		}
	}
	return nd[rt].x;
}
char str[MAXN][MAXL];
string strpre[MAXN];
bool cmp(char a[MAXL], char b[MAXL]) {
	return strcmp(a, b);
}
int dp[MAXN];
int main() {
	tot = 1;
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		cin >> strpre[i];
//		add(str[i]);
	}
	sort(&strpre[1], &strpre[n + 1]);
	int rrrt = 0;
	for (int lll = 1; lll <= n; lll++) {
		for (int i = 0; i < strpre[lll].size(); i++) {
			str[lll][i] = strpre[lll][i];
		}
		str[lll][strpre[lll].size()] = '\0';
		add(str[lll], lll);
		int np = strlen(str[lll]);
		int k;
		dp[lll] = 1;
		for (int i = 0; i < np; i++) {
			if (i != 0 && str[lll][i] == str[lll][i - 1]) continue;
			k = ask_del(str[lll], i);
			if (k) dp[lll] = max(dp[lll], dp[k] + 1);
//				printf("del %d %d\n", i, ans);
		}
		for (int i = 0; i <= np; i++) {
			for (int j = 0; j < 26; j++) {
				if (i != 0 && str[lll][i - 1] == j + 'a') continue;
				k = ask_add(str[lll], i, j + 'a');
				if (k) dp[lll] = max(dp[lll], dp[k] + 1);
//					printf("add %d %d %d\n", i, j, ans);
			}
		}
		for (int i = 0; i < np; i++) {
			for (int j = 0; j < 26; j++) {
				if (j + 'a' == str[lll][i]) continue;
				k = ask_chg(str[lll], i, j + 'a');
				if (k) dp[lll] = max(dp[lll], dp[k] + 1);
//					printf("chg %d %d %d\n", i, j, ans);
			}
		}
		rrrt = max(rrrt, dp[lll]);
//		printf("%d %s\n", dp[lll], str[lll]);
	}
	printf("%d\n", rrrt);
	return 0;
}