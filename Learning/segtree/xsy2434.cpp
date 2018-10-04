#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define inf 9023372036854775807
#define ll long long
using namespace std;
const int MAXN=400000+10;
struct xxx
{
	int y,next,dis;
}a[MAXN*20];
queue<int> q;
int get[MAXN*10],h[MAXN*10];
int lch[MAXN*10],rch[MAXN*10];
ll d[MAXN*10];
bool vis[MAXN*10];
int n,m,tot1,tot,s,rt1,rt0;
int build(int x,int l,int r,int flag);//0=down 1=up
int add1(int x,int l,int r,int lx,int rx);
int add(int x,int y,int dis);
int spfa(int N);

int main()
{
//	freopen("a.in","r",stdin);

	int dis,v,l,r,op;
	scanf("%d%d%d",&n,&m,&s);
	memset(h,-1,sizeof(h));
	tot=n; rt0=tot+1; tot1=0;
	build(++tot,1,n,0);
	rt1=tot+1;
	build(++tot,1,n,1);
	for (int i=1;i<=m;++i)
	{
		scanf("%d",&op);
		if (op==2)
		{
			scanf("%d%d%d%d",&v,&l,&r,&dis);
			get[0]=0;
			add1(rt0,l,r,1,n);
			for (int j=1;j<=get[0];++j)
				add(v,get[j],dis);
		}
		else if (op==3) 
		{
			scanf("%d%d%d%d",&v,&l,&r,&dis);
			get[0]=0;
			add1(rt1,l,r,1,n);
			for (int j=1;j<=get[0];++j)
				add(get[j],v,dis);
		}
		else
		{
			scanf("%d%d%d",&v,&l,&dis);
			add(v,l,dis);
		}	
	}
	spfa(tot);
}

int build(int x,int l,int r,int flag)
{
	if (l==r)
	{
		if (flag) add(l,x,0);
		else add(x,l,0);
		return 0;
	}
	lch[x]=++tot;
	int mid=(l+r)>>1;
	if (!flag) add(x,lch[x],0); 
	else add(lch[x],x,0);
	build(tot,l,mid,flag);
	rch[x]=++tot;
	if (!flag) add(x,rch[x],0); 
	else add(rch[x],x,0);
	build(tot,mid+1,r,flag);	
}

int add1(int x,int l,int r,int lx,int rx)
{
	if (l<=lx&&rx<=r)
	{
		get[++get[0]]=x;	
		return 0;
	}
	int mid=(lx+rx)>>1;
	if (l<=mid) add1(lch[x],l,r,lx,mid);
	if (r>mid) add1(rch[x],l,r,mid+1,rx);
}

int add(int x,int y,int dis)
{
	a[++tot1].y=y; a[tot1].next=h[x]; h[x]=tot1; a[tot1].dis=dis;
}

int spfa(int N)
{
	int v,u;
	while (!q.empty()) q.pop();
	q.push(s);
	memset(vis,false,sizeof(vis));
	vis[s]=true;
	for (int i=1;i<=N;++i) d[i]=inf;
	d[s]=0;
	while (!q.empty())
	{
		v=q.front(); q.pop();
		for (int i=h[v];i!=-1;i=a[i].next)
		{
			u=a[i].y;
			if (d[v]+a[i].dis<d[u])
			{
				d[u]=d[v]+a[i].dis;
				if (!vis[u])
					vis[u]=true,q.push(u);
			}
		}
		vis[v]=false;
	}
	for (int i=1;i<=n;++i)
		printf("%I64d ",d[i]==inf?-1:d[i]);
	printf("\n");
}
