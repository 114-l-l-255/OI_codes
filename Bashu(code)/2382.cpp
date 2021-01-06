#include <cstdio>
#include <queue>
using namespace std;
const int MAXN = 2000001;
int a[MAXN];
int main() {
	priority_queue<int, vector<int>, greater<int> > pq1;
	priority_queue<int> pq2;
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	int ind = 1;
	for (int i = 1; i <= m; i++) {
		int k;
		scanf("%d", &k);
		while (ind <= k) {
			if (i != 1 && pq2.top() > a[ind]) {
				pq2.push(a[ind]);
//				printf("%d in %d\n", a[ind], 2);
				pq1.push(pq2.top());
//				printf("%d in %d\n", pq2.top(), 1);
				pq2.pop();
			}
			else {
				pq1.push(a[ind]);
			}
			ind++;
		}
		printf("%d\n", pq1.top());
		pq2.push(pq1.top());
//		printf("%d in %d\n", pq1.top(), 2);
		pq1.pop();
	}
	return 0;
}