#include<iostream>
#include<cstdio>
#include<cstring>
#define MOD 1000000007
#define ll long long
using namespace std;
const int MAXN=1000010;
char s[MAXN*2];
ll mx[MAXN*2];
ll sum[MAXN*2];
int n,m,len,ans;
int work();
ll fang(ll x) {return x*x%MOD;}
ll sumf(ll x) {return (x*(x+1)*(2*x+1)/6)%MOD;}
ll sum1(ll x) {return ((1+x)*x/2)%MOD;}

int main()
{
	freopen("a.in","r",stdin);

	char s1[MAXN];
	while (scanf("%s",s1)!=EOF)
	{
		len=strlen(s1);
		s[0]='$',s[1]='#';
		for (int i=0;i<len;++i)
			s[(i+1)*2]=s1[i],s[(i+1)*2+1]='#';
		memset(mx,0,sizeof(mx));
		ans=0;
		work();
		printf("%lld\n",ans);	
	}	
}

int work()
{
	int p=0,k=0;
	for (int i=2;i<len;++i)
	{
		if (p>i) 
		{
			if (mx[k*2-i]<p-i)
				mx[i]=mx[k*2-i],sum[i]=sum[k*2-i]+
			else
				mx[i]=p-i,sum[i]=
		}
		else 
		{
			mx[i]=1;
			if (i%2==0) sum[i]=fang(i%MOD);
		}
		while (s[mx[i]+i]==s[i-mx[i]])
		{
			++mx[i];
			if (i%2&&s[mx[i]+i]!='#'&&mx[i]+i<len) 
			   sum[i]=(sum[i]+((mx[i]+i)/2)*((mx[i]-i)/2)%MOD)%MOD;	
		}
		if (i+mx[i]) p=i+mx[i],k=i;
		ans=(ans+sum[i])%MOD;
	}
}
