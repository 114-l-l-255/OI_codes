#include<cstdio>
#include<vector>
#include<algorithm>
#include<cstdlib>
using namespace std;
#define rep(i,n) for(int i=1;i<=n;++i)
#define mp make_pair
#define pb push_back
#define x0 gtmsub
#define y0 gtmshb
#define x1 gtmjtjl
#define y1 gtmsf
const int N=200010;
struct data
{
	int id,siz;
	long long sum;
	bool operator<(const data&a) const {return siz*a.sum<a.siz*sum;}
};
vector<data>h[N];
vector<int>g[N];
int n,a[N],size[N];
long long sum[N],f[N],allsum,ans;
void dfs(int p,int fa)
{
	size[p]=1;
	sum[p]=a[p];
	f[p]=a[p];
	for(auto i:g[p])
	if(i!=fa)
	{
		dfs(i,p);
		size[p]+=size[i];
		sum[p]+=sum[i];
		h[p].pb({i,size[i],sum[i]});
		f[p]+=f[i];
	}
	sort(h[p].begin(),h[p].end());
	int nsiz=1;
	for(auto i:h[p])f[p]+=i.sum*nsiz,nsiz+=i.siz;
}
void work(int p,int fa,int siz,long long suma,long long ff)
{
	f[p]=a[p]+ff;
	for(auto i:g[p])if(i!=fa)f[p]+=f[i];
	h[p].pb({fa,siz,suma});
	sort(h[p].begin(),h[p].end());
	int nsiz=1;
	for(auto i:h[p])f[p]+=i.sum*nsiz,nsiz+=i.siz;
	ans=min(ans,f[p]);
	nsiz=1;
	long long nsum=a[p];
	for(auto i:h[p]){if(i.id!=fa)work(i.id,p,n-size[i.id],allsum-sum[i.id],f[p]-f[i.id]-i.sum*nsiz-i.siz*(allsum-nsum-i.sum));nsum+=i.sum;nsiz+=i.siz;}
}
int main()
{
	scanf("%d",&n);
	rep(i,n-1){int x,y;scanf("%d%d",&x,&y);g[x].pb(y);g[y].pb(x);}
	rep(i,n)scanf("%d",&a[i]),allsum+=a[i];
	dfs(1,0);
	ans=f[1];
	work(1,0,0,0,0);
	printf("%lld\n",ans);
	return 0;
}