#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;
struct node_ {
	int s, t, p;
	bool operator < (const node_& sec) const {
		return this->s < sec.s;
	}
}Node_[300000];
struct node {
	int s, t, p;
	bool operator < (const node& sec) const {
		return this->t < sec.t;
	}
}Node[300000];
multiset<node> S;
int main() {
	int k, n, c;
	scanf("%d %d %d", &k, &n, &c);
	for (int i = 1; i <= k; i++) {
		scanf("%d %d %d", &Node_[i].s, &Node_[i].t, &Node_[i].p); 
	} 
	sort(Node_ + 1, Node_ + 1 + n);
	for (int i = 1; i <= n; i++) {
		Node[i].s = Node_[i].s;
		Node[i].t = Node_[i].t;
		Node[i].p = Node_[i].p;
	}
	int cnt = 0;
	int pos = 1;
//	node tmpnode;
//	tmpnode.t = -0x7fffffff;
//	S.insert(tmpnode);
//	tmpnode.t = 0x7fffffff;
//	S.insert(tmpnode);
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		while (!S.empty() && (*(S.begin())).t <= Node[i].s) {
			S.erase(S.begin());
			cnt--;
		}
		while (cnt < c && Node[i].p) {
			Node[i].p--;
			S.insert(Node[i]);
			ans++;
			cnt++;
		}
		while (Node[i].p) {
			set<node>::iterator it = S.end();
			it--;
			if ((*it).t <= Node[i].t) break;
			S.erase(it);
			S.insert(Node[i]);
			Node[i].p--;
			//替换ans不++ 
		}
	}
	printf("%d", ans);
	return 0; 
}