[传送门](https://www.luogu.com.cn/problem/P2048)

### Description:

有一个长度为 $n$ 的序列，从中选出 $k$ 个长度为 $l \leq k \leq r$ 的不同的区间，使得区间和最大。

### Solution：

前缀和+堆+RMQ

首先前缀和优化区间和。

以区间最大值为关键字建立大根堆 ，枚举左端点，查找 $[l,r]$ 区间加入堆中。然后循环 $k$ 次，每次取出堆顶，累加贡献，间 $[l,pos-1]$ 和 $[pos+1,r]$ 加入堆， $pos$ 代表 $[l,r]$ 区间中最大值的位置。

### Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn=5e5+10;
int n,k,l,r,logn[maxn],f[maxn][24];
ll a[maxn];
void pre(){
	logn[1]=0;
	logn[2]=1;
	for(int i=3;i<=n;i++) logn[i]=logn[i>>1]+1;
}
int mmax(int x,int y){
	return a[x]>a[y]?x:y;
} 
void init(){
	for(int i=1;i<=n;i++) f[i][0]=i;
	for(int j=1;(1<<j)<=n;j++){
		for(int i=1;i+(1<<j)-1<=n;i++){
			f[i][j]=mmax(f[i][j-1],f[i+(1<<j-1)][j-1]);
		}
	}
}
int query(int l,int r){
	int k=logn[r-l+1];
	return mmax(f[l][k],f[r-(1<<k)+1][k]);
}
struct node{
	int pos,l,r,id;
	ll val;
	friend bool operator <(const node &a,const node &b){
		return a.val<b.val;
	}
};
priority_queue<node> q; 
int main(){
	scanf("%d%d%d%d",&n,&k,&l,&r);
	pre();
	for(int i=1;i<=n;i++){
		scanf("%lld",a+i);
		a[i]+=a[i-1];
	}
	init();
	for(int i=1;i+l-1<=n;i++){
		int lmax=i+l-1,rmax=i+r-1;
		if(rmax>n) rmax=n;
		int ppos=query(lmax,rmax);
		ll tmp=a[ppos]-a[i-1];
		q.push((node){i,lmax,rmax,ppos,tmp});
	}
	ll ans=0;
	for(int i=1;i<=k;i++){
		node x=q.top();q.pop();
		ans+=x.val;
		if(x.l!=x.id){
			int ppos=query(x.l,x.id-1);
			q.push((node){x.pos,x.l,x.id-1,ppos,a[ppos]-a[x.pos-1]});
		}
		if(x.r!=x.id){
			int ppos=query(x.id+1,x.r);
			q.push((node){x.pos,x.id+1,x.r,ppos,a[ppos]-a[x.pos-1]});
		}
	}
	printf("%lld\n",ans);
	return 0;
} 
```



