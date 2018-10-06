[**Portal --> CC Chef and Graph Queries**](https://www.codechef.com/problems/GERALD07)

### Solution

​	快乐数据结构题

​	首先考虑一种方式来方便一点地。。计算一个图的联通块数量：我们可以考虑容斥，维护每个连通块的生成树，然后$n-$生成树边数就是答案了

​	这样有一个好，加边的时候比较好处理，但是光这样并不能解决我们的问题

​	顺着这个思路思考，先不考虑时间复杂度，对于一个询问，考虑将编号为$l\sim r$的边一条一条加入第$1\sim l-1$条边得到的生成树（们）中（先不考虑这个生成树边的选择方式），考虑一条边有贡献（成为新的生成树（们）中的一部分）的情况：

（1）这条边可以替换掉$1\sim l-1$中的某条边

（2）这条边的两个端点当前不连通

​	所以问题就变成了，看$l\sim r$中有多少条边可以替换掉在生成树中的编号在$1\sim l-1$范围内的边再加上（2）情况中的边

​	这个时候，我们就可以确定生成树边的选择方式了：因为要让能替换掉在$1\sim l-1$范围内的边尽量多，所以一旦当前边可以替换掉另一条边，我们肯定优先选择编号小的替换

​	再注意到在考虑询问$(l,r)$的时候，我们其实相当于要得到$1\sim r$的生成树（们），于是我们就可以预处理，按顺序加边，用LCT维护当前的生成树（们），再用一棵主席树（按权值存）维护一下第$1\sim i$条边的生成树中，每个编号的边能被多少条编号更大的边替换掉，为了方便查询，那些不需要替换直接加入的边统一加到$0$的位置，然后查询的时候只要在第$r$棵和第$l-1$棵中查一下$[0,l-1]$的和然后相减一下，再拿$n$减一下就是答案了



​	代码大概长这个样子

```C++
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N=2*(1e5)+10,SEG=N*20,inf=2147483647;
int rec[N][2];
int n,m,Q,T;
namespace Lct{/*{{{*/
	const int N=::N*2;
	int ch[N][2],mn[N],fa[N],rev[N],val[N];
	void reset(int x){
		ch[x][0]=ch[x][1]=0; fa[x]=0; val[x]=mn[x]=inf;
	}
	void clear(int n){
		for (int i=1;i<=n;++i) reset(i);
	}
	bool isroot(int x){return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;}
	int which(int x){return ch[fa[x]][1]==x;}
	void reverse(int x){
		swap(ch[x][0],ch[x][1]);
		rev[x]^=1;
	}
	void pushdown1(int x){
		if (!rev[x]) return;
		if (ch[x][0]) reverse(ch[x][0]);
		if (ch[x][1]) reverse(ch[x][1]);
		rev[x]=0;
	}
	void pushdown(int x){
		if (!isroot(x)) pushdown(fa[x]);
		pushdown1(x);
	}
	void pushup(int x){
		mn[x]=val[x];
		if (ch[x][0]) mn[x]=min(mn[x],mn[ch[x][0]]);
		if (ch[x][1]) mn[x]=min(mn[x],mn[ch[x][1]]);
	}
	void rotate(int x){
		int dir=which(x),f=fa[x];
		if (!isroot(f)) ch[fa[f]][which(f)]=x;
		fa[x]=fa[f]; fa[f]=x; 
		if (ch[x][dir^1]) fa[ch[x][dir^1]]=f;
		ch[f][dir]=ch[x][dir^1];
		ch[x][dir^1]=f;
		pushup(f); pushup(x);
	}
	void splay(int x){
		pushdown(x);
		for (int f=fa[x];!isroot(x);f=fa[x]){
			if (!isroot(f))
				rotate(which(f)==which(x)?f:x);
			rotate(x);
		}
		pushup(x);
	}
	void access(int x){
		for (int last=0;x;last=x,x=fa[x]){
			splay(x);
			ch[x][1]=last;
			pushup(x);
		}
	}
	void make_rt(int x){
		access(x);
		splay(x);
		reverse(x);
	}
	bool connected(int x,int y){
		if (x==y) return true;
		make_rt(x);
		access(y);
		splay(y);
		return fa[x];
	}
	void link(int x,int y){
		make_rt(x);
		fa[x]=y;
		access(x);
		splay(x);
	}
	void cut(int x,int y){
		make_rt(x);
		access(y);
		splay(y);
		fa[x]=0;
		ch[y][0]=0;
		pushup(y);
	}
	int query(int x,int y){
		make_rt(x);
		access(y);
		splay(y);
		return mn[y];
	}
}/*}}}*/
namespace Seg{/*{{{*/
	int ch[SEG][2],sum[SEG],rt[SEG];
	int n,tot;
	void clear(){
		for (int i=0;i<=tot;++i)
			ch[i][0]=ch[i][1]=0,sum[i]=0;
		tot=0;
	}
	void init(int _n){clear();n=_n;}
	int newnode(int pre){
		ch[++tot][0]=ch[pre][0]; ch[tot][1]=ch[pre][1]; sum[tot]=sum[pre];
		return tot;
	}
	void _insert(int pre,int &x,int d,int lx,int rx){
		x=newnode(pre);
		++sum[x];
		if (lx==rx) return;
		int mid=lx+rx>>1;
		if (d<=mid) _insert(ch[pre][0],ch[x][0],d,lx,mid);
		else _insert(ch[pre][1],ch[x][1],d,mid+1,rx);
	}
	void insert(int pre,int x,int d){_insert(rt[pre],rt[x],d,1,n);}
	int _query(int L,int R,int l,int r,int lx,int rx){
		if (!L&&!R) return 0;
		if (l<=lx&&rx<=r) return sum[R]-sum[L];
		int mid=lx+rx>>1,ret=0;
		if (l<=mid) ret+=_query(ch[L][0],ch[R][0],l,r,lx,mid);
		if (r>mid) ret+=_query(ch[L][1],ch[R][1],l,r,mid+1,rx);
		return ret;
	}
	int query(int L,int R,int l,int r){return _query(rt[L-1],rt[R],l,r,1,n);}
}/*}}}*/
void init(){
	Lct::clear(n+m);
	Seg::init(m+1);
}
void debug(int x){
	printf("#%d:\n",x);
	for (int i=0;i<=m;++i) printf("%d ",Seg::query(x-1,x,i+1,i+1));
	printf("\n");
}
void solve(){
	int x,y,tmp;
	for (int i=1;i<=m;++i){
		scanf("%d%d",&rec[i][0],&rec[i][1]);
		x=rec[i][0]; y=rec[i][1];
		if (x==y){
			Seg::rt[i]=Seg::rt[i-1];
			continue;
		}
		Lct::val[n+i]=i;
		if (Lct::connected(x,y)){
			tmp=Lct::query(x,y);
			Lct::cut(rec[i][0],n+tmp);
			Lct::cut(rec[i][1],n+tmp);
			Lct::link(x,n+i);
			Lct::link(y,n+i);
			Seg::insert(i-1,i,tmp+1);
		}
		else{
			Lct::link(x,n+i);
			Lct::link(y,n+i);
			Seg::insert(i-1,i,0+1);
		}
		//debug(i);
	}
	int l,r;
	for (int i=1;i<=Q;++i){
		scanf("%d%d",&l,&r);
		printf("%d\n",n-Seg::query(l,r,0+1,(l-1)+1));
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	scanf("%d",&T);
	for (int o=1;o<=T;++o){
		scanf("%d%d%d",&n,&m,&Q);
		init();
		solve();
	}
}
```

