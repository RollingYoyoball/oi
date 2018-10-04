#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;
const int MAXN=100010;
ll c[15][MAXN];
int a[MAXN];
int n,m,k;
ll ans;
ll update(int x,int y,ll delta);
ll query(int x,int y);

int main()
{
	freopen("a.in","r",stdin);

	scanf("%d%d",&n,&k);
	int x;
	ll sum;
	for (int i=1;i<=n;++i)
	{
		scanf("%d",&x);
		update(1,x,1);
		for (int j=2;j<=k+1;++j)
		{
			sum=query(j-1,x-1);
			update(j,x,sum);
			if (j==k+1) ans+=sum;
		}
	}
	printf("%lld\n",ans);
}

ll update(int x,int y,ll delta)
{
	for (;y<=n;y+=y&-y)
		c[x][y]+=delta;
}

ll query(int x,int y)
{
	ll ret=0;
	for (;y>0;y-=y&-y)
		ret+=c[x][y];
	return ret;
}
