#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=50010;
struct xxx
{
	int y,next;
}a[MAXN*2];
int h[MAXN];
int f[MAXN][510];
int n,k,tot,ans;
int dfs(int fa,int x);
int add(int x,int y);

int main()
{
//	freopen("a.in","r",stdin);

	int x,y;
	scanf("%d%d",&n,&k);
	memset(h,-1,sizeof(h));
	for (int i=1;i<n;++i)
	{
		scanf("%d%d",&x,&y);
		add(x,y); add(y,x);
	}
	ans=0;
	dfs(0,1);
	printf("%d\n",ans);
}

int add(int x,int y)
{
	a[++tot].y=y; a[tot].next=h[x]; h[x]=tot;
}

int dfs(int fa,int x)
{
	for (int i=1;i<=k;++i) f[x][i]=0;
	f[x][0]=1;
	int u;
	for (int i=h[x];i!=-1;i=a[i].next)
	{
		u=a[i].y;
		if (u==fa) continue;
		dfs(x,u);
		for (int j=0;j<=k;++j)
			ans+=f[x][j]*f[u][k-j-1];
		for (int j=1;j<=k;++j)
			f[x][j]+=f[u][j-1];
	}
}
