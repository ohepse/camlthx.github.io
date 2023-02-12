#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+10;
const int inf=0x7fffffff;
struct edge{
	int u,v,w,nxt;
}e[maxn<<2];
int cnt,h[maxn<<1];
void add(int u,int v,int w){
	e[++cnt]=(edge){u,v,w,h[u]};
	h[u]=cnt;
}
int n,a[maxn],dis[maxn];
struct node{
	int v,w;
	friend bool operator <(const node &a,const node &b){
		return a.w>b.w;
	}
};
priority_queue<node> q;
void dijstra(int be){
	for(int i=1;i<maxn;i++) dis[i]=inf;
	dis[be]=0;
	q.push((node){be,0});
	while(!q.empty()){
		int u=q.top().v,dist=q.top().w;q.pop();
		if(dist!=dis[u]) continue;
		for(int i=h[u];i;i=e[i].nxt){
			int v=e[i].v;
			if(dis[v]>dis[u]+e[i].w){
				dis[v]=dis[u]+e[i].w;
				q.push((node){v,dis[v]});
			}
		}
	} 
}
int main(){
	freopen("5.in","r",stdin);
	double st=clock();
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	int minn=inf;
	for(int i=1;i<=n;i++){
		minn=min(minn,i+a[i]+1);
		if(i+a[i]<=n) add(i,i+a[i]+1,0);
		else add(i,n+1,i+a[i]-n);
	}
	for(int i=minn;i<=n;i++) add(i,i+1,1);
	for(int i=1;i<=n;i++) add(i+1,i,1);
	dijstra(1);
	printf("%d\n",dis[n+1]);
	double ed=clock();
	printf("%.3lfms\n",ed-st);
	return 0;
} 
