**Portal --> broken qwq**

### Description

​	给你一个长度为$n$的序列$a$和一个正整数$k$，求满足如下条件的区间$[l,r]$的数量：$(\sum\limits_{i=l}^r a[i]-max(l,r))\%k=0$，其中$max$表示的是该区间的最大值

​	数据范围：$n<=300000，k<=100000$，保证答案$<=10^9$

### Solution

​	啊所以说是。。想不到怎么做就想分治吗qwq

​	我们首先可以考虑一种最简单粗暴的求解方式：我们固定一个左端点和最大值，然后看右端点能够移到哪里，然后统计其贡献，快速得出一个区间的表达式值是比较方便的，只要直接维护一个前缀和$sum$，$sum[r]-sum[l-1]-mx$就是表达式的值了

​	然后怎么优化的话。。就是可以将这个思路用到分治里面去

​	对于当前的区间$[l,r]$，我们考虑左端点在$[l,mid]$，右端点在$[mid+1,r]$中的满足条件的区间，	具体的计算有点迷，考虑将这堆区间再按照最大值的位置分成两类，一类是最大值在$mid$及以前，一类是最大值在$mid$以后，这两类的计算方式类似，接下来以第一类为例说一下大致过程：一开始将左端点设在$mid$处，将右端点设在$mid+1$处，每次将左端点往左移一位，然后更新当前位置到$mid$这段的最大值作为整个区间的最大值，然后暴力将右端点往右移，这里我们需要一个计数数组来统计贡献，考虑到我们要算的是$sum[r]-sum[l-1]-mx\equiv 0(mod\ k)$的区间，而当前$l$和$mx$是固定的，所以我们可以将右端点的贡献记在计数数组中$sum[r]\%k$的位置，调用的时候直接调$(sum[l-1]+mx)\%k$位置的值就是贡献了

​	如果说是统计第二类的话，就是变成将贡献记在$sum[l-1]\%k$的位置上，调用的时候是$(sum[l-1]-mx)\%k$位置的值即可

​	最后是。。记得清空

​	还有就是相同的情况只能算到一边去，也就是其中一类在移的时候是$<=mx$，另一类是$<mx$，否则的话会算重



​	代码大概长这个样子

```C++
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N=300010;
int a[N],sum[N],cnt[N];
int n,m,ans;
void solve(int l,int r){
	if (l==r) return;
	int mid=l+r>>1,tpl,tpr,mx;
	tpl=mid; tpr=mid+1; mx=0;
	while (tpl>=l){
		mx=max(mx,a[tpl]);
		while (tpr<=r&&mx>=a[tpr])
			++cnt[sum[tpr]],++tpr;
		ans+=cnt[(sum[tpl-1]+mx)%m];
		--tpl;
	}
	for (int i=mid+1;i<=r;++i) cnt[sum[i]]=0;
	tpl=mid; tpr=mid+1; mx=0;
	while (tpr<=r){
		mx=max(mx,a[tpr]);
		while (tpl>=l&&mx>a[tpl])
			++cnt[sum[tpl-1]],--tpl;
		ans+=cnt[(m-mx%m+sum[tpr])%m];
		++tpr;
	}
	for (int i=l;i<=mid;++i) cnt[sum[i-1]]=0;
	solve(l,mid);
	solve(mid+1,r);
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	scanf("%d%d",&n,&m);
	sum[0]=0;
	for (int i=1;i<=n;++i) scanf("%d",a+i),sum[i]=(sum[i-1]+a[i])%m;
	solve(1,n);
	printf("%d\n",ans);
}
```

