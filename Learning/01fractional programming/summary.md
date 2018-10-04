## 问题描述

​	首先分数规划是一类决策性问题

​	一般形式是：
$$
\lambda=\frac{f(x)}{g(x)}
$$
​	其中$f(x)$和$g(x)$都是连续的实值函数，然后要求$\lambda$的最大值或最小值

​	

​	这类问题中，研究较多的是$01$分数规划，也就是求
$$
\lambda=\frac{\sum (f_i*x_i)}{\sum (g_i*x_i)}
$$
​	其中$x_i \in \{0,1\}​$，其他条件和普通分数规划一样，求$\lambda​$的最大或最小值

​	接下来我们讨论的是$01$分数规划



## 具体求解

​	求解$01$分数规划的问题很重要的一个思想就是二分

​	某种程度上可以理解为一种二分答案，只是判断的方式稍微有一点点不同

​	我们处理一下上面的$\lambda$的表达式：
$$
\begin{aligned}
\sum(f_i*x_i)&=\lambda \sum(g_i*x_i)\\
\end{aligned}
$$
​	移一下项变成：
$$
\sum(f_i*x_i)-\lambda\sum(g_i*x_i)=0
$$
​	这个就是我们需要的一个式子啦



​	具体什么意思呢？

​	以求解表达式的最大值为例，考虑二分最终的答案

​	我们将最终的答案记为$ans$，记当前二分到的$mid$为$\lambda'$，那么上面这个表达式应该满足：

1、$ans<\lambda'$时，$max(\frac{\sum (f_i*x_i)}{\sum (g_i*x_i)})=ans<\lambda'$，也就是$max(\sum(f_i*x_i)-\lambda’\sum(g_i*x_i))<0$

2、$ans=\lambda'$时，则上面这个表达式的值为$0$

3、$ans>\lambda'$时，则上面这个表达式的值$>0$



​	所以我们要做的就是在一个比较合理的时间内求出$max(\sum(f_i*x_i)-\lambda’\sum(g_i*x_i))$（或者$min$）就好啦

​	这样的题目往往会跟一些其他的算法结合起来，比如环啊生成树啊之类的

​	接下来放几道例题帮助理解



## 例题们

​	首先是两道相对来说基础一点的：

[Portal -->bzoj4819新生舞会](https://www.lydsy.com/JudgeOnline/problem.php?id=4819)

​	看到答案的那个形式。。那就分数规划咯。。

​	我们现在相当于是要求：
$$
\frac{\sum\limits_{i=1}^{n} \sum\limits_{j=1}^n a_{i,j}*x_{i,j}}{\sum\limits_{i=1}^{n} \sum\limits_{j=1}^n b_{i,j}*x_{i,j}}
$$
​	这个东西的最大值

​	其中$x_{i,j}\in \{0,1\}$表示$i$和$j$是否是舞伴

​	那明显是一个$01$分数规划的形式，套用上面讲到的方法，现在问题转变成如何判断
$$
max(\sum\limits_{i=1}^{n} \sum\limits_{j=1}^n a_{i,j}*x_{i,j}-\lambda'\sum\limits_{i=1}^{n} \sum\limits_{j=1}^n b_{i,j}*x_{i,j})
$$
​	与$0$的关系



​	这里我们可以考虑用费用流来求解，具体建图相对来说还是比较好想的：

​	男生看成$1$到$n$号，女生看成$1+n$到$n+n$号

1、源点$S$往$1$到$n$（男生）都连一条费用为$0$，流量为$1$的边

2、男生$i$（也就是$i$号点）往女生$j$（也就是$j+n$号点）连一条费用为$(a_{i,j}-\lambda' b_{i,j})$，流量为$1$的边

3、$1+n$到$n+n$号（女生）往汇点$T$连一条费用为$0$，流量为$1$的边

​	然后大力跑最大费用最大流就好啦



​	代码大概长这个样子：

```C++
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define ll long long
using namespace std;
const int N=110,inf=2147483647;
const double eps=1e-8;
struct xxx{
    int x,y,nxt,r;
    double c;
}a[N*N*10+10];
queue<int> q;
int h[N*2],pre[N*2];
double cost[N*2];
bool vis[N*2];
int A[N][N],B[N][N];
int n,m,tot,S,T;
void add(int x,int y,double c,int r);
bool spfa(double &rec);
void build(double mid);
void solve();
 
int main(){
#ifndef ONLINE_JUDGE
    freopen("a.in","r",stdin);
#endif
    scanf("%d",&n);
    for (int i=1;i<=n;++i)
        for (int j=1;j<=n;++j)
            scanf("%d",&A[i][j]);
    for (int i=1;i<=n;++i)
        for (int j=1;j<=n;++j)
            scanf("%d",&B[i][j]);
    solve();
}
 
void add(int x,int y,double c,int r){
    //printf("%d %d %.6lf %d\n",x,y,c,r);
    a[++tot].y=y; a[tot].x=x; a[tot].nxt=h[x]; h[x]=tot; a[tot].r=r; a[tot].c=c;
    a[++tot].y=x; a[tot].x=y; a[tot].nxt=h[y]; h[y]=tot; a[tot].r=0; a[tot].c=-c;
}
 
bool spfa(double &rec){
    while (!q.empty()) q.pop();
    int v,u;
    q.push(S); cost[S]=0;
    pre[S]=-1;
    for (int i=S+1;i<=T;++i) cost[i]=-inf,vis[i]=false;
    vis[S]=true;
    while (!q.empty()){
        v=q.front(); q.pop();
        for (int i=h[v];i!=-1;i=a[i].nxt){
            u=a[i].y;
            if (!a[i].r) continue;
            if (cost[u]<cost[v]+a[i].c){
                cost[u]=cost[v]+a[i].c;
                pre[u]=i;
                if (!vis[u])
                    vis[u]=true,q.push(u);
            }
        }
        vis[v]=false;
    }
    if (cost[T]==-inf) return false;
    int flow=inf;
    u=T;
    while (pre[u]!=-1)
        flow=min(flow,a[pre[u]].r),u=a[pre[u]].x;
    rec+=1.0*flow*cost[T];
    u=T;
    while (pre[u]!=-1)
        a[pre[u]].r-=flow,a[pre[u]^1].r+=flow,u=a[pre[u]].x;
    return true;
}
 
void build(double mid){
    tot=-1;
    S=0; T=2*n+1;
    for (int i=S;i<=T;++i) h[i]=-1;
    for (int i=1;i<=n;++i)
        for (int j=1;j<=n;++j)
            add(i,j+n,1.0*A[i][j]-mid*B[i][j],1);
    for (int i=1;i<=n;++i)
        add(S,i,0,1),add(i+n,T,0,1);
}
 
bool check(double mid){
    double rec=0;
    build(mid);
    while (spfa(rec));
    return rec>0;
}
 
void solve(){
    double l=0,r=10000,mid,ans;
    while (r-l>eps){
        mid=(l+r)*0.5;
        if (check(mid)) ans=mid,l=mid;
        else r=mid;
    }
    printf("%.6lf\n",ans);
}
```



​	

[Portal -->bzoj1690奶牛的旅行](https://www.lydsy.com/JudgeOnline/problem.php?id=1690)

​	（啊好吧这题是权限题qwq）

​	题意的话。。简单来说就是：给你一个有向图，每条边有一个边权，每个点有一个点权，求一个环满足$\frac{\sum 点权}{\sum 边权}$最大，路径中至少含有两个点（也就是保证$\sum边权$不能为$0$）

​	

​	首先我们分析一下最后选出来的环有没有可能是一个复合环

​	粗略想一下。。如果说是一个复合环的话，那么完全可以通过去掉一些路径变成一个简单环并且使得经过的点不减少

​	所以最后选出来的肯定是一个简单环

​	

​	那么问题就转化成了求一个比值最大的简单环，这个就可以用$01$分数规划来解决了

​	那么也就是说我们现在要求一个环的：
$$
max(\sum点权-\lambda'\sum边权)
$$
​	与$0$的关系

​	那么就每次建一个新图，把原图中的$(点权-\lambda' 边权)$ 设成新图的边权，然后用spfa判断一下是否存在正环就好了



​	代码大概长这个样子：

```C++
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int N=1010,M=5010,inf=2147483647;
const double eps=1e-3;
struct xxx{
    int y,nxt;
    double dis;
}a[M*2];
struct Data{
    int x,y,t;
}rec[M];
queue<int> q;
int h[N],val[N],cnt[N];
double cost[N];
bool vis[N];
int n,m,tot,S,T;
void add(int x,int y,double c);
bool spfa();
void build(double mid);
bool check(double mid);
void solve();
 
int main(){
#ifndef ONLINE_JUDGE
    freopen("a.in","r",stdin);
#endif
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;++i) scanf("%d",val+i);
    for (int i=1;i<=m;++i)
        scanf("%d%d%d",&rec[i].x,&rec[i].y,&rec[i].t);
    solve();
}
 
void add(int x,int y,double c){
    //printf("%d %d %.2lf\n",x,y,c);
    a[++tot].y=y; a[tot].nxt=h[x]; h[x]=tot; a[tot].dis=c;
}
 
bool spfa(){
    while (!q.empty()) q.pop();
    int u,v;
    for (int i=S;i<=T;++i) cost[i]=0,vis[i]=true,q.push(i),cnt[i]=0;
    while (!q.empty()){
        v=q.front(); q.pop();
        for (int i=h[v];i!=-1;i=a[i].nxt){
            u=a[i].y;
            if (cost[u]<cost[v]+a[i].dis){
                cost[u]=cost[v]+a[i].dis;
                if (!vis[u]){
                    q.push(u),vis[u]=true;
                    ++cnt[u];
                    if (cnt[u]>n) return true;
                }
            }
        }
        vis[v]=false;
    }
    return false;
}
 
bool check(double mid){
    build(mid);
    return spfa();
}
 
void solve(){
    double l=0,r=1000,mid;
    while (r-l>eps){
        mid=(l+r)*0.5;
        if (check(mid)) l=mid;
        else r=mid;
    }
    printf("%.2lf\n",l);
}
 
void build(double mid){
    tot=0; S=0; T=n+1;
    for (int i=S;i<=T;++i) h[i]=-1;
    for (int i=1;i<=m;++i)
        add(rec[i].x,rec[i].y,1.0*val[rec[i].x]-1.0*rec[i].t*mid);
}
```



​	然后是两道相对来说思考量或者码量大一点的，因为。。篇幅可能会比较长所以新开两篇博来写了，这里就放博客的传送门嗯

[Portal -->bzoj4898商旅](https://www.lydsy.com/JudgeOnline/problem.php?id=4898)

[Portal -->bzoj2402陶陶的难题II](https://www.lydsy.com/JudgeOnline/problem.php?id=2402)



## 总的来说

​	其实感觉。。$01$分数规划更多的是一种转化问题的思想？

​	运用起来还是很灵活的，可以跟各种东西套在一起。。

​	大概就是这样吧ovo

​	



​	

​	