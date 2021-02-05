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
		T v[MAXN], l, r;
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
};

template<typename T1, typename T2> pair<T1, T2> make_pair(T1 a, T2 b) {
	return pair<T1, T2>(a, b);
}
