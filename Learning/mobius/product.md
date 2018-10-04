**Portal -->broken qwq**

### Description

​	求$\prod\limits_{i=1}^n\prod\limits_{j=1}^m f[gcd(i,j)](mod\ 10^9+7)$，其中$f[0]=0,f[1]=1,f[i]=f[i-1]+f[i-2]$

​	数据范围：多组数据，数据组数$T<=1000,1<=n,m<=10^6$

### Solution

​	这题。。一开始我觉得这题好像直接求个范围内$gcd(i,j)=d$的对数就做完了qwq

​	式子长这个样子
$$
\begin{aligned}
Ans&=\prod\limits_{d=1}^{min(n,m)}f(d)^{s(d)}\\
s(d)&=\sum\limits_{i=1}^n\sum\limits_{j=1}^m[gcd(i,j)=d]\\
&=\sum\limits_{k=1}^{\lfloor\frac{min(n,m)}{d}\rfloor}\mu(k)\lfloor\frac{n}{kd}\rfloor\lfloor\frac{m}{kd}\rfloor
\end{aligned}
$$
​	然后发现单组$O(n\sqrt n logn)$然后数据组数$1000$==（不过还是有60）

​	

​	正解并没有题面那么简单qwq实际上正解很妙qwq

​	我们考虑构造一个函数$g(x)$，满足：
$$
f[n]=\prod\limits_{d|n}g(d)
$$
​	这样一来我们就可以把原来的式子化一下变成：
$$
\begin{aligned}
&\prod\limits_{i=1}^n\prod\limits_{j=1}^mf[gcd(i,j)]\\
=&\prod\limits_{i=1}^n\prod\limits_{j=1}^m\prod_{d|i,d|j}g(d)\\
=&\prod\limits_{d=1}^{min(n,m)}g(d)^{\lfloor\frac{n}{d}\rfloor\lfloor\frac{m}{d}\rfloor}
\end{aligned}
$$
​	然后这样我们就不用再在外面枚举一次了，复杂度$O(\sqrt nlogn)$

​	前提是我们知道$g(d)$的前缀积

​	这个东西长得跟反演式子差不多，考虑反演式子的容斥解释，本质上就是容斥的加加减减，换成乘法的话就是乘除就好了，所以我们直接将$\mu$搬到指数上面就好了
$$
g(n)=\prod\limits_{d|n}f(d)^{\mu(\frac{n}{d})}
$$
​	这个可以大力枚举约数什么的直接预处理

​	然后这题就做完啦ovo



​	代码大概长这个样子

```C++
#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;
const int N=1e6+10,MOD=1e9+7;
int f[N],g[N],p[N],miu[N],invf[N],invg[N];
int vis[N];
int n,m,T,ans;
int add(int x,int y){return (1LL*x+MOD+y)%MOD;}
int mul(int x,int y){return 1LL*x*y%MOD;}
int ksm(int x,ll y){
	int ret=1,base=x;
	for (;y;y>>=1,base=mul(base,base))
		if (y&1) ret=mul(ret,base);
	return ret;
}
int inv(int x){return ksm(x,MOD-2);}
void prework(int n){
	int cnt=0;
	miu[1]=1;
	for (int i=2;i<=n;++i){
		if (!vis[i])
			p[++cnt]=i,miu[i]=-1;
		for (int j=1;j<=cnt&&p[j]*i<=n;++j){
			vis[i*p[j]]=true;
			if (i%p[j]==0){
				miu[i*p[j]]=0;
				break;
			}
			else
				miu[i*p[j]]=-miu[i];
		}
	}
	f[0]=0; f[1]=1; g[1]=1;
	for (int i=2;i<=n;++i) f[i]=add(f[i-1],f[i-2]),g[i]=1;
	for (int i=1;i<=n;++i) invf[i]=inv(f[i]);
	for (int i=1;i<=n;++i)
		for (int j=i;j<=n;j+=i){
			if (miu[j/i]==-1) 
				g[j]=mul(g[j],invf[i]);
			else if (miu[j/i]==1)
				g[j]=mul(g[j],f[i]);
		}
	for (int i=2;i<=n;++i) g[i]=mul(g[i],g[i-1]);
	invg[0]=1;
	for (int i=1;i<=n;++i) invg[i]=inv(g[i]);
}
int solve(){
	int ret=1;
	if (n>m) swap(n,m);
	for (int i=1,pos=0;i<=n;i=pos+1){
		pos=min(n/(n/i),m/(m/i));
		ret=mul(ret,ksm(mul(g[pos],invg[i-1]),1LL*(n/i)*(m/i)));
	}
	return ret;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	scanf("%d",&T);
	prework(N-10);
	for (int o=1;o<=T;++o){
		scanf("%d%d",&n,&m);
		ans=solve();		
		printf("%d\n",ans);
	}
}
```

