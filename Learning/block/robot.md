Portal -->broken qwq

### Description

​	  给定$n$和$k$，我们要在$1,2,3,...,n$中选择若干的数，每一种选择的方案被称为选数方案。

​	我们定义一种选数方案是**合法**的，当且仅当$k$没有被选，且任意两个选的数互质。

​	我们定义一种选数方案是**极大**的，当且仅当它是合法的，且不能再从剩下的数中选择任意一个，或者选的是$k$。

​	极大的选数方案的最小的选的个数。 

​	数据范围：多组数据，数据组数$T<=50​$，$1<=n<=1000,1<=k<=n​$，$k​$不是质数

### Solution

​	这种互质的题有一个比较有效的方法，我们可以将每一个数的质因子分成两类，一类是$<=\sqrt n$的，一类是$>\sqrt n$的，不难注意到$>\sqrt n$的质因子最多只能有一个

​	这题的话我们发现$<=\sqrt n$的质数其实很少，只有$11$个，所以可以考虑状压

​	在dp之前我们要先想一下对于那些含有$>\sqrt n$质因子的数要怎么处理，其实仔细想一下会发现比如说$>\sqrt n$的质因子集合为$\{a_1,a_2,a_3...a_m\}$，那么最起码这$m$个数都要选，所以我们直接将这部分加到答案里面去就好了

​	那接下来我们就只用考虑不含$>\sqrt n$质因子的数了

​	记$f[i][j]$表示前$i$个数中选出数的质因子的并的状态为$j$，$j$是一个二进制，表示选出来的数中都出现了哪些质数（按编号来存，比如$2$是第一个质数对应的状态就是$2^0$，$3$是第二个质数所以对应$2^1$，以此类推）

​	假设我们当前考虑第$i$个数（也就是$i$啦。。）的转移，只有在$j$这个状态中不存在$i$的任意一个质因子的时候才可以将$i$选进来（不然就不互质了），我们用$st(i)$表示$i$这个数的质因数的状态，那么也就是在$j\&st(i)$为$0$的时候有：
$$
f[i][j|st(i)]=min(f[i-1][j|st(i)],f[i-1][j]+1-(i是否含有>\sqrt n的质因数))
$$
​	当$i$含有$>\sqrt n$的质因数的时候要将其$-1$不算贡献是因为所有含有$>\sqrt n$的数已经在最开始的时候加到答案里面去了（就是那个$m$个数），不能再选

​	那最后的问题就是空间，滚动一下把第一维滚动掉就好了ovo

​	然后的话就是需要预处理的东西有：质数表，每个数的质因数的状态，每个数的最大质因子（用来判断是否含有$>\sqrt n$的质因数）



​	代码大概长这个样子

```C++
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N=1010,inf=2147483647;
int mxp[N],p[N],st[N],f[2][1<<12];
int vis[N];
int n,m,cnt,K,ans,all,T;
void prework(int n){
	mxp[1]=1; cnt=0; 
	for (int i=2;i<=n;++i){
		if (!vis[i]){
			mxp[i]=i; p[++cnt]=i;
			st[i]=(i<=31?1<<cnt-1:0);
		}
		for (int j=1;j<=cnt&&p[j]*i<=n;++j){
			vis[i*p[j]]=true;
			if (i*p[j]==74)
				int debug=1;
			mxp[i*p[j]]=max(p[j],mxp[i]);
			st[i*p[j]]=st[i]|(p[j]<=31?st[p[j]]:0);
			if (i%p[j]==0) continue;
		}
	}
}
bool ok(int St,int x){return (St&st[x])==0;}
void solve(){
	m=1;
	while (p[m]<=n) ++m;
	--m;
	ans=max(0,m-11);
	m=min(m,11);
	all=1<<m;
	int now=1,pre=0;
	for (int i=0;i<all;++i) f[0][i]=inf;
	f[0][0]=0;
	for (int i=1;i<=n;++i){
		for (int j=0;j<all;++j) f[now][j]=f[pre][j];
		f[now][0]=0;
		for (int j=0;j<all;++j){
			if (!ok(j,i)) continue;
			if (((j|st[i])<all)&&f[pre][j]!=inf&&i!=K)
				f[now][j|st[i]]=min(f[pre][j|st[i]],f[pre][j]+1-(mxp[i]>31));
		}
		swap(now,pre);
	}
	printf("%d\n",f[pre][all-1]+ans+(K!=1));
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	scanf("%d",&T);
	prework(1000);
	for (int o=1;o<=T;++o){
		scanf("%d%d",&n,&K);
		printf("Case #%d: ",o);
		solve();
	}
}
```

