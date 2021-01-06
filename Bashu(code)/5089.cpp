#include <cstdio>
#include <iostream>
#include <cstring>
#include <queue>
#define pre(x) node[x].pre
#define nxt(x) node[x].nxt
#define val(x) node[x].val
using namespace std;
const int maxn = 10000001, INF = 0x7f7f7f7f;
int m, maxnode, pos[2], cnt[2], BEGIN, END, q;
char T[maxn];
queue<int> que;
struct data {
	int pre, nxt;
	char val;
	inline void clear() {
		pre = nxt = 0;
		val = '\0';
	}
} node[maxn];
inline int Require() {
	if (!que.empty()) {
		int temp = que.front();
		que.pop();
		return temp;
	}
	return ++maxnode;
}
inline void Recycle(int x) {
	que.push(x);
	node[x].clear();
}
inline void L_move(int op) {
	if (pos[op] == BEGIN) {
		putchar('F');
		return;
	}
	int u = pos[op], v = pre(u);
	if (nxt(v) ^ u) swap(pre(v), nxt(v));
	pos[op] = v;
	cnt[op]--;
	putchar('T');
}
inline void R_move(int op) {
	if (nxt(pos[op]) == END) {
		putchar('F');
		return;
	}
	int u = nxt(pos[op]), v = nxt(u);
	if (pre(v) ^ u) swap(pre(v), nxt(v));
	pos[op] = u;
	cnt[op]++;
	putchar('T');
}
inline void Insert(int op, char ch) {
	int u = pos[op], v = nxt(u);
	int cur = Require();
	val(cur) = ch;
	pre(cur) = u;
	nxt(cur) = v;
	nxt(u) = cur;
	pre(v) = cur;
	if (cnt[op ^ 1] >= cnt[op]) cnt[op ^ 1]++;
	pos[op] = cur;
	cnt[op]++;
	if (pos[op ^ 1] == u) pos[op ^ 1] = cur;
	putchar('T');
}
inline void Delete(int op) {
	if (nxt(pos[op]) == END) {
		putchar('F');
		return;
	}
	int u = pos[op], v = nxt(u), w = nxt(v);
	if (pre(w) ^ v) swap(pre(w), nxt(w));
	Recycle(v);
	nxt(u) = w;
	pre(w) = u;
	if (cnt[op ^ 1] > cnt[op]) cnt[op ^ 1]--;
	if (pos[op ^ 1] == v) pos[op ^ 1] = u;
	putchar('T');
}
inline void Reserve() {
	if (cnt[1] <= cnt[0]) {
		putchar('F');
		return;
	}
	if (cnt[1] == cnt[0] + 1) {
		putchar('T');
		return;
	}
	int p1 = pos[0], p2 = nxt(p1), p3 = pos[1], p4 = nxt(p3);
	swap(pre(p2), nxt(p2));
	swap(pre(p3), nxt(p3));
	nxt(p1) = p3;
	pre(p3) = p1;
	nxt(p2) = p4;
	pre(p4) = p2;
	pos[1] = p2;
	putchar('T');
}
inline void Show() {
	int root = BEGIN;
	do {
		if(pre(nxt(root)) ^ root) swap(pre(nxt(root)), nxt(nxt(root)));
		root = nxt(root);
		putchar(val(root));
	} while(nxt(root) ^ END);
}
void init() {
	int len = strlen(T);
	BEGIN = 1, END = 2;
	maxnode = 2;
	for (int i = 0; i < len; i++) {
		val(++maxnode) = T[i];
		pre(maxnode) = i == 0 ? BEGIN : maxnode - 1;
		nxt(maxnode) = i == len - 1 ? END : maxnode + 1;
	}
	pre(BEGIN) = -1;
	nxt(BEGIN) = 3;
	pre(END) = maxnode;
	nxt(END) = -1;
	pos[0] = BEGIN;
	pos[1] = maxnode;
	cnt[0] = 0;
	cnt[1] = len;
}
inline char read() {
	char ch = getchar();
	while (ch == ' ' || ch == '\n' || ch == '\r') ch = getchar();
	return ch;
}
int main() {
//	freopen("editor.in", "r", stdin);
//	freopen("editor.out", "w", stdout);
	scanf("%s", T);
	init();
	scanf("%d", &q);
	while (q--) {
		char op = read();
		char temp;
		switch (op) {
			case '<':
				L_move(read() == 'R');
				break;
			case '>':
				R_move(read() == 'R');
				break;
			case 'I':
				temp = read();
				Insert(temp == 'R', read());
				break;
			case 'D':
				Delete(read() == 'R');
				break;
			case 'R':
				Reserve();
				break;
			case 'S':
				Show();
				break;
		}
		putchar('\n');
	}
	return 0;
}