### D4T3 严格次小生成树

#### Description：

给定一张 $n$ 个点 $m$ 条边的无向图，求无向图的严格次小生成树。

设最小生成树的边权之和为 $val$ ，严格次小生成树指边权之和大于 $val$ 的生成树的最小的一个。

#### Solution:

首先严格次小生成树根最小生成树只有一条边不同。 

所以我们可以枚举所有边，如果这条边不在生成树上，那么加入生成树后一定会构成一个环，这时候将边上最大值删去即可。但考虑到严格次小生成树的最大边权与当前边权相同，所以还要记录次大值。

用树剖维护次大值和最大值即可。

#### Code：

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
const int maxn=3e5+10;
struct edge{
	int u,v,w,nxt;
	bool vis;
}e[maxn<<1];
int cnt=0,h[maxn];
inline void add(int u,int v,int w){
	e[++cnt]=(edge){u,v,w,h[u]};
	h[u]=cnt;e[cnt].vis=0;
}
ll vall;
int n,m;
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
int fat[maxn];
int find(int x){
	if(x!=fat[x]) fat[x]=find(fat[x]);
	return fat[x];
}
bool cmp(edge a,edge b){
	return a.w<b.w;
}
void kruskal(){
	sort(e+1,e+1+m,cmp);
	for(int i=1;i<=n;i++) fat[i]=i;
	int sum=0,fu,fv,u,v;//for(int i=1;i<=m;i++) cout<<e[i].u<<" "<<e[i].v<<" "<<e[i].w<<endl;
	for(int i=1;i<=m;i++){
		u=e[i].u,v=e[i].v;
		fu=find(u),fv=find(v);
		//cout<<u<<" "<<v<<" "<<fu<<" "<<fv<<endl;
		if(fu!=fv){
			add(u,v,e[i].w);add(v,u,e[i].w);
			fat[fu]=fv;
			vall+=e[i].w;
			++sum;
			e[i].vis=1;
			if(sum==n-1) break;
		}
	}
}
struct tree{
	int l,r,max,sec;
}t[maxn<<2];
void pushup(int p){
	t[p].max=max(t[p<<1].max,t[p<<1|1].max);
	if(t[p<<1].max==t[p<<1|1].max) t[p].sec=max(t[p<<1].sec,t[p<<1|1].sec);
	else t[p].sec=min(t[p<<1].max,t[p<<1|1].max);
}
void build(int l,int r,int p){
	t[p].l=l;t[p].r=r;
	if(l==r){
		t[p].max=w[dfn[l]];
		return ;
	}
	int mid=(l+r)>>1;
	build(l,mid,p<<1);
	build(mid+1,r,p<<1|1);
	pushup(p);
}
int querymax(int l,int r,int p,int key){
	if(t[p].l>r||t[p].r<l) return -inf;
	if(l<=t[p].l&&t[p].r<=r){
		if(key==t[p].max) return t[p].sec;
		return t[p].max;
	}
	int mid=t[p].l+t[p].r>>1;
	if(r<=mid) return querymax(l,r,p<<1,key);
	else if(mid<l) return querymax(l,r,p<<1|1,key);
	else return max(querymax(l,mid,p<<1,key),querymax(mid+1,r,p<<1|1,key));
}
int getmax(int x,int y,int key){
	int ans=-inf;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		ans=max(ans,querymax(num[top[x]],num[x],1,key));
		x=fa[top[x]];
	}
	if(num[x]>num[y]) swap(x,y);
	ans=max(ans,querymax(num[x]+1,num[y],1,key));
	return ans;
}
int main(){
	n=in;m=in;
	for(int i=1;i<=m;i++){
		e[i].u=in;
		e[i].v=in;
		e[i].w=in;
	}
	cnt=m;
	kruskal();
	dfs1(1,0);
	dfs2(1,1);
	build(1,n,1);
	ll ans=1e18;
	for(int i=1;i<=m;i++){
		if(!e[i].vis) ans=min(ans,vall+e[i].w-getmax(e[i].u,e[i].v,e[i].w));
	}
	printf("%lld\n",ans);
	return 0;
}
```