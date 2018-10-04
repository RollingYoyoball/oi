[**Portal --> CC ForbiddenSum**](https://www.codechef.com/problems/FRBSUM)

### Solution

​	场上想到了$O(NM)$的做法。。~~然而并没有什么用~~

​	首先考虑比较简单的一个问题，给定一个数组$A$，问这些数不能凑成的最小的数是多少

​	有一个很简单的想法：显然$0$不管对于哪个数组来说都是可以表示的，所以接下来我们只用从$1$开始考虑，如果说我知道一个最大的$x$，满足$[1,x]$这个区间内的数都能被当前数组中的数表示出来，这个时候如果说新加入一个数$a$，考虑$x$会有什么变化

​	会发现如果说$a<=x+1$的话，那么这个最大值会从$x$变成$x+a$，构造一下就知道了：对于$[1,x]$中的整数显然都可以被表示出来，而$[x+1,x+a]$这个区间中的每一个数$i$都可由$(i-a)$和$a$组成，而$(i-a)\in [1,x]$，所以成立；当$a>x+1$的话，就没有办法连上了

​	这样得出了整个数组的$x$之后，$x+1$就是答案了

​	所以我们可以得到一个$O(NM)$的做法，就是每个询问区间暴力扫一遍

​	

​	由于要排序，这个算法看起来好像非常难优化，但实际上我们如果换一种角度来看这个算法的流程就比较好优化了：**绕开排序这个瓶颈，放在整个无序的数组上面进行操作**，注意到上面提及的$x$其实是这个数组中某些元素的和，所以这个$x$其实应该是一个$sum$，我们每次在做的事情就是找到一个新的$<=sum+1$的元素，并且将它加进$sum$里面去，直到找不到新的元素为止，由于$sum$本身是递增的，所以无形中相当于从小到大考虑每个元素

​	注意到这个寻找新元素的过程并没有必要一个一个元素地找，实际上我们会发现，对于当前$sum$来说那些$<=sum+1$的新元素一定会在后面的操作中被加进来（因为$sum$只会越来越大），所以每次我们可以将当前$<=sum+1$的所有新元素全部加进来就好了

​	于是问题就转变成了一个求区间中某个范围内的数的和的问题，直接主席树动态开点一波（注意根本不需要离散化之类的（实际上也不能离散化== ）。。因为。。动态开点。。所以点数还是$nlogn$级别的==）

​	至于时间复杂度：首先每次主席树查找是$logn$的，然后。。至于一次询问会查找几次呢。。实际上我们会发现每次$sum$都至少会变成原来的$2$倍，然后题目又说了总和$<=10^9$，那么就是最坏$log_2(10^9)$次左右，问题不大（然而这个$2$倍。。打表发现==并不会严谨证明。。菜醒qwq）



​	代码大概张这个样子

```C++
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=1e5+10,SEG=N*20;
int a[N],tmp[N];
int n,m;
namespace Seg{/*{{{*/
	int ch[SEG][2],sz[SEG],rt[N],sum[SEG];
	int n,tot;
	void init(int _n){tot=0; ch[0][0]=ch[0][1]=0; rt[0]=0; sz[0]=sum[0]=0; n=_n;}
	int newnode(int pre){
		ch[++tot][0]=ch[pre][0]; ch[tot][1]=ch[pre][1]; sz[tot]=sz[pre]; sum[tot]=sum[pre];
		return tot;
	}
	void pushup(int x){sz[x]=sz[ch[x][0]]+sz[ch[x][1]];sum[x]=sum[ch[x][0]]+sum[ch[x][1]];}
	void _insert(int pre,int &x,int d,int lx,int rx){
		x=newnode(pre);
		if (lx==rx){++sz[x];sum[x]+=lx;return;}
		int mid=lx+rx>>1;
		if (d<=mid) _insert(ch[pre][0],ch[x][0],d,lx,mid);
		else _insert(ch[pre][1],ch[x][1],d,mid+1,rx);
		pushup(x);
	}
	void insert(int pre,int x,int d){_insert(rt[pre],rt[x],d,1,n);}
	int _query(int L,int R,int l,int r,int lx,int rx){
		if (!L&&!R) return 0;
		if (l<=lx&&rx<=r) return sum[R]-sum[L];
		int mid=lx+rx>>1,ret=0;
		if (l<=mid) ret+=_query(ch[L][0],ch[R][0],l,r,lx,mid);
		if (r>mid) ret+=_query(ch[L][1],ch[R][1],l,r,mid+1,rx);
		return ret;
	}
	int query(int L,int R,int l,int r){return _query(rt[L-1],rt[R],l,r,1,n);}
}/*}}}*/
void solve(int l,int r){
	int sum=0,tmp,pre=0;
	while (1){
		tmp=Seg::query(l,r,1,sum+1);
		if (tmp==pre){
			printf("%d\n",sum+1);
			return;
		}
		sum=tmp; pre=tmp;
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	int l,r,mx=0;
	scanf("%d",&n);
	for (int i=1;i<=n;++i){
		scanf("%d",a+i);
		mx=max(mx,a[i]);
	}
	Seg::init(mx);
	for (int i=1;i<=n;++i)
		Seg::insert(i-1,i,a[i]);
	scanf("%d",&m);
	for (int i=1;i<=m;++i){
		scanf("%d%d",&l,&r);
		solve(l,r);
	}
}
```

