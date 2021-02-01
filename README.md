# OI_codes

A repository of OI codes.

Author: yinjun2024

And here is some note for problems

**have fun!**

## ACAM

https://docs.qq.com/doc/DSU51Y1FCR1ZaaHJO

老师的讲义，讲的很详细

例题：[https://oj.bashu.com.cn/code/problempage.php?problem_id=6770](https://oj.bashu.com.cn/code/problempage.php?problem_id=6770)

代码：

```cpp
#include<cstdio>
const int MAXN=1000005;int son[MAXN][26],flag[MAXN],fail[MAXN],cnt;char str[MAXN];class Query{private:int q[MAXN];int l,r;public:Query(){l=0,r=-1;}void push(int x){q[++r]=x;}int front(){return q[l];}void pop(){l++;}void clear(){l=0,r=-1;}bool empty(){return l>r;}int size(){return r-l+1;}};int strlen(char*s){for(int i=0;;i++)if(s[i]==0)return i;}template<typename T>void memset(T*s){for(int i=0;i<sizeof(s)/sizeof(T);i++)s[i]=0;}void insert(char*s){int n=strlen(s);int root=1;for(int i=0;i<n;i++){if(son[root][s[i]-'a']==0)son[root][s[i]-'a']=++cnt;root=son[root][s[i]-'a'];}flag[root]++;}Query Q;void Getfail(){for(int i=0;i<26;i++){son[0][i]=1;}Q.push(1);while(!Q.empty()){int u=Q.front();Q.pop();int Fail=fail[u];for(int i=0;i<26;i++){if(son[u][i]==0){son[u][i]=son[Fail][i];}else{fail[son[u][i]]=son[Fail][i];Q.push(son[u][i]);}}}}int Ask(char*s){int n=strlen(s);int ans=0,root=1;for(int i=0;i<n;i++){int tp=son[root][s[i]-'a'];while(tp>1&&flag[tp]!=-1){ans+=flag[tp];flag[tp]=-1;tp=fail[tp];}root=son[root][s[i]-'a'];}return ans;}int main(){cnt=1;int n;scanf("%d",&n);for(int i=1;i<=n;i++){memset(str);scanf("%s",str);insert(str);}Getfail();memset(str);scanf("%s",str);printf("%d",Ask(str));return 0;}
```

## SAM

https://docs.qq.com/doc/DSXdNTEJ0WW1kYlF1

老师的讲义，讲的很详细

例题：[https://oj.bashu.com.cn/code/problempage.php?problem_id=6770](https://oj.bashu.com.cn/code/problempage.php?problem_id=6770)（还是这道题

代码：

```cpp
#include<cstdio>
const int MAXN=2000000;struct node{int len,son[26],link;}st[MAXN*2];struct edge{int to,nxt;}edges[MAXN*2];int head[MAXN],tot;char sofa[MAXN];int leng[MAXN];void add(int u,int v){edges[++tot].to=v;edges[tot].nxt=head[u];head[u]=tot;}int sz,last;template<typename T>void swap(T&a,T&b){T t=a;a=b;b=t;}template<typename T>class priority_queue{private:T v[MAXN],n;void pushup(int i){T tmp=v[i];while(tmp<v[i>>1]){v[i]=v[i>>1];i>>=1;}v[i]=tmp;}void pushdown(int i){T tmp=v[i];while((i<<1)<=n){int ch=i<<1;if(ch<n&&v[ch+1]<v[ch]){ch++;}if(tmp>v[ch]){v[i]=v[ch];i=ch;}else break;}v[i]=tmp;}public:priority_queue(){v[0]=-0x3f3f3f3f;n=0;}void clear(){v[0]=-0x3f3f3f3f;n=0;}void push(T x){v[++n]=x;pushup(n);}void pop(){swap(v[1],v[n--]);pushdown(1);}T top(){return v[1];}bool empty(){return n==0;}};template<typename T>inline int strlen(T*s){for(int i=0;;i++){if(s[i]==0)return i;}}int mmp[MAXN],mmmp;void sam_extend(char cc){int c=cc-'a';int cur=++sz;int p=last;last=cur;st[cur].len=st[p].len+1;while(p!=0&&!st[p].son[c]){st[p].son[c]=cur;p=st[p].link;}if(p==0){st[cur].link=1;}else{int q=st[p].son[c];if(st[p].len+1==st[q].len){st[cur].link=q;}else{int nq=++sz;st[nq].len=st[p].len+1;for(int i=0;i<26;i++){st[nq].son[i]=st[q].son[i];}st[nq].link=st[q].link;while(p!=0&&st[p].son[c]==q){st[p].son[c]=nq;p=st[p].link;}st[q].link=st[cur].link=nq;}}mmp[last]=++mmmp;}char str[MAXN],sts[MAXN];priority_queue<int>pq;int jd;void dfs(int u){if(mmp[u])pq.push(mmp[u]),jd=jd>mmp[u]?jd:mmp[u];else{for(int i=head[u];i;i=edges[i].nxt){dfs(edges[i].to);}}}int main(){last=1;sz=1;int q;scanf("%d",&q);int n=0;for(int i=0;i<q;i++){scanf("%s",sofa+n);n+=leng[i]=strlen(sofa+n);}scanf("%s",str);for(int i=0;;i++){if(str[i]==0){n=i;break;}sam_extend(str[i]);sts[i]=str[i];}int ans=0;for(int i=0,start=0;i<q;start+=leng[i],i++){int rt=1;bool flag=0;for(int j=start;j<leng[i]+start;j++){if(st[rt].son[sofa[j]-'a']==0){flag=1;}rt=st[rt].son[sofa[j]-'a'];}ans+=1-flag;}printf("%d\n",ans);return 0;}
```

例题：[http://hihocoder.com/problemset/solution/1601220](http://hihocoder.com/problemset/solution/1601220)

```cpp
#include<cstdio>
const int MAXN=1000;struct node{int len,son[130],link;}st[MAXN*2];struct edge{int to,nxt;}edges[MAXN*2];int head[MAXN],tot;void add(int u,int v){edges[++tot].to=v;edges[tot].nxt=head[u];head[u]=tot;}int sz,last;template<typename T>void swap(T&a,T&b){T t=a;a=b;b=t;}template<typename T>class priority_queue{private:T v[MAXN],n;void pushup(int i){T tmp=v[i];while(tmp<v[i>>1]){v[i]=v[i>>1];i>>=1;}v[i]=tmp;}void pushdown(int i){T tmp=v[i];while((i<<1)<=n){int ch=i<<1;if(ch<n&&v[ch+1]<v[ch]){ch++;}if(tmp>v[ch]){v[i]=v[ch];i=ch;}else break;}v[i]=tmp;}public:priority_queue(){v[0]=-0x3f3f3f3f;n=0;}void clear(){v[0]=-0x3f3f3f3f;n=0;}void push(T x){v[++n]=x;pushup(n);}void pop(){swap(v[1],v[n--]);pushdown(1);}T top(){return v[1];}bool empty(){return n==0;}};template<typename T>inline int strlen(T*s){for(int i=0;;i++){if(s[i]==0)return i;}}int mmp[MAXN],mmmp;void sam_extend(char cc){int c=cc;int cur=++sz;int p=last;last=cur;st[cur].len=st[p].len+1;while(p!=0&&!st[p].son[c]){st[p].son[c]=cur;p=st[p].link;}if(p==0){st[cur].link=1;}else{int q=st[p].son[c];if(st[p].len+1==st[q].len){st[cur].link=q;}else{int nq=++sz;st[nq].len=st[p].len+1;for(int i='a';i<='z';i++){st[nq].son[i]=st[q].son[i];}st[nq].link=st[q].link;while(p!=0&&st[p].son[c]==q){st[p].son[c]=nq;p=st[p].link;}st[q].link=st[cur].link=nq;}}mmp[last]=++mmmp;}char str[MAXN],sts[MAXN];priority_queue<int>pq;int jd;void dfs(int u){if(mmp[u])pq.push(mmp[u]),jd=jd>mmp[u]?jd:mmp[u];for(int i=head[u];i;i=edges[i].nxt){dfs(edges[i].to);}}int main(){last=1;sz=1;scanf("%s",str);int n;for(int i=0;;i++){if(str[i]==0){n=i;break;}sam_extend(str[i]);sts[i]=str[i];}for(int i=1;i<=sz;i++){if(i>1)add(st[i].link,i);}int q;scanf("%d",&q);for(int i=0;i<q;i++){for(int j=0;;j++){if(str[j])str[j]=0;else break;}scanf("%s",str);int n=strlen(str);int rt=1;for(int j=0;j<n;j++){rt=st[rt].son[str[j]];}jd=0;pq.clear();dfs(rt);for(int j=jd-st[st[rt].link].len;j<=jd;j++){putchar(sts[j-1]);}putchar(' ');for(int j=jd-st[rt].len+1;j<=jd;j++){putchar(sts[j-1]);}while(!pq.empty()){printf(" %d",pq.top());pq.pop();}puts("");}return 0;}
```
