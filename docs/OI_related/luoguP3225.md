[题目](https://www.luogu.com.cn/problem/P3225)

是一道练习 $tarjan$ 的好题。

首先读题，很容易想到是要先跑一遍 $tarjan$ 求割点。然后想想每一个连通块，分为几种情况：

如果没有割点，如果其中一个点断开，那么就会分成两个连通块，所以需要增加两个出口，在其中随便选两种就好， 共$C_n^2$种选择。

如果有一个割点，无论是否断在割点都需要一个出口，在非割点的地方随机选择即可。

如果有两个及以上割点，无论断在哪里，图都是联通的，所以不需要建立出口。

这道题有一些小坑，比如某些数据记得清零。记录最大值的变量没清零： $100pts->90pts$ （悲


然后是代码

~~~cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e3+10;
struct edge{
	int u,v,nxt;
}e[maxn<<2];
int cnt=0,h[maxn];
void add(int u,int v){
	e[++cnt]=(edge){u,v,h[u]};
	h[u]=cnt;	
}
int dfn[maxn],low[maxn],vis[maxn],flag[maxn],tot=0,rt;
void tarjan(int u,int fa){
	int son=0;
	dfn[u]=low[u]=++tot;
	for(int i=h[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(dfn[v]==0){
			son++;
			tarjan(v,u);
			low[u]=min(low[u],low[v]);
			if(low[v]>=dfn[u]) flag[u]=1;
		}
		else if(v!=fa){
			low[u]=min(dfn[v],low[u]);
		}
	}
	if(u==rt&&son==1){
		flag[u]=0;
	}
}
int m,u,v,n,num,cut,col,casessss=0;
unsigned long long ans1,ans2;
void init(){
	cnt=0;tot=0;col=0;n=0;
	ans1=0;ans2=1;
	memset(h,0,sizeof(h));
	memset(dfn,0,sizeof(dfn));
	memset(vis,0,sizeof(vis));
	memset(low,0,sizeof(low));
	memset(flag,0,sizeof(flag));
}
void dfs(int u){
	vis[u]=col;
	num++;
	for(int i=h[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(flag[v]&&vis[v]!=col){
			cut++;
			vis[v]=col;
		}
		if(!vis[v]) dfs(v);
	}
}
int main(){
	while(scanf("%d",&m)){
		if(m==0) break;
		casessss++;
		init();
		for(int i=1;i<=m;i++){
			scanf("%d%d",&u,&v);
			add(u,v);
			add(v,u);
			n=max(n,u);
			n=max(n,v);
		}
		rt=1;
		for(int i=1;i<=n;i++){
			if(!dfn[i]) rt=i,tarjan(rt,-1);
		}
		for(int i=1;i<=n;i++){
			if(!vis[i]&&!flag[i]){
				col++;
				num=cut=0;
				dfs(i);
				if(cut==0){
					ans1+=2;
					ans2*=(num-1)*num/2;
					continue;
				}
				if(cut==1){
					ans1+=1;
					ans2*=num;
					continue;
				}
			}
		}
		printf("Case %d: %lld %lld\n",casessss,ans1,ans2);
	}
	return 0;
} 

~~~