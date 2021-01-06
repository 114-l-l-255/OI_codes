#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <map>
using namespace std;
const int Maxn = 200005;
inline int read() {
	char c;
	int rec = 0;
	while ((c = getchar()) < '0' || c > '9');
	while (c >= '0' && c <= '9') rec = rec * 10 + c - '0', c = getchar();
	return rec;
}
int n, m;
struct Edge {
	int a, b;
} e[Maxn];
map<pair<int,int>, int> table;
namespace Graph {
	struct Branch {
		int next, to;
	} branch[Maxn << 1];
	int h[Maxn], cnt = 0;
	inline void add(int x, int y) {
		branch[++cnt].to = y;
		branch[cnt].next = h[x];
		h[x] = cnt;
		return;
	}
	int size[Maxn], deep[Maxn];
	int top[Maxn], fa[Maxn], son[Maxn];
	void Dfs1(int v, int pre, int dep) {
		size[v] = 1;
		fa[v] = pre;
		deep[v] = dep;
		for (int i = h[v]; i; i = branch[i].next) {
			int j = branch[i].to;
			if (j == pre) continue;
			Dfs1(j, v, dep + 1);
			size[v] += size[j];
			if (size[son[v]] < size[j]) son[v] = j;
		}
		return;
	}
	void Dfs2(int v, int T) {
		top[v] = T;
		if (son[v]) Dfs2(son[v], T);
		for (int i = h[v]; i; i = branch[i].next) {
			int j = branch[i].to;
			if (j == fa[v] || j == son[v]) continue;
			Dfs2(j, j);
		}
		return;
	}
	inline int Lca(int x,int y) {
		while (top[x] != top[y])
			deep[top[x]] < deep[top[y]] ? y = fa[top[y]] : x = fa[top[x]];
		return deep[x] < deep[y] ? x : y;
	}
	inline int Dist(int x, int y) {
		return deep[x] + deep[y] - (deep[Lca(x, y)] << 1);
	}
}
namespace Lct {
	struct Splay {
		int F, s[2], size, rev;
		inline void NewNode(int fa) {
			F = fa;
			s[0] = s[1] = rev = 0;
			size = 1;
			return;
		}
	} tree[Maxn];
	inline bool Isroot(int v) {
		return tree[tree[v].F].s[0] != v && tree[tree[v].F].s[1] != v;
	}
	inline void Pushup(int v) {
		tree[v].size = tree[tree[v].s[0]].size + 1 + tree[tree[v].s[1]].size;
		return;
	}
	inline void Rev(int v) {
		if (v == 0) return;
		tree[v].rev ^= 1;
		swap(tree[v].s[0], tree[v].s[1]);
		return;
	}
	inline void Pushdown(int v) {
		if (tree[v].rev) {
			Rev(tree[v].s[0]);
			Rev(tree[v].s[1]);
			tree[v].rev = 0;
		}
		return;
	}
	inline void Lazy(int v) {
		if (!Isroot(v)) Lazy(tree[v].F);
		Pushdown(v);
		return;
	}
	inline void Set(int v, int u, int f) {
		tree[v].s[f] = u;
		tree[u].F = v;
		return;
	}
	inline void Rotate(int v) {
		int p = tree[v].F, g = tree[p].F;
		int t1 = (v == tree[p].s[1]), t2 = (p == tree[g].s[1]), S = tree[v].s[!t1];
		if (!Isroot(p)) Set(g, v, t2);
		else tree[v].F = g;
		Set(v, p, !t1);
		Set(p, S, t1);
		Pushup(p);
		return;
	}
	inline void Splay(int v) {
		for (Lazy(v); !Isroot(v); Rotate(v)) {
			int p = tree[v].F, g = tree[p].F;
			if (!Isroot(p)) Rotate((v == tree[p].s[1]) ^ (p == tree[g].s[1]) ? v : p);
		}
		Pushup(v);
		return;
	}
	inline void Access(int v) {
		for (int u = 0; v; u = v, v = tree[v].F) {
			Splay(v);
			tree[v].s[1] = u;
			Pushup(v);
		}
		return;
	}
	inline void Make_Root(int v) {
		Access(v);
		Splay(v);
		Rev(v);
	}
	inline int Kth(int k,int v) {
		Pushdown(v);
		while (tree[tree[v].s[0]].size + 1 != k && v) {
			if (tree[tree[v].s[0]].size + 1 > k) v = tree[v].s[0];
			else k -= tree[tree[v].s[0]].size + 1, v = tree[v].s[1];
			Pushdown(v);
		}
		return v;
	}
	inline pair<int,int> Get_Kth(int v, int k) {
		Access(v);
		Splay(v);
		if (tree[v].size <= k) return make_pair(0, 0);
		int goal = tree[v].size - k;
		int u = Kth(goal,v);
		Splay(u);
		v = tree[u].s[1];
		Pushdown(v);
		while (tree[v].s[0]) v = tree[v].s[0], Pushdown(v);
		if (u > v) swap(u, v);
		return make_pair(u, v);
	}
	inline void Build(int v, int pre) {
		tree[v].NewNode(pre);
		for(int i = Graph::h[v]; i; i = Graph::branch[i].next) {
			int j = Graph::branch[i].to;
			if (j == pre) continue;
			Build(j, v);
		}
		return;
	}
}
namespace Union {
	int fa[Maxn], size[Maxn];
	inline int getfa(int x) {
		while (x != fa[x]) x = fa[x];
		return x;
	}
	struct chain {
		int a, b, len;
	} A[Maxn];
	int top = 0;
	struct node {
		int x, y, a, b, len;
	} S[Maxn];
	inline void reset() {
		for (int i = 1; i <= n; i++)
			fa[i] = i, size[i] = 1;
		for (int i = 1; i <= n; i++)
			A[i].a = A[i].b = i, A[i].len = 0;
		top = 0;
		return;
	}
	inline void Sov(int id) {
		int x = e[id].a, y = e[id].b;
		int fx = getfa(x), fy = getfa(y);
		if (size[fx] > size[fy]) swap(fx, fy);
		fa[fx] = fy;
		size[fy] += size[fx];
		S[++top] = (node) {
			fx, fy, A[fy].a, A[fy].b, A[fy].len
		};
		int a = A[fx].a, b = A[fx].b, c = A[fy].a, d = A[fy].b;
		int maxx = A[fx].len, temp;
		x = a;
		y = b;
		if (maxx < A[fy].len) {
			maxx = A[fy].len;
			x = c;
			y = d;
		}
		temp = Graph::Dist(a,c);
		if (maxx < temp) {
			maxx = temp;
			x = a;
			y = c;
		}
		temp = Graph::Dist(a,d);
		if (maxx < temp) {
			maxx = temp;
			x = a;
			y = d;
		}
		temp = Graph::Dist(b,c);
		if (maxx < temp) {
			maxx = temp;
			x = b;
			y = c;
		}
		temp = Graph::Dist(b,d);
		if (maxx < temp) {
			maxx = temp;
			x = b;
			y = d;
		}
		A[fy].a = x;
		A[fy].b = y;
		A[fy].len = maxx;
		return;
	}
	inline void Undo(int lim) {
		while (top > lim) {
			node temp = S[top--];
			int x = temp.x, y = temp.y;
			fa[x] = x;
			size[y] -= size[x];
			int a = temp.a, b = temp.b, c = temp.len;
			A[y].a = a;
			A[y].b = b;
			A[y].len = c;
		}
		return;
	}
	inline int Ask(int x) {
		int fx = getfa(x);
		int a = A[fx].a, b = A[fx].b;
		int maxx = max(Graph::Dist(x, a), Graph::Dist(x, b));
		return maxx;
	}
}
int qpos[Maxn];
vector<int> broken[Maxn];
namespace Sgt {
	struct Segment_Tree {
		int L, R;
		vector<int> id;
	} tree[Maxn << 2];
	void Build(int v, int L, int R) {
		tree[v].L = L;
		tree[v].R = R;
		if (L == R) return;
		int mid = (L + R) >> 1;
		Build(v << 1, L, mid);
		Build(v << 1 | 1, mid + 1, R);
		return;
	}
	inline void Cover(int v,int L,int R,int x) {
		if (tree[v].L > R || tree[v].R < L) return ;
		if(L<=tree[v].L && tree[v].R <= R) {
			tree[v].id.push_back(x);
			return;
		}
		Cover(v << 1, L, R, x);
		Cover(v << 1 | 1, L, R, x);
		return;
	}
	inline void Sov(int v) {
		int top = Union::top;
		for (int i = 0; i < tree[v].id.size(); ++i)
			Union::Sov(tree[v].id[i]);
		if (tree[v].L == tree[v].R) {
			printf("%d\n", Union::Ask(qpos[tree[v].L]));
			Union::Undo(top);
			return;
		}
		Sov(v << 1);
		Sov(v << 1 | 1);
		Union::Undo(top);
		return;
	}
}
int main() {
	n = read();
	for (int i = 1; i < n; i++) {
		int x = read(), y = read();
		if (x > y) swap(x, y);
		e[i].a = x;
		e[i].b = y;
		Graph::add(x, y);
		Graph::add(y, x);
		table[make_pair(x, y)] = i;
	}
	table[make_pair(0, 0)] = 0;
	Graph::Dfs1(1, 0, 1);
	Graph::Dfs2(1, 1);
	Lct::Build(1, 0);
	m = read();
	int qcnt = 0;
	char ch;
	for (int i = 1; i <= m; i++) {
		while ((ch = getchar()) != 'Q' && ch != 'C');
		if (ch == 'Q') {
			int x = read(), k = read();
			++qcnt;
			qpos[qcnt] = x;
			pair<int, int> temp = Lct::Get_Kth(x, k);
			int id = table[temp];
			if (id == 0) continue;
			else broken[id].push_back(qcnt);
		}
		else {
			int x = read();
			Lct::Make_Root(x);
		}
	}
	Sgt::Build(1, 1, qcnt);
	for (int i = 1; i < n; ++i) {
		int L = 1;
		for (int j = 0; j < broken[i].size(); ++j) {
			Sgt::Cover(1, L, broken[i][j] - 1, i);
			L = broken[i][j] + 1;
		}
		Sgt::Cover(1, L, qcnt, i);
	}
	Union::reset();
	Sgt::Sov(1);
	return 0;
}