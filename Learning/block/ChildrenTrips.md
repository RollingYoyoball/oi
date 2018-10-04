[**Portal -->CC_Children Trips**](https://www.codechef.com/problems/TRIPS)

### Solution

​	（英文题解看得真爽qwq不过写的好详细啊ovo）

​	首先这题有一个很重要的条件就是边权是$1$或者$2$，所以~~虽然说我也不知道为什么这样就能突然~~想到了分块（是不是不知道怎么搞的时候就想分块啊qwq）

​	我们按照学生的体力值是否大于$\sqrt n$将所有的询问分成两类，第一类是$P<=\sqrt n$的，第二类是$P>\sqrt n$的

​	我们首先来看$P>\sqrt n$的这类

​	如果说不考虑时间的话，我们有一种非常暴力的做法就是先预处理$pre[i][j]$数组用来倍增求$lca$，然后再预处理一个$dis[x]$表示$x$这个节点到根的距离，有了这两个东西之后我们可以实现一个$single\_jump(x,P)$，其中$x$表示开始往上跳的节点，$P$表示的是学生的体力值，这个过程的作用是在$O(logn)$的时间内求出$x$这个节点在体力限制为$P$的情况下，最远能够往上走到哪一个节点，也就是找到一个深度最浅的$y$满足$dis[x]-dis[y]<=P$，并统计这个过程需要多少步

​	然后对于每次询问$(x,y,P)$我们先求出$lca$，然后分别从$x$和$y$两个节点开始$single\_jump$直到$lca$，当然两边都可能有剩下的一小段，最后处理一下就好了（要么一步走完要么两步走完）

​	这个是最暴力的一个想法，耗时的原因很简单，因为从$x$和$y$开始暴力$single\_jump$，如果$P$很小那就很凉了，但是对于$P>\sqrt n$的情况下，最多跳的步数是$\sqrt n$级别的，所以总的复杂度就是$O(\sqrt n logn)$，用来处理$P>\sqrt n$的情况问题不大ovo



​	接下来就是第一类$P<=\sqrt n$的情况了

​	显然我们要对”暴力$single\_jump$“这步进行优化，也就是要实现一次跳多步$single\_jump$

​	最套路的想法就是同样的我们可以预处理一个倍增数组$up[i][j]$，表示从$i$开始往上进行$1<<j$次$single\_jump$最浅能跳到哪里，处理方法跟求$lca$的倍增数组类似，只要先$O(nlogn)$求出$up[i][0]$然后大力转移就好了，有了这个数组之后我们就可以直接用倍增的方式求要跳多少步可以跳到哪里了，其他部分保持不变

​	但是能预处理的前提是我们知道$P$是多少，现在的问题是每一个询问的$P$都是不同的

​	也就是说每一次我们都要先$O(nlogn)$预处理一遍，这样显然是会爆炸的

​	但是注意到，如果我们只用这个方法来处理$P<=\sqrt n$的情况，$P$的取值只有$\sqrt n$种，我们将第一类的所有询问按照$P$值从小到大排个序，那么最坏的预处理的总复杂度就是$O(n^\frac{3}{2}logn)$，算一下好像有点爆炸然后我们来看一下时间是8sec那。。大概。。也许。。可以吧（实际上cc上面交了一发跑出来是。。4点多秒。。）

​	不过分块的事情是真的qwq不能信复杂度qwq（比如某道回转寿司的题明明算出来炸得不行但是就是能过并且跑得飞快。。）



​	代码大概长这个样子

```C++
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
const int N=1e5+10,TOP=16;
struct xxx{
	int y,nxt,dis;
}a[N*2];
struct Data{
	int left_dis,step;
	Data(){}
	Data(int x,int y){left_dis=x; step=y;}
};
struct Rec{
	int x,y,P,id;
	Rec(){}
	Rec(int x1,int y1,int P1,int id1){x=x1; y=y1; P=P1; id=id1;}
	friend bool operator < (Rec x,Rec y){return x.P<y.P;}
}rec1[N],rec2[N];
int h[N],dep[N],dis[N],ans[N];
int pre[N][TOP+1],up[N][TOP+1];
int n,m,tot,rec1_cnt,rec2_cnt,sq,Cnt;
void add(int x,int y,int d){a[++tot].y=y; a[tot].nxt=h[x]; h[x]=tot; a[tot].dis=d;}
void dfs(int fa,int x,int d,int Dis){
	dis[x]=Dis; dep[x]=d;
	pre[x][0]=fa;
	for (int i=1;i<=TOP;++i) pre[x][i]=pre[pre[x][i-1]][i-1];
	int u;
	for (int i=h[x];i!=-1;i=a[i].nxt){
		u=a[i].y;
		if (u==fa) continue;
		dfs(x,u,d+1,Dis+a[i].dis);
	}
}
int get_lca(int x,int y){
	if (dep[x]<dep[y]) swap(x,y);
	for (int i=TOP;i>=0;--i)
		if (dep[pre[x][i]]>=dep[y]) x=pre[x][i];
	if (x==y) return x;
	for (int i=TOP;i>=0;--i)
		if (pre[x][i]!=pre[y][i]) x=pre[x][i],y=pre[y][i];
	return pre[x][0];
}
int single_jump(int x,int P){
	int now=dis[x];
	for (int i=TOP;i>=0;--i){
		if (now-dis[pre[x][i]]>P) continue;
		x=pre[x][i];
	}
	return x;
}
Data large_up(int x,int aim,int P){
	int tmp,left_dis=0,step=0;
	while (x!=aim){
		tmp=single_jump(x,P);
		if (dep[tmp]>dep[aim]){
			++step;
			x=tmp;
		}
		else{
			left_dis=dis[x]-dis[aim];
			break;
		}
	}
	return Data(left_dis,step);
}
Data small_up(int x,int aim,int P){
	int step=0;
	for (int i=TOP;i>=0;--i){
		if (dep[up[x][i]]>dep[aim])
			step+=1<<i,x=up[x][i];
	}
	return Data(dis[x]-dis[aim],step);
}
void solve(int x,int y,int P,int id){
	if (x==y){ans[id]=0;return;}
	int lca=get_lca(x,y);
	Data tmp1,tmp2;
	tmp1=P<=sq?small_up(x,lca,P):large_up(x,lca,P);
	tmp2=P<=sq?small_up(y,lca,P):large_up(y,lca,P);
	ans[id]=tmp1.step+tmp2.step;
	if (tmp1.left_dis+tmp2.left_dis<=P) ++ans[id];
	else ans[id]+=2;
}
void small_prework(int P){
	++Cnt;//for debug qwq
	for (int i=1;i<=n;++i) up[i][0]=single_jump(i,P);
	for (int j=1;j<=TOP;++j)
		for (int i=1;i<=n;++i)
			up[i][j]=up[up[i][j-1]][j-1];
}
void Large(Rec *rec,int n){
	for (int i=1;i<=n;++i)
		solve(rec[i].x,rec[i].y,rec[i].P,rec[i].id);
}
void Small(Rec *rec,int n){
	sort(rec+1,rec+1+n);
	for (int i=1;i<=n;++i){
		if (i==1||rec[i].P!=rec[i-1].P)
			small_prework(rec[i].P);
		solve(rec[i].x,rec[i].y,rec[i].P,rec[i].id);
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	int x,y,d;
	scanf("%d",&n);
	sq=sqrt(n);
	memset(h,-1,sizeof(h));
	tot=0;
	for (int i=1;i<n;++i){
		scanf("%d%d%d",&x,&y,&d);
		add(x,y,d); add(y,x,d);
	}
	dfs(0,1,1,0);
	scanf("%d",&m);
	rec1_cnt=0; rec2_cnt=0;
	for (int i=1;i<=m;++i){
		scanf("%d%d%d",&x,&y,&d);
		if (d<=sq)
			rec1[++rec1_cnt]=Rec(x,y,d,i);
		else
			rec2[++rec2_cnt]=Rec(x,y,d,i);
	}
	Large(rec2,rec2_cnt);
	Small(rec1,rec1_cnt);
	for (int i=1;i<=m;++i) printf("%d\n",ans[i]);
}
```



​	