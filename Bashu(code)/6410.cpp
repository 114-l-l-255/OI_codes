#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
const int MAXN = 50, MAXM = 16, MAX2M = 65536;
short map[MAXN][MAXN];
short mem[MAXN][MAXN][MAX2M];
pair<short, short> way[] = {
	make_pair(0, 1),
	make_pair(1, 0),
	make_pair(0, -1),
	make_pair(-1, 0)
};
struct node {
	short x, y;
	int br;
	unsigned short step;
	node() {}
	node(int a, int b, int c, int d) {
		x = a, y = b, br = c, step = d;
	}
};
int n, m;
int BFS() {
	mem[0][0][0] = (short)1;
	queue<node> que;
	que.push(node(0, 0, 0, 1));
	while (!que.empty()) {
		node u = que.front();
		que.pop();
//		printf("%d %d %d %d\n", u.x, u.y, u.br, u.step);
		mem[u.x][u.y][u.br] = u.step;
		for (int i = 0; i <= 3; i++) {
			node v = node(u.x + way[i].first, u.y + way[i].second, u.br, u.step + 1);
			if (u.x == n - 1 && u.y == n - 1) return u.step;
//			printf("%d %d %d %d-\n", v.x, v.y, mem[v.x][v.y][v.br], map[v.x][v.y]);
			if (v.x >= 0 && v.y >= 0 && v.x < n && v.y < n && mem[v.x][v.y][v.br] == 0 && (map[v.x][v.y] == 0 || (map[v.x][v.y] >= 1 && map[v.x][v.y] <= m) || (map[v.x][v.y] > m && (1 << (map[v.x][v.y] - m - 1) & v.br)))) {
				if (map[v.x][v.y] >= 1 && map[v.x][v.y] <= m) {
					v.br |= (1 << map[v.x][v.y] - 1);
				}
				mem[v.x][v.y][v.br] = v.step;
				que.push(v);
			}
		}
	}
	int ans = 0x7fffffff;
	for (int i = 0; i < (1 << m); i++) {
		if (mem[n - 1][n - 1][i]) ans = min(ans, (int)mem[n - 1][n - 1][i]);
	}
	return ans;
}
int main() {
//	freopen("syndicate.in", "r", stdin);
//	freopen("syndicate.out", "w", stdout);
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int a;
			scanf("%d", &a);
				map[i][j] = a;
		}
//		printf("line\n");
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
				if (map[i][j] == -2) {
				if (i && map[i - 1][j] != -2) map[i - 1][j] = -1;
				if (j && map[i][j - 1] != -2) map[i][j - 1] = -1;
				if (i != n - 1 && map[i + 1][j] != -2) map[i + 1][j] = -1;
				if (j != n - 1 && map[i][j + 1] != -2) map[i][j + 1] = -1;
			}
		}
	}
	printf("%d", BFS() - 1);
	return 0;
}
/*
6 2
0 0 0 -2 -1 2
-1 0 0 0 -1 0
-2 0 0 0 3 3
-2 0 0 -1 -1 4
0 -1 0 0 -1 0
1 0 0 0 -1 0
*/