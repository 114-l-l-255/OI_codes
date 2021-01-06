#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
queue<int> q[3];
int a[7000001];
char gc() {
	static char buf[1<<20], *S, *T;
	if (T == S) {
		T = (S = buf) + fread(buf, 1, 1 << 20, stdin);
		if (T == S) return EOF;
	}
	return *S++;
}
//#define getchar gc
inline int re() {
	char c;
	int w = 1;
	while ((c = getchar()) < '0' || c > '9') if (c == '-') w = -1;
	int res = c - '0';
	while ((c = getchar()) >= '0' && c <= '9') res = res * 10 + c - '0';
	return res * w;
}
const int Mxdt = (1<<20);
inline char pc(char ch,bool bj) {
	static char buf[Mxdt],*p1=buf,*p2=buf+Mxdt;
	return ((bj)||(*p1++=ch)&&p1==p2)&&fwrite(p1=buf,1,p1-buf,stdout),0;
}
void print(int x) {
	if(x>9)print(x/10);
	pc(x%10^48,false);
}
inline void printnum(int x,int ch) {
	if(x < 0)pc('-',false),x=-x;
	print(x),pc(ch,false);
}
int main() {
	int n = re(), m = re(), qg = re(), u = re(), v = re(), t = re();
	double p = u * 1.0 / v;
	for (int i = 1; i <= n; i++) {
		a[i] = re();
	}
	sort(a + 1, a + n + 1);
	for (int i = n; i >= 1; i--) {
		q[0].push(a[i]);
	}
	int sig = 0;
	for (int SHIK = 1; SHIK <= m; SHIK++) {
		int u = -2147483647, shik;
		for (int i = 0; i < 3; i++) {
			if (!q[i].empty() && q[i].front() > u) u = q[i].front(), shik = i;
		}
		q[shik].pop();
		u += sig;
		sig += qg;
		q[1].push(int(p * u) - sig);
		q[2].push(u - int(p * u) - sig);
		if (SHIK % t == 0) {
			printnum(u, ' ');
		}
	}
	pc('\n', 0);
	for (int i = 1; i <= n + m; i++) {
		int u = -2147483647, shik;
		for (int is = 0; is < 3; is++) {
			if (!q[is].empty() && q[is].front() > u) u = q[is].front(), shik = is;
		}
		q[shik].pop();
		if (i % t == 0) {
			printnum(u + sig, ' ');
		}
	}
	return pc('♂', 1);
}