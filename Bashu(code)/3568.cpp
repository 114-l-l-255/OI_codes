#include <cstdio>
#define null 1000001
const int MAXN = 1000002;
int nxt[MAXN], pre[MAXN];
int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 1; i < n; i++) {
		nxt[i] = i + 1;
	}
	nxt[n] = null;
	for (int i = 2; i <= n; i++) {
		pre[i] = i - 1;
	}
	pre[1] = null;
	for (int i = 0; i < m; i++) {
		char ch;
		int a, b;
		scanf("\n");
		scanf("\r");
		scanf("\n");
		scanf("%c %d %d", &ch, &a, &b);
		if (a == b) continue;
		if (ch == 'A') {
			int prea = pre[a];
			int nxta = nxt[a];
			int preb = pre[b];
			if (preb == a) preb = pre[preb];
			nxt[prea] = nxta;
			pre[nxta] = prea;
			nxt[preb] = a;
			pre[a] = preb;
			nxt[a] = b;
			pre[b] = a;
		}
		if (ch == 'B') {
			int prea = pre[a];
			int nxta = nxt[a];
			int nxtb = nxt[b];
			if (nxtb == a) nxtb = nxt[nxtb];
			nxt[prea] = nxta;
			pre[nxta] = prea;
			nxt[b] = a;
			pre[a] = b;
			nxt[a] = nxtb;
			pre[nxtb] = a;
		}
	}
	int start;
	for (int i = 1; i <= n; i++) {
		if (pre[i] == null) {
			start = i;
			break;
		}
	}
	for (int i = 1; i <= n; i++) {
		printf("%d\n", start);
		start = nxt[start];
	}
	return 0;
}