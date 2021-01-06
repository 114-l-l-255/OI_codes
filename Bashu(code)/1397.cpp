#pragma GCC optimize(2)
#include <cstdio>
#include <cstring>
#include <stack>
#include <algorithm>
using namespace std;
const int MAXN = 1000001;
int sum[MAXN];
int dp[MAXN];
int main() {
	int t;
	while (~scanf("%d", &t)) {
		memset(sum, 0, sizeof(sum));
		memset(dp, 0xcf, sizeof(dp));
		stack<int> s1, s2;
		int pos = 0;
		while (t--) {
			char c = getchar();
			while (c != 'I' && c != 'D' && c != 'L' && c != 'R' && c != 'Q') c = getchar();
			if (c == 'I') {
				int a;
				scanf("%d", &a);
				s1.push(a);
				pos++;
				sum[pos] = sum[pos - 1] + a;
				dp[pos] = max(dp[pos - 1], sum[pos]);
			} else if (c == 'Q') {
				int a;
				scanf("%d", &a);
				printf("%d\n", dp[a]);
			} else if (c == 'L') {
				if (s1.empty()) continue;
				pos--;
				int b = s1.top();
				s1.pop();
				s2.push(b);
			} else if (c == 'D') {
				if (s1.empty()) continue;
				s1.pop();
				pos--;
			} else if (c == 'R') {
				if (s2.empty()) continue;
				int b = s2.top ();
				s2.pop();
				s1.push(b);
				pos++;
				sum[pos] = sum[pos - 1] + b;
				dp[pos] = max(dp[pos - 1], sum[pos]);
			} else {
				puts("♂");
			}
		}
	}
	return 0;
}