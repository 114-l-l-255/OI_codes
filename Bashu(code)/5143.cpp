#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1005, maxk = 1000005;
int n, m, ca, color[maxn], tot, now[maxn], prep[maxk], son[maxk], wi[maxn][2];
bool bo;
void add(int x, int y) {
    tot++, prep[tot] = now[x], now[x] = tot, son[tot] = y;
}
void dfs(int x, int y) {
    color[x] = y;
    for (int i = now[x], so = son[i]; i; i = prep[i], so = son[i]) {
        if (color[so] == -1) {
            dfs(so, 1 - y);
        }
        else if (color[x] == color[so]) bo = 0;
    }
}
int main() {
    scanf("%d", &ca);
    while (ca--) {
        scanf("%d %d", &n, &m);
		bo = 1;
        tot = 0, memset(now,0,sizeof(now));
        for (int i = 1; i <= m; i++) {
            scanf("%d %d", &wi[i][0], &wi[i][1]);
            if (wi[i][0] > wi[i][1])
            swap(wi[i][0], wi[i][1]);
        }
        int a, b, c, d;
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= m; j++) {
                a = wi[i][0], b = wi[i][1], c = wi[j][0], d = wi[j][1];
                if (a < c && c < b && b < d)
                     add(i, j), add(j, i);
            }
        }
        memset(color, -1, sizeof(color));
        for (int i = 1; i <= m; i++)
			if (color[i] == -1)
				dfs(i, 1);
        if (bo == 1) {
        	puts("sane");
		}
        else {
        	puts("non");
		}
    }
    return 0;
}