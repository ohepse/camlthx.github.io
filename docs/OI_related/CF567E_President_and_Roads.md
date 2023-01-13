### 题意：
[点击穿越](https://www.luogu.com.cn/problem/CF567E)

第一次做cf的题真的发现数据强度好大哇qwq（哭。看着是到蓝题，但是已经把我调废了。~~不要问我为什么改了四天才该对，问就是我是蒟蒻~~。

### solution：($Dijstra + Tarjan$)

这道题的思路其实不是很难想，很好理解就是要找出最短路并且找到桥，再枚举每一条边即可。

因为是有向图且要枚举每一条边，所以应该正反建一次图然后分别跑一边 $dijstra$ 。

然后就是找桥，也就是最短路上得必经边，首先得把所有最短路上的边重新建图。第一可以用 $tarjan$ ，这是个简单质朴的方式，代码实现问题也不大。

还有一种方法可以使用最短路计数的方法，设从 $s$ 开始到 $u$ 的最短路条数用 $sum_{0,u}$ 表示，从 $t$ 开始到 $v$ 的最短路条数用 $sum_{1,v}$ 表示,那么如果一条边 $(u,v)$ 是桥的话，一定满足 $sum_{0,u} * sum_{1,v} = sum_{0,t}$ 。

然后直接一通分类讨论就完辣。

~~最短路计数的方法实在是太难写了所以我还是贴 $tarjan$ 吧。~~
听说 cf 的毒瘤数据还卡单模数和 $1e^9$ 的模数，然后便看到各种大佬的随机模数，双模数等等。蒟蒻实在写不来（悲。
### code：
~~~cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn=1e5+10;
const ll inf=0x3f3f3f3f3f3f3f3f;
struct edge{
	ll u,v,w,nxt;
}e[3][maxn<<1];
ll h[3][maxn],cnt[3];
void add(ll u,ll v,ll w,int k){
	e[k][++cnt[k]]=(edge){u,v,w,h[k][u]};
	h[k][u]=cnt[k];
}//k=0是为正向图，k=1是为反向图 
struct reedge{
	ll u,v,w,nxt,num;
}re[maxn<<1];
ll rcnt=0,rh[maxn];
void addedge(ll u,ll v,ll w,ll i){
	re[++rcnt].u=u;re[rcnt].v=v;re[rcnt].w=w;
	re[rcnt].nxt=rh[u];re[rcnt].num=i;
	rh[u]=rcnt;
}//是保存最短路上的边的图 
ll n,m,s,t,u,v,w,dis[3][maxn];
struct node{
	ll i,dis;
	bool operator <(const node&x)const{
		return dis>x.dis;
	}
};
void dijstra(ll be,int k){
	priority_queue<node> q;
	for(int i=0;i<=n;i++) dis[k][i]=inf;
	dis[k][be]=0;
	q.push((node){be,0});
	while(!q.empty()){
		ll u=q.top().i,dist=q.top().dis;
		q.pop();
		if(dis[k][u]!=dist) continue;
		for(int i=h[k][u];i;i=e[k][i].nxt){
			ll v=e[k][i].v,w=e[k][i].w;
			if(dis[k][v]>dis[k][u]+w){
				dis[k][v]=dis[k][u]+w;
				q.push((node){v,dis[k][v]});
			}
		}
	}
}//普通的最短路 
ll dfn[maxn],low[maxn],tot=0,fa[maxn],flag[maxn<<2],ans[maxn<<2];
void tarjan(ll u){
	dfn[u]=low[u]=++tot;
	for(int i=rh[u];i;i=re[i].nxt){
		int v=re[i].v;
		if(!dfn[v]){
			fa[v]=re[i].num;
			tarjan(v);
			low[u]=min(low[u],low[v]);
			if(dfn[u]<low[v]){
				flag[re[i].num]=1;//保存桥的编号 
			}
		}else if(fa[u]!=re[i].num){
			low[u]=min(low[u],dfn[v]);
		}
	}
}//普通的tarjan 
int main(){
	scanf("%lld%lld%lld%lld",&n,&m,&s,&t);
	for(int i=1;i<=m;i++){
		scanf("%lld%lld%lld",&u,&v,&w);
		add(u,v,w,0);//正向建图 
		add(v,u,w,1);//反向建图 
	}
	dijstra(s,0);//正向最短路 
	dijstra(t,1);//反向最短路 
	ll minn=dis[0][t];
	for(int i=1;i<=m;i++){
		ll u=e[0][i].u,v=e[0][i].v,w=e[0][i].w;
		if(dis[0][u]==inf||dis[1][v]==inf){
			flag[i]=-2;//将不可能经过的边设为-2 
		}
		else if(dis[0][u]+dis[1][v]+w==minn){
			addedge(u,v,w,i);
			addedge(v,u,w,i);//对最短路上的边重新建图 
		}
		else if(dis[0][u]+dis[1][v]+w>minn){
			flag[i]=-1;
			ans[i]=w-(minn-1-dis[0][u]-dis[1][v]);//"can"情况的边保存 
		}
	}
	tarjan(s);
	for(int i=1;i<=m;i++){
		if(flag[i]==-1){
			if(ans[i]<e[0][i].w&&ans[i]>0) printf("CAN %lld\n",ans[i]);
			else puts("NO");
		}
		else if(flag[i]==1){
			puts("YES");
		}else{
			if(e[0][i].w>1&&flag[i]!=-2) puts("CAN 1");
			else puts("NO");
		}//一通分类讨论 
	}
	return 0;
} 
~~~