#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;

typedef unsigned u32;
typedef long long s64;

const int MaxLogN = 64;
const int M = 20000116;

int nT, nK;
s64 qL, qR;

int sum;
int digit[MaxLogN];

inline void init(s64 x)
{
	sum = 0;
	for (int i = 0; i < MaxLogN; ++i)
		digit[i] = 0;

	int l = 0;
	while (x > 0)
	{
		sum += (digit[++l] = x % nK);
		x /= nK;
	}
}

int main()
{
//	freopen("b.in", "r", stdin);
//	freopen("b.out", "w", stdout);

	cin >> nT;
	while (nT--)
	{
		cin >> nK >> qL >> qR;

		init(qL);

		u32 res = 0;
		for (s64 i = qL; i <= qR; ++i)
		{
			s64 x = i % M;
			s64 v = (x * x + i + 804) / 233;
			res += (u32)v * (sum % nK);

			++digit[1], ++sum;
			for (int k = 1; digit[k] == nK; ++k)
			{
				digit[k] = 0, ++digit[k + 1];
				sum -= nK - 1;
			}
		}

		cout << res << endl;
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}
/*
10
2 1 10
3 1 10
4 1 10
5 1 10
2 1001 5005
10 123 456
233 1024 6174
16 10000 20000
20 12345678 23456789
987 2333123456789 2333198765432
*/