#include <cstdio>
const int MAXN = 1000001;
char str[MAXN];
unsigned long long h1[MAXN], h2[MAXN];
unsigned long long bs1[MAXN], bs2[MAXN];
bool eq(int l1, int r1, int l2, int r2) {
	unsigned long long h11 = h1[r1] - h1[l1] * bs1[r1 - l1];
	unsigned long long h21 = h1[r2] - h1[l2] * bs1[r2 - l2];
	unsigned long long h12 = h2[r1] - h2[l1] * bs2[r1 - l1];
	unsigned long long h22 = h2[r2] - h2[l2] * bs2[r2 - l2];
	return h11 == h21 && h12 == h22;
}
int strlen_(char *str) {
	for (int i = 0; ; i++) {
		if (str[i] == 0) return i;
	}
}
int main() {
	scanf("%s", str);
	int n = strlen_(str);
	bs1[0] = 1; bs2[0] = 1;
	for (int i = 1; i < n; i++) bs1[i] = bs1[i - 1] * 131;
	for (int i = 1; i < n; i++) bs2[i] = bs2[i - 1] * 13331;
	h1[0] = str[0]; h2[0] = str[0];
	for (int i = 1; i < n; i++) h1[i] = h1[i - 1] * 131 + str[i];
	for (int i = 1; i < n; i++) h2[i] = h2[i - 1] * 13331 + str[i];
	int q;
	scanf("%d", &q);
	for (int i = 0; i < q; i++) {
		int l1, r1, l2, r2;
		scanf("%d %d %d %d", &l1, &r1, &l2, &r2);
		printf("%s\n", eq(l1 - 1, r1 - 1, l2 - 1, r2 - 1) ? "Yes" : "No");
	}
	return 0;
}
/*
1234|56|
1234
123456
1234*100-123456
unsigned long long
*/