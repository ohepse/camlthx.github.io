### 四中不教数论，只好用九中的进度来学习了

-----
upd 11.18 终于开始教数论力！！！！
-----
# 1.数论基础


# 2.质数
## 2.1 质数的判定
没什么好说的，幼儿园大班的知识。

什么？你说你不知道什么是质数？
~~赶紧滚回去上幼儿园~~

kdw听了都要连夜跑过来打你

## 2.2 质数筛
### 2.2.1 埃氏筛
也不知道 $when how$老师 怎么教的，我一直以为这个叫欧拉筛。

#### 原理：
原理很简单，就是质数的倍数一定不是质数。所以我们就可以这样子求质数。

时间复杂度大概是$O(nlog(log n))$。

~~~cpp
    int isprime[maxn];
    memset(isprime,1,sizeof(isprime));//初始全为1，素数标记为0，合数标记为1
    isprime[2]=0;
    for(int i=2;i<=maxn;i++){
        if(!isprime[i]){
            for(int j=2;j*i<=maxn;j++) isprime[i*j]=1;
        }
    }
   
~~~

### 2.2.2 欧拉筛

这才是正统欧拉筛

#### 2.2.2.1 原理：
跟埃氏筛原理相似。但是埃氏筛有个问题：一个数可能被筛了很多次。欧拉筛保证了每个数只被筛一次，从而降低了时间复杂度。

时间复杂度趋近于$O(n)$。

先贴代码

~~~cpp
    int isprime[maxn],a[maxn],cnt=0;
    memset(isprime,0,sizeof(isprime));//初始全为0，素数标记为1，合数标记为0
    memset(a,0,sizeof(a));
    isprime[2]=1;
    for(int i=2;i<=maxn;i++){
        if(!isprime[i]) a[++cnt]=i;
        for(int j=1;j<=cnt&&i*a[j]<=n;j++){
            isprime[i*a[j]]=0;
            if(i%a[j]==0) break;
        }
    }	


~~~
#### 2.2.2.2 欧拉筛的正确性：
对于 if(i%a[j]==0) break; 这句话，设$i=t*a[j]$ ,如果没有$break$ 句，那么下一次循环会执行到$i*a[j+1]$,可以化成$t*a[j]*a[j+1]$ ，这个数已经是$a[j]$ 的倍数，已经被筛过了，所以应该$break$ 。这句话确保了每个数不会被筛第二遍。

通过下文约数的知识我们可以知道，任意正整数$n$可以写为$n=\prod_{i = 1}^{s}pi^{ki}$ ($pi$为质数，$ki$为$pi$的个数) , 同时筛数的时候表达式为 $i*a[j]$ ,所以不用担心漏筛。


# 3.约数
我们知道任意一个数$n$都可以被表示为
$n=\prod_{i = 1}^{s}pi^{ki}$ ($pi$为质数，$ki$为$pi$的个数)，然后我们就可以解决绝大部分关于约数的问题。

## 3.1 $gcd$与$lcm$
我们幼儿园大班就学过，$gcd(a,b)*lcm(a,b)=a*b$,所以我们只需要用欧几里得求出$gcd$便可以知道$lcm$的值。

$gcd$的 $?:$ 三目运算符 写法

~~~cpp 
int gcd(int a,int b){
    return b?gcd(b,a%b):a;
}
~~~
为了防止爆$long long$ ,要写成 $lcm(a,b)=a/gcd(a,b)*b$

### 3.1.1 二进制算法
当 $gcd$ 的两个参数过大时，可以考虑通过不断除2来降低常数,这种方法又被称为更相减损术。

case 1：$a$ 是偶数且 $b$ 是偶数，$gcd(a,b)=gcd(a/2,b/2)$ ;

case 2：$a$ 是偶数且 $b$ 是奇数，$gcd(a,b)=gcd(a/2,b)$ ;

case 3：$a$ 是奇数且 $b$ 是偶数，$gcd(a,b)=gcd(a,b/2)$ ;

case 4：$a$ 是奇数且 $b$ 是奇数，$gcd(a,b)=gcd(a-b,b)$ ;

由于很好理解，代码就先不贴了

------------

upd 2022.10.7

昨天某个初一的小朋友帮我debug的时候看到我的$gcd$并加以嘲笑，说这么写三目一看就是在压行装逼没没有什么用，还是他的非递归写法好。然后不知道为什么把我的约分函数当做$gcd$，并再次痛斥$gcd$不应该是取模吗为什么要除。

发现自从上了初中接触了玄学竞赛以来，都是喊得$gcd$或者$lcm$，那位小盆友一口一个最大公约数差点把我听蒙了（悲）

------------


有什么还会回来补充的

# 4. 欧拉定理
## 4.1 欧拉函数以及求法
### 4.1.1 欧拉函数$\varphi(n)$的定义
$\varphi(n)$ 表示小于n且与n互质的正整数的个数。

数学语言表达为为 $\varphi(n)=|S|,S=$ { $m|1\leq m < n,gcd(m,n)=1$}。

计算式为 $\varphi(n)=n*\prod_{i=1}^{s}\frac{pi-1}{pi}$ ($pi$为$n$的质因数，$s$为$n$的质因数个数)。

特别的，$\varphi(1)=1$。


### 4.1.2 欧拉函数的性质
1.当n为质数时，$\varphi(n)=n-1$

2.欧拉函数是积性函数，但不是完全积性函数。所以当 $gcd(a,b)=1$ 时, $\varphi(ab)=\varphi(a)\varphi(b)$

3.当$n$为奇数时，$\varphi(2n)=\varphi(n)$

4.当 $a$ % $b$ == $0$ 时，$\varphi(ab)=a\varphi(b)$  (这条定理个人没想明白怎么证的)

5.当p为质数时，$\varphi(p^k)=p^k-p^{k-1}$

[一些证明](https://blog.csdn.net/bcr_233/article/details/92227105)

### 4.1.3 欧拉函数的计算方法
#### 4.1.3.1 根据展开式，可以写出最简单的代码用来求单个数的$\varphi$ (代码来源于oi-wiki)

~~~cpp
int euler_phi(int n) {
  int ans = n;
  for (int i = 2; i * i <= n; i++)
    if (n % i == 0) {
      ans = ans / i * (i - 1);
      while (n % i == 0) n /= i;
    }
  if (n > 1) ans = ans / n * (n - 1);
  return ans;
}
~~~

#### 4.1.3.2 筛法求欧拉函数
我们可以通过欧拉筛同时求出欧拉函数值

需要用到的三个性质：

①当$i$为质数时，$\varphi(i)=i-1$

②当 $a$ % $b$ == $0$ 时，$\varphi(ab)=a\varphi(b)$

③当 $a$ % $b \neq 0$ 时,$\varphi(ab)=\varphi(a)\varphi(b)$

~~~cpp
int prime[maxn],phi[maxn],p[maxn],cnt=0;
void getphi(){
	memset(prime,1,sizeof(prime));
	phi[1]=1;
	for(int i=2;i<maxn;i++){
		if(prime[i]){
			p[++cnt]=i;
			phi[i]=i-1;
		}
		for(int j=1;j<=cnt&&i*p[j]<maxn;j++){
			prime[i*p[j]]=0;
			if(!(i%p[j])){
				phi[i*p[j]]=phi[i]*p[j];
				break;
			}
			else{
				phi[i*p[j]]=phi[i]*phi[p[j]];
			}
		}
	}
}

~~~
## 4.2 欧拉定理&费马小定理
### 4.2.1 欧拉定理：
$ a^{\varphi(n)} \equiv 1 \pmod n $ ,满足 $gcd(a,n)=1$ 

### 4.2.2 费马小定理
特别地，在$n$为素数的时候满足 $a^{n-1} \equiv 1 \pmod n$,为费马小定理

### 4.2.3 扩展欧拉定理
用来解决 $ a^b $ % $m $ 过大的问题，进行降幂操作

$$
a^b \equiv
\begin{cases}
a^{b \text{ mod } \varphi(p)},\quad gcd(a,p)=1\\
a^b ,\quad gcd(a,p) \neq 1 , b< \varphi(p) \text{  (mod p) }\\
a^{b \text{ mod } \varphi(p) +\varphi(p)},\quad gcd(a,p) \neq 1,b \geq \varphi(p)\\
\end{cases}
$$

其中最重要的一条：
$$ \forall a,m\text{ 若 }gcd(a,m)=1 \text{ , } a^b \equiv a^{b \text{ mod }\varphi(m)+\varphi(m) } (\text{ mod } m)
$$

若 $m$ 是质数时，可以直接使用费马小定理。
____

比如这道题：[Luogu P4139 上帝与集合的正确用法](https://www.luogu.com.cn/problem/P4139) 是一道模板题。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e7+5;
int phi[maxn],prime[maxn],p[maxn],cnt=0;
void pre(){
	for(int i=2;i<maxn;i++){
		if(!prime[i]){
			p[++cnt]=i;
			phi[i]=i-1;
		}
		for(int j=1;j<=cnt&&i*p[j]<maxn;j++){
			prime[i*p[j]]=1;
			if(i%p[j]==0){
				phi[i*p[j]]=phi[i]*p[j];
				break;
			}
			else phi[i*p[j]]=phi[i]*(p[j]-1); 
		}
	}
}
int mul(int a,int b,int mod){
	int res=0;
	while(b){
		if(b&1) res=(res+a)%mod;
		a=(a+a)%mod;
		b>>=1;
	}
	return res;
}
int qukpow(int a,int b,int mod){
	int res=1;
	while(b){
		if(b&1) res=mul(res,a,mod);
		a=mul(a,a,mod);
		b>>=1;
	}
	return res; 
}
int solve(int p){
	if(p==1) return 0;
	return qukpow(2,solve(phi[p])+phi[p],p);
}
int t,pp;
int main(){
	ios::sync_with_stdio(false);
	cin>>t;
	pre();
	while(t--){
		cin>>pp;
		cout<<solve(pp)<<"\n";
	}
	return 0;
}
```
但是听说用展开式求 $\varphi$ 在加个记搜比线性筛更快。

# 5.欧几里得
## 5.1 欧几里得算法
主要用于求解两个数$a$和$b$的最大公约数,我们不妨设$(a>b)$,其公式为$gcd(a,b)=gcd(b,a \text{ mod } b)=gcd(a \text{ mod } b,b \text{ mod } (a \text{ mod } b))= \ldots =gcd(x,0)$,这里的$x$即为最大公约数

可用于求上文 约数 章节所提到的 $gcd$ 和 $lcm$ 

注意：欧几里得算法的一点要求是$a>b$

## 5.2裴蜀定理
又称贝祖定理。

**定义**：对于整数$a$和$b$以及它们的$gcd(a,b)=d$ ,可以得出存在任意的整数$x$和$y$,使得$ax+by=m$, $m$一定是d的整数倍，且存在$ax+by=d$。当$gcd(a,b)=1$时，存在唯一的一组 $ax+by=1$。

不想写证明了。
## 5.3扩展欧几里得算法（扩欧）
应用1：此算法用来求解 $ax+by=gcd(a,b)$ 的一组可行解。

根据裴蜀定理，该方程一定有解。
    
①：$ax_0+by_0=gcd(a,b)$

②：$bx_1+(a \text{ mod } b)y_1=gcd(b,a \text{ mod } b)$

$\because gcd(a,b)=gcd(b,a \text{ mod } b)$ 

$\therefore ax_0+by_0=bx_1+(a \text{ mod } b)y_1$  ③

$a \text{ mod }b=a- \lfloor a/b \rfloor* b $ ④
    
将④代入③中可得：

$ax_0+by_0=bx_1+(a-\lfloor a/b\rfloor*b)y_1$

解得：

$x_0=y_1,y_0=x_1-\lfloor a/b \rfloor *y_1$

不难发现，$x_0,y_0$ 的 值由$x_1,y_1$ 的值迭代而来。

所以可以通过递归的方式求出可行解

对于递归出口 , 当 $ax+by=gcd(a,0), ax+ by=a$ ,此时的子解为 $x=1,y=0$

用代码实现就是：

   ~~~cpp
    int exgcd(int a, int b, int &x, int &y){
        if (!b){
            x = 1; y = 0;
            return a;   
        }
        int d = exgcd(b, a % b, x, y);
        int temp=y;    
        y=x-(a/b)*y;
        x=temp;
        return d;
    }
   

   ~~~

假设 $x_1$ , $y_1$ , $x_2$ , $y_2$ 是方程的两组解，则：

$ax_1+by_1=c$

$ax_2+by_2=c$

两式子相减得 $a(x_1-x_2)+b(y_1-y_2)=0$ 

令 $d=gcd(a,b)$

有：$(a/d)(x_1-x_2)+(b/d)(y_1-y_2)=0$

此时，$a/d$ 与 $b/d$ 互质，则 $x_1-x_2=(b/d)(y_2-y_1)/(a/d)=k*(b/d)$

则通解可以表示为为：$x=x_0+k*(b/d)$ 。

所以，最小整数解 $x=(x_0 \text{ mod }(b/d)+b/d)\text{ mod }(b/d)$

其中 $x_0$ 是任意解


# 6.逆元
## 6.1 逆元的定义
即 $ax \equiv 1 (\text{ mod } b)$ 的一组解