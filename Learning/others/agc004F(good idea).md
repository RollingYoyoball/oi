[**Portal -->agc004F**](https://agc004.contest.atcoder.jp/tasks/agc004_f)

### Solution

​	好神仙的转化qwq

​	首先我们可以先考虑$m=n-1$的情况下，也就是树的情况下要怎么做

​	首先我们可以将这个问题转化一下：我们对这颗树重新染色，深度为奇数的点为黑色，深度为偶数的点为白色，这样一来原来的操作就变成了对两个相邻的颜色不同的节点进行颜色对调操作，最后的目的是要将所有的黑色点变成白色点，白色点变成黑色点

​	而每一次操作其实相当于交换两个点的颜色，所以我们可以得到结论：有解当且仅当白色点的数量和黑色点的数量相同

​	接下来为了更加直观，我们可以将这个过程理解成每次对调两个相邻的不同颜色的点的位置，使得用最少的步数做到将白点移到原来的黑点位置，黑点移到原来的白点位置

​	接下来我们从每条边的贡献来考虑：这条边连接的两个点需要被交换，说明原来子树中的一些点要被换出去，也就是说原来子树中的黑点比白点多或者白点比黑点多，而为了达到目的至少需要交换的次数应该是黑点和白点数量的差值

​	然后为什么一定能够构造出一个这样的方案的话。。我不太会严谨证明只能感性理解qwq就是考虑每一次交换都会让差值减小$1$，最后减到$0$就达到目的了

​	所以树的情况我们就直接求出每条边两个端点中较深的那个的子树内黑点和白点的差值的绝对值，然后累加起来就是答案了



​	接下来就是环的情况

​	比较套路的处理方式是：既然我们已经知道树怎么做了，那我们考虑断掉一条边然后按照树的方法来算最后再将这条边的影响算上去

​	因为黑色和白色跟深度有关，所以环这里需要根据奇偶性分两类讨论

​	首先是奇环的情况

​	因为是奇环，所以环中会出现两个同色的点相邻的情况，并且我们可以选择这两个颜色相同的点进行颜色反转操作，这对我们原来统计的影响是我们可以通过这条边将其中一个颜色的点数$+1$另一个颜色的点数$-1$，也就是差值$+2$或者$-2$，其他的情况都和树一致，也就是说差值不一定非零就无解，只要差值是一个偶数，我们就可以通过选择这条边进行操作最终将差值变成$0$，然后我们断掉这条边，其他的按照树来处理就好了



​	然后是偶环

​	偶环的影响会更加复杂一点，与奇环不同，在偶环上操作并不会改变黑点总数或者白点总数，所以可以单纯地理解成将点移来移去，假设我们断掉的边是$(x,y)$，我们假设在最优方案下，这条边的使用次数是$w$（也就是将$x$子树中的$w$个点移到$y$子树内，$w$为负数表示从$y$移到$x$），那么也就是说，断掉$(x,y)$之后的树中，记录$x$子树内的那条边的答案按照树的情况处理出来为$w1$，那么实际上这条边的贡献应该是$w1-w$，因为有$w$次需要分给$(x,y)$这条边，而对于$y$这个点来说，对应的边贡献则是要$+w$，因为从$x$那边多了$w$次转移到了$y$的子树中

​	但是现在的问题是，我们并不知道$w$是多少，这个时候我们将答案的表达式写出来可以得到：
$$
ans=abs(w)+\sum\limits_{e}abs(f[e]+a\cdot w)
$$
​	其中$f[e]$表示的是按照树的方式算的每条边的贡献，$a$是一个系数，$a\in \{-1,0,1\}$

​	然后发现后面的形式可以看成在数轴上面给定若干个点，要确定一个点（也就是$w$）使得所有的给定点到该点的距离之和最短，这个问题比较经典，答案应该是中位数

​	所以我们就可以直接将$w$求出来，然后计算$ans$啦



​	最后是一些实现上的问题：

1、虽然说上面的表达式中$f$是按照边存的，但是实际上在实现的时候按照点存会更加方便一点，$f[i]$表示的是$i$在树中从祖先过来的那条边的贡献

2、因为$f[i]$记录的子树内的信息，更新的时候是从后继的$f$值累加得到的，所以环情况中的影响需要沿着树中的祖先一路更新上去



​	代码大概长这个样子

```C++
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1e5+10;
struct xxx{
	int y,nxt,x;
}a[N*2];
int h[N],dep[N],f[N],vis[N],pre[N],mark[N];
int rec[N],lis[N];
int n,m,tot,cutx,cuty,type,cut;
int ans;
int Abs(int x){return x<0?-x:x;}
void add(int x,int y){a[++tot].y=y; a[tot].nxt=h[x]; h[x]=tot; a[tot].x=x;}
void predfs(int fa,int x,int d){
	int u;
	dep[x]=d; f[x]=d%2==0?-1:1; pre[x]=fa;
	for (int i=h[x];i!=-1;i=a[i].nxt){
		u=a[i].y;
		if (u==fa) continue;
		if (dep[u]){
			cutx=x; cuty=u; cut=i;
			type=((dep[x]+dep[u])%2)^1;
			continue;
		}
		predfs(x,u,d+1);
		f[x]+=f[u];
	}
}
void solve(){
	int tmp;
	if (m==n-1){
		if (f[1]){ans=-1; return;}
		ans=0;
		for (int i=1;i<=n;++i) ans+=Abs(f[i]);
		return;
	}
	if (type){
		if (f[1]%2){ans=-1; return;}
		tmp=f[1]/2;
		ans=Abs(tmp);
		for (int i=cutx;i;i=pre[i]) f[i]-=tmp;
		for (int i=cuty;i;i=pre[i]) f[i]-=tmp;
		for (int i=1;i<=n;++i) ans+=Abs(f[i]);
		return;
	}
	else{
		if (f[1]){ans=-1; return;}
		rec[0]=0;
		memset(mark,0,sizeof(mark));
		for (int i=cuty;i!=cutx&&i;i=pre[i]) 
			rec[++rec[0]]=f[i],mark[i]=true;
		sort(rec+1,rec+1+rec[0]);
		if (rec[0]%2==0)
			tmp=(rec[rec[0]/2]+rec[(rec[0]+1)/2])/2;
		else
			tmp=rec[(rec[0]+1)/2];
		ans=Abs(tmp);
		for (int i=1;i<=n;++i)
			if (mark[i]) ans+=Abs(f[i]-tmp);
			else ans+=Abs(f[i]);
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	int x,y,tmp;
	scanf("%d%d",&n,&m);
	memset(h,-1,sizeof(h));
	tot=0;
	for (int i=1;i<=m;++i){
		scanf("%d%d",&x,&y);
		add(x,y); add(y,x);
	}
	type=1;
	predfs(0,1,1);
	solve();
	printf("%d\n",ans);
}
```



