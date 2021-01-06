#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXN = 2001;
int a[MAXN], n;
const int mod = 998244353;
long long sum, ans, fac[MAXN], tot1, tot2, f[MAXN][MAXN], g[MAXN];
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++) {
        if (a[i] == 1) tot1++;
        else tot2++;
    }
    g[0] = 1;
    for (int i = 2; i <= tot1; i++) g[i] = (g[i - 2] + 1ll * g[i - 4] * (i - 2) * (i - 3) % mod) % mod;
    ans = g[tot1] % mod;
    tot1 /= 2;
    f[0][0] = 1;
    for (int i = 1; i <= tot2; i++) {
        for (int j = 0; j <= i; j++) {
            if (tot1) f[i][j] = 1ll * f[i - 1][j] * (i - j - 1 + tot1) % mod;
            if (j > 2) f[i][j] = (f[i][j] + 1ll * f[i - 3][j - 3] * (i - 2) * (i - 1) / 2 % mod) % mod;
            if (j) f[i][j] = (f[i][j] + 1ll * f[i - 1][j - 1] * (j - 1) % mod) % mod;
        }
    }
    for (int i = 0; i <= tot2; i++) sum = (sum + f[tot2][i]) % mod;
    printf("%lld\n", ans * sum % mod);
}