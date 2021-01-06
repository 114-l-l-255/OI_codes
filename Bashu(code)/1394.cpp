#include <cstdio>
#include <algorithm>
int ans[6001];
inline void mul(int k) {
	for (int i = 6000; ~i; i--) {
		ans[i] *= k;
	}
	for (int i = 0; i < 6000; i++) {
		ans[i + 1] += ans[i] / 10;
		ans[i] %= 10;
	}
}
inline int div(int k) {
	int SHIK = 0;
	for (int i = 6000; ~i; i--) {
		SHIK = SHIK * 10 + ans[i];
		ans[i] = SHIK / k;
		SHIK %= k;
	} 
	return SHIK;
}
int main() {
	int n;
	scanf("%d", &n);
	ans[0] = 1;
	for (int i = 2 * n; i > n + 1; i--) {
		mul(i);
	}
	for (int i = 2; i <= n; i++) {
		div(i);
	}
	bool flg = 0;
	for (int i = 6000; ~i; i--) {
		if (ans[i]) flg = 1;
		if (flg) printf("%d", ans[i]);
	}
	return 0;
}