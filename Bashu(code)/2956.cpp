#include <cstdio>
#include <algorithm>
#include <cstring>
#include <stack>
using namespace std;
const int MAXN = 1000005;
char s2[MAXN];
int n, m, tot;
int nxt[MAXN];
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
void Getnxt() {
	nxt[0] = -1;
	int i = 0, j = -1;
	while (i < m) {
		if (j == -1 || s2[i] == s2[j]) {
			nxt[++i] = ++j;
		}
		else j = nxt[j];
	}
}
int main() {
	while (~scanf("%s", s2)) {
		m = strlen(s2);
		tot = 0;
		Getnxt();
		stack<int> st;
		while (!st.empty()) st.pop();
		for (int i = m; i && i != -1; i = nxt[i]) st.push(i);
		while (!st.empty()) printf("%d ", st.top()), st.pop();
		puts("");
		memset(s2, 0, sizeof s2);
		memset(nxt, 0, sizeof nxt);
	}
	return 0;
}