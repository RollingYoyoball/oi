**Portal --> broken qwq**

### Solution

​	（大概是几百万年前的坑==）

​	首先看到异或什么的肯定想到Trie

​	然后根据题意，先手肯定会选择能构成的最小异或值最大的那个点，后手的决策就十分显然了

​	然后看询问，我们考虑离线处理每个子树内的答案

​	

​	考虑最小异或值最大，放在Trie上面比较形象地说就是“最近”的两个值尽量在靠近根的地方分开，更加具体一定就是两个值插入Trie之后对应叶子节点的$lca$深度尽量浅，接下来我们可以从这个东西入手来设一个状态并dp求解

​	为了方便下面的表述，对于一个数$x$，我们用$g(x)$表示在当前Trie中与$x$异或和最小的那个元素（Trie中最近的那个元素）

​	用$lca(x,y)$表示$x$这个值在Trie中对应的叶子节点和$y$这个值在Trie中对应的叶子节点的$lca$

​	接下来我们定义一个数组$f$：
$$
f[i]=max(g(x)\ xor\ x)\ \ \ \ (lca(g(x),x)=i)	然后对于一个子树，我们只要将这个子树中的所有点的值丢进Trie里面去，然后对所有Trie中节点的$f$取一个$max$就好了()
$$
​	然后对于一个子树，我们只要将这个子树中的所有点的值丢进Trie里面去，然后对所有Trie中节点的$f$取一个$max$就好了（具体实现的时候可以选择一路pushup上去）



​	接下来先考虑怎么求解$f$

​	考虑在加入一个新的值$x$的时候，在加入过程中经过了$i$这个Trie中节点，$x$的加入对$f[i]$的影响

​	这里分两种情况：

1、$x$将要去往的节点（也就是$i$的左儿子或者右儿子）为空：如果是这样的话，说明$i$的这个儿子的子树内在添加之后只有$x$这一个值，那么$x$对应的叶子节点到$g(x)$对应的叶子节点的树上简单路径肯定要经过$i$，换句话说就是，如果另一个$i$的儿子中有数，那么$g(x)$肯定在$i$的这个儿子中，所以这个时候我们只要在Trie中另一个$i$的儿子的子树内贪心找一下$g(x)$即可，如果另一个子树内没有数，则没有贡献

2、$x$将要去往的节点不为空：这种情况下说明$x$所在的$i$的儿子的子树中肯定不止$x$这一个元素，所以$g(x)$肯定也在这个$i$的儿子的子树中，所以这种情况下$x$对$f[i]$不会有贡献

​	情况1中寻找的最坏情况是$O(logn)$的，所以一次插入就是$O(log^2n)$的了



​	然后就是我们要怎么统计每个子树的信息

​	显然暴力插什么的直接T出天际

​	这里有一个比较套路的搞法（感觉是套路吧qwq）我们重链剖分一波（然而实际上感觉是启发式合并的思想？）：因为暴力插入的复杂度瓶颈在于插入的元素数量，也就是子树大小，而注意到在回溯的时候，最后一个处理的子树信息其实是不需要清空可以直接继承到父亲去的（但是只能保留一个），所以这个时候我们当然是挑节点数最多的那个放到最后插入，其他的。。暴力插咯==

​	所以总结一下整个过程就是我们先递归处理轻儿子，每处理完一个都要清空再处理下一个，最后递归处理重儿子（这次处理完之后不需要清空Trie），然后将轻儿子子树的信息暴力插进保留了重儿子子树的Trie里面，得到当前节点的整棵子树信息，更新当前节点的询问

​	这样的话。。每个节点最多被插入$logn$次，所以总的时间复杂度是$O(nlog^3n)$的

​	一个小细节：如果说在Trie中实现的时候统计$max(f[i])$采用的是一路pushup上去的做法，那么注意在每次新加一个数的时候算对当前节点影响之前，一定要先将$f[i]$赋成初始值。。因为如果不这么做的话，很有可能这里的$f[i]$存的是pushup上来的Trie中$i$的子树的$f$最大值，当然如果说分开两个数组维护也ok（但是我懒啊==）



​	代码大概长这个样子

```C++
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
const int N=1e5+10,T=N*20,TOP=20;//debug
namespace Trie{/*{{{*/
	int ch[T][2],f[T],sz[T],val[T];
	int tot,rt;
	void init(){tot=rt=0;}
	int newnode(){ch[++tot][0]=ch[tot][1]=0;f[tot]=-1;sz[tot]=0;return tot;}
	void pushup(int x){
		sz[x]=0;
		if (ch[x][0]) f[x]=max(f[x],f[ch[x][0]]),sz[x]+=sz[ch[x][0]];
		if (ch[x][1]) f[x]=max(f[x],f[ch[x][1]]),sz[x]+=sz[ch[x][1]];
	}
	int get_mx(int x,int v,int d){
		int ret=0,dir;
		for (;d>=0;--d){
			dir=v>>d&1;
			if (ch[x][dir]) x=ch[x][dir];
			else x=ch[x][dir^1],ret+=1<<d;
		}
		return ret;
	}
	void _insert(int &x,int v,int d){
		if (!x) x=newnode();
		val[x]=v;
		if (d<0){
			++sz[x];
			f[x]=sz[x]>1?0:-1;
			return;
		}
		int dir=v>>d&1;
		_insert(ch[x][dir],v,d-1);
		f[x]=-1;//!!!
		if (ch[x][0]&&ch[x][1]){
			if (sz[ch[x][0]]==1)
				f[x]=max(f[x],(1<<d)+get_mx(ch[x][1],val[ch[x][0]],d-1));
			if (sz[ch[x][1]]==1)
				f[x]=max(f[x],(1<<d)+get_mx(ch[x][0],val[ch[x][1]],d-1));
		}
		pushup(x);
	}
	void insert(int v){_insert(rt,v,TOP);}
	int query(){return rt?f[rt]:-1;}
}/*}}}*/
struct xxx{
	int y,nxt;
}a[N*2];
vector<int> rec[N];
int h[N],dep[N],sz[N],son[N],st[N],ed[N],lis[N];
int w[N],ans[N];
int n,m,tot,dfn_t;
void add(int x,int y){a[++tot].y=y; a[tot].nxt=h[x]; h[x]=tot;}
void dfs(int fa,int x){
	int u;
	sz[x]=1; son[x]=0;
	st[x]=++dfn_t; lis[dfn_t]=x;
	for (int i=h[x];i!=-1;i=a[i].nxt){
		u=a[i].y;
		if (u==fa) continue;
		dfs(x,u);
		sz[x]+=sz[u];
		if (sz[u]>sz[son[x]]) son[x]=u;
	}
	ed[x]=dfn_t;
}
void dfs1(int fa,int x){
	int u,Ans;
	for (int i=h[x];i!=-1;i=a[i].nxt){
		u=a[i].y;
		if (u==fa||u==son[x]) continue;
		dfs1(x,u);
		Trie::init();
	}
	if (son[x])
		dfs1(x,son[x]);
	Trie::insert(w[x]);
	for (int i=h[x];i!=-1;i=a[i].nxt){
		u=a[i].y;
		if (u==fa||u==son[x]) continue;
		for (int j=st[u];j<=ed[u];++j)
			Trie::insert(w[lis[j]]);
	}
	Ans=Trie::query();
	for (int i=0;i<rec[x].size();++i)
		ans[rec[x][i]]=Ans;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	int x,y;
	scanf("%d",&n);
	memset(h,-1,sizeof(h));
	tot=0;
	for (int i=1;i<=n;++i) scanf("%d",w+i);
	for (int i=1;i<n;++i){
		scanf("%d%d",&x,&y);
		add(x,y); add(y,x);
	}
	scanf("%d",&m);
	for (int i=1;i<=m;++i){
		scanf("%d",&x);
		rec[x].push_back(i);
	}
	dfn_t=0;
	dfs(0,1);
	Trie::init();
	dfs1(0,1);
	for (int i=1;i<=m;++i) printf("%d\n",ans[i]);
}
```

