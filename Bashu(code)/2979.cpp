#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
struct node {
	int son[36];
	int x;
	bool end;
} nd[100001];
int cnt1;
int rt[100001], cnt2;
int ans;
int tr(char ch) {
	if ('a' <= ch && ch <= 'z') return ch - 'a';
	if ('0' <= ch && ch <= '9') return ch - '0' + 26;
}
void change(char* str) {
	int ns = strlen(str);
	int rrt = 1;
	for (int i = 0; i < ns; i++) {
		if (str[i] == '/') {
			if (nd[rrt].x == 0) {
				nd[rrt].x = ++cnt2, rt[cnt2] = (++cnt1);
				if (nd[rrt].end == 1) {
					nd[rrt].end = 0;
					ans--;
				}
				ans++;
			}
			rrt = rt[nd[rrt].x];
		}
		else {
			if (nd[rrt].son[tr(str[i])] == 0) nd[rrt].son[tr(str[i])] = (++cnt1);
			rrt = nd[rrt].son[tr(str[i])];
		}
	}
	if (nd[rrt].end == 0 && nd[rrt].x == 0) ans++, nd[rrt].end = 1;
}
int main() {
	cnt1 = cnt2 = 1;
	rt[1] = 1;
	int n;
	scanf("%d", &n);
	char str[101];
	for (int i = 0; i < n; i++) {
		scanf("%s", str);
		change(str);
		memset(str, 0, sizeof str);
		printf("%d\n", ans - 1);
	}
	return 0;
}