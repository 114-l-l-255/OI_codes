#include <cstdio>
const int MAXP = 50001;
int primes[MAXP];
int ptot;
bool not_prime[MAXP];
void prime(int n) {
    not_prime[0] = not_prime[1] = true;
    for (int i = 2; i <= n; i++) {
        if (not_prime[i] == false) {
            primes[++ptot] = i;
        }
        for (int j = 1; j <= ptot && (long long)i * primes[j] <= n; j++) {
            not_prime[i * primes[j]] = true;
            if (i % primes[j] == 0) break;
        }
    }
}
int main() {
    prime(50000);
    int n;
    scanf("%d", &n);
    while (n--) {
        int ans = 1;
        int a0, a1, b0, b1;
        scanf("%d %d %d %d", &a0, &a1, &b0, &b1);
        for (int i = 1; i <= ptot; i++) {
            if (b1 % primes[i] == 0 || b0 % primes[i] == 0 || a1 % primes[i] == 0 || a0 % primes[i] == 0) {
                int p = primes[i];
                int ma0 = 0, ma1 = 0, mb0 = 0, mb1 = 0, mx = 0;
                while (a0 % p == 0) {
                    ma0++;
                    a0 /= p;
                }
                while (a1 % p == 0) {
                    ma1++;
                    a1 /= p;
                }
                while (b0 % p == 0) {
                    mb0++;
                    b0 /= p;
                }
                while (b1 % p == 0) {
                    mb1++;
                    b1 /= p;
                }
                if (ma1 < ma0 && mb1 > mb0 && ma1 == mb1) {
                    mx = 1;
                }
                else if (ma1 < ma0 && mb1 == mb0 && ma1 <= mb1) {
                    mx = 1;
                }
                else if (ma1 == ma0 && mb1 > mb0 && ma1 <= mb1) {
                    mx = 1;
                }
                else if (ma1 == ma0 && mb1 == mb0 && ma1 <= mb1) {
                    mx = mb1 - ma1 + 1;
                }
                else mx = 0;
                ans = ans * mx;
//            	printf("%d\n", ans);
            }
        }
		if (a0 != 1) {
            int p = a0;
            int ma0 = 0, ma1 = 0, mb0 = 0, mb1 = 0, mx = 0;
            while (a0 % p == 0) {
                ma0++;
                a0 /= p;
            }
            while (a1 % p == 0) {
                ma1++;
                a1 /= p;
            }
            while (b0 % p == 0) {
                mb0++;
                b0 /= p;
            }
            while (b1 % p == 0) {
                mb1++;
                b1 /= p;
            }
            if (ma1 < ma0 && mb1 > mb0 && ma1 == mb1) {
                mx = 1;
            }
            else if (ma1 < ma0 && mb1 == mb0 && ma1 <= mb1) {
                mx = 1;
            }
            else if (ma1 == ma0 && mb1 > mb0 && ma1 <= mb1) {
                mx = 1;
            }
            else if (ma1 == ma0 && mb1 == mb0 && ma1 <= mb1) {
                mx = mb1 - ma1 + 1;
            }
            else mx = 0;
            ans = ans * mx;
//            printf("%da\n", ans);
		}
		if (a1 != 1) {
            int p = a1;
            int ma0 = 0, ma1 = 0, mb0 = 0, mb1 = 0, mx = 0;
            while (a0 % p == 0) {
                ma0++;
                a0 /= p;
            }
            while (a1 % p == 0) {
                ma1++;
                a1 /= p;
            }
            while (b0 % p == 0) {
                mb0++;
                b0 /= p;
            }
            while (b1 % p == 0) {
                mb1++;
                b1 /= p;
            }
            if (ma1 < ma0 && mb1 > mb0 && ma1 == mb1) {
                mx = 1;
            }
            else if (ma1 < ma0 && mb1 == mb0 && ma1 <= mb1) {
                mx = 1;
            }
            else if (ma1 == ma0 && mb1 > mb0 && ma1 <= mb1) {
                mx = 1;
            }
            else if (ma1 == ma0 && mb1 == mb0 && ma1 <= mb1) {
                mx = mb1 - ma1 + 1;
            }
            else mx = 0;
            ans = ans * mx;
//            printf("%ds\n", ans);
		}
		if (b0 != 1) {
            int p = b0;
            int ma0 = 0, ma1 = 0, mb0 = 0, mb1 = 0, mx = 0;
            while (a0 % p == 0) {
                ma0++;
                a0 /= p;
            }
            while (a1 % p == 0) {
                ma1++;
                a1 /= p;
            }
            while (b0 % p == 0) {
                mb0++;
                b0 /= p;
            }
            while (b1 % p == 0) {
                mb1++;
                b1 /= p;
            }
            if (ma1 < ma0 && mb1 > mb0 && ma1 == mb1) {
                mx = 1;
            }
            else if (ma1 < ma0 && mb1 == mb0 && ma1 <= mb1) {
                mx = 1;
            }
            else if (ma1 == ma0 && mb1 > mb0 && ma1 <= mb1) {
                mx = 1;
            }
            else if (ma1 == ma0 && mb1 == mb0 && ma1 <= mb1) {
                mx = mb1 - ma1 + 1;
            }
            else mx = 0;
            ans = ans * mx;
//            printf("%dd\n", ans);
		}
		if (b1 != 1) {
            int p = b1;
            int ma0 = 0, ma1 = 0, mb0 = 0, mb1 = 0, mx = 0;
            while (a0 % p == 0) {
                ma0++;
                a0 /= p;
            }
            while (a1 % p == 0) {
                ma1++;
                a1 /= p;
            }
            while (b0 % p == 0) {
                mb0++;
                b0 /= p;
            }
            while (b1 % p == 0) {
                mb1++;
                b1 /= p;
            }
            if (ma1 < ma0 && mb1 > mb0 && ma1 == mb1) {
                mx = 1;
            }
            else if (ma1 < ma0 && mb1 == mb0 && ma1 <= mb1) {
                mx = 1;
            }
            else if (ma1 == ma0 && mb1 > mb0 && ma1 <= mb1) {
                mx = 1;
            }
            else if (ma1 == ma0 && mb1 == mb0 && ma1 <= mb1) {
                mx = mb1 - ma1 + 1;
            }
            else mx = 0;
            ans = ans * mx;
//            printf("%df\n", ans);
		}
        printf("%d\n", ans);
    }
}