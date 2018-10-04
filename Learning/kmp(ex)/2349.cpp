#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=2010;
char a[MAXN][MAXN];
int nxt[MAXN][MAXN];
bool vis[MAXN];
int n,m,ans;
int get_nxt(int x);
bool work(int x,int y);

int main()
{
	freopen("a.in","r",stdin);

	scanf("%d\n",&m);
	for (int o=1;o<=m;++o)
	{
		scanf("%d",&n);
		ans=-1;
		memset(vis,false,sizeof(vis));
		for (int i=1;i<=n;++i)
		{
			scanf("%s",a[i]);
			get_nxt(i);
		}
		bool flag=true;
		for (int i=2;i<=n;++i)
			for (int j=1;j<i;++j)
			{
				if (vis[j]) continue;
				if (!work(j,i)) ans=i;
				else vis[j]=true;
			}
		printf("Case #%d: %d\n",o,ans);
	}	
}

int get_nxt(int x)
{
	nxt[x][0]=-1;
	int j=-1,len=strlen(a[x]);
	for (int i=1;i<len;++i)
	{
		while (j!=-1&&a[x][j+1]!=a[x][i]) j=nxt[x][j];
		if (a[x][j+1]==a[x][i]) ++j;
		nxt[x][i]=j;
	}
}

bool work(int x,int y)
{
	int j=-1,len=strlen(a[y]),len1=strlen(a[x]);
	for (int i=0;i<len;++i)
	{
		while (j!=-1&&a[x][j+1]!=a[y][i]) j=nxt[x][j];
		if (a[x][j+1]==a[y][i]) ++j;
		if (j==len1-1) return true;
	}
	return false;
}
