Portal --> broken qwq

### Description

​	有n只狐狸在一起聚餐，每只狐狸都有一个年龄。按照狐狸们的习惯，坐在一起的两只狐狸的年龄之和需要是质数。现在这些狐狸们在一些圆桌上吃晚餐（第一只和最后一只狐狸是相邻的），每个圆桌至少做3只狐狸，至多没有限制，现在请你找到一种方案使得狐狸们的座位满足它们的习俗。

​	如果有多种方案同时满足，输出任意一种

​	数据范围：n<=200 年龄<=10000 ，保证有解

### Solution

​	首先质数我们可以预处理

​	注意到一点：从奇偶性来看，一桌狐狸要么一定是一奇一偶这样来坐的（一桌数量为偶数），要么一定是两个$1$连着坐在一起，其他都是一奇一偶（一桌数量为奇数）

​	因为奇数+奇数或者偶数+偶数得到的都是偶数，而唯一的偶数素数是$2=1+1$

​	然后我们稍微处理一下这两种情况，考虑从桌子的某一个地方断开，把一个环变成一个序列这样：一奇一偶的情况随意，怎么断都是一奇一偶，第二种情况则从两个$1$那里断开，变成一个$1$开头，$1$结尾的序列

​	然后我们将狐狸按照年龄的奇偶性分组，很容易转化成一个匹配的问题，那么考虑用网络流来求解

​	我们考虑将源点与奇数的狐狸相连，边的容量为$2$（因为每只奇数狐狸要与两只偶数狐狸相邻），然后奇数偶数狐狸之间的连容量为$1$的边，直接暴力$n^2$枚举是否能够组成素数，素数列表用线性筛预处理出来，最后偶数狐狸与汇点相连，同理边的容量为$2$

​	这样跑完一遍最大流之后，我们沿着满流的边走就能够构造出一组解了

​	至于为什么的话。。首先这是最大匹配，如果说有解的话一定跑出来的是一种每一只奇数狐狸都与两只偶数狐狸相邻的情况，然后具体构造的时候我们考虑dfs，每次走满流的边，并且每次肯定都是从奇数狐狸走到偶数狐狸或者反过来，满足我们上面拆成序列之后的性质



​	代码大概长这个样子

```C++
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
using namespace std;
const int N=210,M=N*N+N,inf=2147483647;
struct xxx{
	int y,nxt,r;
}a[M*2];
queue<int> q;
int h[N],lv[N];
int isnp[20010],p[20010],age[N];
int vis[N];
vector<int> rec[N];
int n,m,tot,num,S,T;
void add(int x,int y,int r){
	//printf("%d %d %d\n",x,y,r);
	a[++tot].y=y; a[tot].nxt=h[x]; h[x]=tot; a[tot].r=r;
	a[++tot].y=x; a[tot].nxt=h[y]; h[y]=tot; a[tot].r=0;
}
bool bfs(){
	while (!q.empty()) q.pop();
	for (int i=S;i<=T;++i) lv[i]=0;
	int u,v;
	q.push(S); lv[S]=1;
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
	int u,flow,ret=0;
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
void prework(int n){
	int cnt=0;
	for (int i=2;i<=n;++i){
		if (!isnp[i]) p[++cnt]=i;
		for (int j=1;j<=cnt&&i*p[j]<=n;++j){
			isnp[i*p[j]]=true;
			if (i%p[j]==0) break;
		}
	}
}
void build(){
	memset(h,-1,sizeof(h));
	tot=-1;
	S=0; T=n+1;
	for (int i=1;i<=n;++i)
		if (age[i]%2) add(S,i,2);
		else add(i,T,2);
	for (int i=1;i<=n;++i){
		if (age[i]%2==0) continue;
		for (int j=1;j<=n;++j){
			if (i==j||age[j]%2) continue;
			if (!isnp[age[i]+age[j]]) add(i,j,1);
		}
	}
}
void get_ans(int x){
	rec[num].push_back(x); vis[x]=true;
	int u;
	for (int i=h[x];i!=-1;i=a[i].nxt){
		u=a[i].y;
		if (vis[u]||u==S||u==T) continue;
		if (((age[x]%2)&&(!a[i].r))||((age[x]%2==0)&&(!a[i^1].r)))
			get_ans(u);
	}
}
void solve(){
	memset(vis,0,sizeof(vis));
	for (int i=1;i<=n;++i)
		if (!vis[i]){
			++num;
			get_ans(i);
		}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	int tmp;
	scanf("%d",&n);
	for (int i=1;i<=n;++i) scanf("%d",age+i);
	prework(20000);
	build();
	tmp=dinic();
	solve();
	printf("%d\n",num);
	for (int i=1;i<=num;++i){
		tmp=rec[i].size();
		printf("%d ",tmp);
		for (int j=0;j<tmp;++j) printf("%d ",rec[i][j]);
		printf("\n");
	}
}
```

​	

​	