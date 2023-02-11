### D3T2 Graph

#### Description:

给一个 $n$ 个点的图，有 $2*n-2$ 条**有向边**。边目录按两部分给出：

1. 开始的 $n-1$ 条边描述了一颗以1号点为根的生成树，每个点都可以由1号点到达。

2. 接下来的 $n-1$ 条边一定是 $<i,1>$ 的有向边，保证每个点都能到达1号点。

有 $q$ 次询问：

`1 x w` 将第 $x$条边的边权修改为 $w$ 

`2 u v` 询问 $u$ 到 $v$ 的最短距离

#### Solution：

~~我是绝对不会说我因为没看见有向边导致样例玩了1个小时~~

讨论一下 $u$ 和 $v$ 的关系。

如果 $u$ 是 $lca$ ，直接求链就可以了。不然查询以 $u$ 为根的子树返回根的最优值就好了。

然后用树剖维护 $dis_i+w_i$ 的最小值，$dis_i$ 表示 $i$ 到根的距离，$w_i$ 表示 $i$ 回到根的距离。

至于为什么觉得 [FSYo的题解](https://blog.csdn.net/sslz_fsy/article/details/82557256?ops_request_misc=&request_id=&biz_id=102&utm_term=graph%20%E7%BA%BF%E6%AE%B5%E6%A0%91&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-0-82557256.142^v73^control_1,201^v4^add_ask,239^v1^insert_chatgpt&spm=1018.2226.3001.4187) 写的很清楚。

#### Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=4e5+10;
#define in read()
#define ll long long
inline ll read(){
	ll x=0,f=1;char c=getchar();
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
struct edge{
	int v,nxt;
	ll w;
}e[maxn<<2];
int h[maxn],cnt=0;
inline void add(int u,int v,ll w){
	e[++cnt].v=v;e[cnt].nxt=h[u];e[cnt].w=w;
	h[u]=cnt;
}
struct tree{
	int l,r;
	ll min,tag;
}t[maxn<<2];
int n,q,tot=0,siz[maxn],rec[maxn],top[maxn],num[maxn],fa[maxn],dep[maxn],pred[maxn],hson[maxn];
ll a[maxn],dis[maxn];
void dfs1(int x){
	siz[x]=1;
	for(int i=h[x];i;i=e[i].nxt){
		int v=e[i].v;
		a[v]=a[x]+e[i].w;
		dep[v]=dep[x]+1;
		fa[v]=x;
		dfs1(v);
		siz[x]+=siz[v];
		if(siz[v]>siz[hson[x]]) hson[x]=v; 
	}
}
void dfs2(int x,int tp){
	top[x]=tp;num[x]=++tot;pred[tot]=x;
	if(!hson[x]) return ;
	dfs2(hson[x],tp);
	for(int i=h[x];i;i=e[i].nxt){
		int v=e[i].v;
		if(v!=hson[x]) dfs2(v,v);
	}
}
void build(int l,int r,int p){
	t[p].l=l;t[p].r=r;
	if(l==r){
		t[p].min=a[pred[l]]+dis[pred[l]];
		return ;
	}
	int mid=l+r>>1;
	build(l,mid,p<<1);
	build(mid+1,r,p<<1|1);
	t[p].min=min(t[p<<1].min,t[p<<1|1].min);
}
void pushdown(int p){
	if(t[p].tag){
		t[p<<1].min+=t[p].tag;
		t[p<<1|1].min+=t[p].tag;
		t[p<<1].tag+=t[p].tag;
		t[p<<1|1].tag+=t[p].tag;
		t[p].tag=0; 
	}
}
void update(int l,int r,int p,ll val){
	if(l>t[p].r||t[p].l>r) return ;
	if(l<=t[p].l&&t[p].r<=r){
		t[p].tag+=val;
		t[p].min+=val;
		return ;
	}
	pushdown(p);
	int mid=t[p].l+t[p].r>>1;
	if(r<=mid) update(l,r,p<<1,val);
	else if(l>mid) update(l,r,p<<1|1,val);
	else update(l,mid,p<<1,val),update(mid+1,r,p<<1|1,val);
	t[p].min=min(t[p<<1].min,t[p<<1|1].min);
}
ll query(int l,int r,int p){
	if(l>t[p].r||t[p].l>r) return 1e18;
	if(l<=t[p].l&&t[p].r<=r) return t[p].min;
	pushdown(p);
	int mid=t[p].l+t[p].r>>1;
	if(r<=mid) return query(l,r,p<<1);
	if(l>mid) return query(l,r,p<<1|1);
	return min(query(l,mid,p<<1),query(mid+1,r,p<<1|1));
}
inline int lca(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		x=fa[top[x]];
	}
	return dep[x]<dep[y]?x:y;
}
int main(){
	n=in;q=in;
	for(int i=1;i<n;i++){
		int u=in,v=in;ll w=in;
		add(u,v,w);
	}
	for(int i=1;i<n;i++){
		int u=in,v=in;ll w=in;
		rec[i]=u;dis[u]=w;
	}
	dfs1(1);dfs2(1,1);
	build(1,n,1);
	while(q--){
		int opt=in;ll x=in,y=in;
		if(opt==1){
			if(x<=n-1) update(num[e[x].v],num[e[x].v]+siz[e[x].v]-1,1,y-e[x].w),e[x].w=y;
			else update(num[rec[x-n+1]],num[rec[x-n+1]],1,y-dis[rec[x-n+1]]),dis[rec[x-n+1]]=y;
		}else{
			if(x==y){
				puts("0");
				continue;
			}
			if(lca(x,y)==x) printf("%lld\n",query(num[y],num[y],1)-dis[y]-query(num[x],num[x],1)+dis[x]);
			else printf("%lld\n",query(num[y],num[y],1)+query(num[x],num[x]+siz[x]-1,1)-query(num[x],num[x],1)+dis[x]-dis[y]);
		}
	}
	return 0;
}
```