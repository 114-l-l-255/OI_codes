#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXN = 32001;
struct node {
	int son[26];
} nd[MAXN];
int tot = 1;
void add(char* str) {
	int np = strlen(str);
	int rt = 1;
	for (int i = 0; i < np; i++) {
		if (nd[rt].son[str[i] - 'A'] == 0) nd[rt].son[str[i] - 'A'] = ++tot;
		rt = nd[rt].son[str[i] - 'A'];
	}
}
int main() {
	char str[70];
	while (~scanf("%s", str)) {
		add(str);
		memset(str, 0, sizeof str);
	}
	printf("%d\n", tot);
	return 0;
}