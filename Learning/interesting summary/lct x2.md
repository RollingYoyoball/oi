#### 两道奇妙深刻lct

[portal 1--> bzoj4817树点染色](https://www.lydsy.com/JudgeOnline/problem.php?id=4817)

​	<font color=#1E90ff>几句话题意：</font>

​		初始的时候有一棵有根树（1号为根），每个点有一个不同的颜色，要求支持以下几种操作：

​		1.把x到根的路径上面的点染成一个颜色

​		2.求两点之间路径上的不同颜色总数

​		3.求x的子树内某点出发到根节点的路径上最多有多少种不同的颜色

[portal 2-->bzoj3779重组病毒](https://www.lydsy.com/JudgeOnline/problem.php?id=3779)（权限题qwq不过可以去xsy上面交）

​	一句话题意：其实就是上面那题加多一个换根操作，并且每次换根之后都会将原来的根执行一次1操作，然后求	的不是有多少种不同颜色，而是子树内某点出发的颜色数量的平均值



​	（感觉这个修改的维护方式不错拎出来写一下）

​	首先这个题的。。暗示很明显了吧qwq，1操作长得基本上就和$access(x)$一样吧qwq

​	关键在于如何维护不同颜色总数

​	先从不用换根考虑，一个比较简单粗暴的想法就是维护每个点到根的路径上颜色总数，那么只有在$access$的时候需要修改，其他时候直接查就好了

​	然后不难发现**LCT中实边链接的两个点颜色肯定是一样的，虚边则是不一样的**

​	所以我们在$access$中断开原来的右儿子，然后连成新的右儿子这步修改，从。。类似树d的一种思路去想一下（应该算是吧？感觉挺像的qwq），会发现**将与原来右儿子的实边变为虚边，则原来的右儿子的splay中的深度最浅的点在原树中的整个子树的答案全部都要+1**，因为原来的时候这整一条链都是一种颜色，但是现在断开变成了两种，那么后面的那部分就全部都要+1了

​	同样的**新的右儿子的splay中深度最浅的点在原树中的整个子树的答案全部都要-1**，道理是一样的，就是原来不同现在变成相同了，所以要-1

​	（一定注意是**深度最浅的点**而不是直接取右儿子。。毕竟这个点在LCT中是跟整一个splay相关联的==）

​	那也就是说，我们只要实现一个**在原树上的子树加/减操作就好了**

​	然而这个东西LCT搞就十分无力了，所以我们可以考虑借助其他的数据结构——线段树，按照原树中的dfs序来建线段树，就可以轻松维护了

​	至于其他的有了线段树再求个lca什么都好说啦ovo



​	然后这个时候，我们会发现，上面的操作除了线段树部分会跟根由直接的关系，其他LCT中的操作并没有这方面的限制之类的（因为什么颜色的加加减减全部在$access$的奇妙深刻统计方式中搞定了，只用看连边是否是实边，根是谁看LCT本身的根），所以上面的那套就可以直接搬到强化版里面去ovo

​	

​	**换根的线段树子树加**

​	然而现在我们要换根了，所以在修改子树的时候就不能直接改了，然而这个并没有什么关系因为只要分类讨论一波：

​	假设我们现在要对$x$的子树进行操作，记原来的根为$root$，注意接下来我们讨论的$x$和$root$的位置关系都是在最初始的以$1$为根的树中的：

​	1.$x==root$：那么直接整棵树改就好了

​	2.$root$在$x$的子树内：那么就是除了$x$到$root$的路径以及以$root$为根的子树不用改，其他全改

​	3.$root$不在$x$的子树内：那么$x$的子树中的点不会受到换根的影响而改变，所以改初始树中$x$的子树就好了

​	这个貌似有道例题是bzoj3083（还没做晚点补）



​	那所以线段树的部分搞完了，整道题就做完了（平均数就维护一下sum和sz就好了一样的qwq）

​	

#### 然而还是想写上一些别的东西

​	1.pushdown真的。。毁一生啊qwq！！LCT这个东西的pushdown已经不是第一次忘记写然后调了很久很久很久很久很久了qwq。。。就是。。。**所有的有reverse操作的LCT在跳儿子之前一定要先！pushdown！而且！是！pushdown_once！**（调傻了的灵大会议。。。和。。。重组病毒。。。）

​	2.调试的时候要时刻记得LCT不是原树。。。只是中序一样而已。。。

​	3.顺便写一下LCT的其他操作好了。。

​	[portal-->xsy1665树剖裸题](http://192.168.102.138/JudgeOnline/viewsolution.php?id=1665)（所以为啥我要用LCT写。。）

​	关于LCT子树取最小值之类的，其实没有那么复杂。。。

​	只要每个点维护一个$mn[x]$然后**搞一个set（或者multiset啦）用来记录虚边所连的部分中的最小值**，然后在$access$的时候如果连进去了就把要断掉的右儿子的mn加进set，把要连上的右儿子的mn从set里面删掉，mn的更新就拿左右儿子的mn和set中的最小值更新就好了，查询直接$access(x)$然后取set中的最小值就好了（这样$x$的子树中的所有值都在set里面，因为$x$到根的路径整一条都变成实边了，那么剩下跟x相连的虚边全部都是$x$的子树中的值）

​	主要就是提供一种思路就是**涉及原树子树的问题那就直接每个点多开一个数组来存虚儿子的信息**

```C++
//like this  
int access(int x){
    for (int last=0;x;last=x,x=fa[x]){
        splay(x);
        if (rch(x)) s[x].insert(mn[rch(x)]);
        rch(x)=last;
        if (rch(x)) s[x].erase(s[x].lower_bound(mn[rch(x)]));
        update(x);
    }
}
int update(int x){
        mn[x]=min(*s[x].begin(),min(lch(x)?mn[lch(x)]:inf,rch(x)?mn[rch(x)]:inf));
}
```

  

​	[portal-->xsy2822选点游戏](http://192.168.102.138/JudgeOnline/problem.php?id=2822)

​	关于LCT维护。。树D之类的，额这个。。怎么说呢。。只是一个方面的思路吧。。

​	就是树D的话一般情况下是考虑$x$和它的儿子之间的转移嘛，但是你如果在LCT上面的话这个就十分疼痛了，所以为了搞定这种情况，可以考虑在设状态的时候**记录每个点的splay中深度最浅&最深的点的对应状态**（比如说这题里面就是$f[x][0/1][0/1]$表示最浅的点选还是不选，最深的点选还是不选），同时**再多开一个数组记录虚儿子的信息**（比如这题里面就是$g[x][0/1]$表示当前点$x$选或不选的时候虚儿子的最大贡献），然后在原来$update$的地方愉快转移一波就好了

​	（其他的遇到再写吧qwq暂时就想到这么多）



​	最后附上bzoj4817的代码和bzoj3779的代码（为什么明明是差不多的两道题码量差这么多疼痛啊qwq）

​	pushdown毁一生qwq

​	

​	bzoj4817大概长这样

```C++
#include<iostream>
#include<cstdio>
#include<cstring>
#define TOP 20
using namespace std;
const int MAXN=1e5+10,SEG=MAXN*4;
struct xxx{
	int y,nxt;
}a[MAXN*2];
int h[MAXN],st[MAXN],ed[MAXN],f[MAXN][TOP+1],dep[MAXN],lis[MAXN];
int tot,dfn_t,n,m;
namespace Seg{/*{{{*/
	int ch[SEG][2],mx[SEG],tag[SEG];
	int tot,n;
	void pushup(int x){mx[x]=max(mx[ch[x][0]],mx[ch[x][1]]);}
	void _build(int x,int l,int r){
		mx[x]=0; tag[x]=0;
		if (l==r) {mx[x]=dep[lis[l]];return ;}
		int mid=l+r>>1;
		ch[x][0]=++tot; _build(ch[x][0],l,mid);
		ch[x][1]=++tot; _build(ch[x][1],mid+1,r);
		pushup(x);
	}
	void build(int _n){n=_n; tot=1; _build(1,1,n);}
	void givetag(int x,int delta){mx[x]+=delta; tag[x]+=delta;}
	void downtag(int x){
		if (tag[x]==0) return;
		if (ch[x][0]) givetag(ch[x][0],tag[x]);
		if (ch[x][1]) givetag(ch[x][1],tag[x]);
		tag[x]=0;
	}
	void _update(int x,int l,int r,int lx,int rx,int delta){
		if (l<=lx&&rx<=r){
			givetag(x,delta);
			return;
		}
		downtag(x);
		int mid=lx+rx>>1;
		if (l<=mid) _update(ch[x][0],l,r,lx,mid,delta);
		if (r>mid) _update(ch[x][1],l,r,mid+1,rx,delta);
		pushup(x);
	}
	void update(int l,int r,int delta){if (!l) return;_update(1,l,r,1,n,delta);}
	int _query(int x,int l,int r,int lx,int rx){
		if (l<=lx&&rx<=r) return mx[x];
		downtag(x);
		int mid=lx+rx>>1,ret=0;
		if (l<=mid) ret=max(ret,_query(ch[x][0],l,r,lx,mid));
		if (r>mid) ret=max(ret,_query(ch[x][1],l,r,mid+1,rx));
		pushup(x);
		return ret;
	}
	int query(int l,int r){return _query(1,l,r,1,n);}
}/*}}}*/
namespace Lct{/*{{{*/
	int ch[MAXN][2],fa[MAXN],rev[MAXN];
	bool isroot(int x){return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;}
	bool which(int x){return ch[fa[x]][1]==x;}
	void rotate(int x){
		int dir=which(x),f=fa[x];
		if (!isroot(f)) ch[fa[f]][which(f)]=x;
		fa[x]=fa[f];
		ch[f][dir]=ch[x][dir^1]; 
		if (ch[x][dir^1]) fa[ch[x][dir^1]]=f;
		ch[x][dir^1]=f; fa[f]=x;
	}
	void splay(int x){
		for (int f=fa[x];!isroot(x);f=fa[x]){
			if (!isroot(f))
				rotate(which(f)==which(x)?f:x);
			rotate(x);
		}
	}
	int modify(int x,int delta){
		while (ch[x][0]) x=ch[x][0];
		Seg::update(st[x],ed[x],delta);
	}
	void access(int x){
		for (int last=0;x;last=x,x=fa[x]){
			splay(x);
			if (ch[x][1]) 
				modify(ch[x][1],1);
			if (last) 
				modify(last,-1);
			ch[x][1]=last;
		}
	}
}/*}}}*/
void add(int x,int y);
void dfs(int fa,int x,int d);
int get_lca(int x,int y);

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	int x,y,op,valx,valy,vallca,lca,valf;
	scanf("%d%d",&n,&m);
	memset(h,-1,sizeof(h));
	tot=0;
	for (int i=1;i<n;++i){
		scanf("%d%d",&x,&y);
		add(x,y); add(y,x);
	}
	dfn_t=0;
	dfs(0,1,1);
	Seg::build(n);
	for (int i=1;i<=m;++i){
		scanf("%d",&op);
		if (op==1){
			scanf("%d",&x);
			Lct::access(x);
		}
		else if (op==2){
			scanf("%d%d",&x,&y);
			lca=get_lca(x,y);
			valx=Seg::query(st[x],st[x]);
			valy=Seg::query(st[y],st[y]);
			vallca=Seg::query(st[lca],st[lca]);
			printf("%d\n",valx+valy-vallca*2+1);
		}
		else{
			scanf("%d",&x);
			valx=Seg::query(st[x],ed[x]);
			printf("%d\n",valx);
		}
	}
}

void add(int x,int y){
	a[++tot].y=y; a[tot].nxt=h[x]; h[x]=tot;
}

void dfs(int fa,int x,int d){
	int u;
	st[x]=++dfn_t; dep[x]=d; lis[dfn_t]=x;
	f[x][0]=fa;
	for (int i=1;i<=TOP;++i) f[x][i]=f[f[x][i-1]][i-1];
	for (int i=h[x];i!=-1;i=a[i].nxt){
		u=a[i].y;
		if (u==fa) continue;
		Lct::fa[u]=x;
		dfs(x,u,d+1);
	}
	ed[x]=dfn_t;
}

int get_lca(int x,int y){
	if (dep[x]<dep[y]) swap(x,y);
	for (int i=TOP;i>=0;--i)
		if (dep[f[x][i]]>=dep[y]) x=f[x][i];
	if (x==y) return x;
	for (int i=TOP;i>=0;--i)
		if (f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
	return f[x][0];
}
```



​	bzoj3779大概长这样qwq（pushdown毁一生qwq！）

```C++
#include<iostream>
#include<cstdio>
#include<cstring>
#define TOP 20
#define ll long long
using namespace std;
const int MAXN=1e5+10,SEG=MAXN*4+10;
struct xxx{
	int y,nxt;
}a[MAXN*2];
char s[20];
int h[MAXN],st[MAXN],ed[MAXN],dep[MAXN],lis[MAXN],f[MAXN][TOP+1],mxdfn[MAXN];
int n,m,tot,dfn_t;
int jump(int x,int d);
namespace Seg{/*{{{*/
	int ch[SEG][2];
	ll sum[SEG],tag[SEG];
	int tot,n;
	void pushup(int x){sum[x]=sum[ch[x][0]]+sum[ch[x][1]];}
	void _build(int x,int l,int r){
		sum[x]=0; tag[x]=0;
		if (l==r){sum[x]=dep[lis[l]]; return;}
		int mid=l+r>>1;
		ch[x][0]=++tot; _build(ch[x][0],l,mid);
		ch[x][1]=++tot; _build(ch[x][1],mid+1,r);
		pushup(x);
	}
	void build(int _n){n=_n; tot=1; _build(1,1,n);}
	void givetag(int x,int l,int r,int delta){tag[x]+=delta;sum[x]+=delta*(r-l+1);}
	void downtag(int x,int l,int r){
		if (tag[x]==0) return;
		int mid=l+r>>1;
		if (ch[x][0]) givetag(ch[x][0],l,mid,tag[x]);
		if (ch[x][1]) givetag(ch[x][1],mid+1,r,tag[x]);
		tag[x]=0;
	}
	void _update(int x,int l,int r,int lx,int rx,int delta){
		if (l<=lx&&rx<=r){
			givetag(x,lx,rx,delta);
			return;
		}
		downtag(x,lx,rx);
		int mid=lx+rx>>1;
		if (l<=mid) _update(ch[x][0],l,r,lx,mid,delta);
		if (r>mid) _update(ch[x][1],l,r,mid+1,rx,delta);
		pushup(x);
	}
	void update(int l,int r,int delta){_update(1,l,r,1,n,delta);}
	ll _query(int x,int l,int r,int lx,int rx){
		if (l<=lx&&rx<=r) return sum[x];
		downtag(x,lx,rx);
		int mid=lx+rx>>1; ll ret=0;
		if (l<=mid) ret+=_query(ch[x][0],l,r,lx,mid);
		if (r>mid) ret+=_query(ch[x][1],l,r,mid+1,rx);
		pushup(x);
		return ret;
	}
	ll query(int l,int r){return _query(1,l,r,1,n);}
}/*}}}*/
namespace Lct{/*{{{*/
	int ch[MAXN][2],fa[MAXN],rev[MAXN];
	int rt;
	bool isroot(int x){return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;}
	bool which(int x){return ch[fa[x]][1]==x;}
	void reverse(int x){
		swap(ch[x][0],ch[x][1]);
		rev[x]^=1;
	}
	void pushdown1(int x){
		if (rev[x]){
			if (ch[x][0]) reverse(ch[x][0]);
			if (ch[x][1]) reverse(ch[x][1]);
			rev[x]=0;
		}
	}
	void pushdown(int x){
		if (!isroot(x)) pushdown(fa[x]);
		pushdown1(x);
	}
	void rotate(int x){
		int dir=which(x),f=fa[x];
		if (!isroot(f)) ch[fa[f]][which(f)]=x;
		fa[x]=fa[f];
		ch[f][dir]=ch[x][dir^1];
		if (ch[x][dir^1]) fa[ch[x][dir^1]]=f;
		ch[x][dir^1]=f; fa[f]=x;
	}
	void splay(int x){
		pushdown(x);
		for (int f=fa[x];!isroot(x);f=fa[x]){
			if (!isroot(f)) 
				rotate(which(f)==which(x)?f:x);
			rotate(x);
		}
	}
	void modify(int x,int delta){
		while (ch[x][0]) pushdown1(x),x=ch[x][0];//pushdown!!!!!!
		if (x==rt){
			Seg::update(1,n,delta);
		}
		else if (st[x]<st[rt]&&st[rt]<=ed[x]){
			int pre=jump(rt,dep[rt]-dep[x]-1);
			if (st[pre]>1)
				Seg::update(1,st[pre]-1,delta);
			if (mxdfn[pre]<n)
				Seg::update(mxdfn[pre]+1,n,delta);
		}
		else{
			Seg::update(st[x],ed[x],delta);
		}
	}
	void access(int x){
		for (int last=0;x;last=x,x=fa[x]){
			splay(x);
			if (ch[x][1])
				modify(ch[x][1],1);
			if (last)
				modify(last,-1);
			ch[x][1]=last;
		}
	}
	void make_rt(int x){
		access(x);
		splay(x);
		reverse(x);
		rt=x;
	}
	double query(int x){
		ll ret=0,sz;
		if (x==rt){
			sz=n;
			ret=Seg::query(1,n);
		}
		else if (st[x]<st[rt]&&st[rt]<=ed[x]){
			int pre=jump(rt,dep[rt]-dep[x]-1);
			if (pre>1) 
				ret=Seg::query(1,st[pre]-1);
			if (mxdfn[pre]<n) 
				ret+=Seg::query(mxdfn[pre]+1,n);
			sz=st[pre]-1+(n-mxdfn[pre]);
		}
		else{
			ret=Seg::query(st[x],ed[x]);
			sz=ed[x]-st[x]+1;
		}
		return (double)ret/sz;
	}
}/*}}}*/
void add(int x,int y);
void dfs(int fa,int x,int d);
int get_lca(int x,int y);

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	int x,y;
	scanf("%d%d",&n,&m);
	memset(h,-1,sizeof(h));
	tot=0;
	for (int i=1;i<n;++i){
		scanf("%d%d",&x,&y);
		add(x,y); add(y,x);
	}
	dfn_t=0;
	dfs(0,1,1);
	Lct::rt=1;
	Seg::build(n);
	double ans;
	for (int i=1;i<=m;++i){
		scanf("%s %d\n",s,&x);
		if (s[2]=='Q'){
			double ans=Lct::query(x);
			printf("%.10lf\n",ans);
		}
		else if (s[2]=='L'){
			Lct::access(x);
		}
		else{
			Lct::make_rt(x);
		}
	}
}

void add(int x,int y){
	a[++tot].y=y; a[tot].nxt=h[x]; h[x]=tot;
}

void dfs(int fa,int x,int d){
	int u;
	f[x][0]=fa; dep[x]=d; st[x]=++dfn_t; lis[dfn_t]=x;
	mxdfn[x]=st[x];
	for (int i=1;i<=TOP;++i) f[x][i]=f[f[x][i-1]][i-1];
	for (int i=h[x];i!=-1;i=a[i].nxt){
		u=a[i].y;
		if (u==fa) continue;
		Lct::fa[u]=x;
		dfs(x,u,d+1);
		mxdfn[x]=max(mxdfn[x],mxdfn[u]);
	}
	ed[x]=dfn_t;
}

int get_lca(int x,int y){
	if (dep[x]<dep[y]) swap(x,y);
	for (int i=TOP;i>=0;--i)
		if (dep[f[x][i]]>=dep[y]) x=f[x][i];
	if (x==y) return x;
	for (int i=TOP;i>=0;--i)
		if (f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
	return f[x][0];
}

int jump(int x,int d){
	if (!d) return x;
	for(int i=0;i<=TOP;++i)
		if (d&(1<<i)) x=f[x][i];
	return x;
}
```

