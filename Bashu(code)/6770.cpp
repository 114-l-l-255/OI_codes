#include <cstdio>
const int MAXN = 1000005;
int son[MAXN][26], flag[MAXN], fail[MAXN], cnt;
char str[MAXN];
class Query {
	private:
		int q[MAXN];
		int l, r;
	public:
		Query() {
			l = 0, r = -1;
		}
		void push(int x) {
			q[++r] = x;
		}
		int front() {
			return q[l];
		}
		void pop() {
			l++;
		}
		void clear() {
			l = 0, r = -1;
		}
		bool empty() {
			return l > r;
		}
		int size() {
			return r - l + 1; 
		}
};
int strlen(char* s) {
	for (int i = 0; ; i++) if (s[i] == 0) return i;
}
template<typename T> void memset(T* s) {
	for (int i = 0; i < sizeof(s) / sizeof(T); i++) s[i] = 0;
}
void insert(char* s) {
	int n = strlen(s);
	int root = 1;
	for (int i = 0; i < n; i++) {
		if (son[root][s[i] - 'a'] == 0) son[root][s[i] - 'a'] = ++cnt;
		root = son[root][s[i] - 'a'];
	}
	flag[root]++;
}
Query Q;
void Getfail() {
//	printf("test\n");
	for (int i = 0; i < 26; i++) {
		son[0][i] = 1;
	}
	Q.push(1);
	while (!Q.empty()) {
		int u = Q.front();
//		printf("%d\n", u);
		Q.pop();
		int Fail = fail[u];
		for (int i = 0; i < 26; i++) {
			if (son[u][i] == 0) {
				son[u][i] = son[Fail][i];
			}
			else {
				fail[son[u][i]] = son[Fail][i];
				Q.push(son[u][i]);
			}
		}
	}
}
int Ask(char* s) {
	int n = strlen(s);
	int ans = 0, root = 1;
	for (int i = 0; i < n; i++) {
		int tp = son[root][s[i] - 'a'];
		while (tp > 1 && flag[tp] != -1) {
			ans += flag[tp];
			flag[tp] = -1;
			tp = fail[tp];
		}
		root = son[root][s[i] - 'a'];
	}
	return ans;
}
int main() {
	cnt = 1;
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		memset(str);
		scanf("%s", str);
		insert(str);
//	printf("test\n");
	}
//	printf("123test\n");
	Getfail();
//	printf("test\n");
	memset(str);
	scanf("%s", str);
	printf("%d", Ask(str));
	return 0;
}