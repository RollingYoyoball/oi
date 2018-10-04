#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#define TOP 20
#define MOD 1000000007
#define ll long long
using namespace std;
const int MAXN=100010;
struct xxx
{
	int f[MAXN];
	int merge(int x,int y)
	{
		x=get_f(x),y=get_f(y);
		if (x!=y) f[x]=y;
	};
	int get_f(int x)
	{
		if (f[x]!=x) f[x]=get_f(f[x]);
		return f[x];
	};
}a[21];
int lg[MAXN];
int n,m,cnt,fx,fy;
ll ans;
int solve(int x,int y,int len);
ll ksm(int b);

int main()
{
	freopen("a.in","r",stdin);

	int l1,r1,l2,r2;
	scanf("%d%d",&n,&m);
	lg[1]=0;
	for (int i=2;i<=n;++i) lg[i]=lg[i>>1]+1;
	for (int i=1;i<=n;++i)
		for (int j=0;j<=lg[n];++j)
			a[j].f[i]=i;
	int len,k;
	for (int i=1;i<=n;++i)
	{
		scanf("%d%d%d%d",&l1,&r1,&l2,&r2);
		len=r1-l1+1,k=lg[len];
		solve(l1,l2,k),solve(r1-(1<<k)+1,r2-(1<<k)+1,k);
	}
	int tmp;
	cnt=-1;
	for (int i=1;i<=n;++i)
		if (a[0].get_f(i)==i) ++cnt;
	ans=(ksm(cnt)*9)%MOD;
	printf("%lld\n",ans);
}

int solve(int x,int y,int len)
{
	fx=a[len].get_f(x),fy=a[len].get_f(y);
	if (fx==fy) return 0;
	a[len].f[fx]=fy;
	if (len==0) return 0;
	solve(x,y,len-1);
	solve(x+(1<<len-1),y+(1<<len-1),len-1);
}

ll ksm(int b)
{
	ll r=1,c=10;
	while (b)
	{
		if (b&1) r=(r*c)%MOD;
		c=(c*c)%MOD;
		b>>=1;
	}
	return r;
}
