#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXN = 400005*3;
struct node {
	int son[26], tg;
} nd[MAXN];
int tot = 1;
void add(char* str, int tag) {
	int np = strlen(str);
	int rt = 1;
	for (int i = 0; i < np; i++) {
		if (nd[rt].son[str[i] - 'a'] == 0) nd[rt].son[str[i] - 'a'] = ++tot;
		rt = nd[rt].son[str[i] - 'a'];
	}
	nd[rt].tg = tag;
}
int search(char* str) {
	int np = strlen(str);
	int rt = 1;
	for (int i = 0; i < np; i++) {
		if (nd[rt].son[str[i] - 'a'] == 0) nd[rt].son[str[i] - 'a'] = ++tot;
		rt = nd[rt].son[str[i] - 'a'];
	}
	return nd[rt].tg;
}
char stdr[400005];
int main() {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%s", stdr);
		int x;
		scanf("%d", &x);
		add(stdr, x);
		memset(stdr, 0, sizeof stdr);
	}
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%s", stdr);
		printf("%d\n", search(stdr));
		memset(stdr, 0, sizeof stdr);
	}
	return 0;
}