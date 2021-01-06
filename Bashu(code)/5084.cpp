/*
 * k = (a, b)
 * x * k * (a' + b') = k ^ 2 * a * b
 * a' + b' | k * a' * b'
 * a' + b' | k
 * a' + b' = k / x
 * ---
 * a + b <= n
 * a' + b' <= n / k
 * ---
 * ==>(a' + b') ^ 2 <= n / x
 * ==>x * (a' + b') ^ 2 <= n
 * m = a' + b'
 * ==> x * m ^ 2 <= n 
 * so ans = Sigma_{i = 1}^{sqrt{n}}{phi(i) * n / i / i}
 */
#include <cstdio>
#include <algorithm>
#include <cmath>
#define int long long
using namespace std;
const int MAXP = 10000001;
const int MAXSN = 10000001;
int primes[MAXP], tot;
bool not_prime[MAXSN];
int phi[MAXSN];
void Prime(int n) {
    not_prime[0] = not_prime[1] = 1;
    phi[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (not_prime[i] == 0) {
            phi[i] = i - 1;
            primes[++tot] = i;
        }
        for (int j = 1; j <= tot; j++) {
            if (primes[j] * i > n) break;
            not_prime[primes[j] * i] = 1;
            if (i % primes[j] == 0) {
                phi[primes[j] * i] = phi[i] * primes[j];
                break;
            }
            else {
                phi[primes[j] * i] = phi[i] * phi[primes[j]];
            }
        }
    }
}
signed main() {
    long long n;
    scanf("%lld", &n);
    Prime(sqrt(n));
    int QwQ = sqrt(n);
    unsigned long long ans = 0;
    for (int i = 2; i <= QwQ; i++) {
        ans += phi[i] * 1ll * (n / i / i);
        // printf("%d\n", phi[i]);
    }
    printf("%llu", ans);
    return 0;
}