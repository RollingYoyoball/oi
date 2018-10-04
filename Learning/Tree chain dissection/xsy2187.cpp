#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=100010;
const int MAXM=200010;
struct xxx
{
	int y,next;
}a[MAXM*4];
int lch[MAXN*4],rch[MAXN*4],sum[MAXN*4],tag[MAXN*4];
int low[MAXN],dfn1[MAXN];
int h[MAXN],son[MAXN],sz[MAXN],top[MAXN],dep[MAXN],up[MAXN],dfn[MAXN],num[MAXN];
bool bridge[MAXN];
int n,m,tot,ans,q,tot1,cnt;
int init();
int tarjan(int fa,int x,int d);
int dfs(int fa,int x,int d);
int dfs1(int x);
int update(int x,int l,int r,int lx,int rx,int delta);
int query(int x,int l,int r,int lx,int rx);
int solve(int x,int y);
int downtag(int x);
int build(int x,int l,int r);
int add(int x,int y);

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);

	int x,y,fx,fy;
	cnt=0;
	while (1)
	{
		++cnt;
		scanf("%d%d",&n,&m);
		ans=0;
		if (n==0&&m==0) break;
		printf("Case %d:\n",cnt);
		tot=0;
		init();
		for (int i=1;i<=m;++i)
		{
			scanf("%d%d",&x,&y);
			add(x,y); add(y,x);
		}
		tarjan(0,1,1);
		tot1=0;
		top[1]=1;
		dfs1(1);
		tot=1;
		build(1,1,n);
		scanf("%d",&q);
		for (int i=1;i<=q;++i)
		{
			scanf("%d%d",&x,&y);
			ans-=solve(x,y);
			printf("%d\n",ans);
		}
		printf("\n");
	}
}

int init()
{
	memset(dfn,0,sizeof(dfn));
	memset(h,-1,sizeof(h));
	memset(bridge,0,sizeof(bridge));
	memset(dfn1,0,sizeof(dfn1));
	memset(top,0,sizeof(top));
}

int tarjan(int fa,int x,int d)
{
	int u;
	low[x]=dfn1[x]=++tot1;
	sz[x]=1; dep[x]=d;
	son[x]=0; up[x]=fa; bridge[x]=0;
	for (int i=h[x];i!=-1;i=a[i].next)
	{
		u=a[i].y;
		if (u==fa) continue;
		if (!dfn1[u])
		{
			tarjan(x,u,d+1);
			low[x]=min(low[x],low[u]);
			if (low[u]>dfn1[x]) bridge[u]=1,++ans;
			sz[x]+=sz[u];
			if (sz[son[x]]<sz[u]) son[x]=u;
		}
		else if (dfn1[u]<dfn1[x])
			low[x]=min(low[x],dfn1[u]);
	}
}

int add(int x,int y)
{
	a[++tot].y=y; a[tot].next=h[x]; h[x]=tot;
}

int dfs1(int x)
{
	int u;
	dfn[x]=++tot1; num[tot1]=x;
	if (son[x])
	{
		top[son[x]]=top[x];
		dfs1(son[x]);
	}
	for (int i=h[x];i!=-1;i=a[i].next)
	{
		u=a[i].y;
		if (u==son[x]||dfn[u]) continue;
		top[u]=u;
		dfs1(u);
	}
}

int build(int x,int l,int r)
{
	if (l==r)
	{
		sum[x]=bridge[num[l]];
		return 0;
	}
	int mid=l+r>>1;
	lch[x]=++tot;
	build(lch[x],l,mid);
	rch[x]=++tot;
	build(rch[x],mid+1,r);
	sum[x]=sum[lch[x]]+sum[rch[x]]; tag[x]=0;
}

int update(int x,int l,int r,int lx,int rx,int delta)
{
	if (l<=lx&&rx<=r)
	{
		sum[x]=0; tag[x]=delta;
		return 0;
	}
	int mid=lx+rx>>1;
	if (tag[x]) downtag(x);
	if (l<=mid) update(lch[x],l,r,lx,mid,delta);
	if (r>mid) update(rch[x],l,r,mid+1,rx,delta);
	sum[x]=sum[lch[x]]+sum[rch[x]];
}

int query(int x,int l,int r,int lx,int rx)
{
	if (l<=lx&&rx<=r)
		return sum[x];
	int mid=lx+rx>>1,ret=0;
	if (tag[x]) downtag(x);
	if (l<=mid) ret+=query(lch[x],l,r,lx,mid);
	if (r>mid) ret+=query(rch[x],l,r,mid+1,rx);
	sum[x]=sum[lch[x]]+sum[rch[x]];
	return ret;
}

int downtag(int x)
{	
	sum[lch[x]]=0; tag[lch[x]]=tag[x];
	sum[rch[x]]=0; tag[rch[x]]=tag[x];
	tag[x]=0;
}

int solve(int x,int y)
{
	int ret=0;
	while (top[x]!=top[y])
	{
		if (dep[top[x]]<dep[top[y]]) swap(x,y);
		ret+=query(1,dfn[top[x]],dfn[x],1,n);
		update(1,dfn[top[x]],dfn[x],1,n,1);
		x=up[top[x]];
	}
	if (min(dfn[x],dfn[y])<max(dfn[x],dfn[y]))
	{
		ret+=query(1,min(dfn[x],dfn[y])+1,max(dfn[x],dfn[y]),1,n);
		update(1,min(dfn[x],dfn[y])+1,max(dfn[x],dfn[y]),1,n,1);
	}
	return ans==0?0:ret;
}
