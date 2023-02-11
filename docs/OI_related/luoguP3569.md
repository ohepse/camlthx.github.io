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