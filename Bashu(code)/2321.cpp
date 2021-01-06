#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
int INF = 1e9 + 7;
int n, ans, maxlen;
char s[10010];
string solve(int l, int r) {
	vector<string> v;
	int cnt = 0, p = l;
	for (int i = l; i <= r; i++) {
		if (s[i] == '0')
			cnt++;
		else
			cnt--;
		if (cnt == 0) {
			v.push_back(solve(p + 1, i - 1));
			p = i + 1;
		}
	}
	sort(v.begin(), v.end());
	string re = "0";
	for (int i = 0; i < (int)v.size(); i++)
		re = re + v[i];
	return re + "1";
}
int main() {
	int n;
	scanf("%d", &n);
	while (n--) {
		int l;
		scanf("%s", s);
		l = strlen(s);
		string a = solve(0, l - 1);
		scanf("%s", s);
		l = strlen(s);
		string b = solve(0, l - 1);
		if (a == b) puts("same");
		else puts("different");
	}
	return 0;
}