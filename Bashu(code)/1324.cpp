#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 1001;
int n, r, ans;
struct node {
    int c, fa, t;
    double w;
} num[1001];
int find() {
    int ans;
    double maxw = 0;
    for (int i = 1; i <= n; i++)
        if (i != r && num[i].w > maxw)
            maxw = num[i].w, ans = i;
    return ans;
}
int main() {
    while (scanf("%d %d", &n, &r) && n && r) {
        ans = 0;
        for (int i = 1; i <= n; i++) scanf("%d", &num[i].c), ans += num[i].c, num[i].t = 1, num[i].fa = 0, num[i].w = num[i].c;
        for (int i = 1, a, b; i < n; i++) scanf("%d %d", &a, &b), num[b].fa = a;
        for (int i = 1; i < n; i++) {
            int tmp = find();
            num[tmp].w = 0;
            int f = num[tmp].fa;
            ans += num[tmp].c * num[f].t;
            for (int j = 1; j <= n; j++)
                if (num[j].fa == tmp)
                    num[j].fa = f;
            num[f].t += num[tmp].t;
            num[f].c += num[tmp].c;
            num[f].w = (double)(num[f].c) / num[f].t;
        }
        printf("%d\n", ans);
    }
}