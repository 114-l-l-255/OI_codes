#include <cstdio>
#include <algorithm>
#include <cstring>
#include <stack>
#include <queue>
using namespace std;
const int MAXN = 1001;
const int MAXM = 2000001;
struct edge {
    int to, nxt;
} edges[MAXM];
int head[MAXN], cnt;
int a[MAXN];
int dp[MAXN];
int vis[MAXN];
stack<int> s[2];
void add(int u, int v) {
    edges[++cnt].to = v;
    edges[cnt].nxt = head[u];
    head[u] = cnt;
}
int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    dp[n] = a[n];
    for (int i = n - 1; i >= 1; i--) {
        dp[i] = min(dp[i + 1], a[i]);
    }
    for (int i = 1; i < n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (a[i] < a[j] && dp[j] < a[i]) {
                add(i, j);
                add(j, i);
                vis[i] = -1;
                vis[j] = -1;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (!~vis[i]) {
            queue<int> que;
            que.push(i);
            vis[i] = 0;
            while (!que.empty()) {
                int u = que.front();
                que.pop();
                for (int i = head[u]; i; i = edges[i].nxt) {
                    if (!~vis[edges[i].to]) {
                        vis[edges[i].to] = vis[u] ^ 1;
                        que.push(edges[i].to);
                    }
                    else if (!vis[edges[i].to] ^ vis[u]) {
                        return printf("0"), 0;
                    }
                }
            }
        }
    }
    int turn = 1;
    for (int i = 1; i <= n; i++) {
        int in = a[i];
        int sta = vis[i];
        if (sta) {
            while (!s[0].empty() && s[0].top() == turn) {
                printf("b ");
                s[0].pop();
                turn++;
            }
        }
        while (!s[sta].empty() && s[sta].top() < in) {
            if (s[sta].empty() || s[sta].top() != turn) {
                printf("%c ", sta ? 'b' : 'd');
                s[sta ^ 1].pop();
                turn++;
            }
            else {
                printf("%c ", sta ? 'd' : 'b');
                s[sta].pop();
                turn++;
            }
        }
        if (sta) {
            while (!s[0].empty() && s[0].top() == turn) {
                printf("b ");
                s[0].pop();
                turn++;
            }
        }
        s[sta].push(in);
        printf("%c ", sta ? 'c' : 'a');
    }
    bool flag = 1;
    while (flag) {
        flag = 0;
        while (!s[0].empty() && s[0].top() == turn) {
            printf("b ");
            s[0].pop();
            turn++;
            flag = 1;
        }
        while (!s[1].empty() && s[1].top() == turn) {
            printf("d ");
            s[1].pop();
            turn++;
        }
    }
    return 0;
}