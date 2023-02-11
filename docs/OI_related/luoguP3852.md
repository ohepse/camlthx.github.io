### D1T3 Kinoman

#### Desciption

共有 $m$ 部电影，第 $i$ 部电影的好看值为 $w_i$。

在 $n$ 天之中,每天会放映一部电影，第 $i$ 天放映的是第 $f_i$ 部。

你可以选择 $l,r(1<=l<=r<=n)$，并观看第 $l,l+1,\dots,r$ 天内所有的电影。如果同一部电影你观看多于一次，你会感到无聊，于是无法获得这部电影的好看值。所以你希望最大化观看且仅观看过一次的电影的好看值的总和。

#### Solution:

第 $i$ 部电影对 $[pre_i+1,i]$ 区间有贡献。用线段树维护区间最大值。每次枚举右端点，每次操作时，将 $[pre_i+1,i]$ 加上 $w_i$ ,但是前面的贡献要减去，所以$[pre_{pre_i},pre_i]$ 减去 $w_i$ 。

#### Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn=1e6+10;
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
int n,m,f[maxn],nxt[maxn],pre[maxn];
ll ans=0,w[maxn];
struct tree{
	int l,r;
	ll tag,sum;
}t[maxn<<2];
void build(int l,int r,int p){
	t[p].l=l;t[p].r=r;
	if(l==r){
		t[p].sum=t[p].tag=0;
		return ;
	}
	int mid=l+r>>1;
	build(l,mid,p<<1);
	build(mid+1,r,p<<1|1);
}
void pushdown(int p){
	if(t[p].tag){
		t[p<<1].tag+=t[p].tag;
		t[p<<1|1].tag+=t[p].tag;
		t[p<<1].sum+=t[p].tag;
		t[p<<1|1].sum+=t[p].tag;
		t[p].tag=0;
	}
}
void update(int l,int r,int p,ll x){
	if(l<=t[p].l&&t[p].r<=r){
		t[p].sum=t[p].sum+x;t[p].tag=t[p].tag+x;
		return ;
	}
	pushdown(p);
	int mid=t[p].l+t[p].r>>1;
	if(l<=mid) update(l,r,p<<1,x);
	if(r>mid) update(l,r,p<<1|1,x);
	t[p].sum=max(t[p<<1].sum,t[p<<1|1].sum);
}
ll query(int l,int r,int p){
	if(l<=t[p].l&&t[p].r<=r) return t[p].sum;
	pushdown(p);
	int mid=t[p].l+t[p].r>>1;
	ll res=0;
	if(l<=mid) res=max(query(l,r,p<<1),res);
	if(r>mid) res=max(query(l,r,p<<1|1),res);
	return res;
}
int main(){
	n=in;m=in;
	for(int i=1;i<=n;i++) f[i]=in;
	for(int i=1;i<=m;i++) scanf("%lld",&w[i]);
	for(int i=1;i<=n;i++) pre[i]=nxt[f[i]],nxt[f[i]]=i;
	build(1,n,1);
	for(int i=1;i<=n;i++){
		ans=max(ans,t[1].sum);
		update(pre[i]+1,i,1,w[f[i]]);
		if(pre[i]) update(pre[pre[i]]+1,pre[i],1,-w[f[i]]);
		ans=max(ans,query(1,i,1));
	}
	printf("%lld\n",ans);
	return 0;
}
```