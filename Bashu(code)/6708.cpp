#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 5001;
const int MAXM = 200001;
struct edge {
	int u, v, w;
	bool operator < (const edge& sec) const {
		return this->w < sec.w;
	}
} edges[MAXM];
class MFS {
	private:
	int fa[MAXN];
	int find_fa(const int a) {
		return this->fa[a] == a ? a : this->fa[a] = this->find_fa(this->fa[a]);
	}
	public:
	MFS() {
		for (int i = 0; i < MAXN; i++) {
			fa[i] = i;
		}
	}
	MFS(const int n) {
		for (int i = 0; i <= n; i++) {
			fa[i] = i;
		}
	}
	void resize(const int n) {
		for (int i = 0; i <= n; i++) {
			fa[i] = i;
		}
	}
	bool merge(const int a, const int b) {
		int x = this->find_fa(a), y = this->find_fa(b);
		if (x == y) return false;
		this->fa[x] = y;
		return true;
	}
};
MFS mfs;
int MST(int n, int m) {
	int sum = 0;
	sort(edges, edges + m);
int cnt = 0;
	for (int i = 0; i < m && cnt < n - 1; i++) {
		if (mfs.merge(edges[i].u, edges[i].v)) {
			cnt++;
			sum += edges[i].w;
		}
	}
	return cnt == n - 1 ? sum : -114514;
}
int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	mfs.resize(n);
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
	}
int WTCL = MST(n, m);
if (WTCL == -114514) printf("orz");
else	printf("%d", WTCL);
	return 0;
}