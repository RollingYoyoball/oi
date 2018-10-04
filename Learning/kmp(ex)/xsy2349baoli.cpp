#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
char s[2010][2010];
bool vis[2010];
int n,m,ans;

int main()
{
	freopen("a.in","r",stdin);

	scanf("%d",&m);
	for (int o=1;o<=m;++o)
	{
		ans=-1;
		scanf("%d",&n);
		memset(vis,false,sizeof(vis));
		for (int i=1;i<=n;++i)
		{
			scanf("%s",s[i]);
			for (int j=1;j<i;++j)
			{
				if (vis[j]) continue;
				if (strstr(s[i],s[j])==NULL) ans=i;
				else vis[j]=true;
			}
		}
		printf("Case #%d: %d\n",o,ans); 
	}
}
