Portal --> broken qwq

### Description

​	给你一个长度为$n$的序列，要在里面选出$m$个区间，区间互不包含，并且至少一个区间的左端点是$x$（给定的），求方案数（按排列算）对$1e9+7$取模

​	数据范围：$n*m<=100000$（实际上是$n,m<=400$ ==)



### Solution

​	这个的话。。既然$n$和$m$都比较友善。。那。。dp咯

​	按照排列算的方案数的话我们可以最后乘一个$m!$就好了

​	（感觉这题的dp思路比较不错）

​	首先从选出区间的特点考虑，注意题目中说的只是不能包含而不是不能重叠

​	考虑一下每一个区间的确定关系到两个因素：开始位置和结束位置，而因为区间不能包含，所以开始位置最前的区间结束位置一定也是最前的，并且不能存在两个选择区间的开始位置或者结束位置相同

​	那么现在考虑这样的一个确定区间的过程，我们从左往右一位位扫，对于每一位，我可以有以下几种选择：

1、作为某个新区间的开始位置

2、作为某个已经确定开始位置的区间的结束位置

3、这一位单独作为一个区间

4、既不是开始位置也不是结束位置

​	然后对于题目“必须有一个区间的左端点是$x$”的限制，我们直接在扫到$x$这位的时候判断一下，不能进行2或4操作就好了

​	具体dp的话我们记$f[i][j][k]$表示当前扫到第$i$位，已经确定了$j$个开始位置和$k$个结束位置（显然$j>=k$），按照上面的4中决策转移就好了

​	至于空间问题。。用滚动数组把第一维滚动掉就好了ovo



​	代码大概长这个样子

```C++
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N=410,MOD=1000000007;
int f[2][N][N];
int n,m,x,now,pre,tmp;
void update(int &x,int y){x=(1LL*x+y)%MOD;}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	scanf("%d%d%d",&m,&n,&x);
	pre=0; now=1;
	f[0][0][0]=1;
	for (int i=1;i<=n;++i){
		memset(f[now],0,sizeof(f[now]));
		for (int j=0;j<=m&&j<=i;++j)
			for (int k=0;k<=j;++k){
				if (f[pre][j][k]==0) continue;
				if (j<m){
					update(f[now][j+1][k+1],f[pre][j][k]);
					update(f[now][j+1][k],f[pre][j][k]);
				}
				if (i!=x) update(f[now][j][k],f[pre][j][k]);
				if (i!=x&&k>0) update(f[now][j][k-1],f[pre][j][k]);
			}
		swap(pre,now);
	}
	tmp=1;
	for (int i=1;i<=m;++i) tmp=1LL*i*tmp%MOD;
	printf("%d\n",1LL*f[pre][m][0]*tmp%MOD);
}
```



​	