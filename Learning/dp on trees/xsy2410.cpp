#include<iostream>
#include<cstdio>
#include<cstring>
#define MOD 1000000007
#define ll long long
using namespace std;
const int MAXN=2010;
struct xxx
{
	int y,next;
}a[MAXN*2];
int h[MAXN],v[MAXN];
bool used[MAXN];
ll f[MAXN];
int n,tot,d;
ll ans;
int dfs(int fa,int x,int mx,int now);
int add(int x,int y);

int main()
{
//	freopen("a.in","r",stdin);
//	freopen("a.out","w",stdout);

	scanf("%d%d",&d,&n);
	for (int i=1;i<=n;++i)
		scanf("%d",v+i);
	int x,y;
	memset(h,-1,sizeof(h));
	tot=0;
	for (int i=1;i<n;++i)
	{
		scanf("%d%d",&x,&y);
		add(x,y); add(y,x);
	}
	ans=0;
	memset(used,false,sizeof(used));
	for (int i=1;i<=n;used[i++]=true)
		dfs(0,i,v[i],i),ans=(ans+f[i])%MOD;
	printf("%lld\n",ans);
}

int dfs(int fa,int x,int mx,int now)
{
	int u,tmp;
	f[x]=1;
	for (int i=h[x];i!=-1;i=a[i].next)
	{
		u=a[i].y;
		if (u==fa) continue;
		if (v[u]<v[now]||(v[u]>mx&&v[u]-v[now]>d)) continue;
		if (v[u]==v[now]&&used[u]) continue;
		dfs(x,u,max(mx,v[u]),now);
		f[x]=(f[x]*f[u]+f[x])%MOD;
	}
}

int add(int x,int y)
{
	a[++tot].y=y; a[tot].next=h[x]; h[x]=tot;
}
