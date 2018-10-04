#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define inf 2147483647
#define TOP 14
using namespace std;
const int MAXN=50010;
const int N=10010;
struct xxx
{
	int y,next,limit;
}a[N*2];
struct xxx1
{
	int x,y,z;
}way[MAXN];
int h[N],f[N][15],fa[N],mn[N][15],dep[N];
bool vis[MAXN];
int n,m,tot,q,lca;
int get_f(int x);
bool cmp(xxx1 x,xxx1 y) {return x.z>y.z;}
int add(int x,int y,int z);
int dfs(int fa1,int x,int d);
int get_lca(int x,int y);

int main()
{
	freopen("a.in","r",stdin);
	
	scanf("%d%d",&n,&m);
	int x,y,z,fx,fy;
	for (int i=1;i<=n;++i) fa[i]=i;
	for (int i=1;i<=m;++i)
		scanf("%d%d%d",&way[i].x,&way[i].y,&way[i].z);
	sort(way+1,way+1+m,cmp);
	int cnt=0;
	memset(h,-1,sizeof(h));
	for (int i=1;i<=m;++i)
	{
		fx=get_f(way[i].x); fy=get_f(way[i].y);
		if (fx!=fy)
		{
			fa[fx]=fy;
			add(way[i].x,way[i].y,way[i].z);
			++cnt;
			if (cnt==n-1) break;
		}
	}
	memset(mn,0x7f,sizeof(mn));
	memset(vis,false,sizeof(vis));
	for (int i=1;i<=n;++i)
		if (!vis[i])
			dfs(0,i,1);	
	scanf("%d",&q);
	for (int i=1;i<=q;++i)
	{
		scanf("%d%d",&x,&y);
		fx=get_f(x); fy=get_f(y);
		if (fx!=fy) printf("-1\n");
		else printf("%d\n",get_lca(x,y));
	}
}

int get_f(int x)
{
	if (fa[x]!=x) fa[x]=get_f(fa[x]);
	return fa[x];
}

int add(int x,int y,int z)
{
	a[++tot].y=y; a[tot].next=h[x]; h[x]=tot; a[tot].limit=z;
	a[++tot].y=x; a[tot].next=h[y]; h[y]=tot; a[tot].limit=z;
}

int dfs(int fa1,int x,int d)
{
	int u;
	f[x][0]=fa1; dep[x]=d; vis[x]=true;
	for (int i=1;i<=TOP;++i) 
	{
		f[x][i]=f[f[x][i-1]][i-1];
		if (1<<i<=dep[x]) mn[x][i]=min(mn[f[x][i-1]][i-1],mn[x][i-1]);
	}
	for (int i=h[x];i!=-1;i=a[i].next)
	{
		u=a[i].y;
		if (u==fa1) continue;
		mn[u][0]=a[i].limit;
		dfs(x,u,d+1);
	}
}

int get_lca(int x,int y)
{
	int ans=inf;
	if (dep[x]<dep[y]) swap(x,y);
	for (int i=TOP;i>=0;--i)
		if (dep[f[x][i]]>=dep[y]) 
			ans=min(ans,mn[x][i]),x=f[x][i];

	if (x==y)
		return ans;
	for (int i=TOP;i>=0;--i)
		if (f[x][i]!=f[y][i]) 
		{
			ans=min(ans,min(mn[x][i],mn[y][i]));
			x=f[x][i],y=f[y][i];
		}
	return min(ans,min(mn[x][0],mn[y][0]));
}
