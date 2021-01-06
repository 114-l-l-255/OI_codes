#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
const int MAXN=1000+20;
using namespace std;
int lx[MAXN],ly[MAXN],rx[MAXN],ry[MAXN];
int color[MAXN] = {1}, S[2501], N;
void cover(int x1,int y1,int x2,int y2,int c,int h)
{
    if (x1 == x2 || y1 == y2) return;
    if (h > N) S[c] += (y2 - y1) * (x2 - x1);
    else {
        if (y1 < ly[h]) cover(min(rx[h], x1), y1, min(rx[h], x2), min(ly[h], y2), c, h + 1);
        if (x2 > rx[h]) cover(max(rx[h], x1), min(ry[h], y1), x2, min(ry[h], y2), c, h + 1);
        if (y2 > ry[h]) cover(max(lx[h], x1), max(ry[h], y1), max(lx[h], x2), y2, c, h + 1);
        if (x1 < lx[h]) cover(x1, max(ly[h], y1), min(lx[h], x2), max(ly[h], y2), c, h + 1);
    }
}
int main() {
    scanf("%d %d %d", &rx[0], &ry[0], &N);
    for (int i = 1; i <= N; i++) {
    	scanf("%d %d %d %d %d", &lx[i], &ly[i], &rx[i], &ry[i], &color[i]);
	}
    S[color[N]] += (rx[N] - lx[N]) * (ry[N] - ly[N]);
    for (int i = N - 1; i >= 0; i--) cover(lx[i], ly[i], rx[i], ry[i], color[i], i + 1);
    for (int i = 1; i <= MAXN; i++) if (S[i] != 0) printf("%d %d\n", i, S[i]);
    return 0;
}