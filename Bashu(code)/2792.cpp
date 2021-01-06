#include <cstdio>
#include <string>
#include <map>
//#include <bits/stdc++.h>
using namespace std;
int n, d, k, w, sum, len;
string ans;
map<int, int> pd;
int main() {
    scanf("%d %d", &n, &d);
    k = n / d, w = -1;
    int fififif = 0;
    if (n % d == 0) {
    	printf("%d\n", n / d); return 0;
	}
    do {
        ans = char(k % 10 + '0') + ans;
        k /= 10;
        fififif++;
    } while(k);
    ans += '.';
    n = n % d;
    do {
//    	printf("!\n");
        if (pd[n] != 0) {
            w = pd[n];
            break;
        }
        else pd[n] = ans.size();
//    	printf("!\n");
        n *= 10;
//    	printf("!\n");
        k = n / d;
        ans += char(k + '0');
//        printf("%d\n", k);
//    	printf("!\n");
        n = n % d;
//        printf("%d\n", ans.size());
    } while(n != 0 && ans.size() <= 200);
//    printf("?");
    if (w != -1) ans += ')';
    len = ans.size();
    for (int i = 0; i < min(len, 50 + fififif + 1); i++) {
        if (i == w) {
        	if(len<=50)printf("%c", '(');
            i--;
            w = -1;
        }
        else putchar(ans[i]);
//        if(i==1)cout<<"ok";
//        sum++;
//        if (sum % 76 == 0) putchar('\n');
    }
//	printf("%c%c%c", ans[0], ans[1], ans[2]);
    return 0;
}