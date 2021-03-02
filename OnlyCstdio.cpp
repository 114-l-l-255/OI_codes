#include <cstdio>

template<typename T> void sort(T *l, T *r) {
	if (l == r - 1) return;
	int mid = (r - l) >> 1;
	sort(l, l + mid);
	sort(l + mid, r);
	T *ll = l, *rr = l + mid;
	T tmp[r - l];
	T *lr = tmp;
	while (ll != l + mid && rr != r) {
		if ((*ll) < (*rr)) {
			*(lr++) = *(ll++);
		}
		else {
			*(lr++) = *(rr++);
		}
	}
	while (ll != l + mid) {
		*(lr++) = *(ll++);
	}
	while (rr != r) {
		*(lr++) = *(rr++);
	}
	for (T *i = l, *j = tmp; i != r; i++, j++) {
		*i = *j;
	}
}

template<typename T> inline T max(T a, T b) {
	return a > b ? a : b;
}

template<typename T> inline T min(T a, T b) {
	return a < b ? a : b;
}

template<typename T> inline T abs(T x) {
	return x < 0 ? -x : x;
}

template<typename T> void swap(T& a, T& b) {
	T t = a;
	a = b;
	b = t;
}

template<typename T> inline void memset(T* s, int sss, int ss) {
	T c = 0;
	for (int i = 0; i < sizeof(T); i++) {
		c *= 128;
		c += sss;
	}
	int cc = ss / sizeof(T);
	for (int i = 0; i < cc; i++) {
		s[i] = c;
	}
}

template<typename T> void reverse(T* a, T* b) {
	b--;
	while (1) {
		swap(*a, *b);
		a++;
		if (a == b) return;
		b--;
		if (a == b) return;
	}
}

template<typename T> inline int strlen(T* s) {
	for (int i = 0; ; i++) {
		if (s[i] == 0) return i;
	}
}

template<typename T> inline void memcpy(T* x, T* s, int siv) {
	int ss = siv / sizeof(T);
	for (int i = 0; i < ss; i++) {
		x[i] = s[i];
	}
}

template<typename T> inline void discretization(T* l, T* r) {
	struct dis {
		T val;
		int id;
		bool operator < (const dis sec) const {
			return val < sec.val;
		}
	} dis[r - l];
	for (T* i = l; i != r; i++) {
		dis[i - l].val = *i;
		dis[i - l].id = i - l;
	}
	sort(dis, dis + (r - l));
	int muti = 0;
	for (T* i = l; i != r; i++) {
		if (i != l && dis[i - l].val == dis[(i - l) - 1].val) {
			muti++;
		}
		*i = dis[i - l].id - muti;
	}
}

template<typename T> class priority_queue {
	private:
		T v[MAXN], n;
		void pushup(int i) {
			T tmp = v[i];
			while (tmp < v[i >> 1]) {
				v[i] = v[i >> 1];
				i >>= 1;
			}
			v[i] = tmp;
		}
		void pushdown(int i) {
			T tmp = v[i];
			while ((i << 1) <= n) {
				int ch = i << 1;
				if (ch < n && v[ch + 1] < v[ch]) {
					ch++;
				}
				if (tmp > v[ch]) {
					v[i] = v[ch];
					i = ch;
				}
				else break;
			}
			v[i] = tmp;
		}
	public:
		priority_queue() {
			v[0] = -0x3f3f3f3f;
			n = 0;
		}
		void clear() {
			v[0] = -0x3f3f3f3f;
			n = 0;
		}
		void push(T x) {
			v[++n] = x;
			pushup(n);
		}
		void pop() {
			swap(v[1], v[n--]);
			pushdown(1);
		} 
		T top() {
			return v[1];
		}
		bool empty() {
			return n == 0;
		}
};

const int mod = 114515;
template<typename T1, typename T2> class hashset {
	//T1只支持'int'!
	private:
		struct _slink {
			_slink *nxt;
			T2 val;
			int As;
		};
		_slink *h[mod];
	public:
		hashset() {
			for (int i = 0; i < mod; i++) h[i] = NULL;
		}
		void clear() {
			for (int i = 0; i < mod; i++) h[i] = NULL;
		}
		void change(int x, T2 id) {
			int now = x % mod;
			if (now < 0) now += mod;
			for (_slink *i = h[now]; i != NULL; i = i->nxt)
				if (i->val == x) {
					i->As = id;
					return;
				}
			_slink *p = new _slink;
			p->nxt = h[now];
			h[now] = p;
			p->val = x;
			p->As = id;
			return;
		}
		T2 find(int x) {
			int now = x % mod;
			if (now < 0) now += mod;
			for (_slink *i = h[now]; i != NULL; i = i->nxt)
				if (i->val == x) return i->As;
			return 0;
		}
		void copy(hashset<T1, T2> sec) {
			//sec -> this
			for (int ii = 0; ii < mod; ii++) {
				for (_slink *i = sec.h[ii]; i != NULL; i = i->nxt) {
					_slink *p = new _slink;
					p->nxt = h[ii];
					h[ii] = p;
					p->val = i->val;
					p->As = i->As;
				}
			}
		}
};

template<typename T> class queue {
	private:
		T v[MAXN];
		int l, r;
	public:
		queue() {
			l = 0, r = -1;
		} 
		void clear() {
			l = 0, r = -1;
		}
		void push(T x) {
			v[++r] = x;
		} 
		void pop() {
			l++;
		}
		T front() {
			return v[l];
		}
		T back() {
			return v[r];
		}
		int size() {
			return r - l + 1; 
		}
		bool empty() {
			return r < l;
		}
};


template<typename T1, typename T2> class pair {
	public:
		T1 first; T2 second;
		pair() {
			first = 0;
			second = 0;
		}
		pair(T1 a, T2 b) {
			first = a;
			second = b;
		}
		bool operator < (pair<T1, T2> sec) {
			return first == sec.first ? second < sec.second : first < sec.first;
		}
		pair<T1, T2> operator = (pair<T1, T2> sec) {
			first = sec.first;
			second = sec.second;
			return *this;
		}
		pair<T1, T2> operator = (int sec) {
			first = sec;
			second = sec;
			return *this;
		}
};

template<typename T1, typename T2> pair<T1, T2> make_pair(T1 a, T2 b) {
	return pair<T1, T2>(a, b);
}


template<int siz> struct ZAlgorithm {
	int Z[siz];
	char str[siz];
	void main() {
		Z[0] = 0;
		int l = 0, r = 0;
		for (int i = 1; i < siz; i++) {
			if (i <= r && Z[i - l] < r - i + 1) {
				Z[i] = Z[i - l];
			}
			else {
				Z[i] = max(0, r - i + 1);
				while (i + Z[i] < siz && str[Z[i]] == str[Z[i] + i]) Z[i]++;
				if (i + Z[i] - 1 > r) l = i, r = i + Z[i] - 1;
			}
		}
	}
};

template<int memory> class bitset {
	public:
		unsigned long long mem[(memory + 0x3f) >> 6];
		int realsize;
		void set_(int block, int val) {
			mem[block >> 6] &= (0xffffffffffffffffull ^ (1ull << (block & 0x3f)));
			mem[block >> 6] |= (unsigned long long)val << (block & 0x3f);
		}
		int get_(int block) {
			return (int)((bool)(mem[block >> 6] & (1ull << (block & 0x3f))));
		}
	public:
		void init_val(unsigned long long val) {
			realsize = (memory + 0x3f) >> 6;
			for (int i = 0; i < realsize; i++) {
				mem[i] = 0ull;
			}
			int iter = 0;
			while (val && iter < memory) {
				set_(iter, val & 1);
				val >>= 1;
				++iter;
			}
		} 
		bitset() {
			init_val(0ull);
		} 
		bitset(unsigned long long val) {
			init_val(val);
		}
		bitset(char* str) {
			realsize = (memory + 0x3f) >> 6;
			for (int i = 0; i < realsize; i++) {
				mem[i] = 0ull;
			}
			int len = strlen(str);
			int iter = 0;
			while (iter < memory && len) {
				--len;
				set_(iter, str[len] - '0');
				++iter;
			} 
		}
		unsigned long long to_ullong() {
			unsigned long long ret = 0;
			if (memory < 0x40) {
				ret = mem[0] & ((1ull << memory) - 1);
				return ret;
			}
			for (int i = 0 < realsize ? 0 : realsize; ~i; --i) {
				ret = (ret << 6) + mem[i];
			}
			for (int i = 1; i < realsize; ++i) {
				if (mem[i]) {
					printf("%llu %d\n", mem[i], i);
					char end[] = "\
terminate called after throwing an instance of \'std::overflow_error\'\n\
  what():  _Base_bitset::_M_do_to_ullong\n\
\n\
This application has requested the Runtime to terminate it in an unusual way.\n\
Please contact yinjun2024 for more information.";
					printf("%s", end);
					int k[1]; 
					k[1145141919] = 810;
				}
			}
			return ret;
		}
		unsigned long to_ulong() {
			return (unsigned long)(to_ullong());
		}
		int operator [] (int index) {
			return get_(index);
		}
		bool operator == (bitset<memory> sec) {
			for (int i = 0; i < realsize; i++) {
				if (mem[i] != sec.mem[i]) return 0;
			}
			return 1;
		}
		bool operator != (bitset<memory> sec) {
			return !((*this) == sec);
		}
		bitset<memory> operator ~ (void) {
			bitset<memory> ans;
			for (int i = 0; i < realsize - 1; i++) {
				ans.mem[i] = ~mem[i];
			}
			if (memory == (realsize - 1) << 6) return ans;
			int ind = ((1ull << (memory - (realsize - 1 << 6))) - 1);
			ans.mem[realsize - 1] = mem[realsize - 1] ^ ind;
			return ans;
		}
		bitset<memory> operator << (unsigned long long x) {
			bitset<memory> ans;
			int a = x >> 6, b = x & 0x3f;
			for (int i = 0; ; i++) {
				if (realsize - a - 2 < i) break;
				ans.mem[i + a] |= mem[i] << b;
				if (realsize - a - 2 <= i) break;
				if (b != 0) ans.mem[i + a + 1] |= mem[i] >> (0x40 - b);
			}
			if ((memory & 0x3f) <= b) {
				unsigned long long tmp;
				if (realsize - a - 2 >= 0 && b != 0) {
					tmp = mem[realsize - a - 2] >> (0x40 - b);
					tmp = tmp & (1ull << (memory & 0x3f));
					ans.mem[realsize - 1] |= tmp;
				}
			}
			else {
				unsigned long long tmp;
				if (realsize - a - 2 >= 0 && b != 0) {
					tmp = mem[realsize - a - 2] >> (0x40 - b);
					ans.mem[realsize - 1] |= tmp;
				}
				tmp = mem[realsize - a - 1] & (1ull << (memory & 0x3f - b));
				tmp = tmp << b;
				ans.mem[realsize - 1] |= tmp;
			}
			return ans;
		}
		void set(int a, int b = 1) {
			set_(a, b);
		}
};
template<int memory> bitset<memory> operator ^ (bitset<memory> fst, bitset<memory> sec) {
	bitset<memory> s;
	s = fst;
	s ^= sec;
	return s;
}
template<int memory> void operator ^= (bitset<memory> &fst, bitset<memory> sec) {
	for (int i = 0; i < fst.realsize; i++) {
		fst.mem[i] ^= sec.mem[i];
	}
}
template<int memory> bitset<memory> operator & (bitset<memory> fst, bitset<memory> sec) {
	bitset<memory> s;
	s = fst;
	s &= sec;
	return s;
}
template<int memory> void operator &= (bitset<memory> &fst, bitset<memory> sec) {
	for (int i = 0; i < fst.realsize; i++) {
		fst.mem[i] &= sec.mem[i];
	}
}
template<int memory> bitset<memory> operator | (bitset<memory> fst, bitset<memory> sec) {
	bitset<memory> s;
	s = fst;
	s |= sec;
	return s;
}
template<int memory> void operator |= (bitset<memory> &fst, bitset<memory> sec) {
	for (int i = 0; i < fst.realsize; i++) {
		fst.mem[i] |= sec.mem[i];
	}
}

void srand(unsigned long long x) {
	rnd[0] = x;
	for (int i = 0; i < (x & 0xff) + 100; i++) {
		unsigned long long r = rnd[0] + rnd[1] + rnd[2] + rnd[0] * rnd[2] + 114514;
		rnd[2] = rnd[1];
		rnd[1] = rnd[0];
		rnd[0] = r;
	}
}
unsigned long long rand() {
	unsigned long long r = rnd[0] + rnd[1] + rnd[2] + rnd[0] * rnd[2] + 114514;
	rnd[2] = rnd[1];
	rnd[1] = rnd[0];
	rnd[0] = r;
	return rnd[0];
}

class fhqTreap {
	struct TreeNode {
		int sz, val, pty, l, r;
	} Node[MAXN];
	int stack[MAXN], tp, cnt, root;
	int Newnode(int val) {
		int now = tp ? stack[tp--] : ++cnt;
		Node[now].sz = 1;
		Node[now].val = val;
		Node[now].pty = (int)(rand() & 0x7fffffff);
		return now;
	}
	void pushup(int u) {
		Node[u].sz = Node[Node[u].l].sz + Node[Node[u].r].sz + 1;
	}
	void Split(int u, int &l, int &r, int val) {
		if (u == 0) {
			l = 0;
			r = 0;
			return;
		}
		if (Node[u].val <= val) {
			l = u;
			Split(Node[l].r, Node[l].r, r, val);
		}
		else {
			r = u;
			Split(Node[r].l, l, Node[r].l, val);
		}
		pushup(u);
	}
	void Split_sz(int u, int &l, int &r, int sz) {
		if (u == 0) {
			l = 0;
			r = 0;
			return;
		}
		if (Node[Node[u].l].sz + 1 <= sz) {
			l = u;
			Split_sz(Node[u].r, Node[u].r, r, sz - Node[Node[u].l].sz - 1);
		}
		else {
			r = u;
			Split_sz(Node[u].l, l, Node[u].l, sz);
		}
		pushup(u);
	}
	void Merge(int &u, int l, int r) {
		if (l == 0 || r == 0) {
			u = l | r;
			return;
		}
		if (Node[l].pty > Node[r].pty) {
			u = l;
			Merge(Node[u].r, Node[u].r, r);
		}
		else {
			u = r;
			Merge(Node[u].l, l, Node[u].l);
		}
		pushup(u);
	}
	int Find(int u, int val) {
		if (u == 0) return 0;
		if (Node[u].val == val) return u;
		if (Node[u].val > val) return Find(Node[u].l, val);
		else return Find(Node[u].r, val);
	}
	void Insert(int val) {
		int l, r;
		Split(root, l, r, val);
		Merge(l, l, Newnode(val));
		Merge(root, l, r);
	}
	void Delete(int val) {
		int a, b;
		Split(root, root, a, val);
		Split(root, root, b, val - 1);
		Merge(b, Node[b].l, Node[b].r);
		Merge(root, root, b);
		Merge(root, root, a);
	}
	int Rank(int val) {
		int x, y;
		Split(root, x, y, val - 1);
		int res = Node[x].sz + 1;
		Merge(root, x, y);
		return res;
	}
	int Kth(int k) {
		int rt = root;
		while (1) {
			if (k <= Node[Node[rt].l].sz) rt = Node[rt].l;
			else if (k == Node[Node[rt].l].sz + 1) return Node[rt].val;
			else k -= Node[Node[rt].l].sz + 1, rt = Node[rt].r;
		}
	}
	int Pre(int val) {
		int x, y;
		Split(root, x, y, val - 1);
		int tmp = x;
		while (Node[tmp].r) tmp = Node[tmp].r;
		int ans = Node[tmp].val;
		Merge(root, x, y);
		return ans;
	}
	int Nxt(int val) {
		int x, y;
		Split(root, x, y, val);
		int tmp = y;
		while (Node[tmp].l) tmp = Node[tmp].l;
		int ans = Node[tmp].val;
		Merge(root, x, y);
		return ans;
	}
};

class Splay {
	public:
		struct TreeNode {
			int val, num, sz, son[2], fa;
			int sss;
			bool r;
		} Node[MAXN];
		int root, tot;
		bool nroot(int x) {return Node[Node[x].fa].son[1] == x || Node[Node[x].fa].son[0] == x;}
		bool get(int x) {
			return x == Node[Node[x].fa].son[1];
		}
		void clear(int x) {
			Node[x].son[0] = Node[x].son[1] = Node[x].fa = Node[x].val = Node[x].sz = Node[x].num = 0;
		}
		void pushup(int x) {
			Node[x].sz = Node[Node[x].son[0]].sz + Node[Node[x].son[1]].sz + Node[x].num;
			Node[x].sss = Node[Node[x].son[0]].sss ^ Node[Node[x].son[1]].sss ^ Node[x].val;
		}
		void pushdown(int x) {
			if (Node[x].r) {
				if (Node[x].son[0]) Node[Node[x].son[0]].son[0] ^= Node[Node[x].son[0]].son[1] ^= Node[Node[x].son[0]].son[0] ^= Node[Node[x].son[0]].son[1], Node[Node[x].son[0]].r ^= 1;
				if (Node[x].son[1]) Node[Node[x].son[1]].son[0] ^= Node[Node[x].son[1]].son[1] ^= Node[Node[x].son[1]].son[0] ^= Node[Node[x].son[1]].son[1], Node[Node[x].son[1]].r ^= 1;
				Node[x].r = 0;
			}
		}
		void Rotate(int x) {
			int y = Node[x].fa, z = Node[y].fa, son = get(x),nry = nroot(y);
			Node[y].son[son] = Node[x].son[son ^ 1];
			if (Node[x].son[son ^ 1]) Node[Node[x].son[son ^ 1]].fa = y;
			Node[x].son[son ^ 1] = y;
			Node[y].fa = x;
			Node[x].fa = z;
			if (nry) Node[z].son[y == Node[z].son[1]] = x;
			pushup(y);
			pushup(x);
		}
		void splay(int x, int fa = 0) {
			pushall(x);
			while (nroot(x)) {
				int f = Node[x].fa;
				if (nroot(f)) get(f) == get(x) ? Rotate(f) : Rotate(x);
				Rotate(x);
			}
		}
		void pushall(int x) {
			if (nroot(x)) pushall(Node[x].fa);
			pushdown(x);
		}
	public:
		void Insert(int val) {
			if (!root) {
				Node[++tot].val = val;
				Node[tot].num = 1;
				root = tot;
				pushup(root);
				return;
			}
			int cur = root, f = 0;
			while (1) {
				if (Node[cur].val == val) {
					Node[cur].num++;
					pushup(cur);
					pushup(f);
					splay(cur);
					break;
				}
				f = cur;
				cur = Node[cur].son[Node[cur].val < val];
				if (!cur) {
					Node[++tot].val = val;
					Node[tot].num = 1;
					Node[tot].fa = f;
					Node[f].son[Node[f].val < val] = tot;
					pushup(tot);
					pushup(f);
					splay(tot);
					break;
				}
			}
		}
		void Delete(int val) {
			Rank(val);
			if (Node[root].num > 1) {
				Node[root].num--;
				pushup(root);
				return;
			}
			if (!Node[root].son[0] && !Node[root].son[1]) {
				clear(root);
				root = 0;
				return;
			}
			if (!Node[root].son[0] || !Node[root].son[1]) {
				int cur = root, chk = !Node[root].son[1] ? 0 : 1;
				root = Node[root].son[chk];
				Node[root].fa = 0;
				clear(cur);
				return;
			}
			int cur = root, x = Pre();
			Node[Node[cur].son[1]].fa = x;
			Node[x].son[1] = Node[cur].son[1];
			clear(cur);
			pushup(root);
		}
		int Rank(int val) {
			int res = 0, cur = root;
			while (1) {
				if (val < Node[cur].val) cur = Node[cur].son[0];
				else {
					res += Node[Node[cur].son[0]].sz;
					if (val == Node[cur].val) {
						splay(cur);
						return res + 1;
					}
					res += Node[cur].num;
					cur = Node[cur].son[1];
				}
			}
		}
		int Kth(int k) {
			int cur = root;
			while (1) {
				if (Node[cur].son[0] && k <= Node[Node[cur].son[0]].sz) {
					cur = Node[cur].son[0];
				} else {
					k -= Node[cur].num + Node[Node[cur].son[0]].sz;
					if (k <= 0) {
						splay(cur);
						return Node[cur].val;
					}
					cur = Node[cur].son[1];
				}
			}
		}
		int Pre() {
			int cur = Node[root].son[0];
			while (Node[cur].son[1]) cur = Node[cur].son[1];
			splay(cur);
			return cur;
		}
		int Pre_(int x) {
			Insert(x);
			int cur = Pre();
			Delete(x);
			return Node[cur].val;
		}
		int Nxt() {
			int cur = Node[root].son[1];
			while (Node[cur].son[0]) cur = Node[cur].son[0];
			splay(cur);
			return cur;
		}
		int Nxt_(int x) {
			Insert(x);
			int cur = Nxt();
			Delete(x);
			return Node[cur].val;
		}
		Splay() {
			for (int i = 0; i < MAXN; i++) {
				Node[i].num = 1;
			}
		}
		int Access(int x) {
			int p;
			for (p = 0; x; x = Node[p = x].fa) {
				splay(x);
				Node[x].son[1] = p;
				pushup(x);
			}
			return p;
		}
		void makeroot(int x) {
			Access(x);
			splay(x);
			Node[x].son[0] ^= Node[x].son[1] ^= Node[x].son[0] ^= Node[x].son[1], Node[x].r ^= 1;
		}
		int findroot(int x) {
			Access(x);
			splay(x);
			while (Node[x].son[0]) pushdown(x), x = Node[x].son[0];
			splay(x);
			return x;
		}
		void split(int x, int y) {
			makeroot(x);
			Access(y);
			splay(y);
		}
		void link(int x, int y) {
			makeroot(x);
			if (findroot(y) != x) Node[x].fa = y;
		}
		void cut(int x, int y) {
			makeroot(x);
			if (findroot(y) == x && Node[y].fa == x && Node[y].son[0] == 0) {
				Node[y].fa = Node[x].son[1] = 0;
				pushup(x);
			}
		}
		void cut_fa(int x) {
			Access(x);
			splay(x);
			Node[x].son[0] = Node[Node[x].son[0]].fa = 0;
		}
		int lca(int u, int v) {
			Access(u);
			return Access(v);
		}
}



template<typename T> inline void memmove(T *fst, T *sec, int size) {
	int len = size / sizeof(T);
	T *tmp = new T[len];
	T *ttmp = tmp;
	for (int i = 0; i < len; i++) {
		*(ttmp++) = *(sec++);
	}
	ttmp = tmp;
	for (int i = 0; i < len; i++) {
		*(fst++) = *(ttmp++);
	}
	delete[] tmp;
}

template<typename T> class vector {
	private:
		T *iter;
		int len, tp;
	public:
		vector() {
			iter = new T;
			len = 1;
		}
		~vector() {
			delete[] iter;
		}
		void pushback(T x) {
			if (tp == len) {
				T *old = iter;
				iter = new T[len << 1];
				memmove(iter, old, len * sizeof(T));
				delete [] old;
				len <<= 1;
			}
			*(iter + (tp++)) = x;
		}
		T operator [] (int index) {
			return *(iter + index);
		}
};
