#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define TOP 20
#define Pr pair<int,int>
#define mp(x,y) make_pair(x,y)
#define ll long long
#define sec second
#define fir first
using namespace std;
const int MAXN=150010;
struct xxx
{
	int y,next,dis;
}a[MAXN*2];
vector<Pr> info[MAXN],finfo[MAXN];
vector<ll> sum[MAXN],fsum[MAXN];
int h[MAXN],sz[MAXN],mx[MAXN],dis[MAXN],dep[MAXN],f[MAXN][TOP+1],Fa[MAXN],age[MAXN];
bool vis[MAXN];
int n,m,tot,A,rt,size;
ll ans;
int add(int x,int y,int dis);
int get_sz(int fa,int x);
int get_rt(int Rt,int fa,int x);
int dfs(int fa,int x,int dep,int dist);
int solve(int x,int predis);
int get_dis(int x,int y);
int get_root(int x) {size=n,rt=0;get_sz(0,x);get_rt(x,0,x);return rt;}
ll query(int st,int x,int l,int r,int sonsz,ll sonsum);
ll calc(vector<Pr> &val,vector<ll> &s,int l,int r,int op);
int get_info(int st,int fa,int x,int dis,int op);
int get_l(vector<Pr> &x,int val);
int get_r(vector<Pr> &x,int val);
int debug(vector<Pr> x);
int debug1(vector<ll> x);

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	
	int x,y,z,l,r;
	scanf("%d%d%d",&n,&m,&A);
	memset(h,-1,sizeof(h));
	for (int i=1;i<=n;++i) scanf("%d",age+i);
	for (int i=1;i<n;++i)
	{
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z);
		add(y,x,z);
	}
	dfs(0,1,1,0);
	solve(1,0);
	for (int i=1;i<=m;++i)
	{
		scanf("%d%d%d",&x,&l,&r);
		l=(l+ans)%A; r=(r+ans)%A;
		if (l>r) swap(l,r);
		ans=query(x,x,l,r,0,0);
		printf("%lld\n",ans);
	}
}

int add(int x,int y,int dis)
{
	a[++tot].y=y; a[tot].next=h[x]; h[x]=tot; a[tot].dis=dis;
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
		mx[x]=max(mx[x],sz[u]);
	}
}

int get_rt(int Rt,int fa,int x)
{
	int u;
	if (sz[Rt]-sz[x]>mx[x]) mx[x]=sz[Rt]-sz[x];
	if (size>=mx[x]) rt=x,size=mx[x];
	for (int i=h[x];i!=-1;i=a[i].next)
	{
		u=a[i].y;
		if (u==fa||vis[u]) continue;
		get_rt(Rt,x,u);
	}
}

int dfs(int fa,int x,int d,int dist)
{
	int u;
	dep[x]=d; dis[x]=dist;
	f[x][0]=fa;
	for (int i=1;i<=TOP;++i) f[x][i]=f[f[x][i-1]][i-1];
	for (int i=h[x];i!=-1;i=a[i].next)
	{
		u=a[i].y;
		if (u==fa) continue;
		dfs(x,u,d+1,dist+a[i].dis);
	}
}

int get_lca(int x,int y)
{
	if (dep[x]<dep[y]) swap(x,y);
	for (int i=TOP;i>=0;--i)
		if (dep[f[x][i]]>=dep[y]) x=f[x][i];
	if (x==y) return x;
	for (int i=TOP;i>=0;--i)
		if (f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
	return f[x][0];
}

int solve(int x,int predis)
{
	int u,rt=x;
	ll tmp;
	x=get_root(x);

	get_info(x,0,x,0,0);
	sort(info[x].begin(),info[x].end());
	/*printf("#%d\n",x);
	debug(info[x]);*/

	tmp=0;
	for (int i=0;i<info[x].size();++i)
		tmp+=info[x][i].sec,sum[x].push_back(tmp);
	if (predis)
	{
		get_info(x,0,rt,predis,1);
		sort(finfo[x].begin(),finfo[x].end());
		tmp=0;
		for (int i=0;i<finfo[x].size();++i)
			tmp+=finfo[x][i].sec,fsum[x].push_back(tmp);
	}
	vis[x]=true;
	for (int i=h[x];i!=-1;i=a[i].next)
	{
		u=a[i].y;
		if (vis[u]) continue;
		Fa[solve(u,a[i].dis)]=x;
	}
	return x;
}

int get_dis(int x,int y)
{
	int lca=get_lca(x,y);
	return dis[x]+dis[y]-2*dis[lca];
}

int get_info(int st,int fa,int x,int dis,int op)//op==0 dist   1 fdist
{
	if (op) 
		finfo[st].push_back(mp(age[x],dis));
	else
		info[st].push_back(mp(age[x],dis));
	for (int i=h[x];i!=-1;i=a[i].next)
		if (a[i].y!=fa&&!vis[a[i].y])
			get_info(st,x,a[i].y,dis+a[i].dis,op);
}

ll calc(vector<Pr> &val,vector<ll> &s,int l,int r,int op)//op==0 sum  1 num
{
	l=get_l(val,l);
	r=get_r(val,r)-1;
	if (l>r) return 0;
//	printf("%d %d\n",l,r);
	if (op)
		return r-l+1;
	if (!l)
		return s[r];
	return s[r]-s[l-1];
}

int get_l(vector<Pr> &x,int val)
{
	int l=0,r=x.size()-1,mid;	
	while (l<=r)
	{
		mid=l+r>>1;
		if (x[mid].fir>=val) r=mid-1;
		else l=mid+1;
	}
	return l;
}

int get_r(vector<Pr> &x,int val)
{
	int l=0,r=x.size()-1,mid;
	while (l<=r)
	{
		mid=l+r>>1;
		if (x[mid].fir>val) r=mid-1;
		else l=mid+1;
	}
	return l;
}

ll query(int st,int x,int l,int r,int sonsz,ll sonsum)
{
	ll ret=0;
	if (Fa[x])
		ret=query(st,Fa[x],l,r,calc(finfo[x],fsum[x],l,r,1),calc(finfo[x],fsum[x],l,r,0));
	ret+=(ll)get_dis(st,x)*(calc(info[x],sum[x],l,r,1)-sonsz)+(calc(info[x],sum[x],l,r,0)-sonsum);
	return ret;
}

int debug(vector<Pr> x)
{
	printf("##############\n");
	for (int i=0;i<x.size();++i)
		printf("%d %d\n",x[i].fir,x[i].sec);
	printf("\n");
}

int debug1(vector<ll> x)
{
	printf("###############\n");
	for (int i=0;i<x.size();++i)
		printf("%d\n",x[i]);
	printf("\n");
}
