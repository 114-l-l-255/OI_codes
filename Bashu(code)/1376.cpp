#include <cstdio>
const int N = 1e5 + 5;
const int INF = 1e9 + 5;
template<typename T> void swap(T& x, T& y) {
	T rmp = x;
	x = y;
	y = rmp;
}
int abs(int k) { return k < 0 ? -k : k; }
struct node {
	int x, y;
	node(int xx = 0, int yy = 0) {
		x = xx;
		y = yy;
	}
	bool operator < (const node &b) const {
		return abs(x) < abs(b.x);
	}
};
node heap[N];
int siz;
void pushup(int x) {
    while (heap[x] < heap[x >> 1]) {
        swap(heap[x], heap[x >> 1]);
        x >>= 1;
    }
}
void go_down(int x) {
    while (1) {
        if ((x << 1) > siz) return;
        node maxx = heap[x << 1];
        if (((x << 1) | 1) <= siz && heap[(x << 1) | 1] < heap[x << 1]) {
            if (heap[(x << 1) | 1] < heap[x]) {
                swap(heap[x], heap[(x << 1) | 1]);
                x = ((x << 1) | 1);
            }
            else return;
        }
        else {
            if (heap[x << 1] < heap[x]) {
                swap(heap[x << 1], heap[x]);
                x = (x << 1);
            }
            else return;
        }
    }
}
void Add(node x) {
    heap[++siz] = x;
    pushup(siz);
}
node Search() {
    return heap[1];
}
void Delete() {
    swap(heap[1], heap[siz]);
    siz--;
    go_down(1);
}
int n, m, cnt, tmp, a[N], b[N], pre[N], nxt[N];
int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[++tmp]);
		if (!a[tmp]) tmp--;
	}
	b[++cnt] = a[1];
	for (int i = 2; i <= tmp; i++) {
		if ((a[i] > 0 && a[i - 1] > 0) || (a[i] < 0 && a[i - 1] < 0)) b[cnt] += a[i];
		else {
			if (cnt == 1 && b[cnt] < 0) cnt--;
			b[++cnt] = a[i];
		}
	}
	if (b[cnt] < 0) cnt--;
	int ans = 0, tot = 0;
	for (int i = 1; i <= cnt; i++) {
		if (b[i] > 0) ans += b[i], tot++;
		Add(node(b[i], i));
	}
	for (int i = 0; i <= cnt + 1; i++) pre[i] = i - 1, nxt[i] = i + 1;
	pre[0] = 0;
	nxt[cnt + 1] = cnt + 1;
	b[0] = b[cnt + 1] = -INF;
	while (tot > m) {
		node p = Search();
		Delete();
		if (b[p.y] != p.x) continue;
		ans -= abs(p.x);
		b[p.y] = b[pre[p.y]] + b[nxt[p.y]] + p.x;
		b[pre[p.y]] = b[nxt[p.y]] = -INF;
		Add(node(b[p.y], p.y));
		pre[p.y] = pre[pre[p.y]];
		nxt[pre[p.y]] = p.y;
		nxt[p.y] = nxt[nxt[p.y]];
		pre[nxt[p.y]] = p.y;
		tot--;
	}
	printf("%d\n", ans);
	return 0;
}