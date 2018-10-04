**Portal -->broken qwq**

### Description

​	给你一个长度为$n$的序列，序列中的每个数都是不超过$m$的正整数，求满足以下两个条件的序列数量：

1.序列中至少有一个质数

2.序列中$n$个数之和为$p$的倍数

​	数据范围：$1<=n<=10^9,1<=m<=2*10^7,1<=p<=100$

### Solution

​	我的妈呀真实智力康复。。为什么连最基础的矩乘优化都忘了==

​	记$f[i][j]$表示前$i$个数和模$p$为$j$的答案，然后转移我们矩乘一下就好了

​	至于必须满足其中一个数是质数，我们考虑容斥，先算出所有的，然后再把所有的素数去掉再算一遍转移矩阵，然后再算一次答案两个相减就好了

​	然而如果像我一开始一样弱智写了个$n^3$矩乘只能拿$50$

​	这题实际上可以直接$f[i+1][(j+k)\%p]=f[i][j]*f[i][k]$就完事了，所以只要$n^2$就好了，真实智力康复qwq



​	代码大概长这个样子

```C++
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int M=2*(1e7)+10,MOD=20170408;
int add(int x,int y){return (1LL*x+y)%MOD;}
int mul(int x,int y){return 1LL*x*y%MOD;}
int n,m,p,Ans1,Ans2,cnt;
struct Mtrix{/*{{{*/
	int a[110];
	int n;
	void init(int _n){n=_n;memset(a,0,sizeof(a));}
	void setUnit(int _n){init(_n);a[0]=1;}
	friend Mtrix operator * (Mtrix &x,Mtrix &y){
		int tmp;
		Mtrix ret;
		ret.init(x.n);
		for (int i=0;i<ret.n;++i)
			for(int j=0;j<ret.n;++j){
				tmp=(i+j)%p;
				ret.a[tmp]=add(ret.a[tmp],mul(x.a[i],y.a[j]));
			}
		return ret;
	}
}ori,ret,base,ans1,ans2,tmp;/*}}}*/
bool vis[M];
int P[1500000];
int get_pos(int x,int y){return (x-y+p)%p;}
void fill(int op){
	int tmp;
	ori.init(p);
	for (int i=1;i<=m;++i){
		if (op==1&&!vis[i]) continue;
		ori.a[i%p]=add(ori.a[i%p],1);
	}
}
void ksm(int y){
	ret.setUnit(p); base=ori;
	for (;y;y>>=1,base=base*base)
		if (y&1) ret=ret*base;
}
void prework(int n){
	cnt=0;
	vis[1]=1;
	for (int i=2;i<=n;++i){
		if (!vis[i])
			P[++cnt]=i;
		for (int j=1;j<=cnt&&P[j]*i<=n;++j){
			vis[i*P[j]]=true;
			if (i%P[j]==0)
				break;
		}
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	scanf("%d%d%d",&n,&m,&p);
	prework(m);
	fill(0);
	ksm(n);
	Ans1=ret.a[0];

	fill(1);
	ksm(n);
	Ans2=ret.a[0];
	printf("%d\n",(Ans1-Ans2+MOD)%MOD);
}
```

