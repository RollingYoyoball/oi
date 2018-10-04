[**Portal -->bzoj2893**](https://www.lydsy.com/JudgeOnline/problem.php?id=2893)

### Descripiton

​	给你一个$n$个点$m$条边的有向图，有一些点是起始点，有一些点是终止点，一次操作可以从一个起始点开始沿着有向图的边走到一个终止点（中途可以经过终止点），求需要至少多少次操作才能覆盖所有的点，无可行方案输出“no solution"

​	数据范围：$t<=10,n <= 1000, m <= 10000 $，其中$t$为数据组数

### Solution

​	首先肯定要缩点

​	完了之后重新建图我们就可以先直接判掉无解的情况了，如果说一个点（下面说的点都是缩完之后的点）的入度为$0$并且不能作为起点，或者说一个点出度为$0$并且不能作为终点那肯定不能走到这个点，所以肯定是无解的

​	否则一定存在一种方案覆盖所有的点

​	那现在就变成了一个求有向无环图的可相交最小点覆盖问题了

​	然后。。不能天真的认为dfs或者大力dp可以直接搞定。。没那么简单qwq

​	实际上这个有很多种做法，其中比较简洁的一种是有上下界的最小流

​	具体建图的话就是，我们将一个原图中的一个点拆成两个，$x$和$x'$

​	然后$x\rightarrow x'$连一条容量下界为$1$上界为$+\infin$的边，表示每个点至少被经过一次

​	对于原图中的每条边$(u,v)$，我们建一条$u'\rightarrow v$的下界为$0$上界为$+\infin$的边，表示每条边最少可以不经过

​	然后跑一遍上下界最小流就好啦，具体一点的话就是建附加源和汇，对于一条容量为$[l,r]$从$u\rightarrow v$的边拆成三条边，附加源$\rightarrow v$流量为$l$，附加汇$\rightarrow u$流量为$l$，$u\rightarrow v$流量为$r-l$，简单说一下理解的话就是前两条边是保证下界，最后一条边是在$[l,r]$范围内随便流

​	这样建完图之后因为是要求有源汇的最小流，求解的话就是以附加源汇为起和终跑最大流，跑完了之后再加一条原来的汇$\rightarrow​$源的$+\infin​$的边，然后再在残留网络上跑一遍最大流就是答案了

​	具体的话。。我也不太会证明qwq可以去[**这篇博客**](https://www.cnblogs.com/mlystdcall/p/6734852.html)膜拜

​	

​	然后还有一种做法相对来说会麻烦一点点，就是有一个结论：如果我们按照如下方式建一个二分图：拆点，对于原图中$(u,v)$的边，在二分图中连$u\rightarrow v'$，那么原图点数$n$-二分图最大匹配数=原图的最小不可相交路径覆盖

​	如果我们再稍微改一下，先对原图用floyd做一次传递闭包，然后如果说两个点$u,v$满足$u$能够到达$v$，那么在二分图中连一条$u\rightarrow v'$的边，这样用同样的方式计算就是原图的最小可相交路径覆盖了

​	然后这题的话我们也可以用这种方式来求解，这样就只用普通网络流来跑个匹配，但是之前还需要传递闭包（具体的话dtz说是先拓扑排序再直接大力dp，不过在这题里面时间是$n^2$级别的，但是因为$n=1000$所以问题不大%%%），大概是这样



​	第一种做法的代码大概长这个样子

```C++
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int N=1010,M=10010,inf=2147483647;
int stok[N],edok[N];
int n,m,t,cntst,cnted;
namespace F{/*{{{*/
	struct xxx{
		int y,nxt,op,r;
	}a[M*10];
	queue<int> q;
	int lv[N*2],h[N*2];
	int tot,S,T,SS,TT;//S和T是附加源汇,SS和TT是原来的源汇
	void init(){
		tot=-1;
		memset(h,-1,sizeof(h));
	}
	void add1(int x,int y,int r){
		//printf("%d %d %d\n",x,y,r);
		a[++tot].y=y; a[tot].nxt=h[x]; h[x]=tot; a[tot].r=r;
		a[++tot].y=x; a[tot].nxt=h[y]; h[y]=tot; a[tot].r=0;
	}
	void add(int x,int y,int l,int r){
		add1(S,y,l);
		add1(x,T,l);
		add1(x,y,r-l);
	}
	bool bfs(){
		while (!q.empty()) q.pop();
		memset(lv,0,sizeof(lv));
		q.push(S); lv[S]=1;
		int u,v;
		while (!q.empty()){
			v=q.front(); q.pop();
			for (int i=h[v];i!=-1;i=a[i].nxt){
				u=a[i].y;
				if (!a[i].r||lv[u]) continue;
				lv[u]=lv[v]+1;
				q.push(u);
				if (u==T) return true;
			}
		}
		return false;
	}
	int dfs(int v,int o){
		if (!o||v==T) return o;
		int u,ret=0,flow;
		for (int i=h[v];i!=-1;i=a[i].nxt){
			u=a[i].y;
			if (!a[i].r||lv[u]!=lv[v]+1) continue;
			flow=dfs(u,min(o,a[i].r));
			if (flow){
				o-=flow;
				ret+=flow;
				a[i].r-=flow;
				a[i^1].r+=flow;
				if (!o) break;
			}
		}
		if (!ret) lv[v]=-1;
		return ret;
	}
	int dinic(){
		int ret=0;
		while (bfs()) ret+=dfs(S,inf);
		return ret;
	}
}/*}}}*/
namespace G{/*{{{*/
	struct xxx{
		int y,nxt;
	}a[M*2];
	int h[N],dfn[N],low[N],st[N],id[N];
	int Stok[N],Edok[N],ind[N],outd[N];
	bool ins[N];
	int tot,dfn_t,cnt,top;
	void add(int x,int y){a[++tot].y=y; a[tot].nxt=h[x]; h[x]=tot;}
	void init(){
		memset(h,-1,sizeof(h));
		tot=0;
		memset(dfn,0,sizeof(dfn));
		memset(ind,0,sizeof(ind));
		memset(outd,0,sizeof(outd));
		memset(ins,false,sizeof(ins));
		memset(Stok,false,sizeof(Stok));
		memset(Edok,false,sizeof(Edok));
		top=0; cnt=0;
	}
	void tarjan(int x){
		int u;
		dfn[x]=low[x]=++dfn_t; st[++top]=x; ins[x]=true;
		for (int i=h[x];i!=-1;i=a[i].nxt){
			u=a[i].y;
			if (!dfn[u]){
				tarjan(u);
				low[x]=min(low[x],low[u]);
			}
			else if (ins[u])
				low[x]=min(low[x],dfn[u]);
		}
		if (low[x]==dfn[x]){
			++cnt; u=st[top];
			while (u!=x){
				id[u]=cnt;
				if (stok[u]) Stok[cnt]=true;
				if (edok[u]) Edok[cnt]=true;
				ins[u]=false; 
				u=st[--top];
			}
			id[x]=cnt;
			if (stok[x]) Stok[cnt]=true;
			if (edok[x]) Edok[cnt]=true;
			ins[x]=false;
			--top;
		}
	}
	bool rebuild(){
		int u;
		dfn_t=0;
		for (int i=1;i<=n;++i)
			if (dfn[i]==0) tarjan(i);
		F::SS=cnt*2+1; F::TT=F::SS+1;
		F::S=F::SS+2; F::T=F::SS+3;
		for (int i=1;i<=n;++i)
			for (int j=h[i];j!=-1;j=a[j].nxt){
				u=a[j].y;
				if (id[i]!=id[u]){
					++ind[id[u]],++outd[id[i]];
					F::add(id[i]+cnt,id[u],0,inf);
				}
			}
		for (int i=1;i<=cnt;++i){
			F::add(i,i+cnt,1,inf);
			if (!ind[i]){
				if (!Stok[i]) return false;
				F::add(F::SS,i,0,inf);
			}
			if (!outd[i]){
				if (!Edok[i]) return false;
				F::add(i+cnt,F::TT,0,inf);
			}
		}
		return true;
	}
}/*}}}*/
void solve(){
	if (!G::rebuild()){printf("no solution\n");return;}
	F::dinic();
	F::add(F::TT,F::SS,0,inf);
	int ans=F::dinic();
	printf("%d\n",ans);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	int x,y;
	scanf("%d",&t);
	for (int o=1;o<=t;++o){
		scanf("%d%d%d%d",&n,&m,&cntst,&cnted);
		G::init();
		memset(stok,false,sizeof(stok));
		memset(edok,false,sizeof(edok));
		for (int i=1;i<=cntst;++i)
			scanf("%d",&x),stok[x]=true;
		for (int i=1;i<=cnted;++i)
			scanf("%d",&x),edok[x]=true;
		for (int i=1;i<=m;++i){
			scanf("%d%d",&x,&y);
			if (x!=y) G::add(x,y);
		}
		F::init();
		solve();
	}
}
```

