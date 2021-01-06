//    ####         #####   
//   ##  ##       ### ###  
//   ##  ##      ###   ### 
//  ##    ##    ###     ###
//  ##    ##    ###        
// ##########   ###        
// ##########   ###        
//##        ##  ###     ###
//##        ##   ###   ### 
//#          #    ### ###  
//#          #     #####   
//所有串：n ^ m
//dp[i]: 长度i的非**串 
//dp[0] = 0
//dp[1] = m;
//dp[2] = m * (m - 1)
//dp[i] = dp[i - 1] * (m - 2);
//通项：dp[n] = m * (m - 1) * (m - 2) ^ (n - 2)
//Ans = 27 - 6 = 21
#include <cstdio>
#include <algorithm>
#define int long long
#define mod 1000000007
using namespace std;
int qkpow(int a, int b) {
	int ans = 1;
	while (b) {
		if (b & 1) {
			ans = ans * a % mod;
		}
		a = a * a % mod;
		b >>= 1;
	}
	return ans;
}
signed main() {
//	freopen("lucky.in", "r", stdin);
//	freopen("lucky.out", "w", stdout);
	int n, m;
	scanf("%lld %lld", &n, &m);
	m %= mod;
	if (n == 1) {
		printf("0");
		return 0;
	}
	int ans1 = qkpow(m, n);
	int ans2 = m * (m - 1) % mod * qkpow(m - 2, n - 2) % mod;
	printf("%lld", ((ans1 - ans2) % mod + mod) % mod);
	return 0;
}