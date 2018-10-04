#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=100010;
struct xxx
{
	int y,next;
}a[MAXN];
int h[MAXN],v[MAXN];
int n,m,tot,ans,s;
int dfs(int x,int sum);
int add(int x,int y);

int main()
{
	freopen("a.in","r",stdin);

	int x,y;
	scanf("%d%d\n",&n,&s);
	for (int i=1;i<=n;++i) scanf("%d",v+i);
	memset(h,-1,sizeof(h));
	tot=0;
	for (int i=1;i<=n;++i)
	{
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	ans=0;
	for (int i=1;i<=n;++i)
		dfs(i,v[i]);
	printf("%d\n",ans);
}

int dfs(int x,int sum)
{
	if (sum==s) ++ans;
	if (sum>s) return 0;
	for (int i=h[x];i!=-1;i=a[i].next)
		dfs(a[i].y,sum+v[a[i].y]);
}

int add(int x,int y)
{
	a[++tot].y=y; a[tot].next=h[x]; h[x]=tot;
}
