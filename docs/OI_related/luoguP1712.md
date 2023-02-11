### D2T1 [NOI2016]区间

#### Desciption:

有 $n$ 个闭区间 $[l_i,r_i]$ ，从中选出 $m$ 个区间，使得存在 $x$ ,使得每个被选择的区间都有 $l_i \leq x \leq r_i$。

选择一个合法的方案，它的花费为最长的区间长度减去最短区间长度，定义区间长度为 $r_i-l_i$。

求最小的花费，如果没有合法方案则输出 $-1$ 。

#### Solution:

考虑先将区间按照花费从小到大排序，然后用尺取法加线段树维护即可。

#### Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=5e5+10;
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
struct point{
	int val,id;
}p[maxn<<2];
struct seg{
	int l,r,len,id;
}a[maxn<<2];
bool cmp2(seg a,seg b){
	return a.len<b.len;
}
bool cmp1(point a,point b){
	return a.val<b.val;
}
int n,m,tot=0,ll[maxn<<1],rr[maxn<<1];
struct tree{
	int l,r,val,tag;
}t[maxn<<3];
void pushdown(int p){
	if(t[p].tag){
		t[p<<1].val+=t[p].tag;
		t[p<<1|1].val+=t[p].tag;
		t[p<<1].tag+=t[p].tag;
		t[p<<1|1].tag+=t[p].tag;
		t[p].tag=0;
	}
	return ;
} 
void update(int l,int r,int ql,int qr,int p,int val){
	if(l>qr||r<ql) return ; 
	if(ql<=l&&r<=qr){
		t[p].val+=val;t[p].tag+=val;
		return ;
	}
	pushdown(p);
	int mid=l+r>>1;
	//if(ql<=mid) 
	update(l,mid,ql,qr,p<<1,val);
	//if(qr>mid) 
	update(mid+1,r,ql,qr,p<<1|1,val);
	t[p].val=max(t[p<<1].val,t[p<<1|1].val);
	return ;
}
int main(){
	
	n=in;m=in;
	for(int i=1;i<=n;i++){
		a[i].l=in;a[i].r=in;
		a[i].len=a[i].r-a[i].l;
		a[i].id=i;
		p[++tot].val=a[i].l;
		p[tot].id=i;
		p[++tot].val=a[i].r;
		p[tot].id=i;
	}
	sort(p+1,p+1+tot,cmp1);
	int num=0;
	p[0].val=-1;
	for(int i=1;i<=tot;i++){
		if(p[i].val!=p[i-1].val) num++;
		if(!ll[p[i].id]) ll[p[i].id]=num;
		else rr[p[i].id]=num;
	}
	sort(a+1,a+1+n,cmp2);
	int ans=0x7fffffff,l=0,r=0;
	while(1){
		while(t[1].val<m&&r<=n){
			r++;
			int idx=a[r].id;
			update(1,num,ll[idx],rr[idx],1,1);
		} 
		if(t[1].val<m) break;
		while(t[1].val>=m&&l<=n){
			l++;
			int idx=a[l].id;
			update(1,num,ll[idx],rr[idx],1,-1);
		}
		ans=min(ans,a[r].len-a[l].len);
	}
	if(ans==0x7fffffff) printf("-1\n");
	else printf("%d\n",ans);
	return 0;
}
```