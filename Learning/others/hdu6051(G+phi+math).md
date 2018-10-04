**Portal --> hdu6051**

### Solution

​	神仙题qwq好吧我个人感觉是神仙题

​	这题其实有一个比较野路子的做法。。就是。。打表观察。。反正场上ckw大佬就是这样把这题A穿的%%%

​	然而实际上正解很神秘或者说很妙。。虽然说是不是用原根是。。套路？反正记录一下：

​	注意到$P$是奇质数，那么我们可以找到一个模$P$意义下的原根$g$

​	然后因为原根具有一些十分优秀的性质（存在唯一的$a$满足$g^a=x$，其中$x\in [1,p),a\in [1,p)$）所以我们可以开始快乐了

​	我们记$x=g^a,y=g^b(a,b\in [1,p))$，那么原来求$f(i)$的式子可以变成：
$$
\begin{aligned}
(x+y)^i\equiv x^i(mod\ P)\Rightarrow (1+g^{b-a})^i\equiv 1(mod\ P)
\end{aligned}
$$
​	（就是两边同除以$x^i​$）

​	然后因为$1+g^{b-a}>=2$，所以一定存在唯一一个$k\in [1,p-1)$满足：
$$
g^k\equiv1+g^{b-a}(mod \ P)
$$
​	所以我们可以把上面的式子写成：
$$
g^{ki}\equiv 1(mod\ P)
$$
​	也就是说$(P-1)|ki$（因为原根的性质并且$g^{P-1}\equiv 1 (mod\ P)$），那么考虑$k$的取值，我们可以把$k$写成这样：
$$
k=\frac{s(P-1)}{i}=\frac{s'(P-1)}{gcd(P-1,i)}
$$
​	然后因为$k\in [1,P-1)$，所以$s'\in [1,gcd(P-1,i))$，所以$k$总共有$gcd(P-1,i)-1$种取值

​	这个时候反过来想，这$gcd(P-1,i)-1$种取值，对应的是那么多个不同的$k$，再反推回去对应的就是那么多个$b-a$的取值，也就是说当$b$固定的时候，也就是$y$固定的时候，有那么多个$a$可以取（也就是说有那么多个$x$可以取），即对于每一个$y$，能取的$x$都有$gcd(P-1,i)-1$个

​	那所以$f(i)=m(gcd(P-1,i)-1)$

​	（可以这样一路推上去都是因为原根那个一一对应的性质，否则不能进行这么神秘的操作）

​	那所以我们的问题变成了求：
$$
\sum\limits_{i=1}^{P-1}i\cdot m(gcd(P-1,i)-1)
$$
​	这个时候我们就要开始大力化式子了qwq：
$$
\begin{aligned}
&\sum\limits_{i=1}^{P-1}i\cdot m(gcd(P-1,i)-1)\\
=&m(\sum\limits_{i=1}^{P-1}i\cdot gcd(P-1,i)-\sum\limits_{i=1}^{P-1}i)\\
=&m\sum\limits_{d|(P-1)}d\sum\limits_{d|i,1<=i<=P-1}i[gcd(P-1,i)=d]-\frac{m(P-1)(P-2)}{2}\\
=&m\sum\limits_{d|(P-1)}d^2\sum\limits_{i=1}^{\frac{P-1}{d}}i[gcd(\frac{P-1}{d},i)=1]\\
\end{aligned}
$$
​	这个时候我们需要一个黑科技：
$$
\begin{aligned}
&\sum\limits_{i=1}^{n}i[gcd(n,i)=1]\\
=&\frac{1}{2}\sum\limits_{i=1}^n (i+(n-i))[gcd(n,i)=1]\\
=&\frac{n}{2}\sum\limits_{i=1}^n [gcd(n,i)=1]\\
=&\frac{n\cdot \varphi(n)}{2}
\end{aligned}
$$
​	具体为什么的话就是。。如果说我们知道$gcd(n,i)=1$，我们可以推出$gcd(n,n-i)=1$，因为如果$gcd(n,n-i)=x(x>1)$，那么$i=n-(n-i)$应该也是$x$的倍数，所以$gcd(n,i)\neq 1$（最少为$x$），所以矛盾，得证

​	然后我们把每一对$i$和$n-i$凑在一起就是上面那个式子的样子了

​	然后对于$n=1$的情况需要特判一下就是如果$n=1$那么应该是等于$1$，也就是$\frac{n\cdot \varphi(n)+[n=1]}{2}$



​	然后有了这个黑科技我们就可以得到最终的式子：
$$
\begin{aligned}
\sum\limits_{i=1}^{P-1}if(i)
=m\sum\limits_{d|(P-1)}d^2\frac{\frac{P-1}{d}\cdot \varphi(\frac{P-1}{d})+[\frac{P-1}{d}=1]}{2}
\end{aligned}
$$
​	然后$\varphi$的话直接根号求，然后枚举一下因数就好了



​	代码大概长这个样子

```C++
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MOD=1e9+7,inv2=500000004;
int n,m,P,ans,T;
int mul(int x,int y){return 1LL*x*y%MOD;}
int add(int x,int y){return (1LL*x+y)%MOD;}
int Phi(int x){
	int ret=1;
	for (int i=2;i*i<=x;++i){
		if (x%i==0) ret=mul(ret,(i-1)),x/=i;
		while (x%i==0) ret=mul(ret,i),x/=i;
	}
	if (x>1) ret=mul(ret,(x-1));
	return ret;
}
int calc(int n){
	int ret=0,x,tmp;
	for (int i=1;i*i<=n;++i){
		if (n%i) continue;
		x=n/i;
		tmp=add(mul(Phi(x),x),(x==1));
		tmp=mul(1LL*i*i%MOD,tmp);
		ret=add(ret,tmp);

		if (i*i==n) continue;
		x=i;
		tmp=add(mul(Phi(x),x),(x==1));
		tmp=mul(1LL*(n/i)*(n/i)%MOD,tmp);
		ret=add(ret,tmp);
	}
	ret=mul(ret,inv2);
	ret=add(ret,MOD-(1LL*(n+1)*n/2)%MOD);
	return ret;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	int tmp,x;
	scanf("%d",&T);
	for (int o=1;o<=T;++o){
		scanf("%d%d",&m,&P);
		ans=calc(P-1);
		printf("Case #%d: %d\n",o,mul(m,ans));
	}
}
```

