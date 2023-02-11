2.6~2.9 数据结构与 $dp$ 专练，每天4题，难度不小，深蓝到深紫之间的难度。

绝大部分题来自bzoj，洛谷上只收录了一小部分。

* D1T1 与或 ：线段树维护二进制操作
* D1T2 排队计划：推导性质+线段树维护
* D1T3 [Kinoman](https://www.luogu.com.cn/problem/p3582)： 权值线段树
* D1T4 [Hotel](https://www.luogu.com.cn/problem/p2894)：线段树+最长子序列
* D2T1 [[NOI2016]区间](https://www.luogu.com.cn/problem/p1712)：双指针+线段树
* D2T2 跳伞求生：贪心/线段树模拟费用流
* D2T3 [Cards](https://www.luogu.com.cn/problem/p3569)：线段树合并
* D2T4 [[AHOI2014/JSOI2014]奇怪的计算器](https://www.luogu.com.cn/problem/p4041)：线段树
* D3T1 层流：树剖+树上染色
* D3T2 Graph：树剖/dfs序+树状数组
* D3T3 three：长链剖分维护 $dp$
* D3T4 [月下“毛景树”](https://www.luogu.com.cn/problem/p4315)：树剖裸题
* D4T1 [[SDOI2014]旅行](https://www.luogu.com.cn/problem/P3313)：树剖+主席树
* D4T2 [[NOI2011]嘉年华](https://www.luogu.com.cn/problem/P1973)：单调队列优化 $dp$
* D4T3 [[BJWC2010]严格次小生成树](https://www.luogu.com.cn/problem/P4180)：树剖+最小生成树
* D4T4 路径的交：dfs序

## Day1 线段树专题（确信

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

---

### D1T2 排队计划

#### Description：

对于一个序列 $h$，有 $m$ 次操作，每次操作 $j$ ，将 $p_j\le i\le n$中，小于等于第 $h_j$ 的元素取出并重排后插入。求每次操作后的逆序对的数量。

#### Solution：

~~一开始以为是个三维偏序~~

首先考虑暴力解法。对于每次询问重新求逆序对即可，预计时间复杂度为 $O(mnlogn)$ ，而且常数巨大。

然后考虑优化。可以观察到这次询问的答案可以从上一次的答案更新。易得对于每个取出的数 $h_i$ ，减少的逆序对的数量就是 $h_i$ 后比它小的数的个数。因为每次操作后序列都趋向有序，所以逆序对的数量会减少，单点暴力修改的时间复杂度是有保证的。

#### Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn=5e5+10;
const int inf=0x7fffffff;
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
int n,m,h[maxn],hsh[maxn],tot=0,x;
ll val[maxn];
struct node{
	int pos,val;
}a[maxn];
struct BIT{
	ll t[maxn];
	inline int lowbit(int x){
		return x&-x;
	}
	inline ll query(int x){
		ll res=0;
		while(x){
			res+=t[x];
			x-=lowbit(x);
		}
		return res;
	} 
	inline void update(int x,ll val){
		while(x<=tot){
			t[x]+=val;
			x+=lowbit(x);
		}
	}
}bit;
bool cmp(node a,node b){
	//if(a.val==b.val) return a.pos<b.pos;
	return a.val<b.val;
}

struct tree{
	int l,r,pos;
}t[maxn<<2];
void pushup(int p){
    if(hsh[t[p<<1|1].pos]<=hsh[t[p<<1].pos]) t[p].pos=t[p<<1|1].pos;
    else t[p].pos=t[p<<1].pos;
}
void build(int l,int r,int p){
	t[p].l=l;t[p].r=r;
	if(l==r){
		t[p].pos=l;
		return ;
	}
	int mid=l+r>>1;
	build(l,mid,p<<1);
	build(mid+1,r,p<<1|1);
	pushup(p);
}
void update(int l,int r,int p,int t){
	if(l==r){
		hsh[l]=inf;
		val[l]=0;
		return ;
	}
	int mid=l+r>>1;
	if(t<=mid) update(l,mid,p<<1,t);
	else update(mid+1,r,p<<1|1,t);
	pushup(p); 
}
int pd(int x,int y){
	if(hsh[y]<=hsh[x]) return y;
	return x;
}
int query(int l,int r,int p){
	if(l<=t[p].l&&t[p].r<=r) return t[p].pos;
	int ans=0;
	int mid=t[p].l+t[p].r>>1;
	if(l<=mid) ans=query(l,r,p<<1);
	if(r>mid){
		int t=query(l,r,p<<1|1);
		if(!ans) ans=t; 
		else ans=pd(ans,t);
	}
	return ans;
}
int main(){
	n=in;m=in;
	for(int i=1;i<=n;i++){
		a[i].pos=i;a[i].val=in;
	} 
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++){
		if(a[i].val!=a[i-1].val) hsh[a[i].pos]=++tot;
		else hsh[a[i].pos]=tot;
	}
	ll ans=0;
	for(int i=n;i>=1;i--){
		bit.update(hsh[i],1);
		val[i]=bit.query(hsh[i]-1);
		ans+=val[i];
	}
	printf("%lld\n",ans);
	build(1,n,1);
	for(int i=1;i<=m;i++){
		x=in;
		while(hsh[x]!=inf){
			int t=query(x,n,1);
			//cout<<"#debug "<<t<<endl;
			ans-=val[t];
			update(1,n,1,t);
		} 
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

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

----

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

---

## Day2 仍然是线段树专题（悲

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

---

### D2T2 跳伞求生

[传送门](http://192.168.101.115/p/1725?tid=63df53a1913b4d038e91609d)

#### Description：

 小Q最近沉迷于《跳伞求生》游戏。他组建了一支由 $n$ 名玩家（包括他自己）组成的战队，编号依次为$1,2,\dots,n$ 。这个游 戏中，每局游戏开始时，所有玩家都会从飞机上跳伞，选择一个目的地降落，跳伞和降落的时间有早有晚。在某局 游戏降落前，他们在空中观察发现地面上一共有 $m$ 间房子，编号依次为 $1$ 到 $m$ 。其中每间房子恰好有一名敌人早于他 们到达。小Q战队的第 $i$ 名玩家拥有 $a_i$发子弹，地面上第i间房子里的敌人拥有 $b_i$ 发子弹，消灭他可以获得 $c_i$ 点积 分。每名玩家必须且只能选择一间房子降落，然后去消灭里面的敌人。若第i名玩家选择了第j间房子，如果 $a_i>b_ j$ ，那么他就可以消灭该敌人，获得 $a_i-b_j+c_j$ 的团队奖励积分，否则他会被敌人消灭。为了防止团灭，小Q不允 许多名玩家选择同一间房子，因此如果某位玩家毫无利用价值，你可以选择让他退出游戏。因为房子之间的距离过长，你可以认为每名玩家在降落之后不能再去消灭其它房间里的敌人。作为小Q战队的指挥，请制定一套最优的降 落方案，使得最后获得的团队奖励总积分最大 

#### Solution：

对于人的贡献为 $a_i$ ，房子的贡献为 $c_j-b_j$ 。 将 $c_j-b_j$ 从大到小排序。对于贡献大的房子，也要用 $a_i$ 大的取消除。用一个 $multiset$ 维护 $a$ ，如果有能消灭敌人的人，并更新答案。

#### Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=5e5+10;
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
struct room{
	int b,c,val;
}p[maxn];
int n,m,a[maxn];
multiset<int> s;
bool cmp1(int a,int b){
	return a>b;
}
bool cmp2(room a,room b){
	return a.val>b.val;
}
int main(){
	n=in;m=in;
	for(int i=1;i<=n;i++) a[i]=in,s.insert(a[i]);
	for(int i=1;i<=m;i++){
		p[i].b=in;p[i].c=in;
		p[i].val=p[i].c-p[i].b;
	}
	sort(a+1,a+1+n,cmp1);
	sort(p+1,p+1+m,cmp2);
	ll ans=0,tot=0;
	int cnt=0;
	for(int i=1;i<=m;i++){
		multiset<int>::iterator it=s.lower_bound(p[i].b+1);
		if(it!=s.end()){
			ans=max(ans,tot+=a[++cnt]+p[i].val);
			s.erase(it);
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```

**诶难道不是线段树专题吗？~~因为这道题还可以用线段树模拟费用流来做~~**

---

### D2T3 Cards

#### Description：

每个卡片有 $a_i$ 和 $b_i$ 两个数。交换 $c_i$ 和 $d_i$ 两个位置上的卡片，判断能否将任意卡片翻转，保证卡片正面的数单调不减。

#### Solution：

考虑线段树维护区间能否单调不减。合并时判断即可。但是常数巨大还在 $T$ 着呢。

对于合并的`pushup`

```cpp
void pushup(int p){
	int mid=t[p].l+t[p].r>>1;
	//t[p].f[0][0]=t[p].f[1][0]=t[p].f[0][1]=t[p].f[1][1]=0;
	for(int i=0;i<=1;i++){
		for(int j=0;j<=1;j++){
			t[p].f[i][j]=0;
			for(int k=0;k<=1;k++){
				for(int l=0;l<=1;l++){
					t[p].f[i][j]|=t[p<<1].f[i][k]&t[p<<1|1].f[l][j]&(val[mid][k]<=val[mid+1][l]);
				}
			}
		}
	}
}
```

#### Code:

改了一下维度降了一下，时间复杂度要优秀一点

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn=2e5+10;
#define in read()
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';
		c=getchar();
	}
	return x*f;
}
int n,m,a,b,val[maxn][2],t[maxn<<2][2]; 
void pushup(int p,int l,int r){
	int mid=l+r>>1;
	if(t[p<<1][0]!=-1){
		if(t[p<<1][0]<=val[mid+1][0]) t[p][0]=t[p<<1|1][0];
		else if(t[p<<1][0]<=val[mid+1][1]) t[p][0]=t[p<<1|1][1];
		else t[p][0]=-1;
	}else t[p][0]=-1;
	if(t[p<<1][1]!=-1){
		if(t[p<<1][1]<=val[mid+1][0]) t[p][1]=t[p<<1|1][0];
		else if(t[p<<1][1]<=val[mid+1][1]) t[p][1]=t[p<<1|1][1];
		else t[p][1]=-1;
	}else t[p][1]=-1;
}
void build(int l,int r,int p){
	if(l==r){
		t[p][0]=val[l][0];
		t[p][1]=val[l][1];
		return ;
	}
	int mid=l+r>>1;
	build(l,mid,p<<1);
	build(mid+1,r,p<<1|1);
	pushup(p,l,r);
}
void update(int l,int r,int p,int x){
	if(l==r){
		t[p][0]=val[l][0];
		t[p][1]=val[l][1];
		return ;
	}
	int mid=l+r>>1;
	if(x<=mid) update(l,mid,p<<1,x);
	else update(mid+1,r,p<<1|1,x);
	pushup(p,l,r);
}
int main(){
	n=in;
	for(int i=1;i<=n;i++){
		val[i][0]=in;val[i][1]=in;
		if(val[i][0]>val[i][1]) swap(val[i][0],val[i][1]);
	}
	m=in;
	build(1,n,1);
	while(m--){
		a=in;b=in;
		swap(val[a][0],val[b][0]);
		swap(val[a][1],val[b][1]);
		update(1,n,1,a);
		update(1,n,1,b);
		if(t[1][0]!=-1||t[1][1]!=-1) puts("TAK");
		else puts("NIE");
	}
	return 0;
}
```



$TLE$ 的代码： 

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn=2e5+10;
#define in read()
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';
		c=getchar();
	}
	return x*f;
}
int n,m,a,b,val[maxn][2]; 
struct tree{
	int l,r;
	bool f[2][2];
}t[maxn<<2];
void pushup(int p){
	int mid=t[p].l+t[p].r>>1;
	//t[p].f[0][0]=t[p].f[1][0]=t[p].f[0][1]=t[p].f[1][1]=0;
	for(int i=0;i<=1;i++){
		for(int j=0;j<=1;j++){
			t[p].f[i][j]=0;
			for(int k=0;k<=1;k++){
				for(int l=0;l<=1;l++){
					t[p].f[i][j]|=t[p<<1].f[i][k]&t[p<<1|1].f[l][j]&(val[mid][k]<=val[mid+1][l]);
				}
			}
		}
	}
}
void build(int l,int r,int p){
	t[p].l=l;t[p].r=r;
	if(l==r){
		t[p].f[0][0]=t[p].f[1][1]=1;
		return ;
	}
	int mid=l+r>>1;
	build(l,mid,p<<1);
	build(mid+1,r,p<<1|1);
	pushup(p);
}
void update(int l,int r,int p,int x){
	if(l==r){
		t[p].f[0][0]=t[p].f[1][1]=1;
		return ;
	}
	int mid=l+r>>1;
	if(x<=mid) update(l,mid,p<<1,x);
	else update(mid+1,r,p<<1|1,x);
	pushup(p);
}
int main(){
	n=in;
	for(int i=1;i<=n;i++){
		val[i][0]=in;val[i][1]=in;
		//if(val[i][0]<val[i][1]) swap(val[i][0],val[i][0]);
	}
	m=in;
	build(1,n,1);
	while(m--){
		a=in;b=in;
		swap(val[a][0],val[b][0]);
		swap(val[a][1],val[b][1]);
		update(1,n,1,a);
		update(1,n,1,b);
		if(t[1].f[0][0]|t[1].f[0][1]|t[1].f[1][0]|t[1].f[1][1]) puts("TAK");
		else puts("NIE");
	}
	return 0;
}
```

---

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

---

## Day3 今天是树剖专题了嗨嗨嗨

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

----

### D3T2 Graph

#### Description:

给一个 $n$ 个点的图，有 $2*n-2$ 条**有向边**。边目录按两部分给出：

1. 开始的 $n-1$ 条边描述了一颗以1号点为根的生成树，每个点都可以由1号点到达。

2. 接下来的 $n-1$ 条边一定是 $<i,1>$ 的有向边，保证每个点都能到达1号点。

有 $q$ 次询问：

`1 x w` 将第 $x$条边的边权修改为 $w$ 

`2 u v` 询问 $u$ 到 $v$ 的最短距离

#### Solution：

~~我是绝对不会说我因为没看见有向边导致样例玩了1个小时~~

讨论一下 $u$ 和 $v$ 的关系。

如果 $u$ 是 $lca$ ，直接求链就可以了。不然查询以 $u$ 为根的子树返回根的最优值就好了。

然后用树剖维护 $dis_i+w_i$ 的最小值，$dis_i$ 表示 $i$ 到根的距离，$w_i$ 表示 $i$ 回到根的距离。

至于为什么觉得 [FSYo的题解](https://blog.csdn.net/sslz_fsy/article/details/82557256?ops_request_misc=&request_id=&biz_id=102&utm_term=graph%20%E7%BA%BF%E6%AE%B5%E6%A0%91&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-0-82557256.142^v73^control_1,201^v4^add_ask,239^v1^insert_chatgpt&spm=1018.2226.3001.4187) 写的很清楚。

#### Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=4e5+10;
#define in read()
#define ll long long
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
struct edge{
	int v,nxt;
	ll w;
}e[maxn<<2];
int h[maxn],cnt=0;
inline void add(int u,int v,ll w){
	e[++cnt].v=v;e[cnt].nxt=h[u];e[cnt].w=w;
	h[u]=cnt;
}
struct tree{
	int l,r;
	ll min,tag;
}t[maxn<<2];
int n,q,tot=0,siz[maxn],rec[maxn],top[maxn],num[maxn],fa[maxn],dep[maxn],pred[maxn],hson[maxn];
ll a[maxn],dis[maxn];
void dfs1(int x){
	siz[x]=1;
	for(int i=h[x];i;i=e[i].nxt){
		int v=e[i].v;
		a[v]=a[x]+e[i].w;
		dep[v]=dep[x]+1;
		fa[v]=x;
		dfs1(v);
		siz[x]+=siz[v];
		if(siz[v]>siz[hson[x]]) hson[x]=v; 
	}
}
void dfs2(int x,int tp){
	top[x]=tp;num[x]=++tot;pred[tot]=x;
	if(!hson[x]) return ;
	dfs2(hson[x],tp);
	for(int i=h[x];i;i=e[i].nxt){
		int v=e[i].v;
		if(v!=hson[x]) dfs2(v,v);
	}
}
void build(int l,int r,int p){
	t[p].l=l;t[p].r=r;
	if(l==r){
		t[p].min=a[pred[l]]+dis[pred[l]];
		return ;
	}
	int mid=l+r>>1;
	build(l,mid,p<<1);
	build(mid+1,r,p<<1|1);
	t[p].min=min(t[p<<1].min,t[p<<1|1].min);
}
void pushdown(int p){
	if(t[p].tag){
		t[p<<1].min+=t[p].tag;
		t[p<<1|1].min+=t[p].tag;
		t[p<<1].tag+=t[p].tag;
		t[p<<1|1].tag+=t[p].tag;
		t[p].tag=0; 
	}
}
void update(int l,int r,int p,ll val){
	if(l>t[p].r||t[p].l>r) return ;
	if(l<=t[p].l&&t[p].r<=r){
		t[p].tag+=val;
		t[p].min+=val;
		return ;
	}
	pushdown(p);
	int mid=t[p].l+t[p].r>>1;
	if(r<=mid) update(l,r,p<<1,val);
	else if(l>mid) update(l,r,p<<1|1,val);
	else update(l,mid,p<<1,val),update(mid+1,r,p<<1|1,val);
	t[p].min=min(t[p<<1].min,t[p<<1|1].min);
}
ll query(int l,int r,int p){
	if(l>t[p].r||t[p].l>r) return 1e18;
	if(l<=t[p].l&&t[p].r<=r) return t[p].min;
	pushdown(p);
	int mid=t[p].l+t[p].r>>1;
	if(r<=mid) return query(l,r,p<<1);
	if(l>mid) return query(l,r,p<<1|1);
	return min(query(l,mid,p<<1),query(mid+1,r,p<<1|1));
}
inline int lca(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		x=fa[top[x]];
	}
	return dep[x]<dep[y]?x:y;
}
int main(){
	n=in;q=in;
	for(int i=1;i<n;i++){
		int u=in,v=in;ll w=in;
		add(u,v,w);
	}
	for(int i=1;i<n;i++){
		int u=in,v=in;ll w=in;
		rec[i]=u;dis[u]=w;
	}
	dfs1(1);dfs2(1,1);
	build(1,n,1);
	while(q--){
		int opt=in;ll x=in,y=in;
		if(opt==1){
			if(x<=n-1) update(num[e[x].v],num[e[x].v]+siz[e[x].v]-1,1,y-e[x].w),e[x].w=y;
			else update(num[rec[x-n+1]],num[rec[x-n+1]],1,y-dis[rec[x-n+1]]),dis[rec[x-n+1]]=y;
		}else{
			if(x==y){
				puts("0");
				continue;
			}
			if(lca(x,y)==x) printf("%lld\n",query(num[y],num[y],1)-dis[y]-query(num[x],num[x],1)+dis[x]);
			else printf("%lld\n",query(num[y],num[y],1)+query(num[x],num[x]+siz[x]-1,1)-query(num[x],num[x],1)+dis[x]-dis[y]);
		}
	}
	return 0;
}
```

----

### D3T3 Three

#### Desciption:

给定一颗 $n$ 个节点的无根树，在树上选三个互不相同的节点，使得三个节点两两之间距离相等，输出方案数。

#### Solution：

首先，我不是很会 $dp$ 

其次，我完全不会长链剖分优化 $dp$ 

最后，我* * * * * *

其实 $dp$ 部分还是听懂了。

设 $f_{i,j}$ 表示以 $i$ 为根的子树中距离 $i$ 为 $j$ 的点数，$g_{i,j}$ 表示 $i$ 的子树中有多少两个点的 $lca$ 到 $i$ 的距离为 $d-j$ ，两个点到他们 $lca$ 的距离是 $d$ 。

很容易发现这两个状态可以互补（？

因此对于一对父子 $(p,v)$ 有如下转移式：
$$
ans+=g_{v,i+1}*f_{p,i}+g_{p,i}*f_{v,i-1}
$$

$$
g_{p,i}+=g_{v,i-1}+f_{v,i-1}*f_{p,i}
$$

$$
f_{p,i}+=f_{v,i-1}
$$

但是代码就完全就看不懂了，什么指针转移力（哭

#### Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
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
const int maxn=3e5+10;
vector<int> e[maxn];
int n,u,v;
ll pool[maxn<<4];
ll* top=pool;
ll *f[maxn],*g[maxn];
ll* get(int len){
	ll* t=top;top+=len;
	return t;
}
ll ans=0;
int dep[maxn],hson[maxn];
void dfs1(int x,int fa){
	dep[x]=0;hson[x]=0;
	for(int i=0;i<e[x].size();i++){
		int v=e[x][i];
		if(v==fa) continue;
		dfs1(v,x);
		dep[x]=max(dep[x],dep[v]+1);
		if(dep[v]>dep[hson[x]]) hson[x]=v;
	}
}
void dfs2(int x,int fa,int &maxlen,int blank){
	maxlen=max(maxlen,dep[x]);
	if(hson[x]){
		dfs2(hson[x],x,maxlen,blank+1);
		ans+=g[hson[x]][1];
		f[x]=f[hson[x]]-1;
		f[x][0]=1;
		g[x]=g[hson[x]]+1;
	}else{
		f[x]=get(maxlen+5+blank)+blank;
		g[x]=get(maxlen+5+blank);
		f[x][0]=1;
	}
	for(int i=0;i<e[x].size();i++){
		int v=e[x][i],mlen=0;
		if(v==fa||v==hson[x]) continue;
		dfs2(v,x,mlen,0);
		for(int j=0;j<dep[v];j++) ans+=f[x][j]*g[v][j+1];
		for(int j=1;j<=dep[v]+1;j++) ans+=g[x][j]*f[v][j-1];
		for(int j=1;j<=dep[v]+1;j++) g[x][j]+=f[x][j]*f[v][j-1];
		for(int j=0;j<=dep[v];j++) f[x][j+1]+=f[v][j];
		for(int j=1;j<=dep[v];j++) g[x][j-1]+=g[v][j];
	}
}
int main(){
	while(1){
		n=in;
		if(n==0) break;
		memset(pool,0,sizeof(pool));
		memset(hson,0,sizeof(hson));
		memset(dep,0,sizeof(dep));
		for(int i=1;i<=n;i++) e[i].clear();
		ans=0;
		for(int i=1;i<n;i++){
			u=in;v=in;
			e[u].push_back(v);
			e[v].push_back(u);
		}
		int mxlen=0;
		dfs1(1,0);
		dfs2(1,0,mxlen,0);
		printf("%lld\n",ans);
	}
	return 0;
}
```



----

### D3T4 月下毛景树

#### Description：

给定一颗 $n$ 个节点有边权的树，维护以下四个操作：

`Change k w` 将第 $k$ 条边的边权改为 $w$

`Cover u v w` 将 $<u,v>$ 路径上的所有边权都改为 $w$

`Add u v w ` 将 $<u,v>$ 路径上的所有边权都加上 $w$

`Max u v` 询问 $<u,v>$ 路径上边权最大值

#### Solution：

将边权转化为深度更大的点的点权，然后变成树剖的模板。

需要注意的是，改变路径上的边权时要去掉 $lca$ 的点权。

```cpp
void modify(int x,int y,int val){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		updadd(num[top[x]],num[x],1,val);
		x=fa[top[x]];
	}
	if(num[x]>num[y]) swap(x,y);
	updadd(num[x],num[y],1,val);
}
```

要变为：

```cpp
void modify(int x,int y,int val){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		updadd(num[top[x]],num[x],1,val);
		x=fa[top[x]];
	}
	if(num[x]>num[y]) swap(x,y);
	updadd(num[x]+1,num[y],1,val);
}
```

#### Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
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
const int maxn=2e5+10;
struct edge{
	int u,v,w,nxt;
}e[maxn<<1];
int cnt=0,h[maxn];
inline void add(int u,int v,int w){
	e[++cnt]=(edge){u,v,w,h[u]};
	h[u]=cnt;
}
int n,q,u,v;
int dep[maxn],siz[maxn],hson[maxn],fa[maxn],w[maxn],id[maxn];
int dfn[maxn],num[maxn],top[maxn],tot=0;
void dfs1(int x,int father){
	siz[x]=1;
	hson[x]=0;
	for(int i=h[x];i;i=e[i].nxt){
		int v=e[i].v;
		if(v==father) continue; 
		dep[v]=dep[x]+1;
		fa[v]=x;
		dfs1(v,x);
		w[v]=e[i].w;
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
	int l,r,max,add,cov;
}t[maxn<<2];
void build(int l,int r,int p){
	t[p].l=l;t[p].r=r;
	if(l==r){
		t[p].max=w[dfn[l]];
		return ;
	}
	int mid=(l+r)>>1;
	build(l,mid,p<<1);
	build(mid+1,r,p<<1|1);
	t[p].max=max(t[p<<1].max,t[p<<1|1].max);
}
void pushcov(int p,int val){
	t[p].max=val;
	t[p].add=0;
	t[p].cov=val;
}
void pushadd(int p,int val){
	t[p].max+=val;
	t[p].add+=val;
}
void pushdown(int p){
	if(t[p].cov){
		pushcov(p<<1,t[p].cov);
		pushcov(p<<1|1,t[p].cov);
		t[p].cov=0;
	}
	if(t[p].add){
		pushadd(p<<1,t[p].add);
		pushadd(p<<1|1,t[p].add);
		t[p].add=0;
	}
}
void updcover(int l,int r,int p,int val){
	if(l<=t[p].l&&t[p].r<=r){
		pushcov(p,val);
		return ;
	}
	pushdown(p);
	int mid=t[p].l+t[p].r>>1;
	if(l<=mid) updcover(l,r,p<<1,val);
	if(r>mid) updcover(l,r,p<<1|1,val);
	t[p].max=max(t[p<<1].max,t[p<<1|1].max);
}
void updadd(int l,int r,int p,int val){
	if(l<=t[p].l&&t[p].r<=r){
		pushadd(p,val);
		return ;
	}
	pushdown(p);
	int mid=t[p].l+t[p].r>>1;
	if(l<=mid) updadd(l,r,p<<1,val);
	if(r>mid) updadd(l,r,p<<1|1,val);
	t[p].max=max(t[p<<1].max,t[p<<1|1].max);
}
int querymax(int l,int r,int p){
	if(l<=t[p].l&&t[p].r<=r) return t[p].max;
	pushdown(p);
	int mid=t[p].l+t[p].r>>1;
	int ans=-0x3f3f3f3f;
	if(l<=mid) ans=max(ans,querymax(l,r,p<<1));
	if(mid<r) ans=max(ans,querymax(l,r,p<<1|1));
	return ans;
}
void cover(int x,int y,int val){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		updcover(num[top[x]],num[x],1,val);
		x=fa[top[x]];
	}
	if(num[x]>num[y]) swap(x,y);
	updcover(num[x]+1,num[y],1,val);
}
void modify(int x,int y,int val){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		updadd(num[top[x]],num[x],1,val);
		x=fa[top[x]];
	}
	if(num[x]>num[y]) swap(x,y);
	updadd(num[x]+1,num[y],1,val);
}
int getmax(int x,int y){
	int ans=-0x3f3f3f3f;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		ans=max(ans,querymax(num[top[x]],num[x],1));
		x=fa[top[x]];
	}
	if(num[x]>num[y]) swap(x,y);
	ans=max(ans,querymax(num[x]+1,num[y],1));
	return ans;
}
int main(){
	freopen("P4315_1.in","r",stdin);
	freopen("ans.out","w",stdout);
	n=in;
	for(int i=1;i<n;i++){
		u=in;v=in;int w=in;
		add(u,v,w);
		add(v,u,w);
	}
	dfs1(1,0);
	dfs2(1,1);
	build(1,tot,1);
	for(int i=1;i<=n*2-2;i+=2) id[i/2+1]=dep[e[i].u]>dep[e[i].v]?e[i].u:e[i].v;
	char opt[10];
	while(1){
		scanf("%s",opt);
		if(opt[0]=='S') break;
		int x=in,y=in,z;
		if(opt[0]=='C'&&opt[1]=='h'){
			updcover(num[id[x]],num[id[x]],1,y);
			continue;
		}
		if(opt[0]=='C'&&opt[1]=='o'){
			z=in;
			cover(x,y,z);
			continue;
		}
		if(opt[0]=='A'){
			z=in;
			modify(x,y,z);
		}
		if(opt[0]=='M') printf("%d\n",getmax(x,y));
	}
	return 0;
}
```

----

## Day4

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

----

### D4T2 NOI嘉年华

[传送门](https://www.luogu.com.cn/problem/P1973)

一道完全没看懂的 $dp$,还被luogu×了。后面慢慢来改。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=505;
const int inf=0x7fffffff;
#define in read()
#define ll long long
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
int n,m=0,f[maxn][maxn],tot[maxn][maxn],suf[maxn][maxn],pre[maxn][maxn],s[maxn],t[maxn],hsh[maxn];
int main(){
	n=in;
	for(int i=1;i<=n;i++){
		hsh[++m]=s[i]=in;
		t[i]=in;
		hsh[++m]=t[i]=t[i]+s[i];
	}
	sort(hsh+1,hsh+1+m);
	m=unique(hsh+1,hsh+1+m)-hsh-1;
	for(int i=1;i<=n;i++){
		s[i]=lower_bound(hsh+1,hsh+1+m,s[i])-hsh;
		t[i]=lower_bound(hsh+1,hsh+1+m,t[i])-hsh;
		for(int l=1;l<=s[i];l++){
			for(int r=m;r>=t[i];r--) tot[l][r]++;
		}
	}
	
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++) pre[i][j]=suf[i][j]=-inf;
	}
	for(int i=1;i<=m;i++){
		for(int j=0;j<=tot[1][i];j++){
			for(int k=1;k<=i;k++){
				pre[i][j]=max(pre[i][j],pre[k][j]+tot[k][i]);
				if(j>=tot[k][i]) pre[i][j]=max(pre[i][j],pre[k][j-tot[k][i]]);
			}
		}
	}
	for(int i=m;i>=1;i--){
		for(int j=0;j<=tot[i][m];j++){
			for(int k=1;k<=m;k++){
			suf[i][j]=max(suf[i][j],suf[k][j]+tot[i][k]);
				if(j>=tot[i][k]) suf[i][j]=max(suf[i][j],suf[k][j-tot[i][k]]);
			}
		}
	}
	int p0,p1;
	for(int l=1;l<=m;l++){
		for(int r=l+1;r<=m;r++){
			for(int y=n,x=0;x<=n;x++){
				p0=min(x+tot[l][r]+y,pre[l][x]+suf[r][y]);
				while(y&&p0<=(p1=min(x+tot[l][r]+y-1,pre[l][x]+suf[r][y-1]))) p0=p1,--y;
				f[l][r]=max(f[l][r],min(x+tot[l][r]+y,pre[l][x]+suf[r][y]));
			}
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++) ans=max(ans,min(pre[m][i],i));
	printf("%d\n",ans);
	for(int i=1;i<=n;i++){
		ans=0;
		for(int l=1;l<=s[i];l++){
			for(int r=m;r>=t[i];r--) ans=max(ans,f[l][r]);
		}
		printf("%d\n",ans);
	}
	return 0;
}
```



----

### D4T3 严格次小生成树

#### Description：

给定一张 $n$ 个点 $m$ 条边的无向图，求无向图的严格次小生成树。

设最小生成树的边权之和为 $val$ ，严格次小生成树指边权之和大于 $val$ 的生成树的最小的一个。

#### Solution:

首先严格次小生成树根最小生成树只有一条边不同。 

所以我们可以枚举所有边，如果这条边不在生成树上，那么加入生成树后一定会构成一个环，这时候将边上最大值删去即可。但考虑到严格次小生成树的最大边权与当前边权相同，所以还要记录次大值。

用树剖维护次大值和最大值即可。

#### Code：

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
const int maxn=3e5+10;
struct edge{
	int u,v,w,nxt;
	bool vis;
}e[maxn<<1];
int cnt=0,h[maxn];
inline void add(int u,int v,int w){
	e[++cnt]=(edge){u,v,w,h[u]};
	h[u]=cnt;e[cnt].vis=0;
}
ll vall;
int n,m;
int dep[maxn],siz[maxn],hson[maxn],fa[maxn],w[maxn],id[maxn];
int dfn[maxn],num[maxn],top[maxn],tot=0;
void dfs1(int x,int father){
	siz[x]=1;
	hson[x]=0;
	for(int i=h[x];i;i=e[i].nxt){
		int v=e[i].v;
		if(v==father) continue; 
		dep[v]=dep[x]+1;
		fa[v]=x;
		dfs1(v,x);
		w[v]=e[i].w;
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
int fat[maxn];
int find(int x){
	if(x!=fat[x]) fat[x]=find(fat[x]);
	return fat[x];
}
bool cmp(edge a,edge b){
	return a.w<b.w;
}
void kruskal(){
	sort(e+1,e+1+m,cmp);
	for(int i=1;i<=n;i++) fat[i]=i;
	int sum=0,fu,fv,u,v;//for(int i=1;i<=m;i++) cout<<e[i].u<<" "<<e[i].v<<" "<<e[i].w<<endl;
	for(int i=1;i<=m;i++){
		u=e[i].u,v=e[i].v;
		fu=find(u),fv=find(v);
		//cout<<u<<" "<<v<<" "<<fu<<" "<<fv<<endl;
		if(fu!=fv){
			add(u,v,e[i].w);add(v,u,e[i].w);
			fat[fu]=fv;
			vall+=e[i].w;
			++sum;
			e[i].vis=1;
			if(sum==n-1) break;
		}
	}
}
struct tree{
	int l,r,max,sec;
}t[maxn<<2];
void pushup(int p){
	t[p].max=max(t[p<<1].max,t[p<<1|1].max);
	if(t[p<<1].max==t[p<<1|1].max) t[p].sec=max(t[p<<1].sec,t[p<<1|1].sec);
	else t[p].sec=min(t[p<<1].max,t[p<<1|1].max);
}
void build(int l,int r,int p){
	t[p].l=l;t[p].r=r;
	if(l==r){
		t[p].max=w[dfn[l]];
		return ;
	}
	int mid=(l+r)>>1;
	build(l,mid,p<<1);
	build(mid+1,r,p<<1|1);
	pushup(p);
}
int querymax(int l,int r,int p,int key){
	if(t[p].l>r||t[p].r<l) return -inf;
	if(l<=t[p].l&&t[p].r<=r){
		if(key==t[p].max) return t[p].sec;
		return t[p].max;
	}
	int mid=t[p].l+t[p].r>>1;
	if(r<=mid) return querymax(l,r,p<<1,key);
	else if(mid<l) return querymax(l,r,p<<1|1,key);
	else return max(querymax(l,mid,p<<1,key),querymax(mid+1,r,p<<1|1,key));
}
int getmax(int x,int y,int key){
	int ans=-inf;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		ans=max(ans,querymax(num[top[x]],num[x],1,key));
		x=fa[top[x]];
	}
	if(num[x]>num[y]) swap(x,y);
	ans=max(ans,querymax(num[x]+1,num[y],1,key));
	return ans;
}
int main(){
	n=in;m=in;
	for(int i=1;i<=m;i++){
		e[i].u=in;
		e[i].v=in;
		e[i].w=in;
	}
	cnt=m;
	kruskal();
	dfs1(1,0);
	dfs2(1,1);
	build(1,n,1);
	ll ans=1e18;
	for(int i=1;i<=m;i++){
		if(!e[i].vis) ans=min(ans,vall+e[i].w-getmax(e[i].u,e[i].v,e[i].w));
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

### D4T4 路径的交

#### Desciption：

给定一颗 $n$ 个节点的树，以及 $m$ 条路径，第 $i$ 条路径与前 $i-1$ 条有多少相交的（点相交即视为路径相交）

#### Solution:

现在有两条路径 $a$ 和 $b$ ，有两种情况，一种是 $a$ 的 $lca$ 在 $b$ 上，另一种是 $b$ 的 $lca$ 在 $a$ 上。

所以就转化成了两个问题：

1. 当前路径上有几个之前的 $lca$

2. 之前的路径有几个经过当前的 $lca$ 

可以用两个树状数组来维护，一个支持单点修改、链上查询，另一个支持链上修改、单点查询。

#### Code：

目前只能用倍增来跳 $lca$ ，用欧拉序跳的有点奇怪（悲

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
int n,m,u,v;
int val[maxn],st[maxn],ed[maxn],tim=0,dfn[maxn<<1],dep[maxn],fath[maxn];
int f[maxn<<1][24];
int mmin(int a,int b){
    return dep[a]<dep[b]?a:b;
};
void dfs(int u,int fa){
	st[u]=++tim;
	f[u][0]=fa;
	for(int i=1;i<19;++i) f[u][i]=f[f[u][i-1]][i-1];
	dep[u]=dep[fa]+1;
	for(int i=h[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(v!=fa) dfs(v,u);
	}
	ed[u]=tim;
}

int lca(int x,int y) {   
    if(dep[x]<dep[y]) swap(x,y);   
    for(int i=18;i>=0;i--) 
	  	if(dep[f[x][i]]>=dep[y]) x=f[x][i];   
    if(x==y) return x;   
    for(int i=18;i>=0;i--) 
	  	if(f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];    
    return f[x][0];   
}
struct bittree{
	int t[maxn],siz;
	inline int lowbit(int x){
		return x&(-x);
	}
	inline void update(int x,int val){
		while(x<=n){
			t[x]+=val;
			x+=lowbit(x);
		}
	}
	inline int query(int x){
		int res=0;
		while(x){
			res+=t[x];
			x-=lowbit(x);
		}
		return res;
	}
}t1,t2;
int clac(int x,int y,int lca){
	int ans=0;
	ans+=t1.query(ed[lca])-t1.query(st[lca]-1);
	ans+=t2.query(st[x])+t2.query(st[y])-t2.query(st[lca])*2;
	return ans;
}
int main(){
	n=in;
	for(int i=1;i<n;i++){
		u=in;v=in;
		add(u,v);add(v,u);
	}
	m=in;
	dfs(1,0);
	for(int i=1;i<=m;i++){
		u=in;v=in;
		int lcaa=lca(u,v);
		printf("%d\n",clac(u,v,lcaa)+val[lcaa]);
		val[lcaa]++;
		t1.update(st[u],1);
		t1.update(st[v],1);
		t1.update(st[lcaa],-2);
		t2.update(st[lcaa],1);
		t2.update(ed[lcaa]+1,-1);
	}
	return 0;
}
```



