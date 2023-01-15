~~我是劳模~~
### 题目：
#### 题目描述
在SSZX食堂，所有的座位是一行一行的排列。现在有 $N$ 个座位排成一行，依次编号 $1,2,\dots,N$ ，每个座位只能坐一个人，现在L想数一下有多少个人坐着，一个一个数太慢了，L决定只选择 $M$ 段连续的座位，对每段分别数出人数。由于食堂噪音十分嘈杂，L无法专心，可能有数错了。但是L认为没有数漏，最多是重复计数导致的。现在他把得到的数据给你，希望你帮他算出，一共最多有多少人。

#### 输入格式
第一行2个整数 $N,M$，分别是座位数量，和L分成 $M$ 段

接下来M行，每行3个整数，$l,r,k$，表示L数了 $l$ 到 $r$ 这一段的座位，他输出的数是 $k$。

#### 输出格式
输出一行一个整数表示答案



~~我们学校食堂没有这么大~~






#### 数据规模
20%数据, $N,M$ <=20

40%数据，$N,M$<=500

20%数据，L选的每段座位 不相交

100%数据，$1 \leq N,M,K \leq 100 000$ , $1 \leq l \leq r \leq N $


### solution：
（差分约束）

说白了就是有一个长度为 $n$ 的 01 串，每次告诉区间 $[l,r]$ 中有多少个 1 ，求次串最多有几个 1 。

首先可以想到用前缀和 $pre_i$ 表示 $[1,i]$ 的范围内有多少个 1 ，答案就是求 $pre_n-pre_0$ 的最大解。每一个条件可以表示为 $pre_r-pre_{l-1}=k$ 。然后考虑用差分约束求解，建立 $(l-1,r)$ 和 $(r,l-1)$ 、权值为 $k$ 的一条边。但是如果这样建完边会发现不连通，所以需要加条件。~~我就在这里卡了好久~~。直到看了其他的题解，又发现了一个约束条件： $0 \leq pre_i-pre_{i-1} \leq 1$ ,很好理解吧。然后跑一遍最短路求最大解就好了。 

### code ：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=5e5+10;
const int inf=0x3f3f3f3f;
struct edge{
	int u,v,w,nxt;
}e[maxn<<2];
int cnt=0,h[maxn];
void add(int u,int v,int w){
	e[++cnt]=(edge){u,v,w,h[u]};
	h[u]=cnt;
}//前向星存图 
int n,m,op,u,v,w,dis[maxn],vis[maxn],cntt[maxn];
bool spfa(int be){
	queue<int> q;
	memset(dis,inf,sizeof(dis));
	memset(vis,0,sizeof(vis));
	q.push(be);
	vis[be]=1;dis[be]=0;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		vis[u]=0;
		for(int i=h[u];i;i=e[i].nxt){
			int v=e[i].v,w=e[i].w;
			if(++cntt[v]>n+1) return false;
			if(dis[v]>dis[u]+w){
				dis[v]=dis[u]+w;
				if(!vis[v]){
					q.push(v);
					vis[v]=1;
				}
			}
		}
	}
	return true;
}
/*关于spfa，他死了。
不要问我为什么还有个return，问就是抄的模板。*/ 
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&u,&v,&w);
		add(u-1,v,w);
		add(v,u-1,w);//pre[r]-pre[l-1]=w,所以建立两条约束边 
	}
	for(int i=1;i<=n;i++){
		add(i-1,i,1);
		add(i,i-1,0);//0<=pre[i]-pre[i-1]<=1的条件建边 
	}
	spfa(0);//最短路求最大值解 
	printf("%d\n",dis[n]);
	return 0;
}
```

这道题借鉴了一点[这篇题解](https://www.luogu.com.cn/blog/five20/solution-p1250)的思路。