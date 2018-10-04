Portal --> broken qwq

### Description

​	大M正在学习函数的光滑性并对Lipschitz常数非常感兴趣：当一个定义域为$[l,r]$的函数$f$，对于定义域内的任意$x,y$都有$|f(x)-f(y)|<=K*|x-y|$时，则称$K$为该函数在$[l,r]$上的Lipschitz常数。     

​	然而大M并不满足于函数，所以他定义：对于一个序列$v[1..n]$的Lipschitz常数$K$，当$1<=x<y<=n$且$x,y$均为整数时，同样满足$|v[x]-v[y]|<=K*|x-y|$的$K$的最小值  

​	现在给你一个长度为n的序列$v[1..n]$并给出$q$个询问，对于每对询问$[l,r]$，你需要求出$v[l..r]$的所有子序列$v[x..y](l<=x<y<=r)$的Lipschitz常数之和 

​	数据范围：$n<=100000,q<=100 $



### Solution

​	这题的关键在于，要证明对于区间$[l,r]$来说，$K$一定是$max(\frac{|v[i]-v[i-1]}{|i-(i-1)|})$

​	我们可以将$\frac{|v[x]-v[y]|}{|x-y|}$看成一个求平均值的过程，再具体一点的话就是如果我们将$v$看成一个函数，这个式子其实相当于求一段区间（两个端点分别是$x$和$y$）中$|v[i]-v[i-1]|$的平均值，那么也就是说明最大值显然应该是在区间长度为$1$的时候取得（否则总能通过舍掉较小的部分取得更优的结果）

​	那所以我们可以直接求得$K$的所有可能的取值了（存在$w$数组中），接下来还是常用的套路，看每个取值能在哪个区间内提供贡献

​	这个其实比较好处理，我们用一个单调栈预处理出每一个$K$值的前一个比它大的位置和后一个比它大的位置，前者记为$pre$，后者记为$nxt$，那么我们可以直接算出这个由$|v[i]-v[i-1]|$产生的$K$对答案的贡献了，它能贡献的子区间左端点的取值范围为$w$数组中的$[max(l+1,pre+1),i]$，右端点的取值范围为$w$数组中的$[i,min(r,nxt-1)]$，其中$l,r$是询问的区间

​	什么叫做$w$数组中的一个区间呢？其实是因为$w$数组的定义写出来的话应该是$w[i]=|v[i]-v[i-1]|$，也就是说$w$中的一个位置其实包含了$v$中的两个位置，这么说好像还是有点绕，但反正就是边界什么的需要稍微。。自己推一下

​	然后还有一个问题是如果说$w$数组中（也就是$K$的所有取值中）有重复的怎么处理，那其实比较显然只要左端点算上重复的，右端点不算上就好了

​	（然而。。貌似左端点不算右端点算不太行的样子（也可能是因为我自己写挫了），就比如说会出现这种情况：$w=\{0,2,1,2,1\}$，然后如果左端点不算右端点算的话会把$K=2$时的$\{2,1,2,1\}$这种情况漏掉）



​	代码大概长这个样子

```C++
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define Pr pair<int,int>
#define mp make_pair 
#define ll long long
using namespace std;
const int N=100010;
int a[N],pre[N],nxt[N],loc[N],w[N];
Pr rec[N];
int n,m,top;
int Abs(int x){return x<0?-x:x;}
bool cmp(int x,int y){return w[x]<w[y];}
void prework(){
	top=0;
	pre[1]=0; rec[++top]=mp(w[1],1);
	for (int i=2;i<=n;++i){
		while(top&&rec[top].first<w[i]) --top;
		if (top==0) pre[i]=0;
		else pre[i]=rec[top].second;
		rec[++top]=mp(w[i],i);
	}
	top=0;
	nxt[n]=n+1; rec[++top]=mp(w[n],n);
	for (int i=n-1;i>=1;--i){
		while (top&&rec[top].first<w[i]) --top;
		if (top==0) nxt[i]=n+1;
		else nxt[i]=rec[top].second;
		rec[++top]=mp(w[i],i);
	}
}
void solve(int l,int r){
	int L,R;
	ll ans=0;
	for (int i=l+1;i<=r;++i){
		L=max(l+1,w[pre[i]]==w[i]?pre[i]:pre[i]+1),R=min(nxt[i]-1,r);
		ans+=1LL*w[i]*((R-i+1)*(i-L+1));
		//printf("%d %d\n",w[i],(R-i+1)*(i-L+1));
	}
	printf("%lld\n",ans);
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	int l,r;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;++i) scanf("%d",a+i);
	w[1]=0;
	for (int i=2;i<=n;++i) w[i]=Abs(a[i]-a[i-1]);
	prework();
	for (int i=1;i<=m;++i){
		scanf("%d%d",&l,&r);		
		solve(l,r);
	}
}
/*
input1
10 4
1 5 2 9 1 3 4 2 1 7
2 4
3 8
7 10
1 9

output1
17
82
23
210

input2
7 6
5 7 7 4 6 6 2
1 2
2 3
2 6
1 7
4 7
3 5

output2
2
0
22
59
16
8
*/
```



​	

​	