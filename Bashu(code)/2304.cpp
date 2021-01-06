#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXL = 51;
struct node {
	int son[26], x;
} nd[600001];
int tot;
void add(char* str) {
	int np = strlen(str);
	int rt = 1;
	for (int i = 0; i < np; i++) {
		if (nd[rt].son[str[i] - 'a'] == 0) nd[rt].son[str[i] - 'a'] = ++tot, nd[tot].x = 0;
		rt = nd[rt].son[str[i] - 'a'];
	}
	nd[rt].x++;
}
void del(char* str) {
	int np = strlen(str);
	int rt = 1;
	for (int i = 0; i < np; i++) {
		if (nd[rt].son[str[i] - 'a'] == 0) nd[rt].son[str[i] - 'a'] = ++tot, nd[tot].x = 0;
		rt = nd[rt].son[str[i] - 'a'];
	}
	if (nd[rt].x > 0) nd[rt].x--;
}
int ask(char* str) {
	int np = strlen(str);
	int rt = 1;
	for (int i = 0; i < np; i++) {
		if (nd[rt].son[str[i] - 'a'] == 0) return 0;
		rt = nd[rt].son[str[i] - 'a'];
	}
	return nd[rt].x;
}
char str[MAXL], op[2];
int main() {
	tot = 1;
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		memset(str, 0, sizeof str);
		scanf("%s %s", op, str);
		if (op[0] == 'A') add(str);
		if (op[0] == 'B') del(str);
		if (op[0] == 'C') printf("%s\n", ask(str) ? "yes" : "no");
	}
	return 0;
}