#include<iostream>
#include<cstdio>
#include<cstring>
#define TOP 19
using namespace std;
const int MAXN=300010;
struct xxx
{
	int y,next;
}a[MAXN*2];
int h[MAXN],dfn[MAXN],f[MAXN][20],dep[MAXN],num[MAXN];
int lch[MAXN*4],rch[MAXN*4],mx[MAXN*4],mn[MAXN*4];
int n,m,tot;
int dfs(int fa,int x,int d);
int build(int x,int l,int r);
int query(int x,int l,int r,int lx,int rx,int mark);//0=mn 1=mx
int pushup(int x);
int add(int x,int y);
int get_lca(int x,int y);

int main()
{
	freopen("a.in","r",stdin);

	int x,y;
	while (scanf("%d",&n)!=EOF)
	{
		memset(h,-1,sizeof(h));
		tot=0;
		for (int i=1;i<n;++i)
		{
			scanf("%d%d",&x,&y);
			add(x,y); add(y,x);
		}
		tot=0;
		dfs(0,1,1);
		tot=1;
		build(1,1,n);
		scanf("%d",&m);
		int xx,yy;
		for (int i=1;i<=m;++i)
		{
			scanf("%d%d",&x,&y);
			xx=query(1,x,y,1,n,0);
			yy=query(1,x,y,1,n,1);
			printf("%d\n",get_lca(num[xx],num[yy]));
		}
	}
}

int dfs(int fa,int x,int d)
{
	int u;
	dfn[x]=++tot; num[tot]=x;
	f[x][0]=fa; dep[x]=d;
	for (int i=1;i<=TOP;++i)
		f[x][i]=f[f[x][i-1]][i-1];
	for (int i=h[x];i!=-1;i=a[i].next)
	{
		u=a[i].y;
		if (u==fa) continue;
		dfs(x,u,d+1);
	}
}

int build(int x,int l,int r)
{
	if (l==r)
	{
		mx[x]=mn[x]=dfn[l];
		return 0;
	}
	int mid=l+r>>1;
	lch[x]=++tot;
	build(lch[x],l,mid);
	rch[x]=++tot;
	build(rch[x],mid+1,r);
	pushup(x);
}

int pushup(int x)
{
	mx[x]=max(mx[lch[x]],mx[rch[x]]);
	mn[x]=min(mn[lch[x]],mn[rch[x]]);
}

int query(int x,int l,int r,int lx,int rx,int mark)//0=mn 1=mx
{
	if (l<=lx&&rx<=r)
		return mark?mx[x]:mn[x];
	int mid=lx+rx>>1,ret1=mark?0:n,ret2=mark?0:n;
	if (l<=mid) ret1=query(lch[x],l,r,lx,mid,mark);
	if (r>mid) ret2=query(rch[x],l,r,mid+1,rx,mark);
	return mark?max(ret1,ret2):min(ret1,ret2);
}

int get_lca(int x,int y)
{
	if (dep[x]<dep[y]) swap(x,y);
	for (int i=TOP;i>=0;--i)
		if (dep[f[x][i]]>=dep[y])
			x=f[x][i];
	if (x==y) return x;
	for (int i=TOP;i>=0;--i)
		if (f[x][i]!=f[y][i])
			x=f[x][i],y=f[y][i];
	return f[x][0];
}

int add(int x,int y)
{
	a[++tot].y=y; a[tot].next=h[x]; h[x]=tot;
}
