#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;
const int MAXN=500010;
int s[MAXN];
int mx[MAXN];
int n,m;
ll ans;
int work();

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);

	scanf("%d\n",&n);
	char ch,pre;
	s[0]=-2;
	for (int i=1;i<=n;++i)
	{
		pre=ch;
		scanf("%c",&ch); 
		if (i>1) s[i-1]=(ch-'0')^(pre-'0');
	}
	s[n]=-1;
	memset(mx,0,sizeof(mx));
	ans=0;
	work();	
	printf("%lld\n",ans);
}

int work()
{
	int p=0,k=0;
	for (int i=1;i<n;++i)
	{
		if (p>i)
			mx[i]=min(mx[2*k-i],p-i);
		else
			mx[i]=1;
		while (s[i+mx[i]]==s[i-mx[i]]) 
			++mx[i];
		if (i+mx[i]>p) p=i+mx[i],k=i;
		if (s[i]) ans+=mx[i];
	}
}
