#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define TOP 20//-----------remember-----------------------//
#define ll long long
#define Pr pair<int,int>
#define mp(x,y) make_pair(x,y)
#define fir first
#define sec second
using namespace std;
const int MAXN=1e5+10;
struct xxx
{
	int y,next,dis;
}a[MAXN*2];
vector<Pr> son[MAXN];//fir=real_son sec=div_son
int h[MAXN],val[MAXN],dfn[MAXN],f[MAXN*2][TOP+1],Fa[MAXN],lis[MAXN*2];
int mx[MAXN],sz[MAXN],Log[MAXN*2];
bool vis[MAXN];
ll dis[MAXN];
ll s1[MAXN],s2[MAXN],s3[MAXN];
int n,m,tot,t,cnt,rt,size;
int add(int x,int y,int dis);
int dfs(int fa,int x,int d,ll dist);
int get_sz(int fa,int x);
int get_rt(int all,int fa,int x);
int update(int st,int x,ll delta);
int prework();
ll get_dis(int x,int y);
int get_lca(int x,int y);
ll calc(int st,int x);
int get_ans(int x);
int solve(int x);
int debug();

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);

	int x,y,z;
	ll tmp;
	scanf("%d%d",&n,&m);
	memset(h,-1,sizeof(h));
	for (int i=1;i<n;++i)
	{
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z); add(y,x,z);
	}
	dfs(0,1,1,0);
	prework();
//	debug();
	rt=solve(1);
	for (int i=1;i<=m;++i)
	{
		scanf("%d%d",&x,&y);
		update(x,x,y);
		tmp=get_ans(rt);
		tmp=calc(tmp,tmp);
		printf("%lld\n",tmp);
	}
}

int add(int x,int y,int dis)
{
	a[++tot].y=y; a[tot].next=h[x]; h[x]=tot; a[tot].dis=dis;
}

int dfs(int fa,int x,int d,ll dist)
{
	int u;
	dis[x]=dist;
	f[++cnt][0]=cnt; lis[cnt]=x;
	dfn[x]=cnt; 
	for (int i=h[x];i!=-1;i=a[i].next)
	{
		u=a[i].y;
		if (u==fa) continue;
		dfs(x,u,d+1,dist+a[i].dis);
		f[++cnt][0]=dfn[x]; 
	}
}

int get_sz(int fa,int x)
{
	int u;
	sz[x]=1; mx[x]=0;
	for (int i=h[x];i!=-1;i=a[i].next)
	{
		u=a[i].y;
		if (u==fa||vis[u]) continue;
		get_sz(x,u);
		sz[x]+=sz[u];
		if (sz[u]>mx[x]) mx[x]=sz[u];
	}
}

int get_rt(int all,int fa,int x)
{
	int u;
	if (sz[all]-sz[x]>mx[x]) mx[x]=sz[all]-sz[x];
	if (mx[x]<size) size=mx[x],rt=x;
	for (int i=h[x];i!=-1;i=a[i].next)
	{
		u=a[i].y;
		if (u==fa||vis[u]) continue;
		get_rt(all,x,u);
	}
}

int get_root(int x)
{
	rt=0,size=n;
	get_sz(0,x); get_rt(x,0,x);
	return rt;
}

int solve(int x)
{
	int u,v,tmp;
	x=get_root(x);
	vis[x]=true;
	for (int i=h[x];i!=-1;i=a[i].next)
	{
		u=a[i].y;
		if (vis[u]) continue;
		tmp=0;
		v=solve(u);
		Fa[v]=x;
		son[x].push_back(mp(u,v));
	}
	return x;
}

int update(int st,int x,ll delta)
{
	s1[x]+=get_dis(st,x)*delta;
	s2[x]+=delta;
	if (!Fa[x]) return 0;
	s3[x]+=get_dis(Fa[x],st)*delta;
	update(st,Fa[x],delta);
}

ll get_dis(int x,int y)
{
	int lca=get_lca(x,y);	
	return dis[x]+dis[y]-2*dis[lca];
}

int prework()
{
	for (int i=2;i<=2*n-1;++i)
		Log[i]=Log[i>>1]+1;
	for (int j=1;(1<<j)<=2*n-1;++j)
		for (int i=1;i+(1<<j)-1<=2*n-1;++i)
			f[i][j]=min(f[i][j-1],f[i+(1<<(j-1))][j-1]);
}

int get_lca(int x,int y)
{
	if (dfn[x]>dfn[y]) swap(x,y);
	int len=dfn[y]-dfn[x]+1,k=Log[len];
	return lis[min(f[dfn[x]][k],f[dfn[y]-(1<<k)+1][k])];
}

ll calc(int st,int x)
{
	ll ret=s1[x];
	if (Fa[x])
		ret+=calc(st,Fa[x])+(s2[Fa[x]]-s2[x])*get_dis(Fa[x],st)-s3[x];
	return ret;
}

int get_ans(int x)
{
	ll now=calc(x,x),tmp;
	Pr u;
	for (int i=0;i<son[x].size();++i)
	{
		u=son[x][i];
		tmp=calc(u.fir,u.fir);
		if (tmp<now)
			return get_ans(u.sec);
	}
	return x;
}

int debug()
{
	for (int i=1;i<=n;++i)
		for (int j=1;j<i;++j)
			printf("%d %d %d\n",j,i,get_lca(i,j));
}
