#include <iostream>
#include <cstdio>
using namespace std;
char op[20];
int c[33000];
int lowbit(int x) {
	return x & (-x);
}
void add(int x, int d) {
	for (int i = x; i <= 33000; i += lowbit(i)) c[i] ^= d;
}
int ask(int x) {
	int ans = 0;
	for (int i = x; i > 0; i -= lowbit(i)) ans ^= c[i];
	return ans;
}
int main() {
	while (~scanf("%s", &op)) {
		if (op[0] == 'A' || op[0] == 'R') {
			int x;
			scanf("%d", &x);
			add(x, x);
		} else {
			int x, y;
			scanf("%s %d %s %d", &op, &x, &op, &y);
			if (x > y) puts("0");
			else printf("%d\n", ask(x - 1) ^ ask(y));
		}
	}
	return 0;
}