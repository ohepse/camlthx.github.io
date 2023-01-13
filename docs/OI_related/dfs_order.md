感觉这个也算是个知识点但是到处都没有教程捏

[这里](https://loj.ac/d/1698)有一篇写的很好的关于dfs序的教程。

dfs序就是把树上问题转化为序列问题，从而通过树状数组或线段树进行维护。

dfs序本身不难理解，难的是与树状数组以及线段树结合，再加上巨大的码量。一下的四个例题码量平均100+。

**多码预警**

下面用一些例题讲解。

## 1.单点修改，子树查询

在dfs序中，$x$ 的子树在两次 $x$ 出现的中间，且是连续的。

所以问题就转化为序列上单点修改，区间查询。树状数组维护即可。

code：

```CPP
#include<bits/stdc++.h>
using namespace std;
#define in read()
#define ll long long
inline ll read(){
	ll x=0,f=1;char c=getchar();
	while(c>'9'||c<'0'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return x*f;
}
const int maxn=1e6+10;
int n,m,r,u,v,opt;
struct edge{
	int u,v,nxt;
}e[maxn<<1];
int cnt=0,h[maxn];
void add(int u,int v){
	e[++cnt]=(edge){u,v,h[u]};
	h[u]=cnt;
}
ll val[maxn],c[maxn<<1];
int lowbit(int x){
	return x&(-x); 
}
void update(int x,int v){
	while(x<=n){
		c[x]+=v;
		x+=lowbit(x);
	}
}
ll query(int x){
	ll res=0;
	while(x){
		res+=c[x];
		x-=lowbit(x);
	}
	return res;
}
int st[maxn],ed[maxn],tim=0;
bool vis[maxn];
void dfs(int x){
	st[x]=++tim;vis[x]=true;
	for(int i=h[x];i;i=e[i].nxt){
		int v=e[i].v;
		if(!vis[v]) dfs(v);
	}
	ed[x]=tim;
}
int main(){
	n=in;m=in;r=in;
	for(int i=1;i<=n;i++){
		val[i]=in;
	}
	for(int i=1;i<n;i++){
		u=in;v=in;
		add(u,v);add(v,u);
	}
	dfs(r);
	for(int i=1;i<=n;i++) update(st[i],val[i]);
	while(m--){
		opt=in;
		if(opt==1){
			u=in;v=in;
			update(st[u],v);
		}
		if(opt==2){
			u=in;
			printf("%lld\n",query(ed[u])-query(st[u]-1));
		}
	}
	return 0;
}
```

## 2.子树修改，子树查询

同理，问题可以转化为区间修改区间查询，很容易想到线段树对伐。然后就有了以下代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define in read()
#define ll long long
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c>'9'||c<'0'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return x*f;
}
const int maxn=1e6+10;
struct tree{
	int l,r;
	ll sum,tag;
}t[maxn<<1];
int n,m,r,u,v,opt;
struct edge{
	int u,v,nxt;
}e[maxn<<1];
int cnt=0,h[maxn];
void add(int u,int v){
	e[++cnt]=(edge){u,v,h[u]};
	h[u]=cnt;
}
int a[maxn<<1],val[maxn];
void build(int p,int l,int r){
	t[p].l=l;t[p].r=r;t[p].tag=0;
	if(l==r){
		t[p].sum=a[l];
		return ;
	}
	int mid=l+r>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	t[p].sum=t[p<<1].sum+t[p<<1|1].sum;
}
void pushdown(int p){
	if(t[p].tag){
		t[p<<1].sum+=t[p].tag*(t[p<<1].r-t[p<<1].l+1);
		t[p<<1|1].sum+=t[p].tag*(t[p<<1|1].r-t[p<<1|1].l+1);
		t[p<<1].tag+=t[p].tag;
		t[p<<1|1].tag+=t[p].tag;
		t[p].tag=0;
	}
}
void update(int l,int r,int p,int val){
	if(l<=t[p].l&&t[p].r<=r){
		t[p].sum+=val*(t[p].r-t[p].l+1);
		t[p].tag+=val;
		return ;
	}
	pushdown(p);
	int mid=t[p].l+t[p].r>>1;
	if(l<=mid) update(l,r,p<<1,val);
	if(r>mid) update(l,r,p<<1|1,val);
	t[p].sum=t[p<<1].sum+t[p<<1|1].sum; 
}
ll query(int l,int r,int p){
	if(l<=t[p].l&&t[p].r<=r) return t[p].sum;
	pushdown(p);
	int mid=t[p].l+t[p].r>>1;
	ll ans=0;
	if(l<=mid) ans+=query(l,r,p<<1);
	if(mid<r) ans+=query(l,r,p<<1|1);
	return ans; 
}
int st[maxn],ed[maxn],tim=0;
bool vis[maxn];
void dfs(ll x){
	st[x]=++tim;vis[x]=true;
	for(int i=h[x];i;i=e[i].nxt){
		ll v=e[i].v;
		if(!vis[v]) dfs(v);
	}
	ed[x]=tim;
}
int main(){
	n=in;m=in;r=in;
	for(int i=1;i<=n;i++) val[i]=in;
	for(int i=1;i<n;i++){
		u=in;v=in;
		add(u,v);add(v,u);
	}
	dfs(r);
	for(int i=1;i<=n;i++) a[st[i]]=val[i];
	build(1,1,n);
	while(m--){
		opt=in;
		if(opt==1){
			u=in;v=in;
			update(st[u],ed[u],1,v);
		}
		if(opt==2){
			u=in;
			printf("%lld\n",query(st[u],ed[u],1));
		}
	}
	return 0;
}
```

被WA、RE、MLE轮流搞废的线段树。

为什么呢？一看数据 $1e6$ 。

还是得转过头来考虑用树状数组维护。

设原数组为 $a_i$ , 差分数组为 $d_i$ 

则有： $a_x=\sum_{i=1}^x d_i$ 

要求：$\sum_{i=1}^{x}a_i$

联立得：$ans=\sum_{i=1}^x\sum_{j=1}^id_j=\sum_{i=1}^x(x-i+1)d_i=(x+1)*\sum_{i=1}^x-\sum_{i=1}^x i*d_i$

然后用两个树状数组分别维护即可。

code：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define in read()
#define ll long long
inline ll read(){
	ll x=0,f=1;char c=getchar();
	while(c>'9'||c<'0'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return x*f;
}
const int maxn=1e6+10;
ll n,m,r,u,v,opt;
struct edge{
	ll u,v,nxt;
}e[maxn<<1];
ll cnt=0,h[maxn];
void add(ll u,ll v){
	e[++cnt]=(edge){u,v,h[u]};
	h[u]=cnt;
}
ll val[maxn],c[maxn<<1][2],sum[maxn];
ll lowbit(ll x){
	return x&(-x); 
}
void update(ll x,ll v,ll k){
	while(x<=n){
		c[x][k]+=v;
		x+=lowbit(x);
	}
}
ll query(ll x,ll k){
	ll res=0;
	while(x){
		res+=c[x][k];
		x-=lowbit(x);
	}
	return res;
}
int st[maxn],ed[maxn],tim=0,dfn[maxn<<2];
bool vis[maxn];
void dfs(ll x,ll fa){
	st[x]=++tim;
	dfn[tim]=x;
	for(int i=h[x];i;i=e[i].nxt){
		int v=e[i].v;
		if(v!=fa) dfs(v,x);
	}
	ed[x]=tim;
}
int main(){
	n=in;m=in;r=in;
	for(int i=1;i<=n;i++) val[i]=in;
	for(int i=1;i<n;i++){
		u=in;v=in;
		add(u,v);add(v,u);
	}
	dfs(r,-1);
	for(int i=1;i<=n;i++) sum[i]=sum[i-1]+val[dfn[i]];
	while(m--){
		opt=in;
		if(opt==1){
			u=in;v=in;
			update(st[u],v,0);
			update(ed[u]+1,-v,0);
			update(st[u],st[u]*v,1);
			update(ed[u]+1,-v*(ed[u]+1),1);
		}
		if(opt==2){
			u=in;
			ll l=st[u],
			r=ed[u];
			ll ans=sum[r]-sum[l-1];
			printf("%lld\n",(r+1)*query(r,0)-
			l*query(l-1,0)-
			query(r,1)+
			query(l-1,1)+ans);
		}
	}
	return 0;
}
```

## 3.链上修改，单点查询，子树查询（树上差分）

单点查询和子树查询前文已经提过了

对于链上修改，每个点维护一个树上前缀和，那么答案就是 $val_x+val_y-val_{lca}-val_{fa_lca}$，这就是所谓的差分 。可以开两个树状数组，一个用来维护点权 $val_x$ ,一个用来维护前缀和。

对于单点查询和子树查询也可以用第一个树状数组解决。

题中还要求 $lca$，这里可以用欧拉序+$ST$ 表来求解，详细在代码中可以看到。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define in read()
#define ll long long
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c>'9'||c<'0'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return x*f;
}
const int maxn=1e6+10;
int n,m,r,u,v,opt;
struct edge{
	int u,v,nxt;
}e[maxn<<1];
int cnt=0,h[maxn];
void add(int u,int v){
	e[++cnt]=(edge){u,v,h[u]};
	h[u]=cnt;
}
int val[maxn];
struct bittree{
	ll c[maxn<<1];int siz;
	inline int lowbit(int x){
		return x&-x;
	}
	void update(int k,ll v){
		if(!k)return;
		while(k<=siz){
			c[k]+=v;k+=lowbit(k);
		}
	}
	ll query(int k){
		ll ans=0;
		while(k){
			ans+=c[k];k-=lowbit(k);
		}
		return ans;
	}
};
bittree A,B;
int st[maxn],ed[maxn],tim=0,dfn[maxn<<1],dep[maxn],fath[maxn];//dfn is used for getting euler order(?
void dfs(int x,int fa,int d){
	st[x]=++tim;
	dfn[tim]=x;
	dep[x]=d;
	fath[x]=fa;
	for(int i=h[x];i;i=e[i].nxt){
		int v=e[i].v;
		if(v==fa) continue;
		dfs(v,x,d+1);
		dfn[++tim]=x;
	}
	ed[x]=tim;
}
int f[maxn<<1][24];
int mmin(int a,int b){
	return dep[a]<dep[b]?a:b;
}
void STinit(int len){
	for(int i=1;i<=len;i++) f[i][0]=dfn[i];
	for(int j=1;(1<<j)<=len;j++){
		for(int i=1;i+(1<<j-1)<len;i++){
			f[i][j]=mmin(f[i][j-1],f[i+(1<<j-1)][j-1]);
		}
	}
}
int lca(int x,int y){
	x=st[x];y=st[y];
	if(x>y) swap(x,y);
	int k=0;
	while((1<<k+1)<=(y-x+1)) k++;
	return mmin(f[x][k],f[y-(1<<k)+1][k]);
}
signed main(){
	n=in;m=in;r=in;
	for(int i=1;i<=n;i++) val[i]=in;
	for(int i=1;i<n;i++){
		u=in;v=in;
		add(u,v);
		add(v,u);
	}
	dfs(r,0,0);
	A.siz=B.siz=tim;
	STinit(tim);
	for(int i=1;i<=n;i++){
		A.update(st[i],(ll)val[i]*(dep[i]+1));
        A.update(st[fath[i]],(ll)-val[i] *(dep[fath[i]]+1));
        B.update(st[i],(ll)val[i]);
        B.update(st[fath[i]],(ll)-val[i]);
	}
	while(m--){
		cin>>opt;
		if(opt==1){
			int x=in,y=in;int p=in;
			int LCA=lca(x,y);
			A.update(st[x],(ll)p*(dep[x]+1));
			A.update(st[y],(ll)p*(dep[y]+1));
			A.update(st[LCA],(ll)-p*(dep[LCA]+1));
			A.update(st[fath[LCA]],(ll)-p*(dep[fath[LCA]]+1));
			
			B.update(st[x],(ll)p);
			B.update(st[y],(ll)p);
			B.update(st[LCA],(ll)-p);
			B.update(st[fath[LCA]],(ll)-p);
		}
		if(opt==2){
			u=in;
			printf("%lld\n",B.query(ed[u])-B.query(st[u]-1));
		}
		if(opt==3){
			u=in;
			printf("%lld\n",A.query(ed[u])-A.query(st[u]-1)-(ll)dep[u]*(B.query(ed[u])-B.query(st[u]-1)));
		}
	}
	return 0;
}
```

## 4.单点修改，子树修改，链上查询

**解法** ：分开考虑两个修改问题，所以先考虑分成修改点权+查询链和修改子树+查询链两个子问题。

**子问题** **1** ：修改点权+查询链可以通过维护每个点到根这条链的点权和来实现。这样，修改点权相当于修改子树，查询链相当于查询点权，然后通过树上差分实现查询任意链的点权和。如对于修改点 $x$ ,则修改  $st[x]+v$ , $[ed[x]+1]-v$，这样，查询x即得到 $[root,x]$ 的路径值。

**子问题** **2** ：修改子树+查询链，通过维护每个点x 到根这条链的点权和 $v[x]$ 。设 $y$ 在 $x$ 子树中，询问点为 $y$ ，$dep[x]$ 表示 $x$ 的深度，对于 $x$ 点权修改，对 $y$ 的影响为 $w*(dep[y]-dep[x]+1)=w*dep[y] – w*(dep[x]-1)$，发现第二项与 $y$ 无关。$-w*(dep[x]-1)$ 用一颗树状数组维护，同时与子问题1一起使用。w值以一颗树状数组维护。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
#define ll long long
int dep[N],st[N],ed[N],fa[N][22];
int n,m,r,cnt=0;
int a[N];
struct Bit{
    ll c[N];int siz;
    inline int lowbit(int x){
		return x&-x;
	}
	Bit(int siz=0):siz(siz){
		memset(c,0,sizeof(c));
	}
	void add(int k,ll v){
		if(!k)return;
		while(k<=siz){
			c[k]+=v;k+=lowbit(k);
		}
	}
	ll sum(int k){
		ll ans=0;
		while(k){
			ans+=c[k];k-=lowbit(k);
		}
		return ans;
	}
}w1,w2;//树状数组 
struct node{
    int u,v;
}g[N*2];
int nxt[N*2],first[N],tot=0;
inline void add(int u,int v){
    g[++tot].u=u;g[tot].v=v;
    nxt[tot]=first[u];first[u]=tot;
}
int lca(int u,int v){
    if(dep[u]<dep[v])swap(u,v);
    for(int i=20;i>=0;i--){
        if(dep[fa[u][i]]>=dep[v])u=fa[u][i];
        if(u==v)return u;
    }
    for(int i=20;i>=0;i--){
        if(fa[u][i]!=fa[v][i]){
            u=fa[u][i];
            v=fa[v][i];
        }
    }
    return fa[u][0];
}
void dfs(int u,int f){
    st[u]=++cnt;
    dep[u]=dep[f]+1;
    fa[u][0]=f;
    for(int i=1;i<21;i++){
        fa[u][i]=fa[fa[u][i-1]][i-1];
    }
    for(int i=first[u];i;i=nxt[i]){
        int v=g[i].v;
        if(f==v)continue;
        dfs(v,u);
    }
    ed[u]=cnt;
}
ll query(int x){
    return w1.sum(st[x])+w2.sum(st[x])*dep[x];
}
ll ask(int x,int y){
    int LCA=lca(x,y); 
   // cout<<w1.sum(st[x])<<endl;
    return query(x)+query(y)-query(LCA)-query(fa[LCA][0]);
}
int main(){
    scanf("%d%d%d",&n,&m,&r);
    w1.siz=w2.siz=n;
    for(int i=1;i<=n;i++)scanf("%d",a+i);
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v);add(v,u);
    }
    dfs(r,0);
    for(int i=1;i<=n;i++){
        w1.add(st[i],(ll)a[i]);
        w1.add(ed[i]+1,(ll)-a[i]);
    }
    while(m--){
        int op,x,y;
        scanf("%d%d%d",&op,&x,&y);
        if(op==1){
            w1.add(st[x],(ll)y);
            w1.add(ed[x]+1,(ll)-y);
        }else if(op==2){
            w1.add(st[x],(ll)-y*(dep[x]-1));
            w1.add(ed[x]+1,(ll)y*(dep[x]-1));
            w2.add(st[x],(ll)y);
            w2.add(ed[x]+1,(ll)-y);
        }else{
            printf("%lld\n",ask(x,y));
        }
    }
    return 0;
}

```







