**吐槽**

好吧这个是真的很妙qwq用来解方程组的网络流嗯不能更清真

------

**正题**

*首先是大概描述*

当一个方程组中所有的方程相加之后可以把所有的变量都消掉（也就是所有变量都出现一正一负可以抵消掉），我们会发现这个其实很像网络流中的流量平衡（正负一个看做流入一个看做流出）。我们可以将每条式子都看做一个点，方程中的常数就是限制方程成立的容量，这样我们就可以跑最大流来求出这个方程组的解了（如果说有一些别的限制条件什么满足×××最小或者最大啊之类的那就跑费用流就好）

*这听起来很玄妙*

然而其实。。拿一道题来说事会更加直观一点。。

[bzoj1061 志愿者招募](http://www.lydsy.com/JudgeOnline/problem.php?id=1061)

我们设第$i$类志愿者的人数为$x_i$，每个志愿者的费用为$v_i$，第$j$天雇佣的人数为$p_j$，那么我们可以把每天的雇佣人数写成一个不等式，为了方便表述这里给几个具体的数好一点

天数4，$p =${$2,3,4,5$}，总共有5类志愿者如下表

|      | 1    | 2    | 3    | 4    | 5    |
| ---- | ---- | ---- | ---- | ---- | ---- |
| 时间   | 1-1  | 1-2  | 2-3  | 3-3  | 3-4  |
| 费用   | 3    | 4    | 5    | 6    | 7    |

那么我们可以列出式子：
$$
\begin{align}
&p_1 = x_1+x_2>=2\\
&p_2=x_1+x_3>=3\\
&p_3=x_3+x_4+x_5>=4\\
&p_4=x_5>=5\\
\end{align}
$$
为了把不等式转成等式，我们可以对每个式子添加一个辅助变量$y_i$，注意$y_i$是有范围的（在不同的题目里面会有不同的限制，但是在这题里面比较直接就是$y_i>=0$，$y_i$的范围会影响到后面建图的时候的边的容量），那么我们可以把式子转化成这样：
$$
\begin{align}
&p_0=0\\
&p_1=x_1+x_2-y_1=2\\
&p_2=x_1+x_3-y_2=3\\
&p_3=x_3+x_4+x_5-y_3=4\\
&p_4=x_5-y_4=5\\
&p_5=0\\
\end{align}
$$
为什么要在一前一后加多两条式子呢？因为这样以后，我们每次用第$i+1$条式子减去第$i$条式子，就可以得到这样的东西：
$$
\begin{align}
&x_1+x_2-y_1=2&(p_1-p_0)\\
&x_3-x_2+y_1-y_2=1&(p_2-p_1)\\
&x_4+x_5-x_1+y_2-y_3=1&(p_3-p_2)\\
&-x_3-x_4+y_3-y_4=1&(p_4-p_3)\\
&-x_5+y_4=-5&(p_5-p_4)\\
\end{align}
$$
现在观察一下这些式子，每个变量都出现了两次，一次为正一次为负，刚好可以抵消，而且所有等式的右边和为0，我们再移下项，变成这样（为了更加方便后面的建图说明）：
$$
\begin{align}
&-x_1-x_2+y_1+2=0\\
&-x_3-x_2-y_1+y_2+1=0\\
&-x_4-x_5+x_1-y_2+y_3+1=0\\
&x_3+x_4-y_3+y_4+1=0\\
&x_5-y_4-5=0\\
\end{align}
$$
那么接下来先说一下如何建图，后面再解释为什么：

- 将第$i$个等式看做图中编号为$i$的点，然后再添加两个点$vs$和$vt$作为源点和汇点


- 对于一个等式$i$中的常数项$c$，如果是非负整数，那么从源点$vs$连一条容量为$c$费用为$0$的有向边到$i$

  如果是负整数，那么从$i$连一条容量为$abs(c)$费用为$0$的有向边到汇点$vt$


- 对于一个等式$i$中的变量$x_i$，如果$x_i$在等式$j$中出现，且在$i$和$j$中符号相反，那么从符号为负的等式连一条容量为$\infty$费用为$v_i$的有向边到符号为正的等式

  （注意，这里的容量应该为$x_i$的上限，这题里面是只要求$x_i>=0$即可所以是$\infty$)

- 对于一个等式$i$中的变量$y_i$，如果$y_i$在等式$j$中出现，且在$i$和$j$中符号相反，那么从符号为负的等式连一条容量为$\infty$费用为$0$的有向边到符号为正的等式

  （同样的，这里的容量应该为$y_i$的上限，这题里面也是恰好$y_i>=0$所以是$\infty$）

建完图之后，跑一遍最小费用最大流，$ans$就是$vs$到$vt$的最小费用

------

怎么去理解呢？

我们看回上面的等式，每个等式的左边都是几个变量和一个常数相加，右边都是0，会发现其实就像网络流中的除了源点和汇点以外其他的点都满足流量平衡（流进多少流出多少）

那么，我们就可以把一个式子中所有正的变量理解为流入的流量，负的变量理解为流出的流量，而正常数可以理解为来自源点的流量（一开始就流过来的一定有的），负的常数则是流向汇点的流量，所以就可以按照这个思路来构建这样的一个网络流模型啦，从源点到汇点的网络最大流就可以满足所有的等式

同时，这题还要求$\sum\limits_{i=1}^{m}x_i*v_i$最小，其实就是一个附加条件，那就给$x$变量对应的边上加上权值然后跑最小费用最大流即可ovo

------

代码的话大概是这样的，顺便吐槽一句bzoj这题的数据好像有点弱啊。。第一次交上去的时候反向边两个都建成tot+1了结果还要过了。。qwq

（其实就是说下面的代码可能还是有bug欢迎纠错qwq）

```c++
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define ll long long
#define inf 1000000
using namespace std;
const int N=1010;
const int M=10010;
struct xxx{
	int y,next,r,op,c;
}a[M*10];
queue<int> q;
int h[N],X[N];
int pre[100010],mn[100010],pred[100010];
ll d[N];
ll ans;
bool vis[N];
int n,m,vs,vt,tot;
int add(int x,int y,int r,int c);
int spfa();

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	int l,r,c,tmp;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;++i) scanf("%d",X+i);
	vs=0,vt=n+2;
	memset(h,-1,sizeof(h));
	for (int i=2;i<=n+1;++i) add(i,i-1,inf,0);
	for (int i=1;i<=m;++i){
		scanf("%d%d%d",&l,&r,&c);
		add(l,r+1,inf,c);
	}
	for (int i=1;i<=n+1;++i){
		tmp=X[i]-X[i-1];
		if (tmp>0) add(vs,i,tmp,0);
		if (tmp<0) add(i,vt,-tmp,0);
	}
	ans=0;
	while (spfa());
	printf("%lld\n",ans);
}

int add(int x,int y,int r,int c){
	a[++tot].y=y; a[tot].next=h[x]; h[x]=tot; a[tot].r=r; a[tot].op=tot+1; a[tot].c=c;
	a[++tot].y=x; a[tot].next=h[y]; h[y]=tot; a[tot].r=0; a[tot].op=tot-1; a[tot].c=-c;
}

int spfa(){
	while (!q.empty()) q.pop();
	for (int i=vs;i<=vt;++i) d[i]=inf,vis[i]=false,mn[i]=inf;
	q.push(vs); vis[vs]=1; d[vs]=0;
	mn[vs]=inf; pre[vs]=-1; pred[vs]=-1;
	int v,u;
	while (!q.empty()){
		v=q.front(); q.pop();
		for (int i=h[v];i!=-1;i=a[i].next){
			u=a[i].y;
			if (!a[i].r) continue;
			if (d[u]>d[v]+a[i].c){
				pre[u]=i; pred[u]=v;
				mn[u]=min(mn[v],a[i].r);
				d[u]=d[v]+a[i].c;
				if (!vis[u])
					vis[u]=1,q.push(u);
			}
		}
		vis[v]=false;
	}
	if (d[vt]==inf) return false;
	ll flow=mn[vt];
	ans+=flow*d[vt];
	u=vt;
	while (pre[u]!=-1){
		a[pre[u]].r-=flow;
		a[a[pre[u]].op].r+=flow;
		u=pred[u];
	}
	return true;
}
```

