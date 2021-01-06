#include <bits/stdc++.h>
using namespace std;
struct node {
	vector<int> arr;
	int flag;
	int son[10];
	node() {
		flag = 0;
		arr.clear();
		memset(son, 0, sizeof(son));
	}
} nd[6000005];
int rt = 1, nodecnt = 1, Q;
char s[65];
void Insert(int id, char *str, int on) {
	int root = 1, n = strlen(str + 1);
	for (int i = 1; i <= n; i++) {
		if (!nd[root].son[str[i] - 'a']) {
			nd[root].son[str[i] - 'a'] = ++nodecnt;
		}
		root = nd[root].son[str[i] - 'a'];
		nd[root].flag += on;
		if (nd[root].flag > nd[root].arr.size()) nd[root].arr.push_back(id);
	}
}
int Query(char *str, int x) {
	int root = 1, n = strlen(str + 1);
	for (int i = 1; i <= n; ++i) {
		if (!nd[root].son[str[i] - 'a']) return -1;
		root = nd[root].son[str[i] - 'a'];
	}
	if (nd[root].arr.size() - 1 < x) return -1;
	return nd[root].arr[x];
}
int main() {
	scanf("%d", &Q);
	int ans = 0;
	for (int i = 1; i <= Q; ++i) {
		int op;
		int a, b, c;
		scanf("%d", &op);
		memset(s, 0, sizeof s);
		scanf("%s", s + 1);
		if (op == 1) Insert(i, s, 1);
		else if (op == 2) Insert(i, s, -1);
		else {
			scanf("%d %d %d", &a, &b, &c);
			int t = (1ll * (int)(abs((double)ans)) * a + b) % c;
			printf("%d\n", ans = Query(s, t));
		}
	}
	return 0;
}