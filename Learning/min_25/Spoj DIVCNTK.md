[Portal -->Spoj DIVCNTK](https://www.spoj.com/problems/DIVCNTK/)

#### Solution

​	这题的话其实是。。洲阁筛模板题？差不多吧

​	题意就是给你一个函数$S_k(x)$
$$
S_k(n)=\sum\limits_{i=1}^{n} \sigma_0(i^k)
$$
​	其中$\sigma_0(x)$表示的是$x$的约数个数，现在已知$n$和$k$求$S_k(n)$ mod $2^{64}$

​	

​	额首先$\sigma_0(x)$是个积性函数

​	然后我们会发现。。这个东西在素数处的取值还是很好求的
$$
\begin{aligned}
&\sigma_0(p)=2\\
&\sigma_0(p^k)=k+1\\
&\sigma_0((p^k)^q)=qk+1\\
\end{aligned}
$$
​	那然后用$g_i$表示$[1,n]$的素数个数，$h_{i,j}$表示$\sum\limits_{k=2}^{i}[k的最小质因子>=P_j]\sigma_0(k)$

​	然后用洲阁筛（或者额。。min_25）的那种方法来搞一下就好了，具体的讲解的话传送一波好了qwq

​	[Portal -->洲阁筛&min_25筛](https://www.cnblogs.com/yoyoball/p/9185144.html)

​	具体的一些实现细节都在上面那篇讲解向博文里面了不想再打一遍了qwq

​	

​	代码大概长这个样子

```C++
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define ll long long
#define ull unsigned long long
using namespace std;
const int MAXN=1e5+10;
ll g[MAXN*2],loc1[MAXN*2],loc2[MAXN*2],rec[MAXN*2];
int P[MAXN];
bool vis[MAXN];
ll n,m,K,cnt,Up,cntval,sq;
ull ans;
void prework(int n);
void init_loc();
int Pos(ll x){return x<=sq?loc1[x]:loc2[n/x];}
void get_g();
ull H(ll i,int j);

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	scanf("%lld%lld",&n,&K);
	sq=sqrt(n)+0.5;
	prework(MAXN);
	init_loc();
	get_g();
	ans=H(n,1)+1;
	printf("%llu\n",ans);
}

void prework(int n){
	cnt=0;
	for (int i=2;i<=n;++i){
		if (!vis[i])
			P[++cnt]=i;
		for (int j=1;j<=cnt&&P[j]*i<=n;++j){
			vis[P[j]*i]=true;
			if (i%P[j]==0) break;
		}
	}
}

void init_loc(){
	cntval=0;
	for (ll i=1,pos;i<=n;i=pos+1){
		rec[++cntval]=n/i;
		pos=n/(n/i);
	}
	reverse(rec+1,rec+1+cntval);
	for (int i=1;i<=cntval;++i)
		if (rec[i]<=sq) loc1[rec[i]]=i;
		else loc2[n/rec[i]]=i;
}

void get_g(){
	for (int i=1;i<=cntval;++i) g[i]=rec[i]-1;
	for (int j=1;j<=cnt&&1LL*P[j]*P[j]<=n;++j)
		for (int i=cntval;i>=1&&rec[i]>=1LL*P[j]*P[j];--i)
			g[i]-=g[Pos(rec[i]/P[j])]-g[Pos(P[j]-1)];
}

ull H(ll i,int j){
	if (i<=1) return 0;
	ull ret=0;
	ll tmp;
	int k;
	for (k=j;k<=cnt&&1LL*P[k]*P[k]<=n&&1LL*P[k]*P[k]<=i;++k){
		tmp=P[k];
		for (int q=1;tmp<=i;tmp*=P[k],++q)
			ret+=(H(i/tmp,k+1)+1)*(q*K+1);
	}
	if (i>=P[k-1])
		ret+=(ull)(K+1)*(g[Pos(i)]-g[Pos(P[k-1])]);
	return ret;
}
```



