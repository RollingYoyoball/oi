#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;
const int MAXN=100010;
ll c[2][2][1010][1010];
int n,m;
int update(int x,int y,ll delta);
ll query(int x,int y);

int main()
{
	freopen("a.in","r",stdin);

	scanf("%d%d",&n,&m);
	int op,x1,y1,x2,y2,z;
	for (int i=1;i<=m;++i)
	{
		scanf("%d%d%d%d%d\n",&op,&x1,&y1,&x2,&y2);
		if (op==1)
		{
			printf("%lld\n",query(x1-1,y1-1)^query(x2,y2)^query(x1-1,y2)^query(x2,y1-1));
		}
		else
		{
			scanf("%d",&z);
			update(x1,y1,z); update(x2+1,y2+1,z);
			update(x1,y2+1,z); update(x2+1,y1,z);
		}
	}
}

int update(int x,int y,ll delta)
{
	for (int i=x;i<=n+1;i+=i&-i)
		for (int j=y;j<=n+1;j+=j&-j)
			c[x&1][y&1][i][j]^=delta;
}

ll query(int x,int y)
{
	ll ret=0;
	for (int i=x;i;i-=i&-i)
		for (int j=y;j;j-=j&-j)
			ret^=c[x&1][y&1][i][j];
	return ret;
}
