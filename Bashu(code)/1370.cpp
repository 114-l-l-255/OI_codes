#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXN = 100001;
char list[MAXN];
char str[MAXN];
int toc;
int main() {
	scanf("%s", str);
	int n = strlen(str);
	int ans = 0, now = 0;
	for (int i = 0; i < n; i++) {
		switch (str[i]) {
			case '(' : {
				list[++toc] = str[i];
				break;
			}
			case '[' : {
				list[++toc] = str[i];
				break;
			}
			case '{' : {
				list[++toc] = str[i];
				break;
			}
			case ')' : {
				if (toc == 0) toc = 0, now = 0;
				else if (list[toc] != '(') toc = 0, now = 0;
				else now++, toc--;
				break;
			}
			case ']' : {
				if (toc == 0) toc = 0, now = 0;
				else if (list[toc] != '[') toc = 0, now = 0;
				else now++, toc--;
				break;
			}
			case '}' : {
				if (toc == 0) toc = 0, now = 0;
				else if (list[toc] != '{') toc = 0, now = 0;
				else now++, toc--;
				break;
			}
		}
		ans = max(ans, now);
	}
	printf("%d", ans * 2);
	return 0;
}