#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=30010;
struct xxx
{
	int y,next;
}a[MAXN*2];
int h[MAXN],lch[MAXN*4],rch[MAXN*4],sum[MAXN*4],mx[MAXN*4],loc[MAXN*4];
int son[MAXN],top[MAXN],sz[MAXN],w[MAXN],dep[MAXN],f[MAXN];
int num[MAXN*4];
int n,m,tot,tot1;
int add(int x,int y);
int dfs(int fa,int x,int d);
int dfs1(int fa,int x);
int build(int x,int l,int r);
int update(int x,int d,int lx,int rx,int delta);
int query(int x,int l,int r,int lx,int rx,int flag);
int get_ans(int x,int y,int flag);
int pushup(int x);

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);

	int x,y;
	scanf("%d",&n);
	memset(h,-1,sizeof(h));
	for (int i=1;i<n;++i)
	{
		scanf("%d%d",&x,&y);
		add(x,y); add(y,x);
	}	
	for (int i=1;i<=n;++i)
		scanf("%d",w+i);
	tot1=0;
	dfs(0,1,1); 
	top[1]=1;
	dfs1(0,1);
	tot=1;
	build(1,1,tot1);
	scanf("%d",&m);
	char op[10];
	for (int i=1;i<=m;++i)
	{
		scanf("%s%d%d",op,&x,&y);
		if (op[0]=='C')
		{
			update(1,loc[x],1,n,y);
		}	
		else if (op[0]=='Q'&&op[1]=='M')
		{
			printf("%d\n",get_ans(x,y,0));
		}
		else
			printf("%d\n",get_ans(x,y,1));
	}
}

int add(int x,int y)
{
	a[++tot].y=y; a[tot].next=h[x]; h[x]=tot;
}

int dfs(int fa,int x,int d)
{
	sz[x]=1; son[x]=0; dep[x]=d;
	f[x]=fa;
	int u;
	for (int i=h[x];i!=-1;i=a[i].next)
	{
		u=a[i].y;
		if (u==fa) continue;
		dfs(x,u,d+1);
		sz[x]+=sz[u];
		if (sz[son[x]]<sz[u]) son[x]=u;
	}
}

int dfs1(int fa,int x)
{
	int u;
	loc[x]=++tot1;
	num[tot1]=x;
	if (son[x])
		top[son[x]]=top[x],dfs1(x,son[x]);
	for (int i=h[x];i!=-1;i=a[i].next)
	{
		u=a[i].y;
		if (u==fa||son[x]==u) continue;
		top[u]=u;
		dfs1(x,u);
	}
}

int update(int x,int d,int lx,int rx,int delta)
{
	if (lx==rx)
	{
		mx[x]=delta,sum[x]=delta;
		return 0;
	}
	int mid=lx+rx>>1;
	if (d<=mid) update(lch[x],d,lx,mid,delta);
	else update(rch[x],d,mid+1,rx,delta);
	pushup(x);
}

int pushup(int x)
{
	sum[x]=sum[lch[x]]+sum[rch[x]];
	mx[x]=max(mx[lch[x]],mx[rch[x]]);
}	

int query(int x,int l,int r,int lx,int rx,int mark)//0=max 1=sum
{
	if (l<=lx&&rx<=r)
	{
		return mark?sum[x]:mx[x];
	}
	int mid=lx+rx>>1,ret1=mark?0:-2147483647,ret2=mark?0:-2147483647;
	if (l<=mid) ret1=query(lch[x],l,r,lx,mid,mark);
	if (r>mid) ret2=query(rch[x],l,r,mid+1,rx,mark);
	return mark?ret1+ret2:max(ret1,ret2);
}

int build(int x,int l,int r)
{
	if (l==r)
	{
		mx[x]=sum[x]=w[num[l]];
		return 0;
	}
	int mid=l+r>>1;
	lch[x]=++tot;
	build(lch[x],l,mid);
	rch[x]=++tot;
	build(rch[x],mid+1,r);
	pushup(x);
}

int get_ans(int x,int y,int flag)
{
	int ret=flag?0:-2147483647;
	while (top[x]!=top[y])
	{
		if (dep[top[x]]<dep[top[y]]) swap(x,y);
		if (flag) ret+=query(1,loc[top[x]],loc[x],1,n,flag);
		else ret=max(ret,query(1,loc[top[x]],loc[x],1,n,flag));
		x=f[top[x]];
	}
	if (flag)
		ret+=query(1,min(loc[x],loc[y]),max(loc[x],loc[y]),1,n,flag);
	else
		ret=max(ret,query(1,min(loc[x],loc[y]),max(loc[x],loc[y]),1,n,flag));
	return ret;
}
