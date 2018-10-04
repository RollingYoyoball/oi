#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=100010;
const int MAX=31;
struct xxx
{
	int y,next,dis;
}a[MAXN*2];
int h[MAXN];
int ch[MAXN*32][2];
int dis[MAXN];
int n,m,tot,ans;
int add(int x,int y,int d);
int dfs(int fa,int x,int d);
int insert(int x);
int query(int x);

int main()
{
	freopen("a.in","r",stdin);

	scanf("%d",&n);
	int x,y,z;
	memset(h,-1,sizeof(h));
	for (int i=1;i<n;++i)
	{
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z);
		add(y,x,z);
	}
	dfs(-1,1,0);
	tot=1;
	for (int i=1;i<=n;++i)
	{
		insert(dis[i]);
	}
	ans=0;
	for (int i=1;i<=n;++i)
	{
		ans=max(ans,query(dis[i]));
	}
	printf("%d\n",ans);
}

int add(int x,int y,int d)
{
	a[++tot].y=y; a[tot].next=h[x]; h[x]=tot; a[tot].dis=d;
}

int dfs(int fa,int x,int d)
{
	dis[x]=d;
	for (int i=h[x];i!=-1;i=a[i].next)
	{
		int u=a[i].y;
		if (u==fa) continue;
		dfs(x,u,d^a[i].dis);
	}
}

int insert(int x)
{
	int now=1;
	for (int i=MAX;i>=0;--i)
	{
		bool w=x&(1<<i);
		if (!ch[now][w]) ch[now][w]=++tot;
		now=ch[now][w];
	}
}

int query(int x)
{
	int now=1,re=0;
	for (int i=MAX;i>=0;--i)
	{
		bool w=x&(1<<i);
		if (ch[now][!w]) re=re+(1<<i),now=ch[now][!w];
		else now=ch[now][w];
	}
	return re;
}
