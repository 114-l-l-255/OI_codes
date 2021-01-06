#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 100001;
int Xor[MAXN];
int son[MAXN * 31][2], cnt;
void adda(int str) {
	int root = 1;
	for (int i = 30; ~i; i--) {
		int kk = bool(str & (1 << i));
		if (son[root][kk] == 0) son[root][kk] = ++cnt;
		root = son[root][kk];
	}
}
int ask_YIW(int str) {
	int root = 1, ans = 0;
	for (int i = 30; ~i; i--) {
		int kk = bool(str & (1 << i));
		if (son[root][1 - kk] == 0) ans += (1 << i), root = son[root][kk];
		else root = son[root][1 - kk];
	}
	return ((1ull << 31) - 1) ^ ans;
}
int main() {
	cnt = 1;
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &Xor[i]);
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		adda(Xor[i]);
		ans = max(ans, ask_YIW(Xor[i]));
//		printf("%d %d\n", Xor[i], ask_YIW(Xor[i]));
	}
	printf("%d", ans);
	return 0;
}