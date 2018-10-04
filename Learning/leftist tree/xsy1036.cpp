#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;
const int MAXN=100010;
int lch[MAXN],rch[MAXN],dis[MAXN];
int f[MAXN],cost[MAXN],w[MAXN],sz[MAXN],pos[MAXN];
int n,m;
ll ans,sum[MAXN];
int merge(int x,int y);
int del(int x);
int add(int x,int fa);

int main()
{
//	freopen("a.in","r",stdin);

	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;++i)
	{
		scanf("%d%d%d",f+i,cost+i,w+i);
		sz[i]=1; pos[i]=i; sum[i]=cost[i];
	}
	ans=0;
	for (int i=n;i>=1;--i)
	{
		while (sum[i]>m) 
			del(i);
		add(i,f[i]);
		ans=max(ans,(ll)sz[i]*w[i]);	
	}
	printf("%lld\n",ans);
}

int merge(int x,int y)
{
	if (x==0||y==0) return x+y;
	if (cost[x]<cost[y]) swap(x,y);
	rch[x]=merge(rch[x],y);
	if (dis[lch[x]]<dis[rch[x]]) swap(lch[x],rch[x]);
	dis[x]=dis[rch[x]]+1;
	return x;
}

int add(int x,int fa)
{
	sum[fa]+=sum[x];
	sz[fa]+=sz[x];
	pos[fa]=merge(pos[fa],pos[x]);
}

int del(int x)
{
	sum[x]-=cost[pos[x]];
	--sz[x];
	pos[x]=merge(lch[pos[x]],rch[pos[x]]);
}
