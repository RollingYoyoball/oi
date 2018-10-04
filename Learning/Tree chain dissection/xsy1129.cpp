#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define inf 2047483647
using namespace std;
const int MAXN=20010;
struct xxx
{
	int y,next;
}a[MAXN];
struct xxx1
{
	int r,y,next,op;
}g[MAXN*256*2];
queue<int> q;
int lch[MAXN*4],rch[MAXN*4];
int dep[MAXN],son[MAXN],sz[MAXN],top[MAXN];
int h[MAXN*4],f[MAXN],v1[MAXN],p[MAXN],k[MAXN],dfn[MAXN],num[MAXN];
int level[MAXN*4],id[MAXN];
int n,m,tot,s,t,tot1,ans,head,tail;
int dfs(int fa,int x,int d);
int dfs1(int fa,int x);
int build(int x,int l,int r);
int update(int x,int l,int r,int lx,int rx);
int add(int x,int y);
int add1(int x,int y,int flow);
int bfs();
int dfs2(int v,int o);
int work(int x,int d);

int main() 
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	
	scanf("%d",&n);
	memset(h,-1,sizeof(h));
	tot=0;
	for (int i=1;i<=n;++i)
	{
		scanf("%d%d%d%d",&f[i],&v1[i],&k[i],&p[i]);
		add(f[i],i); 
	}
	tot1=0;
	dfs(0,1,1);
	top[1]=1;
	dfs1(0,1);
	tot1=0;
	memset(h,-1,sizeof(h));
	build(++tot1,1,n);
	ans=0; s=0; t=tot1+n+1;
	for (int i=1;i<=n;++i)
	{
		if (v1[i]>0) add1(s,id[i],v1[i]),ans+=v1[i];
		else add1(id[i],t,-v1[i]);
		add1(id[i],++tot1,p[i]); 
		work(i,k[i]);
	}
	while(bfs())
		ans-=dfs2(s,inf);
	printf("%d\n",ans);
}

int add(int x,int y)
{
	a[++tot].y=y; a[tot].next=h[x]; h[x]=tot;
}

int add1(int x,int y,int flow)
{
	g[++tot].y=y; g[tot].next=h[x]; h[x]=tot; g[tot].op=tot+1; g[tot].r=flow;
	g[++tot].y=x; g[tot].next=h[y]; h[y]=tot; g[tot].op=tot-1; g[tot].r=0;
}

int dfs(int fa,int x,int d)
{
	sz[x]=1; son[x]=0; dep[x]=d; f[x]=fa;
	for (int i=h[x];i!=-1;i=a[i].next)
	{
		if (a[i].y==fa) continue;
		dfs(x,a[i].y,d+1);
		sz[x]+=sz[a[i].y];
		if (sz[son[x]]<sz[a[i].y]) son[x]=a[i].y;
	}
}

int dfs1(int fa,int x)
{
	int u;
	dfn[x]=++tot1; num[tot1]=x;
	if (son[x])
	{
		top[son[x]]=top[x];
		dfs1(x,son[x]);
	}
	for (int i=h[x];i!=-1;i=a[i].next)
	{
		if (a[i].y==fa||a[i].y==son[x]) continue;
		top[a[i].y]=a[i].y;
		dfs1(x,a[i].y);
	}
}

int build(int x,int l,int r)
{
	if (l==r)
	{
		id[num[l]]=x;
		return 0;
	}
	int mid=l+r>>1;
	lch[x]=++tot1; build(lch[x],l,mid);
	rch[x]=++tot1; build(rch[x],mid+1,r);
	add1(x,lch[x],inf);
	add1(x,rch[x],inf);
}

int update(int x,int l,int r,int lx,int rx)
{
	if (l<=lx&&rx<=r)
		{add1(tot1,x,inf);return 0;}
	int mid=lx+rx>>1;
	if (l<=mid) update(lch[x],l,r,lx,mid);
	if (r>mid) update(rch[x],l,r,mid+1,rx);
}

int work(int x,int d)
{
	if (d==0) return 0;
	for (x=f[x];dep[x]-dep[top[x]]+1<d;x=f[top[x]])
	{
		d-=(dep[x]-dep[top[x]]+1);
		update(1,dfn[top[x]],dfn[x],1,n);
	}
	update(1,dfn[x]-d+1,dfn[x],1,n);
}

int bfs()
{
	while (!q.empty()) q.pop();
	memset(level,0,sizeof(level));
	level[0]=1;
	q.push(0);
	int v,u;
	while (!q.empty())
	{
    	v=q.front(); q.pop();
    	for(int i=h[v];i!=-1;i=g[i].next) 
    	{
    		u=g[i].y;
    		if (g[i].r!=0&&level[u]==0)
    		{
    			level[u]=level[v]+1;
    			q.push(u);
    			if (u==t) return true;
    		}
    	}
	}
	return false;
}

int dfs2(int v,int o)
{
	if (v==t||o==0) return o;
	int ret=0,flow,u;
	for (int i=h[v];i!=-1;i=g[i].next)
	{
		u=g[i].y;
		if (level[u]==level[v]+1&&g[i].r)
		{
			flow=dfs2(u,min(o,g[i].r));
			if (flow!=0) 
			{
				g[i].r-=flow;
				g[g[i].op].r+=flow;
				ret+=flow;
				o-=flow;
				if (o==0) break;
			}
		}
	}
	if (!ret) level[v]=0;
	return ret;
}
