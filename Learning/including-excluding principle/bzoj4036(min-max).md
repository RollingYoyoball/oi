[**Portal --> bzoj4036**](https://www.lydsy.com/JudgeOnline/problem.php?id=4036)

### Solution

​	感觉容斥的东西内容有点qwq多啊qwq还是以题目的形式来慢慢补档好了

​	这里补的是min-max容斥

​	

​	其实min-max容斥好像。。只是一个形式而已。。本质还是普通容斥==

​	记$max(S)$表示集合$S$中最大的元素，记$min(S)$表示集合中最小的元素，那么：
$$
max(S)=\sum\limits_{T\subseteq S}(-1)^{|T|-1}min(T)\\
min(S)=\sum\limits_{T\subseteq S}(-1)^{|T|-1}max(T)\\
$$
​	这个是最基本的形式

​	然后对于第一条式子这里记录一个sk学长提供的比较直观的证明：

​	对于$S$这个数集，我们将其中的每一个元素$x$看成一个$\{1,2,3,...,x\}$的集合，这样$S$就变成了一个集合的集合（我们记为$S'$），原来数集$S$中的最大值就可以看成现在$S'$中所有集合的并的大小，最小值就可以看成$S'$中所有所有集合的交的大小，然后我们有这样一条式子来求一堆集合的并的大小：
$$
|\bigcup\limits_{i=1}^{n}A_i|=\sum\limits_{k=1}^{n}(-1)^{k-1}\sum\limits_{1<=j_1<j_2<...<j_k<=n}|A_{j_1}\cap A_{j_2}\cap ...\cap A_{j_k}|
$$
​	然后我们就发现其实这个稍微转换一下其实就是：
$$
max(S)=\sum\limits_{T\subseteq S}(-1)^{|T|-1}min(T)
$$
​	至于$min$的那条怎么证的话。。我们只要把数集$S$中的每一个元素$x$看成一个$\{x+1,x+2,...inf\}$的集合，同样将$S$转成一个集合的集合$S'$，然后最小值操作就变成了$inf-$集合的并，最大值操作就变成了$inf-$集合的交，然后就$inf$的话系数那里稍微抵消一下之类的最后只剩下一个$inf$，那么其他的就跟上面一样了



​	然后这个东西在期望中也是适用的，也就是：
$$
E(max(S))=\sum\limits_{T\subseteq S}(-1)^{|T|-1}E(min(S))\\
E(min(S))=\sum\limits_{T\subseteq S}(-1)^{|T|-1}E(max(S))\\
$$
​	具体为什么。。首先补一个容斥原理在概率中的应用：

​	对于事件$A_i(1<=i<=n)$，我们记$P(A_i)$表示$A_i$事件发生的概率，那么至少一个事件发生的概率是：
$$
P(\bigcup\limits_{i=1}^{n}A_i)=\sum\limits_{k=1}^{n}(-1)^{k-1}\sum\limits_{1<=j_1<j_2<...<j_k<=n}P(A_{j_1}\cap A_{j_2}\cap ...\cap A_{j_k})
$$
​	然后$E$那个式子的证明什么的。。只要暴力展开一下然后发现就是普通容斥然后就没有然后了==

​	直接讲不太好说，还是放在题目里面比较好



​	比如说这题

​	稍微转化一下题意，其实就是有一个集合$S$，然后每秒给你$S$的任意一个子集（不同子集概率不同），求期望多少秒之后手头上的所有子集的并首次等于$S$

​	首先无解的话就是所有有值的$P$对应的数或起来都还得不到全集

​	接下来就只讨论有解的情况

​	我们记$max(S)​$表示集合$S​$中最后被或到的那个子集（也就是最后一个取到的数），$min(S)​$表示集合$S​$中第一个被或到的子集（也就是第一个取到的数），加上个$E​$在这里表示的就是期望时间，那么我们有：
$$
E(max(S))=\sum\limits_{T\subseteq S}(-1)^{|T|-1}E(min(T))\\
$$
​	我们其实可以把$E(max(S))$理解成我们要的答案，$E(min(T))$理解成或到集合的任意一个子集的期望时间，那$E(min(T))$是很好求的，只要把所有子集的$P$求个和得到概率，然后用$1$除一下就好了：$E(min(T))=\frac{1}{\sum\limits_{S'\cap T \neq \emptyset}P(S')}$

​	那所以我们只要求出$\sum\limits_{S'\cap T \neq \emptyset}P(S')$就可以了，这里需要稍微转化一下：
$$
\sum\limits_{S'\cap T \neq \emptyset}P(S') \Leftrightarrow (\sum P-\sum\limits_{S'\cap T=\emptyset}p(S'))\Leftrightarrow (\sum P-\sum\limits_{S'\subseteq T的补集}P(S'))
$$
​	所以我们现在要对于每一个原集合$S$的子集$T$，求出$\sum\limits_{s'\subseteq T}P(s')$，调用的时候带补集进去就好了

​	到这一步我们重新将这个问题转化回数，也就是说我们其实是要对于$[0,2^n-1]$范围内的每一个数$i$求$f[i]=\sum\limits_{j|i=i}p_j$

​	那么这个用FMT来求（其实就是按照某个顺序转移，Portal-->lcm这题中有用到类似的方法，不再赘述）或者直接FWT来求就好了（FWT的话就是。。或卷积在构造的时候那个形式恰好就是$f[i]=\sum\limits_{j|i=i}a[i]$，所以可以直接对原来的$p$数组进行FWT然后直接用就行了）

​	然后这题就做完了



​	代码大概长这个样子（是FMT的写法）

```C++
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
const int N=(1<<20)+10;
const double eps=1e-6;
int cnt[N];
double p[N],f[N];
int n,m,all;
bool in(int st,int x){return st>>x&1;}
int St(int x){return 1<<x;}
void prework(){
	for (int i=0;i<all;++i) f[i]=p[i];
	for (int i=0;i<n;++i)
		for (int j=0;j<all;++j)
			if (in(j,i))
				f[j]+=f[j^St(i)];
	cnt[0]=0;
	for (int i=0;i<all;++i) cnt[i]=cnt[i>>1]+(i&1);
}
bool check(){
	int st=0;
	for (int i=0;i<all;++i)
		if (fabs(p[i])>eps) st|=i;
	return st==(all-1);
}
void solve(){
	double ans=0;
	for (int i=1;i<all;++i)
		if (cnt[i]&1)
			ans+=1.0/(1.0-f[(all-1)-i]);
		else
			ans-=1.0/(1.0-f[(all-1)-i]);
	printf("%.10lf\n",ans);
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	scanf("%d",&n);
	all=1<<n;
	for (int i=0;i<all;++i) scanf("%lf",p+i);
	if (!check()){printf("INF\n");return 0;}
	prework();
	solve();
}
```

