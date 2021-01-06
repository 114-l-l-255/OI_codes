#include <cstdio>
#include <algorithm>
using namespace std;
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		int a, b;
		scanf("%d %d", &a, &b);
		if (a < b) printf("0.000000\n");
		else printf("%.6lf\n", 1.0 - b * 1.0 / (a + 1));
	}
	return 0;
}