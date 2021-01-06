#include <cstdio>
#include <queue>
using namespace std;
priority_queue<int> pq1;
priority_queue<int, vector<int>, greater<int> > pq2;
int main() {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		int x;
		scanf("%d", &x);
		pq1.push(x);
		while (!pq2.empty() && !pq1.empty() && pq1.top() > pq2.top()) {
			pq1.push(pq2.top());
			pq2.pop();
			pq2.push(pq1.top());
			pq1.pop();
		}
		while (pq2.size() > (i / 2)) {
			pq1.push(pq2.top());
			pq2.pop();
		}
		while (pq2.size() < (i / 2)) {
			pq2.push(pq1.top());
			pq1.pop();
		}
		if (i % 2 == 1) {
			printf("%d\n", pq1.top());
		}
	}
	return 0;
}