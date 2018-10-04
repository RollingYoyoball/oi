[**Portal -->arc068E**](https://arc068.contest.atcoder.jp/tasks/arc068_c)

### Solution

​	真实智力康复==

​	考虑一个区间是否能够对$d$有贡献，两个关键点：

1、如果区间长度$>=d$，那么必定包含一个$d$的倍数，有贡献

2、如果区间长度$<d$，那么要么没有贡献，要么只会包含一个$d$的倍数

​	没了Q^Q

​	一个树状数组区间修改单点查询没了QWQ

​	所以为什么我要分块。。以及为什么我会想线段树加一些奇奇怪怪的东西最后搞到要启发式合并。。

​	总的来说既然直接按照$d$来算会算重，那就应该从区间来想会对哪些$d$有贡献嗯。。

​	另外这题也可以反过来想（正难则反qwq），算出来每个$d$不可能有哪些区间直接减就好了

​	这些基本思路好像现在各种想不到去用。。emmmm



​	代码大概长这个样子

```C++
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=3*(1e5)+10,M=1e5+10;
struct Rec{
	int l,r;
	friend bool operator < (Rec x,Rec y)
	{return (x.r-x.l+1)<(y.r-y.l+1);}
}a[N];
int n,m,ans;
namespace BIT{/*{{{*/
	int c[M];
	int mx;
	void init(int _n){mx=_n; memset(c,0,sizeof(c));}
	void insert(int x,int delta){for (;x<=mx;x+=x&-x) c[x]+=delta;}
	void update(int l,int r){insert(l,1); insert(r+1,-1);}
	int query(int x){
		int ret=0;
		for (;x;x-=x&-x) ret+=c[x];
		return ret;
	}
}/*}}}*/
void solve(){
	int now=1;
	for (int i=1;i<=m;++i){
		while (a[now].r-a[now].l+1<=i&&now<=n){
			BIT::update(a[now].l,a[now].r);
			++now;
		}
		ans=n-now+1;
		for (int j=i;j<=m;j+=i){
			ans+=BIT::query(j);
		}
		printf("%d\n",ans);
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	int l,r;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;++i)
		scanf("%d%d",&a[i].l,&a[i].r);
	sort(a+1,a+1+n);
	BIT::init(m+1);
	solve();
}
```

