~~一天爆肝两道CF毒瘤题题解~~

### 题意：
[传送门](https://www.luogu.com.cn/problem/CF400D)

~~建议使用百度翻译因为那个自带的翻译实在太水了~~

### solution：(并查集+$Floyd$）

同样是很好读懂的一道题，第一问就是让你求一个 $type$ 里的所有点能否以 $0$ 的代价抵达。对于这一问读入之后可以用将所有边权为0的边的端点用并查集合并。然后枚举每个点，如果和同一个 $type$ 其他的点不在一个连通块里就 $puts("NO")$ 即可。

对于第二问就是求每个$type$ 之间的最短距离。多源最短路，又看到 $k \leq 500 $ ,毫无疑问用 $Floyd$ 做就可以了。读入每条边的时候更新 $type$ 之间的距离就好了。

### code:
~~~cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
const int inf=0x3f3f3f3f;
int n,m,k,c[505],u,v,w,fa[maxn],f[505][505],col[maxn];
int find(int x){
	if(fa[x]!=x) fa[x]=find(fa[x]);
	return fa[x];
}
int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=k;i++){
		for(int j=1;j<=k;j++){
			if(i==j) f[i][j]=0;
			else f[i][j]=f[j][i]=inf;
		}
	}//初始化Floyd数组 
	int cnt=1;
	for(int i=1;i<=k;i++){
		scanf("%d",&c[i]);
		for(int j=1;j<=c[i];j++){
			col[cnt++]=i;
		}
	}//预处理出每个点是属于哪个type 
	for(int i=1;i<=n;i++) fa[i]=i;//并查集初始化 
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&u,&v,&w);
		if(!w){
			int fu=find(u),fv=find(v);
			if(fu!=fv) fa[fu]=fv;
		}	
		u=col[u];v=col[v];
		f[u][v]=f[v][u]=min(f[u][v],w);//读入的同时更新边权 
	}
	cnt=1;
	for(int i=1;i<=k;i++){
		int x=find(cnt);
		for(int j=1;j<=c[i];j++){
			if(find(cnt++)!=x){
				puts("No");//如果不在一个连通块内就是“NO” 
				return 0;
			}
		}	
	}
	puts("Yes");
	for(int i=1;i<=k;i++) f[i][i]=0;
	for(int p=1;p<=k;p++){
		for(int i=1;i<=k;i++){
			for(int j=1;j<=k;j++){
				f[i][j]=min(f[i][j],f[i][p]+f[p][j]);
			}
		}
	}//Floyd的板子 
	for(int i=1;i<=k;i++){
		for(int j=1;j<=k;j++){
			printf("%d ",f[i][j]!=inf?f[i][j]:-1);
		}
		printf("\n");
	}//按照题意输出即可 
	return 0;
}
~~~