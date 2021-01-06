#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 1001;
const int MAXS = 4010;
struct king {
	int l, r;
} ki[MAXN];
struct Dou {
	int arr[MAXS];
};
bool cmp(king x, king y) {
	return x.l * x.r < y.l * y.r;
}
Dou mul_ans;
void mul(Dou a, int b) {
	for (int i = 0; i < 4001; i++) {
		mul_ans.arr[i] = a.arr[i] * b;
	}
	for (int i = 0; i < 4001; i++) {
		mul_ans.arr[i + 1] += mul_ans.arr[i] / 10;
		mul_ans.arr[i] %= 10;
	}
	return;
}
Dou div_ans;
void div(Dou a, int b) {
	for (int i = 4001; i >= 0; i--) {
		a.arr[i] += a.arr[i + 1] * 10;
		div_ans.arr[i] = a.arr[i] / b;
		a.arr[i] -= a.arr[i] / b * b;
	}
}
bool less(Dou a, Dou b) {
	for (int i = 4000; i >= 0; i--) {
		if (a.arr[i] < b.arr[i]) return 1;
		if (a.arr[i] > b.arr[i]) return 0;
	}
	return 0;
}
int main() {
	Dou one;
	one.arr[0] = 1;
	Dou zero;
	zero.arr[0] = 0;
	for (int i = 1; i < 4001; i++) {
		one.arr[i] = zero.arr[i] = 0;
	}
	int n;
	scanf("%d", &n);
	for (int i = 0; i <= n; i++) {
		scanf("%d %d", &ki[i].l, &ki[i].r);
	}
	stable_sort(ki + 1, ki + n + 1, cmp);
	mul(one, ki[0].l);
	Dou mul_ = mul_ans;
	Dou ans = zero;
	for (int i = 1; i <= n; i++) {
		div(mul_, ki[i].r);
		if (less(ans, div_ans)) {
			ans = div_ans;
		}
		mul(mul_, ki[i].l);
		mul_ = mul_ans;
	}
	int flag = 0;
	for (int i = 4000; i >= 0; i--) {
		if (ans.arr[i]) flag = 1;
		if (flag or i == 0) printf("%d", ans.arr[i]);
	}
	return 0;
}