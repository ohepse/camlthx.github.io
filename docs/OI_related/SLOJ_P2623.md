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