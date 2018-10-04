#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define TOP 20//!!!
using namespace std;
const int MAXN=100000+10;
struct xxx
{
	int y,next;
}a[MAXN*2];
struct xx1
{
	int a[15],cnt;
}fs[MAXN][21],re,ans;
int h[MAXN],f[MAXN][21],dep[MAXN];
int n,m,q,tot,t1,t2;
int dfs(int fa,int x,int d);
xx1 get_mn(xx1 fs1,xx1 fs2);
int get_lca(int x,int y,int k);
int add(int x,int y);

int main()
{
	freopen("a.in","r",stdin);
//	freopen("a.out","w",stdout);
	
	int x,y,z;
	scanf("%d%d%d\n",&n,&m,&q);
	memset(h,-1,sizeof(h));
	tot=0;
	for (int i=1;i<n;++i)
	{
		scanf("%d%d",&x,&y);
		add(x,y); add(y,x);
	}
	for (int i=1;i<=m;++i) 
	{
		scanf("%d",&x);
		fs[x][0].a[++fs[x][0].cnt]=i;
	}
	dfs(0,1,0);
	for (int i=1;i<=q;++i)
	{
		scanf("%d%d%d",&x,&y,&z);
		get_lca(x,y,z);
	}
}

int dfs(int fa,int x,int d)
{
	int u;
	f[x][1]=fa;
	fs[x][1]=get_mn(fs[x][0],fs[fa][0]);
	dep[x]=d;
	for (int i=2;i<=TOP;++i)
	{
		f[x][i]=f[f[x][i-1]][i-1];
		fs[x][i]=get_mn(fs[f[x][i-1]][i-1],fs[x][i-1]);
	}
	for (int i=h[x];i!=-1;i=a[i].next)
	{
		u=a[i].y;
		if (u==fa) continue;
		dfs(x,u,d+1);
	}
}

int add(int x,int y)
{
	a[++tot].y=y; a[tot].next=h[x]; h[x]=tot;
}

xx1 get_mn(xx1 fs1,xx1 fs2)
{
	t1=t2=1; re.cnt=0;
	while (t1<=fs1.cnt&&t2<=fs2.cnt&&re.cnt<10)
	{
		if (fs1.a[t1]<fs2.a[t2]) re.a[++re.cnt]=fs1.a[t1];
		else re.a[++re.cnt]=fs2.a[t2];
		if (fs1.a[t1]==re.a[re.cnt]) ++t1;
		if (fs2.a[t2]==re.a[re.cnt]) ++t2;
	}	
	for (int i=t1;i<=fs1.cnt&&re.cnt<10;++i) re.a[++re.cnt]=fs1.a[i];
	for (int i=t2;i<=fs2.cnt&&re.cnt<10;++i) re.a[++re.cnt]=fs2.a[i];
	return re;
}

int get_lca(int x,int y,int k)
{
	if (dep[x]<dep[y]) swap(x,y);	
	memset(ans.a,0,sizeof(ans.a));
	ans.cnt=0;
	for (int i=TOP;i>=1;--i)
		if (dep[f[x][i]]>=dep[y])
		{
			ans=get_mn(ans,fs[x][i]);
			x=f[x][i];
		}
	ans=get_mn(ans,fs[x][0]);
	if (x==y)
	{
		k=min(ans.cnt,k);
		printf("%d ",k);
		for (int i=1;i<=k;++i) 
			printf("%d ",ans.a[i]);
		printf("\n");	
		return 0;
	}
	for (int i=TOP;i>=1;--i)
		if (f[x][i]!=f[y][i])
		{
			ans=get_mn(ans,fs[x][i]);
			ans=get_mn(ans,fs[y][i]);
			x=f[x][i],y=f[y][i];
		}
	ans=get_mn(ans,fs[x][1]);
	ans=get_mn(ans,fs[y][1]);
	k=min(ans.cnt,k);
	printf("%d ",k);
	for (int i=1;i<=k;++i)
		printf("%d ",ans.a[i]);
	printf("\n");
}
