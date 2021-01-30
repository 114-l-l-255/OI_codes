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
inline int max(int a, int b) {
	return a > b ? a : b;
}
inline int min(int a, int b) {
	return a < b ? a : b;
}
inline int abs(int x) {
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
