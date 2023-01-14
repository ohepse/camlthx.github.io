## 题目

[传送门]( [P2680 [NOIP2015 提高组\] 运输计划 - 洛谷 | 计算机科学教育新生态 (luogu.com.cn)](https://www.luogu.com.cn/problem/P2680) )

一道感觉不算很难的紫题

翻译一下

给定一棵有边权的树，和 $m$ 组点对，需要选择并清零一条边，使得 $m$ 条边之间的最长路最短。

## solution

最小化最大值，一眼二分。

然后考虑 $check$ 函数怎么写。很容易想到一个很暴力的解法：暴力枚举清零每一条边。一算时间复杂度肯定接受不了。

考虑优化。观察到枚举过程可以进行优化。先预处理出每条路径的长度， $check$ 时统计大于 $mid$ 的边有 $k$ 条，找出被经过 $k$ 次的边且边权最大的一条，判断最长路径 $maxlen$ 减去最长边 $maxd$ 是否小于 $mid$.

综上所述，先用树上差分+$LCA$ 预处理出每条路径的长度，二分答案，树上差分进行 $check$。

## code

细节都批注在代码里了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=3e5+10;
#define in read()
inline int read(){
    int x=0,f=1;char c=getchar();
    while(c>'9'||c<'0'){
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
    int u,v,w,nxt;
}e[maxn<<1];
int cnt=0,h[maxn];
void add(int u,int v,int w){
    e[++cnt]=(edge){u,v,w,h[u]};
    h[u]=cnt;
}
int n,m,u,v,t,l,r,maxlen,tim,st[maxn],val[maxn],dfn[maxn<<1],fa[maxn],dep[maxn],dis[maxn],rot;
void dfs(int x,int father,int d){
    dfn[++tim]=x;
    st[x]=tim;
    fa[x]=father;
    dep[x]=d;
    for(int i=h[x];i;i=e[i].nxt){
        int v=e[i].v;
        if(v==father) continue;
        dis[v]=dis[x]+e[i].w;
        val[v]=e[i].w;
        dfs(v,x,d+1);
        dfn[++tim]=x;
    }
}
//第一次dfs处理出dep,dis等数组，并求出欧拉序用dfn保存，方便用ST表求LCA
int f[maxn<<1][24];
int mmin(int a,int b){
    return dep[a]<dep[b]?a:b;
}
void STinit(int len){
    for(int i=1;i<=len;i++) f[i][0]=dfn[i];
    for(int j=1;(1<<j)<=len;j++){
        for(int i=1;i+(1<<j)-1<=len;i++){
            f[i][j]=mmin(f[i][j-1],f[i+(1<<j-1)][j-1]);
        }
    }
}//ST表初始化
int lca(int x,int y){
    x=st[x];y=st[y];
    if(x>y) swap(x,y);
    int k=0;
    while((1<<k+1)<=(y-x+1)) k++;
    return mmin(f[x][k],f[y-(1<<k)+1][k]);
}//求LCA
struct roads{
    int u,v,Lca,dis;
}rr[maxn];
int s[maxn];
void dfs2(int x,int fa){
    for(int i=h[x];i;i=e[i].nxt){
        int v=e[i].v;
        if(v==fa) continue;
        dfs2(v,x);
        s[x]+=s[v];
    }
}//第二个dfs用来求树上差分，算出每条边经过的次数
bool check(int mid){
    int res=0;
    memset(s,0,sizeof(s));
    for(int i=1;i<=m;i++){
        if(rr[i].dis>mid){
            res++;
            s[rr[i].u]++;
            s[rr[i].v]++;
            s[rr[i].Lca]-=2;
        }
    }
    if(res==0) return true;
    dfs2(rot,0);
    int maxn=0;
    for(int i=1;i<=n;i++){
        if(s[i]==res) maxn=maxn>val[i]?maxn:val[i]; 
    }
    return maxlen-maxn<=mid;
}//check函数上问有解释
int main(){
	int maxt=0; 
    n=in;m=in;
    for(int i=1;i<n;i++){
        u=in;v=in;t=in;
        add(u,v,t);
        add(v,u,t);
    }
    rot=rand()%n+1;
    dfs(rot,0,1);
    STinit(tim);
    for(int i=1;i<=m;i++){
        rr[i].u=in;rr[i].v=in;
        rr[i].Lca=lca(rr[i].u,rr[i].v);
        rr[i].dis=dis[rr[i].u]+dis[rr[i].v]-2*dis[rr[i].Lca];
        r=r>rr[i].dis?r:rr[i].dis;
    }
    l=maxlen-maxt;maxlen=r;int ans=0;
    while(l<=r){
        int mid=l+r>>1;
        if(check(mid)){
            ans=mid;
            r=mid-1;
        }else l=mid+1;
    }
    printf("%d\n",ans);
    return 0;
}
```

 

