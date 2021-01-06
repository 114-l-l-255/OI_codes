/*
FullBlock(X):
X X
 X 
X X
EmptyBlock( ):
   
   
   
Yes, That's Space./xyx
*/
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
const int MAXN3 = 730;
const int MAXN = 7;
bool FullBlock[MAXN][MAXN3][MAXN3];
int pre(int id) {
	int l = pow(3, id - 1);
	for (int i = 0; i < l; i++)
		for (int j = 0; j < l; j++)
			FullBlock[id][i][j] = FullBlock[id - 1][i][j];
	for (int i = 0; i < l; i++)
		for (int j = l + l; j < l + l + l; j++)
			FullBlock[id][i][j] = FullBlock[id - 1][i][j - l - l];
	for (int i = l; i < l + l; i++)
		for (int j = l; j < l + l; j++)
			FullBlock[id][i][j] = FullBlock[id - 1][i - l][j - l];
	for (int i = l + l; i < l + l + l; i++)
		for (int j = 0; j < l; j++)
			FullBlock[id][i][j] = FullBlock[id - 1][i - l - l][j];
	for (int i = l + l; i < l + l + l; i++)
		for (int j = l + l; j < l + l + l; j++)
			FullBlock[id][i][j] = FullBlock[id - 1][i - l - l][j - l - l];
}
int main() {
	FullBlock[0][0][0] = 1;
	pre(1);
	pre(2);
	pre(3);
	pre(4);
	pre(5);
	pre(6);
	int k;
	while (~scanf("%d", &k) && ~k) {
		int l = pow(3, k - 1);
		for (int i = 0; i < l; i++) {
			for (int j = 0; j < l; j++) {
				printf("%c", FullBlock[k - 1][i][j] ? 'X' : ' ');
			}
			printf("\n");
		}
		printf("-\n");
	}
}