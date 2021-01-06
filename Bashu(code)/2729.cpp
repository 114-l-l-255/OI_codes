#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXN = 10001;
const int MAXL = 21;
struct node {
	int son[26], x;
} nd[MAXN * MAXL];
int tot;
void add(char* str) {
	int np = strlen(str);
	int rt = 1;
	for (int i = 0; i < np; i++) {
		if (nd[rt].son[str[i] - 'a'] == 0) nd[rt].son[str[i] - 'a'] = ++tot, nd[tot].x = 0;
		rt = nd[rt].son[str[i] - 'a'];
//		printf("goto %d 1\n", rt);
	}
	nd[rt].x++;
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
int main() {
	tot = 1;
	int n, m;
	scanf("%d %d", &n, &m);
	char str[MAXL];
	for (int i = 0; i < n; i++) {
		memset(str, 0, sizeof str);
		scanf("%s", str);
		add(str);
	}
	for (int i = 0; i < m; i++) {
		memset(str, 0, sizeof str);
		scanf("%s", str);
		if (ask(str) != 0) puts("-1");
		else {
			int np = strlen(str);
			int ans = 0;
			for (int i = 0; i < np; i++) {
				if (i != 0 && str[i] == str[i - 1]) continue;
				ans += ask_del(str, i);
//				printf("del %d %d\n", i, ans);
			}
			for (int i = 0; i <= np; i++) {
				for (int j = 0; j < 26; j++) {
					if (i != 0 && str[i - 1] == j + 'a') continue;
					ans += ask_add(str, i, j + 'a');
//					printf("add %d %d %d\n", i, j, ans);
				}
			}
			for (int i = 0; i < np; i++) {
				for (int j = 0; j < 26; j++) {
					if (j + 'a' == str[i]) continue;
					ans += ask_chg(str, i, j + 'a');
//					printf("chg %d %d %d\n", i, j, ans);
				}
			}
			printf("%d\n", ans);
		}
	}
	return 0;
}