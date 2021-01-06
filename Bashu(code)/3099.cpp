#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;
struct Edge {
	int to, next;
	double val, org;
}; 
const int maxN = 10010;
const double INF = 1e20;
const double eps = 1e-4;


Edge e[maxN << 2];
double Dis[maxN];
bool vis[maxN];
int head[maxN] ;

int cnt, N, M ;

queue<int> q;

int INPUT () {
    int x = 0, f = 1;
	char ch = getchar();
    while (ch < '0' || ch > '9') {
		if (ch == '-') f = - 1;
		ch = getchar();
	}
    while (ch >= '0' && ch <= '9') {
		x = (x << 1) + (x << 3) + ch - '0';
		ch = getchar();
	}
    return x * f ;
}

void Add_Edge(const int x, const int y, const double val) {
    e[++cnt].to = y ;
    e[cnt].org = val ;
    e[cnt].next = head[x] ;
    head[x] = cnt ;
}

bool SPFA(const double x) {
    memset(vis, false, sizeof(vis));
    queue<int> Q ;
    for (int i = 1; i <= N; ++i) 
        Dis[i] = INF;
    for (int i = 1; i <= cnt; ++i) e[i].val = e[i].org - x;
    Q.push(0); 
    vis[0] = true;
    Dis[0] = 0;
    while (!Q.empty()) { 
        int t = Q.front();
		Q.pop();
		vis[t] = false;
        for (int i = head[ t ]; i; i = e[i].next) {
            int temp = e[i].to;
            if (Dis[temp] - eps > Dis[t] + e[i].val) {
                Dis[temp] = Dis[t] + e[i].val;
                if (!vis[temp]) {
                    Q.push(temp) ;
                    vis[temp] = true;
                } 
            }
        } 
    }
    return Dis[N] < -eps;
}

int main() {
    N = INPUT(), M = INPUT(); 
    for (int i = 1; i <= M; ++i) {
        int _x = INPUT(), _y = INPUT(), _val = INPUT();
        Add_Edge( _x, _y, _val); 
    }
    Add_Edge(0, 1, 0);
    double l = 0, r = 1e3 ;
    while (r - l >= eps ) {
        double mid = (l + r) / 2.0;
        if (SPFA(mid)) r = mid ;
        else l = mid ;
    }
    printf("%.3lf", l);
    return 0;
} 