#include <cstdio>
#include <cstring>
#include <algorithm>
#define INF 0x3f3f3f3f
using namespace std;
const int MAXN = 2201;
int n, k, ans, lll;
int a[MAXN], f[MAXN][MAXN][2];
int t[MAXN][MAXN];
int main() {
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        lll += a[i];
    }
    for (int i = 1; i <= n; i++) {
        int l = i, r = n - 1;
        if (r == 0)
            r = n;
        t[i][i] = a[i];
        while (l != r) {
            l++;
            if (l > n)
                l = 1;
            t[i][l] = max(a[l], t[i][l - 1]);
        }
    }
    ans = INF;
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n - i; j++) {
            if (!i && !j)
                continue;
            if (i > 0) {
                int mx;
                if (i + k + 1 > n - j - k)
                    mx = 0;
                else
                    mx = t[i + k + 1][n - j - k];
                f[i][j][0] = min(f[i - 1][j][0] + mx, f[i - 1][j][1] + mx * (i + j));
            }
            else {
                f[i][j][0] = INF;
            }
            if (j > 0) {
                int mx;
                if (i + k + 2 > n - j - k + 1)
                    mx = 0;
                else
                    mx = t[i + k + 2][n - j - k + 1];
                f[i][j][1] = min(f[i][j - 1][1] + mx, f[i][j - 1][0] + mx * (i + j));
            }
            else {
                f[i][j][1] = INF;
            }
            if (i + j == n) {
                ans = min(ans, f[i][j][1]);
                ans = min(ans, f[i][j][0]);
            }
        }
    printf("%d", ans + lll);
}