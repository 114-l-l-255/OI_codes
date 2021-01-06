#include <iostream>
#include <cstdio>
#include <stack>
using namespace std;
stack<int> nums;
stack<char> ops;
void cal() {
	int a = nums.top();
	nums.pop();
	int b = nums.top();
	nums.pop();
	char c = ops.top();
	ops.pop();
	int d;
	if (c == '+') d = b + a;
	else if (c == '-') d = b - a;
	else if (c == '*') d = b * a;
	else if (c == '/') d = b / a;
	else {
		d = 1;
		while (a--) d *= b;
	}
	nums.push(d);
}
int main() {
	string str;
	cin >> str;
	string left;
	for(int i = 0; i <= str.size(); i++) left += '(';
	str = left + str + ')';
	for (int i = 0; i < str.size(); i++) {
		if (str[i] >= '0' && str[i] <= '9') {
			int j = i, t = 0;
			while (str[j] >= '0' && str[j] <= '9') {
				t = t * 10 + str[j] - '0';
				j++;
			}
			i = j - 1;
			nums.push(t);
		}
		else {
			char c = str[i];
			if (c == '+' || c == '-') {
				if (c == '-' && i && !(str[i - 1] >= '0' && str[i - 1] <= '9' || str[i - 1] == ')')) {
					int j = i + 1, t = 0;
					while (str[j] >= '0' && str[j] <= '9') {
						t = t * 10 + str[j] - '0';
						j++;
					}
					i = j - 1;
					nums.push(-t);
				}
				else {
					while (ops.top() != '(') cal();
					ops.push(c);
				}
			}
			else if (c == '*' || c == '/') {
				while (ops.top() == '*' || ops.top() == '/' || ops.top() == '^') cal();
				ops.push(c);
			}
			else if (c == '^') {
				while (ops.top() == '^') cal();
				ops.push(c);
			}
			else if (c == ')') {
				while (ops.top() != '(') cal();
				ops.pop();
			}
			else if(c == '(') ops.push(c);
			else puts("♂");
		}
	}
	cout << nums.top() << endl;
	return 0;
}