#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;
const int MAXN=100010;
struct xxx
{
	int y,next;
}a[MAXN];
int h[MAXN];
ll lch[MAXN],rch[MAXN],dist[MAXN],tp[MAXN];
ll lead[MAXN],num[MAXN];
ll sum[MAXN],salary[MAXN];
ll n,m,tot,rt,cnt;
ll ans;
int add(int x,int y);
int merge(int x,int y);
int dfs(int x);
ll max(ll x,ll y) {return x>y?x:y;}

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	
	int x;
	scanf("%lld%lld",&n,&m);
	rt=0;
	tot=0;
	memset(h,-1,sizeof(h));
	for (int i=1;i<=n;++i)
	{
		scanf("%d%lld%lld",&x,salary+i,lead+i);
		if (x!=0) add(x,i);
		else rt=i;
		lch[i]=rch[i]=0;
		dist[i]=-1;
	}
	memset(tp,0,sizeof(tp));
	ans=0; tot=0;
	dfs(1);
	printf("%lld\n",ans);
}

int add(int x,int y)
{
	a[++tot].y=y; a[tot].next=h[x]; h[x]=tot;
}

int merge(int x,int y)
{
	if (x==0) return y;
	if (y==0) return x;
	if (salary[x]<salary[y]) swap(x,y);
	rch[x]=merge(rch[x],y);
	if (dist[lch[x]]<dist[rch[x]]) swap(lch[x],rch[x]);
	dist[x]=min(dist[lch[x]]+1,dist[rch[x]]+1);
	return x;
}

int delt(int x)
{
	int l=lch[x],r=rch[x];
	lch[x]=rch[x]=0; dist[x]=-1;
	return merge(l,r);
}

int dfs(int x)
{
	tp[x]=x; num[x]=1;
	sum[x]=salary[x];
	int u;
	for (int i=h[x];i!=-1;i=a[i].next)
	{
		u=a[i].y;
		dfs(u);
		num[x]+=num[u];
		sum[x]+=sum[u];
		tp[x]=merge(tp[x],tp[u]);
	}
	while (sum[x]>m)
	{
		sum[x]-=salary[tp[x]];
		tp[x]=delt(tp[x]);
		--num[x];
	}
	ans=max(ans,1LL*lead[x]*num[x]);
}
/*10 9
8 7 9
3 2 7
8 2 6
10 3 0
8 4 1
9 8 8
10 7 1
10 9 6
10 5 7
0 4 0*/
