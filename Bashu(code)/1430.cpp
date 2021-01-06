#include <cstdio>
#include <string>
#include <iostream>
#include <cstring>
using namespace std;
int trie[300][31], trie_[300], mark[1024*1024*2], tot;
void insert(string T) {
	int len = T.size();
	int root = 0;
	for (int i = 0; i < len; i++) {
		int xxx = T[i] - 'a';
		if (!trie[root][xxx]) {
			trie[root][xxx] = ++tot;
		}
		root = trie[root][xxx];
	}
	trie_[root] = 1;
	return;
}
int dfs(string T) {//now it isn't dfs...
	int ans = 0, pos = 0;
    memset(mark, 0, sizeof(mark));
    for (int j = 0; j <= int(T.size() - 1); j++) {
        int now = T[j] - 'a';
        pos = trie[pos][now];
        if (pos == 0) break;
        if (trie_[pos] == 1) mark[j] = 1;
    }
    for (int i = 0; i <= int(T.size() - 1); i++) {
        if (!mark[i]) continue;
		else ans = i + 1;
        pos = 0;
        for (int j = i + 1; j <= int(T.size() - 1); j++) {
            int now = T[j] - 'a';
            pos = trie[pos][now];
            if (pos == 0) break;
            if (trie_[pos] == 1) mark[j] = 1;
        }
    }
    return ans;
}
int main() {
	string tmp;
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		tmp.clear();
		cin >> tmp;
		insert(tmp);
	}
	for (int i = 0; i < m; i++) {
		tmp.clear();
		cin >> tmp;
		printf("%d\n", dfs(tmp));
	}
	return 0;
}