#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=1e5+10;
struct xxx
{
	int y,next;
}a[MAXN];
int h[MAXN],sz[MAXN];
double f[MAXN];
int n,m,tot;
int dfs(int fa,int x);
int dfs1(int fa,int x);
int add(int x,int y);

int main()
{
//	freopen("a.in","r",stdin);

	scanf("%d",&n);
	int x;
	memset(h,-1,sizeof(h));
	for (int i=1;i<n;++i)
	{
		scanf("%d",&x);
		add(x,i+1); 
	}
	f[1]=1;
	dfs(0,1);
	dfs1(0,1);
	for (int i=1;i<=n;++i) printf("%.2lf ",f[i]);
}

int dfs(int fa,int x)
{
	int u;
	sz[x]=1;
	for (int i=h[x];i!=-1;i=a[i].next)
	{
		u=a[i].y;
		if (u==fa) continue;
		dfs(x,u);
		sz[x]+=sz[u];
	}
}

int dfs1(int fa,int x)
{
	int u;
	for (int i=h[x];i!=-1;i=a[i].next)
	{
		u=a[i].y;
		if (u==fa) continue;
		f[u]=(sz[x]-sz[u]-1)*0.5+f[x]+1;
		dfs1(x,u);
	}
}

int add(int x,int y)
{
	a[++tot].y=y; a[tot].next=h[x]; h[x]=tot;
}
