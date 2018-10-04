## 问题描述

​	“今有物不知其数，三三数之余二，五五数之余三，七七数之余二。问物几何？”

​	emmm这是。。最开始这个问题被提出来的描述

​	其实说白了就是求解一次同余式组

​	然后还可以。。解决一些。。需要将模数转化成素数来求解的题目

### 具体内容

​	我们还是把这个东西写成数学语言吧，一般化一点的长这样：
$$
\begin{cases}
x\equiv a_1(mod\ m_1)\\
x\equiv a_2(mod\ m_2)\\
x\equiv a_3(mod\ m_3)\\
...\\
x\equiv a_n(mod\ m_n)\\
\end{cases}
$$
​	其中模数$m_i​$两两互素，记$N=\prod\limits_{i=1}^{n}m_i​$，中国剩余定理说的是：这个同余方程组在模$N​$意义下有唯一解，并且给出了一种具体的构造方案（也就是下面的证明）

​	

​	证明：我们首先来考虑一个更加特殊一点的同余方程组
$$
\begin{cases}
x\equiv 1(mod\ m_1)\\
x\equiv 0(mod\ m_2)\\
x\equiv 0(mod\ m_3)\\
...\\
x\equiv 0(mod\ m_n)\\
\end{cases}
$$
​	我们可以大胆令$x=(N/m_1)*y$，然后就会发现这个方程组就等价于求解同余方程：
$$
(N/m_1)*y \equiv1(mod\ m_1)
$$
​	然后对于我们改变一下左边等于$1$的等式是哪一条，如果是第$i$条的话那么就相当于求解：
$$
(N/m_i)*y_i \equiv1(mod\ m_i)
$$
​	那么我们令$x_i=(N/m_i)*y_i$，就可以构造出原来的方程组（余数为$a_i$的那个方程组）在模$N$意义下的唯一解：
$$
x=\prod_{i=1}^n a_ix_i
$$

### 具体实现	

​	那么现在我们只要求出$y_i$就好了，观察这个式子：
$$
(N/m_i)*y_i \equiv1(mod\ m_i)
$$
​	会发现这个$y_i$我们可以用扩展欧几里得求出

​	因为可以看成$y_i(N/m_1)+q\cdot m_1=1$，而因为$m_i$是两两互素的所以$1=gcd(N/m_1,m_1)$

​	那么直接就上扩欧就好啦



​	代码大概长这个样子

```C++
ll ex_gcd(ll a,ll b,ll &x,ll &y){
	if (b==0){x=1; y=0; return a;}
	ll gcd=ex_gcd(b,a%b,x,y),tmp=x;
	x=y; y=tmp-a/b*y;
	return gcd;
}

ll CRT(int *w,int *a,int n){//w数组里面存的是模数，a里面存的是余数
	ll x,y,ret=0,mod=1,tmp;//这里的mod就是相当于上面讲的N啦
	for (int i=1;i<=n;++i) mod*=w[i];
	for (int i=1;i<=n;++i){
		tmp=mod/w[i];
		ex_gcd(w[i],tmp,x,y);
		ret=(ret+y*tmp*a[i])%mod;
	}
	return (ret+mod)%mod;
}
```



### 具体应用

​	应用的话。。其实就是像上面提到的那样，解决一些要拆模数的问题

​	比如说 -->[这题(bzoj3782)](https://www.cnblogs.com/yoyoball/p/9235889.html)

​	简单说一下就是，这题需要用到Lucas定理，但是这个定理有一个限制条件就是模数必须是质数，那么解决方法就是将模数分解质因数一下，然后分别用Lucas定理求出在几个质因数下的答案，最后用CRT（中国剩余定理）合并一下得到在模那个非质数的模数下的答案就好了

​	目前了解到的就主要是这样的类型的qwq

​	在FFT中也有应用，但是还没有去写。。所以先留着坑吧qwq



### 不互质呢？

​	其实中国剩余定理的条件还是有点苛刻的，模数之间要两两互质

​	如果说不能满足这一点呢？

​	其实也是可以做的，这里我们可以采用一个两两合并的思想

​	假设我们现在要合并两个方程：
$$
\begin{cases}
x\equiv a_1(mod\ m_1)\\
x\equiv a_2(mod\ m_2)
\end{cases}
$$
​	但是其中$m_1，m_2$是不互质的

​	我们可以将上面那个方程组写成
$$
\begin{cases}
x=a_1+x_1\cdot m_1&(1)\\
x=a_2+x_2\cdot m_2&(2)
\end{cases}
$$
​	那么：
$$
\begin{aligned}
x_1\cdot m_1-x_2\cdot m_2&=a_2-a_1\\		
m_1\cdot x_1&\equiv a_2-a_1(mod\ m_2)
\end{aligned}
$$
​	然后我们考虑用逆元将系数$m_1$消掉，但是因为无法保证$m_1m_2$互质，所以我们可以先变一下，记$d=gcd(m_1,m_2)$，则：
$$
\begin{aligned}
\frac{m_1}{d}x_1&\equiv \frac{a_2-a_1}{d}(mod\ \frac{m_2}{d})\\
x_1&\equiv inv(\frac{m_1}{d})\frac{a_2-a_1}{d}(mod\ \frac{m_2}{d})\\
\Updownarrow\\
x_1&=a_1+m_1\cdot inv(\frac{m_1}{d})\cdot \frac{a_2-a_1}{d}+\frac{m_2}{d}\cdot y\\
\end{aligned}
$$
​	注意，由扩欧可以知道，只有在满足$d|(a_2-a_1)$的情况下有解

​	然后这个时候我们再将这条$x_1$的表达式带回$(1)$式中，得到：
$$
\begin{aligned}
x&=a_1+m_1\cdot inv(\frac{m_1}{d})\cdot \frac{a_2-a_1}{d}+\frac{m_1m_2}{d}\cdot y\\
\Updownarrow\\
x&\equiv (a_1+m_1\cdot inv(\frac{m_1}{d})\cdot \frac{a_2-a_1}{d})\%\frac{m_1m_2}{d}(mod\ \frac{m_1m_2}{d})
\end{aligned}
$$
​	也就是说，最后我们合并得到的新的式子$x\equiv a'(mod\ m')$中：
$$
\begin{aligned}
a'&=(a_1+m_1\cdot inv(\frac{m_1}{d})\cdot \frac{a_2-a_1}{d})\%\frac{m_1m_2}{d}\\
m'&=\frac{m_1m_2}{d}
\end{aligned}
$$
​	然后多个同余方程的话我们就两个两个一路合并下去就好了



​	代码大概长这个样子

```c++
ll mul(ll x,ll y,ll mod){//这里mul是为了防止模数特别大的情况下爆出去而用的黑科技
	ll tmp=x*y-(ll)((ld)x/mod*y)*mod;
	return (tmp+mod)%mod;
}
ll ex_gcd(ll a1,ll b1,ll &x,ll &y){
	if (!b1){x=1; y=0; return a1;}
	ll gcd=ex_gcd(b1,a1%b1,x,y),tmp=x;
	x=y; y=tmp-a1/b1*y;
	return gcd;
}
ll inv(ll a1,ll mod){
	ll x,y;
	ll gcd=ex_gcd(a1,mod,x,y);
	if (gcd!=1) return -1;
	return (x%mod+mod)%mod;
}
ll ex_CRT(ll *a,ll *mod,int n){
	ll Mod=mod[1],A=a[1],d,tmp,t,x,y,tmpMod;
	for (int i=2;i<=n;++i){
		d=ex_gcd(Mod,mod[i],x,y);
		tmp=a[i]-A;
		if (tmp%d) 
			return -1;
		tmpMod=Mod/d*mod[i];
		A=(A+mul(mul(Mod,inv(Mod/d,mod[i]/d),tmpMod),tmp/d,tmpMod))%tmpMod;
		Mod=tmpMod;
	}
	return (A%Mod+Mod)%Mod;
}
```

