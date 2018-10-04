#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#define inf 2147483647
#define TOP 18
using namespace std;
const int MAXN=100000+10;
int mn[MAXN][19],mx[MAXN][19],a[MAXN],f[MAXN];
int n,s,l;
int prework();
int query(int l,int r);

int main()
{
//	freopen("a.in","r",stdin);

	scanf("%d%d%d",&n,&s,&l);
	for (int i=1;i<=n;++i)
		scanf("%d",&a[i]),mx[i][0]=a[i],mn[i][0]=a[i];
	prework();
	int st=0;
	for (int i=1;i<=n;++i) f[i]=inf;
	f[0]=0;
	int tmp;
	for (int i=l;i<=n;++i)
	{
		while (i-st>=l&&(query(st+1,i)>s||f[st]==inf)) 
			++st,tmp=query(st,i);
		if (i-st>=l) f[i]=min(f[i],f[st]+1);
	}
	//这里的st表示的是上一个段的结尾 
	printf("%d\n",f[n]==inf?-1:f[n]);
}

int prework()
{
	for (int j=1;j<=log(n)/log(2);++j)
		for (int i=n-(1<<j)+1;i>=1;--i)
		{
			mx[i][j]=max(mx[i][j-1],mx[i+(1<<(j-1))][j-1]);
			mn[i][j]=min(mn[i][j-1],mn[i+(1<<(j-1))][j-1]);
		}
}

int query(int l,int r)
{
	int k=log((double)r-l+1)/log(2.0);
	return max(mx[l][k],mx[r-(1<<k)+1][k])-min(mn[l][k],mn[r-(1<<k)+1][k]);
}
