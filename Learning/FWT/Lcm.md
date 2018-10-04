Portal --> 出错啦qwq（好吧其实是没有）

### Description

​	给定两个正整数$n,k$，选择一些互不相同的正整数，满足这些数的最小公倍数恰好为$n$，并且这些数的和为$k$的倍数

​	求选择的方案数对$232792561$取模

​	数据范围：多组数据，组数$T<=10,n<=10^{18},k<=20$，且$n$的所有质因子不大于$100$

### Solution

​	这题。。好神仙啊qwq敲爆脑子都想不出来系列qwq

​	注意到$n<=10^{18}$意味着$n$至多有$15$个不同的质因子（前$15$个质数乘一下就知道了），并且$k$的范围也是比较小的

​	然后还有一点就是这个模数比较有趣，它$=lcm(1,2,...,20)+1$，也就是说它可以对长度在$1..20$的区间DFT

​	那不管别的我们可以先考虑一个最朴素的dp

​	记$f[i][j]$表示当前所选的数状态为$i$，和$\%k=j$的方案数，其中这个“所选数的状态”具体计算方式是：假设写成分解质因数的形式后$n=\sum p_i^{mi_i}$，其中$p_i$为$n$的每一个不同的质因子，我们的状态是一个二进制数，并且二进制的每一位对应一个$n$的质因子，对于二进制的第$i$位（假设对应$p_i$），如果说当前所选的数中存在一个数$x$满足$p_i^{mi_i}|x$，那么这位为$1$，否则为$0$

​	这样一来，我们最后的答案就应该是$f[(1<<Cnt)-1][0]$，其中$Cnt$为$n$的不同质因子个数

​	至于求解。。分解质因数和预处理因数可以暴力求解，但是后面的dp直接暴力转移的话稳稳的T啊（光枚举子集就要$3^{Cnt}​$了还要再乘个$k​$)，所以现在的问题是我们要怎么比较快速地转移

​	观察这个dp两维的转移，我们会发现第一维的转移可以写成一个集合或卷积的形式（或起来等于某个数就把值累计进去），而第二维的转移则直接枚举因数什么的大力转移就好了

​	然后这里有一个很有意思的想法：首先我们发现这两维如果可以分开处理就会比较好一点，然后注意到这个模数很有趣，允许我们进行区间长度$\in[1,20]$的DFT，而DFT操作之后，dp的这两维在某种意义上就是独立的了，换句话来说，如果说我们先在同行内转移$f$数组，再对转以后每行的不完全计算的$f$数组做一次DFT，这行的$f$的第二维就不会互相影响了，也就是说我们可以通过这种方式实现第一维和第二维转移的分离

​	这样我们就可以先处理$f[][i]$，直观一点来说就是先在同行转移$f$数组，具体一点就是枚举$n$的因数，然后考虑加进去的贡献，也就是假设当前枚举到的因数是$a[i]$，$a[i]$对应的状态是$st$，那么我们可以对于所有的$j\in [0,k)$转移：
$$
f[st][(j+a[i]\%k)]+=f'[st][j]
$$
​	之所以在后面的$f$打了个$'$是因为我们这里要累加进去的是用$a[i]$更新前的$f[st]$的版本

​	

​	这样我们就得到了整合了同行数据之后的$f$数组（**为了防止弄混在接下来的描述中我们还是将这个不完全转移的$f$数组记为$f1$好了**），然后对于每一行DFT一下，接下来就是考虑第一维的转移了，更加直观一点就是。。同列的$f$进行转移

​	接下来为了让描述变得更加简洁，我们将第二维省去（因为反正转移的时候都是同列转移）

​	现在我们要做的事情就是挑出若干个$f1[i]$，满足$i_1\ or\ i_2\ or\ ...\ i_m=st$然后将这堆$f1[i]$的值累加到$f[st]$去

​	我们记$F(S)=\sum\limits_{i\subseteq S}f[i]$，如果说我们知道了$F(S)$的取值，那么只要大力容斥一下就可以得出$f$数组了，具体一点的话就是：
$$
f[T]=\sum\limits_{S\subseteq T}(-1)^{|T|-|S|}F(S)
$$
​	我们将$F(S)$进行一下转化，会发现：
$$
\begin{aligned}
F(S)&=\sum\limits_{j\subseteq S}f[j]\\
&=\prod\limits_{i\subseteq S}(1+f1[i])
\end{aligned}
$$
​	具体的话就是因为对于$f$来说，每一个$f[j]$都是由若干个$f1[i]$组成的，我们考虑将第二个等号后面的连乘的括号拆掉，展开之后会发现囊括了$i$的所有组合方式（为了方便理解可以自己用比较小的规模模拟一下），然后因为我们限制了$i\subseteq S$所以可以保证任意的组合方式都是满足组合后$\subseteq S$的

​	然后由于$f1$是已知的，所以我们现在就要想如何快速求$F(S)$

​	显然枚举子集不现实

​	如果我们直接从小到大枚举状态，每次将这个状态对应的$f1$值转移的话，可能会出现重复计算的情况（比如说$010$可以转移到$011$和$110$，而$011$和$110$又都可以转移到$111$，这样如果按照这种转移方式的话，$111$这里$010$的$f1$值就会被重复计算），所以这里考虑一种很玄学的按顺序转移方式：

​	我们考虑二进制一位一位转移，从低位枚举到高位，每枚举一位就把所有的这位为$0$的状态的值累加到将这位修改为$1$后的状态里面去，具体一点的话就是：

​	我们以$Cnt=3​$为例子，状态转移大概是这样：

![](http://images.cnblogs.com/cnblogs_com/yoyoball/1203630/o_lcm.png)

​	其中橙黄色的箭头表示转移的方向，然后位数是从最右边开始数的

​	这样的话显然所有的状态都能转移到它能转移到的位置，现在我们来说明一下为什么这样不会重复计算：首先可以确认的一点是，这种重复计算的情况只会出现在转移到一个被修改了两个及以上位的状态的时候，而我们这样的枚举方式每次只转移到修改了一位的地方，并且是按照数位从低到高，状态从小到大的顺序转移，比如说刚才提到的$010$在$111$中被重复计算的情况，放在这个转移方式中就应该是：在转移第一位的时候，$010$会先转移到$011$，然后在转移第三位的时候再由累加了$010$的$011$转移到$111$，每次都是从只修改一位的地方转移过来，不会出现重复计算的情况~~（但其实上面的证明也不算。。特别严谨。。还是感性理解既视感qwq）~~

​	然后我们就可以在$O(2^{Cnt})$的时间内求得$F(S)$，接下来直接大力容斥一下就可以得出$f[(1<<Cnt)-1][0]$的值最后IDFT一下就可以得出答案啦



​	代码大概长这个样子

```C++
#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;
const int MOD=232792561,G=71,N=110;
const int p[26]={0,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
ll mi[N],rec_mx[N],Tmp[N],have[N];
ll a[500010];
int f[(1<<15)+10][20];
ll n,K,T,Cnt,all;
void add(int &x,int y){x=(1LL*x+y+MOD)%MOD;}
bool in(int st,int x){return st>>(x-1)&1;}
int St(int x){return 1<<x-1;}
int ksm(int x,int y){
	int ret=1,base=x;
	for (;y;y>>=1,base=1LL*base*base%MOD)
		if (y&1) ret=1LL*ret*base%MOD;
	return ret;
}
namespace DFT{/*{{{*/
	int tmp[110],W[1010][2];
	int inv;
	void init(){
		int rt=ksm(G,(MOD-1)/K);
		W[0][0]=1;
		for (int i=1;i<=1000;++i)
			W[i][0]=1LL*W[i-1][0]*rt%MOD;
		for (int i=0;i<=1000;++i)
			W[i][1]=ksm(W[i][0],MOD-2);
	}
	void dft(int *a,int n,int op){
		for (int i=0;i<n;++i) tmp[i]=0;
		for (int i=0;i<n;++i) 
			for (int j=0;j<n;++j)
				tmp[i]=(1LL*tmp[i]+1LL*a[j]*W[i*j][op==-1]%MOD)%MOD;
		if (op==-1){
			inv=ksm(n,MOD-2);
			for (int i=0;i<n;++i) tmp[i]=1LL*tmp[i]*inv%MOD;
		}
		for (int i=0;i<n;++i) a[i]=tmp[i];
	}
}/*}}}*/
void Div(ll x){
	for (int i=1;i<=25;++i)
		if (x%p[i]==0){
			++Cnt; rec_mx[Cnt]=1; mi[Cnt]=0; have[Cnt]=p[i];
			while (x%p[i]==0) 
				x/=p[i],++mi[Cnt],rec_mx[Cnt]*=p[i];
		}
}
void dfs(int now,ll prod){
	if (now>Cnt){
		a[++a[0]]=prod;return;
	}
	ll tmp=prod;
	for (int i=0;i<=mi[now];++i){
		dfs(now+1,tmp);
		tmp*=have[now];
	}
}
void prework(){
	a[0]=0; Cnt=0;
	Div(n);
	dfs(1,1);
}
void update(int st,int r){
	for (int i=0;i<K;++i) Tmp[i]=f[st][i];
	for (int i=0;i<K;++i) add(f[st][(i+r)%K],Tmp[i]);
}
void solve(){
	int st,op;
	memset(f,0,sizeof(f));
	all=(1<<Cnt)-1;
	for (int i=0;i<=all;++i) f[i][0]=1;//init
	for (int i=1;i<=a[0];++i){
		st=0;
		for (int j=1;j<=Cnt;++j)
			if (a[i]%rec_mx[j]==0) st|=St(j);
		update(st,a[i]%K);
	}
	for (int i=0;i<=all;++i)
		DFT::dft(f[i],K,1);

	for (int i=1;i<=Cnt;++i)
		for (int j=0;j<=all;++j)
			if (in(j,i))
				for (int k=0;k<K;++k)
					f[j][k]=1LL*f[j][k]*f[j^St(i)][k]%MOD;
	for (int i=0;i<all;++i){
		op=1;
		for (int j=1;j<=Cnt;++j)
			if (!in(i,j)) op*=-1;
		for (int j=0;j<K;++j)
			add(f[all][j],op*f[i][j]);
	}
	DFT::dft(f[all],K,-1);
	printf("%d\n",f[all][0]);
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	scanf("%d",&T);
	for (int o=1;o<=T;++o){
		scanf("%lld%lld",&n,&K);
		DFT::init();
		prework();
		solve();
	}
}
```

