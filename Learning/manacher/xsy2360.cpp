#include<iostream>
#include<cstdio>
#include<cstring>
#define MOD 51123987
#define ll long long
using namespace std;
const int MAXN=2000000;
char s[MAXN*2];
int mx[MAXN*2],f[MAXN*2];
ll st[MAXN*2],ed[MAXN*2];
int markl[MAXN*2],markr[MAXN*2];
int n,m;
ll ans,sum;
int work();

int main()
{
	freopen("a.in","r",stdin);
	
	char ch;
	scanf("%d\n",&n);
	s[0]='$',s[1]='#';
	for (int i=1;i<=n;++i)
		scanf("%c",&ch),s[i*2]=ch,s[i*2+1]='#';
	work();
	st[0]=0; ed[n*2+1]=0;
	for (int i=1;i<=n;++i) 
		st[i]=(st[i-1]+markl[i])%MOD,ed[i]=(ed[i-1]+markr[i])%MOD;
	for (int i=1;i<=n;++i) 
		st[i]=(st[i-1]+st[i])%MOD,ed[i]=(ed[i-1]+ed[i])%MOD;
	
	for (int i=1;i<n;++i)
		ans=(ans+(ed[i]*(st[i+1]-st[i]))%MOD)%MOD;
	sum=((ed[n]-1)*ed[n])/2%MOD;
	printf("%lld\n",((sum+MOD)-ans)%MOD);
}

int work()
{
	int p=0,k=0;
	for (int i=2;i<=n*2;++i)
	{
		if (p>i) mx[i]=min(mx[2*k-i],p-i);
		else mx[i]=1;
		while (s[i+mx[i]]==s[i-mx[i]]) ++mx[i];
		if (i+mx[i]>p) p=i+mx[i],k=i;
		sum+=mx[i]/2;
		if (i%2) 
		{
			++markl[i/2-(mx[i]-1)/2+1],--markl[i/2+1];
			--markr[i/2+(mx[i]-1)/2+1],++markr[i/2+1];
		}
		else 
		{
			++markl[i/2-mx[i]/2+1],--markl[i/2+1];
			--markr[i/2+mx[i]/2],++markr[i/2];
		}
	}
}
