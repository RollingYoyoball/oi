#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;
const int MAXN=1000010;
const int MOD=1000000007;
char s[MAXN];
ll next1[MAXN],num[MAXN];
int n,m;
ll len,ans;
int get_next1();

int main()
{
	freopen("a.in","r",stdin);

	scanf("%d",&n);
	for (int o=1;o<=n;++o)
	{
		scanf("%s\n",s);
		len=strlen(s);	
		ans=1;
		memset(next1,0,sizeof(next1));
		get_next1();
	}
}

int get_next1()
{
	int j=-1,k=0;
	num[0]=1;
	next1[0]=-1;
	for (int i=1;i<len;++i)
	{
		while (j!=-1&&s[j+1]!=s[i]) j=next1[j];
		if (s[j+1]==s[i]) ++j;
		next1[i]=j;
		num[i]=num[j]+1;
		
		while (k!=-1&&s[k+1]!=s[i]) k=next1[k];
		if (s[k+1]==s[i]) ++k;
		while (k+1>1+i>>1) 
			k=next1[k];
		ans=(ans*(num[k]+1))%MOD;
	}	
	printf("%lld\n",ans);
}
