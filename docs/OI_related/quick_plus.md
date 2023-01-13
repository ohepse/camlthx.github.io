## background：
当两个 $long long$ 相乘时，很容易爆，但是如果直接写高精度那就亏大发了。

## solution 1：
可以使用一种类似快速幂的方法，只是吧乘法操作变成加法操作。

```cpp
inline ll quickmul(ll a,ll b,ll mod){
	ll res=0;
	while(b){
		if(b&1) res=(res+a)%mod;
		a=(a+a)%mod;
		b>>=1;
	}
	return res;
}

```

## solution 2:
有一种 $O(1)$ 的做法。

实际上，并不建议在比赛中使用 $O(1)$ 快速乘，除非题目非常需要卡常，毕竟浮点的精度不能保证。

```cpp
inline llquckmul(ll a,ll b,ll mod){
	return (a*b-(ll)((long double)a/mod*b)*mod+mod)%mod;
}
 
```
关于原理：

首先，$long long$ 的溢出相当于自动取反和自动取模。而此方法的正确性就是取模的时候模数是一定的。

这里 $longdouble$ 计算出了 $a * b/mod$ ，同时避免了本来可能的一次溢出的 $a* b$ ，这次溢出的可能导致计算错误的（因为后面又除法，所以不能保证正确性），显然 $a/mod$ 与 $b$ 相乘任可能导致溢出，但这次溢出无关紧要。因为在取模可以进行除法。

而转会 $longlong$ 就是为了最后能够取模。

而由于两边可能有或没有溢出，而溢出时取的模数时一定的，所以我们将它们相减后可能得到的答案一定在64位带符号长整型范围内，并且只可能是正确的余数 remainder 或 remainder—mod 。



--摘自LDW的学案

