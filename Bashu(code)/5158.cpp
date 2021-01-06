#include <bits/stdc++.h>
const int MAXN = 100001;
using namespace std;
inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
int cnt, rt, tot, sum;
long long x, y, k, n;
int Head[MAXN], ret[MAXN << 1], Next[2 * MAXN];
int val[MAXN];
int size[MAXN], mx[MAXN], bl[MAXN];
long long in[MAXN], out[MAXN], fac[MAXN], inv[MAXN];
struct node {
    long long v;
    int id;
} qg[MAXN], qh[MAXN];
bool flag[MAXN];
bool cmp(node a, node b) { return a.v < b.v; }
long long qkpow(long long x, long long k) {
    long long t = 1;
    while (k) {
    	if (k & 1) t = (t * x) % y;
    	x = x * x % y;
    	k >>= 1;
	}
    return t;
}
void pre() {
    fac[0] = 1;
    for (register int i = 1; i <= n; i++) {
        fac[i] = (long long)fac[i - 1] * k % y;
    }
    inv[n] = qkpow(fac[n], y - 2);
    for (register int i = n - 1; i; i--) {
        inv[i] = (long long)inv[i + 1] * k % y;
    }
}
inline void ins(int u, int v) {
    ret[++tot] = v;
    Next[tot] = Head[u];
    Head[u] = tot;
}
void getroot(int u, int f) {
    size[u] = 1;
    mx[u] = 0;
    for (int i = Head[u]; i; i = Next[i]) {
        int v = ret[i];
        if (!flag[v] && v != f) {
            getroot(v, u);
            size[u] += size[v];
            mx[u] = max(mx[u], size[v]);
        }
    }
    mx[u] = max(mx[u], sum - size[u]);
    if (mx[u] < mx[rt])
        rt = u;
}
void dfs(int u, int f, long long h, long long g, int l) {
    qh[++cnt].v = h;
    qg[cnt].v = (((long long)(x - g) % y + y) % y) * inv[l] % y;
    qh[cnt].id = u;
    qg[cnt].id = u;
    if (f == rt || u == rt)
        bl[u] = u;
    else
        bl[u] = bl[f];
    for (register int i = Head[u]; i; i = Next[i]) {
        int v = ret[i];
        if (v != f && !flag[v])
            dfs(v, u, (h + val[v] * fac[l - 1]) % y, (g * k + val[v]) % y, l + 1);
    }
}
int queryr(int v) {
    int l = 1, r = cnt;
    while (l != r) {
        int mid = (l + r + 1) >> 1;
        if (qg[mid].v > v)
            r = mid - 1;
        else
            l = mid;
    }
    return l;
}
int queryl(int v) {
    int l = 1, r = cnt;
    while (l != r) {
        int mid = (l + r) >> 1;
        if (qg[mid].v < v)
            l = mid + 1;
        else
            r = mid;
    }
    return l;
}
void solve(int u) {
    cnt = 0;
    flag[u] = 1;
    dfs(u, 0, 0, val[u], 1);
    sort(qh + 1, qh + cnt + 1, cmp);
    sort(qg + 1, qg + cnt + 1, cmp);
    for (register int i = 1; i <= cnt; i++) {
        int l = queryl(qh[i].v);
        int r = queryr(qh[i].v);
        if (qg[l].v != qh[i].v)
            continue;
        for (int j = l; j <= r; j++)
            if (bl[qh[i].id] != bl[qg[j].id] || (bl[qh[i].id] == rt && bl[qg[j].id] == rt)) {
                in[qh[i].id]++;
                out[qg[j].id]++;
            }
    }
    for (register int i = Head[u]; i; i = Next[i]) {
        int v = ret[i];
        if (!flag[v]) {
            rt = 0;
            sum = size[v];
            getroot(v, 0);
            solve(rt);
        }
    }
}
int main() {
    n = read(), y = read(), k = read(), x = read();
    pre();
    for (int i = 1; i <= n; i++)
        val[i] = read();
    for (int i = 1; i < n; i++) {
        int u = read(), v = read();
        ins(u, v);
        ins(v, u);
    }
    rt = 0;
    sum = n;
    mx[0] = n;
    getroot(1, 0);
    solve(rt);
    long long ans = 0;
    for (register int i = 1; i <= n; i++)
        ans += ((long long)in[i] * (n - out[i]) + (long long)out[i] * (n - in[i]) + (long long)2 * out[i] * (n - out[i]) + (long long)2 * in[i] * (n - in[i])); //,cout<<i<<" "<<in[i]<<" "<<out[i]<<endl;
    cout << (long long)n * n * n - ans / 2 << endl;
}