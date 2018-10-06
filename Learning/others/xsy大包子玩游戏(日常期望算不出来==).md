**Portal -->broken qwq**

### Description

​	有$n$个房间，每个房间里面可能有一些其他房间的钥匙，初始的时候所有的房门都是锁上的，随机炸门，问期望炸多少次才能打开所有的房间

​	数据范围：$n<=1000$



### Solution

​	日常期望算不出来==

​	比较套路的想法当然是建成一个有向图，每个房间与这个房间内钥匙对应的房间连一条有向边，那么问题就变成了。。在一个有向图上面删点（删去某个点能够到达的所有点），问期望删多少次才能删掉整张图

​	整体不好考虑，**我们直接对于每一个点考虑其贡献**

​	这里稍微。。表述一下接下来说的“贡献”的具体含义：不考虑期望的情况下，一个点对答案有$1$的贡献，当且仅当将这个点删除的那次操作，选的点就是它本身

​	对于一个点来说，我们记能够达到这个点的点集为$S$，那么可以将这个点删除的操作总共就有$|S|$种，但其中只有一种是选了自己的，所以一个点对答案贡献的期望就是$\frac{1}{|S|}$

​	然后我们对所有的点的期望贡献求个和就是答案了

​	现在的问题是怎么算$S$，那。。反正$n=1000$。。。那。。我们缩一下点变成一个DAG然后bitset记一下能够到达这个每个scc的点有哪些，然后直接跑拓扑排序那样转移就好了



​	代码大概长这个样子

```C++
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<bitset>
using namespace std;
const int N=1010;
struct xxx{
	int y,nxt;
}a[N*N*2];
queue<int> q;
int h[N],in[N],dfn[N],low[N],inst[N],st[N],h1[N];
int bl[N],sz[N];
bitset<N> ok[N];
double ans;
int n,m,T,tot,dfn_t,top,cnt;
void add(int x,int y,int *h){a[++tot].y=y; a[tot].nxt=h[x]; h[x]=tot;}
void tarjan(int x){
	int u;
	dfn[x]=low[x]=++dfn_t; inst[x]=1; st[++top]=x;
	for (int i=h[x];i!=-1;i=a[i].nxt){
		u=a[i].y;
		if (!dfn[u]){
			tarjan(u);
			low[x]=min(low[x],low[u]);
		}
		else if (inst[u])
			low[x]=min(low[x],dfn[u]);
	}
	if (low[x]==dfn[x]){
		++cnt; sz[cnt]=0; ok[cnt].reset();
		while (st[top]!=x){
			bl[st[top]]=cnt;
			ok[cnt][st[top]]=1;
			inst[st[top--]]=0;
			++sz[cnt];
		}
		bl[x]=cnt; --top; ++sz[cnt];
		inst[x]=0; ok[cnt][x]=1;
	}
}
void rebuild(){
	cnt=0; dfn_t=0; top=0;
	for (int i=1;i<=n;++i)
		if (!dfn[i]) tarjan(i);
	memset(h1,-1,sizeof(h1));
	for (int i=1;i<=n;++i){
		for (int j=h[i];j!=-1;j=a[j].nxt){
			if (bl[i]==bl[a[j].y]) continue;
			add(bl[i],bl[a[j].y],h1);
			++in[bl[a[j].y]];
		}
	}
}
void calc(){
	int u,v;
	rebuild();
	while (!q.empty()) q.pop();
	for (int i=1;i<=n;++i)
		if (in[i]==0) q.push(i);

	while (!q.empty()){
		v=q.front(); q.pop();
		for (int i=h1[v];i!=-1;i=a[i].nxt){
			u=a[i].y;
			ok[u]|=ok[v];
			--in[u];
			if (!in[u]) q.push(u);
		}
	}
}
void get_ans(){
	int tmp;
	ans=0;
	for (int i=1;i<=cnt;++i){
		tmp=ok[i].count();
		if (!tmp) continue;
		ans+=(1.0*sz[i])/(1.0*tmp);
	}
}
void init(){
	for (int i=1;i<=n;++i) 
		h[i]=-1,in[i]=0,dfn[i]=0;
	tot=0;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	int x,num;
	scanf("%d",&T);
	for (int o=1;o<=T;++o){
		scanf("%d",&n);
		init();
		for (int i=1;i<=n;++i){
			scanf("%d",&num);
			for (int j=1;j<=num;++j){
				scanf("%d",&x);
				add(i,x,h);
			}
		}
		calc();
		get_ans();
		//for (int i=1;i<=n;++i) printf("%d ",ok[i].count()); printf("\n");
		printf("Case #%d: %.5lf\n",o,ans);
	}
}
```

