#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=500010;
struct xxx
{
	int y,next;
	double p;
}a[MAXN*2];
int h[MAXN];
double p[MAXN],f[MAXN][2],cantf[MAXN];//1表示不能通过父亲充上电的可能性，0表示不能通过自己或者子树上充电的可能性 
int n,tot;
double ans;
int add(int x,int y,int p);
int dfs1(int fa,int x);
int dfs2(int fa,int x);

int main()
{
	freopen("a.in","r",stdin);
	
	int x,y,z;
	scanf("%d",&n);
	memset(h,-1,sizeof(h));
	for (int i=1;i<n;++i)
	{
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z);	add(y,x,z);
	}
	for (int i=1;i<=n;++i)
		scanf("%d",&x),p[i]=(double)x/100;
	dfs1(0,1);
	f[1][1]=1;
	dfs2(0,1);
	printf("%0.6lf\n",ans);
}

int add(int x,int y,int z)
{
	a[++tot].y=y; a[tot].next=h[x]; h[x]=tot; a[tot].p=(double)z/100;
}

int dfs1(int fa,int x)
{
	int u;
	f[x][0]=(double)1-p[x];
	for (int i=h[x];i!=-1;i=a[i].next)
	{
		u=a[i].y;
		if (u==fa) continue;
		dfs1(x,u);
		cantf[u]=f[u][0]+(1-f[u][0])*(1-a[i].p);
		f[x][0]*=cantf[u];
	}	
}

int dfs2(int fa,int x)
{
	int u;
	double cantson;
	ans+=1-f[x][1]*f[x][0];
	for (int i=h[x];i!=-1;i=a[i].next)
	{
		u=a[i].y;
		if (u==fa) continue;
		cantson=cantf[u]<1e-6?0:f[x][1]*(f[x][0]/cantf[u]);
		f[u][1]=cantson+(1-cantson)*(1-a[i].p);
		dfs2(x,u);
	}
}
