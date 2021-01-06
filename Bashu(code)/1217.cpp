#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 50002;
const int MAXLogn = 20;
int my_log[MAXN];
int STMax[MAXN][MAXLogn];
int STMin[MAXN][MAXLogn];
int a[MAXN];
int main() {
    my_log[0] = -1;
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        STMax[i][0] = STMin[i][0] = a[i];
        my_log[i] = my_log[i / 2] + 1;//qwq
    }
    for (int i = 1; i <= my_log[n]; i++) {
        for (int j = 1; j <= n - (1 << i) + 1; j++) {
            STMin[j][i] = min(STMin[j][i - 1], STMin[j + (1 << i - 1)][i - 1]);
            STMax[j][i] = max(STMax[j][i - 1], STMax[j + (1 << i - 1)][i - 1]);
        }
    }
    for (int i = 0; i < m; i++) {
        int l, r;
        scanf("%d %d", &l, &r);
        int jump = my_log[r - l + 1];
        printf("%d\n", max(STMax[l][jump], STMax[r - (1 << jump) + 1][jump]) - min(STMin[l][jump], STMin[r - (1 << jump) + 1][jump]));
    }
    return 0;
}