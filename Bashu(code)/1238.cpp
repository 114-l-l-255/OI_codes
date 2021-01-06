#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN = 2049;
ll n, m, c1[MAXN][MAXN], c2[MAXN][MAXN], c3[MAXN][MAXN], c4[MAXN][MAXN];
void add(ll x, ll y, ll dt) {
    for (int i = x; i <= n; i += (i & -i))
        for (ll j = y; j <= m; j += (j & -j)) {
            c1[i][j] += dt;
            c2[i][j] += dt * y;
            c3[i][j] += dt * x;
            c4[i][j] += dt * x * y;
        }
}
ll ask(ll x, ll y) {
    ll res = 0;
    for (ll i = x; i > 0; i -= (i & -i))
        for (ll j = y; j > 0; j -= (j & -j)) {
            res = res + (x + 1) * (y + 1) * c1[i][j] - (x + 1) * c2[i][j] - (y + 1) * c3[i][j] + c4[i][j];
        }
    return res;
}
void add(ll X1, ll Y1, ll X2, ll Y2, ll dt) {
    add(X1, Y1, dt);
    add(X2 + 1, Y1, -dt);
    add(X1, Y2 + 1, -dt);
    add(X2 + 1, Y2 + 1, dt);
}
ll ask(ll X1, ll Y1, ll X2, ll Y2) {
    return ask(X2, Y2) + ask(X1 - 1, Y1 - 1) -
           ask(X1 - 1, Y2) - ask(X2, Y1 - 1);
}
int main() {
    ll X1, X2, Y1, Y2, z;
    int c;
    scanf("%lld %lld", &n, &m);
    while (scanf("%lld", &c) != EOF) {
        scanf("%lld %lld %lld %lld", &X1, &Y1, &X2, &Y2);
        if (c == 1) {
            scanf("%lld", &z);
            add(X1, Y1, X2, Y2, z);
        }
        else
            printf("%lld\n", ask(X1, Y1, X2, Y2));
    }
    return 0;
}