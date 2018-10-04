#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define ll long long
#define inf 8023372036854775807
using namespace std;
const int MAXN=50010*10;
struct xxx
{
	int y,next,dis;
}a[MAXN*6];
int lch[MAXN],rch[MAXN],h[MAXN];
ll d[MAXN][11],ans;
bool vis[MAXN];
queue<int> q;
int n,m,k,T,tot,tot1,rt0,rt1,s,t;
int add1(int x,int l,int r,int lx,int rx,int node,int dis);
int build(int x,int l,int r,int flag);
ll spfa(int N);
int add(int x,int y,int dis);
int work(int dis);

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	
	int l,r,l1,r1,dis,tmp;
	scanf("%d",&T);
	for (int o=1;o<=T;++o)
	{
		scanf("%d%d%d",&n,&m,&k);
		tot1=0; tot=0;
		memset(h,-1,sizeof(h));
		rt0=tot+1;
		build(++tot,1,n,0);
		rt1=tot+1;
		build(++tot,1,n,1);
		for (int i=1;i<=m;++i)
		{
			scanf("%d%d%d%d%d\n",&l,&r,&l1,&r1,&dis);
			add1(rt0,l,r,1,n,++tot,dis);
			add1(rt1,l1,r1,1,n,tot,dis);
			add1(rt1,l,r,1,n,++tot,dis);
			add1(rt0,l1,r1,1,n,tot,dis);
		}
		ans=spfa(tot);
		if (ans==inf) printf("Yww is our red sun!\n");
		else printf("%lld\n",ans);
	}
}

int add1(int x,int l,int r,int lx,int rx,int node,int dis)
{
	if (l<=lx&&rx<=r)
	{
		if (x>=rt1) 
			add(x,node,dis);
		else add(node,x,0);
		return 0;
	}
	int mid=(lx+rx)>>1;
	if (l<=mid) add1(lch[x],l,r,lx,mid,node,dis);
	if (r>mid) add1(rch[x],l,r,mid+1,rx,node,dis);
}

int build(int x,int l,int r,int flag)
{
	if (l==r)
	{
		if (flag) 
			add(x-rt1+rt0,x,0);
		if (flag&&l==1) s=x;
		if (!flag&&l==n) t=x;
		return 0;
	}
	int mid=(l+r)>>1;
	lch[x]=++tot;
	if (flag) add(lch[x],x,0);
	else add(x,lch[x],0);
	build(lch[x],l,mid,flag);
	rch[x]=++tot;
	if (flag) add(rch[x],x,0);
	else add(x,rch[x],0);
	build(rch[x],mid+1,r,flag);
}

int add(int x,int y,int dis)
{
	a[++tot1].y=y; a[tot1].next=h[x]; h[x]=tot1; a[tot1].dis=dis;
}

ll spfa(int N)
{
	while (!q.empty()) q.pop();
	memset(vis,false,sizeof(vis));
	vis[s]=0;
	for (int i=1;i<=N;++i)
		for (int j=0;j<=k;++j)
			d[i][j]=inf;
	d[s][0]=0;
	q.push(s);
	int v,u;
	while (!q.empty())
	{
		v=q.front(); q.pop();
		for (int i=h[v];i!=-1;i=a[i].next)
		{
			u=a[i].y;
			for (int j=0;j<=k;++j)
			{
				if (j>0)
				{
					if (d[v][j-1]<d[u][j])
					{
						d[u][j]=d[v][j-1];
						if (!vis[u])
							q.push(u),vis[u]=true;
					}	
				}	
				if (d[v][j]+a[i].dis<d[u][j])
				{
					d[u][j]=d[v][j]+a[i].dis;
					if (!vis[u])
						q.push(u),vis[u]=true;
				}
			}
		}
		vis[v]=false;
	}
	ll ret=inf;
	for (int i=0;i<=k;++i)
		ret=min(d[t][i],ret);
	return ret;
}

