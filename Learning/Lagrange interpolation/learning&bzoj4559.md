[**Portal -->bzoj4559**](https://www.lydsy.com/JudgeOnline/problem.php?id=4559)

### 补档计划

​	借这题补个档——拉格朗日插值

​	插值的话大概就是有一个$n-1$次多项式$A(x)$，你只知道它在$n$处的点值，分别是$(x_1,y_1),(x_2,y_2),...,(x_{n},y_{n})$，让你还原这个多项式

​	关于插值我们有很多的方法，有十分粗暴的高消$O(n^3)$，也有十分优秀的快速差值（不会qwq），还有拉格朗日插值法$O(n^2)$（emmm如果说取值位置连续的话。。可以做到$O(n)$）

​	其实拉格朗日差值的核心就是这两条式子：
$$
l_j(x)=\sum\limits_{i=0,i\neq j}^n\frac{x-x_i}{x_j-x_i}\\
A(x)=\sum\limits_{i=1}^{n}y_i\cdot l_i(x)
$$
​	具体为什么的话就是，首先有$n$个处点值是可以确定一个$n-1$次多项式，并且这个多项式是惟一的，那么接下来就是看为什么这样构造是满足条件的：我们观察$l_j(x)$这个多项式的值，当代进去的值为$x_i$中的其中一个时，这个多项式才会为$1$，否则为$0$，所以乘上一个$y_i$然后求一下和就可以满足这$n$处的取值了

​	然后就是这个东西怎么比较。。快一点的求

​	大概是。。我们可以先求出$C(x)=\sum\limits_{i=1}^n(x-x_i)$这个多项式各项系数（可以在$O(n)$的时间内得到，具体的话就是考虑每次暴力拆括号然后未知数的幂指数$+1$，然后系数要乘上$-x_i$），求出这个东西之后，我们就可以在$O(n)$的时间内求出$B_j(x)=\sum\limits_{i=1,i\neq j}^n(x-x_i)$（具体就是直接考虑将$(x-x_j)$这项的贡献去掉就好了），然后我们又可以用$B_j(x)$求出分母然后其他的随便乱搞都可以了

​	那为什么说取值位置连续的话可以$O(n)​$呢？其实。。因为是连续的所以我们的分子可以用阶乘什么的乱搞，然后分母维护一个前缀乘积，一个后缀乘积就好了（实际上好像前缀成绩后缀乘积这个东西完全可以在非连续情况下使用但是反正分母那里要$O(n)​$又何必搞那么麻烦呢嘿嘿。。。）

​	这里贴一下非连续取值的时候的代码（虽然说这题根本不用不过反正都是补档嘛。。一起写好了）

```C++
void solve(int n){
	memset(c,0,sizeof(c));
	c[0]=1;
	for (int i=1;i<=n;++i){
		for (int j=n;j>=0;--j){
			c[j+1]=(c[j+1]+c[j])%MOD;
			c[j]=(-c[j]*X[i])%MOD;
		}
	}//get 系数 of \prod_{i=0}^k (x-x_i)
	ll s=0,tmp=1;
	for (int i=1;i<=n;++i){
		memcpy(d,c,sizeof(d));
		memset(b,0,sizeof(b));
		for (int j=n;j>=0;--j){
			b[j]=d[j+1];
			d[j]=(d[j]+d[j+1]*X[i])%MOD;
			d[j+1]=0;
		}//take (x-x_i) out of \prod_{j=0}^k (x-x_j)
		s=0,tmp=1;
		for (int j=0;j<=n;++j){
			s=(s+tmp*b[j])%MOD;
			tmp=tmp*X[i]%MOD;
		}//get \prod_{j=0,j!=i}^k (x_i-x_j)
		
		s=ksm(s,MOD-2)*Y[i]%MOD;
		for (int j=0;j<=n;++j) b[j]=b[j]*s%MOD;//get the final 系数
		for (int j=0;j<=n;++j)
			ans[j]=(ans[j]+b[j])%MOD;
	}
}
```



### Solution	

​	然后我们来看这题

​	这题的做法很多。。网上有十分优秀的根本不需要拉格朗日插值的做法。。但是我比较菜所以。。

​	考虑一下这个答案要怎么算，因为题目的限制条件有点多所以我们考虑将它拆成两个部分来想：

1.先不管具体分数是多少，只考虑相对大小，求出满足有恰好$K$个人各门分数都小于等于$B$神的方案数，记为$ans1$

2.算具体分数是多少

​	那么最后的答案就应该是$ans1$再乘上对应的第二部分中具体分数不同的贡献

​	我们先来考虑第一部分，这里。。我们考虑用dp+容斥来求解（注意，接下来的dp中所有的转移都不考虑每个人的具体得分，我们在第一部分的求解中只考虑相对大小）

​	记$f[i]$表示至少$i$个人满足条件的方案数，那么我们可以得到：
$$
f[i]=\binom{n-1}i \prod\limits_{j=1}^m \binom{n-1-i}{R_j-1}
$$
​	其中$R_j$表示的是$B$神在第$j$门科目中的排名，这个式子具体一点的含义的话就是：首先我们需要钦定$i$个人是满足条件的，所以总共是$\binom {n-1}i$中选法，然后在钦定了$i$个人一定排在$B$神之后的前提下，我们对于每一门科目又要满足有$R_j-1$个人分数大于$B$神，那只能从$n-1-i$个人中选，所以就是后面的按个组合数了

​	有了这个东西之后我们构造一下容斥系数$a(i)$：
$$
ans1=\sum\limits_{i=K}^na(i)f[i]
$$
​	其实仔细想一下就可以得出：
$$
ans1=\sum\limits_{i=K}^n(-1)^{K-i}\binom i Kf[i]
$$
​	具体一点就是你考虑$f[i]$的含义就是至少$i$个人满足条件，那么这个$K$个人中一旦有$i$个人是被钦定的，$f[i]$就会被算一次，所以乘个系数就好了



​	然后第一部分我们就算完了

​	接着是第二部分（这部分才到插值==）

​	第二部分的话，我们要考虑每个人具体是什么分数了，我们要求的东西其实就是要求有$x$个人比$B$神低，$y$个人比$B$神高的分数有多少种（与第一部分不同的是，这里不需要考虑具体是哪一个人，而是考虑分数）

​	那么对于一门科目$i$，我们有$y=R_i-1,x=(n-1)-y$，	所以我们只要枚举一下$B$神的分数就好了：
$$
\sum\limits_{j=1}^{U_i}(U_i-j)^{R_i-1}\cdot j^{(n-1)-(R_i-1)}
$$
​	其中$U_i$表示这门科目分数上限

​	那么所有的科目的总贡献就是：
$$
ans2=\prod\limits_{i=1}^m\sum\limits_{j=1}^{U_i}(U_i-j)^{R_i-1}\cdot j^{(n-1)-(R_i-1)}
$$
​	最终答案就是$ans1*ans2$啦

​	但是我们看$U_i$的范围是$10^9$，所以。。不能直接算，又发现如果说我们将$U_i$看成一个变量的话，每门科目的贡献可以看成一个$n$次多项式$P(x)$（次数最高只能到$n$），那所以我们可以先暴力带入$x=0...n$，然后把这$n+1$个点值算出来，然后每次$O(n^2)$求值就好了（具体的话就是直接代进拉格朗日插值的那条式子）

​	总的时间复杂度$O(n^3)$（其实。。求值好像可以做到每次$O(n)$的。。不过$n=100$我就写了最暴力的这种了qwq）

​	

​	代码大概长这个样子

```C++
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N=110,MOD=1e9+7;
int u[N],r[N],f[N],c[N][N],g[N];
int n,m,K,ans1,ans2;
int add(int x,int y){return (1LL*x+y)%MOD;}
int mul(int x,int y){return 1LL*x*y%MOD;}
void predp(){
	c[0][0]=1;
	for (int i=1;i<=n;++i){
		c[i][0]=1; c[i][i]=1;
		for (int j=1;j<i;++j)
			c[i][j]=add(c[i-1][j],c[i-1][j-1]);
	}
	for (int i=1;i<=n;++i){
		f[i]=c[n-1][i];
		for (int j=1;j<=m;++j)
			f[i]=mul(f[i],c[n-1-i][r[j]-1]);
	}
}
int ksm(int x,int y){
	int ret=1,base=x;
	for (;y;y>>=1,base=mul(base,base))
		if (y&1) ret=mul(ret,base);
	return ret;
}
void precalc(int U,int R,int &val){
	int tmp;
	val=0;
	for (int i=1;i<=U;++i){
		tmp=mul(ksm(U-i,R-1),ksm(i,(n-1)-(R-1)));
		val=add(val,tmp);
	}
}
int calc(int x){
	int fz,fm,ret=0;
	for (int i=0;i<=n;++i){
		fz=1; fm=1;
		for (int j=0;j<=n;++j){
			if (j==i) continue;
			fz=mul(fz,(x-j+MOD)%MOD);
			fm=mul(fm,(i-j+MOD)%MOD);
		}
		ret=add(ret,1LL*fz*ksm(fm,MOD-2)%MOD*g[i]%MOD);
	}
	return ret;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	scanf("%d%d%d",&n,&m,&K);
	for (int i=1;i<=m;++i) scanf("%d",u+i);
	for (int i=1;i<=m;++i) scanf("%d",r+i);
	predp();
	ans1=0;
	for (int i=K;i<=n;++i){
		if ((K-i)%2==0)
			ans1=add(ans1,mul(c[i][K],f[i]));
		else
			ans1=add(ans1,(1LL*MOD-mul(c[i][K],f[i]))%MOD);
	}
	ans2=1;
	for (int i=1;i<=m;++i){
		if (i==6)
			int debug=1;
		for (int j=0;j<=n;++j)
			precalc(j,r[i],g[j]);
		ans2=mul(ans2,calc(u[i]));
	}
	printf("%d\n",mul(ans1,ans2));
}
```

