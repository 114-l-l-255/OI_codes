#include <cstdio>
struct Trie {
	int c[10];
	bool have;
	int n;
	int num();
} d[10000000];
int null, cnt, root;
int Trie::num() {
	if (&d[n] == this) return n;
	return n = d[n].num();
}
int newnode() {
	++cnt;
	d[cnt].n = cnt;
	return cnt;
}
void insert(char *s) {
	int t = root;
	for (; *s != '\0'; ++s) {
		if (!d[t].c[*s - '0'])
			d[t].c[*s - '0'] = newnode();
		t = d[d[t].c[*s-'0']].num();
	}
	d[t].have = 1;
}
bool find(char *s) {
	int t = root;
	for (; *s != '\0'; ++s) {
		if (!d[t].c[*s - '0'])
			return 0;
		t = d[d[t].c[*s-'0']].num();
	}
	return d[t].have;
}
int open(char *s) {
	int t = root;
	for (; *s != '\0'; ++s) {
		if (!d[t].c[*s - '0'])
			d[t].c[*s - '0'] = newnode();
		t = d[d[t].c[*s - '0']].num();
	}
	return t;
}
void merge(int t1, int t2) {
	if (t1==t2)
		return;
	d[t1].n=t2;
	d[t2].have|=d[t1].have;
	for (int i = 0; i < 10; ++i) {
		int son1 = d[d[t1].c[i]].num(), son2 = d[d[t2].c[i]].num();
		if (son1) {
			if (!son2)
				d[t2].c[i] = son1;
			else {
				merge(son1, son2);
				t2 = d[t2].num();
			}
		}
	}
}
char str1[8000001], str2[100];
int main() {
	null = 0;
	root = newnode();
	int T;
	scanf("%d", &T);
	while (T--) {
		int op;
		scanf("%d", &op);
		if (op == 1) {
			scanf("%s", str1);
			insert(str1);
		} else if (op == 2) {
			scanf("%s", str1);
			printf("%d\n", find(str1));
		} else {
			scanf("%s %s", str1, str2);
			merge(open(str1), open(str2));
		}
	}
	return 0;
}