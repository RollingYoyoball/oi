[**Portal --> bzoj4002**](https://www.lydsy.com/JudgeOnline/problem.php?id=4002)

### Solution

​	虽然说这题有点强行但是感觉还是挺妙的，给你通项让你反推数列的这种==有点毒

​	补档时间

​	首先有一个东西叫做特征方程，我们可以用这个东西来求二阶线性递推数列的通项：

​	对于数列$\{x_n\}$，递推公式为$x_n=a_1x_{n-1}-a_2x_{n-2}$，那么这个数列的特征方程为:
$$
x^2-a_1x+a_2=0
$$
​	如果说这个方程有两个相异的根$p,q$，那么：
$$
\begin{aligned}
A&=\frac{x_2-qx_1}{p(p-q)}\\
B&=\frac{px_1-x_2}{q(p-q)}\\
x_n&=Ap^n+Bq^n
\end{aligned}
$$
​	如果有两个相等的根$p$，那么：
$$
\begin{aligned}
A=\frac{px_1-x_2}{p^2}\\
B=\frac{x_2-px_1}{p^2}\\
x_n=(A+Bn)p^n
\end{aligned}
$$
​	

​	然后我们看回这题

​	有个奇奇怪怪的条件：$b^2< = d<(b+1)^2 $，这个条件说明什么呢？会发现因为这个条件所以$0>=\frac{b-\sqrt d}{2}>-0.5$

​	但是我们要求的是$\lfloor(\frac{b+\sqrt d}{2})^n\rfloor$，那么这个时候我们会发现。。其实我们把这个式子稍微变一下变成：
$$
\lfloor(\frac{b+\sqrt d}{2})^n+(\frac{b-\sqrt d}{2})^n-(\frac{b-\sqrt d}{2})^n\rfloor
$$
​	就好了

​	为什么变成这样呢？首先前面那个东西，我们会发现其实就是。。用特征方程中有相异两根求出的通项式的类似形式，所以我们只要令这两个根为$(\lfloor \frac{b+\sqrt d}{2}\rfloor)^n​$和$(\lfloor \frac{b-\sqrt d}{2}\rfloor)^n​$就好了，然后$A​$和$B​$这两个系数要为$1​$，这样我们就可以求出$x_1​$和$x_2​$和$a_1​$和$a_2​$：
$$
\begin{aligned}
p&=\frac{b+\sqrt d}{2}&&q=\frac{b-\sqrt d}{2}\\
x_1&=p+q&&x_2=p^2+q^2\\
a_1&=b&&a_2=\frac{b^2-d}{4}
\end{aligned}
$$
​	然后！因为题目的条件： b mod 2=1,d mod 4=1 ，所以我们发现$a_1$和$a_2$都是整数，$x_1$和$x_2$也都是整数，所以！前半部分的答案一定是一个整数（然而其实好像可以直接用一个叫做共轭根式的东西说明但是我不太会那个东西qwq）

​	然后这个时候如果是要求那个式子的下取整的话我们直接判断一下$\frac{b-\sqrt d}{2}$是否大于等于$1$即可，会发现只有在$n$是偶数并且$b^2\neq d$的情况下减去这个部分会导致整体的下取整少一，特判一下就好了

​	至于前半部分直接矩阵快速幂求出$x_n$即可

​	然后最后还有一个小问题，就是。。这个模数有点令人难受

​	这个时候我们需要。。一个小技巧来处理一下加法和乘法：加法的话直接就先减去一个模数然后如果小于$0$再加上模数，乘法的话就像快速幂一样处理就好了



​	代码大概长这个样子

```C++
#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;
const ll MOD=7528443412579576937;
ll add(ll x,ll y){
	ll tmp=-MOD+x+y;
	if (tmp<0) tmp+=MOD;
	return tmp;
}
ll mul(ll x,ll y){
	ll ret=0;
	for (;y;y>>=1,x=add(x,x))
		if (y&1) ret=add(ret,x);
	return ret;
}
struct Mtrix{/*{{{*/
	ll a[2][2];
	void init(){memset(a,0,sizeof(a));}
	void setUnit(){for (int i=0;i<2;++i) for (int j=0;j<2;++j) a[i][j]=i==j;}
	friend Mtrix operator * (Mtrix x,Mtrix y){
		Mtrix ret;
		for (int i=0;i<2;++i)
			for (int j=0;j<2;++j){
				ret.a[i][j]=0;
				for (int k=0;k<2;++k)
					ret.a[i][j]=add(ret.a[i][j],mul(x.a[i][k],y.a[k][j]));
			}
		return ret;
	}
}ori,ret,base,ans;/*}}}*/
ll n,m,Ans,d,b;
void ksm(ll y){
	ret.setUnit(); base=ori;
	for (;y;y>>=1,base=base*base)
		if (y&1) ret=ret*base;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	scanf("%lld%lld%lld\n",&b,&d,&n);
	if (n==0){printf("1\n");return 0;}
	ori.init();
	ori.a[1][1]=b;ori.a[0][1]=-(b*b-d)/4;
	ori.a[1][0]=1;
	ans.init();
	ans.a[0][0]=b; ans.a[0][1]=(b*b+d)/2;
	if (n>=2) 
		ksm(n-2),ans=ans*ret;
	if (n==1) Ans=ans.a[0][0];
	else Ans=ans.a[0][1];
	if (b*b!=d&&n%2==0) Ans=add(Ans,MOD-1);
	printf("%lld\n",Ans);
}
```





​	