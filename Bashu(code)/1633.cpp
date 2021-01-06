#include <cstdio>
#include <algorithm>
using namespace std;
struct node {
	int x, y;
	int id;
} nodes1[100001], nodes2[100001];
bool cmpx(node x, node y) {
	return x.x < y.x;
}
bool cmpy(node x, node y) {
	return x.y < y.y;
}
int valx1[100001], valy1[100001];
int valx2[100001], valy2[100001];
int main() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &nodes1[i].x, &nodes1[i].y);
		nodes2[i].x = nodes1[i].x;
		nodes2[i].y = nodes1[i].y;
		nodes1[i].id = nodes2[i].id = i;
	}
	sort(nodes1, nodes1 + n, cmpx);
	sort(nodes2, nodes2 + n, cmpy);
	for (int i = 1; i < n; i++) {
		valx1[nodes1[i].id] = valx1[nodes1[i - 1].id] + i * (nodes1[i].x - nodes1[i - 1].x);
//		printf("%d\n", nodes1[i].id);
	}
	for (int i = n - 2; i >= 0; i--) {
//		printf("%d\n", nodes1[i].id);
		valx2[nodes1[i].id] = valx2[nodes1[i + 1].id] + (n - 1 - i) * (nodes1[i + 1].x - nodes1[i].x);
	}
	for (int i = 1; i < n; i++) {
//		printf("%d\n", nodes2[i].id);
		valy1[nodes2[i].id] = valy1[nodes2[i - 1].id] + i * (nodes2[i].y - nodes2[i - 1].y);
	}
	for (int i = n - 2; i >= 0; i--) {
//		printf("%d\n", nodes2[i].id);
		valy2[nodes2[i].id] = valy2[nodes2[i + 1].id] + (n - 1 - i) * (nodes2[i + 1].y - nodes2[i].y);
	}
	int ans = 0x7fffffff;
	for (int i = 0; i < n; i++) {
//		printf("%d %d %d %d\n", valx1[i], valx2[i], valy1[i], valy2[i]);
		ans = min(ans, valx1[i] + valx2[i] + valy1[i] + valy2[i]);
	}
	printf("%d", ans);
	return 0;
}