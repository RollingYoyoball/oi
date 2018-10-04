#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int MAXM=200010;
const int MAXN=5010;
struct xxx
{
	int y,next;
	double dis;
}a[MAXM*2];
double g[MAXN];
struct data
{
	int x;
	double dis;
	data(int x1,double dis1) {x=x1; dis=dis1;}
	bool operator < (const data &b) const
	{return g[b.x]+b.dis<g[x]+dis;}
};
queue<int> q;
priority_queue<data> q1;
bool vis[MAXN];
int h[MAXN],h1[MAXN];
int n,m,tot,ans;
double e;
int add(int x,int y,double dis);
int add1(int x,int y,double dis);
int get_g();
int astar();

int main()
{
//	freopen("a.in","r",stdin);
//	freopen("a.out","w",stdout);

	int x,y;
	double z;
	memset(h,-1,sizeof(h));
	memset(h1,-1,sizeof(h1));
	tot=0;
	scanf("%d%d%lf",&n,&m,&e);
	for (int i=1;i<=m;++i)
	{
		scanf("%d %d %lf\n",&x,&y,&z);
		add(x,y,z);
		add1(y,x,z);
	}
	get_g();
	ans=0;
	astar();
	printf("%d\n",ans);
}

int add(int x,int y,double dis)
{
	a[++tot].y=y; a[tot].dis=dis; a[tot].next=h[x]; h[x]=tot;
}

int add1(int x,int y,double dis)
{
	a[++tot].y=y; a[tot].dis=dis; a[tot].next=h1[x]; h1[x]=tot;
}

int get_g()
{	
	while (!q.empty()) q.pop();
	q.push(n);
	int u,v;
	memset(g,0x7f,sizeof(g));
	g[n]=0;
	vis[n]=true;
	while (!q.empty())
	{
		u=q.front(); q.pop();
		for (int i=h1[u];i!=-1;i=a[i].next)
		{
			v=a[i].y;
			if (g[v]>g[u]+a[i].dis)
			{
				g[v]=g[u]+a[i].dis;
				if (!vis[v])
					q.push(v),vis[v]=true;
			}
		}
		vis[u]=false;
	}
}

int astar()
{
	q1.push(data(1,0));
	while (!q1.empty())
	{
		data u=q1.top(); q1.pop();
		if (u.x==n)
		{
			e-=u.dis;
			if (e<0) return 0;
			++ans;
		}
		for (int i=h[u.x];i!=-1;i=a[i].next)
			q1.push(data(a[i].y,a[i].dis+u.dis));
	}
}
