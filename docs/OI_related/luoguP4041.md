### D2T3 「AHOI2014」奇怪的计算器

#### Desciption:

[传送门](https://www.luogu.com.cn/problem/P4041)

#### Solution:

如果我们先抛去 $L,R$ 的限制，很容易联想到这是个线段树的板子。

然后如果加上限制，考虑如何修改。如果我们将序列排序，操作也不hi影响序列的单调性。所以我们可以二分出一个位置，及恰好到达边界的位置。对于没超过限制的部分直接修改，超过限制区间直接覆盖即可。因为线段树`query` 操作的本质就就是二分，所以不需要额外二分。对于区间覆盖，维护一个最大最小值即可判断。

代码中有两个细节需要注意：

1. 注意几个运算有优先级，覆盖操作>乘法操作>加减和那个奇怪的操作。
2. 在运算时因为是给整个序列更改，所以直接俄打标记即可。

但其实对于所有的操作都可以化成一个操作，仍然是[idx巨佬的文章](https://ldxkelkel.blog.luogu.org/solution-p4041)

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
#define in read()
#define ll long long
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
struct ask{
	int opt,num;
}q[maxn];
struct number{
	ll num;
	int id;
}a[maxn];
int n,m,L,R;
ll ans[maxn];
char op;
bool cmp(number a,number b){
	return a.num<b.num;
}
struct tree{
	int l,r;
	ll max,min,add,mul,at,cover;
}t[maxn<<2];
void build(int l,int r,int p){
	t[p].l=l;t[p].r=r;t[p].mul=1;
	t[p].add=t[p].at=t[p].cover=0;
	if(l==r){
		t[p].max=a[l].num;
		t[p].min=a[l].num;
		return ;
	}
	int mid=l+r>>1;
	build(l,mid,p<<1);
	build(mid+1,r,p<<1|1);
	t[p].max=max(t[p<<1].max,t[p<<1|1].max);
	t[p].min=min(t[p<<1].min,t[p<<1|1].min);
}
void pushadd(int p,ll val){
	t[p].max+=val;
	t[p].min+=val;
	t[p].add+=val;
}
void pushmul(int p,ll val){
	t[p].max*=val;
	t[p].min*=val;
	t[p].mul*=val;
	t[p].add*=val;
	t[p].at*=val;
}
void pushat(int p,ll val){
	t[p].max+=a[t[p].r].num*val;
	t[p].min+=a[t[p].l].num*val;
	t[p].at+=val;
}
void pushcover(int p,ll val){
	t[p].max=val;
	t[p].min=val;
	t[p].cover=val;
	t[p].add=0;
	t[p].at=0;
	t[p].mul=1;
}
void pushdown(int p){
	if(t[p].cover){
		pushcover(p<<1,t[p].cover);
		pushcover(p<<1|1,t[p].cover);
		t[p].cover=0;
	}
	if(t[p].mul!=1){
		pushmul(p<<1,t[p].mul);
		pushmul(p<<1|1,t[p].mul);
		t[p].mul=1;
	}
	if(t[p].add){
		pushadd(p<<1,t[p].add);
		pushadd(p<<1|1,t[p].add);
		t[p].add=0;
	}
	if(t[p].at){
		pushat(p<<1,t[p].at);
		pushat(p<<1|1,t[p].at);
		t[p].at=0;
	}
}
void updmin(int l,int r,int p){
	if(t[p].max<L) pushcover(p,L);
	if(t[p].min>R) pushcover(p,R);
	if(l==r) return ;
	pushdown(p);
	int mid=l+r>>1;
	updmin(l,mid,p<<1);
	if(t[p<<1|1].min<L)updmin(mid+1,r,p<<1|1);
	t[p].max=max(t[p<<1].max,t[p<<1|1].max);
	t[p].min=min(t[p<<1].min,t[p<<1|1].min);
}
void updmax(int l,int r,int p){
	if(t[p].max<L) pushcover(p,L);
	if(t[p].min>R) pushcover(p,R);
	if(l==r) return ;
	pushdown(p);
	int mid=l+r>>1;
	if(t[p<<1].max>R) updmax(l,mid,p<<1);
	updmax(mid+1,r,p<<1|1);
	t[p].max=max(t[p<<1].max,t[p<<1|1].max);
	t[p].min=min(t[p<<1].min,t[p<<1|1].min);
}
void query(int l,int r,int p){
	if(l==r){
		ans[a[l].id]=t[p].max;
		return ;
	}
	pushdown(p);
	int mid=l+r>>1;
	query(l,mid,p<<1);
	query(mid+1,r,p<<1|1);
}
int main(){
	//freopen("calc1.in","r",stdin);
	n=in;L=in;R=in;
	for(int i=1;i<=n;i++){
		cin>>op;
		if(op=='+') q[i].opt=1;
		if(op=='-') q[i].opt=2;
		if(op=='*') q[i].opt=3;
		if(op=='@') q[i].opt=4;
		q[i].num=(ll)in;
	}
	m=in;
	for(int i=1;i<=m;i++) a[i].num=in,a[i].id=i;
	sort(a+1,a+1+m,cmp);
	build(1,m,1);
	for(int i=1;i<=n;i++){
		if(q[i].opt==1) pushadd(1,q[i].num);
		if(q[i].opt==2) pushadd(1,-q[i].num);
		if(q[i].opt==3) pushmul(1,q[i].num);
		if(q[i].opt==4) pushat(1,q[i].num);
		updmax(1,m,1);
		updmin(1,m,1);
	}
	query(1,m,1);
	for(int i=1;i<=m;i++) printf("%lld\n",ans[i]);
	return 0;
}
```