#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=200010;
int a[MAXN],s[MAXN];
int next1[MAXN];
int n,m;

int main()
{
	freopen("a.in","r",stdin);
	
	scanf("%d%d",&n,&m);
	if (m==1) 
	{
		printf("%d\n",n);
		return 0;
	}
	for (int i=1;i<=n;++i)
	{
		scanf("%d",&a[i]);
		if (i>1) a[i-1]=a[i-1]-a[i];
	}
	for (int i=1;i<=m;++i)
	{
		scanf("%d",&s[i]);
		if (i>1) s[i-1]=s[i-1]-s[i];
	}
	int j=0,ans=0;
	next1[1]=0;
	for (int i=2;i<m;++i)
	{
		while (j&&s[j+1]!=s[i]) 
			j=next1[j];
		if (s[j+1]==s[i]) ++j;
		next1[i]=j;
	}	
	j=0;
	for (int i=1;i<n;++i)
	{
		while (j&&s[j+1]!=a[i]) j=next1[j];
		if (s[j+1]==a[i]) ++j;
		if (j==m-1) ++ans,j=next1[j];	
	}
	printf("%d\n",ans);
}
