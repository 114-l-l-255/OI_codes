#pragma GCC optimize(2, 3)
#pragma GCC optimize("Ofast", "inline")
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 300001;
int seq[MAXN];
int n;
inline int qkmod(int x) {
    return x >= n ? x - n : x;
}
char gc() {
	static char buf[1<<16],*S,*T;
	if(T==S) {
		T=(S=buf)+fread(buf,1,1<<16,stdin);
		if(T==S) return EOF;
	}
	return *S++;
}
#define getchar gc
inline int re(){
	char c;
	int w=1;
	while((c=getchar())<'0'||c>'9')if(c=='-')w=-1;
	int res = c-'0';
	while((c=getchar())>='0'&&c<='9')res = res*10+c-'0';
	return res*w;
}
const int Mxdt = (1<<20);
inline char pc(char ch,bool bj){
	static char buf[Mxdt],*p1=buf,*p2=buf+Mxdt;
	return ((bj)||(*p1++=ch)&&p1==p2)&&fwrite(p1=buf,1,p1-buf,stdout),0;
}
void print(int x){
	if(x>9)print(x/10);
	pc(x%10^48,false);
}
inline void printnum(int x,int ch){
	if(x < 0)pc('-',false),x=-x;
	print(x),pc(ch,false);
}
//	return pc('o',true);
int main() {
//	freopen("sss.txt", "r", stdin);
    n = re();
    for (int i = 0; i < n; i++) {
        seq[i] = re();
    }
    register int i, j, k;
    for (i = 0, j = 1, k = 0; i < n && j < n && k < n; ) {
    	int ii = qkmod(i + k), jj = qkmod(j + k);
        if (seq[ii] == seq[jj]) {
            k++;
        }
        else {
            seq[ii] > seq[jj] ? i += k + 1 : j += k + 1;
            if (i == j) i++;
            k = 0;
        }
    }
    int ans = min(i, j);
    int as = ans + n;
    for (; ans < as; ans++) {
        printnum(seq[qkmod(ans)], ' ');
    }
    return pc('o',true);
}