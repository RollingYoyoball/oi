#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=2*(1e5)+10;
int rt[MAXN*2];
int n,m,t,lastans;
struct segtree
{
	int lch[MAXN*4*20],rch[MAXN*4*20],f[MAXN*4*20],dep[MAXN*4*20];
	int tot;
	int newnode(int x)
	{
		lch[++tot]=lch[x]; rch[tot]=rch[x];
		return tot;
	}
	int build() {rt[0]=++tot;_build(rt[0],1,n);}
	int _build(int x,int l,int r)
	{
		if (l==r)
		{
			f[x]=l;
			return 0;
		}
		int mid=l+r>>1;
		lch[x]=++tot; _build(lch[x],l,mid);
		rch[x]=++tot; _build(rch[x],mid+1,r);
	}
	int insert(int x,int d,int delta) {_insert(rt[x-1],rt[x],d,1,n,delta);}
	int _insert(int pre,int &x,int d,int lx,int rx,int delta)
	{
		x=newnode(pre);
		if (lx==rx)
		{
			f[x]=delta;
			return 0;
		}
		int mid=lx+rx>>1;
		if (d<=mid) _insert(lch[pre],lch[x],d,lx,mid,delta);
		else _insert(rch[pre],rch[x],d,mid+1,rx,delta);
	}
	int add(int t,int x) {_add(rt[t],x,1,n);}
	int _add(int x,int d,int lx,int rx)
	{
		if (lx==rx)
		{
			++dep[x];return 0;
		}
		int mid=lx+rx>>1;
		if (d<=mid) _add(lch[x],d,lx,mid);
		else _add(rch[x],d,mid+1,rx);
	}
	int query(int t,int x) {return _query(rt[t],x,1,n);}
	int _query(int x,int d,int lx,int rx)//return num not val
	{
		if (lx==rx) return x;
		int mid=lx+rx>>1;
		if (d<=mid) return _query(lch[x],d,lx,mid);
		return _query(rch[x],d,mid+1,rx);
	}
	int get_f(int t,int x)//return num not val
	{
		int tmp=query(t,x);
		if (x==f[tmp]) return tmp;
		return get_f(t,f[tmp]);
	}
	int link(int t,int x,int y)
	{
		x=get_f(t,x);
		y=get_f(t,y);
		if (f[x]==f[y]) return 0;
		if (dep[x]>dep[y]) swap(x,y);
		insert(t,f[x],f[y]);
		if (dep[x]==dep[y]) add(t,f[y]);
	}
	int check(int t,int x,int y)
	{
		x=get_f(t,x);
		y=get_f(t,y);
		if (f[x]==f[y]) return 1;
		return 0;
	}
	int debug()
	{
		for (int i=1;i<=n;++i)
			printf("%d ",f[get_f(t,i)]);
		printf("\n");
	}
}seg;

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);

	int x,y,op;
	scanf("%d%d",&n,&m);
	seg.build();
	lastans=t=0;
	for (int i=1;i<=m;++i)
	{
		scanf("%d",&op);
		rt[i]=rt[i-1];
		if (op==1)
		{
			scanf("%d%d",&x,&y);
			x^=lastans; y^=lastans;
			seg.link(i,x,y);
		}
		else if (op==2)
		{
			scanf("%d",&x);
			x^=lastans;
			rt[i]=rt[x];
		}
		else
		{
			scanf("%d%d",&x,&y);
			x^=lastans; y^=lastans;
			lastans=seg.check(i,x,y);
			printf("%d\n",lastans);
		}
	//	seg.debug();
	}
}
