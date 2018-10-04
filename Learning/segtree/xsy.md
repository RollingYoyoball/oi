Portal -->broken qwq

### Description

​	现在有一个树根，标号为$1$，我们要加入一些节点使得它变成一棵树

​	接下来加入的每一个节点都有一个能量值为$v[i]$，我们定义$d[i]$表示一个节点的儿子数$+1$，$son[i]$表示这个节点的儿子列表，一个节点的好看度为$w[i]=d[i]*(v[i]+\sum w[son[i]])$

​	现在给出$q$个操作：

类型1：读入$fa,v$表示新插入一个叶子节点，其父亲为$fa$（保证存在），能量值为$v$

类型2：读入$x$表示询问节点$x$的好看度$w[x]$

​	对于每一个类型2，输出答案



​	范围： 对于100%的数据：q<=200000，v[i]<=10^9 

### Solution

​	我觉得很气愤的事情是。。因为这题的题面出了一些偏差导致我看题看了1h+。。。

​	

​	这题的关键在于，我们要思考一下这个$w[i]$的组成

​	会发现其实$w[i]$可以看成$i$为根的子树内的每个节点$x$的$v[x]$乘上某个系数再加起来

​	而这个系数其实就是$i$到$x$一路上的$d$值的乘积

​	然后因为没有强制在线，我们可以离线处理每一个操作，因为插入的话感觉有点麻烦（其实好像也不会。。但是当时受题解的影响就直接写了转化成删除的版本了。。）所以我们考虑反过来处理，把插入转化成删除操作

​	那所以我们考虑用两棵线段树来分别维护根节点$1$到每一个点的这个系数（我们记为$mul[i]$好了），以及$\sum mul[i]*v[i]$，下标按照$dfn$序来排

​	那么查询就十分方便了，直接先查$x$子树内的$\sum mul[i]*v[i]$，然后再查一下$fa[x]$到$1$的一路上的$d$的乘积（也就是在第一棵线段树上查$dfn[fa[x]]$这个位置的值），然后把这乘积除掉就是答案了

​	至于修改的话，影响到的应该就是$fa[x]$子树内的所有节点（因为删除$x$这个节点相当于将$d[fa[x]]-1$），所以我们要对$fa[x]$子树范围内的所有位置乘上一个$inv(d[fa[x]])*(d[fa[x]]-1)$，其中$inv()$表示的是在$\% 10^9+7$意义下的逆元，然后因为$x$这个节点删掉了，所以我们相当于$x$的子树范围内的所有值直接都变成$0$（断开了嘛就不算了）

​	然后就。。两棵线段树做完啦ovo为了好好熟悉标记永久化写法这里强制自己写的是标记永久化



​	代码大概长这个样子

```C++
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
const int N=200010,MOD=1e9+7,SEG=N*4*2;
struct Q{
	int op,x,val;
}rec[N];
struct xxx{
	int y,nxt;
}a[N*2];
int d[N],v[N],w[N],pre[N],st[N],ed[N];
int h[N],mul[N],lis[N];
int ans[N];
int n,m,tot,dfn_t;
namespace Seg{/*{{{*/
	int ch[SEG][2],sum[SEG],tag[SEG],rt[2];
	int tot,n;
	void pushup(int x){
		sum[x]=1LL*sum[ch[x][0]]*tag[ch[x][0]]%MOD;
		sum[x]=(1LL*sum[x]+1LL*sum[ch[x][1]]*tag[ch[x][1]]%MOD)%MOD;
	}
	void _build(int x,int l,int r,int which){
		sum[x]=0; tag[x]=1;
		if (l==r){
			sum[x]=which==0?mul[lis[l]]:1LL*mul[lis[l]]*v[lis[l]]%MOD;
			return;
		}
		int mid=l+r>>1;
		ch[x][0]=++tot; _build(ch[x][0],l,mid,which);
		ch[x][1]=++tot; _build(ch[x][1],mid+1,r,which);
		pushup(x);
	}
	void build(int which,int _n){rt[which]=++tot; n=_n; _build(rt[which],1,n,which);}
	void _update(int x,int l,int r,int lx,int rx,int delta){
		if (l<=lx&&rx<=r){
			tag[x]=1LL*tag[x]*delta%MOD; return;
		}
		int mid=lx+rx>>1;
		if (r<=mid) _update(ch[x][0],l,r,lx,mid,delta);
		else if (l>mid) _update(ch[x][1],l,r,mid+1,rx,delta);
		else{
			_update(ch[x][0],l,mid,lx,mid,delta);
			_update(ch[x][1],mid+1,r,mid+1,rx,delta);
		}
		pushup(x);
	}
	void update(int which,int l,int r,int delta){_update(rt[which],l,r,1,n,delta);}
	int _query(int x,int l,int r,int lx,int rx){
		if (l<=lx&&rx<=r) return 1LL*sum[x]*tag[x]%MOD;
		int mid=lx+rx>>1;
		if (r<=mid) return 1LL*tag[x]*_query(ch[x][0],l,r,lx,mid)%MOD;
		else if (l>mid) return 1LL*tag[x]*_query(ch[x][1],l,r,mid+1,rx)%MOD;
		else{
			int tmp=1LL*tag[x]*_query(ch[x][0],l,mid,lx,mid)%MOD;
			int tmp2=1LL*tag[x]*_query(ch[x][1],mid+1,r,mid+1,rx)%MOD;
			return (tmp+tmp2)%MOD;
		}
	}
	int query(int which,int l,int r){return _query(rt[which],l,r,1,n);}
}/*}}}*/
int add(int x,int y){a[++tot].y=y; a[tot].nxt=h[x]; h[x]=tot;}
void dfs(int fa,int x,int now){
	int u,sz;
	d[x]=1; mul[x]=now; pre[x]=fa;
	st[x]=++dfn_t; lis[dfn_t]=x;
	for (int i=h[x];i!=-1;i=a[i].nxt) ++d[x];
	mul[x]=1LL*mul[x]*d[x]%MOD;
	for (int i=h[x];i!=-1;i=a[i].nxt){
		u=a[i].y;
		if (u==fa) continue;
		dfs(x,u,mul[x]);
	}
	ed[x]=dfn_t;
}
int ksm(int x,int y){
	int ret=1,base=x;
	for (;y;y>>=1,base=1LL*base*base%MOD)
		if (y&1) ret=1LL*ret*base%MOD;
	return ret;
}
void del(int x){
	int fa=pre[x],inv;
	inv=ksm(d[fa],MOD-2);
	inv=1LL*(d[fa]-1)*inv%MOD;
	--d[fa];
	Seg::update(0,st[fa],ed[fa],inv);
	Seg::update(1,st[fa],ed[fa],inv);
	Seg::update(0,st[x],ed[x],0);
	Seg::update(1,st[x],ed[x],0);
}
int query(int x){
	int ret=Seg::query(1,st[x],ed[x]),tmp;
	if (pre[x]){
		tmp=Seg::query(0,st[pre[x]],st[pre[x]]); 
		tmp=ksm(tmp,MOD-2);
	}
	else tmp=1;
	return 1LL*ret*tmp%MOD;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	int x,y,op;
	scanf("%d%d",&v[1],&m);
	n=1;
	memset(h,-1,sizeof(h));
	tot=0;
	for (int i=1;i<=m;++i){
		scanf("%d",&op);
		if (op==1){
			scanf("%d%d",&x,&y);
			++n; v[n]=y;
			add(x,n);
			rec[i].x=n; rec[i].op=op; rec[i].val=y;
		}
		else{
			scanf("%d",&x);
			rec[i].x=x; rec[i].op=op;
		}
	}
	dfn_t=0;
	dfs(0,1,1);
	Seg::build(0,n);
	Seg::build(1,n);
	for (int i=m;i>=1;--i){
		if (rec[i].op==1)
			del(rec[i].x);
		else{
			ans[i]=query(rec[i].x);
		}
	}
	for (int i=1;i<=m;++i) 
		if (rec[i].op==2) printf("%d\n",ans[i]);
}
```

