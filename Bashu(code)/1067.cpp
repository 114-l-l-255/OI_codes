#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
const int MAXN = 31;
long long f[MAXN][MAXN];
int root[MAXN][MAXN];
bool firstwrite;
long long search(int L, int R) {
	long long now;
	if (L > R) return 1;
	if (f[L][R] == -1)
		for (int k = L; k <= R; k++) {
	    	now = search(L, k - 1) * search(k + 1, R) + f[k][k]; 
		    if (now > f[L][R])  {
				f[L][R] = now; 
				root[L][R] = k;
		    }
		}
	return f[L][R];  
}
void preorder(int L, int r) {
    if (L > r) return;
    if (firstwrite)
        firstwrite = false;
    else
        printf(" ");
    printf("%d", root[L][r]);
    preorder(L, root[L][r] - 1);
    preorder(root[L][r] + 1, r);
}
int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j++)
            f[i][j] = -1;
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &f[i][i]);
        root[i][i] = i;
    }
    printf("%lld\n", search(1, n));
    firstwrite = true;
    preorder(1, n);
    return 0;
}