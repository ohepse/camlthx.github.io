### D3T4 月下毛景树

#### Description：

给定一颗 $n$ 个节点有边权的树，维护以下四个操作：

`Change k w` 将第 $k$ 条边的边权改为 $w$

`Cover u v w` 将 $<u,v>$ 路径上的所有边权都改为 $w$

`Add u v w ` 将 $<u,v>$ 路径上的所有边权都加上 $w$

`Max u v` 询问 $<u,v>$ 路径上边权最大值

#### Solution：

将边权转化为深度更大的点的点权，然后变成树剖的模板。

需要注意的是，改变路径上的边权时要去掉 $lca$ 的点权。

```cpp
void modify(int x,int y,int val){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		updadd(num[top[x]],num[x],1,val);
		x=fa[top[x]];
	}
	if(num[x]>num[y]) swap(x,y);
	updadd(num[x],num[y],1,val);
}
```

要变为：

```cpp
void modify(int x,int y,int val){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		updadd(num[top[x]],num[x],1,val);
		x=fa[top[x]];
	}
	if(num[x]>num[y]) swap(x,y);
	updadd(num[x]+1,num[y],1,val);
}
```

#### Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define in read()
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
	int u,v,w,nxt;
}e[maxn<<1];
int cnt=0,h[maxn];
inline void add(int u,int v,int w){
	e[++cnt]=(edge){u,v,w,h[u]};
	h[u]=cnt;
}
int n,q,u,v;
int dep[maxn],siz[maxn],hson[maxn],fa[maxn],w[maxn],id[maxn];
int dfn[maxn],num[maxn],top[maxn],tot=0;
void dfs1(int x,int father){
	siz[x]=1;
	hson[x]=0;
	for(int i=h[x];i;i=e[i].nxt){
		int v=e[i].v;
		if(v==father) continue; 
		dep[v]=dep[x]+1;
		fa[v]=x;
		dfs1(v,x);
		w[v]=e[i].w;
		siz[x]+=siz[v];
		if(siz[hson[x]]<siz[v]) hson[x]=v;
	}
}
void dfs2(int x,int tp){
	top[x]=tp;
	num[x]=++tot;
	dfn[tot]=x;
	if(hson[x]) dfs2(hson[x],tp);
	for(int i=h[x];i;i=e[i].nxt){
		int v=e[i].v;
		if(v!=fa[x]&&hson[x]!=v) dfs2(v,v);
	}
}
struct tree{
	int l,r,max,add,cov;
}t[maxn<<2];
void build(int l,int r,int p){
	t[p].l=l;t[p].r=r;
	if(l==r){
		t[p].max=w[dfn[l]];
		return ;
	}
	int mid=(l+r)>>1;
	build(l,mid,p<<1);
	build(mid+1,r,p<<1|1);
	t[p].max=max(t[p<<1].max,t[p<<1|1].max);
}
void pushcov(int p,int val){
	t[p].max=val;
	t[p].add=0;
	t[p].cov=val;
}
void pushadd(int p,int val){
	t[p].max+=val;
	t[p].add+=val;
}
void pushdown(int p){
	if(t[p].cov){
		pushcov(p<<1,t[p].cov);
		pushcov(p<<1|1,t[p].cov);
		t[p].cov=0;
	}
	if(t[p].add){
		pushadd(p<<1,t[p].add);
		pushadd(p<<1|1,t[p].add);
		t[p].add=0;
	}
}
void updcover(int l,int r,int p,int val){
	if(l<=t[p].l&&t[p].r<=r){
		pushcov(p,val);
		return ;
	}
	pushdown(p);
	int mid=t[p].l+t[p].r>>1;
	if(l<=mid) updcover(l,r,p<<1,val);
	if(r>mid) updcover(l,r,p<<1|1,val);
	t[p].max=max(t[p<<1].max,t[p<<1|1].max);
}
void updadd(int l,int r,int p,int val){
	if(l<=t[p].l&&t[p].r<=r){
		pushadd(p,val);
		return ;
	}
	pushdown(p);
	int mid=t[p].l+t[p].r>>1;
	if(l<=mid) updadd(l,r,p<<1,val);
	if(r>mid) updadd(l,r,p<<1|1,val);
	t[p].max=max(t[p<<1].max,t[p<<1|1].max);
}
int querymax(int l,int r,int p){
	if(l<=t[p].l&&t[p].r<=r) return t[p].max;
	pushdown(p);
	int mid=t[p].l+t[p].r>>1;
	int ans=-0x3f3f3f3f;
	if(l<=mid) ans=max(ans,querymax(l,r,p<<1));
	if(mid<r) ans=max(ans,querymax(l,r,p<<1|1));
	return ans;
}
void cover(int x,int y,int val){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		updcover(num[top[x]],num[x],1,val);
		x=fa[top[x]];
	}
	if(num[x]>num[y]) swap(x,y);
	updcover(num[x]+1,num[y],1,val);
}
void modify(int x,int y,int val){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		updadd(num[top[x]],num[x],1,val);
		x=fa[top[x]];
	}
	if(num[x]>num[y]) swap(x,y);
	updadd(num[x]+1,num[y],1,val);
}
int getmax(int x,int y){
	int ans=-0x3f3f3f3f;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		ans=max(ans,querymax(num[top[x]],num[x],1));
		x=fa[top[x]];
	}
	if(num[x]>num[y]) swap(x,y);
	ans=max(ans,querymax(num[x]+1,num[y],1));
	return ans;
}
int main(){
	freopen("P4315_1.in","r",stdin);
	freopen("ans.out","w",stdout);
	n=in;
	for(int i=1;i<n;i++){
		u=in;v=in;int w=in;
		add(u,v,w);
		add(v,u,w);
	}
	dfs1(1,0);
	dfs2(1,1);
	build(1,tot,1);
	for(int i=1;i<=n*2-2;i+=2) id[i/2+1]=dep[e[i].u]>dep[e[i].v]?e[i].u:e[i].v;
	char opt[10];
	while(1){
		scanf("%s",opt);
		if(opt[0]=='S') break;
		int x=in,y=in,z;
		if(opt[0]=='C'&&opt[1]=='h'){
			updcover(num[id[x]],num[id[x]],1,y);
			continue;
		}
		if(opt[0]=='C'&&opt[1]=='o'){
			z=in;
			cover(x,y,z);
			continue;
		}
		if(opt[0]=='A'){
			z=in;
			modify(x,y,z);
		}
		if(opt[0]=='M') printf("%d\n",getmax(x,y));
	}
	return 0;
}
```