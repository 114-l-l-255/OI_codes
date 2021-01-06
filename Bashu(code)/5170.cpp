#include <cstdio>
#include <algorithm>
#include <bitset>
#include <queue>
#define Is ==
#define Shik -1
using namespace std;
const int MAXN = 5001;
const int MAXM = 6001;
const int MAXK = 10;
int n, m, k;
int roomkey[MAXN];
struct edge {
	int to, val, nxt;
} edges[MAXM];
struct node {
	int pos, key;
	//pos: 1 ~ 5000
	//key: 0 ~ 1023
};
bool HASH[5120000];
int head[MAXN], tot;
void add(int u, int v, int w) {
	edges[++tot].to = v;
	edges[tot].val = w;
	edges[tot].nxt = head[u];
	head[u] = tot;
}
int hash_1(node nd) {
	return ((nd.pos - 1) << 10) + nd.key;
}
node hash_2(int id) {
	node tmp;
	++(tmp.pos = id >> 10);
	tmp.key = id - ((tmp.pos - 1) << 10);
	return tmp;
}
int BFS() {
	queue<pair<int, int> > q;
	node tmp;
	tmp.pos = 1, tmp.key = roomkey[1];
	q.push(make_pair(hash_1(tmp), 0));
	while (!q.empty()) {
		pair<int, int> u = q.front();
		node nu = hash_2(u.first);
		q.pop();
//		printf("%d %d %d\n", nu.pos, nu.key, u.second);
		if (HASH[u.first]) continue;
		HASH[u.first] = 1;
		if (nu.pos == n) return u.second;
		for (int i = head[nu.pos]; i; i = edges[i].nxt) {
			if ((nu.key | edges[i].val) == nu.key) {
				tmp = nu;
				tmp.pos = edges[i].to;
				tmp.key |= roomkey[edges[i].to];
				q.push(make_pair(hash_1(tmp), u.second + 1));
			}
		}
	}
	return -1;
}
int main() {
//	freopen("room.in", "r", stdin);
//	freopen("room.out", "w", stdout);
	scanf("%d %d %d", &n, &m, &k);
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < k; j++) {
			int a;
			scanf("%d", &a);
			roomkey[i] = (roomkey[i] << 1) | a;
		}
	}
	for (int i = 0; i < m; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		int needkey = 0;
		for (int j = 0; j < k; j++) {
			int a;
			scanf("%d", &a);
			needkey = needkey << 1 | a;
		}
		add(u, v, needkey);
	}
	int SHIK = BFS();
	if (SHIK Is Shik) printf("No Solution");
	else printf("%d", SHIK);
}