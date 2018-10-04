#include<iostream>
#include<cstdio>
#include<cstring>
#define inf 2147483647
using namespace std;
const int MAXN=100010;
struct xxx
{
	int y,next;
}a[MAXN*2];
int h[MAXN],mx[MAXN],mx2[MAXN],id[MAXN];
bool mark[MAXN];
int n,m,d,ans,tot;
int dfs(int fa,int x);
int dfs1(int fa,int x);
int update(int x,int u,int dis);
int add(int x,int y);

int main()
{
//	freopen("a.in","r",stdin);

	scanf("%d%d%d",&n,&m,&d);
	int x,y,z;
	memset(mark,false,sizeof(mark));
	for (int i=1;i<=m;++i) 
		scanf("%d",&x),mark[x]=true;
	memset(h,-1,sizeof(h));
	for (int i=1;i<n;++i)
	{
		scanf("%d%d",&x,&y);
		add(x,y); add(y,x);
	}
	dfs(0,1);
	ans=0;
	dfs1(0,1);
	for (int i=1;i<=n;++i) 
		if (mx[i]<=d) ++ans;
	printf("%d\n",ans);
}

int dfs(int fa,int x)
{
	int u;
	if (mark[x]) mx[x]=0;
	else mx[x]=-inf;
	for (int i=h[x];i!=-1;i=a[i].next)
	{
		u=a[i].y;
		if (u==fa) continue;
		dfs(x,u);
		update(x,u,mx[u]+1);
	}
}

int dfs1(int fa,int x)
{
	int u;
	for (int i=h[x];i!=-1;i=a[i].next)
	{
		u=a[i].y;
		if (u==fa) continue;
		if (u==id[x])
			update(u,x,mx2[x]+1);
		else
			update(u,x,mx[x]+1);
		dfs1(x,u);
	}
}

int update(int x,int u,int dis)
{
	if (mx[x]<dis)
		mx2[x]=mx[x],mx[x]=dis,id[x]=u;
	else mx2[x]=max(mx2[x],dis);
}

int add(int x,int y)
{
	a[++tot].y=y; a[tot].next=h[x]; h[x]=tot;
}
