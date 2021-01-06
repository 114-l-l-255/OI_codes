#include <cstdio>
const int MAXL = 1000001;
int n;
char a[MAXL], b[MAXL];
int strlen(char *a) {
	for (int i = 0; ; i++) if (a[i] == 0) return i;
}
inline int qkmod(int x) {
    return x >= n ? x - n : x;
}
int main() {
	scanf("%s %s", a, b);
	n = strlen(a);
	int i, j, k;
	int s1, s2;
    for (i = 0, j = 1, k = 0; i < n && j < n && k < n; ) {
    	int ii = qkmod(i + k), jj = qkmod(j + k);
        if (a[ii] == a[jj]) {
            k++;
        }
        else {
            a[ii] > a[jj] ? i += k + 1 : j += k + 1;
            if (i == j) i++;
            k = 0;
        }
    }
    s1 = i > j ? j : i;
    for (i = 0, j = 1, k = 0; i < n && j < n && k < n; ) {
    	int ii = qkmod(i + k), jj = qkmod(j + k);
        if (b[ii] == b[jj]) {
            k++;
        }
        else {
            b[ii] > b[jj] ? i += k + 1 : j += k + 1;
            if (i == j) i++;
            k = 0;
        }
    }
    s2 = i > j ? j : i;
    for (i = 0; i < n; i++) {
        if (a[qkmod(s1 + i)] != b[qkmod(s2 + i)]) {
        	puts("No");
        	return 0;
		}
    }
    puts("Yes");
    for (i = 0; i < n; i++) {
        putchar(a[qkmod(s1 + i)]);
    }
    return 0;
}