#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=400010;
struct xxx
{
	int y,next;
}a[MAXN*2];
int h[MAXN];
int sz[MAXN],mx[MAXN],idmx[MAXN];
int up[MAXN],down[MAXN],down2[MAXN],idown[MAXN];
int n,m,tot;
int add(int x,int y);
int update(int x,int u,int size);
int dfs(int fa,int x);
int dfs1(int fa,int x);

int main()
{
//	freopen("a.in","r",stdin);

	int x,y;
	scanf("%d",&n);
	memset(h,-1,sizeof(h));
	for (int i=1;i<n;++i)
	{
		scanf("%d%d",&x,&y);
		add(x,y); add(y,x);
	}
//	memset(ok,true,sizeof(ok));
	dfs(0,1);
	dfs1(0,1);
	bool flag=true;
	for (int i=1;i<=n;++i)
	{
		if (mx[i]<=n/2) flag=true;
		else if (n-sz[i]>n/2) flag=n-sz[i]-up[i]<=n/2;
		else flag=sz[idmx[i]]-down[i]<=n/2;
		printf("%d ",flag);
	}
}

int add(int x,int y)
{
	a[++tot].y=y; a[tot].next=h[x]; h[x]=tot;
}

int dfs(int fa,int x)
{
	int u;
	sz[x]=1; down[x]=0; down2[x]=0; mx[x]=0;
	for (int i=h[x];i!=-1;i=a[i].next)
	{
		u=a[i].y;
		if (u==fa) continue;
		dfs(x,u);
		sz[x]+=sz[u];
		if (sz[u]>mx[x]) idmx[x]=u,mx[x]=sz[u];
		if (sz[u]<=n/2) update(x,u,sz[u]);
		else update(x,u,down[u]);
	}
}

int update(int x,int u,int size)
{
	if (sz[u]>=down[x])
		down2[x]=down[x],down[x]=size,idown[x]=u;
	else if (sz[u]>=down2[x])
		down2[x]=size;
}

int dfs1(int fa,int x)
{
	int u,size;
	if (n-sz[x]>mx[x]) idmx[x]=fa,mx[x]=n-sz[x];
	for (int i=h[x];i!=-1;i=a[i].next)
	{
		u=a[i].y;
		if (u==fa) continue;
		if (n-sz[u]>n/2) up[u]=max(up[x],idown[x]==u?down2[x]:down[x]);
		else up[u]=n-sz[u];
		dfs1(x,u);
	}
}
