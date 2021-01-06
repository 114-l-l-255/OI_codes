#include <bits/stdc++.h>
using namespace std;
priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int > > > q;
const int MAXN = 100010;
const int inf = 1e9;
int len[MAXN],pre[MAXN],nxt[MAXN];
int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	int x = 0, y = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &y);
		len[i] = y - x;
		pre[i] = i - 1, nxt[i] = i + 1;
		x = y;
	}
	int ans = 0;
	for (int i = 2; i <= n; i++)
		q.push(make_pair(len[i], i));
	pre[2] = 0, nxt[n] = 0;
	while (m--) {
		while (q.top().first != len[q.top().second]) q.pop();
		int x = q.top().second, l = pre[x], r = nxt[x];
		ans += len[x];
		q.pop();
		pre[nxt[x] = nxt[r]] = x;
		nxt[pre[x] = pre[l]] = x;
		len[x] = l && r ? min(inf, len[l] + len[r] - len[x]) : inf;
		len[l] = len[r] = inf;
		q.push(make_pair(len[x], x));
	}
	printf("%d", ans);
	return 0;
}