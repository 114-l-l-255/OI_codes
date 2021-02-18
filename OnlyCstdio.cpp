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


/***************working***************/


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
