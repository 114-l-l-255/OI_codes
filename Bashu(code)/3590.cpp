#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <iostream>
#include <unordered_map>
using namespace std;
unordered_map<string, string> mmp;
int main() {
	string str;
//	getline(cin, str);
	char str1[1001], str2[1001];
//	sscanf(str.c_str(), "%s %s", str1, str2);
//	printf("%s\n%s\n%d", str1, str2, str.size());
	while (1) {
		str.clear();
		getline(cin, str);
		if (str.size() == 0) break;
		memset(str1, 0, sizeof str1);
		memset(str2, 0, sizeof str2);
		sscanf(str.c_str(), "%s %s", str1, str2);
		mmp[(string)str2] = (string)str1;
	}
	while (1) {
		memset(str1, 0, sizeof str1);
		if (scanf("%s", str1) == EOF) return 0;
		cout << (mmp[(string)str1] == (string)("") ? "eh" : mmp[(string)str1]) << '\n';
	}
	return 0;
}