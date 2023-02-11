### D1T4 Hotel

#### Description：

对于一个01序列，维护两个值：

`1 x` 找出长度为 $x$ 的区间变为 1，并输出最左的一个左端点。

`2 l r` 将 $[l,r]$ 变成 0。

#### Solution：

对于操作 1，用线段树维护最长子段和，在 `query` 函数里的查询操作改为

```cpp
int query(int l,int r,int p,int length){
	pushdown(p);
	int mid=t[p].l+t[p].r>>1;
	if(t[p<<1].sum>=length) return query(l,r,p<<1,length);
	if(t[p<<1].rmax+t[p<<1|1].lmax>=length) return mid-t[p<<1].rmax+1;
	return query(l,r,p<<1|1,length);
}
```

对于操作 2，区间赋值操作即可

#### Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=5e4+10;
struct tree{
	int l,r,lmax,rmax,sum,tag,len;
};
tree t[maxn<<2];
int n,m,opt,x,d;
void pushup(int p){
	if(t[p<<1].len==t[p<<1].sum) t[p].lmax=t[p<<1].len+t[p<<1|1].lmax;
	else t[p].lmax=t[p<<1].lmax;
	if(t[p<<1|1].len==t[p<<1|1].sum) t[p].rmax=t[p<<1].rmax+t[p<<1|1].len;
	else t[p].rmax=t[p<<1|1].rmax;
	t[p].sum=max(max(t[p<<1].sum,t[p<<1|1].sum),t[p<<1].rmax+t[p<<1|1].lmax);
}
void build(int l,int r,int p){
	t[p].l=l;t[p].r=r;t[p].tag=0;t[p].sum=t[p].len=t[p].lmax=t[p].rmax=r-l+1;
	if(l==r){
		return ;
	}
	int mid=l+r>>1;
	build(l,mid,p<<1);
	build(mid+1,r,p<<1|1);
	pushup(p);
}
void pushdown(int p){
	if(t[p].tag==0) return ;
	t[p<<1].tag=t[p<<1|1].tag=t[p].tag;
	if(t[p].tag==1){
		t[p<<1].sum=t[p<<1].lmax=t[p<<1].rmax=0;
		t[p<<1|1].sum=t[p<<1|1].lmax=t[p<<1|1].rmax=0;
	}
	if(t[p].tag==2){
		t[p<<1].sum=t[p<<1].lmax=t[p<<1].rmax=t[p<<1].len;
		t[p<<1|1].sum=t[p<<1|1].lmax=t[p<<1|1].rmax=t[p<<1|1].len;
	}
	t[p].tag=0;
}
void update(int l,int r,int p,int opt){
	if(l<=t[p].l&&t[p].r<=r){
		if(opt==1) t[p].sum=t[p].lmax=t[p].rmax=0;
		else t[p].sum=t[p].lmax=t[p].rmax=t[p].len;
		t[p].tag=opt;
		return ;
	}
	pushdown(p);
	int mid=t[p].l+t[p].r>>1;
	if(l<=mid) update(l,r,p<<1,opt);
	if(r>mid) update(l,r,p<<1|1,opt);
	pushup(p);
}
int query(int l,int r,int p,int length){
	pushdown(p);
	int mid=t[p].l+t[p].r>>1;
	if(t[p<<1].sum>=length) return query(l,r,p<<1,length);
	if(t[p<<1].rmax+t[p<<1|1].lmax>=length) return mid-t[p<<1].rmax+1;
	return query(l,r,p<<1|1,length);
}
int main(){
	scanf("%d%d",&n,&m);
	build(1,n,1);
	for(int i=1;i<=m;i++){
		scanf("%d",&opt);
		if(opt==1){
			scanf("%d",&d);
			if(t[1].sum<d){
				puts("0");
				continue;
			}
			int ans=query(1,n,1,d);
			printf("%d\n",ans);
			update(ans,ans+d-1,1,1);
		}
		if(opt==2){
			scanf("%d%d",&x,&d);
			update(x,x+d-1,1,2);
		}
	}
	return 0;
}
```