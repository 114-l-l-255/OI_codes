#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXA = 3001;
int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}
struct fraction {
	int x, y;
	// x/y
	bool operator > (const fraction &sec) const {
		fraction a = *this;
		fraction b = sec;
		int Gcd = gcd(a.y, b.y);
		a.x *= b.y / Gcd;
		b.x *= a.y / Gcd;
		return a.x > b.x;
	}
	void init() {
		scanf("%d/%d", &this->x, &this->y);
	}
} Tan, tmp;
struct node {
	int pos, high;
	bool operator < (const node& sec) const {
		return this->pos < sec.pos;
	}
} Node[MAXA];
int main() {
//	freopen("profit.in", "r", stdin);
//	freopen("profit.out", "w", stdout);
	//t:(0,10]
	//a:(0,10]
	//->
	//alpha:(0,90)
	int n;
	scanf("%d", &n);
	while (n--) {
		int ai;
		scanf("%d", &ai);
		for (int i = 1; i <= ai; i++) {
			scanf("%d %d", &Node[i].pos, &Node[i].high);
		}
		sort(Node + 1, Node + 1 + ai);
//		for (int i = 1; i <= ai; i++) {
//			printf("%d %d\n", Node[i].pos, Node[i].high);
//		}
		Tan.init();
		swap(Tan.x, Tan.y);
		int ans = 0;
		int last = -1;
		for (int i = 1; i <= ai; i++) {
			if (last == -1) {
				ans++;
				last = i;
//				printf("!%d\n", i);
				continue;
			}
			tmp.y = Node[last].high - Node[i].high;
			tmp.x = Node[i].pos - Node[last].pos;
			if (tmp.y < 0 || tmp > Tan) {
				last = i;
				ans++;
//				printf("!%d\n", i);
			}
//			printf("%d %d %d %d\n", tmp.x, tmp.y, Tan.x, Tan.y);
		}
		printf("%d\n", ans);
	}
	return 0;
}