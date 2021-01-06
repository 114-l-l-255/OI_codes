#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int son[100001][26];
int tot = 1;
void add(char* str) {
	int len = strlen(str);
	int pos = 1;
	for (int i = 0; i < strlen(str); i++) {
		int tmp = str[i] - 'a';
		if (!son[pos][tmp]) son[pos][tmp] = ++tot;
		pos = son[pos][tmp];
	}
}
char str[100001];
bool dp[100001][2];
void dfs(int x) {
	dp[x][0] = 0;
	dp[x][1] = 0;
	bool flag = 0;
	for (int i = 0; i < 26; i++) {
		if (son[x][i]) {
			flag = 1;
			dfs(son[x][i]);
			if (dp[son[x][i]][0] == 0) dp[x][0] = 1;
			if (dp[son[x][i]][1] == 0) dp[x][1] = 1;
		}
	}
	dp[x][1] = flag ? dp[x][1] : 1;
}
void read(char* str) {
	char ch;
	int tmp = 0;
	ch = getchar();
	while (ch < 'a' || ch > 'z') ch = getchar();
	while (ch >= 'a' && ch <= 'z') {
		str[tmp++] = ch;
		ch = getchar();
	}
	str[tmp] = '\0';
}
int main() {
	int n, k;
	while (~scanf("%d %d", &n, &k)) {
		tot = 1;
		for (int i = 0; i < 100001; i++) {
			son[i][0] = 0; son[i][1] = 0; son[i][2] = 0; son[i][3] = 0; son[i][4] = 0; son[i][5] = 0; son[i][6] = 0; son[i][7] = 0; son[i][8] = 0; son[i][9] = 0; son[i][10] = 0; son[i][11] = 0; son[i][12] = 0; son[i][13] = 0; son[i][14] = 0; son[i][15] = 0; son[i][16] = 0; son[i][17] = 0; son[i][18] = 0; son[i][19] = 0; son[i][20] = 0; son[i][21] = 0; son[i][22] = 0; son[i][23] = 0; son[i][24] = 0; son[i][25] = 0;
		}
		for (int i = 0; i < n; i++) {
			read(str);
//			printf("%s\n", str);
			add(str);
		}
		dfs(1);
		if (dp[1][0]) {
			if (dp[1][1]) {
				printf("HY wins!\n");
			}
			else {
				printf("%s\n", (k & 1) ? "HY wins!" : "Teacher wins!");
			}
		}
		else {
			printf("Teacher wins!\n");
		}
	}
	return 0;
}