**Portal --> broken qwq**

### Description

​	给你一棵树，点的编号从$1$到$n$，每个点有一个权值，每条边有一条边权，现在你要挑其中一个点作为起点，从这个点出发顺着树上的边走一条链，记录一个权值，该值一开始为$0$，每次经过一条边就减去边权，到达一个点就加上点权，要求整个行走过程中记录的权值每时每刻都非负，求该链包含的点的数量的最大值

​	数据范围：$n<=10^5,1<=点权val_i<=10^4,1<=边权d<=10^4$

### Solution

​	暴(dian)力(fen)即是艺术！

​	第一眼看过去应该是。。树分治，于是考虑对于每一个当前的重心$rt$统计过$rt$这个点的可达的链的长度最大值

​	继续进行十分简单粗暴的思考，反正链的话就是某一个子树中走上来，然后再走进某一个子树中，（额接下来的描述可能会比较抽象一点，只是对算法的整个过程进行一个比较抽象的描述，具体会在后面细化）所以我们需要维护两个值，一个是从$rt$沿某个儿子往下走（这个计算过程记为$GoUp$），一个是从某个儿子的子树中往上走到$rt$（这个计算过程记为$GoDown$），有了这两个过程之后，我们可以考虑将$GoDown$中算出的需要补充的值存在一个数组$rec$中，然后在$GoUp$的时候一遍求值一边在$rec$中二分，然后更新答案

​	至于如何保证往上的链和往下的链不在同一个子树内，就直接是点分套路了，我们枚举每一个儿子，在$GoDown$过程中的$rec$数组一直累计之前枚举的儿子中的信息，这样处理一个儿子的时候，先$GoUp$（此时取到的往下走的链一定是之前的儿子的子树内的）再$GoDown$即可

​	那么现在的关键就是，要求每时每刻都非负，这个我们要如何判断呢？考虑行走的时候记录的权值的变化过程，如果说我们要走的边权大于出发的点权，那么此时我们手头上的权值一定要能填补两者之间的“空缺“，也就是要$>val-d$，所以在$GoUp$和$GoDown$过程中，最关键的就是判断当前的累计权值能否填补空缺

​	想清楚了统计的关键，接下来给出$rec$数组的定义：$rec[i]$表示的是往下走的经过$i$个点的链需要填补的最小空缺，再具体一点就是需要补上多少才能使得$\sum val-\sum d>0$

​	首先来考虑$GoDown$过程，因为是顺着走的所以比较好判断，我们在$dfs$当前枚举到的儿子的子树的时候，直接记录从$rt$顺着走到当前节点$x$的$\sum val_i-\sum d_i$即可，然后存到$rec$数组中，注意因为我们需要统计的答案是链上点数相关，所以$rec$按照遍历到的点数来存，然后因为我们需要关心的是走到当前需要填补多少”空缺“，所以如果说$\sum val_i-\sum d_i>=0$的话$rec$就用$0$更新就好了，否则就用$-(\sum val_i-\sum d_i)$更新

​	接着是$GoUp$过程，这个过程会稍微麻烦一点，因为我们是逆着来走的，注意到当前算出来的$\sum val_i-\sum d_i>=0$并不代表往上走的时候每时每刻都是这样，所以我们需要特殊处理一下

​	考虑分段计算，具体什么意思呢？就是说一旦当前这段的$\sum val_i-\sum d_i>=0$，我们就二分一次，然后把这段“断开”，这样做能够保证每时每刻都非负是因为，如果说新加进来$val-d$之后变成负数了，那么一定要等到更深的地方加了一堆$val-d$之后整段权值非负才会更新答案，也就是保证了从下面走上来，断开的每一段都能保证每时每刻权值非负

​	具体实现的话就是除了$\sum val_i-\sum d_i$之外，我们再额外记一个值$tmp$，一旦新开一段我们就把$tmp$赋成$0$，然后继续累加即可

​	最后说一下更新答案的二分部分，当前往上走的链盈余出来的值就是$\sum val_i-\sum d_i$，而我们的$rec$数组存的是需要补上的最小值，那。。直接二分咯

​	然后有一点要注意的是，我们的$rec$数组可能会出现。。点数多（也就是下标大）的反而需要填补的空缺小，因为可能出现。。走着走着突然遇到一个巨大的点权然后一夜暴富的情况，为了保证程序会继续往后找，我们每次更新完$rec$数组之后，每个位置都要取后面的最小值



​	虽然说讲起来好像很啰嗦的样子不过想清楚了超级好写嗯qwq



​	代码大概长这个样子

```C++
#include<iostream>
#include<cstdio>
#include<cstring>
#define mp make_pair
#define Pr pair<int,int>
using namespace std;
const int N=1e5+10,inf=2147483647;
struct xxx{
	int y,nxt,dis;
}a[N*2];
int h[N],sz[N],mx_sz[N],vis[N],rec[N],val[N];
Pr rec_son[N];
int rt,rt_sz,cntson,Sz;
int n,m,tot,Ans;
void add(int x,int y,int d){a[++tot].y=y; a[tot].nxt=h[x]; h[x]=tot; a[tot].dis=d;}
void get_sz(int fa,int x){
	int u;
	sz[x]=1; mx_sz[x]=0;
	for (int i=h[x];i!=-1;i=a[i].nxt){
		u=a[i].y;
		if (u==fa||vis[u]) continue;
		get_sz(x,u);
		sz[x]+=sz[u];
		mx_sz[x]=max(mx_sz[x],sz[u]);
	}
}
void get_rt(int Rt,int fa,int x){
	mx_sz[x]=max(mx_sz[x],sz[Rt]-sz[x]);
	if (mx_sz[x]<rt_sz) rt=x,rt_sz=mx_sz[x];
	int u;
	for (int i=h[x];i!=-1;i=a[i].nxt){
		u=a[i].y;
		if (u==fa||vis[u]) continue;
		get_rt(Rt,x,u);
	}
}
void get_ans(int d,int rest){
	int l=1,r=Sz+1,mid,ans=l;
	while (l<=r){
		mid=l+r>>1;
		if (rec[mid]<=rest) ans=mid,l=mid+1;
		else r=mid-1;
	}
	if (rec[ans]<=rest)
		Ans=max(Ans,ans+d);
}
void go_up(int fa,int x,int d,int now,int tmp){
	if (tmp>=0){
		get_ans(d,now);
		tmp=0;
	}
	int u;
	for (int i=h[x];i!=-1;i=a[i].nxt){
		u=a[i].y;
		if (u==fa||vis[u]) continue;
		go_up(x,u,d+1,now+val[u]-a[i].dis,tmp+val[u]-a[i].dis);
	}
}
void go_dw(int fa,int x,int d,int now,int mn){
	if (mn>=0)
		rec[d]=min(rec[d],0);
	else
		rec[d]=min(rec[d],-mn);//need to be filled
	int u;
	for (int i=h[x];i!=-1;i=a[i].nxt){
		u=a[i].y;
		if (u==fa||vis[u]) continue;
		go_dw(x,u,d+1,now+val[x]-a[i].dis,min(mn,now+val[x]-a[i].dis));
	}
}
void calc(int x){
	int u,d;
	get_sz(0,x);
	cntson=0;
	for (int i=h[x];i!=-1;i=a[i].nxt){
		u=a[i].y;
		if (vis[u]) continue;
		rec_son[++cntson]=mp(u,a[i].dis);
	}
	Sz=sz[x]+1;
	for (int i=1;i<=sz[x]+1;++i) rec[i]=inf;
	rec[1]=0;//x
	for (int i=1;i<=cntson;++i){
		u=rec_son[i].first; d=rec_son[i].second;
		go_up(0,u,1,val[u]-d,val[u]-d);//u
		go_dw(0,u,2,val[x]-d,val[x]-d);//x u
		for (int j=sz[x]+1;j>=1;--j) rec[i]=min(rec[i],rec[i+1]);
	}

	for (int i=1;i<=sz[x]+1;++i) rec[i]=inf;
	rec[1]=0;//x
	for (int i=cntson;i>=1;--i){
		u=rec_son[i].first; d=rec_son[i].second;
		go_up(0,u,1,val[u]-d,val[u]-d);//u
		go_dw(0,u,2,val[x]-d,val[x]-d);//x u
		for (int j=sz[x]+1;j>=1;--j) rec[i]=min(rec[i],rec[i+1]);
	}
}
void solve(int x){
	rt=-1; rt_sz=n+1;
	int u;
	get_sz(0,x);
	get_rt(x,0,x);
	vis[rt]=true;
	calc(rt);
	for (int i=h[rt];i!=-1;i=a[i].nxt){
		u=a[i].y;
		if (vis[u]) continue;
		solve(u);
	}
}
int read(){
	int ret=0; char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while('0'<=ch&&ch<='9') ret=ret*10+ch-'0',ch=getchar();
	return ret;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	int x,y,z;
	n=read();
	for (int i=1;i<=n;++i) val[i]=read();
	memset(h,-1,sizeof(h));
	tot=0;
	for (int i=1;i<n;++i){
		x=read(); y=read(); z=read();
		add(x,y,z);
		add(y,x,z);
	}
	solve(1);
	printf("%d\n",Ans);
}
```



​	

​	