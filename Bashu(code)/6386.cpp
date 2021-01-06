#include <cstdio>
int main() {
//	freopen("game.in", "r", stdin);
//	freopen("game.out", "w", stdout);
	int T;
	scanf("%d", &T);
	while (T--) {
		int n;
		scanf("%d", &n);
		int ans = 1;
		for (int i = 0; i < n; i++) {
			int k;
			scanf("%d", &k);
			if (k == 1) ans ^= 1;
		}
		printf("%s\n", ans ? "hamster" : "rabbit");
	}
	return 0;
}
















































































































/*
BONUS:
yujinn 4023
yujinn058 4925
yujinn101 
yujinn143 
yujinn444 
yujinn456 
yujinn485 
yujinn816 
limoapipi
limipiaop

泥草泥马草马泥马草 3351
泥草泥马草马泥马草117 Lv.1
泥草泥马草马泥马草231 Lv.1
泥草泥马草马泥马草389 Lv.1
泥草泥马草马泥马草444 Lv.1
泥草泥马草马泥马草465 Lv.3 5271
泥草泥马草马泥马草508 Lv.1
泥草泥马草马泥马草534 Lv.1
泥草泥马草马泥马草587 Lv.1
泥草泥马草马泥马草677 Lv.1
泥草泥马草马泥马草734 Lv.1
泥草泥马草马泥马草765 Lv.2
泥草泥马草马泥马草979 Lv.1
*/