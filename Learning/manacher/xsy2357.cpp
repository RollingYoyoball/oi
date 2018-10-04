#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=100010;
int s[MAXN*2];
int mx[MAXN*2],len1,len,ans;
int n,m;
int work();

int main()
{
	freopen("a.in","r",stdin);

	int x;
	scanf("%d",&m);
	for (int o=1;o<=m;++o)
	{
		scanf("%d",&n);
		s[0]=-2; s[1]=-1;
		for (int i=1;i<=n;++i)
			scanf("%d",&x),s[i*2]=x,s[i*2+1]=-1;
		memset(mx,0,sizeof(mx));
		ans=0;
		work();	
		printf("%d\n",ans-1);
	}	
}

int work()
{
	int p=0,k=0;
	for (int i=2;i<=n*2;++i)
	{
		if (p>i)
			mx[i]=min(mx[k*2-i],p-i); 
		else
			mx[i]=1;
		if (s[i]==-1&&s[i+mx[i]]==s[i-mx[i]]) ++mx[i];
		while (s[i+mx[i]]==s[i-mx[i]]&&(s[i+mx[i]]==-1||s[i+mx[i]]<=s[i+mx[i]-2]))
			++mx[i];
		if (i+mx[i]>p) p=i+mx[i],k=i;
		ans=max(ans,mx[i]);
	}		
}
