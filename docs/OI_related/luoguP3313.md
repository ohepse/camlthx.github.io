### D4T1 [SDOI2014]旅行

[传送门](https://www.luogu.com.cn/problem/P3313)

#### Desciption:

给定一颗 $n$ 个节点的树，每个节点都有一个权值和一种颜色。

有 $q$ 个询问：

`CC x c` 将节点 $x$ 的颜色改为 $c$

`CW x w` 将节点 $x$ 的权值改为 $w$

`QS x y` 询问 $<x,y>$ 路径上与 $x,y$ 颜色相同的点的权值和

`QM x y` 询问 $<x,y>$ 路径上与 $x,y$ 颜色相同的点的最大权值

#### Solution:

首先明确肯定用树剖来维护询问和修改。

对于每一个宗教我们都要开一颗线段树来维护，所以考虑用主席树。

主席树+树剖，其他的与线段树+树剖一样。

#### Hint:

1. 查询最大最小值得时候记得加上`if(qr<l||ql>r) return 0;`，不然不晓得飞到哪里去。
2. 主席树的空间玄学问题。本题的 $maxn$ 为 $1e^5$ ，理论上要开到 $maxn<<7$ 的范围才保险，但是 SLOJ上 $maxn<<6$ 才能过。

#### Code:

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
ll vall;
int n,m;
int dep[maxn],siz[maxn],hson[maxn],fa[maxn],w[maxn],c[maxn];
int dfn[maxn],num[maxn],top[maxn],tot=0,len=0,root[maxn];
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
	dfn[tot]=x;
	if(hson[x]) dfs2(hson[x],tp);
	for(int i=h[x];i;i=e[i].nxt){
		int v=e[i].v;
		if(v!=fa[x]&&hson[x]!=v) dfs2(v,v);
	}
}
struct tree{
	int l,r,max,sum;
}t[20000110];
void upd(int &rt,int w,int l,int r,int pos){
	if(!rt) rt=++len;
	t[rt].max=max(t[rt].max,w);
	t[rt].sum=t[rt].sum+w;
	if(l==r) return ;
	int mid=l+r>>1;
	if(pos<=mid) upd(t[rt].l,w,l,mid,pos);
	else upd(t[rt].r,w,mid+1,r,pos);
}
void cls(int &rt,int l,int r,int pos){
	if(l==r){
		t[rt].max=t[rt].sum=0;
		return ;
	}
	int mid=l+r>>1;
	if(pos<=mid) cls(t[rt].l,l,mid,pos);
	else cls(t[rt].r,mid+1,r,pos);
	t[rt].max=max(t[t[rt].l].max,t[t[rt].r].max);
	t[rt].sum=t[t[rt].l].sum+t[t[rt].r].sum;
}
int querymax(int rt,int l,int r,int ql,int qr){
	if(qr<l||ql>r) return 0;
	if(ql<=l&&r<=qr) return t[rt].max;
	int mid=l+r>>1;
	return max(querymax(t[rt].l,l,mid,ql,qr),querymax(t[rt].r,mid+1,r,ql,qr));
}
int querysum(int rt,int l,int r,int ql,int qr){
	if(qr<l||ql>r) return 0;
	if(ql<=l&&r<=qr) return t[rt].sum;
	int mid=l+r>>1;
	return querysum(t[rt].l,l,mid,ql,qr)+querysum(t[rt].r,mid+1,r,ql,qr);
}
int getmax(int x,int y,int reli){
	int ans=-0x3f3f3f3f;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		ans=max(ans,querymax(root[reli],1,n,num[top[x]],num[x]));
		x=fa[top[x]];
	}
	if(dep[x]<dep[y]) swap(x,y);
	ans=max(ans,querymax(root[reli],1,n,num[y],num[x]));
	return ans;
}
int getsum(int x,int y,int reli){
	int ans=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		ans+=querysum(root[reli],1,n,num[top[x]],num[x]);
		x=fa[top[x]];
		
	}
	if(dep[x]<dep[y]) swap(x,y);//cout<<x<<" "<<y<<endl;
	ans+=querysum(root[reli],1,n,num[y],num[x]);
	return ans;
}
int main(){
	n=in;m=in;
	for(int i=1;i<=n;i++){
		w[i]=in;c[i]=in;
	}
	for(int i=1;i<n;i++){
		int x=in,y=in;
		add(x,y);add(y,x);
	}
	dfs1(1,0);dfs2(1,1);
	for(int i=1;i<=n;i++){
		upd(root[c[i]],w[i],1,n,num[i]);
	}
	char opt[10];
	while(m--){
		scanf("%s",opt);
		int x=in,y=in;
		if(opt[0]=='C'&&opt[1]=='C'){
			cls(root[c[x]],1,n,num[x]);
			upd(root[y],w[x],1,n,num[x]);
			c[x]=y;
			continue;
		}
		if(opt[0]=='C'&&opt[1]=='W'){
			cls(root[c[x]],1,n,num[x]);
			upd(root[c[x]],y,1,n,num[x]);
			w[x]=y;
			continue;
		}
		if(opt[0]=='Q'&&opt[1]=='S'){//cout<<"debug"<<endl;
			printf("%d\n",getsum(x,y,c[x]));
			continue;
		}
		printf("%d\n",getmax(x,y,c[x]));
	}
	return 0;
}
```