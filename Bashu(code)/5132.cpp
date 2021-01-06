//       AAA        
//      AA AA       
//     AAA AAA      
//     AA   AA      
//    AAA   AAA     
//    AA     AA     
//   AAA     AAA    
//   AAAAAAAAAAA    
//  AAAAAAAAAAAAA   
//  AA         AA   
// AAA         AAA  
// AA           AA  
//AAA           AAA 
//AA             AA 
//AA             AA 
#include <cstdio>
//#include <cstdlib>
//#include <windows.h>
const int MAXN = 10000;
int dp[MAXN][MAXN];
int arr[MAXN];
int main() {
//	freopen("maou.in", "r", stdin);
//	freopen("maou.out", "w", stdout);
	int n;
	scanf("%d", &n);
	for (register int i = 1; i < n; i++) {
		dp[1][i] = i + 1;
	}
	for (register int i = 2; i < n; i++) {
		for (register int j = 1; j <= n - i; j++) {
			dp[i][j] = (dp[i - 1][j + 1] + (long long)dp[i - 1][j] * j) % 1000007;
		}
	}
//	for (register int i = 1; i < n; i++) {
//		for (register int j = 1; j <= n - i; j++) {
//			printf("%d ", dp[i][j]);
//		}
//		printf("\n");
//	}
	int k;
	scanf("%d", &k);
	int lmax = k;
	register int ans = 0;
	for (register int i = 2; i < n; i++) {
		scanf("%d", &k);
		ans = ((long long)ans + (long long)dp[n - i][lmax > k - 1 ? lmax : k - 1] * (k - 1)) % 1000007;
		lmax = lmax > k ? lmax : k;
//		printf("%d\n", ans);
	}
	scanf("%d", &k);
	printf("%d", ans + k);
//Sleep(5000);
	return 0;
}

/*
111\dp[1][1]\
112/        |
121\        |dp[2][1]
122|dp[1][2]/
123/

1111
1112
1121
1122
1123
----
1211
1212
1213-
1221
1222
1223-
1231
1232
1233
1234
*/