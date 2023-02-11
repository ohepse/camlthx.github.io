### D3T1 层流

#### Description：

对于一个全集 $U$ ，$A,B$ 是它的两个子集，如果 $A \subseteq B$ 或 $B \subseteq A$ 或 $A \cap B = \emptyset$ ，则称 $A,B$ 是 $U$ 的两个层流集。

给定一棵树，$U$ 为树上所有点构成的集合。将两点间的简单路径 $<u,v>$ 经过的点视作一个集合，求给出的 $m$ 对 $<u,v>$ 判断是否满足任意两个集合都是 $U$ 的层流集。  

#### Solution：

考虑染色。先将询问按集合大小从大到小排序，这样可以将问题转化为小区间包含大区间的问题。对于每个集合染色前，判断 $<u,v>$ 上如果有2种及以上的颜色，那么就不符合。

染色过程与[[SDOI2011]染色](https://www.luogu.com.cn/problem/P2486)相同。~~早知道就直接复制这个代码了~~

#### Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
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
struct edge{
	int u,v,nxt;
}e[maxn<<1];
int cnt=0,h[maxn];
void add(int u,int v){
	e[++cnt]=(edge){u,v,h[u]};
	h[u]=cnt; 
}
struct tree{
	int l,r,tag,cnt,lc,rc;
}t[maxn<<2];
int dep[maxn],num[maxn],fa[maxn],siz[maxn],hson[maxn],top[maxn],pred[maxn],tot=0;
void dfs1(int x,int father){
	siz[x]=1;
	hson[x]=0;
	for(int i=h[x];i;i=e[i].nxt){
		int v=e[i].v;
		if(v==father) continue; 
		dep[v]=dep[x]+1;
		fa[v]=x;
		dfs1(v,x);
		siz[x]+=siz[v];
		if(siz[hson[x]]<siz[v]) hson[x]=v;
	}
}
void dfs2(int x,int tp){
	top[x]=tp;
	num[x]=++tot;
	pred[tot]=x; 
	if(hson[x]) dfs2(hson[x],tp);
	for(int i=h[x];i;i=e[i].nxt){
		int v=e[i].v;
		if(v!=fa[x]&&hson[x]!=v) dfs2(v,v);
	}
}
int LC,RC,n,m,u,v,tt,w[maxn];
char opt;
void pushup(int p){
	t[p].cnt=t[p<<1].cnt+t[p<<1|1].cnt;
	if(t[p<<1].rc==t[p<<1|1].lc) t[p].cnt--;
	t[p].lc=t[p<<1].lc;t[p].rc=t[p<<1|1].rc;
}
void build(int l,int r,int p){
	t[p].l=l;t[p].r=r;t[p].tag=0;
	if(l==r){
		t[p].lc=t[p].rc=w[pred[l]];
		t[p].cnt=1;
		return ;
	}
	int mid=l+r>>1;
	build(l,mid,p<<1);
	build(mid+1,r,p<<1|1);
	pushup(p);
}
void pushdown(int p){
	if(t[p].tag){
		t[p<<1].lc=t[p<<1].rc=t[p<<1].tag=t[p].tag;
		t[p<<1].cnt=1;
		t[p<<1|1].lc=t[p<<1|1].rc=t[p<<1|1].tag=t[p].tag;
		t[p<<1|1].cnt=1;
		t[p].tag=0;
	}
}
void update(int l,int r,int p,int val){
	if(l<=t[p].l&&t[p].r<=r){
		t[p].lc=t[p].rc=t[p].tag=val;
		t[p].cnt=1;
		return ;
	}
	pushdown(p);
	int mid=t[p].l+t[p].r>>1;
	if(l<=mid) update(l,r,p<<1,val);
	if(r>mid) update(l,r,p<<1|1,val);
	pushup(p); 
}
int query(int l,int r,int p){
	if(l<=t[p].l&&t[p].r<=r){
		if(t[p].l==l) LC=t[p].lc;
		if(t[p].r==r) RC=t[p].rc;
		return t[p].cnt;
	}	
	pushdown(p);
	int mid=t[p].l+t[p].r>>1;
	if(r<=mid) return query(l,r,p<<1);
	if(l>mid) return query(l,r,p<<1|1);
	int ans=query(l,r,p<<1)+query(l,r,p<<1|1);
	if(t[p<<1].rc==t[p<<1|1].lc) ans--;
	return ans;
}
void upd(int x,int y,int val){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		update(num[top[x]],num[x],1,val);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y]) swap(x,y);
	update(num[x],num[y],1,val);
}
int getsum(int x,int y){
	int res=0,ansl=0,ansr=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y),swap(ansl,ansr);
		res+=query(num[top[x]],num[x],1);
		if(RC==ansl) res--;
		ansl=LC;
		x=fa[top[x]];
	} 
	if(dep[x]>dep[y]) swap(x,y),swap(ansl,ansr);
	res+=query(num[x],num[y],1);
	if(ansl==LC) res--;
	if(ansr==RC) res--;
	return res;
}
int lca(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		x=fa[top[x]];
	}
	if(dep[x]<dep[y]) swap(x,y);
	return y;
}
struct sett{
	int u,v,lcaa,len;
}s[maxn];
bool cmp(sett a,sett b){
	return a.len>b.len;
}
int main(){
	n=in;m=in;
	for(int i=1;i<=n;i++) w[i]=1;
	for(int i=1;i<n;i++){
		u=in;v=in;
		add(u,v);add(v,u);
	}
	dfs1(1,0);
	dfs2(1,1);
	build(1,tot,1);
	for(int i=1;i<=m;i++){
		s[i].u=in;s[i].v=in;
		s[i].lcaa=lca(s[i].u,s[i].v);
		s[i].len=dep[s[i].u]+dep[s[i].v]-2*dep[s[i].lcaa]+1;
	}
	sort(s+1,s+1+m,cmp);
	int col=1;
	for(int i=1;i<=m;i++){
		if(getsum(s[i].u,s[i].v)>1){
			puts("No");
			return 0;
		}
		col++;
		upd(s[i].u,s[i].v,col);
	}
	puts("Yes");
	return 0;
}
```