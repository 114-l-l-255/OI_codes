# OI_codes

A repository of OI codes.

Author: yinjun2024

And here is some note for problems

**have fun!**

~~**I'm a chinese**~~

## ACAM

https://docs.qq.com/doc/DSU51Y1FCR1ZaaHJO

老师的讲义，讲的很详细

例题：[https://oj.bashu.com.cn/code/problempage.php?problem_id=6770](https://oj.bashu.com.cn/code/problempage.php?problem_id=6770)

代码：[https://github.com/yinjun2024/OI_codes/blob/main/Bashu(code)/6770.cpp](https://github.com/yinjun2024/OI_codes/blob/main/Bashu(code)/6770.cpp)

## SAM

https://docs.qq.com/doc/DSXdNTEJ0WW1kYlF1

老师的讲义，讲的很详细

例题：[https://oj.bashu.com.cn/code/problempage.php?problem_id=6770](https://oj.bashu.com.cn/code/problempage.php?problem_id=6770)（还是这道题

代码：

```cpp
#include<cstdio>
const int MAXN=2000000;struct node{int len,son[26],link;}st[MAXN*2];struct edge{int to,nxt;}edges[MAXN*2];int head[MAXN],tot;char sofa[MAXN];int leng[MAXN];void add(int u,int v){edges[++tot].to=v;edges[tot].nxt=head[u];head[u]=tot;}int sz,last;template<typename T>void swap(T&a,T&b){T t=a;a=b;b=t;}template<typename T>class priority_queue{private:T v[MAXN],n;void pushup(int i){T tmp=v[i];while(tmp<v[i>>1]){v[i]=v[i>>1];i>>=1;}v[i]=tmp;}void pushdown(int i){T tmp=v[i];while((i<<1)<=n){int ch=i<<1;if(ch<n&&v[ch+1]<v[ch]){ch++;}if(tmp>v[ch]){v[i]=v[ch];i=ch;}else break;}v[i]=tmp;}public:priority_queue(){v[0]=-0x3f3f3f3f;n=0;}void clear(){v[0]=-0x3f3f3f3f;n=0;}void push(T x){v[++n]=x;pushup(n);}void pop(){swap(v[1],v[n--]);pushdown(1);}T top(){return v[1];}bool empty(){return n==0;}};template<typename T>inline int strlen(T*s){for(int i=0;;i++){if(s[i]==0)return i;}}int mmp[MAXN],mmmp;void sam_extend(char cc){int c=cc-'a';int cur=++sz;int p=last;last=cur;st[cur].len=st[p].len+1;while(p!=0&&!st[p].son[c]){st[p].son[c]=cur;p=st[p].link;}if(p==0){st[cur].link=1;}else{int q=st[p].son[c];if(st[p].len+1==st[q].len){st[cur].link=q;}else{int nq=++sz;st[nq].len=st[p].len+1;for(int i=0;i<26;i++){st[nq].son[i]=st[q].son[i];}st[nq].link=st[q].link;while(p!=0&&st[p].son[c]==q){st[p].son[c]=nq;p=st[p].link;}st[q].link=st[cur].link=nq;}}mmp[last]=++mmmp;}char str[MAXN],sts[MAXN];priority_queue<int>pq;int jd;void dfs(int u){if(mmp[u])pq.push(mmp[u]),jd=jd>mmp[u]?jd:mmp[u];else{for(int i=head[u];i;i=edges[i].nxt){dfs(edges[i].to);}}}int main(){last=1;sz=1;int q;scanf("%d",&q);int n=0;for(int i=0;i<q;i++){scanf("%s",sofa+n);n+=leng[i]=strlen(sofa+n);}scanf("%s",str);for(int i=0;;i++){if(str[i]==0){n=i;break;}sam_extend(str[i]);sts[i]=str[i];}int ans=0;for(int i=0,start=0;i<q;start+=leng[i],i++){int rt=1;bool flag=0;for(int j=start;j<leng[i]+start;j++){if(st[rt].son[sofa[j]-'a']==0){flag=1;}rt=st[rt].son[sofa[j]-'a'];}ans+=1-flag;}printf("%d\n",ans);return 0;}
```
