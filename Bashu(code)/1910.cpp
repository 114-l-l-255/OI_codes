#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
vector<pair<int, int> > G[101];
char str[105][105], st[105];
void dfs(int x, int diep) {
	if (G[x].size() == 0) {
		printf("%s\n", st);
		strcpy(str[x], st);
	}
	else {
		
		for (int i = 0; i < G[x].size(); i++) {
			st[diep] = '0' + i;
			dfs(G[x][i].second, diep + 1);
			st[diep] = '\0';
		}
	}
}
bool cmp(char a[105], char b[105]) {
	return strcmp(a, b) > 0;
}
int main() {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		int a;
		scanf("%d", &a);
		pq.push(make_pair(a, i));
	}
	for (int i = n + 1; i < n + n; i++) {
		pair<int, int> a = pq.top();
		pq.pop();
		pair<int, int> b = pq.top();
		pq.pop();
		G[i].push_back(a);
		G[i].push_back(b);
//		printf("%d %d %d\n",i,a.second,b.second);
		pq.push(make_pair(a.first + b.first, i));
	}
	dfs(n + n - 1, 0);
	return 0;
}