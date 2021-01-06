#include<bits/stdc++.h>
#define GET getchar()
#define N 100005
#define mp(x,y) make_pair((x),(y)) 
#define ll long long
#define M 1000005
#define inf 1000000000
using namespace std;
int read(){
	int x=0,f=1;char c=GET;
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=GET;}
	while('0'<=c&&c<='9'){x=x*10+c-'0';c=GET;}
	return x*f;
}
int n,m,cnt,h[N],val[N],maxx[N][19],p[N][19],flg[M],dep[N];
int Ans[M];
struct Edge{
	int to,next,w;
}a[N*2]; 
void Add(int x,int y,int z){
	cnt++;a[cnt].to=y;a[cnt].w=z;a[cnt].next=h[x];h[x]=cnt;
}
struct Kru{
	int x,y,z,id;
	bool operator <(const Kru &w)const{return z<w.z;}
}e[M];
int prt[N];
int find(int x){return x==prt[x]?x:prt[x]=find(prt[x]);}
void Kruskal(){
	int etot=0;
	for(int i=1;i<=n;++i)prt[i]=i;
	for(int i=1;i<=m;++i){
		int f1=find(e[i].x),f2=find(e[i].y);
		if(f1!=f2){
			flg[i]=1;
			Add(e[i].x,e[i].y,e[i].z);Add(e[i].y,e[i].x,e[i].z);
			prt[f1]=f2;etot++;
			if(etot==n-1)break;
		} 
	}
}
void dfs(int x,int fa){
	p[x][0]=fa;dep[x]=dep[fa]+1;
	for(int i=h[x];i;i=a[i].next){
		int y=a[i].to;
		if(y!=fa){maxx[y][0]=a[i].w;dfs(y,x);}
	}
}
void ST(){
	for(int j=1;j<=18;++j)
		for(int i=1;i<=n;++i){
			p[i][j]=p[p[i][j-1]][j-1];
			maxx[i][j]=max(maxx[i][j-1],maxx[p[i][j-1]][j-1]);
		}
}
int log2(int x){
	if(x<2)return 0;
	return log2(x/2)+1;
}
int Qmax(int x,int y){
	int ret=0;
	if(dep[x]<dep[y])swap(x,y);
	for(int k=log2(dep[x]);k>=0;--k)
		if(dep[p[x][k]]>=dep[y])ret=max(ret,maxx[x][k]),x=p[x][k];
	if(x==y)return ret;
	for(int k=log2(dep[x]);k>=0;--k)
		if(p[x][k]!=p[y][k])ret=max(ret,max(maxx[x][k],maxx[y][k])),x=p[x][k],y=p[y][k];
	return max(ret,max(maxx[x][0],maxx[y][0]));
}
int LCA(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	for(int k=log2(dep[x]);k>=0;--k)
		if(dep[p[x][k]]>=dep[y])x=p[x][k];
	if(x==y)return x;
	for(int k=log2(dep[x]);k>=0;--k)
		if(p[x][k]!=p[y][k])x=p[x][k],y=p[y][k];
	return p[x][0];
}
int ed[M<<1];
typedef pair<int,int>pi;
vector<pi>v[N];
struct Heap{
	int lc,rc,dis;
	int val,id;
}q[M<<1]; 
int Merge(int x,int y){
	if(!x||!y)return x+y;
	if(q[x].val>q[y].val)swap(x,y);
	int &l=q[x].lc,&r=q[x].rc;
	r=Merge(r,y);if(q[l].dis<q[r].dis)swap(l,r);
	q[x].dis=q[r].dis+1;
	return x;
}
int Pop(int x){
	q[x].val=-1;int l=q[x].lc,r=q[x].rc;
	return Merge(l,r);
}
int ind=0;
int Find(int x,int fa){
	int rt=0;
	for(int i=0;i<v[x].size();++i){
		ind++;q[ind].val=v[x][i].first;q[ind].id=v[x][i].second;
		rt=Merge(rt,ind);
	}
	for(int i=h[x];i;i=a[i].next){
		int y=a[i].to;
		if(y!=fa){val[y]=inf;
			int ret=Find(y,x);
			while(1){
				if(!ret)break;
				int pre=q[ret].id;//belong to 1~cnt 
				if(LCA(ed[pre],y)!=y){val[y]=q[ret].val;break;}
				ret=Pop(ret);
			}
			rt=Merge(rt,ret);
		}
	}
	return rt;
}
int main(){
//	freopen("data.in","r",stdin);
//	freopen("data.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;++i)e[i]=(Kru){read(),read(),read(),i};
	sort(e+1,e+m+1);Kruskal();
	dfs(1,0);ST();cnt=0;q[0].dis=-1;
	for(int i=1;i<=m;++i)if(!flg[i]){
		int x=e[i].x,y=e[i].y;
		Ans[e[i].id]=Qmax(x,y);
		int lca=LCA(x,y);
		if(lca!=x)v[x].push_back(mp(e[i].z,++cnt)),ed[cnt]=lca;
		if(lca!=y)v[y].push_back(mp(e[i].z,++cnt)),ed[cnt]=lca;
	}
	Find(1,0);
	for(int i=1;i<=m;++i)if(flg[i]){
		int x=e[i].x,y=e[i].y;
		if(dep[x]<dep[y])swap(x,y);
		Ans[e[i].id]=val[x];
	}
	for(int i=1;i<=m;++i)printf("%d\n",Ans[i]);
	
}
/*
6 7
1 2 2
2 3 1
3 4 0
1 4 3
3 5 20
4 5 8
3 6 14

*/