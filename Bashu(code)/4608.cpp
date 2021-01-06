#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <queue>
#include <cstdlib>
using namespace std;
int Stack[1000];
int top = 0;
struct Trie {
	int l;
	int r;
	int flag;
	void init() {
		l = 0;
		r = 0;
		flag = 0;
	}
} Tree[20000000];
int cnt = 0;
int length = 0;
bool get[35];
int Root;
void build(int &root) {
	root = ++cnt;
	Tree[root].init();
}
void insert(int &root, int len, int flag) {
	if (!root) {
		root = ++cnt;
		Tree[root].init();
	}
	if (len == length) {
		Tree[root].flag = flag;
		return ;
	}
	if (get[len + 1] == 1) {
		insert(Tree[root].l, len + 1, flag);
	} else {
		insert(Tree[root].r, len + 1, flag);
	}
}
void query(int root, int x, int y, int len) {
	if (Tree[root].flag != 0 && Tree[root].flag <= y) {
		while (top > 0 && Stack[top] >= Tree[root].flag) top--;
		top++;
		Stack[top] = Tree[root].flag;
	}
	if (len == 32)return;
	if (get[len + 1] == 1) {
		if (Tree[root].l) query(Tree[root].l, x, y, len + 1);
	} else {
		if (Tree[root].r) query(Tree[root].r, x, y, len + 1);
	}
}
int main() {
	int n;
	char ch;
	scanf("%d", &n);
	build(Root);
	int t = 1;
	for (int i = 1; i <= n; i++) {
		ch = getchar();
		while (ch != 'A' && ch != 'Q') ch = getchar();
		if (ch == 'A') {
			int a, b, c, d;
			scanf("%d.%d.%d.%d/%d", &a, &b, &c, &d, &length);
			memset(get, 0, sizeof(get));
			for (int j = 7; j >= 0; j--) if((1 << j) & a) get[8 - j] = 1;
			for (int j = 7; j >= 0; j--) if((1 << j) & b) get[16 - j] = 1;
			for (int j = 7; j >= 0; j--) if((1 << j) & c) get[24 - j] = 1;
			for (int j = 7; j >= 0; j--) if((1 << j) & d) get[32 - j] = 1;
			insert(Root, 0, t);
			t++;
		}
		if (ch == 'Q') {
			int a, b, c, d, x, y;
			scanf("%d.%d.%d.%d %d %d", &a, &b, &c, &d, &x, &y);
			memset(get, 0, sizeof(get));
			for (int j = 7; j >= 0; j--) if((1 << j) & a) get[8 - j] = 1;
			for (int j = 7; j >= 0; j--) if((1 << j) & b) get[16 - j] = 1;
			for (int j = 7; j >= 0; j--) if((1 << j) & c) get[24 - j] = 1;
			for (int j = 7; j >= 0; j--) if((1 << j) & d) get[32 - j] = 1;
			memset(Stack, 0, sizeof(Stack));
			top = 0;
			query(Root, x, y, 0);
			int ans = 0;
			while (Stack[top] >= x) ans++, top--;
			printf("%d\n", ans);
		}
	}
	return 0;
}