#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
#define TOP 16///!!!
#define up 60
using namespace std;
const int MAXN=20010;
struct xxx
{
	int y,next;
}a[MAXN*2];
struct xx1
{
	ll a[61];
	void insert(ll val)
	{
		for (int i=up;i>=0;--i)
			if (val&((ll)1<<i))
			{
				if (!a[i]) 
				{
					a[i]=val;
					break;
				}
				val^=a[i];
			}
	};
	ll get_mx()
	{
		ll re=0;
		for (int i=up;i>=0;--i)
			if ((re^a[i])>re) re^=a[i];
		return re;
	};
}f1[MAXN][20],ans;
int h[MAXN],f[MAXN][20],dep[MAXN];
int n,m,tot;
int add(int x,int y);
int dfs(int fa,int x,int d);
ll get_lca(int x,int y);
xx1 merge(xx1 a,xx1 b);

int main()
{
	freopen("a.in","r",stdin);

	int x,y;
	ll xx;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;++i) 
		scanf("%lld",&xx),f1[i][0].insert(xx);
	memset(h,-1,sizeof(h));
	tot=0;
	for (int i=1;i<n;++i)
	{
		scanf("%d%d",&x,&y);
		add(x,y); add(y,x);
	}
	dfs(0,1,0);
	for (int i=1;i<=m;++i)
	{
		scanf("%d%d",&x,&y);
		printf("%lld\n",get_lca(x,y));
	}	
}

int add(int x,int y)
{
	a[++tot].y=y; a[tot].next=h[x]; h[x]=tot;
}

int dfs(int fa,int x,int d)
{
	int u;
	f[x][1]=fa;
	f1[x][1]=merge(f1[x][0],f1[fa][0]);
	dep[x]=d;
	for (int i=2;i<=TOP;++i)
	{
		f[x][i]=f[f[x][i-1]][i-1];
		f1[x][i]=merge(f1[f[x][i-1]][i-1],f1[x][i-1]);
	}
	for (int i=h[x];i!=-1;i=a[i].next)
	{
		u=a[i].y;
		if (u==fa) continue;
		dfs(x,u,d+1);
	}
}

xx1 merge(xx1 a,xx1 b)
{
	for (int i=0;i<=up;++i)
		if (b.a[i]) a.insert(b.a[i]);
	return a;
}

ll get_lca(int x,int y)
{
	memset(ans.a,0,sizeof(ans.a));
	if (dep[x]<dep[y]) swap(x,y);
	for (int i=TOP;i>=1;--i)
		if (dep[f[x][i]]>=dep[y])
		{
			ans=merge(ans,f1[x][i]);
			x=f[x][i];
		}
	if (x==y)
	{
		ans=merge(ans,f1[x][0]);
		return ans.get_mx();
	}
	for (int i=TOP;i>=1;--i)
		if (f[x][i]!=f[y][i])
		{
			ans=merge(ans,f1[x][i]);
			ans=merge(ans,f1[y][i]);
			x=f[x][i],y=f[y][i];
		}
	ans=merge(ans,f1[x][1]);
	ans=merge(ans,f1[y][1]);
	return ans.get_mx();
}
