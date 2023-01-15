## description

[传送门](https://www.luogu.com.cn/problem/P2839)

丽洁还是很吊的

这道题我还尚未完全摸透做法，所以仅作为一道好题放在这里

代码难度不大，但是思维含量极高

但我是绝对不会说我的 $queryrmax$ 和 $querylaxm$ 函数因为是复制粘贴的所以 debug 了一个小时（逃

~~说不定几万年后我 AKIOI 之后再回来看就明白了呢~~

## solution

首先对于每一个询问可以进行二分答案。

然后考虑求中位数。一个小套路：==**将所有大于等于 $mid$ 的设为 1，小于的设为 -1，当区间和为 0 的时候就 $mid$ 就是中位数**==。为了选择更大的中位数，所以要尽可能多选择 1。（why？）那么就要维护一个最长子序列。

对于每一个询问都要开一个线段树，那么肯定选择主席树啦（why？）。每个节点维护一个区间和，区间最大前缀和区间最大后缀。

code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e4+10;
struct anss{
	int val,pos;
}s[maxn];
bool cmp(anss a,anss b){
	return a.val<b.val;
}
int n,q,askk[5],lastans=0,a,b,c,d;
int tot=0,sum[maxn<<5],lmax[maxn<<5],rmax[maxn<<5],ls[maxn<<5],rs[maxn<<5],root[maxn];
void pushup(int p){
	sum[p]=sum[ls[p]]+sum[rs[p]];
	lmax[p]=max(lmax[ls[p]],sum[ls[p]]+lmax[rs[p]]);
    rmax[p]=max(rmax[rs[p]],sum[rs[p]]+rmax[ls[p]]);
}
void build(int &rt,int l,int r){
	rt=++tot;
	if(l==r){
		sum[rt]=lmax[rt]=rmax[rt]=1;
		return ;
	}
	int mid=l+r>>1;
	build(ls[rt],l,mid);
	build(rs[rt],mid+1,r);
	pushup(rt);
}
void update(int &rt,int l,int r,int x){
	sum[++tot]=sum[rt],ls[tot]=ls[rt],rs[tot]=rs[rt];rt=tot;
	if(l==r){
		sum[rt]=-1;
		lmax[rt]=max(0,sum[rt]);
		rmax[rt]=max(0,sum[rt]);
		return ;
	}
	int mid=l+r>>1;
	if(x<=mid) update(ls[rt],l,mid,x);
	else update(rs[rt],mid+1,r,x);
	pushup(rt);
}
int querysum(int p,int l,int r,int ql,int qr){
	if(ql>qr) return 0;
	if(ql<=l&&r<=qr) return sum[p];
	int mid=l+r>>1,ans=0;
	if(ql<=mid) ans+=querysum(ls[p],l,mid,ql,qr);
	if(mid<qr) ans+=querysum(rs[p],mid+1,r,ql,qr);
	return ans;
}
int querylmax(int p,int l,int r,int ql,int qr){
	if(ql>qr) return 0;
	if(ql<=l&&r<=qr) return lmax[p];
	int mid=l+r>>1,ans=0;
	if(ql<=mid) ans=querylmax(ls[p],l,mid,ql,qr);
	if(mid<qr) ans=max(ans,querylmax(rs[p],mid+1,r,ql,qr)+querysum(ls[p],l,mid,ql,mid));
	return ans; 
}
int queryrmax(int p,int l,int r,int ql,int qr){
	if(ql>qr) return 0;
	if(ql<=l&&r<=qr) return rmax[p];
	int mid=l+r>>1,ans=0;
	if(qr>mid) ans=queryrmax(rs[p],mid+1,r,ql,qr);
	if(ql<=mid) ans=max(ans,queryrmax(ls[p],l,mid,ql,qr)+querysum(rs[p],mid+1,r,mid+1,qr));
	return ans; 
}
bool check(int mid){
	int res=0;
	res=queryrmax(root[mid],1,n,a,b-1);
	res+=querylmax(root[mid],1,n,c+1,d);
	res+=querysum(root[mid],1,n,b,c);
	return res>=0;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&s[i].val);
		s[i].pos=i;
	}
	sort(s+1,s+1+n,cmp);
	build(root[1],1,n);
	for(int i=2;i<=n;i++){
		root[i]=root[i-1];
		update(root[i],1,n,s[i-1].pos);//为什么是s[i-1]而不是s[i]?
	}
	scanf("%d",&q);
	while(q--){
		for(int i=0;i<4;i++) scanf("%d",&askk[i]);
		for(int i=0;i<4;i++) askk[i]=(askk[i]+lastans)%n+1;
		sort(askk,askk+4);
		a=askk[0];b=askk[1];c=askk[2];d=askk[3];
		int l=1,r=n,ans=0;
		while(l<=r){
			int mid=l+r>>1;
			if(check(mid)){
				ans=mid;
				l=mid+1;
			}
			else r=mid-1;
		}
		lastans=s[ans].val;
		printf("%d\n",lastans);
	}
	return 0;
}
```

## 一些启发

对于主席树，因为它的本质就是线段树。对于操作中下传的 $rt$ 或 $p$ ，本质上就相当于线段树中下传节点的操作。只不过线段树可以直接用 $p<<1$ 和 $p<<1|1$ 的操作完成，而主席树要调用以前保存的数据罢辽。