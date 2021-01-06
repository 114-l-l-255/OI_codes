#include <cstdio>
#include <cstring>
#define NDEBUG
#include <assert.h>
#include <algorithm>
using namespace std;
char str[5000001];
int son[10000001][5], ct;
int main() {
	ct = 1;
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		for (int j = 0; str[j]; j++) str[j] = 0;
		scanf("%s", str);
		int k = strlen(str);
		int root = 1;
		for (int j = 0; j < k; j++) {
			if (son[root][str[j] - 'a'] == 0) son[root][str[j] - 'a'] = ++ct;
			if (son[root][4] == 0) son[root][3] = i - 1, son[root][4] = i;
			else son[root][3] = max(son[root][3], i - son[root][4] - 1), son[root][4] = i;
			root = son[root][str[j] - 'a'];
		}
        if (son[root][4] == 0) son[root][3] = i - 1, son[root][4] = i;
        else son[root][3] = max(son[root][3], i - son[root][4] - 1), son[root][4] = i;
	}
	for (int i = 1; i <= m; i++) {
		for (int j = 0; str[j]; j++) str[j] = 0;
		scanf("%s", str);
		int k = strlen(str);
		int root = 1;
		for (int j = 0; j < k; j++) {
			if (son[root][str[j] - 'a'] == 0) { printf("%d\n", n); goto end; }
			root = son[root][str[j] - 'a'];
		}
		printf("%d\n", max(son[root][3], n - son[root][4]));
		end:;
	}
	return 0;
}