#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
const int MAXN=2*(1e5)+10;
int a[MAXN],out[MAXN],num[MAXN],loc[MAXN];
int n,m,sq,all;
int prework();
int update(int x,int y);
int query(int x);

int main()
{
	freopen("a.in","r",stdin);

	int op,x,y;
	scanf("%d",&n);
	for (int i=1;i<=n;++i)
		scanf("%d",a+i);
	sq=sqrt(n);
	for (int i=1;i<=n;++i) 
		num[i]=i/sq+1;

	prework();
	scanf("%d",&m);
	for (int i=1;i<=m;++i)
	{
		scanf("%d",&op);
		if (op==1)
		{
			scanf("%d",&x);
			++x;
			printf("%d\n",query(x));
		}
		else
		{
			scanf("%d%d",&x,&y);
			++x;
			update(x,y);
		}
	}
}

int update(int x,int y)
{
	int tmp;
	a[x]=y;
	for (int i=x;i>=x/sq*sq;--i)
	{
		tmp=i+a[i];
		if (tmp>n)
			loc[i]=n+1,out[i]=1;
		else if (num[tmp]>num[i])
			loc[i]=tmp,out[i]=1;
		else
			loc[i]=loc[tmp],out[i]=out[tmp]+1;
	}
}

int query(int x)
{
	int ret=0;
	for (int i=x;i<=n;i=loc[i])
		ret+=out[i];
	return ret;
}

int prework()
{
	int tmp;
	for (int i=n;i>=1;--i)
	{
		tmp=i+a[i];
		if (tmp>n)
			loc[i]=n+1,out[i]=1;
		else if (num[tmp]>num[i])
			loc[i]=tmp,out[i]=1;
		else
			loc[i]=loc[tmp],out[i]=out[tmp]+1;
	}
}
