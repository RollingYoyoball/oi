[**Portal -->arc069_f**](https://arc069.contest.atcoder.jp/tasks/arc069_d)

### Solution

​	对于。。2-sat运用十分熟练的人来说。。这题可能是一眼2-sat Q^Q然而这并不是我十分忧伤qwq

​	首先题目里面有一个很明显的暗示：可以放在$x_i$或$y_i$

​	那我们可以将$x_i$和$y_i$看成两种不能共存的选择，我们用一条$(u,v)$的有向边表示选了$u$就必须选$v$，以上都是2-sat的常规操作那么接下来我们应该怎么办呢

​	如果说我们现在的问题变成判断一个数是否可能是最小值的话，这个问题可以采用这样的解决方式：对于一个点$i$，如果说我们选了这个点的$x_i$，那么其他所有的$|x_j-x_i|<d$的点都不能选$x_j$而必须选$y_j$（否则$d$就不是最小了），对于选$y_i$的情况同理，我们可以根据这个建出一个图，然后就可以继续2-sat常规操作大力tarjan缩点判断一下是否有解就好了，具体的话就是一个强联通分量中的所有点的选择状态必须一致，所以如果说存在一个$i$满足$x_i$和$y_i$在同一个强联通分量中那么就无解了

​	将问题转化为判断可以直接上个二分答案

​	现在的问题是怎么优化建图

​	我们将所有的$x$和$y$丢到一个数组（记为$lis$）里面排个序，可以发现满足$|x_j-x_i|<d$的$j$肯定是连续的一段（$l$和$r$可以直接用lower_bound和upper_bound查加一减一什么的有点烦==搞了好久），所以我们可以考虑线段树优化建图，把边数控制在$nlogn$内，线段树就按照$lis$中的这个顺序来建，然后内部是从根到叶子连边，叶子连对应的点的。。反选点（是$x$就选$y$，是$y$就选$x$）就好了

​	这里有一个小问题，点可能是一样的，那我们排完序之后不要去重，然后照常编号什么的就好了



​	代码大概长这个样子

```C++
#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
#include<algorithm>
using namespace std;
const int N=1e4+10,SEG=N*4,M=N*100,N1=SEG+N*2;
struct xxx{
	int y,nxt;
}a[M];
map<int,int>Id;
int p[N][2],lis[N*2],loc[N*2],V[N*2];
int dfn[N1],low[N1],h[N1],st[N1],inst[N1],num[N1];
int n,m,tot,dfn_t,top,cnt,mx,mn,all,tmptot;
void add(int x,int y){a[++tot].y=y; a[tot].nxt=h[x]; h[x]=tot;}
namespace Seg{/*{{{*/
	int ch[SEG][2],id[SEG];
	int n,tot,addtg;
	void _build(int x,int l,int r){
		if (l==r){
			add(addtg+x,loc[l]); return;
		}
		int mid=l+r>>1;
		ch[x][0]=++tot; 
		_build(ch[x][0],l,mid);
		ch[x][1]=++tot; 
		_build(ch[x][1],mid+1,r);
		add(addtg+x,addtg+ch[x][0]);
		add(addtg+x,addtg+ch[x][1]);
	}
	void build(int _n){n=_n;tot=1;addtg=_n;_build(1,1,n);}
	void _link(int x,int l,int r,int lx,int rx,int from){
		if (l<=lx&&rx<=r){
			add(from,addtg+x);
			return;
		}
		int mid=lx+rx>>1;
		if (r<=mid) _link(ch[x][0],l,r,lx,mid,from);
		else if (l>mid) _link(ch[x][1],l,r,mid+1,rx,from);
		else{
			_link(ch[x][0],l,mid,lx,mid,from);
			_link(ch[x][1],mid+1,r,mid+1,rx,from);
		}
	}
	void link(int l,int r,int from){if (l>r) return;_link(1,l,r,1,n,from);}
}/*}}}*/
void prework(){
	lis[0]=0;
	for (int i=1;i<=n;++i) lis[++lis[0]]=p[i][0],lis[++lis[0]]=p[i][1];
	sort(lis+1,lis+1+lis[0]);
	mx=lis[lis[0]]; mn=lis[1];
	//don't unique!
	int tmp;
	Id.clear();
	Id[lis[1]]=1;
	for (int i=2;i<=lis[0];++i)
		if (lis[i-1]!=lis[i]) Id[lis[i]]=i;
	for (int i=1;i<=n;++i){
		tmp=p[i][0];
		p[i][0]=Id[p[i][0]]; V[Id[tmp]]=tmp; ++Id[tmp];
		tmp=p[i][1];
		p[i][1]=Id[p[i][1]]; V[Id[tmp]]=tmp; ++Id[tmp];
		loc[p[i][0]]=n+i;
		loc[p[i][1]]=i;
	}
}
void tarjan(int x){
	int u;
	low[x]=dfn[x]=++dfn_t; st[++top]=x; inst[x]=true;
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
		++cnt;
		u=st[top];
		while (u!=x){
			inst[u]=false;
			num[u]=cnt;
			u=st[--top];
		}
		inst[x]=false; num[x]=cnt; --top;
	}
}
void reset(){
	memset(dfn,0,sizeof(dfn));
	memset(h,-1,sizeof(h));
	memset(inst,false,sizeof(inst));
	tot=0; cnt=0; top=0;
}
void build(int d){
	int l,r;
	Seg::build(lis[0]);
	for (int i=1;i<=n;++i){
		l=lower_bound(lis+1,lis+1+lis[0],V[p[i][0]]-d+1)-lis;
		r=upper_bound(lis+1,lis+1+lis[0],V[p[i][0]]+d-1)-lis-1;
		if (l<=r){
			Seg::link(l,p[i][0]-1,i);
			Seg::link(p[i][0]+1,r,i);
		}

		l=lower_bound(lis+1,lis+1+lis[0],V[p[i][1]]-d+1)-lis;
		r=upper_bound(lis+1,lis+1+lis[0],V[p[i][1]]+d-1)-lis-1;
		if (l<=r){
			Seg::link(l,p[i][1]-1,i+n);
			Seg::link(p[i][1]+1,r,i+n);
		}
	}
}
bool check(int d){
	reset();
	build(d);
	all=Seg::tot+lis[0];
	for (int i=1;i<=all;++i)
		if (!dfn[i])
			tarjan(i);
	for (int i=1;i<=n;++i)
		if (num[i]==num[i+n]) return false;
	return true;
}
void solve(){
	int l=0,r=mx-mn,mid,ans=l;
	while (l<=r){
		mid=l+r>>1;
		if (check(mid)) ans=mid,l=mid+1;
		else r=mid-1;
	}
	printf("%d\n",ans);
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	scanf("%d",&n);
	for (int i=1;i<=n;++i)
		scanf("%d%d",&p[i][0],&p[i][1]);
	prework();
	solve();
}
```



​	