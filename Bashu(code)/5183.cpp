#include <cstdio>
#include <algorithm>
#include <iostream>
#include <iomanip>
using namespace std;
const int MAXN = 10;
double R[MAXN];
char ch;
double solution() {
	ch = getchar();
	double sum = 0.0;
	int type = 0;
	double r = 0.0;
	while (ch != ')') {
//		printf("!");
		if (ch == '(') {
			r = solution();
			if (type == 1) {
				sum += r;
			}
			else if (type == 2) {
				sum += 1.0 / r;
			}
		}
		else if (ch == '-' || ch == '|') {
			int ttype = type;
			type = ch == '-' ? 1 : 2;
			if (ttype == 0) {
				if (type == 1) {
					sum += r;
				}
				else {
					sum += 1.0 / r;
				}
			}
		}
		else if (ch == 'R') {
			int k = getchar() - '0';
			r = R[k];
			if (type == 1) {
				sum += r;
			}
			else if (type == 2) {
				sum += 1.0 / r;
			}
		}
		ch = getchar();
	}
	if (type == 0) return r;
	else return type == 1 ? sum : 1.0 / sum;
}
int main() {
//	freopen("physic.in", "r", stdin);
//	freopen("physic.out", "w", stdout);
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%lf", &R[i]);
	}
//	printf("cows\n");
	do { ch = getchar(); } while (ch != '(');
//	printf("cows\n");
	double ans = solution();
	cout << fixed << setprecision(5) << ans << '\n';
	return 0; 
} 