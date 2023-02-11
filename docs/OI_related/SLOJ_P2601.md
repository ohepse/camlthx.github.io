### D4T4 路径的交

#### Desciption：

给定一颗 $n$ 个节点的树，以及 $m$ 条路径，第 $i$ 条路径与前 $i-1$ 条有多少相交的（点相交即视为路径相交）

#### Solution:

现在有两条路径 $a$ 和 $b$ ，有两种情况，一种是 $a$ 的 $lca$ 在 $b$ 上，另一种是 $b$ 的 $lca$ 在 $a$ 上。

所以就转化成了两个问题：

1. 当前路径上有几个之前的 $lca$

2. 之前的路径有几个经过当前的 $lca$ 

可以用两个树状数组来维护，一个支持单点修改、链上查询，另一个支持链上修改、单点查询。

#### Code：

目前只能用倍增来跳 $lca$ ，用欧拉序跳的有点奇怪（悲

```cpp
#include<bits/stdc++.h>
using namespace std;
#define in read()
#define ll long long
const int inf=0x3f3f3f3f;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	} 
	while(c>='0'&&c<='9'){
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar(); 
	}
	return x*f;
}
const int maxn=2e5+10;
struct edge{
	int u,v,nxt;
}e[maxn*10];
int cnt=0,h[maxn];
inline void add(int u,int v){
	e[++cnt]=(edge){u,v,h[u]};
	h[u]=cnt;
}
int n,m,u,v;
int val[maxn],st[maxn],ed[maxn],tim=0,dfn[maxn<<1],dep[maxn],fath[maxn];
int f[maxn<<1][24];
int mmin(int a,int b){
    return dep[a]<dep[b]?a:b;
};
void dfs(int u,int fa){
	st[u]=++tim;
	f[u][0]=fa;
	for(int i=1;i<19;++i) f[u][i]=f[f[u][i-1]][i-1];
	dep[u]=dep[fa]+1;
	for(int i=h[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(v!=fa) dfs(v,u);
	}
	ed[u]=tim;
}

int lca(int x,int y) {   
    if(dep[x]<dep[y]) swap(x,y);   
    for(int i=18;i>=0;i--) 
	  	if(dep[f[x][i]]>=dep[y]) x=f[x][i];   
    if(x==y) return x;   
    for(int i=18;i>=0;i--) 
	  	if(f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];    
    return f[x][0];   
}
struct bittree{
	int t[maxn],siz;
	inline int lowbit(int x){
		return x&(-x);
	}
	inline void update(int x,int val){
		while(x<=n){
			t[x]+=val;
			x+=lowbit(x);
		}
	}
	inline int query(int x){
		int res=0;
		while(x){
			res+=t[x];
			x-=lowbit(x);
		}
		return res;
	}
}t1,t2;
int clac(int x,int y,int lca){
	int ans=0;
	ans+=t1.query(ed[lca])-t1.query(st[lca]-1);
	ans+=t2.query(st[x])+t2.query(st[y])-t2.query(st[lca])*2;
	return ans;
}
int main(){
	n=in;
	for(int i=1;i<n;i++){
		u=in;v=in;
		add(u,v);add(v,u);
	}
	m=in;
	dfs(1,0);
	for(int i=1;i<=m;i++){
		u=in;v=in;
		int lcaa=lca(u,v);
		printf("%d\n",clac(u,v,lcaa)+val[lcaa]);
		val[lcaa]++;
		t1.update(st[u],1);
		t1.update(st[v],1);
		t1.update(st[lcaa],-2);
		t2.update(st[lcaa],1);
		t2.update(ed[lcaa]+1,-1);
	}
	return 0;
}
```