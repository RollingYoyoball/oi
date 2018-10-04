#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
#define MOD 1000000007
using namespace std;
const int MAXN=100010;
char s[MAXN];
int a[MAXN],nxt[MAXN];
int len,n,P,cnt;
int get_nxt();
int work(int b);

int main()
{
	freopen("a.in","r",stdin);

	scanf("%d%d\n",&n,&P);
	scanf("%s\n",s);
	len=strlen(s);
	for (int i=1;i<=P;++i)
		scanf("%d",a+i),--a[i];
	sort(a+1,a+1+P);	
	get_nxt();
	cnt=n;
	bool flag=true;
	if (P>0)
	{
		cnt-=len;
		for (int i=2;i<=P&&flag;++i)
		{
			if (a[i-1]+len>=a[i])
			{
				int tmp=a[i]-a[i-1];
				if (nxt[tmp]+a[i]==a[i-1]+len)
					cnt=cnt-len+(a[i-1]+len-a[i]);
				else 
					flag=false;
			}
			else cnt-=len;
		}
	}	
	if (!flag) printf("0\n");
	else
		printf("%d\n",work(cnt));
}

int get_nxt()
{
	int j=-1,st=0,p=0;
	nxt[0]=len;
	for (int i=1;i<len;++i,--j)
	{
		if (j<0||i+nxt[i-st]>=p)
		{
			if (j<0)
				p=i,j=0;
			while (p<len&&s[p]==s[j])
				++p,++j;
			nxt[i]=j;
			st=i;
		}
		else
			nxt[i]=nxt[i-st];
	}
}

int work(int b)
{
	int r=1,tmp=26;
	while (b)
	{
		if (b&1) r=((ll)r*tmp)%MOD;
		tmp=((ll)tmp*tmp)%MOD;
		b>>=1;
	}
	return r;
}
