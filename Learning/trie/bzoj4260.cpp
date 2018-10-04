#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;
const int MAXN=4*100000+10;
const int MAX=30;
int ch[MAXN*4][2],a[MAXN];
int mxl[MAXN],mxr[MAXN];
int n,m,tot;
int insert(int x);
int calc(int x);

int main()
{
	freopen("a.in","r",stdin);

	scanf("%d\n",&n);
	for (int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	memset(mxl,0,sizeof(mxl));
	memset(mxr,0,sizeof(mxr));
	memset(ch,0,sizeof(ch));
	int now=0;
	tot=1;
	insert(0);
	for (int i=1;i<=n;++i)
	{
		now^=a[i];
		mxl[i]=calc(now);
		insert(now);
	}
	memset(ch,0,sizeof(ch));
	now=0;
	tot=1;
	insert(0);
	for (int i=n;i>=1;--i)
	{
		now^=a[i];
		mxr[i]=calc(now);
		insert(now);
	}
	int ansl=0;
	for (int i=1;i<=n;++i) 
		mxl[i]=max(mxl[i],mxl[i-1]);
	for (int i=n;i>=1;--i)
		mxr[i]=max(mxr[i+1],mxr[i]);
	for (int i=1;i<n;++i)
		ansl=max(ansl,mxl[i]+mxr[i+1]);
	printf("%d\n",ansl);
}

int insert(int x)
{
	bool w;
	int now=1;
	for (int i=MAX;i>=0;--i)
	{
		w=x&(1<<i);
		if (!ch[now][w]) 
			ch[now][w]=++tot;
		now=ch[now][w];
	}
}

int calc(int x)
{
	bool w;
	int now=1,re=0;
	for (int i=MAX;i>=0;--i)
	{
		w=x&(1<<i);
		if (ch[now][!w]) 
			re=re+(1<<i),now=ch[now][!w];
		else now=ch[now][w];
	}
	return re;
}
//亦或的奇妙性质imp a^a=0 a^0=a 
