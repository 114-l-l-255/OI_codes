#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
#include <set>
#include <unordered_map>
using namespace std;
const int MAXM = 10;
struct lunch {
	int a[MAXM];
	bool operator < (const lunch& sec) const {
		for (int i = 0; i < 10; i++) {
			if (a[i] != sec.a[i]) {
				return a[i] < sec.a[i];
			}
		}
		return 0;
	}
	bool operator == (const lunch& sec) const {
		for (int i = 0; i < 10; i++) {
			if (a[i] != sec.a[i]) {
				return 0;
			}
		}
		return 1;
	}
};
struct egegeg {
	size_t operator () (const pair<int, lunch>&aa) const {
		size_t ans = 0;
		for (int i = 0; i <= 10; i++) {
			ans ^= (1ull << (i << 3)) * aa.second.a[i];
		}
		return ans ^ aa.first;
	}
};
set<pair<int, lunch> > pq;
unordered_map<pair<int, lunch>, int, egegeg > M;
vector<int> mon[MAXM];
int main() {
//	freopen("SHIK.txt", "r", stdin);
//	freopen("SHIK1.txt", "w", stdout);
	int n, k;
	scanf("%d %d", &n, &k);
	for (int i = 0; i < n; i++) {
		int K;
		scanf("%d", &K);
		for (int j = 0; j < K; j++) {
			int a;
			scanf("%d", &a);
			mon[i].push_back(a);
		}
		sort(mon[i].begin(), mon[i].end());
	}
	lunch L; int Tmp = 0;
	for (int i = 0; i < n; i++) {
		Tmp += mon[i][0];
	}
	for (int i = 0; i < 10; i++) {
		L.a[i] = 0;
	}
	pq.insert(make_pair(Tmp, L));
	M[make_pair(Tmp, L)] = 1;
	for (int i = 1; i < k; i++) {
		L = (*pq.begin()).second;
		int SUM = (*pq.begin()).first;
//		printf("%d %d %d %d %d %d %d %d %d %d %d\n", SUM, L.a[0], L.a[1], L.a[2], L.a[3], L.a[4], L.a[5], L.a[6], L.a[7], L.a[8], L.a[9]);
		pq.erase(pq.begin());
		for (int j = 0; j < n; j++) {
			if (L.a[j] != (int)mon[j].size() - 1) {
				L.a[j]++;
				SUM += mon[j][L.a[j]] - mon[j][L.a[j] - 1];
				if (M[make_pair(SUM, L)] == 0) {
					pq.insert(make_pair(SUM, L));
					M[make_pair(SUM, L)] = 1;
//		printf("---%d %d %d %d %d %d %d %d %d %d %d\n", SUM, L.a[0], L.a[1], L.a[2], L.a[3], L.a[4], L.a[5], L.a[6], L.a[7], L.a[8], L.a[9]);
				}
				SUM -= mon[j][L.a[j]] - mon[j][L.a[j] - 1];
				L.a[j]--;
			}
		}
	}
	printf("%d", (*pq.begin()).first);
	return 0;
}