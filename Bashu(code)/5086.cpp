#include <cstdio>
const int mod = 123456789;
const int N = 10010;
int f[N], F[N], g[N], s1[N], s2[N], ans[N], n;
int max(int x, int y) { return x > y ? x : y; }
int main() {
    scanf("%d", &n);
    g[1] = g[2] = 1;
    for (int i = 3; i <= n; i++) g[i] = (g[i - 1] + g[i - 2]) % mod;
    s1[0] = f[0] = 1;
    for (int i = 1; i <= n; i++) f[i] = F[i - 1], F[i] = (F[i - 1] + f[i - 1]) % mod;
    for (int i = 1; i <= n; i++) s1[i] = (s1[i - 1] + f[i]) % mod, s2[i] = (s2[i - 1] + F[i]) % mod;
    for (int i = 1; i <= n - 1; i++) (ans[i] += 1ll * s1[n - i - 1] * f[i] % mod) %= mod;
    for (int i = 1; i <= n << 1; i++)
        for (int k = 1; k <= i; k++)
            (ans[i] += 1ll * f[k - 1] * g[i - k - 1] % mod * s2[n - 2 - max(k - 1, i - k - 1)] % mod) %= mod;
    for (int i = 1; i <= n << 1; i++) printf("%d ", ans[i]);
    return 0;
}