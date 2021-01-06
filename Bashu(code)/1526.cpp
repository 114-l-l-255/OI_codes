#include <cstdio>
#include <algorithm>
#include <stdlib.h>
#include <map>
using namespace std;
map<unsigned long long, bool> Ar;
unsigned long long Hash(int *a) {
	unsigned long long ans = 0;
	for (int i = 0; i < 6; i++) {
		ans += a[i];
	}
	for (int i = 0; i < 5; i++) {
		ans += (long long)a[i] * a[i + 1];
	}
	unsigned long long tmp = 1;
	for (int i = 0; i < 6; i++) {
		tmp = tmp * a[i];
	}
	for (int i = 0; i < 4; i++) {
		ans += (long long)a[i] * a[i + 2];
	}
	ans += (long long)a[4] * a[0];
	ans += (long long)a[5] * a[1];
	return ans + ((long long)a[5] * a[0]) + tmp;
}
int main() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		int aaa[6];
		for (int j = 0; j < 6; j++) {
			scanf("%d", &aaa[j]);
		}
		unsigned long long hs = Hash(aaa);
		if (Ar[hs]) {
			// abort();
			puts("Twin snowflakes found.");
			return 0;
		}
		else {
			Ar[hs] = 1;
		}
	}
	puts("No two snowflakes are alike.");
	return 0;
}