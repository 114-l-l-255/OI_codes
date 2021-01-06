#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
const int MAXN = 1001;
using namespace std;
double lx[MAXN], ly[MAXN], rx[MAXN], ry[MAXN];
double S;
int N;
void cover(double x1, double y1, double x2, double y2, int h) {
	if (x1 == x2 || y1 == y2) return;
	if (h > N) S += (y2 - y1) * (x2 - x1);
	else {
		if (y1 < ly[h]) cover(min(rx[h], x1), y1, min(rx[h], x2), min(ly[h], y2), h + 1);
		if (x2 > rx[h]) cover(max(rx[h], x1), min(ry[h], y1), x2, min(ry[h], y2), h + 1);
		if (y2 > ry[h]) cover(max(lx[h], x1), max(ry[h], y1), max(lx[h], x2), y2, h + 1);
		if (x1 < lx[h]) cover(x1, max(ly[h], y1), min(lx[h], x2), max(ly[h], y2), h + 1);
	}
}
int main() {
	int QwQ = 1;
	while (1) {
		scanf("%d", &N);
		if (N == 0) break;
		for (int i = 1; i <= N; i++) {
			scanf("%lf %lf %lf %lf", &lx[i], &ly[i], &rx[i], &ry[i]);
		}
		S = (rx[N] - lx[N]) * (ry[N] - ly[N]);
		for (int i = N - 1; i >= 1; i--) cover(lx[i], ly[i], rx[i], ry[i], i + 1);
		printf("Test case #%d\nTotal explored area: %.2lf\n\n", QwQ, S);
		QwQ++;
	}
	return 0;
}