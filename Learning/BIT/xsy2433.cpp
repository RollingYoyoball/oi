#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;
const int MAXN=100010;
ll c[2][MAXN];
ll a[MAXN];
int n,m;
int update(int mark,int x,ll delta);
ll query(int mark,int x);

int main()
{
	freopen("a.in","r",stdin);

	scanf("%d%d\n",&n,&m);
	for (int i=1;i<=n;++i)
	{
		scanf("%d",a+i);
		update(0,i,a[i]);
		update(1,i,a[i]*(n-i+1));
	}
	char op[10];
	int x,y;
	for (int i=1;i<=m;++i)
	{
		scanf("%s",op);
		if (op[0]=='Q')
		{
			scanf("%d",&x);
			printf("%lld\n",query(1,x)-query(0,x)*(n-x));
		}
		else
		{
			scanf("%d%d",&x,&y);
			update(0,x,y-a[x]);
			update(1,x,(y-a[x])*(n-x+1));
			a[x]=y;
		}
	}
}

int update(int mark,int x,ll delta)
{
	for (;x<=n;x+=x&-x)
		c[mark][x]+=delta;
}

ll query(int mark,int x)
{
	ll ret=0;
	for (;x>0;x-=x&-x)
		ret+=c[mark][x];
	return ret;
}
