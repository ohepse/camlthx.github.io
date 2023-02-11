### D1T1 与或

#### Description：

对于一个长度为 $n$ 的序列，维护一下三个信息：

`1 l r v` ：将 $a_i,l\leq i \leq r$ 变为 $a_i \text{ and } v$

`2 l r v` ：将 $a_i,l\leq i \leq r$ 变为 $a_i \text{ or } v$

`3 l r ` ：求 $a_i,l\leq i \leq r$ 的最大值

#### Solution:

不会（逃

正解参考[idx巨佬的文章](https://blog.csdn.net/dreaming__ldx/article/details/80850136?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522167575663516782428622687%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=167575663516782428622687&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduend~default-3-80850136-null-null.142^v73^control,201^v4^add_ask,239^v1^control&utm_term=%E4%B8%8E%E6%88%96%E7%BA%BF%E6%AE%B5%E6%A0%91&spm=1018.2226.3001.4187)

#### Code:

这里使用的是暴力解法，可以过掉随机数据

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll int
const int maxn=2e5+10;
#define in read()
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
struct tree{
	ll l,r;
	ll max,min,tag;
}t[maxn<<2];
ll n,q,a[maxn],opt,l,r,x;
void pushup(int p){
	t[p].max=max(t[p<<1].max,t[p<<1|1].max);
	t[p].min=min(t[p<<1].min,t[p<<1|1].min);
}
void build(int l,int r,int p){
	t[p].l=l;t[p].r=r;t[p].max=t[p].min=0;t[p].tag=-1;
	if(l==r){
		t[p].max=t[p].min=t[p].tag=a[l];
		return ;
	}
	int mid=l+r>>1;
	build(l,mid,p<<1);
	build(mid+1,r,p<<1|1);
	pushup(p);
	//t[p].tag=t[p].max;
}
void pushdown(ll p){
	if(t[p].tag!=-1){
		t[p<<1].max=t[p<<1].min=t[p<<1].tag=t[p].tag;
		t[p<<1|1].max=t[p<<1|1].min=t[p<<1|1].tag=t[p].tag;
		t[p].tag=-1; 
	}
}
void updand(int l,int r,int p,int x){
	if(l<=t[p].l&&t[p].r<=r&&t[p].max==t[p].min){
		t[p].max&=x;t[p].min&=x;
		t[p].tag=t[p].max;
		return ;
	}
	pushdown(p);
	int mid=t[p].l+t[p].r>>1;
	if(l<=mid) updand(l,r,p<<1,x);
	if(r>mid) updand(l,r,p<<1|1,x);
	pushup(p);
} 
void updor(int l,int r,int p,int x){
	if(l<=t[p].l&&t[p].r<=r&&t[p].max==t[p].min){
		t[p].max|=x;t[p].min|=x;
		t[p].tag=t[p].max;
		return ;
	}
	pushdown(p);
	int mid=t[p].l+t[p].r>>1;
	if(l<=mid) updor(l,r,p<<1,x);
	if(r>mid) updor(l,r,p<<1|1,x);
	pushup(p);
} 
ll query(int l,int r,int p){
	if(l<=t[p].l&&t[p].r<=r) return t[p].max;
	pushdown(p);
	ll mid=t[p].l+t[p].r>>1;
	ll res=0;
	if(l<=mid) res=query(l,r,p<<1);
	if(r>mid) res=max(query(l,r,p<<1|1),res);
	return res; 
}
int main(){
	n=in;q=in;
	for(int i=1;i<=n;i++) a[i]=in;
	build(1,n,1);
	while(q--){
		opt=in;
		if(opt==1){
			l=in;r=in;x=in;
			updand(l,r,1,x);
			continue;
		}
		if(opt==2){
			l=in;r=in;x=in;
			updor(l,r,1,x);
			continue;
		}
		if(opt==3){
			l=in;r=in;
			printf("%d\n",query(l,r,1));
		}
	} 
	return 0;
}
```