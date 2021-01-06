#include <cstring>
#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
const int MAXN = 300001;
struct edge {
	int to, nxt;
} edges[1001];
int son[MAXN][26], flag[MAXN];
string S[30001];
int len[30001];
int n, num, cnt, tot;
int head[26];
int ans[MAXN];
inline void add_edge(int x, int y) {
	edges[++num].to = y;
	edges[num].nxt = head[x];
	head[x] = num;
}
inline void ins(int x) {
	int now = 0;
	for (int i = 0; i < len[x]; i++) {
		if (!son[now][S[x][i] - 'a'])
			son[now][S[x][i] - 'a'] = ++cnt;
		now = son[now][S[x][i] - 'a'];
	}
	flag[now] = 1;
}
inline int check(int x) {
	int now = 0;
	memset(edges, 0, sizeof(edges));
	int c[26];
	memset(c, 0, sizeof(c));
	memset(head, 0, sizeof(head));
	num = 0;
	for (int i = 0; i < len[x]; i++) {
		if (flag[now])
			return 0;
		for (int j = 0; j < 26; j++)
			if (son[now][j] && S[x][i] - 'a' != j)
				add_edge(S[x][i] - 'a', j), c[j]++;
		now = son[now][S[x][i] - 'a'];
	}
	int cur = 0;
	int q[27];
	memset(q, 0, sizeof(q));
	for (int i = 0; i < 26; i++)
		if (!c[i])
			q[++cur] = i;
	for (int i = 1; i <= cur; i++) {
		for (int j = head[q[i]]; j; j = edges[j].nxt) {
			c[edges[j].to]--;
			if (!c[edges[j].to])
				q[++cur] = edges[j].to;
		}
	}
	return cur == 26;
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		cin >> S[i];
		len[i] = S[i].size();
		ins(i);
	}
	tot = 0;
	for (int i = 1; i <= n; i++)
		if (check(i))
			ans[++tot] = i;
	cout << tot << endl;
	for (int i = 1; i <= tot; i++)
		cout << S[ans[i]] << endl;
	return 0;
}