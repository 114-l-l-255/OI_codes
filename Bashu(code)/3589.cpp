#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXN = 1000001;
char s1[MAXN], s2[MAXN];
int n, m, tot;
int nxt[MAXN];
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
void KMP() {
    Getnxt();
    // printf("!");
    int j = 0;
    for (int i = 0; i < n; ) {
        // printf("%d %d\n", i, j);
        if (j == -1 || s1[i] == s2[j]) {
            i++, j++;
        }
        else j = nxt[j];
        if (j == m) {
            tot++, j = nxt[j];
        }
    }
}
int main() {
	int ns;
	scanf("%d", &ns);
	while (ns--) {
		memset(s1, 0, sizeof s1);
		memset(s2, 0, sizeof s2);
		memset(nxt, 0, sizeof nxt);
	    scanf("%s %s", s2, s1);
	    n = strlen(s1);
	    m = strlen(s2);
	    tot = 0;
	    KMP();
	    printf("%d\n", tot);
	}
    return 0;
}