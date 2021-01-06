#include <cstdio>
#define fo(i,a,b) for(int i=a;i<=b;i++)
#define fod(i,a,b) for(int i=a;i>=b;i--)
#define efo(i,q) for(int i=A[q];i;i=B[i][0])
#define min(q,w) ((q)>(w)?(w):(q))
#define max(q,w) ((q)<(w)?(w):(q))
using namespace std;
typedef long long LL;
const int N = 200500;
int read(int &n) {
	char ch = ' ';
	int q = 0, w = 1;
	for(; (ch != '-') && ((ch < '0') || (ch > '9')); ch = getchar());
	if (ch == '-')w=-1,ch=getchar();
	for(; ch>='0' && ch<='9'; ch=getchar())q=q*10+ch-48;
	n=q*w;
	return n;
}
int m,n,ans,mo;
LL jc[N], jcn[N];
int B[2 * N][2], A[N], B0;
int b[N], z[N];
bool BK;
struct qqww {
	int si;
	LL ans;
} a[N];
LL ksm(LL q, int w) {
	LL ans = 1;
	for (q %= mo; w; w >>= 1, q = q * q % mo) if(w & 1) ans = ans * q % mo;
	return ans;
}
void link(int q, int w) {
	b[w]++;
	B[++B0][0] = A[q];
	A[q] = B0, B[B0][1]=w;
}
LL C(int m, int n) {
	return jc[m] * jcn[n] % mo * jcn[m - n] % mo;
}
int dfs(int q) {
	if (z[q]) {
		BK = 1;
		return 0;
	}
	a[q].ans = 1;
	a[q].si = 0;
	z[q] = 1;
	efo(i, q) {
		a[q].si += dfs(B[i][1]);
		if (BK) return 0;
		a[q].ans = a[q].ans * C(a[q].si, a[B[i][1]].si) % mo * a[B[i][1]].ans % mo;
	}
	return ++a[q].si;
}
int main() {
	int q, w, _;
	read(_);
	jc[0] = jcn[0] = 1;
	while (_--) {
		BK = 0;
		read(n), read(m), read(mo);
		fo (i, 1, n + 1) A[i] = b[i] = z[i] = 0, jc[i] = jc[i - 1] * (LL)i % mo;
		jcn[n + 1] = ksm(jc[n + 1], mo - 2);
		fod (i, n, 1) jcn[i] = jcn[i + 1] * (LL)(i + 1) % mo;
		B0 = A[0] = z[0] = 0;
		fo (i, 1, m) read(w), read(q), link(q, w);
		fo (i, 1, n) if (!b[i]) link(0, i);
		dfs(0);
		q = 0;
		fo (i, 1, n) if(z[i]) q++;
		if (q != n) BK = 1;
		if (BK) printf("0\n");
		else printf("%lld\n", a[0].ans);
	}
	return 0;
}