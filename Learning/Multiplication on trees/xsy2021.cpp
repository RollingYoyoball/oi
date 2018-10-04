#include<iostream>
#include<cstdio>
#include<cstring>
#define TOP 14
using namespace std;
const int MAXN=100000+10;
struct xxx
{
	int y,next;
}a[MAXN*2];
struct xxx1
{
	int node,flag;
}mid1,mid2;
int h[MAXN],f[MAXN][15],sz[MAXN],dep[MAXN];
int n,m,tot,T,loc1,loc2,loc3;
int add(int x,int y);
int dfs(int fa,int x,int d);
int work(int x,int y,int z,int lca1,int lca2);
int get_lca(int x,int y);
xxx1 get_mid(int x,int y,int lca);
int get_node(int x,int len);

int main()
{
	freopen("a.in","r",stdin);

	int x,y,z;
	scanf("%d",&T);
	for (int o=1;o<=T;++o)
	{
		scanf("%d",&n);
		memset(h,-1,sizeof(h));
		tot=0;
		for (int i=1;i<n;++i)
		{
			scanf("%d%d",&x,&y);
			add(x,y); add(y,x);
		}
		dfs(0,1,0);
		scanf("%d",&m);
		for (int i=1;i<=m;++i)
		{
			scanf("%d%d%d",&loc1,&loc2,&loc3);
			x=get_lca(loc1,loc2); y=get_lca(loc2,loc3); z=get_lca(loc3,loc1);
			printf("%d %d %d\n",work(loc1,loc2,loc3,x,z),work(loc2,loc3,loc1,y,x),work(loc3,loc2,loc1,y,z));
		}
	}
}

int add(int x,int y)
{
	a[++tot].y=y; a[tot].next=h[x]; h[x]=tot;
}

int dfs(int fa,int x,int d)
{
	int u;
	f[x][0]=fa; sz[x]=1; dep[x]=d;
	for (int i=1;i<=TOP;++i) f[x][i]=f[f[x][i-1]][i-1];
	for (int i=h[x];i!=-1;i=a[i].next)
	{
		u=a[i].y;
		if (u==fa) continue;
		dfs(x,u,d+1);
		sz[x]+=sz[u];	
	}
}

int get_lca(int x,int y)
{
	if (dep[x]<dep[y]) swap(x,y);
	for (int i=TOP;i>=0;--i)
		if (dep[f[x][i]]>=dep[y])
			x=f[x][i];
	if (x==y) return x;
	for (int i=TOP;i>=0;--i)
		if (f[x][i]!=f[y][i])
			x=f[x][i],y=f[y][i];
	return f[x][0];
}

int work(int x,int y,int z,int lca1,int lca2)
{
	mid1=get_mid(x,y,lca1),mid2=get_mid(x,z,lca2);
	int tmp;
	if (mid1.flag==1&&mid2.flag==1)//down
	{
		return dep[mid1.node]>dep[mid2.node]?sz[mid1.node]:sz[mid2.node];
	}
	else if (mid1.flag==2&&mid2.flag==2)//top
	{
		if (dep[mid1.node]<dep[mid2.node]) swap(mid1,mid2);
		tmp=get_lca(mid1.node,mid2.node);
		if (tmp==mid2.node) return n-sz[mid2.node];
		return n-sz[mid2.node]-sz[mid1.node];		
	}
	else //mid
	{
		if (mid1.flag==2) swap(mid1,mid2);
		tmp=get_lca(mid1.node,mid2.node);
		if (tmp==mid1.node) return sz[mid1.node]-sz[mid2.node];
		return 	sz[mid1.node];	
	}
}

xxx1 get_mid(int x,int y,int lca)
{
	xxx1 re;
	if (dep[x]>=dep[y])//down
		re.flag=1,re.node=get_node(x,(dep[x]+dep[y]-2*dep[lca]-1)/2);
	else//up
		re.flag=2,re.node=get_node(y,(dep[x]+dep[y]-2*dep[lca])/2);
	return re;
}

int get_node(int x,int len)
{
	int now=0;
	for (int i=TOP;i>=0;--i)
		if (now+(1<<i)<=len) now+=1<<i,x=f[x][i];
	return x;
}
