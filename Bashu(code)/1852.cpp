#include <cstdio>
#include <algorithm>
#include <string>
#include <iostream>
#define NDEBUG
#include <assert.h>
using namespace std;
int son[10485760/2-400000][27], tot;
string str;
long long ans = 0;
int main() {
	tot = 1;
	int n;
	scanf("%d", &n);
	scanf("\n");
	scanf("\r");
	for (int i = 0; i < n; i++) {
		str.clear();
		getline(cin, str);
		int root = 1;
		for (int j = 0; j < str.size(); j++) {
			son[root][26]++;
			ans = max(ans, (long long)son[root][26] * j);
//			printf("%lld\n", (long long)son[root][26] * j);
			assert(str[j] >= 'A' && str[j] <= 'Z');
			if (son[root][str[j] - 'A'] == 0) son[root][str[j] - 'A'] = ++tot;
			root = son[root][str[j] - 'A'];
		}
		son[root][26]++;
	}
	printf("%lld", ans);
	return 0;
}