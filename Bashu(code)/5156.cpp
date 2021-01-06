#include <cstdio>
#include <algorithm>
#include <queue>
#include <unordered_map> 
using namespace std;
const int MAXN = 200001;
unsigned long long a[MAXN];
struct M {
	unsigned long long sum;
	int l, r;
	bool operator < (const M& sec) const {
		return sum < sec.sum;
	}
	bool operator == (const M& sec) const {
		return l == sec.l && r == sec.r;
	}
};
struct cmp {
	size_t operator () (const M& m) const {
		return ((size_t)m.l << 17) + m.r;
	}
};
priority_queue<M> pq;
unordered_map<M, bool, cmp> MP;
int main() {
//	freopen("ksum.in", "r", stdin);
//	freopen("ksum.out", "w", stdout);
	int n, k;
	scanf("%d %d", &n, &k);
	unsigned long long sum = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%llu", &a[i]);
		sum += a[i];
	}
	M tmp;
	tmp.sum = sum;
	tmp.l = 1;
	tmp.r = n;
	pq.push(tmp);
	MP[tmp] = 1;
	for (int i = 1; i <= k; i++) {
		tmp = pq.top();
		printf("%llu ", tmp.sum);
		pq.pop();
		if (tmp.l == tmp.r) continue;
		tmp.sum -= a[tmp.l];
		tmp.l++;
		if (!MP[tmp]) pq.push(tmp), MP[tmp] = 1;
//		printf("in %llu %d %d\n", tmp.sum, tmp.l, tmp.r);
		tmp.sum += a[tmp.l - 1] - a[tmp.r];
		tmp.l--;
		tmp.r--;
		if (!MP[tmp]) pq.push(tmp), MP[tmp] = 1;
//		printf("in %llu %d %d\n", tmp.sum, tmp.l, tmp.r);
	}
	return 0;
}