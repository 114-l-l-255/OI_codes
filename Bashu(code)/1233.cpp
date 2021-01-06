#include <cstdio>
#include <cstring>
#define int long long
using namespace std;
const int MAXN = 50001;
int n, a[MAXN], c[1000005], ans[50];
long long f[MAXN];
int lowbit(int x) {
	return x & (-x);
}
void add(int x, int d) {
	for (int i = x; i <= 1000000; i += lowbit(i)) c[i] += d;
}
long long ask(int x) {
	long long ans = 0;
	for (int i = x; i; i -= lowbit(i)) ans += c[i];
	return ans;
}
void jia(int a[], int b[]) {
	if (a[0] < b[0]) a[0] = b[0];
	for (int i = 1; i <= a[0]; ++i) a[i] += b[i];
	for (int i = 1; i <= a[0]; ++i) a[i + 1] += a[i] / 10, a[i] %= 10;
	if (a[a[0] + 1] > 0) ++a[0];
}
void print(int a[]) {
	if (a[0] == 0) printf("0\n");
	for (int i = a[0]; i; --i) printf("%lld", a[i]);
}
signed main() {
	scanf("%lld", &n);
	for (int i = 1; i <= n; ++i) scanf("%lld", &a[i]),f[i]=1;
	for (int i = 2; i <= 5; ++i) {
		memset(c, 0, sizeof(c));
		add(a[i - 1], f[i - 1]);
		f[i - 1] = 0;
		for (int j = i; j <= n; ++j) add(a[j], f[j]), f[j] = ask(a[j] - 1);
	}
	for (int i = 5; i <= n; ++i) {
		int temp[50];
		memset(temp, 0, sizeof(temp));
		while (f[i] > 0) temp[++temp[0]] = f[i] % 10, f[i] /= 10;
		jia(ans, temp);
	}
	print(ans);
	return 0;
}